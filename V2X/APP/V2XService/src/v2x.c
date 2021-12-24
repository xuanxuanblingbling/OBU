/*******************************************************************************
 * 文 件 名 称 ： v2x.c
 * 功 能 描 述 ： v2x协议栈交互模块
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-07-20 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#include "Common.h"
#define MODULE_NAME "BSMTx"
#include "Debug.h"
#include "RBTreeStd.h"
#include "socketCommon.h"

//用于外部引用全局变量
TV2xSrvMsg_t g_tDbusV2xSrvMsg = INIT_V2X_SRV_MSG();
TV2xSrvMsgN4_t g_tDbusV2xSrvMsgN4 = INIT_V2X_SRV_MSG();
RBRoot *pgroot = NULL;
extern SendBuffer *g_pMsgSendBuffer;
extern int g_n32Triger;
/***********************************************************************
 * 函 数 名 称 ：Hash 函数，计算地图
 * 功 能 描 述 ：BSMTx接收V2X协议栈数据
 * 输 入 参 数 ：p_pvArg: 地图
 * 输 入 参 数 ：
 * 输 出 参 数 ：无
 * 返  回  值  :  E_EXIT_OK
 * 开 发 人 员 ：CBS
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
***********************************************************************/

unsigned int Hash(WJVN4_STRU_MapData *pMap)
{
    char smap[512] = {0};
    char *psmap = smap;
    char tmpstr[64] = {0};
    int len = 0;
    unsigned int hash = 0;

    sprintf(tmpstr, "%03d", pMap->strunodes.u8NodeNum);
    strncpy(&smap[len], tmpstr, 3); // uint8 255
    len += 3;
    sprintf(tmpstr, "%05d", pMap->strunodes.struNode[0].struid.n32region);
    strncpy(&smap[len], tmpstr, 5); // uint16
    len += 5;
    sprintf(tmpstr, "%05d", pMap->strunodes.struNode[0].struid.n32id);
    strncpy(&smap[len], tmpstr, 5); // uint16
    len += 5;
    sprintf(tmpstr, "%09lld", (long long int)(pMap->strunodes.struNode[0].strurefPos.n32lat));
    strncpy(&smap[len], tmpstr, 9); // uint double
    len += 9;
    sprintf(tmpstr, "%010lld", (long long int)(pMap->strunodes.struNode[0].strurefPos.n32long));
    strncpy(&smap[len], tmpstr, 10); // uint bouble
    len += 10;
    sprintf(tmpstr, "%03d", pMap->strunodes.struNode[0].struinLinks.u8LinkNum);
    strncpy(&smap[len], tmpstr, 3); // uint8
    len += 3;
    printf("=====[test]  =======%d  %s     *******\n", len, smap);
    while (*psmap)
    {
        hash = (*psmap++) + (hash << 6) + (hash << 16) - hash;
    }

    return (hash & 0x7FFFFFFF);
}

//********************************IPC回调********************************
void RecIpcFun(uint8_t *data, uint64_t length)
{
    LogPrint(LOG_LEVEL_INFO, "V2X", "Start Recive IPC App_data!\n");

    uint32_t l_u32Len = 0;
    TV2xSrvMsg_t l_MessageRecv = {0};
    uint8_t l_n8BccSrc = 0;
    uint8_t l_n8BccDst = 0;

    l_u32Len = length;
    memcpy(&l_MessageRecv, data, l_u32Len);

    pthread_mutex_lock(&(g_pMsgSendBuffer->m_muxtex));
    memcpy(&(g_pMsgSendBuffer->m_msgbufer.messageType), &l_MessageRecv.m_V2xMessageFrame.messageType, l_u32Len - 11);
    pthread_mutex_unlock(&(g_pMsgSendBuffer->m_muxtex));
    g_n32Triger = YES;
}
//********************************IPC回调********************************

