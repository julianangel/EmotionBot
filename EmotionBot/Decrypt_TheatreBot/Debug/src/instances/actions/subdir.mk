################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/instances/actions/ActionTest1.cpp 

OBJS += \
./src/instances/actions/ActionTest1.o 

CPP_DEPS += \
./src/instances/actions/ActionTest1.d 


# Each subdirectory must supply rules for building sources it contributes
src/instances/actions/%.o: ../src/instances/actions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


