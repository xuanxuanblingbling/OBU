#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general_config.h"
#include "cJSON.h"
#include "param_parse.h"
#include "file_operation.h"
#include "wj_log.h"

Tparam_veh_struct  g_param_veh_info;
Tparam_mcu_struct  g_param_mcu_info;
/*************************************************
  名称: Str2ByteA
  描述: 将字符串转换为字节数组
  输入参数:
  输出参数:
  返回值: 解析成功返回０，解析失败返回-1
**************************************************/
static int F_Str2ByteA(char *dst, char *str) 
{    
    char *data = NULL;
    unsigned char highByte,lowByte;

    int l_len = strlen(str);
    printf("VID string : %s \n",str);

    for(int i = 0; i<l_len; i += 2)
    {
        highByte = toupper(str[i]);
        lowByte = toupper(str[i+1]);
        
        if(highByte > 0x39){
            highByte -= 0x37;
        }
        else{
            highByte -= 0x30;
        }

        if(lowByte > 0x39){
            lowByte -= 0x37;
        }
        else{
            lowByte -= 0x30;
        }
        dst[i/2] = (highByte << 4)|lowByte;
        printf(" %02X ",dst[i/2]);
    }
    printf("\n");
    return l_len;
}
/*************************************************
  名称: ParseVehParam
  描述: 解析车辆静态配置信息
  输入参数:
  输出参数:
  返回值: 解析成功返回０，解析失败返回-1
**************************************************/
static int32_t ParseVehParam(cJSON *root, Tparam_veh_struct *param_info)
{
    cJSON *veh_info = NULL;
    int8_t *temp = NULL;
    float   l_value = 0;
    int32_t ret = PARAM_PARSE_FAILED;

    veh_info = cJSON_GetObjectItem(root, "VEH");
    if(NULL != veh_info)
    {
        //车辆类型
        param_info->veh.VehType = (BasicVehicleClass_en)(cJSON_GetObjectItem(veh_info, "VehType")->valueint);
        //长度
        temp = (int8_t *)cJSON_GetObjectItem(veh_info, "VehLength")->valuestring;
        param_info->veh.vehicleLength = atof(temp);
        //宽度
        temp = (int8_t *)cJSON_GetObjectItem(veh_info, "VehWidth")->valuestring;
        param_info->veh.vehicleWidth = atof(temp);
        //高度
        temp = (int8_t *)cJSON_GetObjectItem(veh_info, "VehHigh")->valuestring; 
        param_info->veh.vehicleHeight = atof(temp);
        //车辆id
        temp = (cJSON_GetObjectItem(veh_info, "VehId")->valuestring);
        if(strlen(temp)!=VEH_ID_SIZE)
        {
            LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"Invalid VehId");
            return PARAM_PARSE_FAILED;
        }
        F_Str2ByteA(param_info->veh.VehId,temp);
        //memcpy(param_info->veh.VehId,temp,strlen(temp));
        ret = PARAM_PARSE_SUCCESS;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"get v2x param failed");
    }
    return ret;
}
/*************************************************
  名称: ParseGnssParam
  描述: 获取gnss配置文件信息
  输入参数:
  输出参数:
  返回值:  解析成功返回０，解析失败返回-1
**************************************************/
static int32_t ParseGnssParam(cJSON *root, Tparam_veh_struct *param_info)
{
    cJSON *gnss_info = NULL;
    int32_t ret = PARAM_PARSE_FAILED;

    gnss_info = cJSON_GetObjectItem(root, "GNSS");
    if(NULL != gnss_info)
    {
        param_info->gnss.locationtype = (uint8_t)(cJSON_GetObjectItem(gnss_info, "RtcmFlag")->valueint);
        return PARAM_PARSE_SUCCESS;
    }
    else
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"get pc net param failed");
        return PARAM_PARSE_FAILED;
    } 
}
/*************************************************
  名称: param_qxwz_parse
  描述: AG35在线配置文件解析
  输入参数:
  输出参数:
  返回值:  
**************************************************/
static int32_t ParseQxwzParam(cJSON *root, Tparam_veh_struct *param_info)
{
    cJSON *qxwz_info = NULL;
    int8_t *temp = NULL;
    int32_t ret = PARAM_PARSE_FAILED;

    qxwz_info = cJSON_GetObjectItem(root, "QXWZ");
    if (NULL == qxwz_info)
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"qxwz: get pc net param failed");
        return PARAM_PARSE_FAILED;
    }
    //获取Ak
    temp = (int8_t *)cJSON_GetObjectItem(qxwz_info, "AK")->valuestring;
    if(strlen(temp)!=QXWZ_AK_SIZE)
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"qxwz AK len error");
    }
    memcpy(param_info->qxwz.QxwzAk,temp,QXWZ_AK_SIZE);
    //获取As
    temp = (int8_t *)cJSON_GetObjectItem(qxwz_info, "AS")->valuestring;
    if(strlen(temp)!=QXWZ_AS_SIZE)
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"qxwz AS len error");
    }
    memcpy(param_info->qxwz.QxwzAs,temp,QXWZ_AS_SIZE);

    return PARAM_PARSE_SUCCESS;
}
/*************************************************
  名称: param_veh_parse
  描述: 车身静态配置文件解析
  输入参数:
  输出参数:
  返回值:  
**************************************************/
int32_t param_veh_parse(const int8_t *config_file, Tparam_veh_struct *config)
{
    cJSON *root =  NULL;
    int8_t file_buf[1024] = {0};
    uint32_t file_content_size = 0;

    if(FILE_OPER_SUCCESS != file_read(config_file, file_buf, sizeof(file_buf), &file_content_size))
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"read config file %s failed", config_file);
        return PARAM_PARSE_FAILED;
    }

    if (0 == file_content_size)
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"%s file is empty", config_file);
        return PARAM_PARSE_FAILED;
    }

    root = cJSON_Parse(file_buf);
    if (NULL == root)
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"json parse failed");
        return PARAM_PARSE_FAILED;
    }

    memset(config, 0, sizeof(Tparam_veh_struct));
    //veh
    if(PARAM_PARSE_SUCCESS != ParseVehParam(root, config))
    {
        goto EXIT;
    }
    //gnss
    if(PARAM_PARSE_SUCCESS != ParseGnssParam(root, config))
    {
        goto EXIT;
    }
    //qxwz
    if(PARAM_PARSE_SUCCESS != ParseQxwzParam(root, config))
    {
        goto EXIT;
    }

    cJSON_Delete(root);
            
    return PARAM_PARSE_SUCCESS;

