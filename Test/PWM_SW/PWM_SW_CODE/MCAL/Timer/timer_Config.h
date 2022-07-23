/*
 * timer_Config.h
 *
 *  Created on: May 5, 2022
 *      Author: Seko
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_
/**************************************Timer0 Clock Prescaler Selection*****************************************/
//#define Timer0_Counter_Disabled
//#define Timer0_CLK_No_Prescaler
//#define Timer0_CLK_8_Prescaler
#define Timer0_CLK_64_Prescaler
//#define Timer0_CLK_256_Prescaler
//#define Timer0_CLK_1024_Prescaler
//#define Timer0_CLK_External_FallingEdge_CounterMode //On Pin T0
//#define Timer0_CLK_External_RisingEdge_CounterMode //On Pin T0
/**************************************Timer1 Clock Prescaler Selection*****************************************/
//#define Timer1_Counter_Disabled
//#define Timer1_CLK_No_Prescaler
//#define Timer1_CLK_8_Prescaler
//#define Timer1_CLK_64_Prescaler
//#define Timer1_CLK_256_Prescaler
//#define Timer1_CLK_1024_Prescaler
//#define Timer1_CLK_External_FallingEdge //On Pin T0
//#define Timer1_CLK_External_RisingEdge //On Pin T0
/**********************************************WatchDog*************************************************/
//#define Vcc_5_Volt
//#define Vcc_3_Volt
/******************************WatchDog Vcc=5volt Clock Prescaler Selection*********************************/
//#define WatchDog_16K_CLKCycle__16_3_ms_Prescaler
//#define WatchDog_32K_CLKCycle_32_5_ms_Prescaler
//#define WatchDog_64K_CLKCycle_65_ms_Prescaler
//#define WatchDog_128K_CLKCycle_0_13_s_Prescaler
//#define WatchDog_256K_CLKCycle_0_26_s_Prescaler
//#define WatchDog_512_CLKCycle_0_52_s_Prescaler
//#define WatchDog_1024K_CLKCycle_1_s_Prescaler
//#define WatchDog_2048K_CLKCycle_2_1_s_Prescaler
/******************************WatchDog Vcc=3volt Clock Prescaler Selection*********************************/
//#define WatchDog_16K_CLKCycle_17_1_ms_Prescaler
//#define WatchDog_32K_CLKCycle_34_3_ms_Prescaler
//#define WatchDog_64K_CLKCycle_65_8_ms_Prescaler
//#define WatchDog_128K_CLKCycle_0_14_s_Prescaler
//#define WatchDog_256K_CLKCycle_0_27_s_Prescaler
//#define WatchDog_512_CLKCycle_0_55_s_Prescaler
//#define WatchDog_1024K_CLKCycle_1_1_s_Prescaler
//#define WatchDog_2048K_CLKCycle_2_2_s_Prescaler
/***********************************************TIMER 0*************************************************/
/*****************************************CTC Mode Selection*********************************************/
/*********************************WaveMode Generation Mode Selection************************************/
//#define Timer0_Normal_Timer_Mode
#define Timer0_CTC_Timer_Mode
//#define Timer0_PhaseCorrect_PWM_Mode
//#define Timer0_Fast_PWM_Mode
/*****************************Compare Output Mode/ Non PWM Mode Selection*******************************/
/*OC0 -> PINB3 in Atmega32*/
//#define Normal_PORT_Operation //OC0 Disconnected event not interrupt
//#define Toggle_OCO_Value
//#define Clear_OCO_Value
//#define SET_OC0_Value
/*****************************Compare Output Mode/ Fast PWM Mode Selection*******************************/
//#define Normal_PORT_Operation 		//OC0 Disconnected event not interrupt
//#define ClearCompareMatch_SetTop_OCO	//Non_Inverted Mode
//#define SetCompareMatch_ClearTop_OCO	//Inverted Mode
/*****************************Compare Output Mode/ Phase PWM Mode Selection******************************/
//#define Normal_PORT_Operation 										//OC0 Disconnected
//#define Clear_OC0_CompareMatchCountUP_Set_OC0_CompareMatchCountDown	//Non_Inverted Mode
//#define Set_OC0_CompareMatchCountUP_Clear_OC0_CompareMatchCountDown	//Inverted Mode

