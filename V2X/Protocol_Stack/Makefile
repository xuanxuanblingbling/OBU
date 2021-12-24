######################################################################################
#
# Master Makefile
#
########################################################################################

APP_STACK_DIR = $(shell pwd)
export APP_STACK_DIR

#新增imx6Q 与imx8Q的编译选项
BUILD_TYPE = imx6
export BUILD_TYPE
ifeq ($(CROSS_COMPILE),aarch64-fslc-linux-)
	# @echo "交叉编译目标为imx6q"
	BUILD_TYPE = imx8
	
else ifeq ($(CROSS_COMPILE),aarch64-poky-linux-) 
	# @echo "交叉编译目标为imx8m"
	BUILD_TYPE = imx8

else ifeq ($(CROSS_COMPILE),arm-fslc-linux-gnueabi-) 
	# @echo "交叉编译目标为imx8q"
	BUILD_TYPE = imx6

else
	# @echo "交叉编译目标为x86-64"
	# CC=gcc
endif
#ifdef WVR_M913_0001_ROOTDIR
#	#全局程序编译
#	WVR_M913_0001_ROOTDIR := $(abspath $(APP_STACK_DIR)/../..)
#	SAFETYCERT_DIR := $(abspath $(APP_STACK_DIR)/../SafetyCert)
#else
	#协议栈模块 编译使用
	WVR_M913_0001_ROOTDIR := $(abspath $(APP_STACK_DIR))
	SAFETYCERT_DIR := $(abspath $(APP_STACK_DIR)/SafetyCert)
#endif

export WVR_M913_0001_ROOTDIR
export SAFETYCERT_DIR

# Build groups
BG_WJLOG         	 := lib-wjlog
BG_MSGFRAME2         := lib-MsgFrameV2
BG_MSGFRAME3         := lib-MsgFrameV3
BG_MSGFRAME4         := lib-MsgFrameV4
BG_MSGFRAMEN4        := lib-MsgFrameVN4
# BG_SECLIBIWALL4      := lib-SecLibIwallV4
# BG_SECLIBIWALLN4     := lib-SecLibIwallVN4
# BG_SECLIBXDJA        := lib-SecLibXdja
BG_SECCHIPLIB        := lib-SecChip
BG_SECFRAME          := lib-SecLayer
BG_V2XUTIL           := lib-v2xutil
BG_STACKDEV          := lib-StackDev
BG_CPPUTEST			 := CPPUTEST
BG_APP_TEST          := app-Test

BG_V2XSTACK_ALL		+=${BG_WJLOG}
BG_V2XSTACK_ALL		+=${BG_MSGFRAME2}
BG_V2XSTACK_ALL		+=${BG_MSGFRAME3}
BG_V2XSTACK_ALL		+=${BG_MSGFRAME4}
BG_V2XSTACK_ALL		+=${BG_MSGFRAMEN4}
# BG_V2XSTACK_ALL		+=${BG_SECLIBIWALL4}
# BG_V2XSTACK_ALL		+=${BG_SECLIBIWALLN4}
BG_V2XSTACK_ALL		+=${BG_SECCHIPLIB}
BG_V2XSTACK_ALL		+=${BG_SECFRAME}
BG_V2XSTACK_ALL		+=${BG_STACKDEV}
BG_V2XSTACK_ALL		+=${BG_V2XUTIL}
# BG_V2XSTACK_ALL		+=${BG_APP_TEST}
#BG_V2XSTACK_ALL		+=${BG_CPPUTEST}
# Build list
BL		?= $(BG_V2XSTACK_ALL)



###########################################################################

all:
	test -d ./Stack_Lib/Lib || mkdir -p ./Stack_Lib/Lib;
	test -d ./RSULib || mkdir -p ./RSULib;
	@for target in `echo $(BL) | tr , ' '` ; do  \
		if ! $(MAKE) $${target} ; then  \
			exit 1 ;  \
		fi ;  \
	done
	$(CPYDIR)

