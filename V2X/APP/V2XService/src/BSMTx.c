/*******************************************************************************
 * 文 件 名 称 ： BSMTx.c
 * 功 能 描 述 ： BSM发送模块，接收VDS模块数据并组包发送
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#include "Common.h"
#include "pathHistoryAPI.h"
#include "pathRadius.h"

#define MODULE_NAME "BSMTx"
#include "Debug.h"

#define BSM_THR_CYCLE 5U
int g_n32Triger = 0;

//用于外部引用全局变量
TMsgVehDataFrame_t g_tDbusVehDataFrame;
static bool g_bIsSecurityRandomId = false;
char g_aBsmDynamicId[8] = "NLLST409";

//用于本文件内部使用的全局变量
static THR_mutex_t g_tBsmTimerCbMutex = PTHREAD_MUTEX_INITIALIZER;
static THR_mutex_t g_tBsmMsgUpdateMutex = PTHREAD_MUTEX_INITIALIZER;
static float g_f32V2xCbr = 0.0;
SendBuffer *g_pMsgSendBuffer = NULL;
//pthread_mutex_t
static uint8_t g_u8MsgCnt = 0;

static int BSMTimerPeriod = 100;

static void FV_SendBsmPackage();
static int FV_GenerateBSMTxCycleTime(float p_f32V2xCbr, uint16_t p_u16Speed);
static WJVN4_BIT_BrakeAppliedStatus FV_ConvertBrakeAppliedStatus(uint8_t p_u8BrakeAppliedStatus);
static WJVN4_BIT_ExteriorLights FV_ConvertDExteriorLightsStruct(VehCANData_dbus VechCan);
static WJV2_BIT_ExteriorLights FV_ConvertDExteriorV2LightsStruct(VehCANData_dbus VechCan);
static void FV_TriggerEmergencyBsmMessage(TVehData_t p_ptVehData);
static void FV_V2xSendSrvFaultPush(void);
static void FV_UpdateBsmComponentsBySecurityCertChange(void);

pthread_mutex_t g_SendFuncMutex = PTHREAD_MUTEX_INITIALIZER;

/***********************************************************************
 * 函 数 名 称 ： FV_GenerateBSMTxCycleTime
 * 功 能 描 述 ： 生成BSM消息发送周期
 * 输 入 参 数 ： p_f32V2xCbr           V2X协议栈CBR拥塞值
 * 输 入 参 数 ： p_u16Speed            车速
 * 输 出 参 数 ：无
 * 返  回  值  :  BSM动态周期值
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
static int FV_GenerateBSMTxCycleTime(float p_f32V2xCbr, uint16_t p_u16Speed)
{
    if (FLOAT_CMP_EQ(p_f32V2xCbr, V2X_STACK_CBR_MIN) && FLOAT_CMP_EQ(V2X_STACK_CBR_LV2, p_f32V2xCbr))
    {
        return BSMTX_CYCLE_100MS;
    }
    else if (FLOAT_CMP(p_f32V2xCbr, V2X_STACK_CBR_LV2) && FLOAT_CMP_EQ(V2X_STACK_CBR_LV3, p_f32V2xCbr))
    {
        if (p_u16Speed >= VEHICLE_SPEED_MIN && p_u16Speed <= VEHICLE_SPEED_LV1)
        {
            return BSMTX_CYCLE_1000MS;
        }
        else if (p_u16Speed > VEHICLE_SPEED_LV1 && p_u16Speed <= VEHICLE_SPEED_LV2)
        {
            return BSMTX_CYCLE_500MS;
        }
        else if (p_u16Speed > VEHICLE_SPEED_LV2 && p_u16Speed <= VEHICLE_SPEED_LV3)
        {
            return BSMTX_CYCLE_200MS;
        }
        else
        {
            return BSMTX_CYCLE_100MS;
        }
    }
    else if (FLOAT_CMP(p_f32V2xCbr, V2X_STACK_CBR_LV3) && FLOAT_CMP_EQ(V2X_STACK_CBR_LV4, p_f32V2xCbr))
    {
        if (p_u16Speed >= VEHICLE_SPEED_MIN && p_u16Speed <= VEHICLE_SPEED_LV1)
        {
            return BSMTX_CYCLE_1000MS;
        }
        else if (p_u16Speed > VEHICLE_SPEED_LV1 && p_u16Speed <= VEHICLE_SPEED_LV2)
        {
            return BSMTX_CYCLE_500MS;
        }
        else if (p_u16Speed > VEHICLE_SPEED_LV2 && p_u16Speed <= VEHICLE_SPEED_LV3)
        {
            return BSMTX_CYCLE_400MS;
        }
        else
        {
            return BSMTX_CYCLE_100MS;
        }
    }
    else
    {
        return BSMTX_CYCLE_100MS; /* Return the default timing cycle. */
    }
}

static WJV2_BIT_DriveBehavior FV_ConverDriveBehaviorStatus(uint8_t p_u8BrakeAppliedStatus)
{
    WJV2_BIT_DriveBehavior l_tDriveBehavior;
    uint16_t tmp = ((uint16_t)p_u8BrakeAppliedStatus) << 3;
    memcpy(&l_tDriveBehavior, &tmp, WJV2_LEN_BYTE_DriveBehavior);
    return l_tDriveBehavior;
}
static WJVN4_BIT_BrakeAppliedStatus FV_ConvertBrakeAppliedStatus(uint8_t p_u8BrakeAppliedStatus)
{
    WJVN4_BIT_BrakeAppliedStatus l_tBrakeStatus;
    memcpy(&l_tBrakeStatus, &p_u8BrakeAppliedStatus, WJVN4_LEN_BYTE_EXTERIORLIGHT);
    return l_tBrakeStatus;
}
static WJVN4_BIT_ExteriorLights FV_ConvertDExteriorLightsStruct(VehCANData_dbus VechCan)
{
    WJVN4_BIT_ExteriorLights l_tExteriorLights;
    uint16_t tmp = 0;
    //memcpy(&l_tExteriorLights.bit, &p_u16ExteriorLights, DE_ExteriorLights_un_len);
    tmp = ((uint16_t)VechCan.m_LowBeamSt.m_u8_RecVehLampMessage | ((uint16_t)VechCan.m_HighBeamSt.m_u8_RecVehLampMessage << 1) | ((uint16_t)VechCan.m_LeftTurnLampSt.m_u8_RecVehLampMessage << 2) | ((uint16_t)VechCan.m_RightTurnLampSt.m_u8_RecVehLampMessage << 3) | ((uint16_t)VechCan.m_HazardLampSt.m_u8_RecVehLampMessage << 4) | ((uint16_t)VechCan.m_RearFogLampSt.m_u8_RecVehLampMessage << 7) | ((uint16_t)VechCan.m_ParkingLampSt.m_u8_RecVehLampMessage) << 8);
    memcpy(&l_tExteriorLights, &tmp, WJVN4_LEN_BYTE_EXTERIORLIGHT);
    return l_tExteriorLights;
}
static WJV2_BIT_ExteriorLights FV_ConvertDExteriorV2LightsStruct(VehCANData_dbus VechCan)
{
    WJV2_BIT_ExteriorLights l_tExteriorLights;
    uint16_t tmp = 0;
    //memcpy(&l_tExteriorLights.bit, &p_u16ExteriorLights, DE_ExteriorLights_un_len);
    tmp = ((uint16_t)VechCan.m_LowBeamSt.m_u8_RecVehLampMessage | ((uint16_t)VechCan.m_HighBeamSt.m_u8_RecVehLampMessage << 1) | ((uint16_t)VechCan.m_LeftTurnLampSt.m_u8_RecVehLampMessage << 2) | ((uint16_t)VechCan.m_RightTurnLampSt.m_u8_RecVehLampMessage << 3) | ((uint16_t)VechCan.m_HazardLampSt.m_u8_RecVehLampMessage << 4) | ((uint16_t)VechCan.m_RearFogLampSt.m_u8_RecVehLampMessage << 7) | ((uint16_t)VechCan.m_ParkingLampSt.m_u8_RecVehLampMessage) << 8);
    memcpy(&l_tExteriorLights, &tmp, WJVN4_LEN_BYTE_EXTERIORLIGHT);
    return l_tExteriorLights;
}

