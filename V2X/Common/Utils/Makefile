CUR_DIR = ./
ROOTDIR ?= $(abspath ../..)

# zlog dir
UTILS_DIR := $(CUR_DIR)
APP_STACK_DIR ?= .
UTILS_SRC := $(shell find -maxdepth 5 -name *.c)
MODULE_SOURCES+=$(wildcard $(UTILS_SRC) )

################################################################################
TARGET = $(APP_STACK_DIR)/lib/libapputils.so

CFLAGS += -g -O2
# EXTRA_CFLAGS
EXTRA_CFLAGS += -I$(UTILS_DIR)inc
EXTRA_CFLAGS += -I$(ROOTDIR)/Common/RsuLog/if

# LDFLAGS (find the libs)
LDFLAGS += -pthread -lm -lrt
LDFLAGS += -L $(ROOTDIR)/Common/RsuLog/lib -llog

OBJS := ${MODULE_SOURCES:.c=.o}
################################################################################
# Build Rules
################################################################################

all: $(TARGET)

$(TARGET): ${OBJS} dir_check
	#ar -crv $@ $(OBJS)
	$(CC) -g -shared $(CFLAGS) -o $(TARGET) ${OBJS} ${LDFLAGS} -lstdc++
	cp $(TARGET) $(LIBS_BUILDOUT)

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) -g $(CFLAGS) -fPIC -c $< -o $@ $(EXTRA_CFLAGS)

dir_check:
	@test -d ./lib || mkdir -p lib

clean:
	rm -f $(TARGET) ${OBJS}

