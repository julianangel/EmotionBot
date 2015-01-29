################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general_execution/SimpleActionExecution.cpp \
../src/general_execution/SimpleActionTrajectoryExecution.cpp 

OBJS += \
./src/general_execution/SimpleActionExecution.o \
./src/general_execution/SimpleActionTrajectoryExecution.o 

CPP_DEPS += \
./src/general_execution/SimpleActionExecution.d \
./src/general_execution/SimpleActionTrajectoryExecution.d 


# Each subdirectory must supply rules for building sources it contributes
src/general_execution/%.o: ../src/general_execution/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


