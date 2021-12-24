#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
// #include "common.h"
#include "sdpf_api.h"
#include "wj_log.h"
#include "distance-calc.h"
#include "XdjaKeyApi.h"
// #include "SecLayer.h"
#include "Chip_xdjaNewF.h"
#include "rw-ini.h"

#define MODULE_NAME "Chip_xdja"
#define RSU_PROTOCOL_PATH "/mnt/APP/Config/Config_ProtocolStack.ini"
#define OBU_PROTOCOL_PATH "/mnt/APP/Config/obu/v2x/ProtocolStack.ini"
struct XdjaPinConfig s_XdjaPinConfig;
//安全层操作句柄
struct xdja_seclayer_info_t *s_xdja_seclayer_handle;
#define SECLAYER_ERR(fmt, ...) printf("\033[31m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)
#define SECLAYER_INFO(fmt, ...) printf("\033[32m[Seclayer: %s:%d:%s:%s] " #fmt "\033[0m\r\n", __func__, __LINE__, __DATE__, __TIME__, ##__VA_ARGS__)
//得到当前毫秒级时间
static uint32_t current_time_ms_get(void)
{
    struct timeval curr_time = {0};

    gettimeofday(&curr_time, NULL);

    return (uint32_t)(curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}

//随机获取证书id，用于签名
uint32_t RandomCertIdGet(void)
{
    return random() % 20;
}

uint32_t DirIsExist(const char *file_name)
{
    struct stat buf;
    if(stat(file_name,&buf)==0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

//判断大小模式是否已经一个周期——450ms.1:大于;0:小于等于
static uint8_t mode_used_cycle_time_judge(uint32_t last_time)
{
    uint32_t curr_time = current_time_ms_get();

    if ((curr_time - last_time) >= BIG_SMALL_MODE_CYCLE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//判断证书使用时间是否大于300秒。1:大于;0:小于等于
static uint8_t cert_used_time_judge(uint32_t last_time)
{
    uint32_t curr_time = current_time_ms_get();

    if ((curr_time - last_time) >= CERT_EXPIRED_TIME)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//判断与上次签名是否大于2Km.1:距离大于2Km,0:距离小于2Km
static uint8_t distance_judge(struct postion_t *last_pos, struct postion_t *curr_pos)
{
    double temp = 0.0;
    int32_t distance = 0;

    temp = FG_Getdistance(last_pos->latitude, last_pos->longitude, curr_pos->latitude, curr_pos->longitude);
    distance = (int32_t)floor(temp);

    if (distance >= CERT_CHANGE_DISTANCE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static int GetConfigInfo(const char *FileName)
{
    if (NULL == FileName)
    {
        LogPrint(LOG_LEVEL_INFO, "协议栈参数配置", "param is NULL\n");
        SECLAYER_ERR("协议栈参数配置为空");
        return -1;
    }
    int iVariable = 0;
   

    //参数设置

    s_XdjaPinConfig.m_n32EncryptChipPinInt0 = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipPinInt0", iVariable, FileName);
    s_XdjaPinConfig.m_n32EncryptChipPinInt1 = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipPinInt1", iVariable, FileName);

    //默认不使用，此处以宏定义赋值
    s_XdjaPinConfig.m_n32EncryptChipPinPor = SEC_EncryptChipPinPor;
    s_XdjaPinConfig.m_n32EncryptChipPinPower = SEC_EncryptChipPinPower;
    s_XdjaPinConfig.m_n32EncryptChipPinQwk = SEC_EncryptChipPinQwk;

    s_XdjaPinConfig.m_n32EncryptChipSpeed = SecGetPrivateProfileInt("SecurityParamConfig", "EncryptChipSpeed", iVariable, FileName);
    return 0;
}
//芯片厂商检查-- 信大捷安
uint32_t SecChipFactoryCheck()
{
    int ret = 0;
    int Config_status = 0;
    XKF_HANDLE handle = NULL;
    char *devName = "/dev/spidev0.0";
    XDJA_SPI_CONFIG config = {0};
    XDJA_DEVINFO devInfo = {0};
    ret = DirIsExist(RSU_PROTOCOL_PATH);
    if (0 == ret)
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "%s is exist", RSU_PROTOCOL_PATH);
        GetConfigInfo(RSU_PROTOCOL_PATH);
        Config_status++;
    }
    ret = DirIsExist(OBU_PROTOCOL_PATH);
    if (0 == ret)
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "%s is exist", OBU_PROTOCOL_PATH);
        GetConfigInfo(OBU_PROTOCOL_PATH);
        Config_status++;
    }
    if(Config_status == 0)
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "not find any config, default factory is xdja");
        return 0;
    }
    else if(Config_status == 2)
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "read twice,delet one config");
    }
    
    config.XDJA_INT0_GPIO = s_XdjaPinConfig.m_n32EncryptChipPinInt0;
    config.XDJA_INT1_GPIO = s_XdjaPinConfig.m_n32EncryptChipPinInt1;
    config.XDJA_POR_GPIO = s_XdjaPinConfig.m_n32EncryptChipPinPor;
    config.XDJA_POWER_GPIO = s_XdjaPinConfig.m_n32EncryptChipPinPower;
    config.XDJA_QWK_GPIO = s_XdjaPinConfig.m_n32EncryptChipPinQwk;
    config.SPI_SPEED = s_XdjaPinConfig.m_n32EncryptChipSpeed;

    ret = XKF_SPI_CONFIG(config);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "XKF_SPI_CONFIG  Failed, ret is %d", ret);
        SECLAYER_ERR("XKF_SPI_CONFIG Failed");
        return ret;
    }

    ret = XKF_OpenDevByName((const unsigned char *)devName, &handle);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "XKF_OpenDevByName Failed, ret is %d", ret);
        SECLAYER_ERR("XKF_OpenDevByName Failed");
        return ret;
    }

    ret = XKF_GetDevInfo(handle, &devInfo);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "XKF_GetDevInfo Failed, ret is %d", ret);
        SECLAYER_ERR("XKF_GetDevInfo Failed");
        return ret;
    }
    XKF_CloseDev(handle);

    return 0;
}



