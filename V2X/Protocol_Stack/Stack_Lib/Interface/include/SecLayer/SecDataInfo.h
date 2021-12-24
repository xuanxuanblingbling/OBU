/**
 * @ingroup SecLayer API
 * @{
 *
 * 本模块提供安全层签名消息基本的数据结构.
 *
 * @file SecDataInfo.h
 * @brief API file.
 *
 */
#ifndef _SECDATAINFO_H_
#define _SECDATAINFO_H_

#define MAX_DUMMY_PACKET_LEN (5000)
typedef enum CerType
{
	CerType_Pc = 1, //假名证书
	CerType_Ac = 2	//应用证书
} CerType;
/**
 * @brief 标准消息打包结构体
 */
typedef struct _MsgLayData_st
{
	unsigned long long nAID;						   //消息AID
	CerType u8UseCerType;							   //证书类型
	unsigned char pu8MsgLayData[MAX_DUMMY_PACKET_LEN]; //不包含安全签名的码流
	signed int n32MsgLayDataLen;					   //不包含安全签名的码流长度
	int nEmergencyEventFlag;						   //OBU紧急事件标志 0：无紧急事件 1：有紧急事件
	double dLongitude;								   //OBU经度信息
	double dLatitude;								   //OBU纬度信息
} __attribute__((packed)) MsgLayData_st;

enum cert_status
{
	CERT_NORMAL = 0,
	CERT_CHANGED, //签名签名证书改变
};

struct seclayer_status_t
{
	enum cert_status cert_change_flg; //签名证书是否改变
};

//回调函数，通知安全层状态到上层应用。目前用于通知签名证书的改变。
typedef void (*seclayer_status_callback)(struct seclayer_status_t *sta, void *para);

/**
 * @brief SECSIGNCALL_BACK 安全消息签名接口
 *
 * @param[in] MsgLayData_st -- 待签名的数据信息
 * @param[out] pu8SecLayData -- 已签名的数据信息
 * @param[out] pn32SecLayDataLen -- 已签名的数据信息长度
 *
 */
typedef int (*SECSIGNCALL_BACK)(MsgLayData_st MsgLayData, unsigned char *pu8SecLayData, int *pn32SecLayDataLen);

/**
 * @brief SECVERICALL_BACK 安全消息验签接口
 *
 * @param[in] pu8SecLayData -- 待验签的数据信息
 * @param[in] pn32SecLayDataLen -- 待验签的数据信息长度
 * @param[out] MsgLayData_st -- 已验签的数据信息
 *
 */
typedef int (*SECVERICALL_BACK)(unsigned char *pu8SecLayData, int n32SecLayDataLen, MsgLayData_st *MsgLayData);

#endif
