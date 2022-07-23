/*
 * LCD_Config.h
 *
 *  Created on: Apr 2, 2022
 *      Author: Seko
 */

#ifndef HAL_LCD_LCD_CONFIG_H_
#define HAL_LCD_LCD_CONFIG_H_

//LCD mode selection
#define CLCD_4_BitMode	//4 Bit Mode
//#define CLCD_8_BitMode	//8 Bit Mode

//Selection of Port Used to display LCD Data/ Send Commands
//#define CLCD_DataPort	DIO_PORTA
//#define CLCD_DataPort	DIO_PORTB
#define CLCD_DataPort	DIO_PORTC
//#define CLCD_DataPort	DIO_PORTD

//For 4 bit mode
//#define DataPort	PORTA
//#define DataPort	PORTB
#define   DataPort	PORTC
//#define DataPort	PORTD

//Selection of Port Used to Control LCD
//#define CLCD_ControlPort	DIO_PORTA
#define CLCD_ControlPort	DIO_PORTB
//#define CLCD_ControlPort	DIO_PORTC
//#define CLCD_ControlPort	DIO_PORTD

//RegisterSelect pin selections
//#define CLCD_RS_PIN	7
//#define CLCD_RS_PIN	6
//#define CLCD_RS_PIN	5
//#define CLCD_RS_PIN	4
//#define CLCD_RS_PIN	3
//#define CLCD_RS_PIN	2
//#define CLCD_RS_PIN	1
#define CLCD_RS_PIN	0

//Read/Write pin selections
//#define CLCD_RW_PIN	7
//#define CLCD_RW_PIN	6
//#define CLCD_RW_PIN	5
//#define CLCD_RW_PIN	4
//#define CLCD_RW_PIN	3
//#define CLCD_RW_PIN	2
#define CLCD_RW_PIN	1
//#define CLCD_RW_PIN	0

//Enable pin selections
//#define CLCD_E_PIN	7
//#define CLCD_E_PIN	6
//#define CLCD_E_PIN	5
//#define CLCD_E_PIN	4
//#define CLCD_E_PIN	3
#define CLCD_E_PIN	2
//#define CLCD_E_PIN	1
//#define CLCD_E_PIN	0



//Data pins selections for 4_bit
// first 4 bits
#define Data_Pin0	0
#define Data_Pin1	1
#define Data_Pin2	2
#define Data_Pin3	3
// last 4 bits
#define Data_Pin4	4
#define Data_Pin5	5
#define Data_Pin6	6
#define Data_Pin7	7

//CLCD Init_FunctionSet for 8_BitMode
//#define CLCD_OneLine_5x8Size         0x30
//#define CLCD_OneLine_5x11Size        0x34
#define CLCD_TwoLines_5x8Size        0x38
//#define CLCD_TwoLines_5x11Size       0x3C

//Control Cursor
//#define CLCD_Curser_OFF
//#define CLCD_Curser_ON_NoBlinking
#define CLCD_Curser_ON_Blinking

#endif /* HAL_LCD_LCD_CONFIG_H_ */
