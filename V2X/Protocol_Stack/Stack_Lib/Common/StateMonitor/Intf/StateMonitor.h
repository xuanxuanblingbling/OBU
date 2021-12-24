/**
 * @defgroup StateInterface StateInterface API
 * @{
 *
 * 本模块提供V2X状态监控的API接口.
 *
 * @}
 *
 */

/**
 * @defgroup StateMonitor StateMonitor API
 * @ingroup StateInterface API
 * @{
 *
 * 本模块提供V2X状态监控的API接口.
 *
 * @file StateMonitor.h
 * @brief API file.
 *
 */

#ifndef _STATE_MONITOR_H_
#define _STATE_MONITOR_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
    /**
 * @brief StartV2xRunTimmeMonitor 状态监控启动线程
 *
 * @return IS_OK/IS_ERR             成功/失败
 * 
 * @author dongzhao
 */
    int StartV2xRunTimmeMonitor();
    void UpdateTxQueDataNum();
    void UpdateMsglayerTxDataNum();
    void UpdateMsglayerTxDatabyte(int Byte);
    void UpdateMsglayerTxData(int MsgType);
    void UpdateMsglayerTxDataHelper(int FrameMsgType);
    void UpdateSeclayerTxDataNum();
    void UpdatePC5TxDataNum();
    void UpdateMsglayerRxDatabyte(int Byte);
    void UpdateMsglayerRxDataNum();
    void UpdateMsglayerRxData(int MsgType);
    void UpdateMsglayerRxDataHelper(int FrameMsgType);
    void UpdateSeclayerRxDataNum();
    void UpdateNetlayerRxDataNum();

    void UpdateV2XStatus(int8_t V2xStatus);
    void UpdateSafetyCertStatus(int8_t CertStatus);
    //int GetStatisticsFromNetworkDev(char *pDevName, DevNetStatus* pDevInfo);

#ifdef __cplusplus
}
#endif

#endif