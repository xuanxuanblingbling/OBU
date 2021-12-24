ROOTDIR ?= $(abspath ../..)
CUR_DIR = .

# log dir
TEST_LOG_DIR := $(CUR_DIR)
C_SRCS+=$(wildcard $(TEST_LOG_DIR)/src/*.c )
CXX_SRCS+=$(wildcard $(TEST_LOG_DIR)/src/*.cpp )
################################################################################
TARGET = $(TEST_LOG_DIR)/lib/libtestlog.so

# EXTRA_CFLAGS
EXTRA_CFLAGS += -I$(TEST_LOG_DIR)/inc
EXTRA_CFLAGS += -I$(TEST_LOG_DIR)/if
EXTRA_CFLAGS += -I$(ROOTDIR)/APP/V2XService/inc
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/RsuLog/if
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/Utils/inc
EXTRA_CFLAGS += -I${ROOTDIR}/Protocol_Stack/Stack_Lib/Interface/include
EXTRA_CFLAGS += -I${ROOTDIR}/Protocol_Stack/Stack_Lib/Interface/include/MsgLayerV2
EXTRA_CFLAGS += -I${ROOTDIR}/Protocol_Stack/Stack_Lib/Interface/include/MsgLayerV3
EXTRA_CFLAGS += -I${ROOTDIR}/Protocol_Stack/Stack_Lib/Interface/include/MsgLayerV4
EXTRA_CFLAGS += -I${ROOTDIR}/Protocol_Stack/Stack_Lib/Interface/include/MsgLayerVN4
EXTRA_CFLAGS += -I${ROOTDIR}/Protocol_Stack/Stack_Lib/Interface/include/NetLayer
# LDFLAGS (find the libs)
LDFLAGS += -lpthread -lrt

DEBUG_HEAD=$(ROOTDIR)/Common/Utils/inc/Debug.h
LDFLAGS += -L$(ROOTDIR)/Common/RsuLog/lib -llog

LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lMsgLayerV4
LDFLAGS += -L$(ROOTDIR)/Protocol_Stack/RSULib -lMsgLayerVN4

# OBJS
C_OBJS = ${C_SRCS:.c=.o}
CXX_OBJS = ${CXX_SRCS:.cpp=.o}
################################################################################
# Build Rules
################################################################################
all: $(TARGET)

${TARGET}: dir_check ${C_OBJS} ${CXX_OBJS}
	${CC} -g  -shared ${C_OBJS} ${CXX_OBJS} -o ${TARGET}  ${EXTRA_CFLAGS} ${LDFLAGS}  -lstdc++
	cp $(TARGET) $(LIBS_BUILDOUT)

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) -g -fPIC $(EXTRA_CFLAGS) -o $@ -c $<

${CXX_OBJS}:%.o:%.cpp
	${CXX} -g -fPIC -std=c++14 -Wall ${EXTRA_CFLAGS} -c $< -o $@

dir_check:
	@test -d ./lib || mkdir -p lib

clean:
	rm -f $(TARGET) ${C_OBJS} ${CXX_OBJS}
