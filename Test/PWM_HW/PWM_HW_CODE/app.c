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
#include "util/delay.h"

void main()
	{
			u8 counter;
			Timer0_init();
			DIO_SetPinDirection(DIO_PORTB,3,DIO_OUTPUT);//OC pin O/p
			Timer0_SetValue(125);
			while(1)
				{
					for(counter=0;counter<=255;counter++)
					{
						Timer0_SetValue(counter);
						_delay_ms(10);
					}
				}
	}
