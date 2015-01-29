################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Parameters/CharacterParameters/CharacterEmotionModification.cpp \
../src/Parameters/CharacterParameters/CharacterMovementModification.cpp 

OBJS += \
./src/Parameters/CharacterParameters/CharacterEmotionModification.o \
./src/Parameters/CharacterParameters/CharacterMovementModification.o 

CPP_DEPS += \
./src/Parameters/CharacterParameters/CharacterEmotionModification.d \
./src/Parameters/CharacterParameters/CharacterMovementModification.d 


# Each subdirectory must supply rules for building sources it contributes
src/Parameters/CharacterParameters/%.o: ../src/Parameters/CharacterParameters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


