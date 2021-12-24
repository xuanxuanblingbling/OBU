#ifndef RSU_CONFIG_H
#define RSU_CONFIG_H

#define VDS_CONFIG_FILE_NAME    "/mnt/APP/Config/obu/vds/VDSCfg.json"   /*车辆静态信息json配置文件名称*/
#define MCU_CONFIG_FILE_NAME    "/mnt/APP/Config/obu/vds/MCUCfg.json"   /*MCU在线配置json配置文件名称*/

#define PERI_CHECK_PERIOD   (5) /*外围模块检测周期，单位：秒*/

#define PING_FRAME_NUM  (25)

#define USB_DEST_DIR   "./log"
#define TF_DEST_DIR    "./log"

#define SCRIPTS_DIR     "./scripts/"

#endif
