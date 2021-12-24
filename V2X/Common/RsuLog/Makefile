CUR_DIR = ./

# zlog dir
ZLOG_DIR := $(CUR_DIR)
MODULE_SOURCES+=$(wildcard $(ZLOG_DIR)/src/*.c )

################################################################################
TARGET = $(ZLOG_DIR)/lib/liblog.so

# EXTRA_CFLAGS
EXTRA_CFLAGS += -I$(ZLOG_DIR)inc -I$(ZLOG_DIR)if

# LDFLAGS (find the libs)
LDFLAGS += -lpthread

OBJS := ${MODULE_SOURCES:.c=.o}
################################################################################
# Build Rules
################################################################################
#CC := $(CROSS_COMPILE)gcc

all: $(TARGET)

$(TARGET): ${OBJS} dir_check
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
	rm -f $(LIBS_BUILDOUT)/liblog.so



