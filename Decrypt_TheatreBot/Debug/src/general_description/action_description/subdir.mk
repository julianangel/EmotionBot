################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general_description/action_description/AbstractActionDescription.cpp \
../src/general_description/action_description/SequenceAbstractActionDescription.cpp \
../src/general_description/action_description/SimpleActionDescription.cpp 

OBJS += \
./src/general_description/action_description/AbstractActionDescription.o \
./src/general_description/action_description/SequenceAbstractActionDescription.o \
./src/general_description/action_description/SimpleActionDescription.o 

CPP_DEPS += \
./src/general_description/action_description/AbstractActionDescription.d \
./src/general_description/action_description/SequenceAbstractActionDescription.d \
./src/general_description/action_description/SimpleActionDescription.d 


# Each subdirectory must supply rules for building sources it contributes
src/general_description/action_description/%.o: ../src/general_description/action_description/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


