#####################################################
## 文件功能：编译路侧工程代码，生成定时模块的库
## 开 发 者：黄赛
## 开发日期：20200527
## 修改日志：20200527   创建文件
#####################################################
#####################################################
## 路径包含部分
#####################################################
COMMON_DIR=$(ROOTDIR)/Common
CLOCKTIME_DIR=$(COMMON_DIR)/PreciseTiming
MISC_DIR=$(COMMON_DIR)/Misc
RSULOG=$(COMMON_DIR)/RsuLog
######################源文件##########################
SRC+=$(CLOCKTIME_DIR)/src/*.c
###################中间文件###########################
C_OBJS+=$(patsubst %.c,%.o,$(wildcard $(SRC)))
###################编译参数###########################
CFLAGS += -c
CFLAGS += -Wall
CFLAGS += -fPIC
CFLAGS += -Os
###################头文件#############################
INC_CFLAGS += -I $(MISC_DIR)/if/
INC_CFLAGS += -I $(RSULOG)/if/
INC_CFLAGS += -I $(CLOCKTIME_DIR)/if/
INC_CFLAGS += -I $(CLOCKTIME_DIR)/inc/
#####################################################
## 编译部分
#####################################################
TARGET = $(CLOCKTIME_DIR)/lib/libclocktime.so

all:$(TARGET)

$(TARGET):$(C_OBJS) dir_check
	$(CC) -shared  $(C_OBJS) -o $@
	cp $(TARGET) $(LIBS_BUILDOUT)

$(C_OBJS):%.o:%.c
	$(CC) $(CFLAGS) $(INC_CFLAGS) $< -o $@

dir_check:
	@test -d ./lib || mkdir -p lib
#####################################################
## 清理部分
#####################################################
.PHONY:clean

clean:
	@echo "start to clean"
	-rm -f $(LIBS_BUILDOUT)/libclocktime.so
	-rm -f $(C_OBJS)
	-rm -f $(TARGET)
	@echo "end to clean"