/***********************************************TIMER 1**************************************************/
/******************************************Channel Selection*********************************************/
//#define TIMER1_ChannelA	/*OCRA -> PIND5 in Atmega32*/
//#define TIMER1_ChannelB		/*OCRB -> PIND4 in Atmega32*/
/****************************************CTC Mode Selection*********************************************/
//#define Timer1_Compare_Output_NoPWM_Mode
//#define Timer1_Compare_Output_FastPWM_Mode
//#define Timer1_Compare_Output_PhaseCorrectPWM_Mode
/***************************Compare Output Mode/ Non PWM Mode Selection_ChannelA*************************/
//#define Normal_PORT_Operation_OC1A  //OC1A_ Disconnected event not interrupt
//#define Toggle_Operation_OC1A_Value
//#define Clear_Operation_OC1A_Value
//#define SET_Operation_OC1A_Value
/***************************Compare Output Mode/ Fast PWM Mode Selection_ChannelA************************/
//#define Normal_PORT_Operation_OC1A  			//OC1A_OC1B Disconnected event not interrupt
//#define ClearCompareMatchOC1A_SetTop_OC1A		//Non_Inverted Mode
//#define SetCompareMatchOC1A_ClearTop_OC1A		//Inverted Mode
/**********************Compare Output Mode/ PhaseCorrect PWM Mode Selection_ChannelA*********************/
//#define Normal_PORT_Operation_OC1A				//OC1A_OC1B Disconnected event not interrupt
//#define ClearCompareMatchOC1A_SetTop_OC1A		//Non_Inverted Mode
//#define SetCompareMatchOC1A_ClearTop_OC1A		//Inverted Mode
/***************************Compare Output Mode/ Non PWM Mode Selection_ChannelB*************************/
//#define Normal_PORT_Operation_OC1B  //OC1A_ Disconnected event not interrupt
//#define Toggle_Operation_OC1B_Value
//#define Clear_Operation_OC1B_Value
//#define SET_Operation_OC1B_Value
/***************************Compare Output Mode/ Fast PWM Mode Selection_ChannelB************************/
//#define Normal_PORT_Operation_OC1B  			//OC1A_OC1B Disconnected event not interrupt
//#define ClearCompareMatchOC1B_SetTop_OC1B		//Non_Inverted Mode
//#define SetCompareMatchOC1B_ClearTop_OC1B		//Inverted Mode
/**********************Compare Output Mode/ PhaseCorrect PWM Mode Selection_ChannelB*********************/
//#define Normal_PORT_Operation_OC1B			//OC1A_OC1B Disconnected event not interrupt
//#define ClearCompareMatchOC1B_SetTop_OC1B		//Non_Inverted Mode
//#define SetCompareMatchOC1B_ClearTop_OC1B		//Inverted Mode
/*********************************WaveMode Generation Mode Selection************************************/
/*fixed TopValue*/
//#define Timer1_Normal_Timer_Mode
//#define Timer1_FixedTopValue_PhaseCorrect_PWM_8Bit_Mode 	//Not_16_bit
//#define Timer1_FixedTopValue_PhaseCorrect_PWM_9Bit_Mode	//Not_16_bit
//#define Timer1_FixedTopValue_PhaseCorrect_PWM_10Bit_Mode	//Not_16_bit
//#define Timer1_FixedTopValue_CTC_Timer_Mode
//#define Timer1_FixedTopValue_Fast_PWM_8Bit_Mode		//Not_16_bit
//#define Timer1_FixedTopValue_Fast_PWM_9Bit_Mode		//Not_16_bit
//#define Timer1_FixedTopValue_Fast_PWM_10Bit_Mode		//Not_16_bit
//#define Timer1_FixedValue_Fast_PWM_Mode				// Normal Fast
//#define Timer1_FixedTopValue_PhaseCorrect_PWM_Mode	// Normal Phasecorrect

/*Variable TopValue*/
//#define Timer1_VariableTopValue_ICR1_PhaseCorrect_PWM_Mode		//controllable max value placed in ICR1 16Bit_Reg
//#define Timer1_VariableTopValue_ICR1_Fast_PWM_Mode		//controllable max value placed in ICR1 16Bit_Reg
//#define Timer1_VariableTopValue_ICR1_CTC_Timer_Mode	//controllable max value placed in ICR1 16Bit_Reg

#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
