
CURRENT_DIR = .

OBJLIB_DIR :=$(CURRENT_DIR)/../../lib

########## source file ##############
C_SRCS :=
C_SRCS += $(CURRENT_DIR)/GPS-main.c
C_SRCS += $(CURRENT_DIR)/Common.c
C_SRCS += $(CURRENT_DIR)/GPS_locate.c
C_SRCS += $(CURRENT_DIR)/ConfUtil/*.c

########## object file ##############
C_OBJS := 
C_OBJS += $(patsubst %.c,%.o,$(wildcard $(C_SRCS)))

###################编译参数#############################################
CFLAGS += -c
CFLAGS += -Wall
CFLAGS += -fPIC

###################头文件###############################################
INC_CFLAGS += -I $(CURRENT_DIR)/GPSUtil \
              -I $(CURRENT_DIR)/ \
			  -I $(CURRENT_DIR)/ConfUtil 

################### libarary.so #######################################
LDFLAGS :=
LDFLAGS += -L $(CURRENT_DIR)/  -llog-dev 
LDFLAGS += -L $(CURRENT_DIR)/GPSUtil/ -lgpsutil
LDFLAGS += -L $(CURRENT_DIR)/lib 
LDFLAGS += -lrt -lpthread -lglib-2.0 -lv2x_radio  -lcv2x-kinematics  -lqxwz-pssdk

## 编译部分
#######################################################################
TARGET_PATH=$(CURRENT_DIR)
$(shell mkdir -p $(TARGET_PATH))

TARGET = $(TARGET_PATH)/libgpsinterface.so
all:$(TARGET)

#$(C_OBJS):%.o:%.c
#	$(CC) $(CFLAGS) $(INC_CFLAGS) $< -o $@
#$(TARGET):$(C_OBJS)
#	$(CC) $^ -o $@ $(LDFLAGS) 
all:$(TARGET)

$(TARGET): ${C_OBJS}
	make -C ./GPSUtil all
	$(CC) -shared -fPIC  -o $(TARGET) ${C_OBJS} ${LDFLAGS}
	
$(C_OBJS):%.o:%.c

	$(CC) -g -fPIC $(CFLAGS) $(INC_CFLAGS) -o $@ -c $<
#####################################################
## 清理部分
#####################################################
.PHONY:clean
clean:
	@echo "start to clean"
	make -C ./GPSUtil clean
	-rm -f $(C_OBJS)
	-rm -f $(TARGET)
	@echo "end to clean"


.CPYDIR:
CPYDIR := 
CPYDIR += sudo cp ./libgpsinterface.so ${OBJLIB_DIR};
CPYDIR += sudo cp ./GPSUtil/libgpsutil.so ${OBJLIB_DIR};
CPYDIR += sudo cp ./GPSUtil/liblog-dev.so ${OBJLIB_DIR};