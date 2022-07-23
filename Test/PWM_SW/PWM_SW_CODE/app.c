/*
 * app.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Seko
 */

#include "LIB/STD_Types.h"
#include "LIB/BIT_MATH.h"
#include "SERVICE/Interrupt_Vector.h"
#include "SERVICE/DIO_register.h"
#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/Timer/timer.h"
#include "MCAL/External_Interrupt/External_Interrupt.h"

void LED_ON_OFF(void)
	{
		static u8 counter=0;
		counter++;
		if(counter==10)
		{
			DIO_SetPinValue(DIO_PORTA,1,DIO_LOW);
		}
		else if (counter==20)
		{
			DIO_SetPinValue(DIO_PORTA,1,DIO_HIGH);
			counter=0;
		}

	}
void main()
	{
			Timer0_init();
			DIO_SetPinDirection(DIO_PORTA,1,DIO_OUTPUT);
			DIO_SetPinValue(DIO_PORTA,1,DIO_LOW);
			Timer0_SetValue(250);
			Timer0_CallBack(&LED_ON_OFF);
			Enable_Global_Interrupt(Enable_GIE_Interrupt);
			while(1)
				{
				}
	}
