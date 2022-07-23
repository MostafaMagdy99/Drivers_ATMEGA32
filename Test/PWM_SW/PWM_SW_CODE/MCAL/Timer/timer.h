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
#endif /* MCAL_TIMER_TIMER_H_ */
