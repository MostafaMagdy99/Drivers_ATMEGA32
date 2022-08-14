/*
 * USART.h
 *
 *  Created on: Jun 26, 2022
 *      Author: Seko
 */

#ifndef MCAL_USART_USART_H_
#define MCAL_USART_USART_H_

#include"USART_cfg.h"
#include "../../SERVICE/DIO_register.h"
#include "../../SERVICE/Interrupt_Vector.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"
#include "../DIO/DIO_interface.h"

#define CLEAR_TXB8	0XFE
#define Shift_No_from_9th_DataBit_to_TXB8_bit 8
#define Select_bit_RXB8 (1<<RXB8)
#define Shift_No_from_RXB8_to_9th_DataBit 7
#define Select_bit_9 (1<<8)

void USART_init(void);
void USART_Transmit_Data_Polling(u8 Tx_Data);
STD_Return USART_Receive_Data_Polling(u8 *Rx_Data);

void USART_Transmit_Data_Interrupt(u8 Tx_Data);
STD_Return USART_Receive_Data_Interrupt(u8 *Rx_Data);
void TXC_Callback(void(*Func_PTR)(void));
void RXC_Callback(void(*Func_PTR)(void));
void UDRE_Callback(void(*Func_PTR)(void));

#endif /* MCAL_USART_USART_H_ */
