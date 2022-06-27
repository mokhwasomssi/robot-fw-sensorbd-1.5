################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/apps/app_sensorboard.c \
../Core/Src/apps/apps_init.c \
../Core/Src/apps/msgs.c 

OBJS += \
./Core/Src/apps/app_sensorboard.o \
./Core/Src/apps/apps_init.o \
./Core/Src/apps/msgs.o 

C_DEPS += \
./Core/Src/apps/app_sensorboard.d \
./Core/Src/apps/apps_init.d \
./Core/Src/apps/msgs.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/apps/%.o Core/Src/apps/%.su: ../Core/Src/apps/%.c Core/Src/apps/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Src -I../Core/Src/apps -I../Core/Src/before -I../Core/Src/peripheral -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-apps

clean-Core-2f-Src-2f-apps:
	-$(RM) ./Core/Src/apps/app_sensorboard.d ./Core/Src/apps/app_sensorboard.o ./Core/Src/apps/app_sensorboard.su ./Core/Src/apps/apps_init.d ./Core/Src/apps/apps_init.o ./Core/Src/apps/apps_init.su ./Core/Src/apps/msgs.d ./Core/Src/apps/msgs.o ./Core/Src/apps/msgs.su

.PHONY: clean-Core-2f-Src-2f-apps

