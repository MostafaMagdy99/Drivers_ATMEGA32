/*
 * LCD.c
 *
 *  Created on: Apr 2, 2022
 *      Author: Seko
 */

#include "LCD.h"
#include "LCD_Config.h"
#include <util/delay.h>


void CLCD_init(void)
{
	#if defined CLCD_8_BitMode

	/*Initialize LCD pins direction*/
	DIO_SetPortDirection(CLCD_DataPort,PORT_OUTPUT);
	DIO_SetPinDirection(CLCD_ControlPort,CLCD_RS_PIN,DIO_OUTPUT);
	DIO_SetPinDirection(CLCD_ControlPort,CLCD_RW_PIN,DIO_OUTPUT);
	DIO_SetPinDirection(CLCD_ControlPort,CLCD_E_PIN,DIO_OUTPUT);

	/*Wait for more than 30 ms*/
	_delay_ms(40);


	#elif defined CLCD_4_BitMode
			/*Initialize LCD pins direction*/
				DIO_SetPinDirection(CLCD_DataPort,Data_Pin7,DIO_OUTPUT);
				DIO_SetPinDirection(CLCD_DataPort,Data_Pin6,DIO_OUTPUT);
				DIO_SetPinDirection(CLCD_DataPort,Data_Pin5,DIO_OUTPUT);
				DIO_SetPinDirection(CLCD_DataPort,Data_Pin5,DIO_OUTPUT);

				DIO_SetPinDirection(CLCD_ControlPort,CLCD_RS_PIN,DIO_OUTPUT);
				DIO_SetPinDirection(CLCD_ControlPort,CLCD_RW_PIN,DIO_OUTPUT);
				DIO_SetPinDirection(CLCD_ControlPort,CLCD_E_PIN,DIO_OUTPUT);

				/*Wait for more than 30 ms*/
				_delay_ms(40);

				DIO_SetPinValue(CLCD_ControlPort,CLCD_RS_PIN,DIO_LOW);
				DIO_SetPinValue(CLCD_ControlPort,CLCD_RW_PIN,DIO_LOW);

			/*Set command to data pins*/
			DIO_SetPinValue(CLCD_DataPort,Data_Pin7,DIO_LOW);
			DIO_SetPinValue(CLCD_DataPort,Data_Pin6,DIO_LOW);
			DIO_SetPinValue(CLCD_DataPort,Data_Pin5,DIO_HIGH);
			DIO_SetPinValue(CLCD_DataPort,Data_Pin4,DIO_LOW);
			/*Send enable pulse*/
		    DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
		    _delay_ms(2);
		    DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);
			/*Set command to data pins*/
			DIO_SetPinValue(CLCD_DataPort,Data_Pin7,DIO_LOW);
			DIO_SetPinValue(CLCD_DataPort,Data_Pin6,DIO_LOW);
			DIO_SetPinValue(CLCD_DataPort,Data_Pin5,DIO_HIGH);
			DIO_SetPinValue(CLCD_DataPort,Data_Pin4,DIO_LOW);
			/*Send enable pulse*/
		    DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
		    _delay_ms(2);
		    DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);

		  #if defined CLCD_OneLine_5x8Size
		    DIO_SetPinValue(CLCD_DataPort,Data_Pin7,DIO_LOW);
		    DIO_SetPinValue(CLCD_DataPort,Data_Pin6,DIO_LOW);

		    DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
    		_delay_ms(2);
    		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);

		  #elif defined CLCD_OneLine_5x11Size
  			DIO_SetPinValue(CLCD_DataPort,Data_Pin7,DIO_LOW);
  			DIO_SetPinValue(CLCD_DataPort,Data_Pin6,DIO_HIGH);

  			DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
    		_delay_ms(2);
    		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);

		  #elif defined CLCD_TwoLines_5x8Size
            DIO_SetPinValue(CLCD_DataPort,Data_Pin7,DIO_HIGH);
            DIO_SetPinValue(CLCD_DataPort,Data_Pin6,DIO_LOW);

            DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
    		_delay_ms(2);
    		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);

		  #elif defined CLCD_TwoLines_5x11Size
    		DIO_SetPinValue(CLCD_DataPort,Data_Pin7,DIO_HIGH);
    		DIO_SetPinValue(CLCD_DataPort,Data_Pin6,DIO_HIGH);

    		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
    		_delay_ms(2);
    		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);
		#endif
	#endif

#if defined CLCD_Curser_OFF
		CLCD_SendCommand(CLCD_CURSOR_OFF);

#elif defined CLCD_Curser_ON_NoBlinking
        CLCD_SendCommand(CLCD_DISP_ON_CURSOR);

#elif defined CLCD_Curser_ON_Blinking
        CLCD_SendCommand(CLCD_DISP_ON_CURSOR_BLINK);

#endif
      	/*Clear display*/
        CLCD_SendCommand(CLCD_CLEAR);
}

