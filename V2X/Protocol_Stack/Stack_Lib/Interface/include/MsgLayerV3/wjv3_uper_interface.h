#ifndef _WJV3_UPER_INTERFDACE_H_
#define _WJV3_UPER_INTERFDACE_H_
#include "wjv3_uper_Msg.h"
#define DLL_PUBLIC __attribute__((visibility("default")))
typedef struct
{
    WJV3_ENUM_MessageFrame_PR enumMessageFrameType;
    union
    {
        WJV3_STRU_BasicSafetyMessage strubsmFrame;
        WJV3_STRU_MapData strumapFrame;
        WJV3_STRU_RoadsideSafetyMessage strursmFrame;
        WJV3_STRU_SPAT struspatFrame;
        WJV3_STRU_RoadSideInformation strursiFrame;
    } uniUperMsg;
} WJV3_STRU_MessageFrame;
typedef struct
{
    uint32_t u32MsgNo;
    /* 编码函数 */
    int32_t (*Encode_func)(void *, void *);
    /* 解码函数 */
    int32_t (*Decode_func)(void *, void *);
} FUNC_WJV3_UPER_SCHE;
typedef struct
{
    uint32_t u32Len;
#define MAXV3_UPERBUFF_SIZE 250000
    uint8_t *pu8buff;
} WJV3_UperData;
typedef enum
{
    MSGV3_MessageFrame_UperDecode = 1, /* 消息解码 */
    MSGV3_MessageFrame_UperEncode = 2, /* 消息编码 */

} WJV3_ENUM_InterFace;

/**
 * @brief SetGetAIDFromFileCallbackV3 设置获取AID回调函数接口（外部不使用）
 *
 * @param[in] pFunGetAid -- 获取AID的回调函数
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC void SetGetAIDFromFileCallbackV3(int (*pFunGetAid)(void *pstruMsg));

/**
 * @brief WJV3_UperFromFileEncodeMain 从本地文件解析xml数据，并输出uper码流
 *
 * @param[in] pn8FileName -- 文件路径及名称
 * @param[out] pstruUperData -- 消息层码流长度及uper码流
 * @param[out] pn32MsgAid -- 消息AID
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC int32_t WJV3_UperFromFileEncodeMain(WJV3_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid);

/**
 * @brief WJV3_UperEncOrDecMain 三跨消息编解码接口
 *
 * @param[in] InterFace -- 选择编码或解码
 * @param[in/out] pstruUperData -- 消息层码流长度及uper码流
 * @param[in/out] pstruWjMsg -- 应用层结构体
 *
 * @return true/false             成功/失败
 *
 */
extern DLL_PUBLIC int32_t WJV3_UperEncOrDecMain(WJV3_UperData *pstruUperData, WJV3_STRU_MessageFrame *pstruWjMsg, WJV3_ENUM_InterFace InterFace);

/*三跨消息集接口*/
typedef int32_t (*WJV3_UperFromFileEncodeMain_BACK)(WJV3_UperData *pstruUperData, char *pn8FileName, int *pn32MsgAid);
typedef int32_t (*WJV3_UperEncOrDecMain_BACK)(WJV3_UperData *pstruUperData, WJV3_STRU_MessageFrame *pstruWjMsg, WJV3_ENUM_InterFace InterFace);
typedef void (*WJV3_SetGetAIDFromFileCallback)(int (*pFunGetAid)(void *pstruMsg));
#define WJV3_MessageFrame_PR_bsmFrame_NO 1
#define WJV3_MessageFrame_PR_mapFrame_NO 2
#define WJV3_MessageFrame_PR_rsmFrame_NO 3
#define WJV3_MessageFrame_PR_spatFrame_NO 4
#define WJV3_MessageFrame_PR_rsiFrame_NO 5
#define WJV3_MessageFrame_PR_TOTALNUM 5
#endif