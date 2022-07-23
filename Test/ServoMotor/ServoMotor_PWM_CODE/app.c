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
			u16 counter;
			Timer1_init();
			DIO_SetPinDirection(DIO_PORTD,5,DIO_OUTPUT);//OC1 pin5 PortD O/p
			Timer1_SetICR1_TopValue(20000);


			while(1)
				{

					for(counter=120;counter<=250;counter++)
					{
						 Timer1_SetValueChannelA(counter);
							_delay_ms(10);
					}


				}
	}
