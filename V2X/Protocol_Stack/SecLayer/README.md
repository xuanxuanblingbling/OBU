
安全层版本迭代

20201104  添加是否初始化安全层；添加错误与成功日志高亮显示

6q编译方式为 ： make "imx=6"
8q编译方式为 ： make "imx=8"

version
1.1.0
1.更改加载方式。动态加载SecChiplib：libiwall_f libiwall_newf libxdja_newf libxdja_offline
2.增加信大捷安离线版本,修改配置文件EncryptChipType = 3 为调用离线版本SDK 
3.将芯片SDK 与编译的 libiwall_f libiwall_newf libxdja_newf libxdja_offline 拷贝到设备： /mnt/APP/Libraries/GeneralLibs/iwall/hard
4.将libSecLayer.so 拷贝到设备： /mnt/APP/Libraries/RSULibs