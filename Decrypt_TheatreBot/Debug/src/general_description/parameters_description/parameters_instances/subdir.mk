################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general_description/parameters_description/parameters_instances/AreaPositionParameter.cpp \
../src/general_description/parameters_description/parameters_instances/EmotionParameter.cpp \
../src/general_description/parameters_description/parameters_instances/LandmarkPositionParameter.cpp \
../src/general_description/parameters_description/parameters_instances/ParameterAcceleration.cpp \
../src/general_description/parameters_description/parameters_instances/ParameterPosition.cpp \
../src/general_description/parameters_description/parameters_instances/ParameterTime.cpp \
../src/general_description/parameters_description/parameters_instances/ParameterTranslation.cpp \
../src/general_description/parameters_description/parameters_instances/ParameterVelocity.cpp \
../src/general_description/parameters_description/parameters_instances/PointPositionParameter.cpp 

OBJS += \
./src/general_description/parameters_description/parameters_instances/AreaPositionParameter.o \
./src/general_description/parameters_description/parameters_instances/EmotionParameter.o \
./src/general_description/parameters_description/parameters_instances/LandmarkPositionParameter.o \
./src/general_description/parameters_description/parameters_instances/ParameterAcceleration.o \
./src/general_description/parameters_description/parameters_instances/ParameterPosition.o \
./src/general_description/parameters_description/parameters_instances/ParameterTime.o \
./src/general_description/parameters_description/parameters_instances/ParameterTranslation.o \
./src/general_description/parameters_description/parameters_instances/ParameterVelocity.o \
./src/general_description/parameters_description/parameters_instances/PointPositionParameter.o 

CPP_DEPS += \
./src/general_description/parameters_description/parameters_instances/AreaPositionParameter.d \
./src/general_description/parameters_description/parameters_instances/EmotionParameter.d \
./src/general_description/parameters_description/parameters_instances/LandmarkPositionParameter.d \
./src/general_description/parameters_description/parameters_instances/ParameterAcceleration.d \
./src/general_description/parameters_description/parameters_instances/ParameterPosition.d \
./src/general_description/parameters_description/parameters_instances/ParameterTime.d \
./src/general_description/parameters_description/parameters_instances/ParameterTranslation.d \
./src/general_description/parameters_description/parameters_instances/ParameterVelocity.d \
./src/general_description/parameters_description/parameters_instances/PointPositionParameter.d 


# Each subdirectory must supply rules for building sources it contributes
src/general_description/parameters_description/parameters_instances/%.o: ../src/general_description/parameters_description/parameters_instances/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


