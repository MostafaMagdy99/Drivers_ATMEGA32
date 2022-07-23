/*
 * I2C.h
 *
 *  Created on: Jul 6, 2022
 *      Author: Seko
 */

#ifndef MCAL_I2C_I2C_H_
#define MCAL_I2C_I2C_H_

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "I2C_CFG.h"

#define Mask_Selected_Bit		0xF8
#define Read_Write				0


typedef enum
{
	I2C_ACK,
	I2C_NACK
}I2C_ACK_State_t;

typedef enum
{
	I2C_Enable,
	I2C_Disable
}I2C_Interrupt_Enable_t;
typedef enum
{
	I2C_Start_Condition,
	I2C_RepeatedStart_Condition,
	I2C_Stop_Condition
}I2C_Condition_State_t;

typedef enum
{
	I2C_SlaveAddress_Read,
	I2C_SlaveAddress_Write
}I2C_SlaveAddress_State_t;

/* Pass 0 in SlaveAddress if Master will not be addressed*/
void I2C_init(u8 address);
STD_Return I2C_Interrupt_Enable(I2C_Interrupt_Enable_t state);
STD_Return I2C_ACK_Mode(I2C_ACK_State_t state);
STD_Return I2C_Send_Condtion(I2C_Condition_State_t State);
STD_Return I2C_Slave_Address_Mode(I2C_SlaveAddress_State_t State,u8 address);
STD_Return I2C_Master_WriteData_Mode(u8 Data);
STD_Return I2C_Master_ReceiveData_Mode(u8 *Data);

#endif /* MCAL_I2C_I2C_H_ */
