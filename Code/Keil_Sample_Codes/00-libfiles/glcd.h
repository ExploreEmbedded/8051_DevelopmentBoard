/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
*****************************************************************************************************
 * File:   glcd.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the Library routines for KS108 Graphical LCD(GLCD)

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
#ifndef  _GLCD_H_
#define  _GLCD_H_

#include <stdarg.h>
#include "stdutils.h"
#include "delay.h"


/***************************************************************************************************
                               LCD PORT Configuration
 ***************************************************************************************************/
#define LcdDataBus    P2
#define LcdControlBus P0

#define RS 		0
#define RW		1
#define EN		2
#define CS1		3
#define CS2		4
/**************************************************************************************************/



/***************************************************************************************************
                             Commonly used LCD macros/Constants
***************************************************************************************************/
#define C_DefaultDigits 	10

#define C_GlcdFirstLine_U8 0x00u
#define C_GlcdLastLine_U8  0x07u

#define C_FirstLineAddress_U8 0xB8
#define C_LastLineAddress_U8  0xBF

#define C_DisplayDefaultDigits_U8            0xffu // Will display the exact digits in the number
#define C_MaxDigitsToDisplay_U8              10u   // Max decimal/hexadecimal digits to be displayed
#define C_NumOfBinDigitsToDisplay_U8         16u   // Max bits of a binary number to be displayed
#define C_MaxDigitsToDisplayUsingPrintf_U8   C_DisplayDefaultDigits_U8 /* Max dec/hexadecimal digits to be displayed using printf */

#define C_MaxBarGraphs_U8     4

#define GlcdClearBit(x)    util_BitClear((LcdControlBus),(x))
#define GlcdSetBit(x)      util_BitSet((LcdControlBus),(x))

#define BUSY_FLAG     7
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
#define    Enable_GLCD_DisplayString          1
#define    Enable_GLCD_ScrollMessage          0
#define    Enable_GLCD_DisplayNumber          1
#define    Enable_GLCD_DisplayFloatNumber     0
#define    Enable_GLCD_Printf                 1
#define    Enable_GLCD_DisplayLogo            1
#define    Enable_GLCD_EnableInversion        0
#define    Enable_GLCD_DisableInversion       0
#define    ENABLE_GLCD_VerticalGraph          1
#define    ENABLE_GLCD_HorizontalGraph        1
/**************************************************************************************************/


/***************************************************************************************************
                                 Struct/Enums used
 ***************************************************************************************************/

typedef struct{
	uint8_t PageNum;
	uint8_t LineNum;
	uint8_t CursorPos;
	uint8_t Invertdisplay;
}GLCD_Config;

extern code const unsigned char LogoBitMap[];
/**************************************************************************************************/



/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
void GLCD_Init(void);
void GLCD_DisplayChar(uint8_t ch);
void GLCD_DisplayString(uint8_t *);
void GLCD_ScrollMessage(uint8_t lineNum, char *strptr);
void GLCD_DisplayNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToDisplay_u8);
void GLCD_DisplayFloatNumber(double v_floatNum_f32);
void GLCD_Printf(const char *argList, ...);
void GLCD_Clear(void);
void GLCD_GoToPage(uint8_t );
void GLCD_GoToLine(uint8_t );
void GLCD_GoToNextLine(void);
void GLCD_SetCursor(uint8_t lineNumber,uint8_t CursorPosition);
void GLCD_DisplayLogo(char *ptr_Logo);
void GLCD_EnableInversion(void);
void GLCD_DisableInversion(void);
void GLCD_VerticalGraph(uint8_t var_barGraphNumber_u8, uint8_t var_percentageValue_u8);
void GLCD_HorizontalGraph(uint8_t var_barGraphNumber_u8, uint8_t var_percentageValue_u8);
/**************************************************************************************************/

#endif