/***********************************************************************
 * 函 数 名 称 ：FV_V2xStackHandleMessageThread
 * 功 能 描 述 ：BSMTx接收V2X协议栈数据
 * 输 入 参 数 ：p_pvArg: 线程参数
 * 输 入 参 数 ：p_n32CurState: 线程状态
 * 输 出 参 数 ：无
 * 返  回  值  :  E_EXIT_OK
 * 开 发 人 员 ：姚志强
 * 日期       版本  修改人    描述
 * ========== ======= ========= ================================
 * 2020-07-22 V1.0   YaoZhiqiang    Create
***********************************************************************/
int FV_V2xStackHandleMessageThread(void *p_pvArg, int p_n32CurState)
{

    TModuleObjHdl l_ptObj = (TModuleObjHdl)p_pvArg;
    TMainProcObjHdl l_ptMainProcObj;
    int l_dbusSendLen = 0;

    if (!l_ptObj->m_IsInited)
    {
        THR_cond_wait(&l_ptObj->m_Worker->cond, &l_ptObj->m_Worker->mutex);
        l_ptObj->m_IsInited = true;
        INF("%s start.\n", __func__);
    }
    //bulit Tree
    pgroot = bulitTree();

    static unsigned int mapHasResult = 0;
    static struct timeval mapTime = {0};
    struct timeval Now = {0};
    int count = 0;
    int FrameID = 0;
    int l_n32Frametype = 0;

    recDataFunc("obu_app.socket", RecIpcFun, 0xFF);
    //------------------------------启动IPC-------------------------------------------
    if (true == startFunc("v2x_server.socket", IPC_BOTH_MODE))
    {

        LogPrint(LOG_LEVEL_INFO, "V2X", "Start IPC Success!!!\n");
    }
    //------------------------------启动IPC-------------------------------------------

    //此处耗时约30ms，导致应用层处理缓慢，在不加安全层验签情况下，消息层队列一直处于满负荷状态，会出现丢包，建议可适当修改
    while (l_ptObj->m_Worker->active)
    {
        THR_mutex_lock(&l_ptObj->m_Worker->mutex);
        //Recv Msg
        if (ProtocolStackParamConfig.messageParamConfig.recvParamConfig.RecvSwitch == 1)
        {
            MSG_MessageType_st *l_pData = MsgLayerMessageGetFromQueue();
            if (NULL != l_pData)
            {
                //RSC消息
                if (MSG_MessageType_ID_Two == l_pData->messageType)
                {
                    if (l_pData->msgtype.MessageTwo.enumMessageFrameType == MSGV2_MessageFrame_PR_msgFrameExt)
                    {
                        if (l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.enumpresent == WJV2_value_PR_RoadsideCoordination)
                        {

                            memset(&g_tRoadsideCoordination, 0x00, sizeof(g_tRoadsideCoordination));
                            //RSC：RSU向HV发送
                            LogPrint(LOG_LEVEL_INFO, "V2X", "WJV2_value_PR_RoadsideCoordination!!!\n");
                            //RSU_ID
                            memcpy(g_tRoadsideCoordination.bootDeviceId, l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.u8OCTid, WJV2_MAX_ID_SIZE);
                            //RSU纬度
                            g_tRoadsideCoordination.bootDeviceLat = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strurefPos.n32lat;
                            //RSU经度
                            g_tRoadsideCoordination.bootDeviceLng = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strurefPos.n32long;

                            //单车级协作 Coordinates（RSU可能会给多辆车广播引导信息）
                            if (l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.u8coordinatesPresent == WJV2_PRESENT)
                            {
                                //Coordinates数量
                                uint8_t Coordinates = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.u8coordinatesNum;
                                for (int i = 0; i < Coordinates; i++)
                                {
                                    //获取自车ID

                                    memcpy(g_tRoadsideCoordination.hv_id, &g_tDbusVehDataFrame.m_MsgData.m_vehId[9], 8U);
                                    LogPrint(LOG_LEVEL_INFO, "V2X", "g_tRoadsideCoordination.hv_id is %s", g_tRoadsideCoordination.hv_id);
                                    LogPrint(LOG_LEVEL_INFO, "V2X", "struRoadsideCoordination.u8OCTvehId is %s", l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].u8OCTvehId);
                                    int ret = strcmp(l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].u8OCTvehId, g_tRoadsideCoordination.hv_id);
                                    if (0 == ret)
                                    {
                                        // //自车位置信息
                                        // g_tRoadsideCoordination.hv_lat = (double)(g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_latitude / 1E7);
                                        // g_tRoadsideCoordination.hv_lon = (double)(g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_longitude / 1E7);
                                        // g_tRoadsideCoordination.hv_ele = (double)(g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_int_altitude);
                                        // //自车速度
                                        // g_tRoadsideCoordination.hv_speed = g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_dbl_speed;
                                        // //自车航向角
                                        // g_tRoadsideCoordination.hv_head = g_tDbusVehDataFrame.m_MsgData.m_gpsdata_st.m_dbl_heading;
                                        //引导信息状态 0：引导失败 1：引导成功 只要OBU接收到RSC消息并且引导信息中vehicle ID和OBU自身ID一致，则状态为成功
                                        g_tRoadsideCoordination.guideStart = GUIDESTART_SUCCESS;
                                        //协同场景的类型
                                        LogPrint(LOG_LEVEL_INFO, "V2X", "bitinfo0 is %d", l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].bitinfo.u8CoordinationInfo[0]);
                                        LogPrint(LOG_LEVEL_INFO, "V2X", "bitinfo1 is %d", l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].bitinfo.u8CoordinationInfo[1]);
                                        g_tRoadsideCoordination.collSceType = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].bitinfo.u8CoordinationInfo[0];

                                        //引导设备的类型引导设备类型(默认RSU)
                                        g_tRoadsideCoordination.bootDeviceType = BOOTDEVICETYEP_RSU;

                                        if (l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].u8driveSuggestionPresent == WJV2_PRESENT)
                                        {
                                            //驾驶建议
                                            LogPrint(LOG_LEVEL_INFO, "V2X", "driving_advice0 is %d", l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strudriveSuggestion.bitsuggestion.u8DriveBehavior[0]);
                                            LogPrint(LOG_LEVEL_INFO, "V2X", "driving_advice1 is %d", l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strudriveSuggestion.bitsuggestion.u8DriveBehavior[1]);
                                            g_tRoadsideCoordination.driving_advice = ((l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strudriveSuggestion.bitsuggestion.u8DriveBehavior[0]) + ((l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strudriveSuggestion.bitsuggestion.u8DriveBehavior[1] & 0xfc) << 16));
                                            LogPrint(LOG_LEVEL_INFO, "V2X", "driving_advice is %d", g_tRoadsideCoordination.driving_advice);
                                        }
                                        else
                                        {
                                        }
                                        if (l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].u8pathGuidancePresent == WJV2_PRESENT)
                                        {
                                            //规划路径点的数量
                                            /* 与协议不一致 协议为100 暂定为16 */
                                            g_tRoadsideCoordination.planpathpoints = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strupathGuidance.u8PathPlanningPointNum;
                                            LogPrint(LOG_LEVEL_INFO, "V2X", "g_tRoadsideCoordination.planpathpoints is %d", g_tRoadsideCoordination.planpathpoints);
                                            //预计到达时间，从当前时刻到达路径规划最后一个点的预估时间
                                            if (l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strupathGuidance.struPathPlanningPoint[g_tRoadsideCoordination.planpathpoints - 1].u8estimatedTimePresent == WJV2_PRESENT)
                                            {
                                                g_tRoadsideCoordination.arrival_time = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strupathGuidance.struPathPlanningPoint[g_tRoadsideCoordination.planpathpoints - 1].n32estimatedTime;
                                            }
                                            else
                                            {
                                                g_tRoadsideCoordination.arrival_time = 0; //无效
                                            }

                                            //规划路径中最后一个点的经纬度
                                            //路径目标点纬度
                                            g_tRoadsideCoordination.tarLat = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strupathGuidance.struPathPlanningPoint[g_tRoadsideCoordination.planpathpoints - 1].strupos.struoffsetLL.u.strupositionLatLon.n32lat;
                                            //路径目标点的经度
                                            g_tRoadsideCoordination.tarLon = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strupathGuidance.struPathPlanningPoint[g_tRoadsideCoordination.planpathpoints - 1].strupos.struoffsetLL.u.strupositionLatLon.n32lon;
                                            for (int j = 0; j < g_tRoadsideCoordination.planpathpoints; j++)
                                            {
                                                //规划路径的纬度
                                                g_tRoadsideCoordination.planpathpoint[j].planpathPointlat = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strupathGuidance.struPathPlanningPoint[j].strupos.struoffsetLL.u.strupositionLatLon.n32lat;
                                                //规划路径点的经度
                                                g_tRoadsideCoordination.planpathpoint[j].planpathPointlon = l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.strucoordinatesList.strucoordinates[i].strupathGuidance.struPathPlanningPoint[j].strupos.struoffsetLL.u.strupositionLatLon.n32lon;
                                            }
                                            //Send to Dbus --协作时匝道汇入
                                            FV_emit_v2x_net_cooperative();
                                            LogPrint(LOG_LEVEL_ERR, "V2X", "FV_emit_v2x_net_cooperative success");
                                        }
                                    }
                                }
                            }
                            else
                            {
                                LogPrint(LOG_LEVEL_ERR, "V2X", "u8coordinatesPresent  = %d\n", l_pData->msgtype.MessageTwo.uniUperMsg.struFrameExt.choice.struRoadsideCoordination.u8coordinatesPresent);
                            }
                        }
                    }
                }
                l_dbusSendLen = DealDataToDbus(l_pData, &l_n32Frametype);
                LogPrint(LOG_LEVEL_INFO, "V2X", "Revcive Message Len  = %d\n", l_dbusSendLen);
                if (l_dbusSendLen > 0)
                {
                    l_dbusSendLen += 4;
                    LogPrint(LOG_LEVEL_INFO, "V2X", "Revcive Message Type  = %d\n", l_pData->messageType);

                    //Send to Dbus
                    FV_emit_v2x_srv_msg(l_dbusSendLen + 11, l_pData->messageType, l_n32Frametype);
                }

                free(l_pData);
                l_pData = NULL;
            }