#define IS_EMERGGECY(veh_data)                                \
    (veh_data.m_warningevent.Event.m_event_HazardLights ||    \
     veh_data.m_warningevent.Event.m_event_ABS ||             \
     veh_data.m_warningevent.Event.m_event_Traction ||        \
     veh_data.m_warningevent.Event.m_event_Stability ||       \
     veh_data.m_warningevent.Event.m_event_HardBraking ||     \
     veh_data.m_warningevent.Event.m_event_FlatTire ||        \
     veh_data.m_warningevent.Event.m_event_DisabledVehicle || \
     veh_data.m_warningevent.Event.m_event_AirBagDeployment)

static void FV_TriggerEmergencyBsmMessage(TVehData_t p_ptVehData)
{
    if (IS_EMERGGECY(p_ptVehData))
    {
        //触发紧急BSM消息，立即进行发送
        DBG("触发紧急BSM消息，立即进行发送\n");
        FV_SendBsmPackage(BSM);
    }
}
static void FV_InitativeSendMessage(TrigeInitative *trig)
{
    if (YES == *trig)
    {
        printf("=== V2XFRAME SEND ===START ====\n");
        //触发紧急BSM消息，立即进行发送
        DBG("触发紧急V2XFRAME消息，立即进行发送\n");
        FV_SendBsmPackage(V2FRAME);
        *trig = NO;
    }
}

int encode_code_BSM(WJVN4_STRU_MessageFrame *pmsg_frame)
{
    pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_OrdinaryConven_en;
    pmsg_frame->uniUperMsg.strubsmFrame.u8posAccuracyPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.u8posConfidencePresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.u8anglePresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.u8MotionConfidenceSetPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.u8safetyExtPresent = WJVN4_ABSENT;    // MSG_OPTIONAL_YES;
    pmsg_frame->uniUperMsg.strubsmFrame.u8emergencyExtPresent = WJVN4_ABSENT; // MSG_OPTIONAL_YES;

    /* Data */
    //    DE_MsgCount_t                         msgCnt; /* Msg count. *///
    pmsg_frame->uniUperMsg.strubsmFrame.n32msgCnt = 120;
    //    DE_TemporaryID_st                         bsm_id; /* Product id. *///
    pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid[0] = 0x11;
    pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid[1] = 0x21;
    pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid[2] = 0x31;
    pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid[3] = 0x41;

    //    DE_DSecond_t                         bsm_secMark; /* DSRC second. Unit: millisecond. *///
    pmsg_frame->uniUperMsg.strubsmFrame.n32secMark = 47295;
    //    DE_TimeConfidence_en           bsm_timeConfidence; /* timeConfidence */;
    pmsg_frame->uniUperMsg.strubsmFrame.u8timeConfidencePresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.enumtimeConfidence = WJVN4_TimeConfidencetime0000005;
    //    DF_Position3D_st                         bsm_pos; /* position */
    pmsg_frame->uniUperMsg.strubsmFrame.strupos.u8elevationPresent = WJVN4_PRESENT;

    static double l_dlat = 40.0470699;
    pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32lat = 40.0470699;
    l_dlat += 0.000001;

    pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32long = 116.2891714;

    pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32elevation = 54.4;
    //    DF_PositionalAccuracy_st             posAccuracy; /* Vehicle position accuracy. */
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32semiMajor = 0.1;
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32semiMajor = 0.2;
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32orientation = 0.3;
    //    DF_PositionConfidenceSet_st                bsm_posCon; /* Vehicle position accuracy. */
    pmsg_frame->uniUperMsg.strubsmFrame.struposConfidence.u8elevationPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.struposConfidence.enumpos = WJVN4_PositionConfidencea10m;
    pmsg_frame->uniUperMsg.strubsmFrame.struposConfidence.enumelevation = WJVN4_ElevationConfidenceelev050_00;
    //    DE_TransmissionState_en                    bsm_trans; /* Transmission status. */
    pmsg_frame->uniUperMsg.strubsmFrame.enumtransmission = WJVN4_TransmissionStatereserved1;
    //    DE_Speed_t                                 bsm_speed; /* Driving speed. Unit km/h. */
    pmsg_frame->uniUperMsg.strubsmFrame.n32speed = 10.6;
    //    DE_Heading_t                             bsm_heading; /* Driving direction. Unit degree. */
    pmsg_frame->uniUperMsg.strubsmFrame.n32heading = 5.0;
    //    DE_SteeringWheelAngle_t                    bsm_angle; /* Steering wheel angle. Unit degree. optional*/
    pmsg_frame->uniUperMsg.strubsmFrame.n32angle = 30.000;
    //    DF_MotionConfidenceSet_st              bsm_motioncfd; /* motion confidenceset optional*/
    pmsg_frame->uniUperMsg.strubsmFrame.strumotionCfd.u8speedCfdPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strumotionCfd.u8headingCfdPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strumotionCfd.u8steerCfdPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strumotionCfd.enumspeedCfd = WJVN4_SpeedConfidenceprec5ms;
    pmsg_frame->uniUperMsg.strubsmFrame.strumotionCfd.enumheadingCfd = WJVN4_HeadingConfidenceprec05deg;
    //    DF_AccelerationSet4Way_st                bsm_acceSet; /* Driving acceleration set. */
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32lat = 10.000;
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32long = 9.000;
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32vert = 8.000;
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32yaw = 7.000;
    //    DF_BrakeSystemStatus_st               bsm_brakes; /* Brake system status. */
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8absPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8auxBrakesPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8brakePadelPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8scsPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8tractionPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8wheelBrakesPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8brakeBoostPresent = WJVN4_PRESENT;

    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.enumabs = WJVN4_AntiLockBrakeStatusoff;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.enumauxBrakes = WJVN4_AuxiliaryBrakeStatusoff;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.enumbrakeBoost = WJVN4_BrakeBoostAppliedoff;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.enumbrakePadel = WJVN4_BrakePedalStatusoff;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.enumscs = WJVN4_StabilityControlStatusoff;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.enumtraction = WJVN4_TractionControlStatusoff;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.strbitwheelBrakes.u8BrakeAppliedStatus[0] = 0;

    //    DF_VehicleSize_st                       bsm_size; /* Vehicle size. */
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.u8heightPresent = WJVN4_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32height = 2;
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32length = 5;
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32width = 2;
    //    DF_VehicleClassification_st     bsm_vehcls; /* vehicle class*/
    pmsg_frame->uniUperMsg.strubsmFrame.struvehicleClass.n32classification = WJVN4_BasicVehicleClasspassengerVehicleTypeUnknown;
    pmsg_frame->uniUperMsg.strubsmFrame.struvehicleClass.u8fuelTypePresent = WJVN4_ABSENT;
    return 0;
}

