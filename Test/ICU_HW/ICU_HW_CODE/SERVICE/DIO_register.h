/*
 * @file          DIO_register.h
 * @author        MostafaMagdy
 * @email         MostafaMagii7@gmail.com
 * @Git account:  https:github.com/MostafaMagdy99
 * @version       0.1
 * @date 		  2022-04-28
 * 
 * @copyright Copyright (c) 2022
 * 
 * Description :  Header file for the Atmega32 Register
 */

/*This is preprocessor Header file guard  */
#ifndef DIO_REGISTER_H_
#define DIO_REGISTER_H_

/******************************************PORTA**********************************************/
#define PORTA		*((volatile u8* const)0x3B)
#define DDRA		*((volatile u8* const)0x3A)
#define PINA		*((volatile u8* const)0x39)
/******************************************PORTB**********************************************/
#define PORTB		*((volatile u8* const)0x38)
#define DDRB		*((volatile u8* const)0x37)
#define PINB		*((volatile u8*const )0x36)
/******************************************PORTC**********************************************/
#define PORTC		*((volatile u8* const)0x35)
#define DDRC		*((volatile u8* const)0x34)
#define PINC		*((volatile u8* const)0x33)
/******************************************PORTD**********************************************/
#define PORTD		*((volatile u8* const)0x32)
#define DDRD		*((volatile u8* const)0x31)
#define PIND		*((volatile u8* const)0x30)

/***************************************Status Register****************************************/
#define SREG		*((volatile u8* const)0x5F)
/* Global_interrupt_Enable Pin (I_BIT) */
#define GIE				7 						
/********************************External interrupt Register***********************************/
#define GICR		*((volatile u8* const)0x5B)
#define INT0			6
#define INT1			7
#define INT2			5
/******************************External interrupt Flag Register********************************/
#define GIFR		*((volatile u8* const)0x5A)
#define INTF0			6
#define INTF1			7
#define INTF2			5
/***********************************Sense Control Registers*************************************/
#define MCUCR		*((volatile u8* const)0x55)
#define ISC00			0
#define ISC01			1
#define ISC10			2
#define ISC11			3

#define MCUCSR		*((volatile u8* const)0x54)
#define ISC2			6
/******************************************ADC Registers*****************************************/
#define ADMUX		*((volatile u8* const)0x27)
#define REFS1			7		//ADC select reference
#define REFS0			6		//ADC select reference
#define ADLAR			5
#define MUX4			4
#define MUX3			3
#define MUX2			2
#define MUX1			1
#define MUX0			0
/*******************************************************************************************************/
#define ADCSRA		*((volatile u8* const)0x26)
#define ADEN			7		//Enable ADC
#define ADSC			6		//Start_ADC_Conversion_Enable
#define ADATE			5		//AutoTrigger_Enable
#define ADIF			4		//ADC interrupt flag
#define ADIE			3		//ADC interrupt enable
#define ADPS2			2
#define ADPS1			1
#define ADPS0			0

