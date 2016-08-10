/***************************************************************************************************
                                   ExploreEmbedded Copyright Notice 
****************************************************************************************************
 * File:   oled_i2c.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: SSD1306 I2C OLED library to display strings, numbers, graphs and logos

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider 
buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php
EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 
Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/


/* The orginal Arduino libaray from rinkyDink is modified for low end controllers with small RAM memory.
    ExploreEmbedded oled_i2c.c library does not have a RAM buffer and hence different fonts and graphics are not supported.
	You can download the arduino library from this link http://www.rinkydinkelectronics.com/library.php?id=79 .
		
  OLED_I2C.cpp - Arduino/chipKit library support for 128x64 pixel SSD1306 OLEDs
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
  This library has been made to make it easy to use 128x64 pixel OLED displays
  based on the SSD1306 controller chip with an Arduino or a chipKit.

  You can always find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#ifndef _OLED_I2C_H_
#define _OLED_I2C_H_
#include "stdutils.h"


/******************************************************************************
                      SSD1306 ID and Command List
******************************************************************************/
#define SSD1306_ADDRESS		0x3C

#define SSD1306_COMMAND			0x00
#define SSD1306_DATA			0xC0
#define SSD1306_DATA_CONTINUE	0x40

#define SSD1306_SET_CONTRAST_CONTROL					0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME					0xA4
#define SSD1306_DISPLAY_ALL_ON							0xA5
#define SSD1306_NORMAL_DISPLAY							0xA6
#define SSD1306_INVERT_DISPLAY							0xA7
#define SSD1306_DISPLAY_OFF								0xAE
#define SSD1306_DISPLAY_ON								0xAF
#define SSD1306_NOP										0xE3

#define SSD1306_HORIZONTAL_SCROLL_RIGHT					0x26
#define SSD1306_HORIZONTAL_SCROLL_LEFT					0x27
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_RIGHT	0x29
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_LEFT		0x2A
#define SSD1306_DEACTIVATE_SCROLL						0x2E
#define SSD1306_ACTIVATE_SCROLL							0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA				0xA3

#define SSD1306_SET_LOWER_COLUMN						0x00
#define SSD1306_SET_HIGHER_COLUMN						0x10
#define SSD1306_MEMORY_ADDR_MODE						0x20
#define SSD1306_SET_COLUMN_ADDR							0x21
#define SSD1306_SET_PAGE_ADDR							0x22

#define SSD1306_SET_START_LINE							0x40
#define SSD1306_SET_SEGMENT_REMAP						0xA0
#define SSD1306_SET_MULTIPLEX_RATIO						0xA8
#define SSD1306_COM_SCAN_DIR_INC						0xC0
#define SSD1306_COM_SCAN_DIR_DEC						0xC8
#define SSD1306_SET_DISPLAY_OFFSET						0xD3
#define SSD1306_SET_COM_PINS							0xDA
#define SSD1306_CHARGE_PUMP								0x8D

#define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO				0xD5
#define SSD1306_SET_PRECHARGE_PERIOD					0xD9
#define SSD1306_SET_VCOM_DESELECT						0xDB
/****************************************************************************/





/***************************************************************************************************
                             Commonly used LCD macros/Constants
***************************************************************************************************/
#define C_DefaultDigits     10

#define C_OledFirstLine_U8 0x00u
#define C_OledLastLine_U8  0x07u

#define C_FirstLineAddress_U8 0xB8
#define C_LastLineAddress_U8  0xBF

#define C_DisplayDefaultDigits_U8            0xffu // Will display the exact digits in the number
#define C_MaxDigitsToDisplay_U8              10u   // Max decimal/hexadecimal digits to be displayed
#define C_NumOfBinDigitsToDisplay_U8         16u   // Max bits of a binary number to be displayed
#define C_MaxDigitsToDisplayUsingPrintf_U8   C_DisplayDefaultDigits_U8 /* Max dec/hexadecimal digits to be displayed using printf */

#define C_MaxBarGraphs_U8     4
/**************************************************************************************************/



/***************************************************************************************************
                 PreCompile configurations to enable/disable the functions
****************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring its respective macros to 1/0.
 2. By default all the API's are disabled.
 3. Displaying of floating number takes huge controller resources and need to be enabled only
    if required. This implies for other interfaces as well.
****************************************************************************************************/
#define    Enable_OLED_DisplayString          0
#define    Enable_OLED_ScrollMessage          0
#define    Enable_OLED_DisplayNumber          0
#define    Enable_OLED_DisplayFloatNumber     0
#define    Enable_OLED_Printf                 0
#define    Enable_OLED_DisplayLogo            1
#define    Enable_OLED_EnableInversion        0
#define    Enable_OLED_DisableInversion       0
#define    ENABLE_OLED_VerticalGraph          0
#define    ENABLE_OLED_HorizontalGraph        0
#define    Enable_OLED_SetBrightness          0
#define    Enable_OLED_GoToLine               0
/**************************************************************************************************/


/***************************************************************************************************
                                Logo bit map declaration
 ***************************************************************************************************/
extern code const unsigned char LogoBitMap[];
/**************************************************************************************************/



/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
void OLED_Init(void);
void OLED_DisplayChar(uint8_t ch);
void OLED_DisplayString(uint8_t *);
void OLED_ScrollMessage(uint8_t lineNum, char *strptr);
void OLED_DisplayNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToDisplay_u8);
void OLED_DisplayFloatNumber(double v_floatNum_f32);
void OLED_Printf(const char *argList, ...);
void OLED_Clear(void);
void OLED_GoToPage(uint8_t );
void OLED_GoToLine(uint8_t );
void OLED_GoToNextLine(void);
void OLED_SetCursor(uint8_t lineNumber,uint8_t CursorPosition);
void OLED_DisplayLogo(char *ptr_Logo);
void OLED_EnableInversion(void);
void OLED_DisableInversion(void);
void OLED_VerticalGraph(uint8_t var_barGraphNumber_u8, uint8_t var_percentageValue_u8);
void OLED_HorizontalGraph(uint8_t var_barGraphNumber_u8, uint8_t var_percentageValue_u8);
/**************************************************************************************************/   

#endif