static void FV_SendBsmPackage(SendFrameTpye sendframetype)
{
    MSG_MessageType_st *l_tBsmMsgBuffer = NULL;

    pthread_mutex_lock(&g_SendFuncMutex);

    if (BSM == sendframetype)
    {
        //调用发送接口发送
        if (ProtocolStackParamConfig.messageParamConfig.m_SendParam[0].m_nSendSwitch == 1)
        {
            //FV_CallocBsmGlobalBuffer();
            if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == 4)
            {
                pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
                g_pMsgSendBuffer->m_msgbufer.messageType = MSG_MessageType_ID_Four;
                FV_CreateBsmMinmumPackage(&(g_pMsgSendBuffer->m_msgbufer.msgtype.MessageFour), g_tDbusVehDataFrame.m_MsgData);
                pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
            }
            else if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == 5)
            {
                pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
                g_pMsgSendBuffer->m_msgbufer.messageType = MSG_MessageType_ID_NEW_Four;
                FV_CreateBsmMinmumPackage(&(g_pMsgSendBuffer->m_msgbufer.msgtype.MessageNewFour), g_tDbusVehDataFrame.m_MsgData);
                pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
            }
            else if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == 2)
            {
                pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
                g_pMsgSendBuffer->m_msgbufer.messageType = MSG_MessageType_ID_Two;
                FV_CreateV2BsmMinmumPackage(&(g_pMsgSendBuffer->m_msgbufer.msgtype.MessageTwo), g_tDbusVehDataFrame.m_MsgData);
                pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
            }
            else
            {
                /* code */
            }

            l_tBsmMsgBuffer = calloc(1, sizeof(MSG_MessageType_st));
            // actual sending action
            pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
            memcpy(l_tBsmMsgBuffer, &(g_pMsgSendBuffer->m_msgbufer), sizeof(MSG_MessageType_st));
            pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
            LogPrint(LOG_LEVEL_DEBUG, STACK_MSG_MODULE, "Send msgType %d  %d", g_pMsgSendBuffer->m_msgbufer.messageType,
                     l_tBsmMsgBuffer->messageType);
            SendFrameMessageData(l_tBsmMsgBuffer);
        }
    }
    else if (V2FRAME == sendframetype)
    { /* code */
    }
    else
    {
        return;
    }
    // l_tBsmMsgBuffer = calloc(1, sizeof(MSG_MessageType_st));
    // // actual sending action
    // pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
    // memcpy(l_tBsmMsgBuffer, &(g_pMsgSendBuffer->m_msgbufer), sizeof(MSG_MessageType_st));
    // pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
    // LogPrint(LOG_LEVEL_DEBUG, STACK_MSG_MODULE, "Send msgType %d  %d", g_pMsgSendBuffer->m_msgbufer.messageType,
    //          l_tBsmMsgBuffer->messageType);
    // SendFrameMessageData(l_tBsmMsgBuffer);
    pthread_mutex_unlock(&g_SendFuncMutex);
}
/******************************************************************
 * 函 数 名 称    : FV_SendVIRPackage
 * 功 能 描 述    : 二期消息集VIR消息组包（通州测试场协作时匝道汇入场景需要）
 * 输 入 参 数    : 无
 * 输 出 参 数    : 无
 * 返  回  值     : IS_OK/IS_ERR              成功/失败*
 * 开 发 人 员    : bo_jiang 
 *        日期           版本      修改人     描述
 * ================== ======== ========== ===========================
 * 2021-12-03 16:15:37 V1.0     bo_jiang   Create
*=====================================================================*/
static void FV_SendVIRPackage(SendFrameTpye sendframetype)
{
    MSG_MessageType_st *l_tBsmMsgBuffer = NULL;

    pthread_mutex_lock(&g_SendFuncMutex);
    // LogPrint(LOG_LEVEL_DEBUG, STACK_MSG_MODULE, "FV_SendVIRPackage sendframetype %d", sendframetype);
    if (VIR == sendframetype)
    {
        //调用发送接口发送
        // LogPrint(LOG_LEVEL_DEBUG, STACK_MSG_MODULE, "ProtocolStackParamConfig.messageParamConfig.m_SendParam[13].m_nSendSwitch %d", ProtocolStackParamConfig.messageParamConfig.m_SendParam[13].m_nSendSwitch);
        if (ProtocolStackParamConfig.messageParamConfig.m_SendParam[13].m_nSendSwitch == 1)
        {
            //FV_CallocBsmGlobalBuffer();
            if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == 4)
            {
                pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
                g_pMsgSendBuffer->m_msgbufer.messageType = MSG_MessageType_ID_Four;
                FV_CreateBsmMinmumPackage(&(g_pMsgSendBuffer->m_msgbufer.msgtype.MessageFour), g_tDbusVehDataFrame.m_MsgData);
                pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
            }
            else if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == 5)
            {
                pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
                g_pMsgSendBuffer->m_msgbufer.messageType = MSG_MessageType_ID_NEW_Four;
                FV_CreateBsmMinmumPackage(&(g_pMsgSendBuffer->m_msgbufer.msgtype.MessageNewFour), g_tDbusVehDataFrame.m_MsgData);
                pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
            }
            else if (ProtocolStackParamConfig.msgFrameConfig.MsgFrameVersion == 2)
            {
                pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
                g_pMsgSendBuffer->m_msgbufer.messageType = MSG_MessageType_ID_Two;
                FV_CreateVIRMinmumPackage(&(g_pMsgSendBuffer->m_msgbufer.msgtype.MessageTwo), g_tDbusVehDataFrame.m_MsgData);
                pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
            }
            else
            {
                /* code */
            }

            l_tBsmMsgBuffer = calloc(1, sizeof(MSG_MessageType_st));
            // actual sending action
            pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
            memcpy(l_tBsmMsgBuffer, &(g_pMsgSendBuffer->m_msgbufer), sizeof(MSG_MessageType_st));
            pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
            LogPrint(LOG_LEVEL_DEBUG, STACK_MSG_MODULE, "Send msgType %d  %d", g_pMsgSendBuffer->m_msgbufer.messageType,
                     l_tBsmMsgBuffer->messageType);
            SendFrameMessageData(l_tBsmMsgBuffer);
        }
    }
    else if (V2FRAME == sendframetype)
    { /* code */
    }
    else
    {
        return;
    }
    pthread_mutex_unlock(&g_SendFuncMutex);
}

static void FV_V2xSendSrvFaultPush(void)
{
    for (int l_n32Cnt = 0; l_n32Cnt < 5; ++l_n32Cnt)
    {
        FV_emit_v2x_srv_fault_push();
        OSA_millisecondsleep(100);
    }
}

/*  开辟BSM发送的全局buffer */
void FV_CallocBsmGlobalBuffer(void)
{
    if (NULL == g_pMsgSendBuffer)
    {
        pthread_mutex_init(&g_SendFuncMutex, NULL);
        //g_pMsgSendBuffer = calloc(1, sizeof(MSG_MessageType_st));
        g_pMsgSendBuffer = calloc(1, sizeof(SendBuffer));
        bzero(&(g_pMsgSendBuffer->m_msgbufer), sizeof(MSG_MessageType_st));
        pthread_mutex_init(&(g_pMsgSendBuffer->m_muxtex), NULL);
    }
}

/* 释放BSM发送的全局buffer */
void FV_FreeBsmGlobalBuffer(void)
{
    if (g_pMsgSendBuffer)
    {
        free(g_pMsgSendBuffer);
        g_pMsgSendBuffer = NULL;
    }
}

static void *FV_CheckAg15FaultRoutine(void *p_Arg)
{
    bool *l_pbTrouble = (bool *)p_Arg;
    if (0 != utils_system("/bin/ping -w 5 " V2X_AG15_IF_IP " >/dev/null 2>&1"))
    {
        g_tDbusSrvFaultPush.m_IsAg15ComFault = IS_TROUBLE;
        *l_pbTrouble = true;
        FV_V2xSendSrvFaultPush();
    }
    pthread_exit(NULL);
    pthread_detach(pthread_self());
}

