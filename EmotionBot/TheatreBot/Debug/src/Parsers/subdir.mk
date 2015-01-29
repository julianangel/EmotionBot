################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Parsers/EmotionParser.cpp \
../src/Parsers/ParserAction.cpp \
../src/Parsers/ParserActionParameters.cpp 

OBJS += \
./src/Parsers/EmotionParser.o \
./src/Parsers/ParserAction.o \
./src/Parsers/ParserActionParameters.o 

CPP_DEPS += \
./src/Parsers/EmotionParser.d \
./src/Parsers/ParserAction.d \
./src/Parsers/ParserActionParameters.d 


# Each subdirectory must supply rules for building sources it contributes
src/Parsers/%.o: ../src/Parsers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -g -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


