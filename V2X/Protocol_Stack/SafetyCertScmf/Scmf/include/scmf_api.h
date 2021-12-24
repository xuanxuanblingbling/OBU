/*! @file       
 *  @author     wlx
 *  @version    1.1
 *  @brief      scmf api头文件
 */


#ifndef SCMF_API_H
#define SCMF_API_H

typedef enum _ErrCode
{
	SCMF_Err_Ok = 0x0,						//正确
	SCMF_Err_SetSafeChipGpioFailed = 0x100,	//设置安全芯片GPIO失败
	SCMF_Err_InitFailed,					//库初始化失败
	SCMF_Err_NoInitialized,					//库未初始化
	SCMF_Err_InvalidParam,					//无效参数
	SCMF_Err_StartServiceFailed,			//启动服务失败
	SCMF_Err_StopServiceFailed,				//停止服务失败

	SCMF_Err_Unknown  						//其它
}SCMF_ErrCode;

#pragma pack(1)
///后台服务URL地址
typedef struct _ServiceConfig
{
	char* eraUrl; 
	char* praUrl;
	char* araUrl;
	char* mraUrl;//若无，填NULL
	char* rdcUrl;//若无，填NULL
	char* mdcUrl;//若无，填NULL
	char* cpocUrl;//若无，填NULL
}TServiceConfig;

#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif

/**
    * @brief 设置芯片GPIO参数,在初始化前调用
    *
    * @param[in]  Int0  3276 INT1引脚，3275 INT4引脚
    * @param[in]  Int1  3276 INT4引脚，3275 INT5引脚
    * @param[in]  Por   POR复位引脚【可选，不使用保持-1】
    * @param[in]  Power GPIO供电引脚【可选，不使用保持-1】
    * @param[in]  Qwk   低功耗唤醒引脚【可选，不使用保持-1】
    * @param[in]  Speed SPI频率配置,默认20/MHz
    *
    * @return 错误码
    * @retval 0-成功 其他-错误
    * 优先查找芯片，
    */
int ITS_SCMF_SetSafeChipGpio(int Int0, int Int1, int Por, int Power, int Qwk, int Speed);

/**
    * @brief设置日志文件存储位置和大小,在初始化前调用, 若不设置，默认在/tmp路径下，大小10MB.
	*  		日志路径下包含scmf、ssf、xdjakey三个日志文件,容量至少4MB，3个类型日志容量分别为2M、1M、1M
    *
    * @param[in]    logFilePath    日志文件存储路径
    * @param[in]    capacity_mb    日志文件大小，单位：MB
    *
    */
void ITS_SCMF_SetLogConf(const char *logFilePath, int capacity_mb);

/**
    * @brief 初始化
    *
    * @param[in]  defaultAlg		 默认算法，0-sm2 1-nist，目前仅支持sm2
    * @param[in]  dataRootPath		 过程数据存放路径
    *
    * @return 错误码
    * @retval 0-成功 其他-错误
*/
int ITS_SCMF_Init(int defaultAlg,  const char* dataRootPath);

/**
    * @brief 回收资源
    *
    * @return 错误码
    * @retval 0为正确，其他为错误
*/ 
int ITS_SCMF_Destroy();

/**
    * @brief 查看版本信息
    *
    * @param[out] version             版本信息
    * @param[in/out] versionLen      版本信息长度
    * @return 错误码
    * @retval 0为正确，其他为错误
*/
int ITS_SCMF_Version(char* version, int* versionLen);

/**
    * @brief 启动服务
    *
    * @param[in] cfg   服务配置信息
    * @return 错误码
    * @retval 0为正确，其他为错误
*/
int ITS_SCMF_StartService(const TServiceConfig* cfg);

/**
    * @brief 停止服务
    *
    * @return 错误码
    * @retval 0为正确，其他为错误
*/
int ITS_SCMF_StopService();

#ifdef __cplusplus
}
#endif

#endif