/***********************************************************************
 * 函 数 名 称 ：FV_V2xStackSendingCallback
 * 功 能 描 述 ：BSMTx发送BSM组包接口回调函数
 * 输 入 参 数 ：无
 * 输 入 参 数 ：无
 * 输 出 参 数 ：returnInfo: 协议栈发送状态返回值
 * 返  回  值  :  无
 * 开 发 人 员 ：姚志强
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
void FV_V2xStackSendingCallback(SendCallbackReturnInfo returnInfo)
{
    static int l_n32Cnt = 0;
    static bool l_bTrouble = false;
    static TSrvFaultPush_t l_tDbusSrvFaultPush = INIT_SRV_FAULT_PUSH();

    SendDataReturnInfo ag15SendDataReturnInfo;
    //调用协议栈回调函数进行发送
    if (returnInfo.error_type == 0)
    {
        V2X_SendData(returnInfo.sendDataInfo, &ag15SendDataReturnInfo);
        LogPrint(LOG_LEVEL_DEBUG, "Stack ", "V2X_SendData ok \n");
    }

    g_f32V2xCbr = ag15SendDataReturnInfo.Current_CBR / 100.0;

    memset(&g_tDbusSrvFaultPush, 0xFF, sizeof(g_tDbusSrvFaultPush));
    if (ERR_SECURE_LAYER_ENCODE == returnInfo.error_type)
    {
        g_tDbusSrvFaultPush.m_IsHsmComFault = IS_TROUBLE;
        l_bTrouble = true;
        if (memcmp(&g_tDbusSrvFaultPush, &l_tDbusSrvFaultPush, sizeof(g_tDbusSrvFaultPush)))
        {
            FV_V2xSendSrvFaultPush();
            l_tDbusSrvFaultPush = g_tDbusSrvFaultPush;
        }
    }
    else if (ERR_V2X_SEND == returnInfo.error_type)
    {
        if (memcmp(&g_tDbusSrvFaultPush, &l_tDbusSrvFaultPush, sizeof(g_tDbusSrvFaultPush)))
        {
            pthread_t l_tid;
            pthread_create(&l_tid, NULL, FV_CheckAg15FaultRoutine, &l_bTrouble);
            OSA_millisecondsleep(5U);
            l_tDbusSrvFaultPush = g_tDbusSrvFaultPush;
        }
    }
    else if (ERR_SUCCESS == returnInfo.error_type)
    {
        if (l_bTrouble)
        {
            g_tDbusSrvFaultPush.m_IsHsmComFault = IS_RECOVERY;
            g_tDbusSrvFaultPush.m_IsAg15ComFault = IS_RECOVERY;
            FV_V2xSendSrvFaultPush();
            l_bTrouble = false;
        }
    }
    else
    {
        INF("V2xStackSend callback error_type:%d\n", returnInfo.error_type);
        l_bTrouble = false;
        g_tDbusSrvFaultPush.m_IsHsmComFault = IS_DEFAULT;
        g_tDbusSrvFaultPush.m_IsAg15ComFault = IS_DEFAULT;
    }
}

static void FV_UpdateBsmComponentsBySecurityCertChange(void)
{
    static bool l_bMutexInited = false;
    if (!l_bMutexInited)
    {
        THR_mutex_init(&g_tBsmMsgUpdateMutex);
        l_bMutexInited = true;
    }

    THR_mutex_lock(&g_tBsmMsgUpdateMutex);
    if (FV_IsSecurityCertUpdate())
    {
        //清空当前buffer的所有数据
        bzero(&(g_pMsgSendBuffer->m_msgbufer), sizeof(g_pMsgSendBuffer->m_msgbufer));
        //随机产生一个MsgCnt
        srand((unsigned)time(NULL));
        g_u8MsgCnt = rand() % 127;
        //随即产生BSM八位的ID
        srand((unsigned)time(NULL));
        uint64_t l_u64BsmID = rand() % UINT64_MAX;
        memcpy(g_aBsmDynamicId, &l_u64BsmID, 8U);
        g_bIsSecurityRandomId = true;
        //清空历史轨迹和历史计数
        bzero(a_PHConciseDataBuffer, sizeof(a_PHConciseDataBuffer));
        nHistoryCount = 0;
        //立即发送当前更新历史轨迹后的BSM包
        FV_SendBsmPackage(BSM);
        FV_ResetSecurityCertUpdateFlag();
    }
    THR_mutex_unlock(&g_tBsmMsgUpdateMutex);
}

/***********************************************************************
 * 函 数 名 称 ：FV_CreateBsmMinmumPackage
 * 功 能 描 述 ：BSM组包函数
 * 输 入 参 数 ：p_ptVehData: VDS车身数据结构体
 * 输 入 参 数 ：无
 * 输 出 参 数 ：p_ptBsm: BSM组包后的指针
 * 返  回  值  :  E_OK/E_NOT_OK
 * 开 发 人 员 ：姚志强
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
/****
 * 新版veh数据结构下的BSM组包函数
 * ***/
