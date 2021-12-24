/*******************************************************************************
 * 文 件 名 称 ： OnlineCfg.h
 * 功 能 描 述 ： BSMTx模块在线配置文件解析头文件
 * 开 发 人 员 ： YaoZhiqiang
 * 日期       版本  修改人    描述
 * ========== ======= ========= =======================================
 * 2020-09-01 V1.0    YaoZhiqiang   Create
 *
 * @Copyright (C)  2020  .wanji. all right reserved
*******************************************************************************/
#ifndef __ON_LINE_CFG__
#define __ON_LINE_CFG__

#include "V2xBasicTypes.h"

V2X_BEGIN_HEADER

typedef struct
{
    struct
    {
        int m_Wgs2Gci;
        int m_RandId;
        int m_CbrCtl;
    } m_BSMTx;

    struct
    {
        int m_CertUpdate;
        int m_HsmType;
        int m_CAPlatform;
    } m_CerM;
} TV2XOnLineConfigType;

V2X_END_HEADER

#endif /* __ON_LINE_CFG__ */
