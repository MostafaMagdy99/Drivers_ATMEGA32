/*
 * app.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Seko
 */

#include "LIB/STD_Types.h"
#include "LIB/BIT_MATH.h"
#include "SERVICE/Interrupt_Vector.h"
#include "MCAL/External_Interrupt/External_Interrupt.h"
#include "SERVICE/DIO_register.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/SPI/SPI.h"
#include "avr/delay.h"

u8 var;

void ReciveData(void)
{
	SPI_Receive_Data_Interrupt(&var);
			 if (var == 10)
			 {
				 DIO_SetPinValue(DIO_PORTC,0,DIO_HIGH);
			 }
}

void main(void)
{

	SPI_init();

	SPI_MasterSlave_Selection(SPI_SLAVE);
	SPI_Interrupt_State(SPI_Interrupt_Enable);
	STC_Callback(&ReciveData);

	DIO_SetPinDirection(DIO_PORTC,0,DIO_OUTPUT);
	DIO_SetPinValue(DIO_PORTC,0,DIO_LOW);


	Enable_Global_Interrupt(Enable_GIE_Interrupt);
	while(1)
	{

	}
}


