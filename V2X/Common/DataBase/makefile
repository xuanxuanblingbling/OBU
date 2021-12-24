#####################################################
## 文件功能：编译路侧工程代码，生成数据库使用的库
## 开 发 者：黄赛
## 开发日期：20200514
## 修改日志：20200514   创建文件
#####################################################
#####################################################
## 路径包含部分
#####################################################
COMMON_DIR=$(ROOTDIR)/Common
CLOCKTIME_DIR=$(COMMON_DIR)/PreciseTiming
MISC_DIR=$(COMMON_DIR)/Misc
RSULOG=$(COMMON_DIR)/RsuLog
DATABASE_DIR=$(COMMON_DIR)/DataBase
######################源文件##########################
SRC+=$(DATABASE_DIR)/src/DataBase.c
###################中间文件###########################
C_OBJS+=$(patsubst %.c,%.o,$(wildcard $(SRC)))
###################编译参数###########################
CFLAGS += -c
CFLAGS += -Wall
CFLAGS += -fPIC
CFLAGS += -Os
###################头文件#############################
INC_CFLAGS += -I $(DATABASE_DIR)/inc/
INC_CFLAGS += -I $(DATABASE_DIR)/if/
INC_CFLAGS += -I $(COMMON_DIR)/RsuLog/if/
INC_CFLAGS += -I $(COMMON_DIR)/Libraries/inc/sqlite3/
INC_CFLAGS += -I $(MISC_DIR)/if/
#####################################################
## 编译部分
#####################################################
TARGET = $(DATABASE_DIR)/lib/libdatabase.so
all:$(TARGET)
$(TARGET):$(C_OBJS) dir_check
	$(CC) -shared  $(C_OBJS)  -o $@
	cp $(TARGET) $(LIBS_BUILDOUT)
$(C_OBJS):%.o:%.c
	$(CC) $(CFLAGS) $(INC_CFLAGS) $< -o $@
dir_check:
	test -d ./lib || mkdir -p lib
#####################################################
## 清理部分
#####################################################
.PHONY:clean
clean:
	@echo "start to clean"
	-rm -f $(LIBS_BUILDOUT)/libdatabase.so
	-rm -f $(C_OBJS)
	-rm -f $(TARGET)
	@echo "end to clean"

