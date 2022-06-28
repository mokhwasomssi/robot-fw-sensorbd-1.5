################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/before/dot_matrix1.c \
../Core/Src/before/dot_matrix2.c 

OBJS += \
./Core/Src/before/dot_matrix1.o \
./Core/Src/before/dot_matrix2.o 

C_DEPS += \
./Core/Src/before/dot_matrix1.d \
./Core/Src/before/dot_matrix2.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/before/%.o Core/Src/before/%.su: ../Core/Src/before/%.c Core/Src/before/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Src -I../Core/Src/apps -I../Core/Src/util -I../Core/Src/before -I../Core/Src/peripheral -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-before

clean-Core-2f-Src-2f-before:
	-$(RM) ./Core/Src/before/dot_matrix1.d ./Core/Src/before/dot_matrix1.o ./Core/Src/before/dot_matrix1.su ./Core/Src/before/dot_matrix2.d ./Core/Src/before/dot_matrix2.o ./Core/Src/before/dot_matrix2.su

.PHONY: clean-Core-2f-Src-2f-before

