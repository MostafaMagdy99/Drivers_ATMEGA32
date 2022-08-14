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

u8 Svar ;
void main (void)
{
	I2C_init_Salve(0x20); // the TWBR that made the required speed , and the address of the master

	 DIO_SetPortDirection(DIO_PORTA,PORT_OUTPUT);
	 DIO_SetPortValue(DIO_PORTA,PORT_LOW);

		//I2C_Interrupt_Enable(I2C_Enable);
		//Enable_Global_Interrupt(Enable_GIE_Interrupt);
	 I2C_SalveListenToBus();
	 I2C_SalveReceiveData(&Svar);
while(1)
{
	 DIO_SetPortValue(DIO_PORTA,Svar);


//	DIO_SetPortValue(DIO_PORTA,SVar);


}
}

