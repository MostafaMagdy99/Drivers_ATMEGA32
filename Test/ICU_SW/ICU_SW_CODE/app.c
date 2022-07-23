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

void ICU_SW(void)
{
	static u8 counter=0;
	counter++;
	if (counter==1) // indicator for Position 1
	{
		Timer1_SetValueChannelA(0);
	}
	else if (counter==2) // indicator for Position 2
		{
		Timer1_ReadValueChannelA(&Reading1);
		PeriodTicks=Reading1;
		External_Int1_EdgeSelection(Falling_Edge_Sense);
		}
	else if (counter==3) // indicator for Position 3
	{
	Timer1_ReadValueChannelA(&Reading2);
	OnTicks=Reading2-PeriodTicks;
	//Enable_External_INT0(Disable_PIE_Interrupt);
	}
	else
		counter=0;

}
void main()
	{
			DIO_SetPinDirection(DIO_PORTB,3,DIO_OUTPUT); //TO GENERATE PWM TIMER0
			DIO_SetPinDirection(DIO_PORTD,2,DIO_INPUT);  //FOR THE EXT INT & Read Timer1 from it

			CLCD_init();

			CallBack_Int1(&ICU_SW);

			Enable_External_INT1(Enable_PIE_Interrupt);
			External_Int1_EdgeSelection(Rising_Edge_Sense);

			Timer1_init();
			Timer0_SetValue(64);
			Timer0_init();

			Enable_Global_Interrupt(Enable_GIE_Interrupt);
			while(1)
				{

				while((PeriodTicks==0)&&(OnTicks==0)); //infinity loop till period & On time measured
					CLCD_GoToXY(0,0);
					CLCD_SendWord("PeriodTicks=");
					CLCD_Display_Decimal_Number(PeriodTicks);
					CLCD_GoToXY(1,0);
					CLCD_SendWord("OnTicks=");
					CLCD_Display_Decimal_Number(OnTicks);

				}
	}
