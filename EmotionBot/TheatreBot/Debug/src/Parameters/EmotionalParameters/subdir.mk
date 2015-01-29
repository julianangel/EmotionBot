################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Parameters/EmotionalParameters/EmotionMovementParameter.cpp \
../src/Parameters/EmotionalParameters/EmotionParameter.cpp 

OBJS += \
./src/Parameters/EmotionalParameters/EmotionMovementParameter.o \
./src/Parameters/EmotionalParameters/EmotionParameter.o 

CPP_DEPS += \
./src/Parameters/EmotionalParameters/EmotionMovementParameter.d \
./src/Parameters/EmotionalParameters/EmotionParameter.d 


# Each subdirectory must supply rules for building sources it contributes
src/Parameters/EmotionalParameters/%.o: ../src/Parameters/EmotionalParameters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


