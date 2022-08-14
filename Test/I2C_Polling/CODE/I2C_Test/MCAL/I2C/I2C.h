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
#define Read_Write_Pin				0


typedef enum
{
	I2C_NO_Error,
	 I2C_Error,
	I2C_StartCondition_Error,
	I2C_RepeatedStartCondition_Error,
	I2C_SlaveAddress_ACK_Read_Error, //Depend on the ACK Mode if ACK is is Enabled
	I2C_SlaveAddress_ACK_Write_Error, //Depend on the ACK Mode if ACK is is Enabled
	I2C_SlaveAddress_NACK_Read_Error, //Depend on the ACK Mode if ACK is is disabled
	I2C_SlaveAddress_NACK_Write_Error,  //Depend on the ACK Mode if ACK is is disabled
	I2C_MasterByte_ACK_Write_Error, //Depend on the ACK Mode if ACK is is Enabled
	I2C_MasterByte_NACK_Write_Error,//Depend on the ACK Mode if ACK is is disabled
	I2C_MasterByte_ACK_Read_Error,//Depend on the ACK Mode if ACK is is Enabled
	I2C_MasterByte_NACK_Read_Error, //Depend on the ACK Mode if ACK is is disabled
	I2C_SlaveByte_ACK_Read_Error,//Depend on the ACK Mode if ACK is is Enabled
	I2C_SlaveByte_NACK_Read_Error, //Depend on the ACK Mode if ACK is is disabled
	I2C_SlaveByte_ACK_Write_Error, //Depend on the ACK Mode if ACK is is Enabled
	I2C_SlaveByte_NACK_Write_Error,//Depend on the ACK Mode if ACK is is disabled
	I2C_SlaveLastByte_Write_Error,//Depend on the ACK Mode if ACK is is disabled
	I2C_SlaveReceive_SLA_W_ACK_Error,
	I2C_SlaveReceive_SLA_R_ACK_Error,
	I2C_Slave_Arbritration_Lost_GeneralCall_ACK_Error,
	I2C_StopCondition_Error
}I2C_Error_States_t;

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

/* Pass 0 in SlaveAddress if Master will not be addressed or master no one will send data to it*/
void I2C_init_Master(u8 TWBR_Value,u8 address); //Address for Slave mode its ID which master call it but For Master mode it is the Id when the master is in receive mode
void I2C_init_Salve(u8 address);

STD_Return I2C_Interrupt_Enable(I2C_Interrupt_Enable_t state);
I2C_Error_States_t I2C_RepeatedStart_Condtion_Polling(void);
I2C_Error_States_t I2C_Start_Condtion_Polling(void);
void I2C_Stop_Condtion_Polling(void);


I2C_Error_States_t I2C_Slave_WriteAddress_Mode_Polling(u8 SalveAddress);
I2C_Error_States_t I2C_Slave_ReadAddress_Mode_Polling(u8 address);

I2C_Error_States_t I2C_MasterWriteDataByte(u8 Data);
I2C_Error_States_t I2C_MasterReadDataByte(u8 *Data);

I2C_Error_States_t I2C_SalveReceiveData(u8 *Data);
I2C_Error_States_t I2C_SalveWriteData(u8 Data);

I2C_Error_States_t I2C_SalveListenToBus();

void I2C_Callback(void (*func_ptr)(void));
void I2C_Status_Check(u8 *Status);

#endif /* MCAL_I2C_I2C_H_ */
