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

#include <stdio.h>
#include <stdarg.h>
#include <reg51.h>
#include "oled_i2c.h"
#include "stdutils.h"
#include "delay.h"


sbit SCL_PIN = P0^0;
sbit SDA_PIN = P0^1;


uint8_t OledLineNum,OledCursorPos;



/***************************************************************************************************
                                  Local Function Declaration
 ***************************************************************************************************/
void oledSendCommand(uint8_t cmd);
void oledSendStart(uint8_t address);
void oledSendStop(void);
void oledWaitForAck(void);
void oledSendByte(uint8_t ch);
/**************************************************************************************************/


#define FONT_SIZE 5
code const OledFontTable[][FONT_SIZE]=
{
        0x00, 0x00, 0x00, 0x00, 0x00,   // space
        0x00, 0x00, 0x2f, 0x00, 0x00,   // !
        0x00, 0x07, 0x00, 0x07, 0x00,   // "
        0x14, 0x7f, 0x14, 0x7f, 0x14,   // #
        0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $
        0x23, 0x13, 0x08, 0x64, 0x62,   // %
        0x36, 0x49, 0x55, 0x22, 0x50,   // &
        0x00, 0x05, 0x03, 0x00, 0x00,   // '
        0x00, 0x1c, 0x22, 0x41, 0x00,   // (
        0x00, 0x41, 0x22, 0x1c, 0x00,   // )
        0x14, 0x08, 0x3E, 0x08, 0x14,   // *
        0x08, 0x08, 0x3E, 0x08, 0x08,   // +
        0x00, 0x00, 0xA0, 0x60, 0x00,   // ,
        0x08, 0x08, 0x08, 0x08, 0x08,   // -
        0x00, 0x60, 0x60, 0x00, 0x00,   // .
        0x20, 0x10, 0x08, 0x04, 0x02,   // /

        0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0
        0x00, 0x42, 0x7F, 0x40, 0x00,   // 1
        0x42, 0x61, 0x51, 0x49, 0x46,   // 2
        0x21, 0x41, 0x45, 0x4B, 0x31,   // 3
        0x18, 0x14, 0x12, 0x7F, 0x10,   // 4
        0x27, 0x45, 0x45, 0x45, 0x39,   // 5
        0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6
        0x01, 0x71, 0x09, 0x05, 0x03,   // 7
        0x36, 0x49, 0x49, 0x49, 0x36,   // 8
        0x06, 0x49, 0x49, 0x29, 0x1E,   // 9

        0x00, 0x36, 0x36, 0x00, 0x00,   // :
        0x00, 0x56, 0x36, 0x00, 0x00,   // ;
        0x08, 0x14, 0x22, 0x41, 0x00,   // <
        0x14, 0x14, 0x14, 0x14, 0x14,   // =
        0x00, 0x41, 0x22, 0x14, 0x08,   // >
        0x02, 0x01, 0x51, 0x09, 0x06,   // ?
        0x32, 0x49, 0x59, 0x51, 0x3E,   // @

        0x7C, 0x12, 0x11, 0x12, 0x7C,   // A
        0x7F, 0x49, 0x49, 0x49, 0x36,   // B
        0x3E, 0x41, 0x41, 0x41, 0x22,   // C
        0x7F, 0x41, 0x41, 0x22, 0x1C,   // D
        0x7F, 0x49, 0x49, 0x49, 0x41,   // E
        0x7F, 0x09, 0x09, 0x09, 0x01,   // F
        0x3E, 0x41, 0x49, 0x49, 0x7A,   // G
        0x7F, 0x08, 0x08, 0x08, 0x7F,   // H
        0x00, 0x41, 0x7F, 0x41, 0x00,   // I
        0x20, 0x40, 0x41, 0x3F, 0x01,   // J
        0x7F, 0x08, 0x14, 0x22, 0x41,   // K
        0x7F, 0x40, 0x40, 0x40, 0x40,   // L
        0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M
        0x7F, 0x04, 0x08, 0x10, 0x7F,   // N
        0x3E, 0x41, 0x41, 0x41, 0x3E,   // O
        0x7F, 0x09, 0x09, 0x09, 0x06,   // P
        0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q
        0x7F, 0x09, 0x19, 0x29, 0x46,   // R
        0x46, 0x49, 0x49, 0x49, 0x31,   // S
        0x01, 0x01, 0x7F, 0x01, 0x01,   // T
        0x3F, 0x40, 0x40, 0x40, 0x3F,   // U
        0x1F, 0x20, 0x40, 0x20, 0x1F,   // V
        0x3F, 0x40, 0x38, 0x40, 0x3F,   // W
        0x63, 0x14, 0x08, 0x14, 0x63,   // X
        0x07, 0x08, 0x70, 0x08, 0x07,   // Y
        0x61, 0x51, 0x49, 0x45, 0x43,   // Z

        0x00, 0x7F, 0x41, 0x41, 0x00,   // [
        0x55, 0xAA, 0x55, 0xAA, 0x55,   // Backslash (Checker pattern)
        0x00, 0x41, 0x41, 0x7F, 0x00,   // ]
        0x04, 0x02, 0x01, 0x02, 0x04,   // ^
        0x40, 0x40, 0x40, 0x40, 0x40,   // _
        0x00, 0x03, 0x05, 0x00, 0x00,   // `

        0x20, 0x54, 0x54, 0x54, 0x78,   // a
        0x7F, 0x48, 0x44, 0x44, 0x38,   // b
        0x38, 0x44, 0x44, 0x44, 0x20,   // c
        0x38, 0x44, 0x44, 0x48, 0x7F,   // d
        0x38, 0x54, 0x54, 0x54, 0x18,   // e
        0x08, 0x7E, 0x09, 0x01, 0x02,   // f
        0x18, 0xA4, 0xA4, 0xA4, 0x7C,   // g
        0x7F, 0x08, 0x04, 0x04, 0x78,   // h
        0x00, 0x44, 0x7D, 0x40, 0x00,   // i
        0x40, 0x80, 0x84, 0x7D, 0x00,   // j
        0x7F, 0x10, 0x28, 0x44, 0x00,   // k
        0x00, 0x41, 0x7F, 0x40, 0x00,   // l
        0x7C, 0x04, 0x18, 0x04, 0x78,   // m
        0x7C, 0x08, 0x04, 0x04, 0x78,   // n
        0x38, 0x44, 0x44, 0x44, 0x38,   // o
        0xFC, 0x24, 0x24, 0x24, 0x18,   // p
        0x18, 0x24, 0x24, 0x18, 0xFC,   // q
        0x7C, 0x08, 0x04, 0x04, 0x08,   // r
        0x48, 0x54, 0x54, 0x54, 0x20,   // s
        0x04, 0x3F, 0x44, 0x40, 0x20,   // t
        0x3C, 0x40, 0x40, 0x20, 0x7C,   // u
        0x1C, 0x20, 0x40, 0x20, 0x1C,   // v
        0x3C, 0x40, 0x30, 0x40, 0x3C,   // w
        0x44, 0x28, 0x10, 0x28, 0x44,   // x
        0x1C, 0xA0, 0xA0, 0xA0, 0x7C,   // y
        0x44, 0x64, 0x54, 0x4C, 0x44,   // z

        0x00, 0x10, 0x7C, 0x82, 0x00,   // {
        0x00, 0x00, 0xFF, 0x00, 0x00,   // |
        0x00, 0x82, 0x7C, 0x10, 0x00,   // }
        0x00, 0x06, 0x09, 0x09, 0x06    // ~ (Degrees)
};



