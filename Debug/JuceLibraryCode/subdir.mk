################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../JuceLibraryCode/juce_audio_basics.cpp \
../JuceLibraryCode/juce_audio_devices.cpp \
../JuceLibraryCode/juce_audio_formats.cpp \
../JuceLibraryCode/juce_core.cpp \
../JuceLibraryCode/juce_cryptography.cpp \
../JuceLibraryCode/juce_data_structures.cpp \
../JuceLibraryCode/juce_events.cpp 

OBJS += \
./JuceLibraryCode/juce_audio_basics.o \
./JuceLibraryCode/juce_audio_devices.o \
./JuceLibraryCode/juce_audio_formats.o \
./JuceLibraryCode/juce_core.o \
./JuceLibraryCode/juce_cryptography.o \
./JuceLibraryCode/juce_data_structures.o \
./JuceLibraryCode/juce_events.o 

CPP_DEPS += \
./JuceLibraryCode/juce_audio_basics.d \
./JuceLibraryCode/juce_audio_devices.d \
./JuceLibraryCode/juce_audio_formats.d \
./JuceLibraryCode/juce_core.d \
./JuceLibraryCode/juce_cryptography.d \
./JuceLibraryCode/juce_data_structures.d \
./JuceLibraryCode/juce_events.d 


# Each subdirectory must supply rules for building sources it contributes
JuceLibraryCode/%.o: ../JuceLibraryCode/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -I"/home/james/workspace/LaunchkeyDemo/JuceLibraryCode" -I/home/james/raspberrypi/rootfs/usr/include/arm-linux-gnueabihf/ -I/home/james/raspberrypi/rootfs/usr/include/ -I/home/james/JUCE/modules -O0 -g3 -ggdb -Wall -c -fmessage-length=0  $(shell pkg-config --cflags alsa libcurl x11) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