#define ADCH		*((volatile u8* const)0x25)		//ADC data register high
#define ADCL		*((volatile u8* const)0x24)		//ADC data register low
/****************************************Timers Mask registers******************************************/
#define TIMSK		*((volatile u8* const)0x59) //Timer/Counter Interrupt Mask Register
#define OCIE2			7		//Timer/Counter2 Output Compare Match Interrupt Enable
#define TOIE2			6		//Timer/Counter2 Overflow Interrupt Enable
#define TICIE1			5		//Timer/Counter1, Input Capture Interrupt Enable
#define OCIE1A			4		//Timer/Counter1 Output Compare A Match Interrupt Enable
#define OCIE1B			3		//Timer/Counter1 Output Compare B Match Interrupt Enable
#define TOIE1			2		//Timer/Counter1 Overflow Interrupt Enable
#define OCIE0			1		//Timer/Counter0 Output Compare Match Interrupt Enable
#define TOIE0			0		//Timer/Counter0 Overflow Interrupt Enable
/**********************************Timer/Counter Interrupt Flag Register*******************************/
#define TIFR		*((volatile u8* const)0x58)
#define OCF2			7		//Output Compare Flag 2
#define TOV2			6		//Timer/Counter2 Overflow Flag
#define ICF1			5		//Timer/Counter1, Input Capture Flag
#define OCF1A			4		//Output Compare A Flag 1
#define OCF1B			3		//Output Compare B Flag 1
#define TOV1			2		//Timer/Counter1 Overflow Flag
#define OCF0			1		//Output Compare Flag 0
#define TOV0			0		//Timer/Counter0 Overflow Flag
/****************************************Timer 0 registers**********************************************/
#define TCCR0		*((volatile u8* const)0x53) //Timer/Counter0 Control Register
#define FOC0			7		//Force Output Compare
#define WGM00			6		//Waveform Generation Mode
#define COM01			5		//Compare Match Output Mode
#define COM00			4		//Compare Match Output Mode
#define WGM01			3		//Waveform Generation Mode
#define CS02			2		//Clock Select
#define CS01			1		//Clock Select
#define CS00			0		//Clock Select
/*************************************Timer/Counter0 Register*******************************************/
#define TCNT0		*((volatile u8* const)0x52)
/*************************************Output Compare TIMER 0 Register*****************************************/
#define OCR0		*((volatile u8* const)0x5C)
/****************************************Timer 1 registers**********************************************/
#define TCCR1A		*((volatile u8* const)0x4F) //Timer/Counter0 Control RegisterA
#define WGM10			0		//Waveform Generation Mode
#define WGM11			1		//Waveform Generation Mode
#define COM1B0			4		//Compare Match Output Mode channelB
#define COM1B1			5		//Compare Match Output Mode channelB
#define COM1A0			6		//Compare Match Output Mode channelA
#define COM1A1			7		//Compare Match Output Mode channelA
/*******************************************************************************************************/
#define TCCR1B		*((volatile u8* const)0x4E) //Timer/Counter0 Control RegisterB
#define CS10			0		//Clock Select
#define CS11			1		//Clock Select
#define CS12			2		//Clock Select
#define WGM12			3		//Waveform Generation Mode
#define WGM13			4		//Waveform Generation Mode
#define ICES1			6       //Input capture select
/************************************Output Compare TIMER 1 RegisterA************************************/
/*LOW and HIGH RegisterA*/
#define OCR1A		*((volatile u16* const)0x4A)
/************************************Output Compare TIMER 1 RegisterB************************************/
/*LOW and HIGH RegisterB*/
#define OCR1B		*((volatile u16* const)0x48)
/***************************************Capture TIMER 1 Register****************************************/
/*Input Capture Register*/
#define ICR1		*((volatile u16* const)0x46)
/*************************************Timer/Counter1 Register*******************************************/
#define TCNT1		*((volatile u16* const)0x4C)
/****************************************Timer 2 registers**********************************************/
//Timer/Counter2 Control Register
#define TCCR2		*((volatile u8* const)0x45)
#define FOC2			7		//Force Output Compare
#define WGM20			6		//Waveform Generation Mode
#define COM21			5		//Compare Match Output Mode
#define COM20			4		//Compare Match Output Mode
#define WGM21			3		//Waveform Generation Mode
#define CS22			2		//Clock Select
#define CS21			1		//Clock Select
#define CS20			0		//Clock Select
/*******************************************************************************************************/
//Asynchronous Status Register � ASSR
#define ASSR		*((volatile u8* const)0x42)
#define AS2				3		//Asynchronous Timer/Counter2
#define TCN2UB			2		//Timer/Counter2 Update Busy
#define OCR2UB			1		//Output Compare Register2 Update Busy
#define TCR2UB			0		//Timer/Counter Control Register2 Update Busy
/*******************************************************************************************************/
//Timer/Counter2 Register
#define TCNT2		*((volatile u8* const)0x44)
/*******************************************************************************************************/
//Output Compare 2 Register
#define OCR2		*((volatile u8* const)0x43)
/****************************************Timer 2 registers**********************************************/
#define WDTCR		*((volatile u8* const)0x41)
#define	WDTOE		   4		//Disable bit for the sequence of disabling WDT
#define WDE			   3		//Enable WDT
#define WDP2		   2		//WDT Prescaler bit 2
#define WDP1		   1		//WDT Prescaler bit 1
#define WDP0		   0		//WDT Prescaler bit 0
/**************************************Special function I/O Register************************************/
#define SFIOR		*((volatile u8* const)0x50)
#define PUD				2						//Pull up disable bit in SFIOR
/*******************************************************************************************************/
/*This is preprocessor Header file guard End  */
#endif /* DIO_REGISTER_H_ */
