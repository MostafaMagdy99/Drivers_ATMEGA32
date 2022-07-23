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
#include "MCAL/USART/USART.h"

void main(void)
{
	USART_init();
	u8 var = ' ' ;
	while (1)
	{
		USART_Transmit_Data(var);

		USART_Receive_Data(&var);

	}
}
