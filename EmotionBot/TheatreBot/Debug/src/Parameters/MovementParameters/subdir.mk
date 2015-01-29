################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Parameters/MovementParameters/Amplitude.cpp \
../src/Parameters/MovementParameters/Circle.cpp \
../src/Parameters/MovementParameters/Landmark.cpp \
../src/Parameters/MovementParameters/Point.cpp \
../src/Parameters/MovementParameters/Position.cpp \
../src/Parameters/MovementParameters/Quaternion.cpp \
../src/Parameters/MovementParameters/Square.cpp 

OBJS += \
./src/Parameters/MovementParameters/Amplitude.o \
./src/Parameters/MovementParameters/Circle.o \
./src/Parameters/MovementParameters/Landmark.o \
./src/Parameters/MovementParameters/Point.o \
./src/Parameters/MovementParameters/Position.o \
./src/Parameters/MovementParameters/Quaternion.o \
./src/Parameters/MovementParameters/Square.o 

CPP_DEPS += \
./src/Parameters/MovementParameters/Amplitude.d \
./src/Parameters/MovementParameters/Circle.d \
./src/Parameters/MovementParameters/Landmark.d \
./src/Parameters/MovementParameters/Point.d \
./src/Parameters/MovementParameters/Position.d \
./src/Parameters/MovementParameters/Quaternion.d \
./src/Parameters/MovementParameters/Square.d 


# Each subdirectory must supply rules for building sources it contributes
src/Parameters/MovementParameters/%.o: ../src/Parameters/MovementParameters/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