/**************************************************************************************************
                                void OLED_Init()
 ***************************************************************************************************
 * I/P Arguments:  none
 * Return value : none

 * description  :This function is used to initialize the OLED in the normal mode.
                After initializing the OLED, It clears the OLED and sets the cursor to first line first position. .

 **************************************************************************************************/
void OLED_Init(void)
{ 
    oledSendCommand(SSD1306_DISPLAY_OFF);
    oledSendCommand(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    oledSendCommand(0x80);
    oledSendCommand(SSD1306_SET_MULTIPLEX_RATIO);
    oledSendCommand(0x3F);
    oledSendCommand(SSD1306_SET_DISPLAY_OFFSET);
    oledSendCommand(0x0);
    oledSendCommand(SSD1306_SET_START_LINE | 0x0);
    oledSendCommand(SSD1306_CHARGE_PUMP);
    oledSendCommand(0x14);
    oledSendCommand(SSD1306_MEMORY_ADDR_MODE);
    oledSendCommand(0x00);
    oledSendCommand(SSD1306_SET_SEGMENT_REMAP | 0x1);
    oledSendCommand(SSD1306_COM_SCAN_DIR_DEC);
    oledSendCommand(SSD1306_SET_COM_PINS);
    oledSendCommand(0x12);
    oledSendCommand(SSD1306_SET_CONTRAST_CONTROL);
    oledSendCommand(0xCF);
    oledSendCommand(SSD1306_SET_PRECHARGE_PERIOD);
    oledSendCommand(0xF1);
    oledSendCommand(SSD1306_SET_VCOM_DESELECT);
    oledSendCommand(0x40);
    oledSendCommand(SSD1306_DISPLAY_ALL_ON_RESUME);
    oledSendCommand(SSD1306_NORMAL_DISPLAY);
    oledSendCommand(SSD1306_DISPLAY_ON);

    OLED_Clear();  /* Clear the complete LCD during init */
}





/***************************************************************************************************
                       void OLED_DisplayChar( char ch)
 ****************************************************************************************************
 * I/P Arguments: ASCII value of the char to be displayed.
 * Return value    : none

 * description  : This function sends a character to be displayed on LCD.
                  Any valid ascii value can be passed to display respective character

 ****************************************************************************************************/
void OLED_DisplayChar(uint8_t ch)
{
    uint8_t dat,i=0;

    if(((OledCursorPos+FONT_SIZE)>=128) || (ch=='\n'))
    {
        /* If the cursor has reached to end of line on page1
        OR NewLine command is issued Then Move the cursor to next line */
        OLED_GoToNextLine();
    }
    if(ch!='\n') /* TODO */
    {
        ch = ch-0x20; // As the lookup table starts from Space(0x20)

        while(1)
        {
            dat= OledFontTable[ch][i]; /* Get the data to be displayed for LookUptable*/


            oledSendByte(dat); /* Display the data and keep track of cursor */
            OledCursorPos++;

            i++;

            if(i==FONT_SIZE) /* Exit the loop if End of char is encountered */
            {
                oledSendByte(0x00); /* Display the data and keep track of cursor */
                OledCursorPos++;
                break;
            }
        }
    }
}






/***************************************************************************************************
                       void OLED_DisplayString(char *ptr_stringPointer_u8)
 ****************************************************************************************************
 * I/P Arguments: String(Address of the string) to be displayed.
 * Return value    : none

 * description  :
               This function is used to display the ASCII string on the lcd.
                 1.The ptr_stringPointer_u8 points to the first char of the string
                    and traverses till the end(NULL CHAR)and displays a char each time.

 ****************************************************************************************************/
#if(Enable_OLED_DisplayString==1)
void OLED_DisplayString(uint8_t *ptr)
{
    while(*ptr)
        OLED_DisplayChar(*ptr++);
}
#endif





/***************************************************************************************************
               void OLED_ScrollMessage(uint8_t v_lineNumber_u8, char *ptr_msgPointer_u8)
 ****************************************************************************************************
 * I/P Arguments:
                  uint8_t  : Line number on which the message has to be scrolled
                  char *: pointer to the string to be scrolled

 * Return value    : none

 * description  :This function scrolls the given message on the specified line.
                 If the specified line number is out of range then the message
                 will be scrolled on first line
 ****************************************************************************************************/
#if (Enable_OLED_ScrollMessage == 1)
void OLED_ScrollMessage(uint8_t lineNum, char *strptr)
{
    unsigned char i,j,k,l,cursor,ch;

    if(lineNum > 7)
        lineNum = 0; // Select first line if the lineNumberToStartDisplay is out of range

    for(i=0;strptr[i];i++)
    {
        /* Loop to display the complete string,    each time 16 chars are displayed and
        pointer is incremented to point to next char */

        for(k=0;k<6;k++)
        {
            OLED_SetCursor(lineNum,6-k);     //Move the Cursor to first line
            cursor = 6-k;

            for(j=0;(strptr[i+j] && (cursor<128));j++)
            {
                ch = strptr[i+j]-0x20;
                for(l=0;(l<5) && (cursor<128);l++)//Display first 16 Chars or till Null char is reached
                {
                    oledSendByte(OledFontTable[ch][l]);
                    cursor++;
                }

                oledSendByte(0);
                DELAY_us(10);
                cursor++;
            }
            DELAY_ms(20);
        }
    }
}
#endif





/***************************************************************************************************
void OLED_DisplayNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToDisplay_u8)
 ****************************************************************************************************
 * Function name:  OLED_DisplayNumber()
 * I/P Arguments:
                  uint8_t :  specifies type of number C_BINARY_U8(2),C_DECIMAL_U8(10), C_HEX_U8(16)
                  uint32_t: Number to be displayed on the LCD.
                  uint8_t : Number of digits to be displayed

 * Return value    : none

 * description  :This function is used to display a max of 10digit decimal/Hex number OR specified
                 number of bits for binary number.

                1st parameter specifies type of number C_BINARY_U8(2),C_DECIMAL_U8(10), C_HEX_U8(16)
                3rd parameter specifies the number of digits from the right side to be displayed
                 The output for the input combinations is as below

    Binary:     1.(2,10,4) then 4-LSB will be displayed ie. 1010
                2.(C_BINARY_U8,10,8) then 8-LSB will be displayed ie. 00001010
                3.(C_BINARY_U8,10,2) then 2-LSB will be displayed ie. 10

    Decimal:    4.(10,12345,4) then 4-digits ie. 2345 will be displayed
                5.(C_DECIMAL_U8,12345,6) then 6-digits ie. 012345 will be displayed
                6.(10,12345,C_DisplayDefaultDigits_U8) then 12345 will be displayed.\

    Hex:        7.(16,0x12AB,3) then 3-digits ie. 2AB will be displayed
                8.(C_HEX_U8,0x12AB,6) then 6-digits ie. 0012AB will be displayed
                9.(C_HEX_U8,0x12AB,C_DisplayDefaultDigits_U8) then 12AB will be displayed.
 ****************************************************************************************************/
#if ((Enable_OLED_DisplayNumber == 1) || (Enable_OLED_DisplayFloatNumber == 1) || (Enable_OLED_Printf==1))
void OLED_DisplayNumber(uint8_t v_numericSystem_u8, uint32_t v_number_u32, uint8_t v_numOfDigitsToDisplay_u8)
{
    uint8_t i=0,a[10];

    if(C_BINARY_U8 == v_numericSystem_u8)
    {
        while(v_numOfDigitsToDisplay_u8!=0)
        {
            /* Start Extracting the bits from the specified bit positions.
          Get the Acsii values of the bits and display */
            i = util_GetBitStatus(v_number_u32,(v_numOfDigitsToDisplay_u8-1));
            OLED_DisplayChar(util_Dec2Ascii(i));
            v_numOfDigitsToDisplay_u8--;
        }
    }
    else if(v_number_u32==0)
    {
        /* If the number is zero then update the array with the same for displaying */
        for(i=0;((i<v_numOfDigitsToDisplay_u8) && (i<C_MaxDigitsToDisplay_U8));i++)
            OLED_DisplayChar('0');
    }
    else
    {
        for(i=0;i<v_numOfDigitsToDisplay_u8;i++)
        {
            /* Continue extracting the digits from right side
               till the Specified v_numOfDigitsToDisplay_u8 */
            if(v_number_u32!=0)
            {
                /* Extract the digits from the number till it becomes zero.
                First get the remainder and divide the number by TypeOfNum(10-Dec, 16-Hex) each time.

                example for Decimal number:
                If v_number_u32 = 123 then extracted remainder will be 3 and number will be 12.
                The process continues till it becomes zero or max digits reached*/
                a[i]=util_GetMod32(v_number_u32,v_numericSystem_u8);
                v_number_u32=v_number_u32/v_numericSystem_u8;
            }
            else if( (v_numOfDigitsToDisplay_u8 == C_DisplayDefaultDigits_U8) ||
                    (v_numOfDigitsToDisplay_u8 > C_MaxDigitsToDisplay_U8))
            {
                /* Stop the iteration if the Max number of digits are reached or
                 the user expects exact(Default) digits in the number to be displayed */
                break;
            }
            else
            {
                /* In case user expects more digits to be displayed than the actual digits in number,
                  then update the remaining digits with zero.
               Ex: v_num_u32 is 123 and user wants five digits then 00123 has to be displayed */
                a[i]=0;
            }
        }

        while(i!=0)
        {
            /* Finally get the ascii values of the digits and display*/
            OLED_DisplayChar(util_Hex2Ascii(a[i-1]));
            i--;
        }
    }
}
#endif








/*************************************************************************************************
            void  OLED_DisplayFloatNumber(double v_floatNum_f32)
 **************************************************************************************************
 * Function name:  OLED_DisplayFloatNumber()
 * I/P Arguments: float: float Number to be displayed on the LCD.

 * Return value    : none

 * description  :This function is used to display a floating point number
                 It supports 6digits of precision.

    Note: Float will be disabled by default as it takes huge controller resources
         It can be enabled by changing value of Enable_OLED_DisplayFloatNumber to 1 in lcd.h
 ***************************************************************************************************/
#if (Enable_OLED_DisplayFloatNumber == 1)
void OLED_DisplayFloatNumber(double v_floatNum_f32)
{
    uint32_t v_temp_u32;
    /* Dirty hack to support the floating point by extracting the integer and fractional part.
      1.Type cast the number to int to get the integer part.
      2.Display the extracted integer part followed by a decimal point(.)
      3.Later the integer part is made zero by subtracting with the extracted integer value.
      4.Finally the fractional part is multiplied by 100000 to support 6-digit precision */

    v_temp_u32 = (uint32_t) v_floatNum_f32;
    OLED_DisplayNumber(C_DECIMAL_U8,v_temp_u32,C_DisplayDefaultDigits_U8);

    OLED_DisplayChar('.');

    v_floatNum_f32 = v_floatNum_f32 - v_temp_u32;
    v_temp_u32 = v_floatNum_f32 * 1000000;
    OLED_DisplayNumber(C_DECIMAL_U8,v_temp_u32,C_DisplayDefaultDigits_U8);
}
#endif






/*************************************************************************************************
            void OLED_Printf(const char *argList, ...)
 **************************************************************************************************
 * Function name:  OLED_Printf()
 * I/P Arguments: variable length arguments similar to printf

 * Return value    : none

 * description  :This function is similar to printf function in C.
                 It takes the arguments with specified format and prints accordingly
                 The supported format specifiers are as below.
                 1. %c: character
                 2. %d: signed 16-bit number
                 3. %D: signed 32-bit number
                 4. %u: unsigned 16-bit number
                 5. %U: unsigned 32-bit number
                 6. %b: 16-bit binary number
                 7. %B: 32-bit binary number
                 8. %f: Float number
                 9. %x: 16-bit hexadecimal number
                 10. %X: 32-bit hexadecimal number
                 11. %s: String



  Extra feature is available to specify the number of digits to be displayed using printf.
     ex: %4d: will display the lower four digits of the decimal number.
         %12b: will display the 12-LSB of the number
         %d: Will display the exact digits of the number

#####: In case of printing the 8-bit variables, it is recommended to type cast and promote them to uint16_t.
        uint8_t v_Num_u8;
        OLED_Printf("num1:%u",(uint16_t)v_Num_u8);
 **************************************************************************************************/
#if ( Enable_OLED_Printf == 1 )
void OLED_Printf(const char *argList, ...)
{
    const char *ptr;
    va_list argp;
    sint16_t v_num_s16;
    sint32_t v_num_s32;
    uint16_t v_num_u16;
    uint32_t v_num_u32;
    char *str;
    char  ch;
    uint8_t v_numOfDigitsToDisp_u8;
#if (Enable_OLED_DisplayFloatNumber == 1)
    double v_floatNum_f32;
#endif

    va_start(argp, argList);

    /* Loop through the list to extract all the input arguments */
    for(ptr = argList; *ptr != '\0'; ptr++)
    {

        ch= *ptr;
        if(ch == '%')         /*Check for '%' as there will be format specifier after it */
        {
            ptr++;
            ch = *ptr;
            if((ch>=0x30) && (ch<=0x39))
            {
                v_numOfDigitsToDisp_u8 = 0;
                while((ch>=0x30) && (ch<=0x39))
                {
                    v_numOfDigitsToDisp_u8 = (v_numOfDigitsToDisp_u8 * 10) + (ch-0x30);
                    ptr++;
                    ch = *ptr;
                }
            }
            else
            {
                v_numOfDigitsToDisp_u8 = C_MaxDigitsToDisplayUsingPrintf_U8;
            }


            switch(ch)       /* Decode the type of the argument */
            {
            case 'C':
            case 'c':     /* Argument type is of char, hence read char data from the argp */
                ch = va_arg(argp, int);
                OLED_DisplayChar(ch);
                break;

            case 'd':    /* Argument type is of signed integer, hence read 16bit data from the argp */
                v_num_s16 = va_arg(argp, int);
                if(v_num_s16<0)
                { /* If the number is -ve then display the 2's complement along with '-' sign */
                    v_num_s16 = -v_num_s16;
                    OLED_DisplayChar('-');
                }
                OLED_DisplayNumber(C_DECIMAL_U8,v_num_s16,v_numOfDigitsToDisp_u8);
                break;

            case 'D':    /* Argument type is of integer, hence read 16bit data from the argp */
                v_num_s32 = va_arg(argp, sint32_t);
                if(v_num_s32<0)
                { /* If the number is -ve then display the 2's complement along with '-' sign */
                    v_num_s32 = -v_num_s32;
                    OLED_DisplayChar('-');
                }
                OLED_DisplayNumber(C_DECIMAL_U8,v_num_s32,v_numOfDigitsToDisp_u8);
                break;

            case 'u':    /* Argument type is of unsigned integer, hence read 16bit unsigned data */
                v_num_u16 = va_arg(argp, int);
                OLED_DisplayNumber(C_DECIMAL_U8,v_num_u16,v_numOfDigitsToDisp_u8);
                break;

            case 'U':    /* Argument type is of integer, hence read 32bit unsigend data */
                v_num_u32 = va_arg(argp, uint32_t);
                OLED_DisplayNumber(C_DECIMAL_U8,v_num_u32,v_numOfDigitsToDisp_u8);
                break;

            case 'x':  /* Argument type is of hex, hence hexadecimal data from the argp */
                v_num_u16 = va_arg(argp, int);
                OLED_DisplayNumber(C_HEX_U8,v_num_u16,v_numOfDigitsToDisp_u8);
                break;

            case 'X':  /* Argument type is of hex, hence hexadecimal data from the argp */
                v_num_u32 = va_arg(argp, uint32_t);
                OLED_DisplayNumber(C_HEX_U8,v_num_u32,v_numOfDigitsToDisp_u8);
                break;


            case 'b':  /* Argument type is of binary,Read int and convert to binary */
                v_num_u16 = va_arg(argp, int);
                if(v_numOfDigitsToDisp_u8 == C_MaxDigitsToDisplayUsingPrintf_U8)
                    v_numOfDigitsToDisp_u8 = 16;
                OLED_DisplayNumber(C_BINARY_U8,v_num_u16,v_numOfDigitsToDisp_u8);
                break;

            case 'B':  /* Argument type is of binary,Read int and convert to binary */
                v_num_u32 = va_arg(argp, uint32_t);
                if(v_numOfDigitsToDisp_u8 == C_MaxDigitsToDisplayUsingPrintf_U8)
                    v_numOfDigitsToDisp_u8 = 16;
                OLED_DisplayNumber(C_BINARY_U8,v_num_u32,v_numOfDigitsToDisp_u8);
                break;


            case 'F':
            case 'f': /* Argument type is of float, hence read double data from the argp */
#if (Enable_OLED_DisplayFloatNumber == 1)
                v_floatNum_f32 = va_arg(argp, double);
                OLED_DisplayFloatNumber(v_floatNum_f32);
#endif
                break;


            case 'S':
            case 's': /* Argument type is of string, hence get the pointer to sting passed */
                str = va_arg(argp, char *);
                OLED_DisplayString(str);
                break;

            case '%':
                OLED_DisplayChar('%');
                break;
            }
        }
        else
        {
            /* As '%' is not detected display/transmit the char passed */
            OLED_DisplayChar(ch);
        }
    }

    va_end(argp);
}
#endif






/***************************************************************************************************
                         void OLED_Clear()
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description  :This function clears the LCD and moves the cursor to beginning of first line
 ****************************************************************************************************/
void OLED_Clear()
{
    int i;

    oledSendCommand(SSD1306_SET_COLUMN_ADDR);
    oledSendCommand(0);
    oledSendCommand(127);

    oledSendCommand(SSD1306_SET_PAGE_ADDR);
    oledSendCommand(0);
    oledSendCommand(7);


    oledSendStart(SSD1306_ADDRESS<<1);
    oledSendByte(SSD1306_DATA_CONTINUE);

    for (i=0; i<1024; i++)      // Write Zeros to clear the display
    {
        oledSendByte(0);
    }

    oledSendCommand(SSD1306_SET_COLUMN_ADDR);
    oledSendCommand(0);
    oledSendCommand(127);

    oledSendCommand(SSD1306_SET_PAGE_ADDR);
    oledSendCommand(0);
    oledSendCommand(7);	  

    oledSendStart(SSD1306_ADDRESS<<1);
    oledSendByte(SSD1306_DATA_CONTINUE);
}





/***************************************************************************************************
                         void OLED_GoToLine(uint8_t v_lineNumber_u8)
 ****************************************************************************************************
 * I/P Arguments: uint8_t: Line number(0-7).
 * Return value    : none

 * description  :This function moves the Cursor to beginning of the specified line.
        If the requested line number is out of range, it will not move the cursor.

 Note: The line numbers run from 0 to 7
 ****************************************************************************************************/
#if (Enable_OLED_GoToLine == 1)
void  OLED_GoToLine(uint8_t lineNumber)
{
    if(lineNumber<8)
    {   /* If the line number is within range
         then move it to specified line and keep track*/
        OledLineNum = lineNumber;
        OLED_SetCursor(OledLineNum,0);
    }
}
#endif






/***************************************************************************************************
                         void  OLED_GoToNextLine()
 ****************************************************************************************************
 * I/P Arguments: none
 * Return value    : none

 * description  :This function moves the Cursor to beginning of the next line.
        If the cursor is on last line and NextLine command is issued then
        it will move the cursor to first line.
 ****************************************************************************************************/
void  OLED_GoToNextLine()
{
    /*Increment the current line number.
      In case it exceeds the limit, rool it back to first line */
    OledLineNum++;
    OledLineNum = OledLineNum&0x07;
    OLED_SetCursor(OledLineNum,0); /* Finally move it to next line */
}







/***************************************************************************************************
                void OLED_SetCursor(char v_lineNumber_u8,char v_charNumber_u8)
 ****************************************************************************************************
 * I/P Arguments: char row,char col
                 row -> line number(line1=1, line2=2),
                        For 2line LCD the I/P argument should be either 1 or 2.
                 col -> char number.
                        For 16-char LCD the I/P argument should be between 0-15.
 * Return value    : none

 * description  :This function moves the Cursor to specified position

                   Note:If the Input(Line/Char number) are out of range
                        then no action will be taken
 ****************************************************************************************************/
void OLED_SetCursor(uint8_t lineNumber,uint8_t cursorPosition)
{
    /* Move the Cursor to specified position only if it is in range */
    if((lineNumber <= C_OledLastLine_U8) && (cursorPosition <= 127))
    {
        OledLineNum=lineNumber;   /* Save the specified line number */
        OledCursorPos=cursorPosition; /* Save the specified cursor position */

        oledSendCommand(SSD1306_SET_COLUMN_ADDR);
        oledSendCommand(cursorPosition);
        oledSendCommand(127);

        oledSendCommand(SSD1306_SET_PAGE_ADDR);
        oledSendCommand(lineNumber);
        oledSendCommand(7);

        oledSendStart(SSD1306_ADDRESS<<1);
        oledSendByte(SSD1306_DATA_CONTINUE);
    }
}




/***************************************************************************************************
                       void OLED_DisplayLogo(char *ptr_Logo)
 ****************************************************************************************************
 * I/P Arguments   : Array Bit Map(Address of Bit Map) to be displayed.
 * Return value    : none

 * description  :
               This function is used to display the logo for using the bit map.
               User should pass the array/address of bitmap for diplay the logo.
               User can enable/disable the inversion of the dislpay by using the below functions.
               OLED_EnableInversion/OLED_DisableInversion
 ****************************************************************************************************/
#if (Enable_OLED_DisplayLogo == 1)
void OLED_DisplayLogo(char *ptr_Logo)
{
    int i;

    OLED_SetCursor(0,0);

    oledSendStart(SSD1306_ADDRESS<<1);
    oledSendByte(SSD1306_DATA_CONTINUE);

    for ( i=0; i<1024; i++)      // Send data
    {
        oledSendByte(ptr_Logo[i]);
    }
}
#endif





/***************************************************************************************************
void OLED_VerticalGraph(uint8_t barGraphNumber, uint8_t percentageValue)
 ****************************************************************************************************
 * I/P Arguments   : barGraphNumber : position of bar ( 0 to 3 )
                     percentageValue : value of the bar in percentage(0-100)
 * Return value    : none

 * description  :
                This function displays bar graph in horizontal direction.
 ****************************************************************************************************/
#if (ENABLE_OLED_VerticalGraph ==1)
void OLED_VerticalGraph(uint8_t barGraphNumber, uint8_t percentageValue)
{
    uint8_t lineNumberToStartDisplay,i,j,barGraphPosition;
    uint8_t lineNumber,valueToDisplay;


    if((barGraphNumber < C_MaxBarGraphs_U8) && (percentageValue<=100))
    {
        barGraphPosition = barGraphNumber * 32;

        OLED_SetCursor(0,barGraphPosition+8);
        OLED_DisplayNumber(E_DECIMAL,percentageValue,3);


        /* Divide the value by 8, as we have 8-pixels for each line */
        percentageValue = percentageValue/2;
        lineNumberToStartDisplay = (percentageValue>>3);
        lineNumber = 7-lineNumberToStartDisplay;


        for(i=1;i<8;i++)
        {
            OLED_SetCursor(i,(barGraphPosition+12));
            if(i<lineNumber)
            {
                valueToDisplay = 0x00;
            }
            else if(i== lineNumber)
            {
                valueToDisplay = util_GetMod8(percentageValue,8);
                valueToDisplay = (0xff<<(8-valueToDisplay));
            }
            else
            {
                valueToDisplay = 0xff;
            }

            for(j=0;j<12;j++)
            {
                oledSendByte(valueToDisplay);
            }
        }
    }
}
#endif




/***************************************************************************************************
    void OLED_DisplayHorizontalGraph(uint8_t barGraphNumber, uint8_t percentageValue)
 ****************************************************************************************************
 * I/P Arguments   : barGraphNumber : position of bar ( 0 to 3 )
                     percentageValue : value of the bar in percentage(0-100)
 * Return value    : none

 * description  :
                This function displays bar graph in vertical direction.
 ****************************************************************************************************/
#if (ENABLE_OLED_HorizontalGraph ==1)
void OLED_HorizontalGraph(uint8_t barGraphNumber, uint8_t percentageValue)
{
    uint8_t lineNumberToStartDisplay,i;
    lineNumberToStartDisplay = (barGraphNumber * 2)+1;

    if((barGraphNumber < C_MaxBarGraphs_U8) && (percentageValue<=100))
    {
        OLED_SetCursor(lineNumberToStartDisplay,0);

        for(i=0;i<percentageValue;i++)
        {
            oledSendByte(0xff);
        }

        for(i=percentageValue;i<100;i++)
        {
            oledSendByte(0x00);
        }

        OLED_SetCursor(lineNumberToStartDisplay,105);

        OLED_DisplayNumber(E_DECIMAL,percentageValue,3);
    }
}
#endif




/***************************************************************************************************
                       void OLED_EnableInversion(void)
 ****************************************************************************************************
 * I/P Arguments   : none.
 * Return value    : none

 * description  :
               This function is used to Enable the display inversion.
               Once this is enabled the background pixels will be turned ON and char pixels will be OFF.

 ****************************************************************************************************/
#if (Enable_OLED_EnableInversion == 1)
void OLED_EnableInversion(void)
{
    oledSendCommand(SSD1306_INVERT_DISPLAY);
}
#endif







/***************************************************************************************************
                       void OLED_DisableInversion(void)
 ****************************************************************************************************
 * I/P Arguments   : none.
 * Return value    : none

 * description  :
               This function is used to clear the display inversion.

 ****************************************************************************************************/
#if (Enable_OLED_DisableInversion == 1)
void OLED_DisableInversion(void)
{
    oledSendCommand(SSD1306_NORMAL_DISPLAY);
}
#endif






/***************************************************************************************************
                       void OLED_SetBrightness(uint8_t brightnessValue)
 ****************************************************************************************************
 * I/P Arguments   : uint8_t: brightness level from 0-255.
 * Return value    : none

 * description  :
               This function is used to adjust the contrast/Brightness of the OLED.

 ****************************************************************************************************/
#if (Enable_OLED_SetBrightness == 1)
void OLED_SetBrightness(uint8_t brightnessValue)
{
    oledSendCommand(SSD1306_SET_CONTRAST_CONTROL);
    oledSendCommand(brightnessValue);
}
#endif






/********************************************************************************
                Local FUnctions for sending the command/data
 ********************************************************************************/

void oledSendStart(uint8_t address)
{
    SDA_PIN = LOW;
    SDA_PIN = HIGH;
    SCL_PIN = HIGH;
    SDA_PIN = LOW;
    SCL_PIN = LOW;
    oledSendByte(address);
}


void oledSendStop()
{
    SDA_PIN = LOW;
    SCL_PIN = HIGH;
    SDA_PIN = LOW;	
    SDA_PIN = HIGH;
}


void oledWaitForAck()
{
    SDA_PIN = HIGH; //Configure SDA_PIN as Input to read the ACK                //delay_us(1);
    SCL_PIN = HIGH;
    while(SDA_PIN==HIGH);
    SCL_PIN = LOW;
}


void oledSendByte(uint8_t ch)
{
    char i;		 

    SCL_PIN = LOW;
    for ( i = 7; i>=0; i--)
    {
        SDA_PIN = (ch >> (i)) & 0x1; 
        SCL_PIN = HIGH; 
        SCL_PIN = LOW;  
    }

    oledWaitForAck();
}


void oledSendCommand(uint8_t cmd)
{
    oledSendStart(SSD1306_ADDRESS<<1);
    oledSendByte(SSD1306_COMMAND);
    oledSendByte(cmd);
    oledSendStop();
}

/*****************************************************************************************************/

