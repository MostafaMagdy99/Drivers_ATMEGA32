/*
 * timer.c
 *
 *  Created on: May 5, 2022
 *      Author: Seko
 */

#include "timer.h"

static void (*Timer0_OVF_CallBack_Func)(void);
static void (*Timer0_CTC_CallBack_Func)(void);
static void (*Timer1_OVF_CallBack_Func)(void);
static void (*Timer1_CTC_A_CallBack_Func)(void);
static void (*Timer1_CTC_B_CallBack_Func)(void);
static void (*Timer1_ICU_CallBackFunc)(void);
static void (*Timer2_OVF_CallBack_Func)(void);
static void (*Timer2_CTC_CallBack_Func)(void);

void Timer0_init(void)
{
	#if defined Timer0_Normal_Timer_Mode
		CLEAR_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
		SET_BIT(TIMSK,TOIE0);	//Enable Overflow Interrupt peripheral
	#elif defined Timer0_CTC_Timer_Mode
			CLEAR_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
			SET_BIT(TIMSK,OCIE0);	//Enable Compare Output Interrupt peripheral
/***************************************CTC Mode Selection******************************************/
/*********************************Compare Output Mode/ Non PWM Mode*********************************/
			/*OC0 -> PINB3 in Atmega32*/
		#if defined Normal_PORT_Operation //OC0 Disconnected
				CLEAR_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
		#elif defined Toggle_OCO_Value
				SET_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
		#elif defined Clear_OCO_Value
				CLEAR_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
		#elif defined SET_OCR0_Value
				SET_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
		#endif
#elif defined Timer0_PhaseCorrect_PWM_Mode
		SET_BIT(TCCR0,WGM00);
		CLEAR_BIT(TCCR0,WGM01);
/*****************************Compare Output Mode/ Phase PWM Mode Selection******************************/
		#if defined Normal_PORT_Operation
						CLEAR_BIT(TCCR0,COM00);
						CLEAR_BIT(TCCR0,COM01);
		#elif defined Clear_OC0_CompareMatchCountUP_Set_OC0_CompareMatchCountDown
						CLEAR_BIT(TCCR0,COM00);
						SET_BIT(TCCR0,COM01);
		#elif defined Set_OC0_CompareMatchCountUP_Clear_OC0_CompareMatchCountDown
						SET_BIT(TCCR0,COM00);
						SET_BIT(TCCR0,COM01);
		#endif

#elif  defined Timer0_Fast_PWM_Mode
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
/*****************************Compare Output Mode/ Fast PWM Mode Selection*******************************/
		/*OC0 -> PINB3 in Atmega32*/
		#if defined Normal_PORT_Operation //OC0 Disconnected
				CLEAR_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
		#elif defined ClearCompareMatch_SetTop_OCO	//Non_Inverted Mode
				CLEAR_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
		#elif defined SetCompareMatch_ClearTop_OCO 	//Inverted Mode
				SET_BIT(TCCR0,COM00);
				SET_BIT(TCCR0,COM01);
		#endif
#endif
/**************************************Timer0 Clock Prescaler Selection*****************************************/
		#if defined Timer0_Counter_Disabled
				CLEAR_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_No_Prescaler
				SET_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_8_Prescaler
				CLEAR_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_64_Prescaler
				SET_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_256_Prescaler
				CLEAR_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_1024_Prescaler
				SET_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_External_FallingEdge_CounterMode //On Pin T0
				CLEAR_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS02);
		#elif defined Timer0_CLK_External_RisingEdge_CounterMode //On Pin T0
				SET_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				SET_BIT(TCCR0,CS02);
		#endif
}
void Timer0_SetValue(u8 Value)
{
#if defined Timer0_Normal_Timer_Mode
	TCNT0 = Value; //Set Overflow Value
#elif defined Timer0_CTC_Timer_Mode
	OCR0 = Value; //Set Compare Output Value
#elif defined Timer0_PhaseCorrect_PWM_Mode
	OCR0 = Value; //Set Compare Output Value to set the value of duty cycle
#elif defined Timer0_Fast_PWM_Mode
	OCR0 = Value; //Set Compare Output Value to set the value of duty cycle
#endif
}

void Timer0_CallBack(void (*FUNC_PTR)(void))
{
	#if defined Timer0_Normal_Timer_Mode
		Timer0_OVF_CallBack_Func = FUNC_PTR;
	#elif defined Timer0_CTC_Timer_Mode
		Timer0_CTC_CallBack_Func = FUNC_PTR;
	#endif
}
ISR(TIMER0_OVF_vect)
{
	Timer0_OVF_CallBack_Func();
}

