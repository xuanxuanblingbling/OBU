#################################################################
#                     PRIVATE PART                              #
#################################################################

ifeq ($(CROSS_COMPILE),aarch64-fslc-linux-)
	# @echo "交叉编译目标为imx6q"
	IMX = imx8
	
else ifeq ($(CROSS_COMPILE),aarch64-poky-linux-) 
	# @echo "交叉编译目标为imx8m"
	IMX = imx8

else ifeq ($(CROSS_COMPILE),arm-fslc-linux-gnueabi-) 
	# @echo "交叉编译目标为imx8q"
	IMX = imx6

else
	# @echo "交叉编译目标为x86-64"
	# CC=gcc
endif

# 动态链接

APP_SEC_DIR = .

# 头文件
INC_CFLAGS_IWALLF = -I $(APP_SEC_DIR)/inc/iwallF/
INC_CFLAGS_IWALLNEWF = -I $(APP_SEC_DIR)/inc/iwallNewF/
INC_CFLAGS_XDJA = -I $(APP_SEC_DIR)/inc/xdja/
INC_CFLAGS_OFFLINE = -I $(APP_SEC_DIR)/inc/xdjaoffline/
INC_CFLAGS_SECFRAMEV4 = -I $(APP_SEC_DIR)/src/iwallF/SecFrameV4/
INC_CFLAGS_SECFRAMEVN4 = -I $(APP_SEC_DIR)/src/iwallNewF/SecFrameVN4/
INC_CFLAGS_LOG += -I $(APP_SEC_DIR)/log/if/
INC_CFLAGS_LOG += -I $(APP_SEC_DIR)/log/inc/
INC_CFLAGS_GLIB += -I $(APP_SEC_DIR)/inc/glib-2.0
INC_CFLAGS_PUB += -I $(APP_SEC_DIR)/inc/
INC_CFLAGS_TOOL = -I $(APP_SEC_DIR)/Tools/Intf/

