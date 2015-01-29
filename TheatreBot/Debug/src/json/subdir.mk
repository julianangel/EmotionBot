################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json/jsoncpp.cpp 

OBJS += \
./src/json/jsoncpp.o 

CPP_DEPS += \
./src/json/jsoncpp.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/%.o: ../src/json/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