ISR(TIMER0_COMP_vect)
{
	Timer0_CTC_CallBack_Func();
}


void Timer1_init(void)
{
/******************************************Channel Selection*********************************************/
#if defined TIMER1_ChannelA
/***************************Compare Output Mode/ Non PWM Mode Selection_ChannelA*************************/
#if defined Timer1_Compare_Output_NoPWM_Mode
#if defined Normal_PORT_Operation_OC1A
	CLEAR_BIT(TCCR1A,COM1A0);
	CLEAR_BIT(TCCR1A,COM1A1);
#elif defined Toggle_Operation_OC1A_Value
	SET_BIT(TCCR1A,COM1A0);
	CLEAR_BIT(TCCR1A,COM1A1);
#elif defined Clear_Operation_OC1A_Value
	CLEAR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#elif defined SET_Operation_OC1A_Value
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#endif
/***************************Compare Output Mode/ Fast PWM Mode Selection_ChannelA************************/
#elif defined Timer1_Compare_Output_FastPWM_Mode
#if defined Normal_PORT_Operation_OC1A
	CLEAR_BIT(TCCR1A,COM1A0);
	CLEAR_BIT(TCCR1A,COM1A1);
#elif defined ClearCompareMatchOC1A_SetTop_OC1A //Non_Inverted Mode
	CLEAR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#elif defined SetCompareMatchOC1A_ClearTop_OC1A //Inverted Mode
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#endif
/**********************Compare Output Mode/ PhaseCorrect PWM Mode Selection_ChannelA*********************/
#elif defined Timer1_Compare_Output_PhaseCorrectPWM_Mode
#if defined Normal_PORT_Operation_OC1A
	CLEAR_BIT(TCCR1A,COM1A0);
	CLEAR_BIT(TCCR1A,COM1A1);
#elif defined ClearCompareMatchOC1A_SetTop_OC1A //Non_Inverted Mode
	CLEAR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#elif defined SetCompareMatchOC1A_ClearTop_OC1A	//Inverted Mode
	SET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
#endif
#endif

#elif defined TIMER1_ChannelB
/***************************Compare Output Mode/ Non PWM Mode Selection_ChannelB*************************/
#if defined Timer1_Compare_Output_NoPWM_Mode
#if defined Normal_PORT_Operation_OC1B
	CLEAR_BIT(TCCR1A,COM1B0);
	CLEAR_BIT(TCCR1A,COM1B1);
#elif defined Toggle_Operation_OC1B_Value
	SET_BIT(TCCR1A,COM1B0);
	CLEAR_BIT(TCCR1A,COM1B1);
#elif defined Clear_Operation_OC1B_Value
	CLEAR_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#elif defined SET_Operation_OC1B_Value
	SET_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#endif
/***************************Compare Output Mode/ Fast PWM Mode Selection_ChannelB************************/
#elif defined Timer1_Compare_Output_FastPWM_Mode
#if defined Normal_PORT_Operation_OC1B
	CLEAR_BIT(TCCR1A,COM1B0);
	CLEAR_BIT(TCCR1A,COM1B1);
#elif defined ClearCompareMatchOC1B_SetTop_OC1B	//Non_Inverted Mode
	CLEAR_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#elif defined SetCompareMatchOC1B_ClearTop_OC1B	//Inverted Mode
	SET_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#endif
/**********************Compare Output Mode/ PhaseCorrect PWM Mode Selection_ChannelB*********************/
#elif defined Timer1_Compare_Output_PhaseCorrectPWM_Mode
#if defined Normal_PORT_Operation_OC1B
	CLEAR_BIT(TCCR1A,COM1B0);
	CLEAR_BIT(TCCR1A,COM1B1);
#elif defined ClearCompareMatchOC1B_SetTop_OC1B	//Non_Inverted Mode
	CLEAR_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#elif defined SetCompareMatchOC1B_ClearTop_OC1B	//Inverted Mode
	SET_BIT(TCCR1A,COM1B0);
	SET_BIT(TCCR1A,COM1B1);
#endif
#endif
#endif
/**************************************Clock Prescaler Selection*****************************************/
	#if defined Timer1_Counter_Disabled
			CLEAR_BIT(TCCR1B,CS10);
			CLEAR_BIT(TCCR1B,CS11);
			CLEAR_BIT(TCCR1B,CS12);
	#elif defined Timer1_CLK_No_Prescaler
			SET_BIT(TCCR1B,CS10);
			CLEAR_BIT(TCCR1B,CS11);
			CLEAR_BIT(TCCR1B,CS12);
	#elif defined Timer1_CLK_8_Prescaler
			CLEAR_BIT(TCCR1B,CS10);
			SET_BIT(TCCR1B,CS11);
			CLEAR_BIT(TCCR1B,CS12);
	#elif defined Timer1_CLK_64_Prescaler
			SET_BIT(TCCR1B,CS10);
			SET_BIT(TCCR1B,CS11);
			CLEAR_BIT(TCCR1B,CS12);
	#elif defined Timer1_CLK_256_Prescaler
			CLEAR_BIT(TCCR1B,CS10);
			CLEAR_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS12);
	#elif defined Timer1_CLK_1024_Prescaler
			SET_BIT(TCCR1B,CS10);
			CLEAR_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS12);
	#elif defined Timer1_CLK_External_FallingEdge_CounterMode //On Pin T0
			CLEAR_BIT(TCCR1B,CS10);
			SET_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS12);
	#elif defined Timer1_CLK_External_RisingEdge_CounterMode //On Pin T0
			SET_BIT(TCCR1B,CS10);
			SET_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS12);
	#endif

