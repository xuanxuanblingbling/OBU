
APP_DIR := .
ASN_DIR := .

ASN_MODULE_SRCS := $(wildcard ./*.c)

# This file may be used as an input for make(3)
# Remove the lines below to convert it into a pure .am file
TARGET = $(APP_STACK_DIR)/lib/libmsgframe.so


EXTRA_CFLAGS += -I $(ASN_DIR)

OBJS := ${ASN_MODULE_SRCS:.c=.o}

################################################################################
# Build Rules
################################################################################
#CC := $(CROSS_COMPILE)gcc

all: $(TARGET)

$(TARGET): ${OBJS}
	$(CC) -shared $(CFLAGS) -o $(TARGET) ${OBJS} ${LDFLAGS}

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -fPIC -c $< -o $@ $(EXTRA_CFLAGS)
clean:
	rm -f $(TARGET)
	find ./ -name "*.o" |xargs rm -rf
	find ./ -name "*.d" |xargs rm -rf
