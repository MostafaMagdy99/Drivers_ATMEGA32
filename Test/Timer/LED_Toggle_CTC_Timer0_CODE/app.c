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

void LED_DELAY(void)
	{
		static u16 counter=0;
		counter++;
		if(counter==4000)
		{
			DIO_togglePin(DIO_PORTB,0);
			counter=0;
		}

	}
void main()
	{
			Timer0_init();
			DIO_SetPinDirection(DIO_PORTB,0,DIO_OUTPUT);
			DIO_SetPinValue(DIO_PORTB,0,DIO_HIGH);
			Timer0_SetValue(250);
			Timer0_CallBack(&LED_DELAY);
			Enable_Global_Interrupt(Enable_GIE_Interrupt);
			while(1)
				{
				}
	}
