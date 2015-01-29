################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/instances/platform_profiles/PlatformTest1.cpp 

OBJS += \
./src/instances/platform_profiles/PlatformTest1.o 

CPP_DEPS += \
./src/instances/platform_profiles/PlatformTest1.d 


# Each subdirectory must supply rules for building sources it contributes
src/instances/platform_profiles/%.o: ../src/instances/platform_profiles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


