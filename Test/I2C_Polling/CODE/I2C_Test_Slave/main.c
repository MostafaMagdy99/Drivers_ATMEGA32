/*
 * main.c
 *
 *  Created on: Jul 27, 2022
 *      Author: Seko
 */

#include "MCAL/I2C/I2C.h"
#include "MCAL/DIO/DIO_interface.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_Types.h"
#include "MCAL/External_Interrupt/External_Interrupt.h"
#include "avr/delay.h"

u8 Svar;
void main (void)
{
	 DIO_SetPortDirection(DIO_PORTA,PORT_OUTPUT);
	 DIO_SetPortValue(DIO_PORTA,PORT_LOW);

		//I2C_Interrupt_Enable(I2C_Enable);
		//Enable_Global_Interrupt(Enable_GIE_Interrupt);
	 I2C_init_Master(72,0x15); // the TWBR that made the required speed , and the address of the master

	 I2C_Start_Condtion_Polling();
	I2C_Slave_WriteAddress_Mode_Polling(0x20);
	I2C_MasterWriteDataByte(0xF0);
while(1)
{

}
}