int32_t SecChip_Init(seclayer_status_callback cb, void *cb_para, const char *fileName)
{
    int32_t ret = -1;
    char version[100] = {0};
    int versionlen = sizeof(version);
    ret = GetConfigInfo(fileName);

    /* 设置log路径 */
    ITS_SDPF_SetLogConf((const char *)"/mnt/RWD/RsuLog", 10);
    /* 设置安全芯片对应的IO */
    ret = ITS_SDPF_SetSafeChipGpio(s_XdjaPinConfig.m_n32EncryptChipPinInt0, s_XdjaPinConfig.m_n32EncryptChipPinInt1,
                                    s_XdjaPinConfig.m_n32EncryptChipPinPor, s_XdjaPinConfig.m_n32EncryptChipPinPower,
                                    s_XdjaPinConfig.m_n32EncryptChipPinQwk, s_XdjaPinConfig.m_n32EncryptChipSpeed);
    if (Err_ok != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "ITS_SDPF_SetSafeChipGpio Failed");
        SECLAYER_ERR("ITS_SDPF_SetSafeChipGpio Failed");
        return -1;
    }
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "ITS_SDPF_SetSafeChipGpio Success");
    SECLAYER_INFO("ITS_SDPF_SetSafeChipGpio Success");

    /* 初始化签名 */
    ret = ITS_SDPF_Init((const char *)"/mnt/APP/Config/certs");
    if (Err_ok != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "ITS_SDPF_Init_ Failed");
        SECLAYER_ERR("ITS_SDPF_Init_ Failed");
        return -1;
    }
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "ITS_SDPF_Init_ Success");
    SECLAYER_INFO("ITS_SDPF_Init_ Success");

    /* 获取版本 */
    ret = ITS_SDPF_Version(version, &versionlen);
    if (Err_ok != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Get Version Failed");
        SECLAYER_ERR("Get Version Failed");
    }
    else
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "version:%s\n", version);
    }
    s_xdja_seclayer_handle = (struct xdja_seclayer_info_t*)malloc(sizeof(struct xdja_seclayer_info_t));
    s_xdja_seclayer_handle->cb_fun = cb;
    s_xdja_seclayer_handle->cb_para = cb_para;

    ret = pthread_mutex_init(&s_xdja_seclayer_handle->seclayer_lock, NULL);
    if (0 != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "pthread mutex init failed");
        SECLAYER_ERR("<<<<<<<< pthread mutex init failed");
        free(s_xdja_seclayer_handle);
    }

    s_xdja_seclayer_handle->first_paket = 1;
    s_xdja_seclayer_handle->curr_cert_id = RandomCertIdGet(); //随机选择一个证书

    return 0;
}

