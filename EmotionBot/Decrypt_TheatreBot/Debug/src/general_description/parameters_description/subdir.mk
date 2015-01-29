################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general_description/parameters_description/ActionParameter.cpp \
../src/general_description/parameters_description/Parameter.cpp \
../src/general_description/parameters_description/ParameterValue.cpp 

OBJS += \
./src/general_description/parameters_description/ActionParameter.o \
./src/general_description/parameters_description/Parameter.o \
./src/general_description/parameters_description/ParameterValue.o 

CPP_DEPS += \
./src/general_description/parameters_description/ActionParameter.d \
./src/general_description/parameters_description/Parameter.d \
./src/general_description/parameters_description/ParameterValue.d 


# Each subdirectory must supply rules for building sources it contributes
src/general_description/parameters_description/%.o: ../src/general_description/parameters_description/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


