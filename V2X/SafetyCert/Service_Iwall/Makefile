CUR_DIR = ./

export ARCH
export CROSS_COMPILE

# zlog dir
CERT_DIR := $(CUR_DIR)
APP_STACK_DIR ?= .
MODULE_SOURCES+=$(wildcard $(CERT_DIR)src/*.c )
MODULE_SOURCES+=$(wildcard $(CERT_DIR)src/SecFrame/*.c )
MODULE_SOURCES+=$(wildcard $(CERT_DIR)src/utils/json/*.c )
MODULE_SOURCES+=$(wildcard $(CERT_DIR)src/utils/queue/*.c )
MODULE_SOURCES+=$(wildcard $(CERT_DIR)src/utils/thread/*.c )
MODULE_SOURCES+=$(wildcard $(CERT_DIR)src/utils/timer/*.c )

CXX_SRC+=$(wildcard $(CERT_DIR)src/*.cpp)

################################################################################
TARGET = $(CERT_DIR)../lib/libcertmanager.so

#LDFLAGS += -L$(CUR_DIR)/lib -lmsgframe

LDFLAGS += -L$(CUR_DIR)../../Common/Libraries/lib/iwall/hard -liwall_v2x_api -liwall_v2x \
           -L$(CUR_DIR)../../Common/RsuLog/lib -llog

# EXTRA_CFLAGS
EXTRA_CFLAGS += -I$(CERT_DIR)inc -I$(CERT_DIR)if \
                -I$(CERT_DIR)../../Common/Libraries/inc/iwall \
                -I$(CERT_DIR)../../V2XStack/Service/V2XUtil/_01_AG15Layer/Include/glib-2.0/ \
                -I$(CERT_DIR)../../Common/RsuLog/if/ \
                -I$(CERT_DIR)src/SecFrame \
                -I$(CERT_DIR)src/utils/json/ \
                -I$(CERT_DIR)src/utils/queue/ \
                -I$(CERT_DIR)src/utils/thread/ \
                -I$(CERT_DIR)/src/utils/timer/ \
                -I$(CERT_DIR)/src/utils/ini/

# LDFLAGS (find the libs)
LDFLAGS += -lpthread

C_OBJS := ${MODULE_SOURCES:.c=.o}
CXX_OBJS = ${CXX_SRC:.cpp=.o}
################################################################################
# Build Rules
################################################################################
#CC := $(CROSS_COMPILE)gcc

all: $(TARGET)

${TARGET}: ${C_OBJS} ${CXX_OBJS}
	${CC} -g  -shared ${C_OBJS} ${CXX_OBJS} -o ${TARGET}  ${EXTRA_CFLAGS} ${LDFLAGS}  -lstdc++
	cp $(TARGET) $(LIBS_BUILDOUT)
.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) -g -fPIC $(EXTRA_CFLAGS) -o $@ -c $<


${CXX_OBJS}:%.o:%.cpp
	${CXX} -g -fPIC -std=c++14 -Wall ${EXTRA_CFLAGS} -c $< -o $@


clean:
	rm -f $(TARGET) ${C_OBJS} ${CXX_OBJS}
	#rm -rf ../../../Build_Out/Libraries/RSULibs/libcertmanager.so



