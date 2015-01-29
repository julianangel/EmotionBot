################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ActionDescription/SimpleActions/SimpleActionDoNothing.cpp \
../src/ActionDescription/SimpleActions/SimpleActionMoveBody.cpp \
../src/ActionDescription/SimpleActions/SimpleActionMoveShoulder.cpp \
../src/ActionDescription/SimpleActions/SimpleActionMoveTorso.cpp \
../src/ActionDescription/SimpleActions/SimpleActionOscillateBody.cpp \
../src/ActionDescription/SimpleActions/SimpleActionOscillateShoulder.cpp \
../src/ActionDescription/SimpleActions/SimpleActionOscillateTorso.cpp \
../src/ActionDescription/SimpleActions/SimpleActionSpeak.cpp 

OBJS += \
./src/ActionDescription/SimpleActions/SimpleActionDoNothing.o \
./src/ActionDescription/SimpleActions/SimpleActionMoveBody.o \
./src/ActionDescription/SimpleActions/SimpleActionMoveShoulder.o \
./src/ActionDescription/SimpleActions/SimpleActionMoveTorso.o \
./src/ActionDescription/SimpleActions/SimpleActionOscillateBody.o \
./src/ActionDescription/SimpleActions/SimpleActionOscillateShoulder.o \
./src/ActionDescription/SimpleActions/SimpleActionOscillateTorso.o \
./src/ActionDescription/SimpleActions/SimpleActionSpeak.o 

CPP_DEPS += \
./src/ActionDescription/SimpleActions/SimpleActionDoNothing.d \
./src/ActionDescription/SimpleActions/SimpleActionMoveBody.d \
./src/ActionDescription/SimpleActions/SimpleActionMoveShoulder.d \
./src/ActionDescription/SimpleActions/SimpleActionMoveTorso.d \
./src/ActionDescription/SimpleActions/SimpleActionOscillateBody.d \
./src/ActionDescription/SimpleActions/SimpleActionOscillateShoulder.d \
./src/ActionDescription/SimpleActions/SimpleActionOscillateTorso.d \
./src/ActionDescription/SimpleActions/SimpleActionSpeak.d 


# Each subdirectory must supply rules for building sources it contributes
src/ActionDescription/SimpleActions/%.o: ../src/ActionDescription/SimpleActions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


