#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include "seclayer.h"
#include "distance-calc.h"
#include "sdpf_api.h"
#include "ds_api.h"

#define SEC_MODULE_ONLINE 0 // 1:在线模式  0:离线模式

#define PC_CERTS_NUM    (20)    //20个PC证书
#define CERT_EXPIRED_TIME   (300000)   //300秒换一张证书
#define BIG_SMALL_MODE_CYCLE    (450)   //一大四小模式450毫秒为一个周期
#define CERT_CHANGE_DISTANCE    (2000)  //超过2000m后再进行证书切换

#define MODULE_NAME "seclayer"

#define  TDCL_ROOT_DIR "/mnt/APP/Config/obu/v2x/"

#define CERT_TYPE   1      //输入证书类型:1 PC，2 AC ,3 保留
#define RCA_PATH    "/mnt/APP/Config/obu/v2x/cacerts"
#define ECA_PATH    "/mnt/APP/Config/obu/v2x/eccerts"
#define PCA_PATH    "/mnt/APP/Config/obu/v2x/pccerts"
#define ACA_PATH    "/mnt/APP/Config/obu/v2x/accerts"

enum sign_mode
{
    SMALL_MODE_SIGN = 0,    //以小模式进行签名
    BIG_MODE_SIGN           //以大模式进行签名
};


struct postion_t
{
    double longitude;   //经度
    double latitude;    //纬度
};

struct seclayer_info_t
{
    int32_t first_paket;                  //1表示为第一包签名数据；
    int32_t curr_cert_id;                 //当前使用的证书id
    uint32_t last_big_mode_time_ms;      //最近一次携带完整证书(大模式)的时间
    uint32_t cert_used_first_time_ms;    //当前证书第一次使用的时间
    struct postion_t last_pos;           //第一次使用当前证书签名时的位置
    seclayer_status_callback cb_fun;     //回调函数，用于证书切换时通知上层应用
    void *cb_para;                       //回调函数参数
    pthread_mutex_t seclayer_lock;       //对句柄进行加锁
};

//安全层操作句柄
static struct seclayer_info_t *s_seclayer_handle = NULL;


//得到当前毫秒级时间
static uint32_t current_time_ms_get(void)
{
    struct timeval curr_time = {0};

    gettimeofday(&curr_time, NULL);

    return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}


