################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Main.cpp 

OBJS += \
./Main.o 

CPP_DEPS += \
./Main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -I"/home/james/workspace/LaunchkeyDemo/JuceLibraryCode" -I/home/james/raspberrypi/rootfs/usr/include/arm-linux-gnueabihf/ -I/home/james/raspberrypi/rootfs/usr/include/ -I/home/james/JUCE/modules -O0 -g3 -ggdb -Wall -c -fmessage-length=0  $(shell pkg-config --cflags alsa libcurl x11) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


