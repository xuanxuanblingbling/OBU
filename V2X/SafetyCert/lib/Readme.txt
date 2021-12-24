编译：
1. Common\Libraries\ 目录下的 libglib-2.0.so 和 libpcre.so.1 这两个库文件在系统中已经存在，无需单独拷贝到系统中，只需拷贝libiwall_v2x_api.so 和 libiwall_v2x.so。
2. libcert-manager.so 使用了liblog.so。

执行
1. 新长城安全芯片需要将 IwallStrategy.ini文件放在固定目录—— /usr/local/config/，因此需要手动创建该目录，并将该文件拷贝到目录中。
2. 将 certs/ 目录拷贝到 /mnt/APP/Config/ 目录下。