#################################################################
#                     PRIVATE PART                              #
#################################################################
APP_STACK_DIR = ./../..
# 消息层二期目录
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/MsgFrameV2
# 对外接口目录
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/LogLayer
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/MsgLayerV2
# 源文件
CSRC += $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/MsgFrameV2/*.c
CSRC += $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/Src/*.c
C_OBJS += $(patsubst %.c,%.o,$(wildcard $(CSRC)))
# 动态库编译标志
DEBUG = y
ifeq ($(DEBUG),y)
DEBUG_CFLAGS += -DDEBUG
DEBUG_CFLAGS += -g
endif
CFLAGS += -c
CFLAGS += -Os
CFLAGS += -Wall
CFLAGS += -fPIC
CFLAGS += -fvisibility=hidden
CFLAGS += $(DEBUG_CFLAGS)
# 目标文件

Target_Lib=$(APP_STACK_DIR)/Lib/libMsgLayerV2.a
Target_Dll=$(APP_STACK_DIR)/Lib/libMsgLayerV2.so
TARGET = $(Target_Lib) $(Target_Dll)
# 编译规则
all:$(TARGET)
$(Target_Lib):$(C_OBJS)
	$(AR) rcs $@ $^
	@echo -e "\n>>>>> Compiling V2*$(Target_Lib)* sucessfully ended\n"
$(Target_Dll):$(C_OBJS)
	$(CC) -shared $^ -o $@
	@echo -e "\n>>>>> Compiling V2*$(Target_Dll)* sucessfully ended\n"
$(C_OBJS):%.o:%.c
	$(CC) $(CFLAGS) $(INC_CFLAGS) $< -o $@
.PHONY:all clean
clean:
	-rm -f $(C_OBJS)
	-rm -f $(TARGET)
