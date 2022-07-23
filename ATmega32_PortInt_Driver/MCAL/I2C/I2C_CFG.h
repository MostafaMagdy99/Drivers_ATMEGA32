/*
 * I2C_CFG.h
 *
 *  Created on: Jul 6, 2022
 *      Author: Seko
 */

#ifndef MCAL_I2C_I2C_CFG_H_
#define MCAL_I2C_I2C_CFG_H_

#define Master_Mode
#define Slave_Mode

/*Master Prescale*/
#define Prescaler_0
#define Prescaler_1
#define Prescaler_2
#define Prescaler_3
/*Master  TWBR register Value to acheive the required SCL Frequency (Clock Freq) depend on Prescaler*/
#define TWBR_Value

//#define Master_Recognize_GeneralCall
#define Master_Not_Recognize_GeneralCall
//#define Slave_Recognize_GeneralCall
//#define Slave_Not_Recognize_GeneralCall

//#define Master_Not_Addressed
#define Master_Addressed

#define Status_With_ACK
#define Status_With_NACK
/*Master  Transmitter Mode Status Code*/
#define START_ACK						0x08 /* Start has been sent */
#define REP_START_ACK					0x10 /*Repeated Start*/
#define MasterSend_SLA_WRR_ACK			0x18 /*Master Send (SlaveAddres and Write request+ACK)*/
#define MasterSend_SLA_WRR_NACK			0x20 /*Master Send (SlaveAddres and Write request_NACK)*/
#define MasterSend_DataByte_ACK 		0x28 /*Master Send Data + ACK*/
#define MasterSend_DataByte_NACK 		0x30 /*Master Send Data + NACK*/
#define Master_Arbritration_Lost		0x38 /*Arbritration Lost in SLA+ACK or in DataByte*/

/*Master  Receiver Mode Status Code*/
#define START_ACK						0x08 /* Start has been sent */
#define REP_START_ACK					0x10 /*Repeated Start*/
#define Master_Arbritration_Lost		0x38 /*Arbritration Lost in SLA+ACK or in DataByte*/
#define MasterSend_SLA_RDR_ACK			0x40 /*Master send (SlaveAddress and Read request + ACK)*/
#define MasterSend_SLA_RDR_NACK			0x48 /*Master send (SlaveAddress and Read request + NACK)*/
#define MasterReceive_DataByte_ACK 		0x50 /*Master Receive Data + ACK*/
#define MasterReceive_DataByte_NACK 		0x58 /*Master Receive Data + NACK*/

/*Slave Transmitter Mode Status Code*/
#define SlaveReceive_SLA_R_ACK		0xA8
#define Slave_Arbritration_Lost_SLA_RW_Master_R_ACK			0xB0
#define Slave_DataByte_Transmitted_ACK	0xB8
#define Slave_DataByte_Transmitted_NACK	0xC0


/*Slave Receiver Mode Status Code*/
#define SlaveReceive_SLA_W_ACK						0x60 /*Slave receive SLA+W+ACK */
#define Slave_Arbritration_Lost_SLA_RW_Master_W_ACK			0x68 /*Arbritration Lost in SLA+ACK or in DataByte*/
#define GeneralCall_Received_ACK						0x70
#define Slave_Arbritration_Lost_GeneralCall_ACK		0x78 /*Arbritration Lost in SLA+ACK or in DataByte*/
#define Slave_DataByte_Receive_ACK					0x80
#define Slave_DataByte_Receive_NACK					0x88
#define StopCondition_RepeatedStopCondition			0xA0

#endif /* MCAL_I2C_I2C_CFG_H_ */
