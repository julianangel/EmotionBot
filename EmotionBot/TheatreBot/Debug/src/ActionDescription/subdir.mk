################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ActionDescription/AbstractActionDescription.cpp \
../src/ActionDescription/CompositeActionDescription.cpp \
../src/ActionDescription/SimpleActionDescription.cpp 

OBJS += \
./src/ActionDescription/AbstractActionDescription.o \
./src/ActionDescription/CompositeActionDescription.o \
./src/ActionDescription/SimpleActionDescription.o 

CPP_DEPS += \
./src/ActionDescription/AbstractActionDescription.d \
./src/ActionDescription/CompositeActionDescription.d \
./src/ActionDescription/SimpleActionDescription.d 


# Each subdirectory must supply rules for building sources it contributes
src/ActionDescription/%.o: ../src/ActionDescription/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


