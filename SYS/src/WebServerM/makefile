TARGET = web
CUR_PATH = .
#获取所有c cpp h文件
DIRS = $(shell find $(CUR_PATH) -maxdepth 10 -type d)
SRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))
CSRC = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

OBJS = ${SRC:%.cpp=%.o}
COBJS = ${CSRC:.c=.o}

#文件生成路径
DIR_LIB = ./../../lib
BIN_TARGET = ${CUR_PATH}/${TARGET}

#编译工具链
ver = debug

ARCH_CC = arm-fslc-linux-gnueabi-gcc  -mfpu=neon  -mfloat-abi=hard  --sysroot=/opt/fslc-framebuffer/2.4.4/sysroots/armv7at2hf-neon-fslc-linux-gnueabi
ARCH_CXX = arm-fslc-linux-gnueabi-gcc -E  -mfpu=neon -mfloat-abi=hard --sysroot=/opt/fslc-framebuffer/2.4.4/sysroots/armv7at2hf-neon-fslc-linux-gnueabi
#CC = gcc
#CXX = g++
#ARCH_CC = $(CC)
#ARCH_CXX = $(CXX)

#依赖库及头文件
LDFLAGS += -ldbus-glib-1 -ldbus-1 -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -pthread -lrt -lm -lstdc++

CFLAGS += -DMG_ENABLE_HTTP_STREAMING_MULTIPART -DMG_ENABLE_CALLBACK_USERDATA -W -DNONUTF8CONV -DELPP_NO_DEFAULT_LOG_FILE '-Wno-implicit-fallthrough'
LIBS += -L$(DIR_LIB) -llog
LIBS += -lrt -lm -lpthread -ldl -D_GNU_SOURCE

INC += -I ./../Log 				\
       -I ./../WebServerM/main 	\
       -I ./../Cjson 	            \

#PKGCFLAGS += `pkg-config --cflags dbus-glib-1 dbus-1 glib-2.0`
#PKGLIBS += `pkg-config --libs dbus-glib-1 dbus-1 glib-2.0`

ifeq ($(ver), debug)

all: ${OBJS} ${COBJS}
	$(CXX) $(CFLAGS) -g -std=c++14 -Wall $^ -o ${BIN_TARGET} $(LIBS) $(LDFLAGS)

#编译所有源文件
${OBJS}:%.o:%.cpp
	$(CXX) $(CFLAGS) $(INC) -g -std=c++14 -Wall -c $< -o $@ $(LIBS) $(LDFLAGS)

${COBJS}:%.o:%.c
	$(CC) $(CFLAGS) $(INC) -fno-stack-protector -g -std=c11 -Wall -c $< -o $@ $(LIBS) $(LDFLAGS)
	
else
all: ${OBJS} ${COBJS}
	$(ARCH_CXX) $(CFLAGS) $(INC) -std=c++14 -Wall $^ -o ${BIN_TARGET} $(LIBS)
	
#编译所有源文件
${DIR_OBJ}:%.o:%.cpp
	$(ARCH_CXX) $(CFLAGS) $(INC) -std=c++14 -Wall -c $< -o $@

${DIR_OBJ}:%.o:%.c
	$(ARCH_CC) $(INC) -std=c11 -Wall -c $< -o $@ 
	
endif

.PHONY: clean sysm
clean:
	rm -rf ${OBJS} ${COBJS} sysm Authen.json UserInfo.db ./logs
