#################################################################
#                     PRIVATE PART                              #
#################################################################

APP_STACK_DIR = .
# 公共目录
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/Tools/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/Tools/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/RsuLog/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/RsuLog/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/ParamConfig/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/PreciseTiming/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/PreciseTiming/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/Common/StateMonitor/Intf
# 消息层二期场景消息集目录
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/MsgFrameV2
# 消息层4跨目录
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV4/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV4/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV4/MsgFrameV4
# 消息层3跨目录
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV3/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV3/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerV3/MsgFrameV3
# 消息层新4跨目录
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerVN4/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerVN4/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/MsgLayer/MsgLayerVN4/MsgFrameVN4
# 安全层目录
INC_CFLAGS += -I $(APP_STACK_DIR)/SecLayer/Intf
# 网络层目录
INC_CFLAGS += -I$(APP_STACK_DIR)/NetLayer/Inc
INC_CFLAGS += -I$(APP_STACK_DIR)/NetLayer/Intf
# 业务处理目录
INC_CFLAGS += -I $(APP_STACK_DIR)/BusinessProcess/Stack_Rx/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/BusinessProcess/Stack_Rx/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/BusinessProcess/Stack_Tx/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/BusinessProcess/Stack_Tx/Intf
INC_CFLAGS += -I $(APP_STACK_DIR)/BusinessProcess/TransparentTrasmit/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/BusinessProcess/TransparentTrasmit/Intf
# 对外接口目录
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/LogLayer
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/MsgLayerV2
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/MsgLayerV3
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/MsgLayerV4
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/MsgLayerVN4
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/NetLayer
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/AppLayer
INC_CFLAGS += -I $(APP_STACK_DIR)/Interface/include/SecLayer
# 动态链接库
# LDFLAGS += -L$(APP_STACK_DIR)/Lib -lMsgLayerV2
# LDFLAGS += -L$(APP_STACK_DIR)/Lib -lMsgLayerV4
# LDFLAGS += -L$(APP_STACK_DIR)/Lib -lMsgLayerV3
# LDFLAGS += -L$(APP_STACK_DIR)/Lib -lMsgLayerVN4
LDFLAGS += -lpthread -lm -lstdc++
LDFLAGS += -lrt
LDFLAGS += -fvisibility=hidden
# 动态链接条件编译
DEBUG = y
ifeq ($(DEBUG),y)
	DEBUG_CFLAGS := -O -g -DDEBUG
else
	DEBUG_CFLAGS := -O2
endif

CFLAGS := -Wall -fPIC -shared
CFLAGS += $(DEBUG_CFLAGS)

# 需要排除的目录
# ASN生成的c代码有3跨消息层MsgFrame，4跨消息层MsgFrame，以及安全层SecFrame，该三个目录存在重复定义的接口，所以此处排除目录
# 以下目录单独编译，生成动态库及静态库，生成libStackDev时，采用静态链接
exclude_dirs += $(APP_STACK_DIR)/MsgLayer/MsgLayerV4/MsgFrameV4
exclude_dirs += $(APP_STACK_DIR)/MsgLayer/MsgLayerV4/Src
exclude_dirs += $(APP_STACK_DIR)/MsgLayer/MsgLayerV3/MsgFrameV3
exclude_dirs += $(APP_STACK_DIR)/MsgLayer/MsgLayerV3/Src
exclude_dirs += $(APP_STACK_DIR)/MsgLayer/MsgLayerVN4/MsgFrameVN4
exclude_dirs += $(APP_STACK_DIR)/MsgLayer/MsgLayerVN4/Src
exclude_dirs += $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/MsgFrameV2
exclude_dirs += $(APP_STACK_DIR)/MsgLayer/MsgLayerV2/Src
exclude_dirs += $(APP_STACK_DIR)/Common/RsuLog/Src
DIRS := $(shell find $(APP_STACK_DIR) -maxdepth 5 -type d)
DIRS := $(filter-out $(exclude_dirs),$(DIRS))

CPPSRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
CSRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

CXX_OBJS = ${CPPSRC:%.cpp=%.o}
C_OBJS = ${CSRC:.c=.o}

LIB_PATH=$(APP_STACK_DIR)/Lib/
OBJ_DLL=libStackDev.so
DLL_PATHFILE=$(LIB_PATH)$(OBJ_DLL)

ll: $(DLL_PATHFILE)
$(DLL_PATHFILE):$(C_OBJS) $(CXX_OBJS)
	$(CC) $(CFLAGS) -o $(DLL_PATHFILE) $(C_OBJS) $(CXX_OBJS) $(LDFLAGS)
	@echo -e "\n>>>>> Compiling *$(OBJ_DLL)* sucessfully ended\n"


ifeq ($(findstring .c, $(CSRC)), .c)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_CFLAGS)
endif

ifeq ($(findstring .cpp, $(CPPSRC)), .cpp)
%.o:%.cpp
	$(CXX) $(CFLAGS) -std=c++14 $(INC_CFLAGS) -c $< -o $@
endif

clean:
	-rm -f $(C_OBJS)
	-rm -f $(CXX_OBJS)
	-rm -f $(DLL_PATHFILE)

