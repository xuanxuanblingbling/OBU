<!--
 * @Descripttion: 
 * @version: 
 * @Author: wanji.net.cn
 * @email: mk_wanji@126.com
 * @Date: 2021-12-03 08:37:59
 * @LastEditors: VanJee Technology Co.,Ltd
 * @LastEditTime: 2021-12-03 08:37:59
-->
#通州公路院Net模块，功能（1）将10帧和11帧通过UDP上传至万集孪生平台，其中10帧增加事件戳和GPS定位状态，11帧增加了ueid；（2）将OBU状态信息（静态信息、运行状态信息、场景信息等）通过MQTT上传至万集孪生平台，数据内容采用protobuf。

所需配置文件：1、Config_MQTTInfo.ini(此文件为MQTT的配置文件，包括MQTT服务器地址等)；2、NetConfig.json(此文件为UDP配置文件)
上述两个配置文件的路径为：/mnt/APP/Config/obu/net/

1、OBU统计信息上报由V2X通过共享内存和NET进行数据交互，V2X创建共享内存发送OBU统计信息的判断条件为：引用状态监控，即协议栈配置文件;是否引用状态监控（0不使用，1使用）置为1

2、OBU自身静态信息上报（上线时上报一次）其中：固件版本号、应用程序版本、车牌号、设备SN、车辆类型全部在/mnt/APP/Config/obu/net/Config_OBUInfo.ini中获取

3、OBU设备实时状态信息，其中：车辆ID、车辆经纬度、海拔、航向角和速度、车辆类型、GNSS状态从DBUS上获取VDS的车辆数据。其中车辆所属车道ID和车辆所在地图本地节点ID通过DBUS获取APP的匹配数据；

4、OBU运行状态信息从/mnt/APP/Config/obu/sysm/DynamicInfo/DynamicInfo.json中获取
