################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/app_main.c 

OBJS += \
./App/app_main.o 

C_DEPS += \
./App/app_main.d 


# Each subdirectory must supply rules for building sources it contributes
App/app_main.o: ../App/app_main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Trinamic/tmc -I../Trinamic/tmc/helpers -I../Trinamic/tmc/ic/TMC5130 -I../TMC5130 -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"App/app_main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

