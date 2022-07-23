/*
 * USART.c
 *
 *  Created on: Jun 26, 2022
 *      Author: Seko
 */

#include "USART.h"

static void (*TXC_CallBackFunc)(void);
static void (*RXC_CallBackFunc)(void);
static void (*UDRE_CallBackFunc)(void);

void USART_init(void)
{
   u16 UBBR_Temp = 0;
	//Enable USART Mode
	#if defined USART_Tx_Only
	SET_BIT(UCSRB,TXEN);
	#elif defined USART_Rx_Only
	SET_BIT(UCSRB,RXEN);
	#elif defined USART_Tx_Rx
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	#endif
	//Interrupt Mode
	#if defined USART_InterruptDisable
	#elif defined USART_Rx_InterruptEnable
    SET_BIT(UCSRB,RXCIE);
	#elif defined USART_Tx_InterruptEnable
    SET_BIT(UCSRB,TXCIE);
	#elif defined USART_UDRE_InterruptEnable
    SET_BIT(UCSRB,UDRIE);
	#elif defined USART_RxComplete_TxComplete_InterruptEnable
    SET_BIT(UCSRB,RXCIE);
    SET_BIT(UCSRB,TXCIE);
	#elif defined USART_RxComplete_UDRE_InterruptEnable
    SET_BIT(UCSRB,RXCIE);
    SET_BIT(UCSRB,UDRIE);
	#elif defined USART_TxComplete_UDRE_InterruptEnable
    SET_BIT(UCSRB,TXCIE);
    SET_BIT(UCSRB,UDRIE);
	#elif defined USART_RxComplete_TxComplete_UDRE_InterruptEnable
    SET_BIT(UCSRB,RXCIE);
    SET_BIT(UCSRB,TXCIE);
    SET_BIT(UCSRB,UDRIE);
	#endif
    //ProcessorType
	#if defined USART_SingleProcessor
    CLEAR_BIT(UCSRA,MPCM);
    #elif defined USART_MultiProcessor
    SET_BIT(UCSRA,MPCM);
    #endif

    //OperationMode
    #if defined USART_Asynchronus_NormalSpeed
    UBBR_Temp=((f32)F_CPU) /((16.0)*(BaudRate))-0.5;
    SET_BIT(UCSRC,URSEL);

    #elif defined USART_Asynchronus_DoubleSpeed
    SET_BIT(UCSRC,URSEL);
    SET_BIT(UCSRA,U2x);

    #elif defined USART_Synchronus
    SET_BIT(UCSRC,URSEL);
    SET_BIT(UCSRC,UMSEL);
	#endif

    //Set BaudRate Value in UBRR Register
    UBRRH = (u16)(UBBR_Temp>>8);
    UBRRL = (u8)UBBR_Temp;

    //ClockPolarity
	#if defined USART_Recieve_Sample_OnFalling_Transmit_Sample_OnRising
    CLEAR_BIT(UCSRC,UCPOL);
	#elif defined USART_Recieve_Sample_OnRising_Transmit_Sample_OnFalling
    SET_BIT(UCSRC,UCPOL);
    #endif
    //ControlFrame
    //StopBit Number
    #if defined USART_Frame_1StopBit
    CLEAR_BIT(UCSRC,USBS);
    #elif defined USART_Frame_2StopBit
    SET_BIT(UCSRC,USBS);
    #endif
    //Parity
    #if defined USART_Frame_DisableParity
    CLEAR_BIT(UCSRC,UPM0);
    CLEAR_BIT(UCSRC,UPM1);
    #elif defined USART_Frame_EvenParity
    CLEAR_BIT(UCSRC,UPM0);
    SET_BIT(UCSRC,UPM1);
    #elif defined USART_Frame_OddParity
    SET_BIT(UCSRC,UPM0);
    SET_BIT(UCSRC,UPM1);
    #endif
    //DataFrame
    #if defined USART_5DataBit
    CLEAR_BIT(UCSRC,UCSZ0);
    CLEAR_BIT(UCSRC,UCSZ1);
    CLEAR_BIT(UCSRC,UCSZ2);
	#elif defined USART_6DataBit
    SET_BIT(UCSRC,UCSZ0);
    CLEAR_BIT(UCSRC,UCSZ1);
    CLEAR_BIT(UCSRC,UCSZ2);
	#elif defined USART_7DataBit
    CLEAR_BIT(UCSRC,UCSZ0);
    SET_BIT(UCSRC,UCSZ1);
    CLEAR_BIT(UCSRC,UCSZ2);
	#elif defined USART_8DataBit
    SET_BIT(UCSRC,UCSZ0);
    SET_BIT(UCSRC,UCSZ1);
    CLEAR_BIT(UCSRC,UCSZ2);
    #elif defined USART_9DataBit
    SET_BIT(UCSRC,UCSZ0);
    SET_BIT(UCSRC,UCSZ1);
    SET_BIT(UCSRC,UCSZ2);
    #endif

}

void USART_Transmit_Data(u8 Tx_Data)
{
	/* by using interrupt method when the UDRE ready and equal 1 start to transmit*/
	while(IS_BIT_CLEAR(UCSRA, UDRE));
		#if defined USART_5DataBit
		UDR = Tx_Data;
		#elif defined USART_6DataBit
		UDR = Tx_Data;
		#elif defined USART_7DataBit
		UDR = Tx_Data;
		#elif defined USART_8DataBit
		UDR = Tx_Data;
		#elif defined USART_9DataBit
		/*Clear bit of TXB8 and select bit no of Data 9 and shifted it TXB8 bit*/
		UCSRB |= (UCSRB & CLEAR_TXB8) | ((Tx_Data&(Select_bit_9))>>Shift_No_from_9th_DataBit_to_TXB8_bit);
		/*Rest of 9 bit data stored in the UDR Register*/
		UDR = Tx_Data;
		#endif
}
STD_Return USART_Receive_Data(u8 *Rx_Data)
{

	while(IS_BIT_CLEAR(UCSRA,RXC));
		//Error found solve by users
			if ((IS_BIT_SET(UCSRA,FE))||(IS_BIT_SET(UCSRA,DOR))||(IS_BIT_SET(UCSRA,PE)))
			{
				return E_OK;
			}
			else
			{
				#if defined USART_5DataBit
					*Rx_Data = UDR;
					#elif defined USART_6DataBit
					*Rx_Data = UDR;
					#elif defined USART_7DataBit
					*Rx_Data = UDR;
					#elif defined USART_8DataBit
					*Rx_Data = UDR;
					#elif defined USART_9DataBit
					*Rx_Data |= ((UCSRB&Select_bit_RXB8)<<Shift_No_from_RXB8_to_9th_DataBit);
					*Rx_Data |= UDR;
					#endif
	}
	return E_NOK;
}

void TXC_Callback(void(*Func_PTR)(void))
{
	TXC_CallBackFunc = Func_PTR;
}
ISR(USART_TXC_vect)
{
	(*TXC_CallBackFunc)();
}

void RXC_Callback(void(*Func_PTR)(void))
{
	RXC_CallBackFunc = Func_PTR;
}
ISR(USART_RXC_vect)
{
	(*RXC_CallBackFunc)();
}

void UDRE_Callback(void(*Func_PTR)(void))
{
	UDRE_CallBackFunc = Func_PTR;
}

ISR(USART_UDRE_vect)
{
	(*UDRE_CallBackFunc)();
}
