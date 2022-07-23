/*
 * USART_cfg.h
 *
 *  Created on: Jun 26, 2022
 *      Author: Seko
 */

#ifndef MCAL_USART_USART_CFG_H_
#define MCAL_USART_USART_CFG_H_

//Set CPU frequency Value
#define F_CPU 8000000UL

// Set BaudRate Value
#define BaudRate 9600

//EnableMode
#define USART_Tx_Only
//#define USART_Rx_Only
//#define USART_Tx_Rx
//Interrupt Enable
//#define USART_InterruptDisable
//#define USART_Rx_InterruptEnable
//#define USART_Tx_InterruptEnable
//#define USART_RxComplete_TxComplete_InterruptEnable
//#define USART_RxComplete_UDRE_InterruptEnable
//#define USART_TxComplete_UDRE_InterruptEnable
//#define USART_RxComplete_TxComplete_UDRE_InterruptEnable
#define USART_UDRE_InterruptEnable
//ProcessorType
#define USART_SingleProcessor
//#define USART_MultiProcessor
//OperationMode
#define USART_Asynchronus_NormalSpeed
//#define USART_Asynchronus_DoubleSpeed
//#define USART_Synchronus
//ClockPolarity
//#define USART_Recieve_Sample_OnFalling_Transmit_Sample_OnRising
#define USART_Recieve_Sample_OnRising_Transmit_Sample_OnFalling

//ControlFrame
//StopBit Number
#define USART_Frame_1StopBit
//#define USART_Frame_2StopBit
//Parity
#define USART_Frame_DisableParity
//#define USART_Frame_EvenParity
//#define USART_Frame_OddParity
//DataFrame
//#define USART_5DataBit
//#define USART_6DataBit
//#define USART_7DataBit
#define USART_8DataBit
//#define USART_9DataBit


#endif /* MCAL_USART_USART_CFG_H_ */
