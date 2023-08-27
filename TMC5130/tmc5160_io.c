
#include "spi.h"
#include "Macros.h"
#include "TMC5160.h"
#include "TMC5160_io.h"
#include "TMC5160_Constants.h"
#include "RegisterAccess.h"

void TMC5160_IO_Init(TMC5160TypeDef *handle)
{
    // spi configured in cube @see spi.c
    // gpio configured in cube @see gpio.c

    HAL_GPIO_WritePin(TMC_EN_GPIO_Port, TMC_EN_Pin, GPIO_PIN_RESET);

    for (size_t i = 0; i < TMC5160_REGISTER_COUNT; i++)
    {
        handle->registerAccess[i] = TMC5160_defaultRegisterAccess[i];

        // Write to the shadow
        uint8_t address = TMC_ADDRESS(i);
        handle->shadowRegister[address] = TMC5160_Read_Register(handle, address);
    }
}

void TMC5160_Write_Register(TMC5160TypeDef *handle, uint8_t address, int32_t value)
{
    uint8_t temp;
    address += TMC5160_WRITE_BIT;

    HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, &address, 1, 100);

    temp = ((value >> 24UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((value >> 16UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((value >> 8UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((value >> 0UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_SET);

    // Write to the shadow register and mark the register dirty
    address = TMC_ADDRESS(address);
    handle->shadowRegister[address] = value;
    handle->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

void My_Write_Register(TMC5160TypeDef *handle, uint8_t address, int32_t value)
{
    uint8_t temp;

    HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_Transmit(&hspi1, &address, 1, 100);

    temp = ((value >> 24UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((value >> 16UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((value >> 8UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((value >> 0UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_SET);

    // Write to the shadow register and mark the register dirty
    // address = TMC_ADDRESS(address);
    // handle->shadowRegister[address] = value;
    // handle->registerAccess[address] |= TMC_ACCESS_DIRTY;
}

// Read an integer from the given address
int32_t TMC5160_Read_Register(TMC5160TypeDef *handle, uint8_t address)
{
    uint8_t temp = 0x00;
    address = TMC_ADDRESS(address);
    int32_t val = 0;

    // register not readable -> shadow register copy
    if (!TMC_IS_READABLE(handle->registerAccess[address]))
        return handle->shadowRegister[address];

    HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &address, 1, 100);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);
    HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, &address, 1, 100);
    HAL_SPI_Receive(&hspi1, &temp, 1, 100);
    val = temp << 24;
    HAL_SPI_Receive(&hspi1, &temp, 1, 100);
    val |= temp << 16;
    HAL_SPI_Receive(&hspi1, &temp, 1, 100);
    val |= temp << 8;
    HAL_SPI_Receive(&hspi1, &temp, 1, 100);
    val |= temp << 0;
    HAL_GPIO_WritePin(handle->CS_Port, handle->CS_Pin, GPIO_PIN_SET);

    return val;
}
