################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/instances/platform_profiles/subdir.mk
-include src/instances/emotion_profiles/subdir.mk
-include src/instances/actions/subdir.mk
-include src/general_execution/action_execution/subdir.mk
-include src/general_execution/subdir.mk
-include src/general_description/platform_description/subdir.mk
-include src/general_description/parameters_description/parameters_instances/subdir.mk
-include src/general_description/parameters_description/subdir.mk
-include src/general_description/emotion_description/subdir.mk
-include src/general_description/action_description/instance_simple_action_description/subdir.mk
-include src/general_description/action_description/instance_compound_action_description/subdir.mk
-include src/general_description/action_description/subdir.mk
-include src/action_modulation/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Decrypt_TheatreBot

# Tool invocations
Decrypt_TheatreBot: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "Decrypt_TheatreBot" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) Decrypt_TheatreBot
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
