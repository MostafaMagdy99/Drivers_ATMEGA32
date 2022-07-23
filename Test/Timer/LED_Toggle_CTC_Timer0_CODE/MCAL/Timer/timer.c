/*
 * timer.c
 *
 *  Created on: May 5, 2022
 *      Author: Seko
 */

#include "timer.h"

static void (*CTC_CallBack_Func)(void);
void Timer0_init(void)
{
	#if defined Timer0_CTC_Timer_Mode
			CLEAR_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
			SET_BIT(TIMSK,OCIE0);	//Enable Compare Output Interrupt peripheral
/***************************************CTC Mode Selection******************************************/
/*********************************Compare Output Mode/ Non PWM Mode*********************************/
			/*OC0 -> PINB3 in Atmega32*/
		#if defined Normal_PORT_Operation //OC0 Disconnected
				CLEAR_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
		#elif defined Toggle_OCO_Value
				SET_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
		#elif defined Clear_OCO_Value
				CLEAR_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
		#elif defined SET_OCR0_Value
				SET_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
		#endif
	#endif
/**************************************Timer0 Clock Prescaler Selection*****************************************/
		#if defined Timer0_Counter_Disabled
				CLEAR_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_No_Prescaler
				SET_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_8_Prescaler
				CLEAR_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_64_Prescaler
				SET_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02)
		#elif defined Timer0_CLK_256_Prescaler
				CLEAR_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_1024_Prescaler
				SET_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_External_FallingEdge_CounterMode //On Pin T0
				CLEAR_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_External_RisingEdge_CounterMode //On Pin T0
				SET_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS02);
		#endif
}
void Timer0_SetValue(u8 Value)
{
#if defined Timer0_Normal_Timer_Mode
	TCNT0 = Value; //Set Overflow Value
#elif defined Timer0_CTC_Timer_Mode
	OCR0 = Value; //Set Compare Output Value
#elif defined Timer0_Fast_PWM_Mode
	OCR0 = Value; //Set Compare Output Value to set the value of duty cycle
#endif
}

void Timer0_CallBack(void (*FUNC_PTR)(void))
{
#if defined Timer0_CTC_Timer_Mode
	CTC_CallBack_Func = FUNC_PTR;
#endif
}

ISR(TIMER0_COMP_vect)
{
	CTC_CallBack_Func();
}
