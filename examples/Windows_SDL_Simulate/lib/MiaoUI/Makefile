#目标文件名
target = smartRoom

#编译工具链
cc := arm-linux-gnueabihf-gcc 

#链接库的文件路径、头文件路径与要链接的库
PI_LIB_PATH := -I /home/lgb/piLib/piInclude/WiringPi/wiringPi -L /home/lgb/piLib -lwiringPi

#.o文件存放路径
O_PATH = ./obj

#源文件路径
SUBDIR := $(shell pwd)

#获取源文件路径下的所有.o文件名
GCC_SOURCE_PATH = $(foreach dir,$(SUBDIR),$(wildcard $(dir)/*.c))
GCC_OBJ_PATH = $(patsubst %.c,$(O_PATH)/%.o, $(notdir $(GCC_SOURCE_PATH)))


#生成目标文件
$(target) : $(GCC_OBJ_PATH)
	$(cc) $(GCC_OBJ_PATH) $(PI_LIB_PATH) -o $(target)


#将生成的.o文件放到O_PATH目录下
$(O_PATH)/%.o: $(SUBDIR)/%.c
	$(cc) -c $(PI_LIB_PATH) $< -o $@


#伪目标
.PHONY : clean

clean :
	rm $(GCC_OBJ_PATH)
	rm $(target)

