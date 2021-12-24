######################################################################################
# Master Makefile
########################################################################################

ROOTDIR = $(shell pwd)
COMMONDIR = $(ROOTDIR)/Common
LIBS_BUILDOUT = $(ROOTDIR)/libs

export ROOTDIR LIBS_BUILDOUT COMMONDIR

# Build groups
#MAKE_SRCCODE_COM_DATABASE		:= Make_DataBase			#数据库
MAKE_SRCCODE_CLOCKTIME			:= Make_ClockTime			#定时
MAKE_SRCCODE_COM_RSULOG			:= Make_RsuLog				#系统日志
MAKE_SRCCODE_COM_TESTLOG		:= Make_TestLog				#四跨日志
MAKE_SRCCODE_COM_UTILS			:= Make_Utils				#通用组件
MAKE_SRCCODE_COM_FUNCS			:= Make_Funcs				#通用函数

MAKE_SRCCODE_V2X_V2XSTACK		:= Make_V2XStack			#V2X协议栈模块
MAKE_SRCCODE_V2X_V2XSEVICE		:= Make_APP				    #V2X APP
MAKE_SRCCODE_V2X_V2XTEST		:= Make_TEST				#MAKE TEST
###########################################################################

MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_CLOCKTIME}					#定时库
MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_COM_DATABASE}				#数据库
MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_COM_RSULOG}				#日志库
MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_COM_UTILS}					#通用组件
MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_COM_FUNCS}					#通用函数

MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_V2X_V2XSTACK}				#协议栈
MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_COM_TESTLOG}				#四跨日志库
MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_V2X_V2XSEVICE}				#V2X APP

#MAKE_SRCCODE_GROUP              +=${MAKE_SRCCODE_V2X_V2XTEST}
# Build list
BL_MAKE_ALL		?= $(MAKE_SRCCODE_GROUP)
###########################################################################

export ARCH
export CROSS_COMPILE

DEBUG = y
ifeq ($(DEBUG),y)
	DEBUG_CFLAGS := -O -g -DDEBUG
else
	DEBUG_CFLAGS := -O2
endif

CFLAGS := -Wall #-Werror -MD
CFLAGS += $(DEBUG_CFLAGS)

export EXTRA_CFLAGS
export LDFLAGS
export CFLAGS

all: dir_check
	@for target in `echo $(BL_MAKE_ALL) | tr , ' '` ; do  \
		if ! $(MAKE) $${target} ; then  \
			exit 1 ;  \
		fi ;  \
	done
	$(CPYDIR)

clean:
	find ./ -name "*.o" |xargs rm -rf
	@rm -f .toolchain
	@sudo rm -rf $(INSTALLDIR)
	@for target in `echo $(BL_MAKE_ALL) | tr , ' '` ; do  \
		$(MAKE) $${target} CMD=clean ; \
	done
	$(DELDIR)

dir_check:
	@test -d ./libs || mkdir -p ./libs
################################################################################
#
# Software Components Build Rule
#
################################################################################
##
##
## BG_COMMON components:
## build out libclocktime.so
Make_ClockTime:
	@$(MAKE) -C Common/PreciseTiming $(CMD)

## build out libdatabase.so
#Make_DataBase:
	#@$(MAKE) -C Common/DataBase $(CMD)

## build out liblog.so
Make_RsuLog:
	@$(MAKE) -C Common/RsuLog $(CMD)

## build out libtestlog.so
Make_TestLog:
	@$(MAKE) -C Common/TestLog $(CMD)

## build out libapputils.so
Make_Utils:
	@$(MAKE) -C Common/Utils $(CMD)

## build out libfunctions.so
Make_Funcs:
	@$(MAKE) -C Common/Functions $(CMD)

## BG_SafetyCertcomponents:
# Make_SafetyCert:
# 	#@$(MAKE) -C SafetyCert/Service $(CMD)
# 	@$(MAKE) -C SafetyCert/Service_Iwall $(CMD)

## BG_V2XStack components:
## make in v2x stack
Make_V2XStack:
	@$(MAKE) -C Protocol_Stack $(CMD)

## make in APP;
Make_APP:
	@$(MAKE) -C APP $(CMD)

## make in TEST;
# Make_TEST:
# 	#@$(MAKE) -C TEST $(CMD)

.CPYDIR:
CPYDIR :=
#CPYDIR += sudo mkdir ./libs;

.DELDIR:
DELDIR :=
#DELDIR += sudo rm -rf ./lib;
#DELDIR += sudo rm ./lib/*;
