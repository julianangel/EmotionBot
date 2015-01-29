################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general_description/action_description/intance_action_description/MoveBodySimpleActionDescription.cpp \
../src/general_description/action_description/intance_action_description/MoveShoulderSimpleActionDescription.cpp 

OBJS += \
./src/general_description/action_description/intance_action_description/MoveBodySimpleActionDescription.o \
./src/general_description/action_description/intance_action_description/MoveShoulderSimpleActionDescription.o 

CPP_DEPS += \
./src/general_description/action_description/intance_action_description/MoveBodySimpleActionDescription.d \
./src/general_description/action_description/intance_action_description/MoveShoulderSimpleActionDescription.d 


# Each subdirectory must supply rules for building sources it contributes
src/general_description/action_description/intance_action_description/%.o: ../src/general_description/action_description/intance_action_description/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


