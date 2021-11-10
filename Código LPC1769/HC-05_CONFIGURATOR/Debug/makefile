################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: HC-05_CONFIGURATOR.axf

# Tool invocations
HC-05_CONFIGURATOR.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/federico/Escritorio/Workspace/LPC_BaseBoardBB1769_R02/Debug" -L"/home/federico/Escritorio/Workspace/LibFreeRTOS_8.2.3/Debug" -L"/home/federico/Escritorio/Workspace/lpc_chip_175x_6x/Debug" -Xlinker -Map="HC-05_CONFIGURATOR.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "HC-05_CONFIGURATOR_Debug.ld" -o "HC-05_CONFIGURATOR.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) HC-05_CONFIGURATOR.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "HC-05_CONFIGURATOR.axf"; # arm-none-eabi-objcopy -v -O binary "HC-05_CONFIGURATOR.axf" "HC-05_CONFIGURATOR.bin" ; # checksum -p LPC1769 -d "HC-05_CONFIGURATOR.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
