################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Parameters/SpeakParameters/Speak.cpp 

OBJS += \
./src/Parameters/SpeakParameters/Speak.o 

CPP_DEPS += \
./src/Parameters/SpeakParameters/Speak.d 


# Each subdirectory must supply rules for building sources it contributes
src/Parameters/SpeakParameters/%.o: ../src/Parameters/SpeakParameters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


