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


void main(void)
{
	static u8 var;

	SPI_init();

	DIO_SetPinDirection(DIO_PORTC,0,DIO_OUTPUT);
	DIO_SetPinValue(DIO_PORTC,0,DIO_LOW);

	SPI_MasterSlave_Selection(SPI_SLAVE);
	while(1)
	{

		SPI_Receive_Data(&var);
		 _delay_ms(10);
		 if (var == 10)
		 {
			 DIO_SetPinValue(DIO_PORTC,0,DIO_HIGH);
		 }
	}
}
