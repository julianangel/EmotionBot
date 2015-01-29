################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general_execution/action_execution/MoveBodyExecution.cpp \
../src/general_execution/action_execution/MoveShoulderExecution.cpp \
../src/general_execution/action_execution/OscillateBodyExecution.cpp \
../src/general_execution/action_execution/OscillateShoulderExecution.cpp \
../src/general_execution/action_execution/SpeakExecution.cpp 

OBJS += \
./src/general_execution/action_execution/MoveBodyExecution.o \
./src/general_execution/action_execution/MoveShoulderExecution.o \
./src/general_execution/action_execution/OscillateBodyExecution.o \
./src/general_execution/action_execution/OscillateShoulderExecution.o \
./src/general_execution/action_execution/SpeakExecution.o 

CPP_DEPS += \
./src/general_execution/action_execution/MoveBodyExecution.d \
./src/general_execution/action_execution/MoveShoulderExecution.d \
./src/general_execution/action_execution/OscillateBodyExecution.d \
./src/general_execution/action_execution/OscillateShoulderExecution.d \
./src/general_execution/action_execution/SpeakExecution.d 


# Each subdirectory must supply rules for building sources it contributes
src/general_execution/action_execution/%.o: ../src/general_execution/action_execution/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