/*********************************WaveMode Generation Mode Selection************************************/
#if defined Timer1_Normal_Timer_Mode
				CLEAR_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				SET_BIT(TIMSK,TOIE1);
#elif defined Timer1_FixedTopValue_PhaseCorrect_PWM_8Bit_Mode
			SET_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
#elif defined Timer1_FixedTopValue_PhaseCorrect_PWM_9Bit_Mode
			CLEAR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
#elif defined Timer1_FixedTopValue_PhaseCorrect_PWM_10Bit_Mode
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
#elif defined Timer1_FixedTopValue_CTC_Timer_Mode
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			SET_BIT(TIMSK,OCIE1);
#elif defined Timer1_FixedTopValue_Fast_PWM_8Bit_Mode
			SET_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
#elif defined Timer1_FixedTopValue_Fast_PWM_9Bit_Mode
			CLEAR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
#elif defined Timer1_FixedTopValue_Fast_PWM_10Bit_Mode
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
#elif defined Timer1_VariableTopValue_ICR1_PhaseCorrect_PWM_Mode
			CLEAR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
#elif defined Timer1_FixedTopValue_PhaseCorrect_PWM_Mode
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
#elif defined Timer1_VariableTopValue_ICR1_Fast_PWM_Mode
			CLEAR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
#elif defined Timer1_FixedValue_Fast_PWM_Mode
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
#elif defined Timer1_VariableTopValue_ICR1_CTC_Timer_Mode
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
#endif
}

void Timer1_SetValueChannelA(u16 Value)	//to Set value of timer ChannelA
{
#if defined TIMER1_ChannelA
	#if defined Timer1_Normal_Timer_Mode
		TCNT1 = Value; //Set Overflow Value
	#elif defined Timer1_FixedMaxValue_CTC_Timer_Mode
		OCR1A = Value; //Set Compare Output Value
	#elif defined Timer1_FixedValue_Fast_PWM_Mode
		OCR1A = Value; //Set Compare Output Value to set the value of duty cycle
	#elif defined Timer1_FixedTopValue_PhaseCorrect_PWM_Mode
		OCR1A = Value;
	#elif defined Timer1_VariableTopValue_ICR1_Fast_PWM_Mode	//Set Comp value for ChannelA
		OCR1A=Value;
	#endif
#endif
}
void Timer1_SetValueChannelB(u16 Value)	//to Set value of timer ChannelB
{
#if defined TIMER1_ChannelB
	#if defined Timer1_Normal_Timer_Mode
	TCNT1 = Value; //Set Overflow Value
	#elif defined Timer1_FixedMaxValue_CTC_Timer_Mode
	OCR1B = Value; //Set Compare Output Value
	#elif defined Timer1_FixedValue_Fast_PWM_Mode
	OCR1B= Value; //Set Compare Output Value to set the value of duty cycle
	#elif defined Timer1_FixedTopValue_PhaseCorrect_PWM_Mode
	OCR1B = Value;
	#elif defined Timer1_VariableTopValue_ICR1_Fast_PWM_Mode	//Set Comp value for ChannelB
		OCR1B=Value;
	#endif
#endif
}

void Timer1_ReadValueChannelA(u16 *value)	//to Read value of timer
{
#if defined TIMER1_ChannelA
#if defined Timer1_Normal_Timer_Mode
	*value=TCNT1; //Set Overflow Value
#elif defined Timer1_FixedMaxValue_CTC_Timer_Mode
	*value=OCR1A;
#elif defined Timer1_FixedValue_Fast_PWM_Mode
			*value=OCR1A;
#elif defined Timer1_FixedTopValue_PhaseCorrect_PWM_Mode
			*value=OCR1A;
#endif
#endif
}

