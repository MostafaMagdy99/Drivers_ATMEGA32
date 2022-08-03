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
#define Write_Mode				0
#define Read_Mode				1

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

}I2C_Error_States_t;

typedef enum
{
	I2C_Enable_Interrupt,
	I2C_Disable_Interrupt
}I2C_Interrupt_Enable_t;



/* Pass 0 in MasterAddress if Master will not be addressed or master no one will send data to it*/
void I2C_Master_init(u8 TWBR_Value,u8 Master_address); //Address For Master mode it is the Id when the master is in receive mode
void I2C_Slave_init(u8 Slave_address);//Address for Slave mode its ID which master call it

STD_Return I2C_Interrupt_Enable(I2C_Interrupt_Enable_t state);

I2C_Error_States_t I2C_Start_Condtion_Polling(void);
I2C_Error_States_t I2C_RepeatedStart_Condtion_Polling(void);
void I2C_Stop_Condition(void);

I2C_Error_States_t I2C_SlaveAddressWrite_MasterTransmitterMode_Polling(u8 Slave_address);
I2C_Error_States_t I2C_SlaveAddressRead_MasterReceiverMode_Polling(u8 Slave_address);

I2C_Error_States_t I2C_MasterTransmitter_WriteData_Polling(u8 Sended_Data);
I2C_Error_States_t I2C_MasterReceiver_ReceiveData_Polling(u8 *Received_Data);

void I2C_TransmiterMaster_Writebyte(u8 device_address,u8 Data_Location,u8 data);
void I2C_TransmiterMaster_Rewritebyte(u8 device_address,u8 Data_Location,u8 data);

void I2C_read_byte(u8 device_address,u8 *data,u8 data_Loc);
void I2C_Reread_byte(u8 device_address,u8 *data,u8 data_Loc);

void I2C_Callback(void (*func_ptr)(void));


#endif /* MCAL_I2C_I2C_H_ */
