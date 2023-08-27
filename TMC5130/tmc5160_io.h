#ifndef TMC5160_IO_H_
#define TMC5160_IO_H_

#include "stm32f4xx_hal.h"

void TMC5160_IO_Init(TMC5160TypeDef *TMC5160);
void TMC5160_Write_Register(TMC5160TypeDef *handle, uint8_t address, int32_t value);
int32_t TMC5160_Read_Register(TMC5160TypeDef *handle, uint8_t address);
void My_Write_Register(TMC5160TypeDef *handle, uint8_t address, int32_t value);
#endif /* TMC5160_IO_H_ */
