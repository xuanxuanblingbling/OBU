# Compile for arm architecture
ARCH ?= arm
export ARCH

ROOTDIR ?= $(abspath ..)

# APP dir
APP_STACK_DIR = $(ROOTDIR)/Protocol_Stack
SAFETYCERT_DIR= $(ROOTDIR)
#SOURCES := 
UTILS_SRC = $(shell find . -maxdepth 5 -name *.c)
UTILS_CPP = $(shell find . -maxdepth 5 -name *.cpp)
UTILS_CPP += $($(ROOTDIR)/Common/TestLog/src/*.cpp)
C_SRCS += $(wildcard $(UTILS_SRC))
CXX_SRCS += $(wildcard $(UTILS_CPP))

################################################################################
TARGET = V2X_APP.bin

# EXTRA_CFLAGS
EXTRA_CFLAGS += -I${APP_STACK_DIR}
#协议栈头消息层头文件
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface/include
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface/include/MsgLayerV2
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface/include/MsgLayerV3
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface/include/MsgLayerV4
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface/include/MsgLayerVN4
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface/include/NetLayer
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface/include/AppLayer
EXTRA_CFLAGS += -I${APP_STACK_DIR}/Stack_Lib/Interface/include/SecLayer
#协议栈头接入层头文件
EXTRA_CFLAGS += -I${APP_STACK_DIR}/V2XUtil/Intf
#协议栈头安全层头文件
EXTRA_CFLAGS += -I${APP_STACK_DIR}/SecLayer/Intf

EXTRA_CFLAGS += -I$(ROOTDIR)/Common/RsuLog/if
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/Misc/if
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/Utils/inc
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/Libraries/inc/iwall/
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/Functions/inc
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/Functions/if
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/TestLog/if
EXTRA_CFLAGS += -I$(ROOTDIR)/APP/DBus/inc
EXTRA_CFLAGS += -I$(ROOTDIR)/APP/IPC/inc
EXTRA_CFLAGS += -I$(ROOTDIR)/APP/V2XService/inc

# EXTRA_CFLAGS
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
# DIR_LIBS = ./lib/imx6
else ifeq ($(IMX),imx8)
CROSS_SYSROOT_USR_DIR = /opt/fsl-imx-xwayland/4.14-sumo/sysroots/aarch64-poky-linux/usr
# DIR_LIBS = ./lib/imx8
endif

CROSS_USR_HEAD_POREFIX= $(CROSS_SYSROOT_USR_DIR)/include
CROSS_GIB_LIB_HEAD = $(CROSS_SYSROOT_USR_DIR)/lib/glib-2.0/include

EXTRA_CFLAGS +=  -I $(CROSS_USR_HEAD_POREFIX)/glib-2.0  \
				 -I $(CROSS_USR_HEAD_POREFIX)/gio-unix-2.0 \
				 -I ${CROSS_USR_HEAD_POREFIX}/dbus-1.0 \
			     -I $(CROSS_USR_HEAD_POREFIX)/glib-2.0/glib \
			     -I $(CROSS_GIB_LIB_HEAD)

# LDFLAGS (find the libs)
#链接协议栈动态库
LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lMsgLayerV2
LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lMsgLayerV3
LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lMsgLayerV4
LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lMsgLayerVN4
LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lSecLayer
LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lStackDev
# LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lv2xutil
LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lv2xAG15
# LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -liwallV4_1
# LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -liwall_v2x_api
# LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -liwall_v2x
# LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lxdja_vn4
# LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lsdpf
# LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lssf
# LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lxdjakey
LDFLAGS += -lv2x_radio -lv2x_radio -lcv2x-kinematics

LDFLAGS += -L$(ROOTDIR)/Common/Utils/lib -lapputils
LDFLAGS += -L$(ROOTDIR)/Common/RsuLog/lib -llog
LDFLAGS += -L$(ROOTDIR)/Common/Functions/lib -lfunctions
LDFLAGS += -L$(ROOTDIR)/Common/TestLog/lib -ltestlog


LDFLAGS += -ldbus-glib-1 -ldbus-1 -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -pthread -lrt -lm -lstdc++

# OBJS
C_OBJS = ${C_SRCS:.c=.o}
CXX_OBJS = ${CXX_SRCS:.cpp=.o}
################################################################################
# Build Rules
################################################################################

all: $(TARGET)

${TARGET}: ${C_OBJS} ${CXX_OBJS}
	${CC} -g ${C_OBJS} ${CXX_OBJS} -o ${TARGET}  ${EXTRA_CFLAGS} ${LDFLAGS}

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) -g  $(EXTRA_CFLAGS) -o $@ -c $< 

${CXX_OBJS}:%.o:%.cpp
	${CXX} -g -std=c++14 -Wall ${EXTRA_CFLAGS} -c $< -o $@ 

.PHONY: clean
clean:
	rm -f ${C_OBJS} ${CXX_OBJS} ${TARGET}
