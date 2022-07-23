/*
 * SPI.h
 *
 *  Created on: Jun 28, 2022
 *      Author: Seko
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include "SPI_CFG.h"
#include "../../SERVICE/DIO_register.h"
#include "../../SERVICE/Interrupt_Vector.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/External_Interrupt/External_Interrupt.h"

typedef enum
{
	SPI_Interrupt_Enable,
	SPI_Interrupt_Disable,
}SPI_Interrupt_State_t;

typedef enum
{
    SPI_SLAVE,
    SPI_MASTER
} SPI_Mode_Selection_t;


void SPI_init(void);
STD_Return SPI_Interrupt_State(SPI_Interrupt_State_t state);
STD_Return SPI_MasterSlave_Selection(SPI_Mode_Selection_t mode);
void SPI_Transmit_Data(u8 Trasnsmitted_Data);
void SPI_Receive_Data(u8 *Received_Data);
void STC_Callback(void(*func_ptr)(void)); //Serial Transfer complete SPI_Interrupt
#endif /* MCAL_SPI_SPI_H_ */
