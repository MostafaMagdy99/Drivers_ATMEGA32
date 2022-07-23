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

u8 var = 'B' ;


void TX(void)
{
	USART_Transmit_Data_Interrupt(var);
}

void main(void)
{
	USART_init();

	UDRE_Callback(&TX);

	Enable_Global_Interrupt(Enable_GIE_Interrupt);
	while (1)
	{

	}
}