int32_t SecDataSign_RSU(uint64_t aid, uint8_t *pdu, int32_t pdu_size,
                                  uint8_t *spdu, int32_t *spdu_size)
{
    struct xdja_seclayer_info_t *seclayer_handle = s_xdja_seclayer_handle;
    enum sign_mode mode = BIG_MODE_SIGN;
    // struct seclayer_status_t sec_status = {0};
    uint32_t cert_id = 0;
    int32_t ret = -1;

    if ((NULL == pdu) || (0 == pdu_size) ||
        (NULL == spdu) || (NULL == spdu_size) || (0 == *spdu_size))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "XDJA Sign NewFour_RSU Para Wrong");
        SECLAYER_ERR("XDJA Sign NewFour_RSU Para Wrong");
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "PDU SIZE %d ", pdu_size);
        SECLAYER_ERR("PDU SIZE %d ", pdu_size);
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "SPDU SIZE %d ", *spdu_size);
        SECLAYER_ERR("SPDU SIZE %d ", *spdu_size);

        return -1;
    }

    if (NULL == seclayer_handle)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Seclayer Handle Is NULL ");
        SECLAYER_ERR("Seclayer Handle Is NULL ");
        return -1;
    }
    /*cert id is 0*/
    pthread_mutex_lock(&seclayer_handle->seclayer_lock);
    if (1 == seclayer_handle->first_paket)
    { //第一包需要验签的数据，
        cert_id = seclayer_handle->curr_cert_id;
        mode = BIG_MODE_SIGN;
        seclayer_handle->first_paket = 0;
        seclayer_handle->cert_used_first_time_ms = current_time_ms_get();
        seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
    }
    else
    {
        if (mode_used_cycle_time_judge(seclayer_handle->last_big_mode_time_ms))
        { //距离上一次携带完整证书已经过去450ms,使用大模式进行签名
            mode = BIG_MODE_SIGN;
            seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
        }
        else
        {
            mode = SMALL_MODE_SIGN;
        }
    }

    ret = ITS_SDPF_GenSignedSPDU(AC_CERT_SIGN, cert_id, mode, aid, pdu, pdu_size, spdu, spdu_size);
    if (IS_OK != ret)
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "<<<<<<<< XDJA Sign NewFour_RSU PDU Failed , Ret is %d", ret);
        SECLAYER_ERR("<<<<<<<< XDJA Sign NewFour_RSU PDU Failed , Ret is %d", ret);
    }
    pthread_mutex_unlock(&seclayer_handle->seclayer_lock);
    LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "XDJA Sign New Four PDU RSU Result , Ret is %d", ret);
    return ret;
}

