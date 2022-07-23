/*
 * SPI.c
 *
 *  Created on: Jun 28, 2022
 *      Author: Seko
 */
#include "SPI.h"

static void (*STC_Callback_Func)(void);

void SPI_init(void)
{
		SET_BIT(SPCR,SPE);
	    #if defined DataOrder_MSB
	    CLEAR_BIT(SPCR,DORD);	//leave it cleared by default or CLEAR_BIT
	    #elif defined DataOrder_LSB
	    SET_BIT(SPCR,DORD);
	    #endif

	    #if defined SCK_FREQUENCY_4
	    //leave it cleared by default
	    #elif defined SCK_FREQUENCY_16
	    SET_BIT(SPCR,SPR0);
	    #elif defined SCK_FREQUENCY_64
	    SET_BIT(SPCR,SPR1);
	    #elif defined SCK_FREQUENCY_128
	    SET_BIT(SPCR, SPR0);
	    SET_BIT(SPCR, SPR1);
	    #elif defined SPI2x_SCK_FREQUENCY_2
	    SET_BIT(SPSR,SPI2X);
	    #elif defined SPI2x_SCK_FREQUENCY_8
	    SET_BIT(SPSR,SPI2X);
	    SET_BIT(SPCR,SPR0);
	    #elif defined SPI2x_SCK_FREQUENCY_32
	    SET_BIT(SPSR,SPI2X);
	    SET_BIT(SPCR,SPR1);
	    #elif defined SPI2x_SCK_FREQUENCY_64
	    SET_BIT(SPSR,SPI2X);
	    SET_BIT(SPCR,SPR0);
	    SET_BIT(SPCR,SPR1);
	    #endif

	    #if defined Leading_Edge_Rising_Trailling_Edge_Falling
			CLEAR_BIT(SPCR,CPOL);
		#elif defined	Leading_Edge_Falling_Trailling_Edge_Rising
			SET_BIT(SPCR,CPOL);
		#endif

		//Clock phase selection
		#if defined Receive_First_Send_Second
			CLEAR_BIT(SPCR,CPHA);
		#elif defined Send_First_Receive_Second
			SET_BIT(SPCR,CPHA);
		#endif
}

STD_Return SPI_Interrupt_State(SPI_Interrupt_State_t state)
{
	switch(state)
		{
			case SPI_Interrupt_Enable:
				SET_BIT(SPCR,SPIE);
				break;
			case SPI_Interrupt_Disable:
				CLEAR_BIT(SPCR,SPIE);
				break;
			default:
		       return E_OK;
		}
	return E_NOK;
}

STD_Return SPI_MasterSlave_Selection(SPI_Mode_Selection_t mode)
{
    switch (mode)
		{

    		case SPI_MASTER:
				SET_BIT(SPCR,MSTR);

    				break;
			case SPI_SLAVE:
				CLEAR_BIT(SPCR,MSTR);
				break;

			default:
				return E_OK;
		}
	return E_NOK;
}


void SPI_Transmit_Data_Polling(u8 Trasnsmitted_Data)
{
	SPDR= Trasnsmitted_Data;
	while (IS_BIT_CLEAR(SPSR, SPIF));

}
void SPI_Receive_Data_Polling(u8 *Received_Data)
{
	while (IS_BIT_CLEAR(SPSR, SPIF));
	*Received_Data=SPDR;
}

void SPI_TranRec_Data(u8 TransmitData,u8 *ReceiveData)
{
	/*send data*/
	SPDR= TransmitData;
	/*wait till transfer completed*/
	while (GET_BIT(SPSR, SPIF)==0);
	/*receive data*/
	*ReceiveData=SPDR;
}

void SPI_Transmit_Data_Interrupt(u8 Trasnsmitted_Data)
{
	SPDR= Trasnsmitted_Data;
}
void SPI_Receive_Data_Interrupt(u8 *Received_Data)
{
	*Received_Data=SPDR;
}


void STC_Callback(void(*func_ptr)(void))
{
	STC_Callback_Func=func_ptr;
}

ISR(SPI_STC_vect)
{
	(*STC_Callback_Func)();
}
