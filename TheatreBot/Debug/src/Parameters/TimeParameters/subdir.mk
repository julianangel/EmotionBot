################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Parameters/TimeParameters/Time.cpp \
../src/Parameters/TimeParameters/Velocity.cpp 

OBJS += \
./src/Parameters/TimeParameters/Time.o \
./src/Parameters/TimeParameters/Velocity.o 

CPP_DEPS += \
./src/Parameters/TimeParameters/Time.d \
./src/Parameters/TimeParameters/Velocity.d 


# Each subdirectory must supply rules for building sources it contributes
src/Parameters/TimeParameters/%.o: ../src/Parameters/TimeParameters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

