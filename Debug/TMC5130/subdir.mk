################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TMC5130/tmc5160.c \
../TMC5130/tmc5160_io.c 

OBJS += \
./TMC5130/tmc5160.o \
./TMC5130/tmc5160_io.o 

C_DEPS += \
./TMC5130/tmc5160.d \
./TMC5130/tmc5160_io.d 


# Each subdirectory must supply rules for building sources it contributes
TMC5130/tmc5160.o: ../TMC5130/tmc5160.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Trinamic/tmc -I../Trinamic/tmc/helpers -I../Trinamic/tmc/ic/TMC5130 -I../TMC5130 -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"TMC5130/tmc5160.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
TMC5130/tmc5160_io.o: ../TMC5130/tmc5160_io.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DStartrampe -DUSE_HAL_DRIVER -DSTM32F401xE -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Trinamic/tmc -I../Trinamic/tmc/helpers -I../Trinamic/tmc/ic/TMC5130 -I../TMC5130 -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"TMC5130/tmc5160_io.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

