################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ActionDescription/CompositeActions/CompositeActionWalk.cpp 

OBJS += \
./src/ActionDescription/CompositeActions/CompositeActionWalk.o 

CPP_DEPS += \
./src/ActionDescription/CompositeActions/CompositeActionWalk.d 


# Each subdirectory must supply rules for building sources it contributes
src/ActionDescription/CompositeActions/%.o: ../src/ActionDescription/CompositeActions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


