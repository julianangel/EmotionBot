################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EmotionDescription/ActionChanges.cpp \
../src/EmotionDescription/EmotionProfile.cpp 

OBJS += \
./src/EmotionDescription/ActionChanges.o \
./src/EmotionDescription/EmotionProfile.o 

CPP_DEPS += \
./src/EmotionDescription/ActionChanges.d \
./src/EmotionDescription/EmotionProfile.d 


# Each subdirectory must supply rules for building sources it contributes
src/EmotionDescription/%.o: ../src/EmotionDescription/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