EXIT:
    
    cJSON_Delete(root);   
    return PARAM_PARSE_FAILED;
}
/*************************************************
  名称: param_mcu_parse
  描述: MCU在线配置文件解析
  输入参数:
  输出参数:
  返回值:  
**************************************************/
int32_t param_mcu_parse(const int8_t *config_file, Tparam_mcu_struct *config)
{
    cJSON *root =  NULL;
    int8_t *temp = NULL;
    int8_t file_buf[512] = {0};
    uint32_t file_content_size = 0;

    if(FILE_OPER_SUCCESS != file_read(config_file, file_buf, sizeof(file_buf), &file_content_size))
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"read config file %s failed", config_file);
        return PARAM_PARSE_FAILED;
    }

    if (0 == file_content_size)
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"%s file is empty", config_file);
        return PARAM_PARSE_FAILED;
    }

    root = cJSON_Parse(file_buf);
    if (NULL == root)
    {
        LogPrint(LOG_LEVEL_ERR,MODULE_NAME,"json parse failed");
        return PARAM_PARSE_FAILED;
    }

    memset(config, 0, sizeof(Tparam_mcu_struct));

    config->PwrUpDlyTime = (uint32_t)(cJSON_GetObjectItem(root, "PwrUpDlyTime")->valueint);
    config->PwrUpDlyTimeStorFlag = (uint8_t)(cJSON_GetObjectItem(root, "PwrUpDlyTimeFlag")->valueint);
    config->DiagDlyTime = (uint32_t)(cJSON_GetObjectItem(root, "DiagDlyTime")->valueint);
    config->DiagDlyTimeStorFlag = (uint8_t)(cJSON_GetObjectItem(root, "DiagDlyTimeFlag")->valueint);
    config->DiagVoltRangeL = (uint32_t)(cJSON_GetObjectItem(root, "DiagVoltRangeMin")->valueint);
    config->DiagVoltRangeLStorFlag = (uint8_t)(cJSON_GetObjectItem(root, "DiagVoltRangeMinFlag")->valueint);
    config->DiagVoltRangeH = (uint32_t)(cJSON_GetObjectItem(root, "DiagVoltRangeMax")->valueint);
    config->DiagVoltRangeHStorFlag = (uint8_t)(cJSON_GetObjectItem(root, "DiagVoltRangeMaxFlag")->valueint);
    config->DiagHystsVoltH = (uint32_t)(cJSON_GetObjectItem(root, "DiagHystsVoltUp")->valueint);
    config->DiagHystsVoltHStorFlag = (uint8_t)(cJSON_GetObjectItem(root, "DiagHystsVoltUpFlag")->valueint);
    config->DiagHystsVoltL = (uint32_t)(cJSON_GetObjectItem(root, "DiagHystsVoltDown")->valueint);
    config->DiagHystsVoltLStorFlag = (uint8_t)(cJSON_GetObjectItem(root, "DiagHystsVoltDownFlag")->valueint);

    cJSON_Delete(root);  
    return PARAM_PARSE_SUCCESS;
EXIT:
    
    cJSON_Delete(root);   
    return PARAM_PARSE_FAILED;
}
