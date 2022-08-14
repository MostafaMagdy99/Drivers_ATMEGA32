/*
 * timer.h
 *
 *  Created on: May 5, 2022
 *      Author: Seko
 */

#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"
#include "../../SERVICE/DIO_register.h"
#include "../../SERVICE/Interrupt_Vector.h"
#include "timer_Config.h"

typedef enum
{
	ICU_Falling_Edge,
	ICU_Rising_Edge
}ICU_Edge_Control_t;

typedef enum
{
	Enable_ICU_Interrupt,
	Disable_ICU_Interrupt
}ICU_Interrupt_State;

void Timer0_init(void);
void Timer0_SetValue(u8 Value);
void Timer0_CallBack(void(*FUNC_PTR)(void));

void Timer1_init(void);
void Timer1_SetValueChannelA(u16 Value);	//to Set value of timer ChannelA
void Timer1_SetValueChannelB(u16 Value);	//to Set value of timer ChannelB
void Timer1_ReadValueChannelA(u16 *value);  //to Read value of timer ChannelA
void Timer1_ReadValueChannelB(u16 *value);  //to Read value of timer ChannelB
STD_Return Timer1_ICU_EdgeSelection(ICU_Edge_Control_t State); //for Edge Selection which ICU will used
STD_Return Timer1_ICU_Interrupt(ICU_Interrupt_State State); //Enable or Disable ICU interrupt
void Timer1_SetICR1_TopValue(u16 Top_Value);
void Timer1_Read_ICR_Value(u16  *value);
void ICU_CallBack_Func(void(*PTR_Func)(void));

void Timer2_init(void);
void Timer2_SetValue(u8 Value);
void Timer2_CallBack(void (*FUNC_PTR)(void));

#endif /* MCAL_TIMER_TIMER_H_ */
