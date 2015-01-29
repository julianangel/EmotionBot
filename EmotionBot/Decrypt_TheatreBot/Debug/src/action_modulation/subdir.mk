################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/action_modulation/ActionAddition.cpp \
../src/action_modulation/ActionModification.cpp 

OBJS += \
./src/action_modulation/ActionAddition.o \
./src/action_modulation/ActionModification.o 

CPP_DEPS += \
./src/action_modulation/ActionAddition.d \
./src/action_modulation/ActionModification.d 


# Each subdirectory must supply rules for building sources it contributes
src/action_modulation/%.o: ../src/action_modulation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


