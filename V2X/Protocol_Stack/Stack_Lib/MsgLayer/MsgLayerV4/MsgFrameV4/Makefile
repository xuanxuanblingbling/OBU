
APP_DIR := .
ASN_DIR := .

ASN_MODULE_SRCS := $(wildcard ./*.c)

# This file may be used as an input for make(3)
# Remove the lines below to convert it into a pure .am file
TARGETDLL = ../Lib/libmsgframeV4.so
TARGETLIB = ../Lib/libmsgframeV4.a
EXTRA_CFLAGS += -I $(ASN_DIR)

OBJS := ${ASN_MODULE_SRCS:.c=.o}

################################################################################
# Build Rules
################################################################################
#CC := $(CROSS_COMPILE)gcc

all: $(TARGETDLL)
$(TARGETDLL): ${OBJS}
	$(CC) -shared $(CFLAGS) -o $(TARGETDLL) ${OBJS} ${LDFLAGS}
	@echo -e "\n>>>>> Compiling *$(TARGETDLL)* sucessfully ended\n"

all: $(TARGETLIB)
$(TARGETLIB): ${OBJS}
	$(AR) rcs $(TARGETLIB) ${OBJS}
	@echo -e "\n>>>>> Compiling *$(TARGETLIB)* sucessfully ended\n"

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -fPIC -c $< -o $@ $(EXTRA_CFLAGS)
clean:
	rm -f $(TARGETDLL)
	rm -f $(TARGETLIB)
	find ./ -name "*.o" |xargs rm -rf
	find ./ -name "*.d" |xargs rm -rf
