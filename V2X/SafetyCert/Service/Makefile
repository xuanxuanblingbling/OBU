CUR_DIR = ./

export ARCH
export CROSS_COMPILE

# zlog dir
CERT_DIR := $(CUR_DIR)
APP_STACK_DIR ?= .
MODULE_SOURCES+=$(wildcard $(CERT_DIR)src/*.c )


################################################################################
TARGET = $(CERT_DIR)../lib/libcertmanager.so

# EXTRA_CFLAGS
EXTRA_CFLAGS += -I$(CERT_DIR)inc -I$(CERT_DIR)if 

# LDFLAGS (find the libs)
LDFLAGS += -L$(CUR_DIR)lib -ldatasec -lssf -lxdjakey -lccsaasn1  
LDFLAGS += -lm


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



