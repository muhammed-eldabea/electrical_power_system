/*
 * LCD.c
 *
 *  Created on: Sep 19, 2019
 *      Author: Muhammed Eldabea Hashem 
 */




#include "lcd.h"

void LCD_Init()
{
	Control_Direction|= (1<<En) | (1<<RS)  | (1<<RW) ;
#if (BITS_mode == 8)
	Write_Direction = 0xff ;
	LCD_SendCommand(0x38) ;
	LCD_SendCommand(0x0c) ;
	LCD_SendCommand(0x01) ;
#else
#ifdef upper_port
	Write_Direction = 0xf0 ;
#else
	Write_Direction = 0x0f ;
#endif
	LCD_SendCommand(FOUR_BITS_DATA_MODE)       ;
	LCD_SendCommand(TWO_LINE_LCD_Four_BIT_MODE) ;
	LCD_SendCommand(0x0c) ;
	LCD_SendCommand(0x01) ;

#endif
}




void LCD_SendCommand (uint8 command)
{
	CLEAR_BIT(Control_PORT  , RS) ;
	CLEAR_BIT(Control_PORT,RW)  ;
	_delay_ms(1) ;
	SET_BIT(Control_PORT,En)  ;
	_delay_ms(1)  ;

#if(BITS_mode == 8  )
	Write_PORT = command ;
	_delay_ms(1) ;
	CLEAR_BIT(Control_PORT , En) ;

#elif (BITS_mode ==4)
#ifdef upper_port
	Write_PORT = (Write_PORT & 0x0f) |(command & 0xf0 ) ;
#else
	Write_PORT = (Write_PORT & 0xf0) | ((command & 0xf0 ) >>4 ) ;
#endif
	_delay_ms(1) ;
	CLEAR_BIT(Control_PORT , En) ;
	_delay_ms(1)  ;
	SET_BIT(Control_PORT , En)  ;
	_delay_ms(1) ;
#ifdef upper_port
	Write_PORT = (Write_PORT & 0x0f) | ((command & 0x0f ) <<4 );
#else
	Write_PORT = (Write_PORT & 0xf0) | (command & 0x0f )  ;
#endif



	_delay_ms(1) ;
	CLEAR_BIT(Control_PORT , En) ;
	_delay_ms(1)  ;
	SET_BIT(Control_PORT , En)  ;
	_delay_ms(1) ;


#endif

}







void LCD_DisplayChar (uint8 data)
{

	SET_BIT(Control_PORT  , RS) ;
	CLEAR_BIT(Control_PORT,RW)  ;
	_delay_ms(1) ;
	SET_BIT(Control_PORT,En)  ;
	_delay_ms(1)  ;

#if(BITS_mode == 8  )
	Write_PORT = data ;
	_delay_ms(1) ;
	CLEAR_BIT(Control_PORT , En) ;

#elif (BITS_mode ==4)
#ifdef upper_port
	Write_PORT = (Write_PORT & 0x0f) |(data & 0xf0 ) ;
#else
	Write_PORT = (Write_PORT & 0xf0) | ((data & 0xf0 ) >>4 ) ;
#endif
	_delay_ms(1) ;
	CLEAR_BIT(Control_PORT , En) ;
	_delay_ms(1)  ;
	SET_BIT(Control_PORT , En)  ;
	_delay_ms(1) ;
#ifdef upper_port
	Write_PORT = (Write_PORT & 0x0f) | ((data & 0x0f ) <<4 );
#else
	Write_PORT = (Write_PORT & 0xf0) | (data & 0x0f )  ;
#endif



	_delay_ms(1) ;
	CLEAR_BIT(Control_PORT , En) ;
	_delay_ms(1)  ;
	SET_BIT(Control_PORT , En)  ;
	_delay_ms(1) ;





#endif

}
void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		LCD_DisplayChar(Str[i]);
		i++;
	}

}
void LCD_intgerToString(int data)
{
   char buff[16];
   itoa(data,buff,10);
   LCD_displayString(buff);
}

void LCD_GoToRowAndCol (uint8 row , uint8 col)
{
	uint8 Adresse ;
	switch(row)
	{
	case 0 :
		Adresse = col ;
		break ;
	case 1 :
		Adresse = col +0x40 ;
		break ;
	case 2 :
		Adresse = col + 0x010  ;
		break ;
	case 3 :
		Adresse = col + 0x050 ;
		break ;
	}

	LCD_SendCommand(Adresse | SET_CURSOR_LOCATION) ;

}


void LCD_DisplayStringRowCol(uint8 row , uint8 col ,const char*str)
{
	LCD_GoToRowAndCol(row,col) ;
	LCD_displayString(str) ;
}


void LCD_DisplayFloat(float data)
{
	uint8 deci = data ;
	int fra  =  (int)(data-deci)*100 ;
	LCD_GoToRowAndCol(1,3) ;
	LCD_intgerToString(data) ;
	LCD_GoToRowAndCol(1,5) ;
	LCD_intgerToString(fra) ;

}
