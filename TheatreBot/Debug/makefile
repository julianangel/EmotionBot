################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/json/subdir.mk
-include src/Test/subdir.mk
-include src/Parsers/subdir.mk
-include src/Parameters/TimeParameters/subdir.mk
-include src/Parameters/SpeakParameters/subdir.mk
-include src/Parameters/MovementParameters/subdir.mk
-include src/Parameters/EmotionalParameters/subdir.mk
-include src/Parameters/CharacterParameters/subdir.mk
-include src/Parameters/subdir.mk
-include src/LoadInformation/subdir.mk
-include src/EmotionDescription/subdir.mk
-include src/ContextDescription/subdir.mk
-include src/ActionModulation/subdir.mk
-include src/ActionDescription/SimpleActions/subdir.mk
-include src/ActionDescription/CompositeActions/subdir.mk
-include src/ActionDescription/subdir.mk
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
all: TheatreBot

# Tool invocations
TheatreBot: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "TheatreBot" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) TheatreBot
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