#源文件
SRC_IWALLF_PATH = $(APP_SEC_DIR)/src/iwallF/*.c
SRC_IWALLNewF_PATH = $(APP_SEC_DIR)/src/iwallNewF/*.c
SRC_XDJA_PATH = $(APP_SEC_DIR)/src/xdjaNewF/*.c
SRC_XDJA_OFFLINE_PATH = $(APP_SEC_DIR)/src/xdjaOffLineNewF/*.c
SRC_SECFRAMEV4_PATH = $(APP_SEC_DIR)/src/iwallF/SecFrameV4/*.c
SRC_SECFRAMEVN4_PATH = $(APP_SEC_DIR)/src/iwallNewF/SecFrameVN4/*.c
# SRC_LOG_PATH = $(APP_SEC_DIR)/log/src/*.c
SRC_TOOL_PATH = $(APP_SEC_DIR)/Tools/Src/*.c

#目标文件
C_OBJSVF_IWALL += $(patsubst %.c,%.o,$(wildcard $(SRC_IWALLF_PATH)))
C_OBJSVF_IWALL += $(patsubst %.c,%.o,$(wildcard $(SRC_SECFRAMEV4_PATH)))
C_OBJSVF_IWALL += $(patsubst %.c,%.o,$(wildcard $(SRC_TOOL_PATH)))
C_OBJSVF_IWALL += $(patsubst %.c,%.o,$(wildcard $(SRC_LOG_PATH)))

C_OBJSVNEWF_IWALL += $(patsubst %.c,%.o,$(wildcard $(SRC_IWALLNewF_PATH)))
C_OBJSVNEWF_IWALL += $(patsubst %.c,%.o,$(wildcard $(SRC_SECFRAMEVN4_PATH)))
C_OBJSVNEWF_IWALL += $(patsubst %.c,%.o,$(wildcard $(SRC_TOOL_PATH)))
C_OBJSVNEWF_IWALL += $(patsubst %.c,%.o,$(wildcard $(SRC_LOG_PATH)))

C_OBJSVNEWF_XDJA += $(patsubst %.c,%.o,$(wildcard $(SRC_XDJA_PATH)))
C_OBJSVNEWF_XDJA += $(patsubst %.c,%.o,$(wildcard $(SRC_TOOL_PATH)))
C_OBJSVNEWF_XDJA += $(patsubst %.c,%.o,$(wildcard $(SRC_LOG_PATH)))

C_OBJSVNEWF_XDJA_OFFLINE += $(patsubst %.c,%.o,$(wildcard $(SRC_XDJA_OFFLINE_PATH)))
C_OBJSVNEWF_XDJA_OFFLINE += $(patsubst %.c,%.o,$(wildcard $(SRC_TOOL_PATH)))
C_OBJSVNEWF_XDJA_OFFLINE += $(patsubst %.c,%.o,$(wildcard $(SRC_LOG_PATH)))

###########################使用C标志##############################
CFLAGS += -c
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -fPIC
CFLAGS += -O2
CFLAGS += -shared
# CFLAGS += -D_HUANGSAI_
############################ 动态链接链接############################
LD_FLAGS += -lpthread -lm -lstdc++ -lglib-2.0 -lrt
############################ SDK动态链接链接############################
#8q 不使用 iwall sdk   
LD_FLAGS_SDKIWALL_F += -L $(APP_SEC_DIR)./Lib/iwallSDK/ -liwall_v2x_api -liwall_v2x

LD_FLAGS_SDKIWALL_NEWF += -L $(APP_SEC_DIR)./Lib/iwallSDK/ -liwall_v2xsecurity_api -liwall_v2x

#在线xdja sdk 仅支持新四跨
LD_FLAGS_SDKXDJA_NEWF += -L$(APP_SEC_DIR)./Lib/xdjaSDK/$(IMX)/ -lsdpf
# LD_FLAGS_SDKXDJA_NEWF += -L$(APP_SEC_DIR)/lib/xdjaSDK/$(IMX)/ -lssf
# LD_FLAGS_SDKXDJA_NEWF += -L$(APP_SEC_DIR)/lib/xdjaSDK/$(IMX)/ -lxdjakey

#离线xdja sdk 仅支持新四跨
LD_FLAGS_SDKXDJA_OFFLINE_NEWF += -L$(APP_SEC_DIR)./Lib/xdjaOffLineSDK/$(IMX)/ -ldatasec
# LD_FLAGS_SDKXDJA_NEWF += -L$(APP_SEC_DIR)/lib/xdjaSDK/$(IMX)/ -lssf
# LD_FLAGS_SDKXDJA_NEWF += -L$(APP_SEC_DIR)/lib/xdjaSDK/$(IMX)/ -lxdjakey

TARGET1 = $(APP_SEC_DIR)./Lib/SecDllOpen/libiwall_f.so
TARGET2 = $(APP_SEC_DIR)./Lib/SecDllOpen/libiwall_newf.so
TARGET3 = $(APP_SEC_DIR)./Lib/SecDllOpen/libxdja_newf.so
TARGET4 = $(APP_SEC_DIR)./Lib/SecDllOpen/libxdja_offline.so

ifeq ($(IMX),imx6)
	TARGET = $(TARGET1) $(TARGET2) $(TARGET3)  $(TARGET4)
else 
	TARGET = $(TARGET3)  $(TARGET4)
endif

# TARGET =  $(TARGET2) $(TARGET3)  
all:$(TARGET)
ifeq ($(IMX),imx6)
$(TARGET1):$(C_OBJSVF_IWALL) 
	 $(CC) $^ -shared -o $@  $(LD_FLAGS_SDKIWALL_F) $(LD_FLAGS)
$(TARGET2):$(C_OBJSVNEWF_IWALL) 
	$(CC) $^ -shared -o $@   $(LD_FLAGS) $(LD_FLAGS_SDKIWALL_NEWF)
$(TARGET3):$(C_OBJSVNEWF_XDJA) 
	$(CC) $^ -shared -o $@  $(LD_FLAGS_SDKXDJA_NEWF) $(LD_FLAGS)
$(TARGET4):$(C_OBJSVNEWF_XDJA_OFFLINE) 
	$(CC) $^ -shared -o $@  $(LD_FLAGS_SDKXDJA_OFFLINE_NEWF) $(LD_FLAGS)
else 
$(TARGET3):$(C_OBJSVNEWF_XDJA) 
	$(CC) $^ -shared -o $@  $(LD_FLAGS_SDKXDJA_NEWF) $(LD_FLAGS)
$(TARGET4):$(C_OBJSVNEWF_XDJA_OFFLINE) 
	$(CC) $^ -shared -o $@  $(LD_FLAGS_SDKXDJA_OFFLINE_NEWF) $(LD_FLAGS)
endif


$(C_OBJSVF_IWALL):%.o:%.c
	 $(CC) $(CFLAGS) $(INC_CFLAGS_SECFRAMEV4) $(INC_CFLAGS_IWALLF) $(INC_CFLAGS_TOOL) $(INC_CFLAGS_LOG) $(INC_CFLAGS_GLIB) $(INC_CFLAGS_PUB) $< -o $@
$(C_OBJSVNEWF_IWALL):%.o:%.c
	$(CC) $(CFLAGS)  $(INC_CFLAGS_SECFRAMEVN4) $(INC_CFLAGS_IWALLNEWF) $(INC_CFLAGS_TOOL) $(INC_CFLAGS_LOG) $(INC_CFLAGS_GLIB) $(INC_CFLAGS_PUB) $< -o $@
$(C_OBJSVNEWF_XDJA):%.o:%.c
	$(CC) $(CFLAGS)  $(INC_CFLAGS_XDJA) $(INC_CFLAGS_TOOL) $(INC_CFLAGS_LOG)  $(INC_CFLAGS_PUB) $< -o $@
$(C_OBJSVNEWF_XDJA_OFFLINE):%.o:%.c
	$(CC) $(CFLAGS)  $(INC_CFLAGS_OFFLINE) $(INC_CFLAGS_TOOL) $(INC_CFLAGS_LOG)  $(INC_CFLAGS_PUB) $< -o $@

.PHONY:all clean
clean:
	-rm -f $(C_OBJSVF_IWALL)
	-rm -f $(C_OBJSVNEWF_IWALL)
	-rm -f $(C_OBJSVNEWF_XDJA)
	-rm -f $(C_OBJSVNEWF_XDJA_OFFLINE)
	-rm -f $(TARGET)
	@echo "end to clean"