Std_ReturnType FV_CreateBsmMinmumPackage(WJVN4_STRU_MessageFrame *pmsg_frame, TVehData_t p_ptVehData)
{
    if (!pmsg_frame)
    {
        ERR("Invliad Param\n");
        return E_NOT_OK;
    }

    bzero(pmsg_frame, sizeof(WJVN4_STRU_MessageFrame));

    pmsg_frame->uniUperMsg.strubsmFrame.n32msgCnt = g_u8MsgCnt;
    if (1 == g_tV2XOnlineCfg.m_BSMTx.m_RandId)
    {
        srand((unsigned)time(NULL));
        g_u8MsgCnt = rand() % 127;
    }
    else
    {
        g_u8MsgCnt >= 127 ? (g_u8MsgCnt = 0) : g_u8MsgCnt++;
    }

    if (g_bIsSecurityRandomId)
    {
        /* Update the MsgId by the security certificate update each 5 minutes. */
        memcpy(pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid, g_aBsmDynamicId, 8U);
    }
    else
    {
        static char l_n8Buffer[8] = {0};
        /* When the ID totall zero, memcpy the global ID. */
        if (!memcmp(&p_ptVehData.m_vehId[9], l_n8Buffer, 8U))
        {
            memcpy(pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid, g_aBsmDynamicId, 8U);
        }
        else
        {
            /* Default use the vds ID member. */
            memcpy(pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid, &p_ptVehData.m_vehId[9], 8U);
            memcpy(g_aBsmDynamicId, &p_ptVehData.m_vehId[9], 8U);
        }
    }

    //===== secMark Dsecond
#if EN_TEST_LOG
    /* 新四跨采用海拔记录MSG计数*/
    static outertyp_t l_BsmMsgCnt = 4098;
    p_ptBsm->msg.bsm.bsm_pos.pos_ele = bsctyp_decode(DE_Elevation, l_BsmMsgCnt);
    l_BsmMsgCnt++ > 64098 ? (l_BsmMsgCnt = 4098) : (l_BsmMsgCnt = l_BsmMsgCnt);
    /* 新四跨采用当前系统时间的ms数 */
    p_ptBsm->msg.bsm.bsm_secMark = utils_timer_ms() % 60000U;
#else
    pmsg_frame->uniUperMsg.strubsmFrame.n32secMark = p_ptVehData.m_gpsdata_st.m_u64_timestamp % 60000U;
#endif

    //====  timeConfidence TimeConfidence OPTIONAL,
    pmsg_frame->uniUperMsg.strubsmFrame.u8timeConfidencePresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.enumtimeConfidence = WJVN4_TimeConfidenceunavailable;

    //===== postion3D
    double l_latitude, l_longitude;
    if (1 == g_tV2XOnlineCfg.m_BSMTx.m_Wgs2Gci)
    {
        gps_transform((p_ptVehData.m_gpsdata_st.m_int_latitude / 1E7) * 1.0000000, (p_ptVehData.m_gpsdata_st.m_int_longitude / 1E7) * 1.0000000, &l_latitude, &l_longitude);
        pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32lat = l_latitude * 1.0000000;
        pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32long = l_longitude * 1.0000000;
    }
    else
    {
        pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32lat = p_ptVehData.m_gpsdata_st.m_int_latitude;
        pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32long = p_ptVehData.m_gpsdata_st.m_int_longitude;
    }
    pmsg_frame->uniUperMsg.strubsmFrame.strupos.u8elevationPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32elevation = p_ptVehData.m_gpsdata_st.m_int_altitude * 0.1; //系数与VDS传过来的数据有关系

    //BSM LOG
    LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Lat is %d", pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32lat);
    LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Long is %d", pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32long);
    LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Ele is %d", pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32elevation);

    // === postionalAccuracy
    pmsg_frame->uniUperMsg.strubsmFrame.u8posAccuracyPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32semiMajor = 10; // p_ptVehData.m_semiMajorAxisAccuracy * 0.05;
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32semiMajor = 12.7;
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32orientation = 359.9945078786; //0 ~ 359.9945078786

    //=== posConfidence PositionConfidenceSet OPTIONAL
    pmsg_frame->uniUperMsg.strubsmFrame.u8posConfidencePresent = WJV2_ABSENT;

    //===transmission  Speed   Heading
    pmsg_frame->uniUperMsg.strubsmFrame.enumtransmission = p_ptVehData.m_candata_st.m_DE_TransmissionState.m_u8_TransmissionStateData & 0xFF;
    pmsg_frame->uniUperMsg.strubsmFrame.n32speed = p_ptVehData.m_gpsdata_st.m_dbl_speed * 50;     // Uints 0.02m/s
    pmsg_frame->uniUperMsg.strubsmFrame.n32heading = p_ptVehData.m_gpsdata_st.m_dbl_heading * 80; //Uints  0.0125 degrees

    LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Speed is %d", pmsg_frame->uniUperMsg.strubsmFrame.n32speed);
    LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Heading is %d", pmsg_frame->uniUperMsg.strubsmFrame.n32heading);

    // === angle SteeringWheelAngle OPTIONAL
    pmsg_frame->uniUperMsg.strubsmFrame.u8anglePresent = WJV2_ABSENT;

    // ===  motionCfd MotionConfidenceSet OPTIONAL
    pmsg_frame->uniUperMsg.strubsmFrame.u8MotionConfidenceSetPresent = WJV2_ABSENT;

    // ==== AccelerationSet4Way
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32lat = p_ptVehData.m_int_acclng * 100;   // uints 0..01m/s^2
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32long = p_ptVehData.m_int_acclng * 100;  // uints 0..01m/s^2
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32vert = p_ptVehData.m_int_accvert * 100; // uints 0..01m/s^2
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32yaw = p_ptVehData.m_int_accvert * 100;  // uints 0..01m/s^2

    // ==== BrakeSystemStatus
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8brakePadelPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.enumbrakePadel = p_ptVehData.m_candata_st.m_DF_BrakeSystemStatus.m_u8_BrakeSystemStatusData;

    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8wheelBrakesPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8tractionPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8absPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8scsPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8brakeBoostPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8auxBrakesPresent = WJV2_ABSENT;

    // ==== VehicleSize
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.u8heightPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32height = p_ptVehData.m_vehicleHeight / 5; //分辨率5cm // uinits 10mm
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32length = p_ptVehData.m_vehicleLength;     //分辨率1cm uinits 10mm
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32width = p_ptVehData.m_vehicleWidth;       //分辨率1cm uinits 10mm

    // ==== VehicleClassification
    pmsg_frame->uniUperMsg.strubsmFrame.struvehicleClass.n32classification = p_ptVehData.m_basicVehicleClass;
    pmsg_frame->uniUperMsg.strubsmFrame.struvehicleClass.u8fuelTypePresent = WJV2_ABSENT;

    // ************ special veh
    uint16_t l_u16Mask = 1 << 9;
    bool l_bIsEmergency = false;
    bool l_bIs_EmergencyVeh = false;

    if ((p_ptVehData.m_basicVehicleClass <= WJVN4_BasicVehicleClassemergencyOtherAmbulance) &&
        (p_ptVehData.m_basicVehicleClass >= WJVN4_BasicVehicleClassemergencyFireLightVehicle))
    {
        l_bIs_EmergencyVeh = true;
    }

    //紧急车辆普通型
    if ((l_bIs_EmergencyVeh) && !p_ptVehData.m_warningevent.Byte)
    {
        DBG("紧急车辆普通型\n");
        pmsg_frame->uniUperMsg.strubsmFrame.u8emergencyExtPresent = WJV2_PRESENT; // MSG_OPTIONAL_YES;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8responseTypePresent = WJV2_PRESENT;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8sirenUsePresent = WJV2_ABSENT;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8lightsUsePresent = WJV2_ABSENT;

        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumresponseType = WJVN4_ResponseTypeemergency;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumsirenUse = WJVN4_SirenInUseinUse;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumlightsUse = WJVN4_LightbarInUseinUse;
        pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_SpecialConven_en;
    }
    //紧急车辆事件型
    if ((l_bIs_EmergencyVeh) || IS_EMERGGECY(p_ptVehData))
    {
        DBG("紧急车辆事件型\n");
        //if (p_ptVehData.m_warningevent.Event.m_event_HazardLights)
        if (p_ptVehData.m_candata_st.m_EmergeWarningLightSt.m_u8_RecVehLampMessage)
        {
            pmsg_frame->uniUperMsg.strubsmFrame.u8emergencyExtPresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8responseTypePresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8sirenUsePresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8lightsUsePresent = WJV2_PRESENT;

            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumresponseType = WJVN4_ResponseTypeemergency;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumsirenUse = WJVN4_SirenInUseinUse;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumlightsUse = WJVN4_LightbarInUseinUse;
        }
        pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_SpecialEvent_en;
        l_bIsEmergency = true;
    }
    //普通车辆事件型
    if (!(l_bIs_EmergencyVeh) && IS_EMERGGECY(p_ptVehData))
    {
        DBG("普通车辆事件型\n");
        if (p_ptVehData.m_warningevent.Event.m_event_HazardLights)
        {
            pmsg_frame->uniUperMsg.strubsmFrame.u8emergencyExtPresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8responseTypePresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8lightsUsePresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumresponseType = WJVN4_ResponseTypeemergency;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumlightsUse = WJVN4_LightbarInUseinUse;
        }
        pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_OrdinaryEvent_en;
        l_bIsEmergency = true;
    }
    //普通车辆普通型
    if (!(l_bIs_EmergencyVeh) && !p_ptVehData.m_warningevent.Byte)
    {
        DBG("普通车辆普通型\n");
        pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_OrdinaryConven_en;
    }

    // === VehicleSafetyExtensions
    pmsg_frame->uniUperMsg.strubsmFrame.u8safetyExtPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.u8lightsPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitlights = FV_ConvertDExteriorLightsStruct(p_ptVehData.m_candata_st);

    if (l_bIsEmergency)
    {
        pmsg_frame->uniUperMsg.strubsmFrame.u8safetyExtPresent = WJV2_PRESENT; // MSG_OPTIONAL_YES;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.u8eventsPresent = WJV2_PRESENT;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventHazardLights = p_ptVehData.m_warningevent.Event.m_event_HazardLights;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventABSactivated = p_ptVehData.m_warningevent.Event.m_event_ABS;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventTractionControlLoss = p_ptVehData.m_warningevent.Event.m_event_Traction;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventStabilityControlactivated = p_ptVehData.m_warningevent.Event.m_event_Stability;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventHardBraking = p_ptVehData.m_warningevent.Event.m_event_HardBraking;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventFlatTire = p_ptVehData.m_warningevent.Event.m_event_FlatTire;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventDisabledVehicle = p_ptVehData.m_warningevent.Event.m_event_DisabledVehicle;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventAirBagDeployment = p_ptVehData.m_warningevent.Event.m_event_AirBagDeployment;
    }
    return E_OK;
}
Std_ReturnType FV_CreateV2BsmMinmumPackage(WJV2_STRU_MessageFrame *pmsg_frame, TVehData_t p_ptVehData)
{
    if (!pmsg_frame)
    {
        ERR("Invliad Param\n");
        return E_NOT_OK;
    }

    bzero(pmsg_frame, sizeof(WJV2_STRU_MessageFrame));
    pmsg_frame->enumMessageFrameType = MSGV2_MessageFrame_ID_BSM_en;
    pmsg_frame->uniUperMsg.strubsmFrame.n32msgCnt = g_u8MsgCnt;
    if (1 == g_tV2XOnlineCfg.m_BSMTx.m_RandId)
    {
        srand((unsigned)time(NULL));
        g_u8MsgCnt = rand() % 127;
    }
    else
    {
        g_u8MsgCnt >= 127 ? (g_u8MsgCnt = 0) : g_u8MsgCnt++;
    }

    if (g_bIsSecurityRandomId)
    {
        /* Update the MsgId by the security certificate update each 5 minutes. */
        memcpy(pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid, g_aBsmDynamicId, 8U);
    }
    else
    {
        static char l_n8Buffer[8] = {0};
        /* When the ID totall zero, memcpy the global ID. */
        if (!memcmp(&p_ptVehData.m_vehId[9], l_n8Buffer, 8U))
        {
            memcpy(pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid, g_aBsmDynamicId, 8U);
        }
        else
        {
            /* Default use the vds ID member. */
            memcpy(pmsg_frame->uniUperMsg.strubsmFrame.u8OCTid, &p_ptVehData.m_vehId[9], 8U);
            memcpy(g_aBsmDynamicId, &p_ptVehData.m_vehId[9], 8U);
        }
    }

    //===== secMark Dsecond
#if EN_TEST_LOG
    /* 新四跨采用海拔记录MSG计数*/
    static outertyp_t l_BsmMsgCnt = 4098;
    p_ptBsm->msg.bsm.bsm_pos.pos_ele = bsctyp_decode(DE_Elevation, l_BsmMsgCnt);
    l_BsmMsgCnt++ > 64098 ? (l_BsmMsgCnt = 4098) : (l_BsmMsgCnt = l_BsmMsgCnt);
    /* 新四跨采用当前系统时间的ms数 */
    p_ptBsm->msg.bsm.bsm_secMark = utils_timer_ms() % 60000U;
#else
    pmsg_frame->uniUperMsg.strubsmFrame.n32secMark = p_ptVehData.m_gpsdata_st.m_u64_timestamp % 60000U;
#endif

    //====  timeConfidence TimeConfidence OPTIONAL,
    pmsg_frame->uniUperMsg.strubsmFrame.u8timeConfidencePresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.enumtimeConfidence = WJVN4_TimeConfidenceunavailable;

    //===== postion3D
    double l_latitude, l_longitude;
    if (1 == g_tV2XOnlineCfg.m_BSMTx.m_Wgs2Gci)
    {
        gps_transform((p_ptVehData.m_gpsdata_st.m_int_latitude / 1E7) * 1.0000000, (p_ptVehData.m_gpsdata_st.m_int_longitude / 1E7) * 1.0000000, &l_latitude, &l_longitude);
        pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32lat = l_latitude * 1.0000000;
        pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32long = l_longitude * 1.0000000;
    }
    else
    {
        pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32lat = p_ptVehData.m_gpsdata_st.m_int_latitude;
        pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32long = p_ptVehData.m_gpsdata_st.m_int_longitude;
    }
    pmsg_frame->uniUperMsg.strubsmFrame.strupos.u8elevationPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32elevation = p_ptVehData.m_gpsdata_st.m_int_altitude * 0.1; //系数与VDS传过来的数据有关系

    //BSM LOG
    // LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Lat is %d", pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32lat);
    // LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Long is %d", pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32long);
    // LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Ele is %d", pmsg_frame->uniUperMsg.strubsmFrame.strupos.n32elevation);

    // === postionalAccuracy
    pmsg_frame->uniUperMsg.strubsmFrame.u8posAccuracyPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32semiMajor = 10; // p_ptVehData.m_semiMajorAxisAccuracy * 0.05;
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32semiMajor = 12.7;
    pmsg_frame->uniUperMsg.strubsmFrame.struposAccuracy.n32orientation = 359.9945078786; //0 ~ 359.9945078786

    //=== posConfidence PositionConfidenceSet OPTIONAL
    pmsg_frame->uniUperMsg.strubsmFrame.u8posConfidencePresent = WJV2_ABSENT;

    //===transmission  Speed   Heading
    pmsg_frame->uniUperMsg.strubsmFrame.enumtransmission = p_ptVehData.m_candata_st.m_DE_TransmissionState.m_u8_TransmissionStateData & 0xFF;
    pmsg_frame->uniUperMsg.strubsmFrame.n32speed = p_ptVehData.m_gpsdata_st.m_dbl_speed * 50;     // Uints 0.02m/s
    pmsg_frame->uniUperMsg.strubsmFrame.n32heading = p_ptVehData.m_gpsdata_st.m_dbl_heading * 80; //Uints  0.0125 degrees

    // LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Speed is %d", pmsg_frame->uniUperMsg.strubsmFrame.n32speed);
    // LogPrint(LOG_LEVEL_EMERG, "BSM_TX", "Vehicle_Heading is %d", pmsg_frame->uniUperMsg.strubsmFrame.n32heading);

    // === angle SteeringWheelAngle OPTIONAL
    pmsg_frame->uniUperMsg.strubsmFrame.u8anglePresent = WJV2_ABSENT;

    // ===  motionCfd MotionConfidenceSet OPTIONAL
    pmsg_frame->uniUperMsg.strubsmFrame.u8MotionConfidenceSetPresent = WJV2_ABSENT;

    // ==== AccelerationSet4Way
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32lat = p_ptVehData.m_int_acclng * 100;   // uints 0..01m/s^2
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32long = p_ptVehData.m_int_acclng * 100;  // uints 0..01m/s^2
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32vert = p_ptVehData.m_int_accvert * 100; // uints 0..01m/s^2
    pmsg_frame->uniUperMsg.strubsmFrame.struaccelSet.n32yaw = p_ptVehData.m_int_accvert * 100;  // uints 0..01m/s^2

    // ==== BrakeSystemStatus
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8brakePadelPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.enumbrakePadel = p_ptVehData.m_candata_st.m_DF_BrakeSystemStatus.m_u8_BrakeSystemStatusData;

    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8wheelBrakesPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8tractionPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8absPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8scsPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8brakeBoostPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strubrakes.u8auxBrakesPresent = WJV2_ABSENT;

    // ==== VehicleSize
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.u8heightPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32height = p_ptVehData.m_vehicleHeight / 5; //分辨率5cm // uinits 10mm
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32length = p_ptVehData.m_vehicleLength;     //分辨率1cm uinits 10mm
    pmsg_frame->uniUperMsg.strubsmFrame.strusize.n32width = p_ptVehData.m_vehicleWidth;       //分辨率1cm uinits 10mm

    // ==== VehicleClassification
    pmsg_frame->uniUperMsg.strubsmFrame.struvehicleClass.n32classification = p_ptVehData.m_basicVehicleClass;
    pmsg_frame->uniUperMsg.strubsmFrame.struvehicleClass.u8fuelTypePresent = WJV2_ABSENT;

    // ************ special veh
    uint16_t l_u16Mask = 1 << 9;
    bool l_bIsEmergency = false;
    bool l_bIs_EmergencyVeh = false;

    if ((p_ptVehData.m_basicVehicleClass <= WJVN4_BasicVehicleClassemergencyOtherAmbulance) &&
        (p_ptVehData.m_basicVehicleClass >= WJVN4_BasicVehicleClassemergencyFireLightVehicle))
    {
        l_bIs_EmergencyVeh = true;
    }

    //紧急车辆普通型
    if ((l_bIs_EmergencyVeh) && !p_ptVehData.m_warningevent.Byte)
    {
        DBG("紧急车辆普通型\n");
        pmsg_frame->uniUperMsg.strubsmFrame.u8emergencyExtPresent = WJV2_PRESENT; // MSG_OPTIONAL_YES;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8responseTypePresent = WJV2_PRESENT;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8sirenUsePresent = WJV2_ABSENT;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8lightsUsePresent = WJV2_ABSENT;

        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumresponseType = WJVN4_ResponseTypeemergency;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumsirenUse = WJVN4_SirenInUseinUse;
        pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumlightsUse = WJVN4_LightbarInUseinUse;
        pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_SpecialConven_en;
    }
    //紧急车辆事件型
    if ((l_bIs_EmergencyVeh) || IS_EMERGGECY(p_ptVehData))
    {
        DBG("紧急车辆事件型\n");
        //if (p_ptVehData.m_warningevent.Event.m_event_HazardLights)
        if (p_ptVehData.m_candata_st.m_EmergeWarningLightSt.m_u8_RecVehLampMessage)
        {
            pmsg_frame->uniUperMsg.strubsmFrame.u8emergencyExtPresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8responseTypePresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8sirenUsePresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8lightsUsePresent = WJV2_PRESENT;

            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumresponseType = WJVN4_ResponseTypeemergency;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumsirenUse = WJVN4_SirenInUseinUse;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumlightsUse = WJVN4_LightbarInUseinUse;
        }
        pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_SpecialEvent_en;
        l_bIsEmergency = true;
    }
    //普通车辆事件型
    if (!(l_bIs_EmergencyVeh) && IS_EMERGGECY(p_ptVehData))
    {
        DBG("普通车辆事件型\n");
        if (p_ptVehData.m_warningevent.Event.m_event_HazardLights)
        {
            pmsg_frame->uniUperMsg.strubsmFrame.u8emergencyExtPresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8responseTypePresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.u8lightsUsePresent = WJV2_PRESENT;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumresponseType = WJVN4_ResponseTypeemergency;
            pmsg_frame->uniUperMsg.strubsmFrame.struemergencyExt.enumlightsUse = WJVN4_LightbarInUseinUse;
        }
        pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_OrdinaryEvent_en;
        l_bIsEmergency = true;
    }
    //普通车辆普通型
    if (!(l_bIs_EmergencyVeh) && !p_ptVehData.m_warningevent.Byte)
    {
        DBG("普通车辆普通型\n");
        pmsg_frame->enumMessageFrameType = MSGVN4_MessageFrame_ID_BSM_OrdinaryConven_en;
    }

    // === VehicleSafetyExtensions
    pmsg_frame->uniUperMsg.strubsmFrame.u8safetyExtPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.u8lightsPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitlights = FV_ConvertDExteriorV2LightsStruct(p_ptVehData.m_candata_st);

    if (l_bIsEmergency)
    {
        pmsg_frame->uniUperMsg.strubsmFrame.u8safetyExtPresent = WJV2_PRESENT; // MSG_OPTIONAL_YES;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.u8eventsPresent = WJV2_PRESENT;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventHazardLights = p_ptVehData.m_warningevent.Event.m_event_HazardLights;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventABSactivated = p_ptVehData.m_warningevent.Event.m_event_ABS;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventTractionControlLoss = p_ptVehData.m_warningevent.Event.m_event_Traction;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventStabilityControlactivated = p_ptVehData.m_warningevent.Event.m_event_Stability;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventHardBraking = p_ptVehData.m_warningevent.Event.m_event_HardBraking;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventFlatTire = p_ptVehData.m_warningevent.Event.m_event_FlatTire;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventDisabledVehicle = p_ptVehData.m_warningevent.Event.m_event_DisabledVehicle;
        pmsg_frame->uniUperMsg.strubsmFrame.strusafetyExt.strbitevents.bit_eventAirBagDeployment = p_ptVehData.m_warningevent.Event.m_event_AirBagDeployment;
    }
    return E_OK;
}
/***********************************************************************
 * 函 数 名 称 FV_CreateVIRMinmumPackage
 * 功 能 描 述 ：BSM组包函数
 * 输 入 参 数 ：p_ptVehData: VDS车身数据结构体
 * 输 入 参 数 ：无
 * 输 出 参 数 ：p_ptBsm: BSM组包后的指针
 * 返  回  值  :  E_OK/E_NOT_OK
 * 开 发 人 员 ：
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2021-12-03 V1.0       Create
***********************************************************************/
Std_ReturnType FV_CreateVIRMinmumPackage(WJV2_STRU_MessageFrame *pmsg_frame, TVehData_t p_ptVehData)
{
    if (!pmsg_frame)
    {
        ERR("Invliad Param\n");
        return E_NOT_OK;
    }
    // if (p_ptVehData.m_driveIntent.m_u8CLCintent != 1)
    // {
    //     ERR("Invliad Param\n");
    //     return E_NOT_OK;
    // }
    bzero(pmsg_frame, sizeof(WJV2_STRU_MessageFrame));
    pmsg_frame->enumMessageFrameType = MSGV2_MessageFrame_PR_msgFrameExt;
    pmsg_frame->uniUperMsg.struFrameExt.enumpresent = WJV2_value_PR_VehIntentionAndRequest;
    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.n32msgCnt = g_u8MsgCnt;
    g_u8MsgCnt >= 127 ? (g_u8MsgCnt = 0) : g_u8MsgCnt++;
    if (1 == g_tV2XOnlineCfg.m_BSMTx.m_RandId)
    {
        srand((unsigned)time(NULL));
        g_u8MsgCnt = rand() % 127;
    }
    else
    {
        g_u8MsgCnt >= 127 ? (g_u8MsgCnt = 0) : g_u8MsgCnt++;
    }

    if (g_bIsSecurityRandomId)
    {
        /* Update the MsgId by the security certificate update each 5 minutes. */
        memcpy(pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.u8OCTid, g_aBsmDynamicId, 8U);
    }
    else
    {
        static char l_n8Buffer[8] = {0};
        /* When the ID totall zero, memcpy the global ID. */
        if (!memcmp(&p_ptVehData.m_vehId[9], l_n8Buffer, 8U))
        {
            memcpy(pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.u8OCTid, g_aBsmDynamicId, 8U);
        }
        else
        {
            /* Default use the vds ID member. */
            memcpy(pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.u8OCTid, &p_ptVehData.m_vehId[9], 8U);
            memcpy(g_aBsmDynamicId, &p_ptVehData.m_vehId[9], 8U);
        }
    }

    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.n32secMark = p_ptVehData.m_gpsdata_st.m_u64_timestamp % 60000U;

    //===== postion3D
    double l_latitude, l_longitude;
    if (1 == g_tV2XOnlineCfg.m_BSMTx.m_Wgs2Gci)
    {
        gps_transform((p_ptVehData.m_gpsdata_st.m_int_latitude / 1E7) * 1.0000000, (p_ptVehData.m_gpsdata_st.m_int_longitude / 1E7) * 1.0000000, &l_latitude, &l_longitude);
        pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.strurefPos.n32lat = l_latitude * 1.0000000;
        pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.strurefPos.n32long = l_longitude * 1.0000000;
    }
    else
    {
        pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.strurefPos.n32lat = p_ptVehData.m_gpsdata_st.m_int_latitude;
        pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.strurefPos.n32long = p_ptVehData.m_gpsdata_st.m_int_longitude;
    }
    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.strurefPos.u8elevationPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.strurefPos.n32elevation = p_ptVehData.m_gpsdata_st.m_int_altitude * 0.1; //系数与VDS传过来的数据有关系

    //=== struintAndReqt OPTIONAL
    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.struintAndReq.u8currentPosPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.struintAndReq.u8path_PlanningPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.struintAndReq.u8reqsPresent = WJV2_ABSENT;
    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.struintAndReq.u8currentBehaviorPresent = WJV2_PRESENT;
    pmsg_frame->uniUperMsg.struFrameExt.choice.struVehIntentionAndRequest.struintAndReq.bitcurrentBehavior = FV_ConverDriveBehaviorStatus(p_ptVehData.m_driveIntent.m_u8CLCintent);

    return E_OK;
}
/***********************************************************************
 * 函 数 名 称 ：FV_CheckSum
 * 功 能 描 述 ：异或校验
 * 输 入 参 数 ：p_pvData: buffer地址
 * 输 入 参 数 ：p_u32Len: buffer长度
 * 输 出 参 数 ：无
 * 返  回  值  :  校验值
 * 开 发 人 员 ：Yaozhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
uint8_t FV_CheckSum(void *p_pvData, size_t p_u32Len)
{
    uint8_t *l_pu8Data = (uint8_t *)p_pvData;
    uint8_t l_u8Bcc = 0;
    for (size_t l_u32Cnt = 0; l_u32Cnt < p_u32Len; l_u32Cnt++)
    {
        l_u8Bcc ^= *l_pu8Data++;
    }
    return l_u8Bcc;
}

/***********************************************************************
 * 函 数 名 称 ：FV_BsmProcessMsgTimerCb
 * 功 能 描 述 ：BSM发送时钟回调函数
 * 输 入 参 数 ：无
 * 输 入 参 数 ：无
 * 输 出 参 数 ：value: 创建时钟时候的参数
 * 返  回  值  :  无
 * 开 发 人 员 ：Yaozhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
#include <semaphore.h>
extern sem_t *m_sem;
void FV_BsmProcessMsgTimerCb(union sigval value)
{
    static utils_timer start;
    TModuleObjHdl l_ptObj = (TModuleObjHdl)value.sival_ptr;
    static bool l_bMutexInited = false;
    int CurrentTimerPeriod = 0;
    while (1)
    {
        if (!l_bMutexInited)
        {
            THR_mutex_init(&g_tBsmTimerCbMutex);
            l_bMutexInited = true;
        }
        CurrentTimerPeriod = BSMTimerPeriod * 1000;
        THR_mutex_lock(&g_tBsmTimerCbMutex);
        DBG("___bsmtx___ interval: %lld\n", utils_timer_ms() - start);
        start = utils_timer_ms();
        usleep(CurrentTimerPeriod);
        if (g_tDbusVehDataFrame.m_MsgData.m_driveIntent.m_u8CLCintent != 0)
            FV_SendVIRPackage(VIR);
        FV_SendBsmPackage(BSM);
        THR_mutex_unlock(&g_tBsmTimerCbMutex);
    }
}

void FV_ChangeBsmTimerCycleDynamic(TModuleObjHdl p_ptObj)
{
    uint32_t l_u32GlobalBsmTimerPeriod = DEF_BSM_CYCLE;
    static uint32_t l_u32TimerPeriod = DEF_BSM_CYCLE;
    OSA_TimerHndl *l_tTimerHndl = &p_ptObj->m_ObjTimerHndl.m_TimerHndl;

    //在BSM周期改变的时候动态调整Timer的周期
    l_u32GlobalBsmTimerPeriod = FV_GenerateBSMTxCycleTime(g_f32V2xCbr, (uint16_t)g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_dbl_speed);
    if (l_u32TimerPeriod != l_u32GlobalBsmTimerPeriod)
    {
        INF("l_u32GlobalBsmTimerPeriod changed from %d--->%d\n", l_u32TimerPeriod, l_u32GlobalBsmTimerPeriod);
        OSA_timerStop(l_tTimerHndl);
        //开启新的BSM发送周期
        l_tTimerHndl->period_s = 0;
        l_tTimerHndl->period_ms = l_u32GlobalBsmTimerPeriod;
        OSA_timerStart(l_tTimerHndl);
        l_u32TimerPeriod = l_u32GlobalBsmTimerPeriod;
    }
}

/***********************************************************************
 * 函 数 名 称 ：FV_BsmMessageProcessThread
 * 功 能 描 述 ：BSM线程函数
 * 输 入 参 数 ：p_pvArg: 线程参数
 * 输 入 参 数 ：p_n32CurState: 线程当前的状态
 * 输 出 参 数 ：无
 * 返  回  值  :  E_EXIT_OK
 * 开 发 人 员 ：Yaozhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
int FV_BsmMessageProcessThread(void *p_pvArg, int p_n32CurState)
{
    TModuleObjHdl l_ptObj = (TModuleObjHdl)p_pvArg;

    if (!l_ptObj->m_IsInited)
    {
        THR_cond_wait(&l_ptObj->m_Worker->cond, &l_ptObj->m_Worker->mutex);
        l_ptObj->m_IsInited = true;
        INF("%s Start\n", __func__);
    }

    while (l_ptObj->m_Worker->active)
    {
        THR_mutex_lock(&l_ptObj->m_Worker->mutex);
        //根据证书根性的状态，进行BSM的ID/CNT/pathhistory的更新
        FV_UpdateBsmComponentsBySecurityCertChange();
        //发送紧急BSM
        FV_TriggerEmergencyBsmMessage(g_tDbusVehDataFrame.m_MsgData);

        FV_InitativeSendMessage(&g_n32Triger);

        if (1 == g_tV2XOnlineCfg.m_BSMTx.m_CbrCtl)
        {
            FV_ChangeBsmTimerCycleDynamic(l_ptObj);
        }
        usleep(50000);
        // OSA_millisecondsleep(BSM_THR_CYCLE); /* Set the BSM thread module fixed time cycle. */
        THR_mutex_unlock(&l_ptObj->m_Worker->mutex);
    }

    if (!l_ptObj->m_Worker->active)
    {
        INF("%s quit\n", __func__);
        l_ptObj->m_IsInited = false;
        pthread_mutex_destroy(&g_tBsmTimerCbMutex);
        pthread_mutex_destroy(&g_tBsmMsgUpdateMutex);
        THR_thread_exit(NULL);
    }
    return E_EXIT_OK;
}
