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
all: TDII_TPO_Medidor_PA_v1.0.axf

# Tool invocations
TDII_TPO_Medidor_PA_v1.0.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/federico/Escritorio/Workspace/LPC_BaseBoardBB1769_R02/Debug" -L"/home/federico/Escritorio/Workspace/LibFreeRTOS_8.2.3/Debug" -L"/home/federico/Escritorio/Workspace/lpc_chip_175x_6x/Debug" -Xlinker -Map="TDII_TPO_Medidor_PA_v1.0.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "TDII_TPO_Medidor_PA_Debug.ld" -o "TDII_TPO_Medidor_PA_v1.0.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) TDII_TPO_Medidor_PA_v1.0.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "TDII_TPO_Medidor_PA_v1.0.axf"; # arm-none-eabi-objcopy -v -O binary "TDII_TPO_Medidor_PA_v1.0.axf" "TDII_TPO_Medidor_PA_v1.0.bin" ; # checksum -p LPC1769 -d "TDII_TPO_Medidor_PA_v1.0.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
