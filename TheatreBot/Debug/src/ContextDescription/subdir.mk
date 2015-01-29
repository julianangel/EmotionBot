################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ContextDescription/AbstractContextDescription.cpp \
../src/ContextDescription/CompositeContextDescription.cpp \
../src/ContextDescription/SimpleContextDescription.cpp 

OBJS += \
./src/ContextDescription/AbstractContextDescription.o \
./src/ContextDescription/CompositeContextDescription.o \
./src/ContextDescription/SimpleContextDescription.o 

CPP_DEPS += \
./src/ContextDescription/AbstractContextDescription.d \
./src/ContextDescription/CompositeContextDescription.d \
./src/ContextDescription/SimpleContextDescription.d 


# Each subdirectory must supply rules for building sources it contributes
src/ContextDescription/%.o: ../src/ContextDescription/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