#if EN_TEST_LOG
            FL_SetRecvdSelfBsmMsg(g_aBsmDynamicId, &g_tDbusVehDataFrame.m_MsgData);
            OSA_millisecondsleep(2U);
            FL_WriteRecvdMsgLog(&g_tDbusV2xSrvMsg.m_V2xMessageFrame);
#endif
            //此处休眠是否可去掉？
        }
        else
        {
            //WM：建议写成这样
            OSA_millisecondsleep(10U);
        }

        THR_mutex_unlock(&l_ptObj->m_Worker->mutex);
    }

    //停止IPC
    stopFunc();
    INF("%s quit\n", __func__);
    l_ptObj->m_IsInited = false;
    THR_thread_exit(NULL);
    return E_EXIT_OK;
}

/*******************************************************************************
 * @function name： FV_InitV2xComponents
 * @bref   ： V2X stack init
 * @author ：CBS
 * @input  ： NO
 * @output  : NO
 * @return  ：const 0
********************************************************/
int MapHash(WJVN4_STRU_MapData *mapdata)
{
    static unsigned int mapHasResult = 0;
    static struct timeval mapTime = {0};
    struct timeval Now = {0};
    unsigned int NowHashresult = 0;

    NowHashresult = Hash(mapdata);
    if (mapHasResult != NowHashresult)
    {
        gettimeofday(&Now, NULL);
        if ((Now.tv_sec - mapTime.tv_sec) < 2)
        {
            LogPrint(LOG_LEVEL_INFO, "V2X", "Recived MAP message  time  Too short ");
            return 1;
        }
        else
        {
            gettimeofday(&mapTime, NULL);
            mapHasResult = NowHashresult;
            LogPrint(LOG_LEVEL_INFO, "V2X", "Recived MAP  New RIGHT");
            return 0;
        }
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, "V2X", "Recived MAP  SAME ");
        return 1;
    }
}

