/*
 * I2c.c
 *
 *  Created on: Jul 6, 2022
 *      Author: Seko
 */
#include "I2C.h"
void I2C_init_Master(u8 TWBR_Value,u8 Address)
{
	/*Enable TWI*/
	SET_BIT(TWCR,TWEN);
	/*Enable ACK*/
#if defined ACK_Enable
	SET_BIT(TWCR,TWEA);
#elif defined NACK_Enable
CLEAR_BIT(TWCR,TWEA);
	#endif
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

	#if defined Master_Addressed
	/*write Address */
	TWAR=Address<<1;
	#elif defined  Master_Not_Addressed
	TWAR = 0;
	#endif

	#if defined I2C_Master_Not_Recognize_GeneralCall
	SET_BIT(TWAR,TWGCE);
	#elif defined I2C_Master_Not_Recognize_GeneralCall
	CLEAR_BIT(TWAR,TWGCE);
	#endif
}

/*TWI Initialize as a Salve*/

void I2C_init_Salve(u8 Address)
{
	/*Enable TWI*/
	SET_BIT(TWCR,TWEN);

	#if defined ACK_Enable
		SET_BIT(TWCR,TWEA);
	#elif defined NACK_Enable
	CLEAR_BIT(TWCR,TWEA);
		#endif
	/*Enable interrupt flag*/
	SET_BIT(TWCR,TWINT);
	#if defined Slave_Addressed
	/*write Address */
	TWAR=Address<<1;
	#elif defined Slave_Not_Addressed
	TWAR = 0;
	#endif
	#if defined I2C_Slave_Recognize_GeneralCall
	SET_BIT(TWAR,TWGCE);
	#elif define I2C_Slave_Not_Recognize_GeneralCall
	CLEAR_BIT(TWAR,TWGCE);
	#endif
}

/*TWI Start condition*/
I2C_Error_States_t I2C_Start_Condtion_Polling(void)
{
	/*send start condition*/
	SET_BIT(TWCR,TWSTA);
	/*Clear  TWI flag*/
	SET_BIT(TWCR,TWINT);
	/*wait until the operation finish and Flag Is Raised*/
	while(GET_BIT(TWCR,TWINT)==0);
	/*Check the operation statues of start condition*/
	if((TWSR&0xF8) != 0x08)
	{

		return I2C_StartCondition_Error;
	}
	else
	{

		return I2C_NO_Error;
	}

}
/*TWI Start Repeated Function*/
I2C_Error_States_t  I2C_RepeatedStart_Condtion_Polling(void)
{
		/*send start condition*/
		SET_BIT(TWCR,TWSTA);
		/*Clear  TWI flag*/
		SET_BIT(TWCR,TWINT);
		/*wait until the operation finish and Flag Is Rasised*/
		while(GET_BIT(TWCR,TWINT)==0);
		/*Check the operation statues*/
		if((TWSR&0xF8) != 0x10)
		{
			return I2C_RepeatedStartCondition_Error;
		}
		else
		{
			return I2C_NO_Error;
		}
}

/*TWI send  SLave Address with Write*/
I2C_Error_States_t I2C_Slave_WriteAddress_Mode_Polling(u8 SalveAddress)
{
	TWDR &= ((SalveAddress<<1)|0);                    //Address and write instruction
	CLEAR_BIT(TWCR,TWSTA);

	#if defined ACK_Enable
		SET_BIT(TWCR,TWEA);
	#elif defined NACK_Enable
	CLEAR_BIT(TWCR,TWEA);
		#endif
	SET_BIT(TWCR,TWINT);
	while(GET_BIT(TWCR,TWINT)==0);               // Wait till complete TWDR byte transmitted
#if defined Status_With_ACK
	/*Check the operation statuesSLA+W &ACK*/
	if(((TWSR)&(0xF8)) != (0x18))
	{
		return I2C_SlaveAddress_ACK_Write_Error;
	}
	else
	{
		return I2C_NO_Error;
		/*Do Nothing*/
	}
#elif defined Status_With_NACK
	/*Check the operation statuesSLA+W &NACK*/
	if((TWSR&0xF8) != 0x20)
		{
		/*Do Nothing*/
		return I2C_SlaveAddress_NACK_Write_Error;

		}
		else
		{
			return I2C_NO_Error;
			/*Do Nothing*/
		}
#endif
}