int32_t SecDataSign_OBU(uint64_t aid, int32_t emergency_event_flag,
                                  double longitude, double latitude,
                                  uint8_t *pdu, int32_t pdu_size, uint8_t *spdu, int32_t *spdu_size)
{
    struct xdja_seclayer_info_t *seclayer_handle = s_xdja_seclayer_handle;
    enum sign_mode mode = BIG_MODE_SIGN;
    struct postion_t curr_pos = {0};
    struct seclayer_status_t sec_status = {0};
    uint32_t cert_id = 0;
    int32_t ret = 0;

    if ((NULL == pdu) || (0 == pdu_size) || (NULL == spdu) || (NULL == spdu_size) || (0 == *spdu_size))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "<<<<<<<< Sign NewFour_OBU Para Wrong");
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "PDU SIZE %d ", pdu_size);
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "SPDU SIZE %d ", *spdu_size);
        SECLAYER_ERR("<<<<<<<< Sign NewFour_OBU Para Wrong");
        SECLAYER_ERR("PDU SIZE %d ", pdu_size);
        SECLAYER_ERR("SPDU SIZE %d ", *spdu_size);
        return -1;
    }

    if (NULL == seclayer_handle)
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "Call SeclayerInit First");
        SECLAYER_ERR("Call SeclayerInit First");
        return -1;
    }

    curr_pos.latitude = latitude;
    curr_pos.longitude = longitude;

    pthread_mutex_lock(&seclayer_handle->seclayer_lock);
    if (1 == seclayer_handle->first_paket)
    { //第一包需要验签的数据，
        cert_id = seclayer_handle->curr_cert_id;
        mode = BIG_MODE_SIGN;
        seclayer_handle->first_paket = 0;
        seclayer_handle->cert_used_first_time_ms = current_time_ms_get();
        seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
    }
    else if (0 != emergency_event_flag)
    { //有紧急事件,那么就携带当前完整证书
        cert_id = seclayer_handle->curr_cert_id;
        mode = BIG_MODE_SIGN;
        seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
    }
    else if (1 != distance_judge(&seclayer_handle->last_pos, &curr_pos))
    { //距离小于2KM，继续使用当前证书
        cert_id = seclayer_handle->curr_cert_id;
        if (mode_used_cycle_time_judge(seclayer_handle->last_big_mode_time_ms))
        { //距离上一次携带完整证书已经过去450ms,使用大模式进行签名
            mode = BIG_MODE_SIGN;
            seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
        }
        else
        {
            mode = SMALL_MODE_SIGN;
        }
    }
    else if (cert_used_time_judge(seclayer_handle->cert_used_first_time_ms))
    { //距离大于2KM，当前证书使用超过300s,切换证书
        sec_status.cert_change_flg = CERT_CHANGED;
        mode = BIG_MODE_SIGN;
        cert_id = RandomCertIdGet(); //random_cert_id_get
        seclayer_handle->cert_used_first_time_ms = current_time_ms_get();
        seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
        seclayer_handle->last_pos.latitude = latitude;
        seclayer_handle->last_pos.longitude = longitude;
        seclayer_handle->cb_fun(&sec_status, seclayer_handle->cb_para); //调用回调函数，通知上层应用证书改变
    }
    else
    { //没有关键事件，距离大于2KM，当前证书使用没有超过300s
        cert_id = seclayer_handle->curr_cert_id;
        if (mode_used_cycle_time_judge(seclayer_handle->last_big_mode_time_ms))
        { //距离上一次携带完整证书已经过去450ms,使用大模式进行签名
            mode = BIG_MODE_SIGN;
            seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
        }
        else
        {
            mode = SMALL_MODE_SIGN;
        }
    }

    ret = ITS_SDPF_GenSignedSPDU(PC_CERT_SIGN, cert_id, mode, aid, pdu, pdu_size, spdu, spdu_size);
    if (IS_OK != ret)
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "<<<<<<<< XDJA Sign NewFour_RSU PDU Failed , Ret is %d", ret);
        SECLAYER_ERR("<<<<<<<< XDJA Sign NewFour_RSU PDU Failed , Ret is %d", ret);
    }
    seclayer_handle->curr_cert_id = cert_id;
    pthread_mutex_unlock(&seclayer_handle->seclayer_lock);
    // LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "XDJA Sign New Four PDU OBU Result , Ret is %d", ret);

    return ret;
}

int32_t SecDataVerify(uint8_t *spdu, int32_t spdu_size,
                                uint8_t *pdu, int32_t *pdu_size,uint64_t* aid)
{
    struct xdja_seclayer_info_t *seclayer_handle = s_xdja_seclayer_handle;
    int32_t ret = -1;

    if ((NULL == spdu) || (0 == spdu_size) || (NULL == pdu) ||
        (NULL == pdu_size) || (0 == *pdu_size))
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< XDJA Verify NewFour Para Wrong");
        SECLAYER_ERR("<<<<<<<< XDJA Verify NewFour Para Wrong");
        return -1;
    }

    if (NULL == seclayer_handle)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "Call SeclayerInit First");
        SECLAYER_ERR("Call SeclayerInit First");
        return -1;
    }
    //printf("-----------------p_pu64AID = %d\n",*aid);
    pthread_mutex_lock(&seclayer_handle->seclayer_lock);
    ret = ITS_SDPF_VerifySignedSPDU(*aid, spdu, spdu_size, pdu, pdu_size);
    if (IS_OK != ret)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "<<<<<<<< XDJA Verify NewFour SPDU Failed  Ret is %d", ret);
        SECLAYER_ERR("<<<<<<<< XDJA Verify NewFour SPDU Failed , Ret is %d", ret);
    }
    pthread_mutex_unlock(&seclayer_handle->seclayer_lock);
    // LogPrint(LOG_LEVEL_INFO, MODULE_NAME, "XDJA Verify New Four SPDU Result , Ret is %d", ret);

    return ret;
}

int32_t SecChipDeinit(void)
{
    struct xdja_seclayer_info_t *seclayer_handle = s_xdja_seclayer_handle;

    if (NULL == seclayer_handle)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "call seclayer_init first");
        SECLAYER_ERR("<<<<<<<< call seclayer_init first");
        return -1;
    }

    pthread_mutex_destroy(&seclayer_handle->seclayer_lock);
    free(seclayer_handle);
    s_xdja_seclayer_handle = NULL;
    ITS_SDPF_Destroy();

    return 0;
}