################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ActionModulation/ActionAddition.cpp \
../src/ActionModulation/ActionExecution.cpp \
../src/ActionModulation/ActionModulation.cpp \
../src/ActionModulation/ActionModulationSubSystem.cpp 

OBJS += \
./src/ActionModulation/ActionAddition.o \
./src/ActionModulation/ActionExecution.o \
./src/ActionModulation/ActionModulation.o \
./src/ActionModulation/ActionModulationSubSystem.o 

CPP_DEPS += \
./src/ActionModulation/ActionAddition.d \
./src/ActionModulation/ActionExecution.d \
./src/ActionModulation/ActionModulation.d \
./src/ActionModulation/ActionModulationSubSystem.d 


# Each subdirectory must supply rules for building sources it contributes
src/ActionModulation/%.o: ../src/ActionModulation/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


