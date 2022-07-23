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
	u8 svar;
	SPI_init();

	SPI_MasterSlave_Selection(SPI_MASTER);
	while(1)
	{
		SPI_Transmit_Data(10);
		 _delay_ms(10);
	}
}
