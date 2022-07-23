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

u8 Rvar ;

void RX(void)
{
	USART_Receive_Data_Interrupt(&Rvar);
	if (Rvar =='A')
	{
		DIO_SetPinValue(DIO_PORTA,0,DIO_HIGH);
	}
}
void main(void)
{
	USART_init();

	DIO_SetPinDirection(DIO_PORTA,0,DIO_OUTPUT);
	DIO_SetPinValue(DIO_PORTA,0,DIO_LOW);
	RXC_Callback(&RX);

	Enable_Global_Interrupt(Enable_GIE_Interrupt);
	while (1)
	{

	}
}
