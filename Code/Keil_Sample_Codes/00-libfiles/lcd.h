/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
*****************************************************************************************************
 * File:   lcd.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the LCD port configurations, CMD list, function prototypes

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
***************************************************************************************************/



/***************************************************************************************************
                             Revision History
*****************************************************************************************************
15.0: Initial version 
****************************************************************************************************/


#ifndef _LCD_H_
#define _LCD_H_

#include "stdutils.h"
#include "gpio.h"



/***************************************************************************************************
                 PreCompile configurations to enable/disable the functions
****************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring its respective macros to 1/0.
 2. By default all the API's are disabled.
 3. Displaying of floating number takes huge controller resources and need to be enabled only 
    if required. This implies for other interfaces as well. 
****************************************************************************************************/
#define    Enable_LCD_SetCursor              0
#define    Enable_LCD_DisplayString          1
#define    Enable_LCD_ScrollMessage          0
#define    Enable_LCD_DisplayNumber          0
#define    Enable_LCD_DisplayFloatNumber     0
#define    Enable_LCD_Printf                 0
/**************************************************************************************************/







/***************************************************************************************************
                        List of commonly used LCD Commands 
****************************************************************************************************/
#define CMD_LCD_CLEAR                0x01u
#define CMD_LCD_RETURN_HOME          0x02u
#define CMD_DISPLAY_ON_CURSOR_OFF    0x0Cu
#define CMD_DISPLAY_ON_CURSOR_ON     0x0Eu
#define CMD_DISPLAY_ON_CURSOR_BLINK  0x0Fu
#define CMD_LCD_FOUR_BIT_MODE        0x28u
#define CMD_LCD_EIGHT_BIT_MODE       0x38u
/**************************************************************************************************/







/***************************************************************************************************
                             Commonly used LCD macros/Constants
**************************************************************************************************/
#define C_EightBitMode_U8 8u
#define C_FourBitMode_U8  4u

#define C_ScrollDelayTime_U8     100


#define C_DisplayDefaultDigits_U8            0xffu // Will display the exact digits in the number
#define C_MaxDigitsToDisplay_U8              10u   // Max decimal/hexadecimal digits to be displayed
#define C_NumOfBinDigitsToDisplay_U8         16u   // Max bits of a binary number to be displayed
#define C_MaxDigitsToDisplayUsingPrintf_U8   C_DisplayDefaultDigits_U8 /* Max dec/hexadecimal digits to be displayed using printf */
/**************************************************************************************************/







/***************************************************************************************************
                                 Struct/Enums used
****************************************************************************************************/
#define C_LcdLineZero   0x00
#define C_LcdLineOne    0x01
#define C_LcdLineTwo    0x02
#define C_LcdLineThree  0x03
#define C_LcdMaxLines   0x04


typedef struct
{
    uint8_t v_MaxSupportedLines_U8;
    uint8_t v_MaxSupportedChars_U8;
    uint8_t v_LcdMode_U8;
    gpioPins_et RS;
    gpioPins_et RW;
    gpioPins_et EN;
    gpioPins_et D0;
    gpioPins_et D1;
    gpioPins_et D2;
    gpioPins_et D3;
    gpioPins_et D4;
    gpioPins_et D5;
    gpioPins_et D6;
    gpioPins_et D7;
}LcdConfig_st;

/**************************************************************************************************/





/***************************************************************************************************
                             Function Prototypes
****************************************************************************************************/
void LCD_Init(uint8_t v_lcdNoOfLines_u8, uint8_t v_MaxCharsPerLine_u8);
void LCD_CmdWrite( uint8_t v_lcdCmd_u8);
void LCD_DisplayChar( char v_lcdData_u8);
void LCD_Clear();
void LCD_GoToLine(uint8_t v_lineNumber_u8);
void LCD_GoToNextLine();
void LCD_SetCursor(uint8_t v_lineNumber_u8, uint8_t v_charNumber_u8);
void LCD_DisplayString(char *ptr_stringPointer_u8);
void LCD_ScrollMessage(uint8_t v_lineNumber_u8, char *ptr_msgPointer_u8);
void LCD_DisplayNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToDisplay_u8);
void LCD_DisplayFloatNumber(float v_floatNum_f32);
void LCD_Printf(const char *argList, ...);
void LCD_SetUp(gpioPins_et RS, 
               gpioPins_et RW, 
               gpioPins_et EN,
               gpioPins_et D0, 
               gpioPins_et D1, 
               gpioPins_et D2, 
               gpioPins_et D3,
               gpioPins_et D4,
               gpioPins_et D5,
               gpioPins_et D6,
               gpioPins_et D7 );
/**************************************************************************************************/

#endif
