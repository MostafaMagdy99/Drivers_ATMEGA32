/*
 * I2c.c
 *
 *  Created on: Jul 6, 2022
 *      Author: Seko
 */
#include "I2C.h"

void I2C_init(u8 address)
{
	#if defined Master_Mode
	#if defined Prescaler_0
		CLEAR_BIT(TWSR,TWPS0);
		CLEAR_BIT(TWSR,TWPS1);
		TWBR_Value;
		#elif defined Prescaler_1
		SET_BIT(TWSR,TWPS0);
		CLEAR_BIT(TWSR,TWPS1);
		TWBR_Value;
		#elif defined Prescaler_2
		CLEAR_BIT(TWSR,TWPS0);
		SET_BIT(TWSR,TWPS1);
		TWBR_Value;
		#elif defined Prescaler_3
		SET_BIT(TWSR,TWPS0);
		SET_BIT(TWSR,TWPS1);
		TWBR_Value;
	#if defined Recognize_GeneralCall
		SET_BIT(TWAR,TWGCE);
		#elif defined Not_Recognize_GeneralCall
		CLEAR_BIT(TWAR,TWGCE);
	#endif

	#if defined Master_Not_Addressed
		TWAR =  0;
	#elif defined Master_Addressed
		TWAR = address << 1;
	#endif
		#endif

	#elif defined Slave_Mode
		TWAR = address << 1;
	#if defined Slave_Recognize_GeneralCall
		SET_BIT(TWAR,TWGCE);
		#elif Slave_defined Not_Recognize_GeneralCall
		CLEAR_BIT(TWAR,TWGCE);
#endif
		#endif
	SET_BIT(TWCR,TWEN);
}

STD_Return I2C_Interrupt_Enable(I2C_Interrupt_Enable_t state)
{
	switch (state)
	{
		case I2C_Enable:
			SET_BIT(TWCR,TWIE);
			break;
		case I2C_Disable:
			CLEAR_BIT(TWCR,TWIE);
			break;
		default:
			return E_OK;
	}
	return E_NOK;
}

STD_Return I2C_ACK_Mode(I2C_ACK_State_t state)
{
	switch (state)
	{
		case I2C_ACK:
			SET_BIT(TWCR,TWEA);
			break;
		case I2C_NACK:
			CLEAR_BIT(TWCR,TWEA);
			break;
		default:
			return E_OK;
	}
	return E_NOK;
}

STD_Return I2C_Send_Condtion(I2C_Condition_State_t State)
{
	switch(State)
	{
		case I2C_Start_Condition:
			/* Send Start condition*/
			SET_BIT(TWCR,TWSTA);
			/* Clear the interrupt flag to operate the start condition*/
			SET_BIT(TWCR,TWINT);
			/*wait until the interrupt flag raise again and previous operation is completed*/
			while((GET_BIT(TWCR,TWINT))==0);
			/* check operation status register*/
			if ((TWSR & Mask_Selected_Bit) != START_ACK)
			{
				return E_OK;
			}
			break;
		case I2C_RepeatedStart_Condition:
			/* Send Repeated Start condition*/
			SET_BIT(TWCR,TWSTA);
			/* Clear the interrupt flag to operate the start condition*/
			SET_BIT(TWCR,TWINT);
			/*wait until the interrupt flag raise again and previous operation is completed*/
			while((GET_BIT(TWCR,TWINT))==0);
			/* check operation status register*/
			if ((TWSR & Mask_Selected_Bit) != REP_START_ACK)
			{
				return E_OK;
			}
			break;
		case I2C_Stop_Condition:
			SET_BIT(TWCR,TWSTO);
			/* Clear the interrupt flag to operate the stop condition*/
			SET_BIT(TWCR,TWINT);
			break;
		default:
			return E_OK;
	}
	return E_NOK;
}

STD_Return I2C_Slave_Address_Mode(I2C_SlaveAddress_State_t State,u8 address)
{
	switch (State)
	{
		case I2C_SlaveAddress_Read:
			SET_BIT(TWDR,Read_Write);
			/*Set the Slave Address in the MSB 7 bits in data register*/
			TWDR = address << 1;
			/* Clear the interrupt flag to operate the Slave Start Read*/
			SET_BIT(TWCR,TWINT);
			/*wait until the interrupt flag raise again and previous operation is completed*/
			while((GET_BIT(TWCR,TWINT))==0);
#if defined Status_With_ACK
			/* check operation status register*/
			if ((TWSR & Mask_Selected_Bit) != MasterSend_SLA_RDR_ACK)
			{
				return E_OK;
			}
#elif defined Status_With_NACK
	/* check operation status register*/
	if ((TWSR & Mask_Selected_Bit) != MasterSend_SLA_RDR_NACK)
	{
		return E_OK;
	}
#endif
			break;
		case I2C_SlaveAddress_Write:
			CLEAR_BIT(TWDR,Read_Write);
			/*Set the Slave Address in the MSB 7 bits in data register*/
			TWDR = address << 1;
			/* Clear the interrupt flag to operate the start Slave Start Write*/
			SET_BIT(TWCR,TWINT);
			/*wait until the interrupt flag raise again and previous operation is completed*/
			while((GET_BIT(TWCR,TWINT))==0);
#if defined Status_With_ACK
			/* check operation status register*/
			if ((TWSR & Mask_Selected_Bit) != MasterSend_SLA_WRR_ACK)
			{
				return E_OK;
			}
#elif defined Status_With_NACK
	/* check operation status register*/
	if ((TWSR & Mask_Selected_Bit) != MasterSend_SLA_WRR_NACK)
	{
		return E_OK;
	}
#endif
			break;
		default:
			return E_OK;
	}

	return E_NOK;
}

STD_Return I2C_Master_WriteData_Mode(u8 Data)
{
	/*Write Data byte*/
	TWDR = Data;
	/* Clear the interrupt flag to operate the Master Sending Data*/
	SET_BIT(TWCR,TWINT);
	/*wait until the interrupt flag rise again and previous operation is completed*/
	while((GET_BIT(TWCR,TWINT))==0);
	/* check operation status register*/

#if defined Status_With_ACK
	if ((TWSR & Mask_Selected_Bit) != MasterSend_DataByte_ACK)
	{
		return E_OK;
	}
#elif defined Status_With_NACK
	/* check operation status register*/
	if ((TWSR & Mask_Selected_Bit) != MasterSend_DataByte_NACK)
	{
		return E_OK;
	}
#endif
	return E_NOK;
}
STD_Return I2C_Master_ReceiveData_Mode(u8 *Data)
{
	/* Clear the interrupt flag to operate the Slave Sending data Operation*/
	SET_BIT(TWCR,TWINT);
	/*wait until the interrupt flag raise again and previous operation is completed*/
	while((GET_BIT(TWCR,TWINT))==0);

#if defined Status_With_ACK
	/* check operation status register*/
	if ((TWSR & Mask_Selected_Bit) != MasterReceive_DataByte_ACK)
	{
		return E_OK;
	}
	else
		{
			/*Read Data byte after flag cleared*/
			 *Data = TWDR;
		}
#elif defined Status_With_NACK
	/* check operation status register*/
	if ((TWSR & Mask_Selected_Bit) != MasterReceive_DataByte_NACK)
	{
		return E_OK;
	}
	else
	{
		/*Read Data byte after flag cleared*/
		 *Data = TWDR;
	}
#endif

	return E_NOK;
}
