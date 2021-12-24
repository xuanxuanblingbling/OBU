#include "ConfigModuleRW.h"
#include "wjv2_uper_interface.h"
#include "./../MsgFrameV2/MessageFrame.h"
#include "wj_log.h"

/*二期消息集接口*/
WJV2_UperFromFileEncodeMain_BACK wjv2_UperFromFileEncodeMain = NULL;
WJV2_UperEncOrDecMain_BACK wjv2_UperEncOrDecMain = NULL;

int getAIDFromFileV2(void *pstruMsg);

void SetWJV2_MessageCallback(WJV2_UperFromFileEncodeMain_BACK p_wjv2_UperFromFileEncodeMain,
                             WJV2_UperEncOrDecMain_BACK p_wjv2_UperEncOrDecMain,
                             WJV2_SetGetAIDFromFileCallback p_wjv2_SetGetAIDFromFileCallback)
{
    wjv2_UperFromFileEncodeMain = p_wjv2_UperFromFileEncodeMain;
    wjv2_UperEncOrDecMain = p_wjv2_UperEncOrDecMain;
    if (NULL != p_wjv2_SetGetAIDFromFileCallback)
    {
        p_wjv2_SetGetAIDFromFileCallback(getAIDFromFileV2);
        printf("%s %s %d wjv2_SetGetAIDFromFileCallback Success!\n", __FILE__, __FUNCTION__, __LINE__);
    }
}

/**
 * @brief     getAIDFromFile检查消息号函数
 * @details   协议栈消息层编解码中 统一 消息的解码函数入口
 * @param   [in]   MessageFrame_t *msg_frame_ptr   WJ结构
 * @return      本函数返回执行结果，AID的值
 * @author      huangsai
* @par 修改日志:
* <table>
* <tr><th>Date        <th>Version  <th>Author    <th>Description
* <tr><td>2020/09/10  <td>1.0      <td>huangsai  <td>创建初始版本
* </table>
*/
int getAIDFromFileV2(void *pstruMsg)
{
    /* 入参为空检查 */
    if (NULL == pstruMsg)
    {
        LogPrint(LOG_LEVEL_ERR,
                 "MSGLAYERV2MSG",
                 "input is null:pstruMsgframe = %p", pstruMsg);
        return -1;
    }
    MessageFrame_t *pstruMsgFrame = (MessageFrame_t *)pstruMsg;
    int MessageAID = ProtocolStackParamConfig.DSMPParamConfig.StandardMessageAID;
    switch (pstruMsgFrame->present)
    {
    case MessageFrame_PR_mapFrame:
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.MAPMSGAID;
        break;
    case MessageFrame_PR_bsmFrame:
        if (pstruMsgFrame->choice.bsmFrame.safetyExt != NULL)
        {
            if (pstruMsgFrame->choice.bsmFrame.safetyExt->events != NULL)
            {
                //普通车辆+事件型
                MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryEvent;
            }
            else
            {
                //普通车辆+常规型
                MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven;
            }
        }
        else if (pstruMsgFrame->choice.bsmFrame.emergencyExt != NULL)
        {
            if (pstruMsgFrame->choice.bsmFrame.emergencyExt->responseType != NULL)
            {
                //特殊车辆+事件型
                MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialEvent;
            }
            else
            {
                //特殊车辆+常规型
                MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMSpecialConven;
            }
        }
        else
        {
            //普通车辆+常规型
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.BSMOrdinaryConven;
        }
        break;
    case MessageFrame_PR_rsiFrame:
        if (pstruMsgFrame->choice.rsiFrame.rtss != NULL)
        {
            //道路信息-静态类应用
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadStatic;
        }
        else if (pstruMsgFrame->choice.rsiFrame.rtes != NULL)
        {
            switch (pstruMsgFrame->choice.rsiFrame.rtes->list.array[0]->eventType)
            {
            case 401:
            case 405:
            case 406:
            case 901:
            case 902:
            case 903:
            case 904:
            case 905:
            case 906:
            {
                //当前只检查第一个节点的事件类型
                //道路信息-动态类应用
                MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadDynamic;
                break;
            }
            default:
            {
                //道路信息-半静态类应用
                MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSIRoadHalfStatic;
            }
            }
        }
        break;
    case MessageFrame_PR_spatFrame:
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.SPATMSGAID;
        break;
    case MessageFrame_PR_rsmFrame:
        MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSMMSGAID;
        break;
    case MessageFrame_PR_msgFrameExt:
        switch (pstruMsgFrame->choice.msgFrameExt.value.present)
        {
            /*二期场景消息集*/
        case value_PR_TestMsg:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.TESTMSGAID;
            break;
        }
        case value_PR_RTCMcorrections:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RTCMMSGAID;
            break;
        }
        case value_PR_PAMData:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.PAMMSGAID;
            break;
        }
        case value_PR_CLPMM:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.CLPMMMSGAID;
            break;
        }
        case value_PR_PersonalSafetyMessage:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.PSMMSGAID;
            break;
        }
        case value_PR_RoadsideCoordination:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.RSCMSGAID;
            break;
        }
        case value_PR_SensorSharingMsg:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.SSMMSGAID;
            break;
        }
        case value_PR_VehIntentionAndRequest:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.VIRMSGAID;
            break;
        }
        case value_PR_VehiclePaymentMessage:
        {
            MessageAID = ProtocolStackParamConfig.messageParamConfig.msgAid.VPMMSGAID;
            break;
        }
        default:
        {
            LogPrint(LOG_LEVEL_ERR,
                     "MSGLAYERV2MSG",
                     "Msg present is err:pstruMsgFrame->present = %d", pstruMsgFrame->choice.msgFrameExt.value.present);
            break;
        }
        }
        break;
    default:
        LogPrint(LOG_LEVEL_ERR,
                 "MSGLAYERV2MSG",
                 "Msg present is err:pstruMsgFrame->present = %d", pstruMsgFrame->present);
        break;
    }
    return MessageAID;
}