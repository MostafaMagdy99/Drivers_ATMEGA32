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

void Timer0_init(void);
void Timer0_SetValue(u8 Value);
void Timer0_CallBack(void(*FUNC_PTR)(void));

void Timer1_init(void);
void Timer1_SetValueChannelA(u16 Value);	//to Set value of timer ChannelA
void Timer1_SetValueChannelB(u16 Value);	//to Set value of timer ChannelB
void Timer1_SetICR1_TopValue(u16 Top_Value);
void Timer1_SetCompMatch_Value(u16 Comp_Value);

void Timer2_init(void);
void Timer2_SetValue(u8 Value);
void Timer2_CallBack(void (*FUNC_PTR)(void));

#endif /* MCAL_TIMER_TIMER_H_ */
