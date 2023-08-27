#include <stdlib.h>

#include "tmc5160.h"
#include "tmc5160_io.h"
#include "delay_us.h"
#include "usart.h"
#include "main.h"

TMC5160TypeDef Motor_X;

void App_Main(void)
{
	int32_t sts = 0;

	Motor_X.CS_Port = SPI_CS_X_GPIO_Port;
	Motor_X.CS_Pin = SPI_CS_X_Pin;

	TMC5160_IO_Init(&Motor_X);

	//---->

	// My_Write_Register(&Motor_X, 0xEC, 0x000100C3);
	// My_Write_Register(&Motor_X, 0x90, 0x00061F0A);
	// My_Write_Register(&Motor_X, 0x91, 0x0000000A);
	// My_Write_Register(&Motor_X, 0x80, 0x00000004);
	// My_Write_Register(&Motor_X, 0x93, 0x000001F4);

	// My_Write_Register(&Motor_X, 0xA4, 0x000003E8);
	// My_Write_Register(&Motor_X, 0xA5, 0x0000C350);
	// My_Write_Register(&Motor_X, 0xA6, 0x000001F4);
	// My_Write_Register(&Motor_X, 0xA7, 0x00030D40);
	// My_Write_Register(&Motor_X, 0xA8, 0x000002BC);
	// My_Write_Register(&Motor_X, 0xAA, 0x00000578);
	// My_Write_Register(&Motor_X, 0xAB, 0x0000000A);
	// My_Write_Register(&Motor_X, 0xA0, 0x00000000);
	// My_Write_Register(&Motor_X, 0xAD, 0xFFFF3800);

	//_------>

	TMC5160_Set_Chopper_TOff(&Motor_X, 4);			 //
	TMC5160_Set_Chopper_Blank_Time(&Motor_X, 0b10);	 //
	TMC5160_Set_I_MAX(&Motor_X, 4);					 //
	TMC5160_Set_I_STBY(&Motor_X, 2);				 //
	TMC5160_Set_Microstep_Resolution(&Motor_X, 256); //
	TMC5160_Set_SE_Speed_THRESH(&Motor_X, 0xFFFFF);
	TMC5160_Set_SE_HSpeed_THRESH(&Motor_X, 0);
	TMC5160_Set_SE_I_MIN(&Motor_X, 5);
	TMC5160_Set_SE_HYS(&Motor_X, 2);
	TMC5160_Set_SE_I_DWN_Step(&Motor_X, 0b01);

	TMC5160_Set_ACC_A1(&Motor_X, 0x3E8);
	TMC5160_Set_ACC_MAX(&Motor_X, 0x1F4);

	TMC5160_Set_VEL_Start(&Motor_X, 100);
	TMC5160_Set_VEL_V1(&Motor_X, 0x0);
	TMC5160_Set_VEL_MAX(&Motor_X, 0x196A0);
	TMC5160_Set_VEL_Stop(&Motor_X, 0xA);

	TMC5160_Set_DEC_MAX(&Motor_X, 0x2BC);
	TMC5160_Set_DEC_D1(&Motor_X, 0x578);

	TMC5160_Set_stallGuard2_THRESH(&Motor_X, 12);
	TMC5160_Set_Auto_Right_Stop(&Motor_X, 0);
	TMC5160_Set_Auto_Left_Stop(&Motor_X, 0);
	TMC5160_Set_Auto_Left_Pol_Stop(&Motor_X, 0);
	TMC5160_Set_Auto_Right_Pol_Stop(&Motor_X, 0);


	TMC5160_Run(&Motor_X, -1000000);

	UNUSED(sts);
}
