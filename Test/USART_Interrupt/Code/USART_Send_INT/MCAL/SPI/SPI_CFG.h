/*
 * SPI_CFG.h
 *
 *  Created on: Jun 28, 2022
 *      Author: Seko
 */

#ifndef MCAL_SPI_SPI_CFG_H_
#define MCAL_SPI_SPI_CFG_H_

//Data order register
#define DataOrder_LSB
//#define DataOrder_MSB

//SPI SCK & Oscillator Frequecy

//#define SCK_FREQUENCY_4
#define SCK_FREQUENCY_16
//#define SCK_FREQUENCY_64
//#define SCK_FREQUENCY_128
//#define SPI2x_SCK_FREQUENCY_2
//#define SPI2x_SCK_FREQUENCY_8
//#define SPI2x_SCK_FREQUENCY_32
//#define SPI2x_SCK_FREQUENCY_64

//SPI Pins Port
#define SS_PORT		DIO_PORTB
#define MOSI_PORT	DIO_PORTB
#define MISO_PORT	DIO_PORTB
#define SCK_PORT	DIO_PORTB

// SPI pins number
#define SS_PIN		4
#define MOSI_PIN	5
#define MISO_PIN	6
#define SCK_PIN		7

//Clock Polarity selection
#define Leading_Edge_Rising_Trailling_Edge_Falling
#define	Leading_Edge_Falling_Trailling_Edge_Rising
//Clock phase selection
#define Receive_First_Send_Second
#define Send_First_Receive_Second
#endif /* MCAL_SPI_SPI_CFG_H_ */