/*TWI send SLave Address with Read*/
I2C_Error_States_t I2C_Slave_ReadAddress_Mode_Polling(u8 SalveAddress)
{
	/*Send Salve Address --> 7 Bit with Read */
	TWDR &= ((SalveAddress <<1)|	SET_BIT(TWDR,Read_Write_Pin));//Address and write instruction
	/*Clear interrupt TWI Flag*/
	#if defined ACK_Enable
		SET_BIT(TWCR,TWEA);
	#elif defined NACK_Enable
	CLEAR_BIT(TWCR,TWEA);
		#endif
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	/*wait until the operation finish and Flag Is Rasised*/
	while(GET_BIT(TWCR,TWINT)==0);
#if defined Status_With_ACK
	/*Check the operation statues ACK*/
	if((TWSR&0xF8) != 0x40)
	{
		return I2C_SlaveAddress_ACK_Read_Error;
	}
	else
	{
		/*Do Nothing*/
	}
#elif defined Status_With_NACK

	/*Check the operation statues NACK*/
	if((TWSR&0xF8) != 0x48)
	{
		return I2C_SlaveAddress_NACK_Read_Error;
	}
	else
	{
		/*Do Nothing*/
	}
#endif
	return I2C_NO_Error;
}

/*TWI send data as a master*/
I2C_Error_States_t I2C_MasterWriteDataByte(u8 Data)
{
	/*Send Data */
	TWDR=Data;
	/*Clear interrupt TWI Flag*/
	#if defined ACK_Enable
		SET_BIT(TWCR,TWEA);
	#elif defined NACK_Enable
	CLEAR_BIT(TWCR,TWEA);
		#endif
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	/*wait until the operation finish and Flag Is Rasised*/
	while(GET_BIT(TWCR,TWINT)==0);
#if defined Status_With_ACK
	/*Check the operation statues data transmit with ACK*/
	if((TWSR&0xF8) != 0x28)
	{
		return I2C_MasterByte_ACK_Write_Error;
	}
	else
	{
		/*Do Nothing*/
	}
#elif defined Status_With_NACK
	/*Check the operation statues data transmit with NACK*/
		if((TWSR&0xF8) != 0x30)
		{
			return I2C_MasterByte_NACK_Write_Error;
		}
		else
		{
			/*Do Nothing*/
		}
#endif
	return I2C_NO_Error;
}

/*TWI read data as a master*/
I2C_Error_States_t I2C_MasterReadDataByte(u8 *Data)
{
	/*Clear interrupt TWI Flag*/
	#if defined ACK_Enable
		SET_BIT(TWCR,TWEA);
	#elif defined NACK_Enable
	CLEAR_BIT(TWCR,TWEA);
		#endif
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	/*wait until the operation finish and Flag Is Raised*/
	while(GET_BIT(TWCR,TWINT)==0);
#if defined Status_With_ACK
	/*Check the operation statues*/
	if((TWSR&0xF8) != 0x50)
	{
		return I2C_MasterByte_ACK_Read_Error;
	}
	else
	{
		*Data=TWDR;
	}
#elif defined Status_With_NACK
	/*Check the operation statues*/
	if((TWSR&0xF8) != 0x58)
	{
		return I2C_MasterByte_NACK_Read_Error;
	}
	else
	{
		*Data=TWDR;
	}
#endif
	return I2C_NO_Error;
}

