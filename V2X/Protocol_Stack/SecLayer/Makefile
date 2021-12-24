#################################################################
#                     PRIVATE PART                              #
#################################################################

APP_SEC_DIR = .
# 头文件目录
INC_CFLAGS += -I $(APP_SEC_DIR)/Inc
INC_CFLAGS += -I $(APP_SEC_DIR)/Intf
INC_CFLAGS += -I $(APP_SEC_DIR)/Common/Tools/Intf
INC_CFLAGS += -I $(APP_SEC_DIR)/log/if/
INC_CFLAGS += -I $(APP_SEC_DIR)/log/inc/

# 对外接口目录
# log
INC_CFLAGS += -I $(APP_SEC_DIR)./Stack_Lib/Interface/include/LogLayer
# SecDataInfo.h
INC_CFLAGS += -I $(APP_SEC_DIR)./Stack_Lib/Interface/include/SecLayer

# 源文件
SRC_SECLAYER_PATH += $(APP_SEC_DIR)/Src/*.c
SRC_SECLAYER_PATH += $(APP_SEC_DIR)/Common/Tools/Src/*.c
SRC_SECLAYER_PATH += $(APP_SEC_DIR)/log/src/*.c

#目标文件
C_OBJ_SECLAYER += $(patsubst %.c,%.o,$(wildcard $(SRC_SECLAYER_PATH)))

###########################使用C标志##############################
CFLAGS += -c
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -fPIC
CFLAGS += -O2
CFLAGS += -shared
# CFLAGS += -D_HUANGSAI_
############################ 动态链接############################
LD_FLAGS += -lpthread -lstdc++ -ldl
############################ SDK动态链接链接############################
TARGET = $(APP_SEC_DIR)/Lib/libSecLayer.so  
all:$(TARGET)
$(TARGET):$(C_OBJ_SECLAYER) 
	$(CC) $^ -shared -o $@ $(LD_FLAGS)
$(C_OBJ_SECLAYER):%.o:%.c
	$(CC) $(CFLAGS) $(INC_CFLAGS) $< -o $@

clean:
	-rm -f $(TARGET)
	-rm -f $(C_OBJ_SECLAYER)
	@echo "end to clean"












