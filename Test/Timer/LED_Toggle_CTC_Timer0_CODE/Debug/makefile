################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/Timer/subdir.mk
-include MCAL/External_Interrupt/Debug/subdir.mk
-include MCAL/External_Interrupt/subdir.mk
-include MCAL/DIO/Debug/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include MCAL/.metadata/.plugins/org.eclipse.cdt.managedbuilder.core/subdir.mk
-include MCAL/.metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include MCAL/.metadata/.metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include HAL/StopWatch/subdir.mk
-include HAL/SevenSegment_Driver/.metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include HAL/SevenSegment_Driver/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/Keypad/subdir.mk
-include HAL/.metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
LED_Toggle_CTC_Timer0.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: LED_Toggle_CTC_Timer0.elf secondary-outputs

# Tool invocations
LED_Toggle_CTC_Timer0.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,LED_Toggle_CTC_Timer0.map -mmcu=atmega32 -o "LED_Toggle_CTC_Timer0.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

LED_Toggle_CTC_Timer0.lss: LED_Toggle_CTC_Timer0.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S LED_Toggle_CTC_Timer0.elf  >"LED_Toggle_CTC_Timer0.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: LED_Toggle_CTC_Timer0.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 LED_Toggle_CTC_Timer0.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) LED_Toggle_CTC_Timer0.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
