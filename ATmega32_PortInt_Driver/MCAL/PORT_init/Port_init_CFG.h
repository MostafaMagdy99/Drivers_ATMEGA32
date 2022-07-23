/*
 * Port_init_CFG.h
 *
 *  Created on: Jul 23, 2022
 *      Author: Seko
 */

#ifndef MCAL_PORT_INIT_PORT_INIT_CFG_H_
#define MCAL_PORT_INIT_PORT_INIT_CFG_H_


/*Initialize Direction for PORTA*/
/*
 *
 * 0 for input
 * 1 for Output
 *
 */

#define PORTA_Pin0_Direction  			0
#define PORTA_Pin1_Direction            0
#define PORTA_Pin2_Direction            0
#define PORTA_Pin3_Direction            0
#define PORTA_Pin4_Direction            0
#define PORTA_Pin5_Direction            0
#define PORTA_Pin6_Direction            0
#define PORTA_Pin7_Direction            0

/*Initialize Value for PORTA*/
/*
 * if Direction Input
 * 0 for Floating
 * 1 for Enable_PullUp
 *
 * if Direction Output
 * 0 for LOW
 * 1 for HIGH
 */

#define PORTA_Pin0_Value  			0
#define PORTA_Pin1_Value            0
#define PORTA_Pin2_Value            0
#define PORTA_Pin3_Value            0
#define PORTA_Pin4_Value            0
#define PORTA_Pin5_Value            0
#define PORTA_Pin6_Value            0
#define PORTA_Pin7_Value            0

/*Initialize Direction for PORTB*/
/*
 *
 * 0 for input
 * 1 for Output
 *
 */
#define PORTB_Pin0_Direction  			0 //T0 -> External Frequency For counter / timer0
#define PORTB_Pin1_Direction            0 //T1 -> External Frequency For counter / timer0
#define PORTB_Pin2_Direction            0
#define PORTB_Pin3_Direction            0 //OC0 Timer0
#define PORTB_Pin4_Direction            0 //SS_Pin Input
#define PORTB_Pin5_Direction            0 //MOSI_Pin Master = Output / Slave = Input
#define PORTB_Pin6_Direction            0 //MISO_Pin Master = Input / Slave = Output
#define PORTB_Pin7_Direction            0 //SCK_PIN  Master = Output / Slave = Input

/*Initialize Value for PORTB*/
/*
 * if Direction Input
 * 0 for Floating
 * 1 for Enable_PullUp
 *
 * if Direction Output
 * 0 for LOW
 * 1 for HIGH
 */

#define PORTB_Pin0_Value   			     0
#define PORTB_Pin1_Value                 0
#define PORTB_Pin2_Value                 0
#define PORTB_Pin3_Value                 0
#define PORTB_Pin4_Value                 0 //SS_Pin Enable_PullUp
#define PORTB_Pin5_Value                 0
#define PORTB_Pin6_Value                 0
#define PORTB_Pin7_Value                 0

/*Initialize Direction for PORTC*/
/*
 *
 * 0 for input
 * 1 for Output
 *
 */
#define PORTC_Pin0_Direction  			 0 // RS in LCD is Output
#define PORTC_Pin1_Direction             0 // RW in LCD is Output
#define PORTC_Pin2_Direction             0 // E in LCD is Output
#define PORTC_Pin3_Direction             0
#define PORTC_Pin4_Direction             0 // Output For Data of LCD in 4 bit mode
#define PORTC_Pin5_Direction             0 // Output For Data of LCD in 4 bit mode
#define PORTC_Pin6_Direction             0 // Output For Data of LCD in 4 bit mode
#define PORTC_Pin7_Direction             0 // Output For Data of LCD in 4 bit mode

/*Initialize Value for PORTC*/
/*
 * if Direction Input
 * 0 for Floating
 * 1 for Enable_PullUp
 *
 * if Direction Output
 * 0 for LOW
 * 1 for HIGH
 */

#define PORTC_Pin0_Value  			      0
#define PORTC_Pin1_Value                  0
#define PORTC_Pin2_Value                  0
#define PORTC_Pin3_Value                  0
#define PORTC_Pin4_Value                  0
#define PORTC_Pin5_Value                  0
#define PORTC_Pin6_Value                  0
#define PORTC_Pin7_Value                  0

/*Initialize Direction for PORTD*/
/*
 *
 * 0 for input
 * 1 for Output
 *
 */
#define PORTD_Pin0_Direction  			  0 //RXD for USART
#define PORTD_Pin1_Direction              0 //TXD for USART
#define PORTD_Pin2_Direction              0
#define PORTD_Pin3_Direction              0
#define PORTD_Pin4_Direction              0 //OC1B Timer1 Register B
#define PORTD_Pin5_Direction              1 //OC1A Timer1 Register A
#define PORTD_Pin6_Direction              0 //ICP for Timer1
#define PORTD_Pin7_Direction              0 //OC2 for Timer2

/*Initialize Value for PORTD*/
/*
 * if Direction Input
 * 0 for Floating
 * 1 for Enable_PullUp
 *
 * if Direction Output
 * 0 for LOW
 * 1 for HIGH
 */

#define PORTD_Pin0_Value   			      0
#define PORTD_Pin1_Value                  0
#define PORTD_Pin2_Value                  0
#define PORTD_Pin3_Value                  0
#define PORTD_Pin4_Value                  0
#define PORTD_Pin5_Value                  0
#define PORTD_Pin6_Value                  0
#define PORTD_Pin7_Value                  0

#endif /* MCAL_PORT_INIT_PORT_INIT_CFG_H_ */
