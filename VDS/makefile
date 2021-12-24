
############ 本工程中CAN模块和 GPS模块需要单独编译为 .so文件  libcan.so libgpsinterface.so libgpsutil.so      ########################
###########  另外GPS模块还要依赖 libqxwz-pssdk.so文件   需要单独执行 ./src/CAN_Model/makefile  和 .src/GPSInterface/Makefile    #####
DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = .
CURRENT_DIR = ./
SRC_DBUS = ./src/dbus
SRC_EDCODE = ./src/edcode
SRC_GNSS = ./src/mcu
SRC_MCU = ./src/gnss
SRC_UTILS = ./src/utils
SRC_GPS = ./src/GPSInterface/GPSUtil



#
SRC_DIR=${shell find ${CURRENT_DIR} -maxdepth 10 -type d}
#
SRC = $(foreach dir,${SRC_DIR},$(wildcard $(dir)/*.c))

OBJ = $(patsubst %.c,%.o,${SRC})
#########
TARGET = vds
BIN_TARGET = ${DIR_BIN}/${TARGET}
#########################
CFLAGS = -c
LIBS +=  -ldbus-glib-1 -ldbus-1 -lglib-2.0 -pthread -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lm

########GPS lib#################
#LIBS += -lgpsinterface -lgpsutil -lqxwz-pssdk 

########CAN lib#################
#LIBS +=-L ./src/CAN_Model  -lcan



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

CROSS_USR_HEAD_POREFIX= $(CROSS_SYSROOT_USR_DIR)/include
CROSS_GIB_LIB_HEAD = $(CROSS_SYSROOT_USR_DIR)/lib/glib-2.0/include
EXTRA_CFLAGS += -I ${DIR_INC}			     \
				-I ${SRC_DBUS} 			     \
				-I ${SRC_EDCODE} 		     \
				-I ${SRC_GNSS} 			     \
				-I ${SRC_MCU} 			     \
				-I ${SRC_UTILS}			     \
				-I $(CROSS_USR_HEAD_POREFIX)/glib-2.0  \
				-I $(CROSS_USR_HEAD_POREFIX)/gio-unix-2.0 \
				-I ${CROSS_USR_HEAD_POREFIX}/dbus-1.0 \
				-I $(CROSS_USR_HEAD_POREFIX)/glib-2.0/glib \
				-I $(CROSS_GIB_LIB_HEAD) \
				-I $(SRC_GPS) \
				-I $(DIR_SRC)/GPSInterface \
				-I $(DIR_SRC)/GPSInterface/ConfUtil

EXTRA_CFLAGS += -I $(DIR_SRC)/CAN_Model/ReadIniFile 
				

LDFLAGS += -L $(DIR_LIBS) $(LIBS) -llog -lcv2x-kinematics -lqxwz-pssdk 


${BIN_TARGET}:dir_check ${OBJ}
	$(CC) $(OBJ) -o $@  $(LDFLAGS) $(LIBS)
    
${OBJ}:%.o:%.c 
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(INC_CFLAGS) -c $< -o $@ $(CFLAGS)

dir_check:
	@test -d ./obj || mkdir -p ./obj

.PHONY:clean
clean:
	make -C ./src/GPSInterface clean
	make -C ./src/CAN_Model clean
	rm -rf $(OBJ) $(BIN_TARGET) ./obj/*

