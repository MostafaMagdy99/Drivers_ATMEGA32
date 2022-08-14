/*
 * @file 		  Interrupt_Vector.h
 * @author        MostafaMagdy
 * @email         MostafaMagii7@gmail.com
 * @Git account:  https:github.com/MostafaMagdy99
 * @version       0.1
 * @date 		  2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 *  Description :  Header file for the Interrupt vectors
 */

/*This is preprocessor Header file guard  */
#ifndef SERVICE_INTERRUPT_VECTOR_H_
#define SERVICE_INTERRUPT_VECTOR_H_
/******************************************Includes**************************************************/
#include "DIO_register.h"
/*****************************************EXT INT ISR************************************************/
#define ISR(vector, ...) \
	void vector(void) __attribute__ ((signal,used,externally_visible)) __VA_ARGS__;\
	void vector(void)
/***********************************Interrupt Vectors Section****************************************/

/*****************************************INT VECTORS************************************************/
#define INT0_Vect		__vector_1
#define INT1_Vect		__vector_2
#define INT2_Vect		__vector_3
/*****************************************ADC VECTORS************************************************/
#define ADC_Vect			__vector_16
/*****************************************Timer0 VECTORS************************************************/
#define TIMER0_COMP_vect	__vector_10
#define TIMER0_OVF_vect		__vector_11
/*****************************************Timer1 VECTORS************************************************/
#define TIMER1_ICU_vect		__vector_6
#define TIMER1_COMPA_vect	__vector_7
#define TIMER1_COMPB_vect	__vector_8
#define TIMER1_OVF_vect		__vector_9
/*****************************************Timer2 VECTORS************************************************/
#define TIMER2_COMP_vect	__vector_4
#define TIMER2_OVF_vect		__vector_5
/*****************************************USART VECTORS************************************************/
#define USART_RXC_vect			__vector_13
#define USART_UDRE_vect			__vector_14
#define USART_TXC_vect			__vector_15
/*******************************************SPI VECTORS**************************************************/
#define SPI_STC_vect			__vector_12 //Serial transfer complete STC
/*******************************************I2C VECTORS**************************************************/
#define I2C_Vect			__vector_19
/****************************************************************************************************/
/*This is preprocessor Header file guard End  */
#endif /* SERVICE_INTERRUPT_VECTOR_H_ */
