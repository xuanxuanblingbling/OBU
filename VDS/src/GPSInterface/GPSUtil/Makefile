CUR_DIR = ./
MODULE_SOURCES += $(CUR_DIR)GPS.c
MODULE_SOURCES += $(CUR_DIR)kinematics_test.c

################################################################################
TARGET := libgpsutil.so

OBJS := ${MODULE_SOURCES:.c=.o}

#asn1c的环境
prefix_asn1c=../V2XUtil/LTEV_ZTE_Util/include
EXTRA_CFLAGS :=
EXTRA_CFLAGS += -I$(prefix_asn1c)
EXTRA_CFLAGS += -I$(prefix_asn1c)/glib-2.0
EXTRA_CFLAGS += -I../
EXTRA_CFLAGS += -I./
EXTRA_CFLAGS += -I../../../include
EXTRA_CFLAGS += -I../../utils
EXTRA_CFLAGS += -I../../edcode
EXTRA_CFLAGS += -I../../gnss
EXTRA_CFLAGS += -I../../dbus
LDFLAGS :=
LDFLAGS += -L ./ -lqxwz-pssdk 

CFLAGS :=

################################################################################
# Build Rules
################################################################################
#CC := $(CROSS_COMPILE)gcc


all: $(TARGET)

$(TARGET): ${OBJS}
	$(CC) -shared -fPIC $(CFLAGS) -o $(TARGET) ${OBJS} ${LDFLAGS}

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -fPIC -c $< -o $@ $(EXTRA_CFLAGS) ${LDFLAGS}

clean:
	rm -f $(TARGET)
	#rm -f $(OBJS)
	find ./ -name "*.o" |xargs rm -rf
	find ./ -name "*.d" |xargs rm -rf
