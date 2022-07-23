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
#include "HAL/LCD/LCD.h"
#include "util/delay.h"

	static	 u16 PeriodTicks=0;
	static	 u16	OnTicks=0;
	static	 u16	Reading1;
	static	 u16	Reading2;
	static	 u16	Reading3;

void ICU_HW(void)
{
	static u8 counter=0;
	counter++;
	if (counter==1) // indicator for Position 1
	{
		Timer1_Read_ICR_Value(&Reading1);
	}
	else if (counter==2) // indicator for Position 2
		{
		Timer1_Read_ICR_Value(&Reading2);
		PeriodTicks=Reading2-Reading1;
		Timer1_ICU_EdgeSelection(ICU_Falling_Edge);
		}
	else if (counter==3) // indicator for Position 3
	{
		Timer1_Read_ICR_Value(&Reading3);
	OnTicks=Reading3-Reading2;
	}
}
void main()
	{
			DIO_SetPinDirection(DIO_PORTB,3,DIO_OUTPUT); //TO GENERATE PWM TIMER0
			DIO_SetPinDirection(DIO_PORTD,6,DIO_INPUT);  //ICP pin to receive the ICU result

			CLCD_init();

			ICU_CallBack_Func(&ICU_HW);
			Timer1_ICU_Interrupt(Enable_ICU_Interrupt);
			Timer1_ICU_EdgeSelection(ICU_Rising_Edge);
			Timer1_init();
			Timer0_SetValue(64);
			Timer0_init();

			Enable_Global_Interrupt(Enable_GIE_Interrupt);
			while(1)
				{
				while((PeriodTicks==0)&&(OnTicks==0)); //infinity loop till period & On time measured
					CLCD_GoToXY(0,0);
					CLCD_SendWord("OnTks=");
					CLCD_Display_Decimal_Number(OnTicks);
					CLCD_GoToXY(1,0);
			    	CLCD_SendWord("PeriodTks=");
					CLCD_Display_Decimal_Number(PeriodTicks);
				}
	}