//随机获取证书id，用于签名
static uint32_t random_cert_id_get(void)
{
    return random() % 20;
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

int32_t seclayer_init(seclayer_status_callback cb, void *cb_para)
{
    struct seclayer_info_t *seclayer_handle = NULL;
    int32_t ret = 0;

    if (NULL == cb)
    {
        printf("callback function is NULL\n");
        return -1;
    }

#if SEC_MODULE_ONLINE
    ret = ITS_SDPF_Init();
    if (0 != ret)
    {
        printf("sdpf init failed\n");
        return -1;
    }
#else

    ret = DS_InitSecurityService(TDCL_ROOT_DIR);
    if(Err_ok != ret)
    {
        printf("init fail\n");
        return ret;
    }

    ret = DS_LoadOfflineCert(RCA_PATH, ECA_PATH, PCA_PATH, ACA_PATH);
    if(Err_ok != ret)
    {
        printf("DS_LoadOfflineCert fail\n");
    }

    ret = DS_InitSecurityService(TDCL_ROOT_DIR);
    if(Err_ok != ret)
    {
        printf("init fail\n");
        return -1;
    }

#endif

    seclayer_handle = (struct seclayer_info_t *)malloc(sizeof(struct seclayer_info_t));
    if (NULL == seclayer_handle)
    {
        printf("malloc failed\n");
        return -1;
    }

    memset(seclayer_handle, 0, (sizeof(struct seclayer_info_t)));

    seclayer_handle->cb_fun = cb;
    seclayer_handle->cb_para = cb_para;

    ret = pthread_mutex_init(&seclayer_handle->seclayer_lock, NULL);
    if (0 != ret)
    {
        printf("pthread mutex init failed\n");
        free(seclayer_handle);
    }

    seclayer_handle->first_paket = 1;
    seclayer_handle->curr_cert_id = random_cert_id_get(); //随机选择一个证书

    s_seclayer_handle = seclayer_handle;

    return 0;
}


int32_t seclayer_sign(int32_t aid, int32_t emergency_event_flag, double longitude, double latitude, uint8_t *pdu, uint32_t pdu_size, uint8_t *spdu, uint32_t *spdu_size)
{
    struct seclayer_info_t *seclayer_handle = s_seclayer_handle;
    enum sign_mode mode = BIG_MODE_SIGN;
    struct postion_t curr_pos = {0};
    struct seclayer_status_t sec_status = {0};
    uint32_t cert_id = 0;
    int32_t ret = 0;

    if ((NULL == pdu) || (0 == pdu_size) || (NULL == spdu) || (NULL == spdu_size) || (0 == *spdu_size))
    {
        printf("wrong para\n");
        return -1;
    }

    if (NULL == seclayer_handle)
    {
        printf("call seclayer_init first\n");
        return -1;
    }

    curr_pos.latitude = latitude;
    curr_pos.longitude = longitude;

    pthread_mutex_lock(&seclayer_handle->seclayer_lock);
    if (1 == seclayer_handle->first_paket)
    {//第一包需要验签的数据，
        cert_id = seclayer_handle->curr_cert_id;
        mode = BIG_MODE_SIGN;
        seclayer_handle->first_paket = 0;
        seclayer_handle->cert_used_first_time_ms = current_time_ms_get();
        seclayer_handle->last_big_mode_time_ms = current_time_ms_get();

        seclayer_handle->last_pos.latitude = latitude;
        seclayer_handle->last_pos.longitude = longitude;
    }
    else if (0 != emergency_event_flag)
    {//有紧急事件,那么就携带当前完整证书
        cert_id = seclayer_handle->curr_cert_id;
        mode = BIG_MODE_SIGN;
        seclayer_handle->last_big_mode_time_ms = current_time_ms_get();

    }
    else if (1 != distance_judge(&seclayer_handle->last_pos, &curr_pos))
    {//距离小于2KM，继续使用当前证书
        cert_id = seclayer_handle->curr_cert_id;
        if (mode_used_cycle_time_judge(seclayer_handle->last_big_mode_time_ms))
        {//距离上一次携带完整证书已经过去450ms,使用大模式进行签名
            mode = BIG_MODE_SIGN;
            seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
        }
        else
        {
            mode = SMALL_MODE_SIGN;
        }

    }
    else if (cert_used_time_judge(seclayer_handle->cert_used_first_time_ms))
    {//距离大于2KM，当前证书使用超过300s,切换证书
        sec_status.cert_change_flg = CERT_CHANGED;
        mode = BIG_MODE_SIGN;
        cert_id = random_cert_id_get();
        seclayer_handle->cert_used_first_time_ms = current_time_ms_get();
        seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
        seclayer_handle->cb_fun(seclayer_handle->cb_para, &sec_status);     //调用回调函数，通知上层应用证书改变

        seclayer_handle->last_pos.latitude = latitude;
        seclayer_handle->last_pos.longitude = longitude;

    }
    else
    {//没有关键事件，距离大于2KM，当前证书使用没有超过300s
        cert_id = seclayer_handle->curr_cert_id;
        if (mode_used_cycle_time_judge(seclayer_handle->last_big_mode_time_ms))
        {//距离上一次携带完整证书已经过去450ms,使用大模式进行签名
            mode = BIG_MODE_SIGN;
            seclayer_handle->last_big_mode_time_ms = current_time_ms_get();
        }
        else
        {
            mode = SMALL_MODE_SIGN;
        }

    }


#if SEC_MODULE_ONLINE

    ret = ITS_SDPF_GenSignedSPDU(1, cert_id, mode, aid, pdu, pdu_size, spdu, spdu_size);
    printf("signed spdu result:%d\n", ret);

#else

    ret = DS_Sign(CERT_TYPE, cert_id, mode, aid, pdu, pdu_size, spdu, spdu_size);
    if(Err_ok != ret)
    {
        printf("generate spdu fail\n");
        return ret;
    }

#endif

    seclayer_handle->curr_cert_id = cert_id;
    pthread_mutex_unlock(&seclayer_handle->seclayer_lock);

    return ret;
}


int32_t seclayer_verify(long aid, uint8_t *spdu, uint32_t spdu_size, uint8_t *pdu, uint32_t *pdu_size)
{
    struct seclayer_info_t *seclayer_handle = s_seclayer_handle;
    int32_t ret = 0;

    if ((NULL == spdu) || (0 == spdu_size) || (NULL == pdu) || (NULL == pdu_size) || (0 == *pdu_size))
    {
        printf("wrong para\n");
        return -1;
    }

    if (NULL == seclayer_handle)
    {
        printf("call seclayer_init first\n");
        return -1;
    }

    pthread_mutex_lock(&seclayer_handle->seclayer_lock);

#if SEC_MODULE_ONLINE
    ret = ITS_SDPF_VerifySignedSPDU(aid, spdu, spdu_size, pdu, pdu_size);
    printf("verify result:%d\n", ret);

#else
    ret = DS_VerifySigned(aid, spdu, spdu_size, pdu, pdu_size);
    if(Err_ok != ret)
    {
        printf("verify spdu fail\n");
    }
#endif

    pthread_mutex_unlock(&seclayer_handle->seclayer_lock);

    return ret;
}


int32_t seclayer_deinit(void)
{
    struct seclayer_info_t *seclayer_handle = s_seclayer_handle;

    if (NULL == seclayer_handle)
    {
        printf("call seclayer_init first\n");
        return -1;
    }

    pthread_mutex_destroy(&seclayer_handle->seclayer_lock);
    free(seclayer_handle);
    s_seclayer_handle = NULL;

#if SEC_MODULE_ONLINE

    ITS_SDPF_Destroy();
#endif
    return 0;
}
