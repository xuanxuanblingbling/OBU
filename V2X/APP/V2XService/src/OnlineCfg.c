/*******************************************************************************
 * 文 件 名 称 ： OnlineCfg.c
 * 功 能 描 述 ： BSMTx模块在线配置文件解析
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-09-01 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/

#include "Common.h"
#include "cJSON.h"

#define MODULE_NAME "BSMTx"
#include "Debug.h"

static int Print_Json(cJSON *p_json)
{
    char *l_pCjson;
    if (LOOK_UNLIKELY(p_json))
        return -1;

    l_pCjson = cJSON_Print(p_json);
    printf("%s\n", l_pCjson);
    free(l_pCjson);
    l_pCjson = NULL;
}

static cJSON *Read_JFile(const char *p_pPathFile)
{
    char *l_pn8Buf;
    int l_n32Fd;
    size_t l_u32FileSIze;
    cJSON *l_pCjsonRoot = NULL;

    if (LOOK_UNLIKELY(p_pPathFile))
        return NULL;
    if ((l_n32Fd = open(p_pPathFile, O_RDONLY, 0644)) == -1)
    {
        ERR_MSG("open");
        return NULL;
    }

    l_u32FileSIze = lseek(l_n32Fd, 0, SEEK_END);
    lseek(l_n32Fd, 0, SEEK_SET);

    l_pn8Buf = (char *)calloc(1, l_u32FileSIze + 1);
    if (LOOK_UNLIKELY(l_pn8Buf))
        return NULL;
    bzero(l_pn8Buf, l_u32FileSIze + 1);

    ssize_t l_nbytes = read(l_n32Fd, l_pn8Buf, l_u32FileSIze);
    if (l_nbytes == -1)
    {
        ERR_MSG("read");
        free(l_pn8Buf);
        l_pn8Buf = NULL;
        return NULL;
    }
    close(l_n32Fd);

    l_pCjsonRoot = cJSON_Parse(l_pn8Buf);
    if (LOOK_UNLIKELY(l_pCjsonRoot))
    {
        ERR("cJSON_Parse error:%s\n", cJSON_GetErrorPtr());
        l_pCjsonRoot = NULL;
    }
    else
    {
        Print_Json(l_pCjsonRoot);
    }

    free(l_pn8Buf);
    l_pn8Buf = NULL;
    return l_pCjsonRoot;
}

static int Free_Json(cJSON *p_json)
{
    if (LOOK_UNLIKELY(p_json))
        return -1;
    else
        cJSON_Delete(p_json);
    return 0;
}

int FV_ParseV2XOnlineCfg(TV2XOnLineConfigType *p_pOnlineCfg, const char *p_pPathFile)
{
    if (LOOK_UNLIKELY(p_pOnlineCfg))
    {
        ERR("Invalid Param!\n");
        return -1;
    }

    cJSON *l_pCjsonRoot = Read_JFile(p_pPathFile);
    if (LOOK_UNLIKELY(l_pCjsonRoot))
    {
        ERR("Invalid cJson Root!\n");
        return -1;
    }

    cJSON *l_pJsonLevel1Root = cJSON_GetObjectItem(l_pCjsonRoot, "BSMTx");
    cJSON *l_pLevel1Child = cJSON_GetObjectItem(l_pJsonLevel1Root, "wgs2gcj");
    p_pOnlineCfg->m_BSMTx.m_Wgs2Gci = l_pLevel1Child->valueint;
    l_pLevel1Child = cJSON_GetObjectItem(l_pJsonLevel1Root, "randId");
    p_pOnlineCfg->m_BSMTx.m_RandId = l_pLevel1Child->valueint;
    l_pLevel1Child = cJSON_GetObjectItem(l_pJsonLevel1Root, "cbrCtrl");
    p_pOnlineCfg->m_BSMTx.m_CbrCtl = l_pLevel1Child->valueint;

    l_pJsonLevel1Root = cJSON_GetObjectItem(l_pCjsonRoot, "CertM");
    l_pLevel1Child = cJSON_GetObjectItem(l_pJsonLevel1Root, "certUpdate");
    p_pOnlineCfg->m_CerM.m_CertUpdate = l_pLevel1Child->valueint;
    l_pLevel1Child = cJSON_GetObjectItem(l_pJsonLevel1Root, "hsmType");
    p_pOnlineCfg->m_CerM.m_HsmType = l_pLevel1Child->valueint;
    l_pLevel1Child = cJSON_GetObjectItem(l_pJsonLevel1Root, "caPlatform");
    p_pOnlineCfg->m_CerM.m_CAPlatform = l_pLevel1Child->valueint;
    return Free_Json(l_pCjsonRoot);
}

/* Nothing beyond compare */