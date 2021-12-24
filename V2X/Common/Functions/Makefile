#####################################################
## 文件功能：编译路侧工程代码，生成数据库使用的库
## 开 发 者：姚志强
## 开发日期：20200831
## 修改日志：20200831   创建文件
#####################################################
#####################################################
## 路径包含部分
#####################################################
ROOTDIR ?= $(abspath ../..)
COMMON_DIR=$(ROOTDIR)/Common
MISC_DIR=$(COMMON_DIR)/Misc
RSULOG=$(COMMON_DIR)/RsuLog
FUNCTIONS_DIR = $(COMMON_DIR)/Functions
######################源文件##########################
SRC+=$(FUNCTIONS_DIR)/src/*.c
###################中间文件###########################
C_OBJS+=$(patsubst %.c,%.o,$(wildcard $(SRC)))
###################编译参数###########################
CFLAGS += -c
CFLAGS += -Wall
CFLAGS += -fPIC
CFLAGS += -Os
###################头文件#############################
INC_CFLAGS += -I $(FUNCTIONS_DIR)/inc/
INC_CFLAGS += -I $(FUNCTIONS_DIR)/if/
INC_CFLAGS += -I $(RSULOG)/if/
INC_CFLAGS += -I $(MISC_DIR)/if/
###################对应的库##########################
LDFLAGS += -L $(COMMON_DIR)/RsuLog/lib -llog

#####################################################
## 编译部分
#####################################################
TARGET = $(FUNCTIONS_DIR)/lib/libfunctions.so
all:$(TARGET)
$(TARGET):dir_check $(C_OBJS)
	$(CC) -shared  $(C_OBJS)  -o $@ ${LDFLAGS}
	cp $(TARGET) $(LIBS_BUILDOUT)
$(C_OBJS):%.o:%.c
	$(CC) $(CFLAGS) $(INC_CFLAGS) $< -o $@
dir_check:
	test -d ./lib || mkdir -p ./lib
#####################################################
## 清理部分
#####################################################
.PHONY:clean
clean:
	@echo "start to clean"
	-rm -f $(C_OBJS)
	-rm -f $(TARGET)
	@echo "end to clean"