void CLCD_SendCommand(u8 Command)
{
	/*Set RS pin to low for command*/
    DIO_SetPinValue(CLCD_ControlPort,CLCD_RS_PIN,DIO_LOW);

    /*Set RW pin to low for write*/
    DIO_SetPinValue(CLCD_ControlPort,CLCD_RW_PIN,DIO_LOW);

	#if defined  CLCD_8_BitMode

    /*Set command to data pins*/
        DIO_SetPortValue(CLCD_DataPort,Command);

        /*Send enable pulse*/
        DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
        _delay_ms(2);
        DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);

	#elif defined CLCD_4_BitMode

		DataPort =  (DataPort & 0x0F)| (UpperNibble_BitMask_Command); //send upper 4 bit

		DIO_SetPinValue(CLCD_ControlPort,CLCD_RS_PIN,DIO_LOW);
		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);

		_delay_us(50);
		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);
		_delay_us(200);

		DataPort =  (DataPort & 0x0F)| (LowerNibble_BitMask_Command);	//send lower 4 bit

		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
		_delay_us(2000);
		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);
#endif
}

void CLCD_SendData(u8 Data)
{
	/*Set RS pin to High for Data*/
    DIO_SetPinValue(CLCD_ControlPort,CLCD_RS_PIN,DIO_HIGH);

    /*Set RW pin to low for write*/
    DIO_SetPinValue(CLCD_ControlPort,CLCD_RW_PIN,DIO_LOW);

	#if defined  CLCD_8_BitMode
    /*Set command to data pins*/
       DIO_SetPortValue(CLCD_DataPort,Data);

       /*Send enable pulse*/
       DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
       _delay_ms(2);
       DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);

	#elif defined CLCD_4_BitMode
		DataPort = (DataPort & 0x0F) | (UpperNibble_BitMask_Data);	//send upper 4 bit

		DIO_SetPinValue(CLCD_ControlPort,CLCD_RS_PIN,DIO_HIGH);
		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);

		_delay_us(50);
		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);
		_delay_us(2000);

		DataPort = (DataPort & 0x0F) | (LowerNibble_BitMask_Data); 	//send lower 4 bit

		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_HIGH);
		_delay_us(2000);
		DIO_SetPinValue(CLCD_ControlPort,CLCD_E_PIN,DIO_LOW);
#endif
}

void CLCD_SendWord(u8 *Word)
{
	u8 Counter=0;
	while(Word[Counter]!='\0')
	{
		CLCD_SendData(Word[Counter]);
		Counter++;
		if(Counter==16)
			CLCD_GoToXY(1,0);
	}
}

void CLCD_GoToXY(u8 X_Position,u8 Y_Position)
{
	u8 DDRAM_address;
	if(Y_Position == 0)
		{
			DDRAM_address = X_Position;
			CLCD_SendCommand(DDRAM_address+Set_Bit7); //128 the value of bit 7 when it set high in DDRAM
		}
	else if (Y_Position == 1)
		{
		DDRAM_address = X_Position + FirstLoc_SecondLine;
		CLCD_SendCommand(DDRAM_address+Set_Bit7); //128 the value of bit 7 when it set high in DDRAM
		}
}

void CLCD_SendSpecialChar(u8 *Pattern,u8 BlockNumber,u8 X_Position,u8 Y_Position)
{
	u8 Counter,CGRAM_Address;

	/*Calculating the Address of the CGRAM whose block is 8 bytes*/
	CGRAM_Address = BlockNumber*8;

	/*Send the CGRAM Address to point on the first location then the address counter will continue to increment
	 * 1 with setting bit 6 and clearing the bit 7*/
		CLCD_SendCommand(CGRAM_Address+Set_Bit6);

	/*Loop to the start inserting the pattern into the CGRAM Byte by Byte*/
		for(Counter=0;Counter<8;Counter++)
		{
			CLCD_SendData(Pattern[Counter]);
		}

	/*go back to the DDRAM to display the pattern in the selected position*/
		CLCD_GoToXY(X_Position,Y_Position);

	/*The DDRAM accessing the CGRAM by block to Displaying the pattern*/
		CLCD_SendData(BlockNumber);
}


void CLCD_Display_Decimal_Number(s32 num)
{
	u8 i = 0, j, digit, str[10];

	/* if number 0 */
	if (0 == num)
	{
		CLCD_SendData('0');
	}

	/* if the number is negative */
	if (num < 0)
	{
		CLCD_SendData('-');

		/* convert to positive form */
		num = num * -1;
	}

	/* loop on digits of the number */
	while (num > 0)
	{
		digit = (num % 10) + '0';
		str[i] = digit;
		num /= 10;
		i++;
	}

	/* print str on LCD */
	for (j = i; j > 0; j--)
	{
		CLCD_SendData(str[j - 1]);
	}
}

void CLCD_Display_RealNumber(f32 num)
{
	//Left number to the decimal point
	s32 left = (s32)num;
	//calculation to the Right number to the decimal point
	u8 right = (f32)(num - left) * 100;
	//Display Left number to the decimal point
	CLCD_Display_Decimal_Number(left);
	//Display the decimal point
	CLCD_SendData('.');
	//Display the Right number to the decimal point
	CLCD_Display_Decimal_Number(right);
}

