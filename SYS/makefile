TARGET = sysm
CUR_PATH = .
#获取所有c cpp h文件
DIRS = $(shell find $(CUR_PATH) -maxdepth 10 -type d)
SRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
CSRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

OBJS = ${SRC:%.cpp=%.o}
COBJS = ${CSRC:.c=.o}

#文件生成路径
BIN_TARGET = ${CUR_PATH}/${TARGET}

#编译工具链
ver = debug

#CC = aarch64-fslc-linux-gcc --sysroot=/opt/fslc-wayland/2.5.2/sysroots/aarch64-fslc-linux
#CXX = aarch64-fslc-linux-g++  --sysroot=/opt/fslc-wayland/2.5.2/sysroots/aarch64-fslc-linux
# CC = gcc
# CXX = g++
ARCH_CC = $(CC)
ARCH_CXX = $(CXX)


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
CROSSCOMPILE_6Q = 6Q
CROSSCOMPILE_FLAG = -D CROSSCOMPILE_6Q
else ifeq ($(IMX),imx8)
CROSS_SYSROOT_USR_DIR = /opt/fsl-imx-xwayland/4.14-sumo/sysroots/aarch64-poky-linux/usr
DIR_LIBS = ./lib/imx8
CROSSCOMPILE=8M
CROSSCOMPILE_FLAG = -D CROSSCOMPILE_8M
$(info ************  TEST VERSION 1************)
endif

#依赖库及头文件
CROSS_USR_HEAD_POREFIX= $(CROSS_SYSROOT_USR_DIR)/include
CROSS_GIB_LIB_HEAD = $(CROSS_SYSROOT_USR_DIR)/lib/glib-2.0/include
CFLAGS +=  -I $(CROSS_USR_HEAD_POREFIX)/glib-2.0  \
        -I $(CROSS_USR_HEAD_POREFIX)/gio-unix-2.0 \
        -I ${CROSS_USR_HEAD_POREFIX}/dbus-1.0 \
        -I $(CROSS_USR_HEAD_POREFIX)/glib-2.0/glib \
        -I $(CROSS_GIB_LIB_HEAD)
LDFLAGS += -ldbus-glib-1 -ldbus-1 -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -pthread -lrt -lm -lstdc++

CFLAGS += $(CROSSCOMPILE_FLAG) -DMG_ENABLE_HTTP_STREAMING_MULTIPART -DMG_ENABLE_CALLBACK_USERDATA -W -DNONUTF8CONV -DELPP_NO_DEFAULT_LOG_FILE '-Wno-implicit-fallthrough' 

LIBS += -L$(DIR_LIBS) -llog
LIBS += -lrt -lm -lpthread -ldl -D_GNU_SOURCE
LIBS += -lclocktime

INC += -I ./src/Cfg            \
-I ./src/CfgM            \
       -I ./src/DiagM 				\
       -I ./src/Log 				\
       -I ./src/MsgRcvSd			\
       -I ./src/PowerM 				\
       -I ./src/StateM 				\
       -I ./src/WebServerM/main 	\
       -I ./src/Cjson 	            \
       -I ./src/MsgMonitor 	            \
       -I ./src/LED              \


#PKGCFLAGS += `pkg-config --cflags dbus-glib-1 dbus-1 glib-2.0`
#PKGLIBS += `pkg-config --libs dbus-glib-1 dbus-1 glib-2.0`

ifeq ($(ver), debug)

all: ${OBJS} ${COBJS}
	$(CXX) $(CFLAGS) -g -std=c++14 -Wall $^ -o ${BIN_TARGET} $(LIBS) $(LDFLAGS)

#编译所有源文件
${OBJS}:%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -g -std=c++14 -Wall -c $< -o $@ $(LIBS) $(LDFLAGS)

${COBJS}:%.o:%.c
	$(CC) $(CFLAGS) $(INC) -fno-stack-protector -g -std=c11 -Wall -c $< -o $@ $(LIBS) $(LDFLAGS)
	
else
all: ${OBJS} ${COBJS}
	$(ARCH_CXX) $(CFLAGS) $(INC) -std=c++14 -Wall $^ -o ${BIN_TARGET} $(LIBS)
	
#编译所有源文件
${DIR_OBJ}:%.o:%.cpp
	$(ARCH_CXX) $(CFLAGS) $(INC) -std=c++14 -Wall -c $< -o $@

${DIR_OBJ}:%.o:%.c
	$(ARCH_CC) $(INC) -std=c11 -Wall -c $< -o $@ 
	
endif

.PHONY: clean sysm
clean:
	rm -rf ${OBJS} ${COBJS} sysm Authen.json UserInfo.db ./logs
