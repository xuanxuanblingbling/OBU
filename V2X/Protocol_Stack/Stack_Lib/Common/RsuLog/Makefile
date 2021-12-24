#################################################################
#                     PRIVATE PART                              #
#################################################################
APP_STACK_DIR = .

INC_CFLAGS += -I $(APP_STACK_DIR)/Inc
INC_CFLAGS += -I $(APP_STACK_DIR)/Intf
# 对外接口目录
INC_CFLAGS += -I $(APP_STACK_DIR)/../../Interface/include/LogLayer
# 源文件
CSRC += $(APP_STACK_DIR)/Src/*.c
C_OBJS += $(patsubst %.c,%.o,$(wildcard $(CSRC)))

CSRCPP += $(APP_STACK_DIR)/Src/*.cpp
CPP_OBJS += $(patsubst %.cpp,%.o,$(wildcard $(CSRCPP)))

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
LD_FLAGS += -lpthread -lm -lstdc++
# 目标文件
Target_Lib=$(APP_STACK_DIR)/Lib/liblog.a
Target_Dll=$(APP_STACK_DIR)/Lib/liblog.so
TARGET = $(Target_Lib) $(Target_Dll)
# 编译规则
all:$(TARGET)
$(Target_Lib):$(C_OBJS) $(CPP_OBJS)
	$(AR) rcs $@ $^
	@echo -e "\n>>>>> Compiling *$(Target_Lib)* sucessfully ended\n"
$(Target_Dll):$(C_OBJS) $(CPP_OBJS)
	$(CC) -shared $^ -o $@
	@echo -e "\n>>>>> Compiling *$(Target_Dll)* sucessfully ended\n"
$(C_OBJS):%.o:%.c
	$(CC) $(CFLAGS) $(INC_CFLAGS) $(LD_FLAGS) $< -o $@ 
$(CPP_OBJS):%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC_CFLAGS) $(LD_FLAGS) $< -o $@
.PHONY:all clean 
clean:
	-rm -f $(C_OBJS)
	-rm -f $(CPP_OBJS)
	-rm -f $(TARGET)
