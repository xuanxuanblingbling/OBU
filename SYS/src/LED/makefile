CURRENT_DIR := .
DIRS = $(shell find $(CURRENT_DIR) -maxdepth 1 -type d)
SRC_C := $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))

INC_DIR = -I ./
INC_DIR += -I ../Log
 
LIBS += -lrt -lpthread

OBJS_C =$(patsubst %.c, %.o, $(SRC_C))

BIN_TARGET := ledtest

all:${OBJS_C}
	$(CC) -g -std=c++14 -Wall $^ -o ${BIN_TARGET}  $(LIBS)

${OBJS_C}:%.o:%.c
	$(CC)  $(INC_DIR) -fno-stack-protector -g -std=c11 -Wall -c $< -o $@  