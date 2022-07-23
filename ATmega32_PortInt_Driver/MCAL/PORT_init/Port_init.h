/*
 * Port_init.h
 *
 *  Created on: Jul 23, 2022
 *      Author: Seko
 */

#ifndef MCAL_PORT_INIT_PORT_INIT_H_
#define MCAL_PORT_INIT_PORT_INIT_H_

#include "../../LIB/STD_Types.h"
#include "Port_init_CFG.h"

#include "../../SERVICE/DIO_register.h"

#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)			CONC_Helper(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_Helper(b7,b6,b5,b4,b3,b2,b1,b0)	0b##b7##b6##b5##b4##b3##b2##b1##b0

#define PORTA_init_Direction		CONC(PORTA_Pin7_Direction,PORTA_Pin6_Direction,PORTA_Pin5_Direction,PORTA_Pin4_Direction,PORTA_Pin3_Direction,PORTA_Pin2_Direction,PORTA_Pin1_Direction,PORTA_Pin0_Direction)
#define PORTA_init_Value			CONC(PORTA_Pin7_Value,PORTA_Pin6_Value,PORTA_Pin5_Value,PORTA_Pin4_Value,PORTA_Pin3_Value,PORTA_Pin2_Value,PORTA_Pin1_Value,PORTA_Pin0_Value)


#define PORTB_init_Direction		CONC(PORTB_Pin7_Direction,PORTB_Pin6_Direction,PORTB_Pin5_Direction,PORTB_Pin4_Direction,PORTB_Pin3_Direction,PORTB_Pin2_Direction,PORTB_Pin1_Direction,PORTB_Pin0_Direction)
#define PORTB_init_Value			CONC(PORTB_Pin7_Value,PORTB_Pin6_Value,PORTB_Pin5_Value,PORTB_Pin4_Value,PORTB_Pin3_Value,PORTB_Pin2_Value,PORTB_Pin1_Value,PORTB_Pin0_Value)

#define PORTC_init_Direction		CONC(PORTC_Pin7_Direction,PORTC_Pin6_Direction,PORTC_Pin5_Direction,PORTC_Pin4_Direction,PORTC_Pin3_Direction,PORTC_Pin2_Direction,PORTC_Pin1_Direction,PORTC_Pin0_Direction)
#define PORTC_init_Value			CONC(PORTC_Pin7_Value,PORTC_Pin6_Value,PORTC_Pin5_Value,PORTC_Pin4_Value,PORTC_Pin3_Value,PORTC_Pin2_Value,PORTC_Pin1_Value,PORTC_Pin0_Value)

#define PORTD_init_Direction		CONC(PORTD_Pin7_Direction,PORTD_Pin6_Direction,PORTD_Pin5_Direction,PORTD_Pin4_Direction,PORTD_Pin3_Direction,PORTD_Pin2_Direction,PORTD_Pin1_Direction,PORTD_Pin0_Direction)
#define PORTD_init_Value			CONC(PORTD_Pin7_Value,PORTD_Pin6_Value,PORTD_Pin5_Value,PORTD_Pin4_Value,PORTD_Pin3_Value,PORTD_Pin2_Value,PORTD_Pin1_Value,PORTD_Pin0_Value)

void PORT_init(void);

#endif /* MCAL_PORT_INIT_PORT_INIT_H_ */