clean:
	-find ./ -name "*.o" |xargs rm -rf
	-rm -f .toolchain
	-rm -rf $(INSTALLDIR)
	-rm -rf ./RSULib/*.so
	@for target in `echo $(BL) | tr , ' '` ; do  \
		$(MAKE) $${target} CMD=clean ; \
	done
	-rm ./RSULib/SecDllOpen/*.so
	$(DELDIR)

################################################################################
#
# Software Components Build Rule
#
################################################################################

##
## BG_V2XLAYER components:
##
lib-wjlog:
	test -d ./Stack_Lib/Common/RsuLog/Lib || mkdir -p ./Stack_Lib/Common/RsuLog/Lib;
	@$(MAKE) -C Stack_Lib/Common/RsuLog $(CMD)
lib-MsgFrameV2:
	test -d ./Stack_Lib/MsgLayer/MsgLayerV2/Lib || mkdir -p ./Stack_Lib/MsgLayer/MsgLayerV2/Lib;
	@$(MAKE) -C Stack_Lib/MsgLayer/MsgLayerV2 $(CMD)
lib-MsgFrameV3:
	test -d ./Stack_Lib/MsgLayer/MsgLayerV3/Lib || mkdir -p ./Stack_Lib/MsgLayer/MsgLayerV3/Lib;
	@$(MAKE) -C Stack_Lib/MsgLayer/MsgLayerV3 $(CMD)
lib-MsgFrameV4:
	test -d ./Stack_Lib/MsgLayer/MsgLayerV4/Lib || mkdir -p ./Stack_Lib/MsgLayer/MsgLayerV4/Lib;
	@$(MAKE) -C Stack_Lib/MsgLayer/MsgLayerV4 $(CMD)
lib-MsgFrameVN4:
	test -d ./Stack_Lib/MsgLayer/MsgLayerVN4/Lib || mkdir -p ./Stack_Lib/MsgLayer/MsgLayerVN4/Lib;
	@$(MAKE) -C Stack_Lib/MsgLayer/MsgLayerVN4 $(CMD)

lib-SecChip:
	test -d ./SecLayer/SecChiplib/Lib/ || mkdir -p ./SecLayer/SecChiplib/Lib;
	@$(MAKE) -C ./SecLayer/SecChiplib $(CMD)
lib-SecLayer:
	test -d ./SecLayer/Lib || mkdir -p ./SecLayer/Lib;
	@$(MAKE) -C SecLayer $(CMD)
	-cp ./SecLayer/Lib/*.so ./RSULib;
	-cp ./SecLayer/Lib/SecDllOpen/*.so ./RSULib/SecDllOpen;
	-cp ./SecLayer/Lib/iwallSDK/*.so ./RSULib/SecDllOpen;
	-cp ./SecLayer/Lib/xdjaSDK/$(BUILD_TYPE)/*.so ./RSULib/SecDllOpen;
	-cp ./SecLayer/Lib/xdjaOffLineSDK/$(BUILD_TYPE)/*.so ./RSULib/SecDllOpen;
lib-StackDev:
	test -d ./Stack_Lib/Lib || mkdir -p ./Stack_Lib/Lib;
	@$(MAKE) -C Stack_Lib $(CMD)
	-cp ./Stack_Lib/Lib/*.so ./RSULib;
lib-v2xutil:
	test -d ./V2XUtil/Lib/$(BUILD_TYPE) || mkdir -p ./V2XUtil/Lib/$(BUILD_TYPE);
	@$(MAKE) -C V2XUtil $(CMD)
	# -cp ./V2XUtil/_01_CX7100Layer/lib/* ./RSULib;
	-cp ./V2XUtil/Lib/$(BUILD_TYPE)/*.so ./RSULib;
app-Test:
	@$(MAKE) -C _TestCode $(CMD)
CPPUTEST:
	@$(MAKE) -C TEST $(CMD)

.CPYDIR:
CPYDIR :=

.DELDIR:
DELDIR :=



