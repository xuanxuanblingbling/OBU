#############################################################
#                         TSP MakeFile                      #
#############################################################
CURRENT_DIR = ./
DIR_INC = ./include
DIR_CURLINC = ./include/curl
SRC_UTILS = ./src/utils
DIR_INI = ./src/ReadIniFile

TARGET = TSP
BIN_TARGET = ${CURRENT_DIR}${TARGET}

CFLAGS = -c
LIBS += -ldbus-glib-1 -ldbus-1 -lglib-2.0 -pthread -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lcurl -lssl -lcrypto -lrt
LIBS += -lwebsockets -llog

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
				-I ${DIR_CURLINC}			 \
				-I ${SRC_UTILS}			     \
				-I ${DIR_LIBS}			     \
				-I $(CROSS_USR_HEAD_POREFIX)/glib-2.0  \
				-I $(CROSS_USR_HEAD_POREFIX)/gio-unix-2.0 \
				-I ${CROSS_USR_HEAD_POREFIX}/dbus-1.0 \
				-I $(CROSS_USR_HEAD_POREFIX)/glib-2.0/glib \
				-I $(CROSS_GIB_LIB_HEAD) \
				

EXTRA_CFLAGS += -I $(DIR_INI) \
				
LDFLAGS += -L $(DIR_LIBS) $(LIBS)

SRC_DIR=${shell find ${CURRENT_DIR} -maxdepth 10 -type d}
SRC = $(foreach dir,${SRC_DIR},$(wildcard $(dir)/*.c)) 
OBJ = $(patsubst %.c,%.o,${SRC})
${BIN_TARGET}:dir_check ${OBJ}
	$(CC) $(OBJ) -o $@ $(LDFLAGS)
    
${OBJ}:%.o:%.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(INC_CFLAGS) -c $< -o $@ $(CFLAGS)

dir_check:
	@test -d ./obj || mkdir -p ./obj

.PHONY:clean
clean:
	rm -rf $(OBJ) $(BIN_TARGET) ./obj/*

