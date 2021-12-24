#include "ConfigModuleRW.h"
#include "wjvn4_uper_interface.h"
#include "./../MsgFrameVN4/MessageFrame.h"
#include "wj_log.h"

/*新四跨消息集接口*/
WJVN4_UperFromFileEncodeMain_BACK wjvn4_UperFromFileEncodeMain = NULL;
WJVN4_UperEncOrDecMain_BACK wjvn4_UperEncOrDecMain = NULL;

int getAIDFromFileVN4(void *pstruMsg);

void SetWJVN4_MessageCallback(WJVN4_UperFromFileEncodeMain_BACK p_wjvn4_UperFromFileEncodeMain,
                              WJVN4_UperEncOrDecMain_BACK p_wjvn4_UperEncOrDecMain,
                              WJVN4_SetGetAIDFromFileCallback p_wjvn4_SetGetAIDFromFileCallback)
{
    wjvn4_UperFromFileEncodeMain = p_wjvn4_UperFromFileEncodeMain;
    wjvn4_UperEncOrDecMain = p_wjvn4_UperEncOrDecMain;
    if (NULL != p_wjvn4_SetGetAIDFromFileCallback)
    {
        p_wjvn4_SetGetAIDFromFileCallback(getAIDFromFileVN4);
        printf("%s %s %d wjvn4_SetGetAIDFromFileCallback Success!\n", __FILE__, __FUNCTION__, __LINE__);
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
int getAIDFromFileVN4(void *pstruMsg)
{
    /* 入参为空检查 */
    if (NULL == pstruMsg)
    {
        LogPrint(LOG_LEVEL_ERR,
                 "MSGLAYERVN4MSG",
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
    default:
        LogPrint(LOG_LEVEL_ERR,
                 "MSGLAYERVN4MSG",
                 "Msg present is err:pstruMsgFrame->present = %d", pstruMsgFrame->present);
        break;
    }
    return MessageAID;
}