/*
 * I2c.c
 *
 *  Created on: Jul 6, 2022
 *      Author: Seko
 */
#include "I2C.h"

//static void (*I2C_Callback_Func)(void);


/*Master  TWBR register Value to acheive the required SCL Frequency (Clock Freq) depend on Prescaler*/
/* Calculate the TWBR_Value from the equation in DataSheet*/
/*Set Value of prescalar according to the required value need in SCL and that also give TWBR_Value in range from 0 to 255*/

void I2C_Master_init(u8 TWBR_Value,u8 Master_address)
{

	#if defined Master_Prescaler_1
		CLEAR_BIT(TWSR,TWPS0);
		CLEAR_BIT(TWSR,TWPS1);
		#elif defined Master_Prescaler_4
		SET_BIT(TWSR,TWPS0);
		CLEAR_BIT(TWSR,TWPS1);
		#elif defined Master_Prescaler_16
		CLEAR_BIT(TWSR,TWPS0);
		SET_BIT(TWSR,TWPS1);
		#elif defined Master_Prescaler_64
		SET_BIT(TWSR,TWPS0);
		SET_BIT(TWSR,TWPS1);
	#endif
	TWBR = TWBR_Value; //Define the value from data sheet
	/* initialize the address of the master*/
	#if defined Master_Not_Addressed
		TWAR =  (Master_address & 0X00);
	#elif defined Master_Addressed
		TWAR = (Master_address & 0XFE) ;
	#endif

	#if defined I2C_Master_Recognize_GeneralCall
		SET_BIT(TWAR,TWGCE);
		#elif defined I2C_Master_Not_Recognize_GeneralCall
		CLEAR_BIT(TWAR,TWGCE);
	#endif
	#if defined Master_Enable_ACK_Bit
		SET_BIT(TWCR,TWEA);	// Master used it when master is a receiver
	#elif defined Master_Disable_ACK_Bit
	CLEAR_BIT(TWCR,TWEA);
	#endif
	/*Enable the I2C*/
	SET_BIT(TWCR,TWEN);
}

void I2C_Slave_init(u8 Slave_address)
{
	/* initialize the address of the master*/
	TWAR = (Slave_address  & 0XFE) ;
	#if defined I2C_Slave_Recognize_GeneralCall
		SET_BIT(TWAR,TWGCE);
		#elif defined I2C_Slave_Not_Recognize_GeneralCall
		CLEAR_BIT(TWAR,TWGCE);
	#endif

	#if defined Slave_Enable_ACK_Bit
		SET_BIT(TWCR,TWEA);	// Master used it when master is a receiver
	#elif defined Slave_Disable_ACK_Bit
	CLEAR_BIT(TWCR,TWEA);
	#endif
	/*Enable the I2C*/
	SET_BIT(TWCR,TWEN);
}

STD_Return I2C_Interrupt_Enable(I2C_Interrupt_Enable_t state)
{
	switch (state)
	{
		case I2C_Enable_Interrupt:
			SET_BIT(TWCR,TWIE);
			break;
		case I2C_Disable_Interrupt:
			CLEAR_BIT(TWCR,TWIE);
			break;
		default:
			return E_OK;
	}
	return E_NOK;
}

I2C_Error_States_t I2C_Start_Condtion_Polling(void)
{
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);
	if((TWSR & 0XF8) != START_ACK)
	{
		return 	I2C_StartCondition_Error;
	}
	else
	{
		CLEAR_BIT(TWCR,TWSTA);
		return I2C_NO_Error;
	}
}

I2C_Error_States_t I2C_RepeatedStart_Condtion_Polling(void)
{
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);
	if((TWSR & 0XF8) != REP_START_ACK)
	{
		return 	I2C_RepeatedStartCondition_Error;
	}
	else
	{
		CLEAR_BIT(TWCR,TWSTA);
		return I2C_NO_Error;
	}
}

void I2C_Stop_Condition(void)
{
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTO);
}

I2C_Error_States_t I2C_SlaveAddressWrite_MasterTransmitterMode_Polling(u8 Slave_address)
{
	TWDR = ((Slave_address << 1)|Write_Mode);
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);
#if defined Status_With_ACK

	if((TWSR & 0XF8) == MasterSend_SLA_WRR_ACK)
	{
		return 	I2C_SlaveAddress_ACK_Write_Error;
	}
#elif defined Status_With_NACK
	{
		if((TWSR & 0XF8) != MasterSend_SLA_WRR_NACK)
		{
			return 	I2C_SlaveAddress_NACK_Write_Error;
		}
	}
#endif
	else
	{
		return I2C_NO_Error;
	}
}

I2C_Error_States_t I2C_SlaveAddressRead_MasterReceiverMode_Polling(u8 Slave_address)
{
	TWDR = ((Slave_address << 1)|Read_Mode);
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT) == 0);
#if defined Status_With_ACK

	if((TWSR & 0XF8) == MasterSend_SLA_RDR_ACK)
	{
		return 	I2C_SlaveAddress_ACK_Read_Error;
	}
#elif defined Status_With_NACK
	{
		if((TWSR & 0XF8) != MasterSend_SLA_RDR_NACK)
		{
			return 	I2C_SlaveAddress_NACK_Read_Error;
		}
	}
#endif
	else
	{
		return I2C_NO_Error;
	}
}

I2C_Error_States_t I2C_MasterTransmitter_WriteData_Polling(u8 Sended_Data)
{

	TWDR = Sended_Data;
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT)==0);

#if defined Status_With_ACK

	if((TWSR & 0XF8) == MasterSend_DataByte_ACK)
	{

		return 	I2C_MasterByte_ACK_Write_Error;
	}
#elif defined Status_With_NACK
	{
		if((TWSR & 0XF8) != MasterSend_DataByte_NACK)
		{
			return 	I2C_MasterByte_NACK_Write_Error;
		}
	}
#endif
	else
	{
		return I2C_NO_Error;
	}
}

I2C_Error_States_t I2C_MasterReceiver_ReceiveData_Polling(u8 *Received_Data)
{
	SET_BIT(TWCR,TWINT);

	while(GET_BIT(TWCR,TWINT)==0);

	#if defined Status_With_ACK

	if((TWSR & 0XF8) == MasterReceive_DataByte_ACK)
	{
		return 	I2C_MasterByte_ACK_Write_Error;
	}
#elif defined Status_With_NACK
	{
		if((TWSR & 0XF8) != MasterReceive_DataByte_NACK)
		{
			return 	I2C_MasterByte_NACK_Write_Error;
		}
	}
#endif
	else
	{

		*Received_Data = TWDR;
		return I2C_NO_Error;
	}
}

void I2C_TransmiterMaster_Writebyte(u8 device_address,u8 Data_Location,u8 data)
{
	I2C_Start_Condtion_Polling();
	I2C_SlaveAddressWrite_MasterTransmitterMode_Polling(device_address);
	I2C_MasterTransmitter_WriteData_Polling(Data_Location);
	I2C_MasterTransmitter_WriteData_Polling(data);
}
void I2C_TransmiterMaster_Rewritebyte(u8 device_address,u8 Data_Location,u8 data)
{
	I2C_RepeatedStart_Condtion_Polling();
	I2C_SlaveAddressWrite_MasterTransmitterMode_Polling(device_address);
	I2C_MasterTransmitter_WriteData_Polling(data);
}

