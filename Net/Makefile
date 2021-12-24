#设置当前路径
CUR_PATH = .
#递归若干层的路径
DIRS = $(shell find $(CUR_PATH) -maxdepth 5 -type d)
#递归找到所有与规则匹配的文件
SRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
CSRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))


ifeq ($(CROSS_COMPILE),aarch64-fslc-linux-)
	# @echo "交叉编译目标为imx8q"
	IMX = imx8
else ifeq ($(CROSS_COMPILE),aarch64-poky-linux-) 
	# @echo "交叉编译目标为imx8m"
	IMX = imx8
else ifeq ($(CROSS_COMPILE),arm-fslc-linux-gnueabi-) 
	# @echo "交叉编译目标为imx6q"
	IMX = imx6
else
	# @echo "交叉编译目标为x86-64"
	# CC=gcc
endif

ifeq ($(IMX),imx6)
CROSS_SYSROOT_USR_DIR= /opt/fslc-framebuffer/2.4.4/sysroots/armv7at2hf-neon-fslc-linux-gnueabi/usr
DIR_LIBS = ./lib/imx6
else ifeq ($(IMX),imx8)
CROSS_SYSROOT_USR_DIR = /opt/fsl-imx-xwayland/4.14-sumo/sysroots/aarch64-poky-linux/usr
DIR_LIBS = ./lib/imx8
endif

DIR_LIB =-I./lib
EXTERN_INC=-I./include -I./include/Curvefit -I./include/Nanoflann -I./include/json -I.
#GIB_INC=-I./include/glib-dbus/liunx/include/gio-unix-2.0 -I./include/glib-dbus/liunx/include/glib-2.0 -I./include/glib-dbus/liunx/lib/glib-2.0/include -I./include/glib-dbus/liunx/#include -I./include/glib-dbus/liunx/include/libmount
DBUS_INC=-I./include/dbus -I./include/glib-dbus/liunx/include/dbus-1.0 -I./include/glib-dbus/liunx/lib/dbus-1.0/include



CROSS_USR_HEAD_POREFIX= $(CROSS_SYSROOT_USR_DIR)/include
CROSS_GIB_LIB_HEAD = $(CROSS_SYSROOT_USR_DIR)/lib/glib-2.0/include
EXTRA_CFLAGS += -I $(CROSS_USR_HEAD_POREFIX)/glib-2.0  \
		-I $(CROSS_USR_HEAD_POREFIX)/gio-unix-2.0 \
		-I ${CROSS_USR_HEAD_POREFIX}/dbus-1.0 \
		-I $(CROSS_USR_HEAD_POREFIX)/glib-2.0/glib \
		-I $(CROSS_GIB_LIB_HEAD) \


GIB_LIBS = -lgmodule-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lmount  -lz -lffi
DBUS_LIBS = -ldbus-1 -lexpat

CFLAGS = -O2 -pipe -feliminate-unused-debug-types
CFLAGS += -DDBUS_COMPILATION -DHAVE_CONFIG_H
#-DMG_ENABLE_SSL  -g
CFLAGS += -L./include/glib-dbus/include/lib -I./Extern


#两种改变变量后缀的方法
OBJS = ${SRC:%.cpp=%.o}
COBJS = ${CSRC:.c=.o}

INC= $(EXTRA_CFLAGS) $(DBUS_INC) $(EXTERN_INC)
LIBS += $(DBUS_LIBS) $(GIB_LIBS) $(SIGCPP_LIBS) -ldl -pthread 
LIBS += -L $(DIR_LIBS)/libprotobuf/ -lprotobuf-c
LIBS += -L $(DIR_LIBS)/paho_mqtt/ -lpaho-mqtt3a
LIBS += -L $(DIR_LIBS) -llog 

all: ${OBJS} ${COBJS}
	$(CXX) $(CFLAGS) $(INC) -std=c++17 -Wall $^ -o NET_ARM.bin $(LIBS)
	
	#编译所有源文件
${OBJS}:%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -std=c++17 -Wall -c $< -o $@ $(LIBS)

${COBJS}:%.o:%.c
	$(CC) $(CFLAGS) $(INC) -std=c11 -Wall -c $< -o $@ $(LIBS)
	

.PHONY: clean test
clean:
	rm -rf ${OBJS} test ${COBJS}
	rm -rf $(CUR_PATH)/NET_ARM.bin

test:
	@echo "test print---------------"
	@echo "OBJS:" ${OBJS}
	@echo "test print over----------
