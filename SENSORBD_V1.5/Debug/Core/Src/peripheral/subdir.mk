################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/peripheral/interface_board.c \
../Core/Src/peripheral/uart_test.c \
../Core/Src/peripheral/ultrasonic_HG_C40U.c 

OBJS += \
./Core/Src/peripheral/interface_board.o \
./Core/Src/peripheral/uart_test.o \
./Core/Src/peripheral/ultrasonic_HG_C40U.o 

C_DEPS += \
./Core/Src/peripheral/interface_board.d \
./Core/Src/peripheral/uart_test.d \
./Core/Src/peripheral/ultrasonic_HG_C40U.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/peripheral/%.o Core/Src/peripheral/%.su: ../Core/Src/peripheral/%.c Core/Src/peripheral/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Core/Src -I../Core/Src/apps -I../Core/Src/util -I../Core/Src/before -I../Core/Src/peripheral -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-peripheral

clean-Core-2f-Src-2f-peripheral:
	-$(RM) ./Core/Src/peripheral/interface_board.d ./Core/Src/peripheral/interface_board.o ./Core/Src/peripheral/interface_board.su ./Core/Src/peripheral/uart_test.d ./Core/Src/peripheral/uart_test.o ./Core/Src/peripheral/uart_test.su ./Core/Src/peripheral/ultrasonic_HG_C40U.d ./Core/Src/peripheral/ultrasonic_HG_C40U.o ./Core/Src/peripheral/ultrasonic_HG_C40U.su

.PHONY: clean-Core-2f-Src-2f-peripheral

