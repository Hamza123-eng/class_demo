################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Trinamic/tmc/helpers/CRC.c \
../Trinamic/tmc/helpers/Functions.c 

OBJS += \
./Trinamic/tmc/helpers/CRC.o \
./Trinamic/tmc/helpers/Functions.o 

C_DEPS += \
./Trinamic/tmc/helpers/CRC.d \
./Trinamic/tmc/helpers/Functions.d 


# Each subdirectory must supply rules for building sources it contributes
Trinamic/tmc/helpers/CRC.o: ../Trinamic/tmc/helpers/CRC.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Trinamic/tmc -I../Trinamic/tmc/helpers -I../Trinamic/tmc/ic/TMC5130 -I../TMC5130 -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Trinamic/tmc/helpers/CRC.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Trinamic/tmc/helpers/Functions.o: ../Trinamic/tmc/helpers/Functions.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Trinamic/tmc -I../Trinamic/tmc/helpers -I../Trinamic/tmc/ic/TMC5130 -I../TMC5130 -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Trinamic/tmc/helpers/Functions.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