void Timer1_ReadValueChannelB(u16 *value)
{
#if defined TIMER1_ChannelB
#if defined Timer1_Normal_Timer_Mode
	*value=TCNT1; //Set Overflow Value
#elif defined Timer1_FixedMaxValue_CTC_Timer_Mode
	*value=OCR1B;
#elif defined Timer1_FixedValue_Fast_PWM_Mode
	*value=OCR1B;
#elif defined Timer1_FixedTopValue_PhaseCorrect_PWM_Mode
	*value=OCR1B;
#endif
#endif
}

STD_Return Timer1_ICU_EdgeSelection(ICU_Edge_Control_t State) //for Edge Selection which ICU will used
{
	switch (State)
	{
		case ICU_Rising_Edge:
			SET_BIT(TCCR1B,ICES1);
			break;
		case ICU_Falling_Edge:
			CLEAR_BIT(TCCR1B,ICES1);
			break;
		default:
			return E_OK;
	}
	return E_NOK;
}
STD_Return Timer1_ICU_Interrupt(ICU_Interrupt_State State) //Enable or Disable ICU interrupt
{
	switch(State)
	{
	//receive the ICU  result on the ICP pin => pin 6 portD
	case Enable_ICU_Interrupt:
		//Enable Input Capture Interrupt
		SET_BIT(TIMSK,TICIE1);
		break;
	case Disable_ICU_Interrupt:
		//disable Input Capture Interrupt
		CLEAR_BIT(TIMSK,TICIE1);
		break;
	default:
		return E_OK;
	}
return E_NOK;
}

void Timer1_SetICR1_TopValue(u16 Top_Value) //ICR1
{
	ICR1=Top_Value;
}

void Timer1_Read_ICR_Value(u16  *value)
{
	//Store value of InputCaptureRegister & get it back
	*value=ICR1;
}
void ICU_CallBack_Func(void(*PTR_Func)(void))
{
	Timer1_ICU_CallBackFunc=PTR_Func;
}

