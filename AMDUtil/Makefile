#COMPILE AMD SDK files
#set project type
PRJ_TYPE := g++
#set Debug or Release
Compile_Flag := Release
#set output path
Output := bin
#set source path
SRC := src
#add libs used here
LIBS := -lOpenCL
#INCLUDEPATH := -I/home/waanan/NVIDIA_GPU_Computing_SDK/OpenCL/common/inc
INCLUDEPATH := -I/opt/AMDAPPSDK-2.9-1/include
###################################
#DON"T MODIFY THE BELOWS
#combine output folder
FinalOutput := $(Output)/$(Compile_Flag)/
#list all dirs
SUBDIRS := $(shell find $(SRC) -type d)

#flags in makefile
DEBUG_FLAG = -O0 -g3 -Wall -c -fmessage-length=0
RELEASE_FLAG = -O3 -Wall -c -fmessage-length=0

RM := rm -rf

#set compile flag
ifeq ($(Compile_Flag),Debug)
CFLAGS := $(DEBUG_FLAG)
else
CFLAGS := $(RELEASE_FLAG)
endif

#prepare files
CPP_SRCS := $(shell find $(SRC) -name *.cpp)

OBJS := $(CPP_SRCS:%.cpp=$(FinalOutput)%.o)

#all target
all: dir $(OBJS)

dir:
	mkdir -p $(FinalOutput); 
	for val in $(SUBDIRS);do \
   	mkdir -p $(FinalOutput)$${val}; \
	done;

$(FinalOutput)%o:./%cpp
	@echo 'Building file: $<'
	@echo 'Invoking:GCC C++ Compiler'
	$(PRJ_TYPE) $(CFLAGS) $(INCLUDEPATH) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

#other targets
clean:
	-$(RM) $(Output)/*
	-@echo ' '
.PHONY:all clean

