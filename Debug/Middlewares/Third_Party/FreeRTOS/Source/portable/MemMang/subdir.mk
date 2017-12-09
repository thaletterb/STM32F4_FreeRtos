################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F407VGTx -DSTM32F4 -DSTM32F407G_DISC1 -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/inc" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/CMSIS/core" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/CMSIS/device" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/HAL_Driver/Inc/Legacy" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/HAL_Driver/Inc" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/ampire480272" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/ampire640480" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/Common" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/cs43l22" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/exc7200" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/ft6x06" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/ili9325" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/ili9341" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/l3gd20" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/lis302dl" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/lis3dsh" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/ls016b8uy" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/lsm303dlhc" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/mfxstm32l152" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/n25q128a" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/n25q256a" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/n25q512a" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/otm8009a" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/ov2640" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/s25fl512s" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/s5k5cag" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/st7735" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/st7789h2" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/stmpe1600" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/stmpe811" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/ts3510" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/Components/wm8994" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities" -I"/Users/brianvuong/Documents/workspace/STM32F4 Free Rtos/Utilities/STM32F4-Discovery" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


