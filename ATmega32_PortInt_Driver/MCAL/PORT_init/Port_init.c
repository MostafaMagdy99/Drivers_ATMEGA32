/*
 * Port_init.c
 *
 *  Created on: Jul 23, 2022
 *      Author: Seko
 */

#include "Port_init.h"

void PORT_init(void)
{
	DDRA = PORTA_init_Direction;
	DDRB = PORTB_init_Direction;
	DDRC = PORTC_init_Direction;
	DDRD = PORTD_init_Direction;

	PORTA = PORTA_init_Value;
	PORTB = PORTB_init_Value;
	PORTC = PORTC_init_Value;
	PORTD = PORTD_init_Value;
}