/*Salve Listen to bus*/
I2C_Error_States_t I2C_SalveListenToBus(u8 *BusData)
{
	while(1)
	{
		/*wait until operation finish*/
		while(GET_BIT(TWCR,TWINT)==0);
		if((TWSR&0xF8) !=0x60)

		{
			return I2C_SlaveReceive_SLA_W_ACK_Error;
		}
		else
		{
		}
		/*Own SlA+R with ACK return slave transmit*/
		if((TWSR&0xF8) !=0xA8)
		{
			return 	I2C_SlaveReceive_SLA_R_ACK_Error;
		}
		else
		{

		}

		/*General Call with ACK return*/
		if((TWSR&0xF8) !=0x70)
		{
			return I2C_Slave_Arbritration_Lost_GeneralCall_ACK_Error;
		}
		else
		{

		}
		return I2C_NO_Error;
	}

}

/*Salve Receive*/
I2C_Error_States_t I2C_SalveReceiveData(u8 *Data)
{
	SET_BIT(TWCR,TWEN);
	/*Clear interrupt TWI Flag*/
	#if defined ACK_Enable
		SET_BIT(TWCR,TWEA);
	#elif defined NACK_Enable
	CLEAR_BIT(TWCR,TWEA);
		#endif
SET_BIT(TWCR,TWINT);

	/*wait until operation End */
	while(GET_BIT(TWCR,TWINT)==0);
	*Data = TWDR;

#if defined Status_With_ACK
	/*check for received data with ACK*/
	if((TWSR&0xF8)!=0x80)
	{
		return I2C_SlaveByte_ACK_Read_Error;
	}
	else
	{
		*Data = TWDR;
	}
#elif defined Status_With_NACK
	/*check for received data with NACK*/
	if((TWSR&0xF8) !=0x88)
	{
		return I2C_SlaveByte_ACK_Read_Error;
	}
	else
	{
		*Data = TWDR;
	}
#endif
	/*Check For Stop condition*/
	if((TWSR&0xF8) !=0xA0)
	{
		return I2C_StopCondition_Error;
	}
	{
		/*Clear Flag*/
		SET_BIT(TWCR,TWINT);
	}
	return I2C_NO_Error;
}


I2C_Error_States_t I2C_SalveWriteData(u8 Data)
{
	TWDR=Data;
	/*Clear interrupt TWI Flag*/
	#if defined ACK_Enable
		SET_BIT(TWCR,TWEA);
	#elif defined NACK_Enable
	CLEAR_BIT(TWCR,TWEA);
		#endif
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWEN);
	/*wait until operation End */
	while(GET_BIT(TWCR,TWINT)==0);
	/*Check For Repeated Start*/
	if((TWSR&0xF8) !=0xA0)
	{
		return I2C_RepeatedStartCondition_Error;
	}
	else
	{
		/*Clear Flag*/
		SET_BIT(TWCR,TWINT);
		return I2C_NO_Error;
	}
#if defined Status_With_ACK
	/*Check For Data Transmit And ACK */
	if((TWSR&0xF8) !=0xB8)
	{
		return I2C_SlaveByte_ACK_Write_Error;
	}
	else
	{
		return I2C_NO_Error;
	}
	/*Check for Last byte Transmit and ACK Received*/
	if((TWSR&0xF8) !=0xC8)
	{
		return I2C_SlaveLastByte_Write_Error;
	}
	else
	{

	}
#elif defined Status_With_NACK
	/*Check For Data Transmit And NACK */
	if((TWSR&0xF8) !=0xC0)
	{
		return I2C_SlaveByte_NACK_Write_Error;
	}
	else
	{
		/*Clear flag*/
		SET_BIT(TWCR,TWINT);
		return I2C_NO_Error;
	}

#endif
	return I2C_NO_Error;
}

/*TWI Stop condition*/
void I2C_Stop_Condtion_Polling(void)
{
	/*Send Stop Condition*/
	SET_BIT(TWCR,TWSTO);
	/*Clear TWI  interrupt flag*/
	SET_BIT(TWCR,TWINT);
}


void I2C_Status_Check(u8 *Status)
{
	*Status = (TWSR & (0XF8));
}
