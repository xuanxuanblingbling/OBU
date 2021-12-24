#################################################################
#                     PRIVATE PART                              #
#################################################################

APP_STACK_DIR = .
# 接入层目录
INC_CFLAGS += -I$(APP_STACK_DIR)/Inc
INC_CFLAGS += -I$(APP_STACK_DIR)/Intf
# 对外接口目录
INC_CFLAGS += -I $(APP_STACK_DIR)./Stack_Lib/Interface/include
INC_CFLAGS += -I $(APP_STACK_DIR)./Stack_Lib/Interface/include/LogLayer
INC_CFLAGS += -I $(APP_STACK_DIR)./Stack_Lib/Interface/include/AppLayer
# 动态链接库
LDFLAGS += -lpthread -lm -lstdc++ -dl
LDFLAGS += -fvisibility=hidden

LDFLAGSAG15 += -lrt -lglib-2.0
LDFLAGSAG15 += -lv2x_radio -lcv2x-kinematics

# INC_CFLAGSCX += -I $(APP_STACK_DIR)/_01_CX7100Layer/include
# LDFLAGSCX += -L$(APP_STACK_DIR)/_01_CX7100Layer/lib -lgps
INC_CFLAGSCX += 
LDFLAGSCX += 
# 动态链接条件编译
DEBUG = y
ifeq ($(DEBUG),y)
	DEBUG_CFLAGS := -O -g -DDEBUG
else
	DEBUG_CFLAGS := -O2
endif

CFLAGS := -Wall -fPIC -shared
CFLAGS += $(DEBUG_CFLAGS)

CSRC += $(APP_STACK_DIR)/Src/*.c
CXXSRC += $(APP_STACK_DIR)/Src/*.cpp
C_OBJS += $(patsubst %.c,%.o,$(wildcard $(CSRC)))
CXX_OBJS += $(patsubst %.cpp,%.o,$(wildcard $(CXXSRC)))

CSRCAG15 += $(APP_STACK_DIR)/_01_AG15Layer/*.c
CXXSRCAG15 += $(APP_STACK_DIR)/_01_AG15Layer/*.cpp
C_OBJSAG15 += $(patsubst %.c,%.o,$(wildcard $(CSRCAG15)))
CXX_OBJSAG15 += $(patsubst %.cpp,%.o,$(wildcard $(CXXSRCAG15)))

CSRCCX += $(APP_STACK_DIR)/_01_CX7100Layer/*.c
CXXSRCCX += $(APP_STACK_DIR)/_01_CX7100Layer/*.cpp
C_OBJSCX += $(patsubst %.c,%.o,$(wildcard $(CSRCCX)))
CXX_OBJSCX += $(patsubst %.cpp,%.o,$(wildcard $(CXXSRCCX)))

CSRCDT += $(APP_STACK_DIR)/_01_DTLayer/*.c
CXXSRCDT += $(APP_STACK_DIR)/_01_DTLayer/*.cpp
C_OBJSDT += $(patsubst %.c,%.o,$(wildcard $(CSRCDT)))
CXX_OBJSDT += $(patsubst %.cpp,%.o,$(wildcard $(CXXSRCDT)))

LIB_PATH=$(APP_STACK_DIR)/Lib/$(BUILD_TYPE)/
OBJ_DLL=libv2xutil.so
OBJ_DLL_AG15=libv2xAG15.so
OBJ_DLL_CX=libv2xCX7100.so
OBJ_DLL_DT=libv2xDMD3A.so
DLL_PATHFILE=$(LIB_PATH)$(OBJ_DLL)
DLL_PATHFILE_AG15=$(LIB_PATH)$(OBJ_DLL_AG15)
DLL_PATHFILE_CX=$(LIB_PATH)$(OBJ_DLL_CX)
DLL_PATHFILE_DT=$(LIB_PATH)$(OBJ_DLL_DT)


ll: $(DLL_PATHFILE)
$(DLL_PATHFILE):$(C_OBJS) $(CXX_OBJS)
	$(CC) $(CFLAGS) -o $(DLL_PATHFILE) $(C_OBJS) $(CXX_OBJS) $(LDFLAGS)
	@echo -e "\n>>>>> Compiling *$(OBJ_DLL)* sucessfully ended\n"

ll: $(DLL_PATHFILE_CX)
$(DLL_PATHFILE_CX):$(C_OBJSCX) $(CXX_OBJSCX)
	$(CC) $(CFLAGS) -o $(DLL_PATHFILE_CX) $(C_OBJSCX) $(CXX_OBJSCX) $(LDFLAGS) $(LDFLAGSCX)
	@echo -e "\n>>>>> Compiling *$(OBJ_DLL_CX)* sucessfully ended\n"

ll: $(DLL_PATHFILE_DT)
$(DLL_PATHFILE_DT):$(C_OBJSDT) $(CXX_OBJSDT)
	$(CC) $(CFLAGS) -o $(DLL_PATHFILE_DT) $(C_OBJSDT) $(CXX_OBJSDT) $(LDFLAGS)
	@echo -e "\n>>>>> Compiling *$(OBJ_DLL_DT)* sucessfully ended\n"

ll: $(DLL_PATHFILE_AG15)
$(DLL_PATHFILE_AG15):$(C_OBJSAG15) $(CXX_OBJSAG15)
	$(CC) $(CFLAGS) -o $(DLL_PATHFILE_AG15) $(C_OBJSAG15) $(CXX_OBJSAG15) $(LDFLAGS) $(LDFLAGSAG15)
	@echo -e "\n>>>>> Compiling *$(OBJ_DLL_AG15)* sucessfully ended\n"


$(CXX_OBJS):%.o:%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ -std=c++14 $(INC_CFLAGS)
$(C_OBJS):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_CFLAGS)

$(CXX_OBJSAG15):%.o:%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ -std=c++14 $(INC_CFLAGS)
$(C_OBJSAG15):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_CFLAGS)

$(CXX_OBJSCX):%.o:%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ -std=c++14 $(INC_CFLAGS) $(INC_CFLAGSCX)
$(C_OBJSCX):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_CFLAGS)

$(CXX_OBJSDT):%.o:%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@ -std=c++14 $(INC_CFLAGS)
$(C_OBJSDT):%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_CFLAGS)

clean:
	-rm -f $(C_OBJS)
	-rm -f $(CXX_OBJS)
	-rm -f $(DLL_PATHFILE)
	-rm -f $(C_OBJSAG15)
	-rm -f $(CXX_OBJSAG15)
	-rm -f $(DLL_PATHFILE_AG15)
	-rm -f $(C_OBJSCX)
	-rm -f $(CXX_OBJSCX)
	-rm -f $(DLL_PATHFILE_CX)
	-rm -f $(C_OBJSDT)
	-rm -f $(CXX_OBJSDT)
	-rm -f $(DLL_PATHFILE_DT)

