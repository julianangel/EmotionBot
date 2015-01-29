################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general/parameters/ActionParameter.cpp \
../src/general/parameters/Parameter.cpp \
../src/general/parameters/ParameterValue.cpp 

OBJS += \
./src/general/parameters/ActionParameter.o \
./src/general/parameters/Parameter.o \
./src/general/parameters/ParameterValue.o 

CPP_DEPS += \
./src/general/parameters/ActionParameter.d \
./src/general/parameters/Parameter.d \
./src/general/parameters/ParameterValue.d 


# Each subdirectory must supply rules for building sources it contributes
src/general/parameters/%.o: ../src/general/parameters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


