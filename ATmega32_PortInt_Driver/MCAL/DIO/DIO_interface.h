/*
 * @file 		  DIO_interface.h
 * @author        MostafaMagdy
 * @email         MostafaMagii7@gmail.com
 * @Git account:  https:github.com/MostafaMagdy99
 * @version       0.1
 * @date          2022-04-26
 * 
 * @copyright Copyright (c) 2022
 * 
 * Description :  Header file for the DIO driver
 */

/*This is preprocessor Header file guard  */
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/******************************************Includes**************************************************/
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_MATH.h"
#include "../../SERVICE/DIO_register.h"
/*******************************************Defintions***********************************************/
#define MAX_PinNum 	7
#define PORT_HIGH	0xff
#define PORT_LOW	0
#define NULL 0
/*****************************************************************************************************/
/**
 * @brief 
 * enum : 			user define
 * Description :	State PORTS DIO_PORTA,DIO_PORTB,DIO_PORTC,DIO_PORTD
 * 
 * _t means that it is a datatype
**/
typedef enum
	{
		DIO_PORTA,
		DIO_PORTB,
		DIO_PORTC,
		DIO_PORTD
	} DIO_Ports_t;
/*****************************************************************************************************/
/**
 * @brief 
 * enum : 			user define
 * Description :	State PinValue DIO_LOW/DIO_HIGH
 * 
 * _t means that it is a datatype
**/
typedef enum
	{
		DIO_LOW,
		DIO_HIGH
	} DIO_State_t;

/*******************************************************************************************************/
/**
 * @brief 
 * Prototype    	 	: STD_Return DIO_SetPinValue(DIO_Ports_t PORT,u8 PIN,DIO_State_t State);		  
 * Description  	 	: function for Set specific Pin in a port value High or Low
 * 
 * @param PORT 			: takes the four PORTS DIO_PORTA,DIO_PORTB,DIO_PORTC,DIO_PORTD
 * @param PIN 			: takes the number of pin in the PORT
 * @param State 		: takes the Value of the single PIN is DIO_HIGH or DIO_LOW
 * @return STD_Return	: STD_Return for Error identification
 * 
 * 							return 0 mean Error is found , return 1 mean Error is not found
 **/
STD_Return DIO_SetPinValue(DIO_Ports_t PORT,u8 PIN,DIO_State_t State);		 
/*******************************************************************************************************/
/**
 * @brief 
 * Prototype    	 	: STD_Return DIO_SetPortValue(DIO_Ports_t PORT,u8 value);
 * Description  	 	: function for Set PORT Value High or Low
 * 
 * @param PORT 			: takes the four PORTS DIO_PORTA,DIO_PORTB,DIO_PORTC,DIO_PORTD
 * @param value  		: takes the value  of all pins in the port PORT_HIGH/PORT_LOW
 * @return STD_Return	: STD_Return for Error identification
 * 
 * 						  return 0 mean Error is found , return 1 mean Error is not found
 **/
STD_Return DIO_SetPortValue(DIO_Ports_t PORT,u8 value);	 
/*******************************************************************************************************/       
/**
 * @brief 
 * Prototype    	 	: STD_Return DIO_GetPinValue(DIO_Ports_t PORT,u8 PIN,DIO_State_t* State);  
 * Description  	 	: function for storing the value of pin 
 * 
 * @param PORT 			: takes the four PORTS DIO_PORTA,DIO_PORTB,DIO_PORTC,DIO_PORTD
 * @param PIN 		    : takes the number of pin in the PORT
 * @param State 		: pointer of the state that takes the Value of the single PIN is DIO_HIGH or DIO_LOW
 * @return STD_Return	: STD_Return for Error identification
 * 
 * 						  return 0 mean Error is found , return 1 mean Error is not found
 **/
STD_Return DIO_GetPinValue(DIO_Ports_t PORT,u8 PIN,DIO_State_t* State);        
/*******************************************************************************************************/
/**
 * @brief 
 * Prototype    	 	: STD_Return DIO_togglePin(DIO_Ports_t port,u8 pin); 
 * Description  	 	: function for toggle the current value of pin 
 *  
 * @param port 			: takes the four PORTS DIO_PORTA,DIO_PORTB,DIO_PORTC,DIO_PORTD
 * @param pin 			: takes the number of pin in the PORT
 * @return STD_Return	: STD_Return for Error identification
 * 
 * 						  return 0 mean Error is found , return 1 mean Error is not found
 **/
STD_Return DIO_togglePin(DIO_Ports_t port,u8 pin);

/*******************************************************************************************************/
/*This is preprocessor Header file guard End  */
#endif /* DIO_INTERFACE_H_ */
