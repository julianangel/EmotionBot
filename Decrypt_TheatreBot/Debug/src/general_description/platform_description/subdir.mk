################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/general_description/platform_description/PlatformDescription.cpp 

OBJS += \
./src/general_description/platform_description/PlatformDescription.o 

CPP_DEPS += \
./src/general_description/platform_description/PlatformDescription.d 


# Each subdirectory must supply rules for building sources it contributes
src/general_description/platform_description/%.o: ../src/general_description/platform_description/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


