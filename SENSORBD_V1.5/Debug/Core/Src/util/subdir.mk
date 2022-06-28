################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/util/u_bsp_driver.c \
../Core/Src/util/u_strings.c \
../Core/Src/util/u_timer.c 

OBJS += \
./Core/Src/util/u_bsp_driver.o \
./Core/Src/util/u_strings.o \
./Core/Src/util/u_timer.o 

C_DEPS += \
./Core/Src/util/u_bsp_driver.d \
./Core/Src/util/u_strings.d \
./Core/Src/util/u_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/util/%.o Core/Src/util/%.su: ../Core/Src/util/%.c Core/Src/util/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Src -I../Core/Src/apps -I../Core/Src/util -I../Core/Src/before -I../Core/Src/peripheral -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-util

clean-Core-2f-Src-2f-util:
	-$(RM) ./Core/Src/util/u_bsp_driver.d ./Core/Src/util/u_bsp_driver.o ./Core/Src/util/u_bsp_driver.su ./Core/Src/util/u_strings.d ./Core/Src/util/u_strings.o ./Core/Src/util/u_strings.su ./Core/Src/util/u_timer.d ./Core/Src/util/u_timer.o ./Core/Src/util/u_timer.su

.PHONY: clean-Core-2f-Src-2f-util