void Timer1_CallBack(void (*FUNC_PTR)(void))
{
	#if defined Timer1_Normal_Timer_Mode
	Timer1_OVF_CallBack_Func = FUNC_PTR;
	#elif defined Timer1_FixedMaxValue_CTC_Timer_Mode
	#if defined TIMER1_ChannelA
		Timer1_CTC_A_CallBack_Func = FUNC_PTR;
	#elif defined TIMER1_ChannelB
		Timer1_CTC_B_CallBack_Func = FUNC_PTR;
	#endif
		#endif
}
//ISR of OVF
ISR(TIMER1_OVF_vect)
{
	Timer1_OVF_CallBack_Func();
}
//ISR of COMP_ChannelA
ISR(TIMER1_COMPA_vect)
{
	Timer1_CTC_A_CallBack_Func();
}
//ISR of COMP_ChannelB
ISR(TIMER1_COMPB_vect)
{
	Timer1_CTC_B_CallBack_Func();
}
//ISR of ICU
ISR(TIMER1_ICU_vect)
{
	Timer1_ICU_CallBackFunc();
}
void Timer2_init(void)
{
	#if defined Timer2_Normal_Timer_Mode
		CLEAR_BIT(TCCR2,WGM20);
		CLEAR_BIT(TCCR2,WGM21);
		SET_BIT(TIMSK,TOIE2);	//Enable Overflow Interrupt peripheral
	#elif defined Timer2_CTC_Timer_Mode
			CLEAR_BIT(TCCR2,WGM20);
			SET_BIT(TCCR2,WGM21);
			SET_BIT(TIMSK,OCIE2);	//Enable Compare Output Interrupt peripheral
/***************************************CTC Mode Selection******************************************/
/*********************************Compare Output Mode/ Non PWM Mode*********************************/
			/*OC2 -> PIND7 in Atmega32*/
		#if defined Normal_PORT_Operation //OC2 Disconnected
				CLEAR_BIT(TCCR2,COM20);
				CLEAR_BIT(TCCR2,COM21);
		#elif defined Toggle_OC2_Value
				SET_BIT(TCCR2,COM20);
				CLEAR_BIT(TCCR2,COM21);
		#elif defined Clear_OC2_Value
				CLEAR_BIT(TCCR2,COM20);
				SET_BIT(TCCR2,COM21);
		#elif defined SET_OCR2_Value
				SET_BIT(TCCR2,COM20);
				SET_BIT(TCCR2,COM21);
		#endif
#elif defined Timer2_PhaseCorrect_PWM_Mode
		SET_BIT(TCCR2,WGM20);
		CLEAR_BIT(TCCR2,WGM21);
/*****************************Compare Output Mode/ Phase PWM Mode Selection******************************/
		#if defined Normal_PORT_Operation
						CLEAR_BIT(TCCR2,COM20);
						CLEAR_BIT(TCCR2,COM21);
		#elif defined Clear_OC2_CompareMatchCountUP_Set_OC2_CompareMatchCountDown
						CLEAR_BIT(TCCR2,COM20);
						SET_BIT(TCCR2,COM21);
		#elif defined Set_OC2_CompareMatchCountUP_Clear_OC2_CompareMatchCountDown
						SET_BIT(TCCR2,COM20);
						SET_BIT(TCCR2,COM21);
		#endif

#elif  defined Timer2_Fast_PWM_Mode
		SET_BIT(TCCR2,WGM20);
		SET_BIT(TCCR2,WGM21);
/*****************************Compare Output Mode/ Fast PWM Mode Selection*******************************/
		/*OC2 -> PIND7 in Atmega32*/
		#if defined Normal_PORT_Operation //OC2 Disconnected
				CLEAR_BIT(TCCR2,COM20);
				CLEAR_BIT(TCCR2,COM21);
		#elif defined ClearCompareMatch_SetTop_OC2	//Non_Inverted Mode
				CLEAR_BIT(TCCR2,COM20);
				SET_BIT(TCCR2,COM21);
		#elif defined SetCompareMatch_ClearTop_OC2 	//Inverted Mode
				SET_BIT(TCCR2,COM20);
				SET_BIT(TCCR2,COM21);
		#endif
#endif
/**************************************Timer2 Clock Prescaler Selection*****************************************/
		#if defined Timer2_Counter_Disabled
				CLEAR_BIT(TCCR2,CS20);
				CLEAR_BIT(TCCR2,CS21);
				CLEAR_BIT(TCCR2,CS22);
		#elif defined Timer2_CLK_No_Prescaler
				SET_BIT(TCCR2,CS20);
				CLEAR_BIT(TCCR2,CS21);
				CLEAR_BIT(TCCR2,CS22);
		#elif defined Timer2_CLK_8_Prescaler
				CLEAR_BIT(TCCR2,CS20);
				SET_BIT(TCCR2,CS21);
				CLEAR_BIT(TCCR2,CS22);
		#elif defined Timer2_CLK_64_Prescaler
				SET_BIT(TCCR2,CS20);
				SET_BIT(TCCR2,CS21);
				CLEAR_BIT(TCCR2,CS22)
		#elif defined Timer2_CLK_256_Prescaler
				CLEAR_BIT(TCCR2,CS20);
				CLEAR_BIT(TCCR2,CS21);
				SET_BIT(TCCR2,CS22);
		#elif defined Timer2_CLK_1024_Prescaler
				SET_BIT(TCCR2,CS20);
				CLEAR_BIT(TCCR2,CS21);
				SET_BIT(TCCR2,CS22);
		#elif defined Timer2_CLK_External_FallingEdge_CounterMode //On Pin T2
				CLEAR_BIT(TCCR2,CS20);
				SET_BIT(TCCR2,CS21);
				SET_BIT(TCCR2,CS22);
		#elif defined Timer2_CLK_External_RisingEdge_CounterMode //On Pin T2
				SET_BIT(TCCR2,CS20);
				SET_BIT(TCCR2,CS21);
				SET_BIT(TCCR2,CS22);
		#endif
}
void Timer2_SetValue(u8 Value)
{
#if defined Timer2_Normal_Timer_Mode
	TCNT2 = Value; //Set Overflow Value
#elif defined Timer2_CTC_Timer_Mode
	OCR2 = Value; //Set Compare Output Value
#elif defined Timer2_PhaseCorrect_PWM_Mode
	OCR2 = Value; //Set Compare Output Value to set the value of duty cycle
#elif defined Timer2_Fast_PWM_Mode
	OCR2 = Value; //Set Compare Output Value to set the value of duty cycle
#endif
}

void Timer2_CallBack(void (*FUNC_PTR)(void))
{
	#if defined Timer2_Normal_Timer_Mode
		Timer2_OVF_CallBack_Func = FUNC_PTR;
	#elif defined Timer2_CTC_Timer_Mode
		Timer2_CTC_CallBack_Func = FUNC_PTR;
	#endif
}
ISR(TIMER2_OVF_vect)
{
	Timer2_OVF_CallBack_Func();
}

ISR(TIMER2_COMP_vect)
{
	Timer2_CTC_CallBack_Func();
}

