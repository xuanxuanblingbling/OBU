
CURRET_DIR =.

###############source file##########
C_SRCS :=
C_SRCS +=$(CURRET_DIR)/*.c

################object files############
C_OBJS :=
C_OBJS +=$(patsubst %.c,%.o,$(wildcard $(C_SRCS)))

################ include path ############
IN_PATH :=
IN_PATH += -I${CURRET_DIR}

################ library path & libraries ############

LD_CFLAGS :=
LD_CFLAGS += -L$(CURRET_DIR)/../  -lgpsinterface  -llog-dev
LD_CFLAGS += -L$(CURRET_DIR)/../GPSUtil  -lgpsutil -lqxwz-pssdk
LD_CFLAGS += -lpthread -lm

################ complie configs ################

COM_CFLAGS :=
COM_CFLAGS += -c -Wall

################ target ################

TARGET = gps_exc

################ complie target ################

all:${TARGET}
${TARGET}:${C_OBJS}
	$(CC) $^ -o $@ $(LD_CFLAGS)	

${C_OBJS}:%.o:%.c 
	$(CC) $(COM_CFLAGS) $(IN_PATH) $< -o $@

.PHONY:clean
clean:
	@echo "start to clean"
	-rm -f $(C_OBJS)
	-rm -f $(TARGET)
	@echo "end to clean"