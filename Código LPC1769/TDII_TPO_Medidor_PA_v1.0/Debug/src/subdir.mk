################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC.c \
../src/EINT.c \
../src/ILI9340.c \
../src/PULSO.c \
../src/TDII_TPO_Medidor_PA_v1.0.c \
../src/TIMER.c \
../src/UART.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/sysinit.c 

OBJS += \
./src/ADC.o \
./src/EINT.o \
./src/ILI9340.o \
./src/PULSO.o \
./src/TDII_TPO_Medidor_PA_v1.0.o \
./src/TIMER.o \
./src/UART.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/sysinit.o 

C_DEPS += \
./src/ADC.d \
./src/EINT.d \
./src/ILI9340.d \
./src/PULSO.d \
./src/TDII_TPO_Medidor_PA_v1.0.d \
./src/TIMER.d \
./src/UART.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"/home/federico/Escritorio/Workspace/LibFreeRTOS_8.2.3/src/demo_code" -I"/home/federico/Escritorio/Workspace/LibFreeRTOS_8.2.3/src/portable/GCC/ARM_CM3" -I"/home/federico/Escritorio/Workspace/LibFreeRTOS_8.2.3/src" -I"/home/federico/Escritorio/Workspace/LibFreeRTOS_8.2.3/inc" -I"/home/federico/Escritorio/Workspace/LPC_BaseBoardBB1769_R02/inc" -I"/home/federico/Escritorio/Workspace/lpc_chip_175x_6x/inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