/*******************************************************************************
 * @function name： FV_InitV2xComponents
 * @bref   ： V2X stack init
 * @author ：CBS
 * @input  ： NO
 * @output  : NO
 * @return  ：const 0
********************************************************/
int DealDataToDbus(MSG_MessageType_st *pMesgData, int *pFrametype)
{
    int frametype = 0;
    int msgtype = 0;
    int l_n32len = 0;
    Node *objetNode = NULL;

    msgtype = pMesgData->messageType;

    if (msgtype == MSG_MessageType_ID_Four)
    {
        frametype = pMesgData->msgtype.MessageFour.enumMessageFrameType;
        memcpy(&g_tDbusV2xSrvMsg.m_V2xMessageFrame.messageType, &pMesgData->messageType, sizeof(WJV4_STRU_MessageFrame) + 4);
    }
    else if (msgtype == MSG_MessageType_ID_NEW_Four)
    {

        frametype = pMesgData->msgtype.MessageNewFour.enumMessageFrameType;
        //RSM存储log
        // if ((MSGVN4_MessageFrame_ID_RSM_en == frametype))
        // {
        //     //RSU位置信息
        //     LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM RSU_Lat:%d", pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.strurefPos.n32lat);
        //     LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM RSU_Long:%d", pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.strurefPos.n32long);
        //     if (pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.strurefPos.u8elevationPresent == WJVN4_PRESENT)
        //     {
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM RSU_Ele:%d", pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.strurefPos.n32elevation);
        //     }

        //     for (int i = 0; i < pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.u8ParticipantDataNum; i++)
        //     {
        //         //交通参与者类型
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Type is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].enumptcType);
        //         //交通参与者位置
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Lat is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].strupos.struoffsetLL.u.strupositionLatLon.n32lat);
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Long is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].strupos.struoffsetLL.u.strupositionLatLon.n32lon);
        //         if (pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].strupos.u8offsetVPresent == WJVN4_PRESENT)
        //         {
        //             LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Ele is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].strupos.struoffsetV.u.n32elevation);
        //         }
        //         //交通参与者速度
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Speed is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].n32speed);
        //         //交通参与者航向角
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Heading is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].n32heading);
        //     }

        //交通参与者速度
        // }
        memcpy(&g_tDbusV2xSrvMsg.m_V2xMessageFrame.messageType, &pMesgData->messageType, sizeof(WJVN4_STRU_MessageFrame) + 4);
    }
    else if (msgtype == MSG_MessageType_ID_Two)
    {
        frametype = pMesgData->msgtype.MessageTwo.enumMessageFrameType;
        memcpy(&g_tDbusV2xSrvMsg.m_V2xMessageFrame.messageType, &pMesgData->messageType, sizeof(WJV2_STRU_MessageFrame) + 4);
        if (frametype == MSGV2_MessageFrame_PR_msgFrameExt)
        {
            frametype = pMesgData->msgtype.MessageTwo.uniUperMsg.struFrameExt.enumpresent;
        }
        //RSM存储log
        // if ((MSGVN4_MessageFrame_ID_RSM_en == frametype))
        // {
        //     //RSU位置信息
        //     LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM RSU_Lat:%d", pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.strurefPos.n32lat);
        //     LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM RSU_Long:%d", pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.strurefPos.n32long);
        //     if (pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.strurefPos.u8elevationPresent == WJVN4_PRESENT)
        //     {
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM RSU_Ele:%d", pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.strurefPos.n32elevation);
        //     }

        //     for (int i = 0; i < pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.u8ParticipantDataNum; i++)
        //     {
        //         //交通参与者类型
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Type is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].enumptcType);
        //         //交通参与者位置
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Lat is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].strupos.struoffsetLL.u.strupositionLatLon.n32lat);
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Long is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].strupos.struoffsetLL.u.strupositionLatLon.n32lon);
        //         if (pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].strupos.u8offsetVPresent == WJVN4_PRESENT)
        //         {
        //             LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Ele is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].strupos.struoffsetV.u.n32elevation);
        //         }
        //         //交通参与者速度
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Speed is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].n32speed);
        //         //交通参与者航向角
        //         LogPrint(LOG_LEVEL_EMERG, "V2X_RSM", "Revcive_RSM Praticipant[%d]Heading is %d", i, pMesgData->msgtype.MessageNewFour.uniUperMsg.strursmFrame.struparticipants.struParticipantData[i].n32heading);
        //     }

        //     //交通参与者速度
        // }
    }
    else
    {
    }

    LogPrint(LOG_LEVEL_INFO, "V2X", "Revcive Message TYPE ： %d  FRAMETYPE-----： %d \n", msgtype, frametype);
    // some frametype is 1 2   but some is 101  501
    if (frametype >= 100)
    {
        frametype = frametype / 100;
    }
    *pFrametype = frametype;

    // get the frame lenght
    objetNode = search(pgroot->node, (msgtype * 100 + frametype));

    if (NULL != objetNode)
    {
        l_n32len = objetNode->val;
    }
    else
    {
        LogPrint(LOG_LEVEL_INFO, "V2X", "Rootnode ： %p  Key： %d \n", pgroot->node, msgtype * 100 + frametype);
        l_n32len = 0;
        return l_n32len;
    }

    // memcpy(&g_tDbusV2xSrvMsg.m_V2xMessageFrame.messageType, &pMesgData->messageType, (l_n32len + 4)); // 4bytes messageTpye
    // if frme is map check hash
    if (MSGVN4_MessageFrame_ID_MAPDATA_en == frametype)
    {
        for (int i = 0; i < pMesgData->msgtype.MessageNewFour.uniUperMsg.strumapFrame.strunodes.u8NodeNum; i++)
        {
            for (int j = 0; j < pMesgData->msgtype.MessageNewFour.uniUperMsg.strumapFrame.strunodes.struNode[i].struinLinks.u8LinkNum; j++)
            {
                for (int p = 0; p < pMesgData->msgtype.MessageNewFour.uniUperMsg.strumapFrame.strunodes.struNode[i].struinLinks.struLink[j].strulanes.u8LaneNum; p++)
                {
                    LogPrint(LOG_LEVEL_INFO, "V2X", "Map Lane ID is %d\n",
                             pMesgData->msgtype.MessageNewFour.uniUperMsg.strumapFrame.strunodes.struNode[i].struinLinks.struLink[j].strulanes.struLane[p].n32laneID);
                }
            }
        }
        if (MapHash(&pMesgData->msgtype.MessageNewFour.uniUperMsg.strumapFrame))
        {
            // l_n32len = -1;
        }
    }

    return l_n32len;
}