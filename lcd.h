/*
 * LCD.h
 *
 *  Created on: Sep 19, 2019
 *      Author: Muhammed Eldabea Hashem
 */

#ifndef LCD_H_
#define LCD_H_
/*******************************Includes*****************************************/
#include "std_types.h"
#include "common_macros.h"
#include "microcontroller_config.h"
#include <stdlib.h>




/*******************************Defination***************************************/
#define BITS_mode 8  /*chang this value to select bits mode 4 or 8 */

#define Control_PORT PORTB
#define Write_PORT    PORTC
#define Write_Direction DDRC
#define Control_Direction DDRB
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80
#define RS PB0   /*regiester slect mask whene we send command and set whene we send data */
#define En PB1   /* enable */
#define RW PB2   /*read and write  masked to write data and set to read data  */
#define v0 PB3   /*adjust consrast for maximum constrain conect it to ground  */



/******************************FounctionProtoType********************************/

void LCD_Init() ;
void LCD_SendCommand (uint8 command)  ;
void LCD_DisplayChar (uint8 data) ;
void LCD_displayString(const char *Str) ;
void LCD_intgerToString(int data) ;
void LCD_GoToRowAndCol (uint8 row , uint8 col) ;
void LCD_DisplayStringRowCol(uint8 row , uint8 col ,const char*str) ; /*print in a specific locatin */
void LCD_DisplayFloat(float data) ;





/********************************************************************************/

#endif /* LCD_H_ */
