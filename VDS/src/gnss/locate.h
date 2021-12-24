#ifndef _LOCATE_H
#define _LOCATE_H

#include <stdio.h>

#define AG35_CONFIG_RQ_TAG    0x20//AG35配置请求TAG值

#define AG35_CONFIG_RS_TAG    0x90//AG35配置响应TAG值
#define AG35_LOCATE_TAG       0x91//AG35定位信息TAG值
#define AG35_FAULT_TAG        0x92//AG35故障反馈TAG值

#define AG35_MAX(a,b,c) (a>b?(a>c?a:c):(b>c?b:c))

#define AG35_MAX_BUF_LEN  AG35_MAX(AG35_LOCATE_FRAME_LEN,AG35_FAULT_FRAME_LEN,AG35_CFGRS_FRAME_LEN)

//Gnss数据
typedef struct gnss_data
{
	int64_t        m_time;//获取车辆经纬度的时间
    double         m_latitude;//纬度
    double         m_longitude;//经度
    double         m_altitude;//海拔
    double         m_semiMajorAxisAccuracy;//定位系统精度
    double         m_speed;//车速
    uint8_t        m_qtySvUsed;//gnss可用卫星个数
}__attribute__ ((packed))TGNSS;

typedef struct locate_data
{
    uint8_t        m_Tag;
    uint8_t        m_Length;
    TGNSS          gnss;
    uint8_t        m_Bcc;
}__attribute__ ((packed))TLOCATE_Data;

/**/
extern  TLOCATE_Data	 g_Location_Data;
/**/
extern  void    FL_GnssModuleCreat(void);

#endif
