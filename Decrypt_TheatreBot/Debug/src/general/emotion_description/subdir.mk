################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general/emotion_description/ActionChanges.cpp \
../src/general/emotion_description/EmotionProfile.cpp 

OBJS += \
./src/general/emotion_description/ActionChanges.o \
./src/general/emotion_description/EmotionProfile.o 

CPP_DEPS += \
./src/general/emotion_description/ActionChanges.d \
./src/general/emotion_description/EmotionProfile.d 


# Each subdirectory must supply rules for building sources it contributes
src/general/emotion_description/%.o: ../src/general/emotion_description/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


