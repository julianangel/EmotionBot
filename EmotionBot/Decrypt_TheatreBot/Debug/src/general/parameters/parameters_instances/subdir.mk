################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general/parameters/parameters_instances/AreaPosition.cpp \
../src/general/parameters/parameters_instances/EmotionParameter.cpp \
../src/general/parameters/parameters_instances/LandmarkPosition.cpp \
../src/general/parameters/parameters_instances/ParameterAcceleration.cpp \
../src/general/parameters/parameters_instances/ParameterPosition.cpp \
../src/general/parameters/parameters_instances/ParameterTime.cpp \
../src/general/parameters/parameters_instances/ParameterVelocity.cpp \
../src/general/parameters/parameters_instances/PointPosition.cpp 

OBJS += \
./src/general/parameters/parameters_instances/AreaPosition.o \
./src/general/parameters/parameters_instances/EmotionParameter.o \
./src/general/parameters/parameters_instances/LandmarkPosition.o \
./src/general/parameters/parameters_instances/ParameterAcceleration.o \
./src/general/parameters/parameters_instances/ParameterPosition.o \
./src/general/parameters/parameters_instances/ParameterTime.o \
./src/general/parameters/parameters_instances/ParameterVelocity.o \
./src/general/parameters/parameters_instances/PointPosition.o 

CPP_DEPS += \
./src/general/parameters/parameters_instances/AreaPosition.d \
./src/general/parameters/parameters_instances/EmotionParameter.d \
./src/general/parameters/parameters_instances/LandmarkPosition.d \
./src/general/parameters/parameters_instances/ParameterAcceleration.d \
./src/general/parameters/parameters_instances/ParameterPosition.d \
./src/general/parameters/parameters_instances/ParameterTime.d \
./src/general/parameters/parameters_instances/ParameterVelocity.d \
./src/general/parameters/parameters_instances/PointPosition.d 


# Each subdirectory must supply rules for building sources it contributes
src/general/parameters/parameters_instances/%.o: ../src/general/parameters/parameters_instances/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


