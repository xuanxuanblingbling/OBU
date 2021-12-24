CUR_DIR = .

export ARCH
export CROSS_COMPILE
CERT_DIR := $(CUR_DIR)
MODULE_SOURCES+=$(wildcard $(CERT_DIR)/CAN/*.c )
#MODULE_SOURCES+=$(wildcard $(CERT_DIR)/CAN/*.c )
MODULE_SOURCES+=$(wildcard $(CERT_DIR)/ReadIniFile/*.c )

TARGET = $(CERT_DIR)/libcan.so

#LDFLAGS
LDFLAGS :=
LDFLAGS += -L$(CUR_DIR)/log
LDFLAGS += -lpthread -llog-dev
 
# EXTRA_CFLAGS
EXTRA_CFLAGS += -I$(CERT_DIR)/CAN \
                -I$(CERT_DIR)/ReadIniFile \
				-I$(CERT_DIR)/log \


# LDFLAGS (find the libs)

#C_OBJS+=$(patsubst %.c,%.o,$(wildcard $(C_SRCS)))
C_OBJS := ${MODULE_SOURCES:.c=.o}

##连接 dbus .o
LINK_OBJS += ./../../obj/*.o

all:$(TARGET)
$(TARGET):$(C_OBJS)
	${CC} -g  -shared ${C_OBJS}  ${LINK_OBJS} -o ${TARGET}  ${EXTRA_CFLAGS} ${LDFLAGS}

$(C_OBJS):%.o:%.c
	$(CC) -g -fPIC $(EXTRA_CFLAGS) -o $@ -c $<

##################
.PHONY:clean
clean:
	@echo "start to clean"
	-rm -f $(C_OBJS)
	-rm -f $(TARGET)
	@echo "end to clean"
	