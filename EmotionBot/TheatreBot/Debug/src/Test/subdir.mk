################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Test/TestLoadEmotion.cpp 

OBJS += \
./src/Test/TestLoadEmotion.o 

CPP_DEPS += \
./src/Test/TestLoadEmotion.d 


# Each subdirectory must supply rules for building sources it contributes
src/Test/%.o: ../src/Test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


