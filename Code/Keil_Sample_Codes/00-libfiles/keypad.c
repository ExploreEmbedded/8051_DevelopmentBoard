/***************************************************************************************************
                                              ExploreEmbedded Copyright Notice 	
 ****************************************************************************************************
 * File:   keypad.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library routines for 4x4 Hex-Keypad

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
 **************************************************************************************************/



/***************************************************************************************************
                             Revision History
 ****************************************************************************************************
15.0: Initial version 
16.0: KEYPAD_Init function is updated to specify the row/col connections as parameters.
      Included the gpio functions to read/write the individual row/col.
 ***************************************************************************************************/


/***************************************************************************************************
                             PORT configurations/Connections
 ****************************************************************************************************
            ___________________
           |    |    |    |    |
           | 0  | 1  | 2  | 3  |--------- R0
           |____|____|____|____|
           |    |    |    |    |
		   | 4  | 5  | 6  | 7  |--------- R1
           |____|____|____|____|
           |    |    |    |    |
		   | 8  | 9  | A  | B  |--------- R2
		   |____|____|____|____|
		   |    |    |    |    |
		   | C  | D  | E  | F  |--------- R3
           |____|____|____|____|
             |    |    |    |
             |    |    |    |____________ C3
             |    |    |
             |    |    |_________________ C2
             |    |
             |    |______________________ C1
             |
             |___________________________ C0

 ****************************************************************************************************/


#include "keypad.h"
#include "delay.h"
#include "gpio.h"

gpioPins_et A_RowsPins_U8[C_MaxRows_U8];
gpioPins_et A_ColsPins_U8[C_MaxCols_U8];         

const uint8_t A_KeyLookUptable_U8[C_MaxRows_U8][C_MaxCols_U8]=
{
	    '0','1','2','3',
      '4','5','6','7',
      '8','9','A','B',
      'C','D','E','F'
};


/***************************************************************************************************
                           local function prototypes
 ***************************************************************************************************/
static void keypad_WaitForKeyRelease(void);
static void keypad_WaitForKeyPress(void);
/**************************************************************************************************/





/***************************************************************************************************
                   void KEYPAD_Init()
 ***************************************************************************************************
 * I/P Arguments:Pin numbers where the rows and columns are conneted.
 * Return value : none

 * description  : This function configures the rows and columns for keypad scan
        1.ROW lines are configured as Output.
        2.Column Lines are configured as Input.
 ***************************************************************************************************/
void KEYPAD_Init(
        gpioPins_et row_0, 
        gpioPins_et row_1, 
        gpioPins_et row_2,
        gpioPins_et row_3, 
        gpioPins_et col_0,
        gpioPins_et col_1, 
        gpioPins_et col_2,
        gpioPins_et col_3 )
{
    uint8_t i;

    A_RowsPins_U8[0] = row_0;
    A_RowsPins_U8[1] = row_1;
    A_RowsPins_U8[2] = row_2;
    A_RowsPins_U8[3] = row_3;

    A_ColsPins_U8[0] = col_0;
    A_ColsPins_U8[1] = col_1;
    A_ColsPins_U8[2] = col_2;
    A_ColsPins_U8[3] = col_3;

    for(i=0;i<C_MaxRows_U8;i++)
    {
        GPIO_PinDirection(A_RowsPins_U8[i],OUTPUT);
    }

    for(i=0;i<C_MaxCols_U8;i++)
    {
        GPIO_PinDirection(A_ColsPins_U8[i],INPUT);
    }
}




/***************************************************************************************************
                   static void keypad_WaitForKeyRelease(void)
 ***************************************************************************************************
 * I/P Arguments:none

 * Return value	: none

 * description  : This function waits till the previous key is released.
 ***************************************************************************************************/
static void keypad_WaitForKeyRelease(void)
{

    uint8_t i,v_keyStatus_u8;

    for (i=0;i<C_MaxRows_U8;i++)
    {
        GPIO_PinWrite(A_RowsPins_U8[i],LOW); 
    }

    do
    {
        do
        {
            v_keyStatus_u8 = 1;
            for(i=0; i<C_MaxCols_U8; i++)
            {
                v_keyStatus_u8 &= GPIO_PinRead(A_ColsPins_U8[i]);
            } 
        }while(v_keyStatus_u8 == 0);

        DELAY_us(C_DebounceTimeInMicroSecond_U16);

        v_keyStatus_u8 = 1;
        for(i=0; i<C_MaxCols_U8; i++)
        {
            v_keyStatus_u8 &= GPIO_PinRead(A_ColsPins_U8[i]);
        } 
    }while(v_keyStatus_u8 == 0);
}
 





/***************************************************************************************************
                   static void keypad_WaitForKeyPress(void)
 ***************************************************************************************************
 * I/P Arguments:none

 * Return value	: none

 * description  : This function waits till a new key is pressed.
                  The new Key pressed can be decoded by the function KEYPAD_GetKey.
 ***************************************************************************************************/
static void keypad_WaitForKeyPress(void)
{
    uint8_t i,v_keyStatus_u8;

    for (i=0;i<C_MaxRows_U8;i++)
    {
        GPIO_PinWrite(A_RowsPins_U8[i],LOW); 
    }

    do
    {
        do
        {
            v_keyStatus_u8 = 1;
            for(i=0; i<C_MaxCols_U8; i++)
            {
                v_keyStatus_u8 &= GPIO_PinRead(A_ColsPins_U8[i]);
            } 
        }while(v_keyStatus_u8 != 0);


        DELAY_us(C_DebounceTimeInMicroSecond_U16);

        v_keyStatus_u8 = 1;
        for(i=0; i<C_MaxCols_U8; i++)
        {
            v_keyStatus_u8 &= GPIO_PinRead(A_ColsPins_U8[i]);
        } 
    }while(v_keyStatus_u8 != 0);
}










/***************************************************************************************************
                   unsigned char KEYPAD_GetKey()
 ***************************************************************************************************
 * I/P Arguments:none

 * Return value	: uint8_t--> ASCII value of the Key Pressed

 * description: This function waits till a key is pressed and returns its ASCII Value
                It follows the following sequences to decode the key pressed:
				1.Wait till the previous key is released..
				2.Wait for the new key press.
				3.Scan all the rows one at a time for the pressed key.
				4.Decodes the key pressed depending on ROW-COL combination and returns its
				  ASCII value.
 ***************************************************************************************************/
uint8_t KEYPAD_GetKey(void)
{
    uint8_t i,j,v_KeyPressed_u8 = 0;


    keypad_WaitForKeyRelease();
    keypad_WaitForKeyPress();

    for (i=0;i<C_MaxRows_U8;i++)
    {
        GPIO_PinWrite(A_RowsPins_U8[i],HIGH); 
    }

    for (i=0;(i<C_MaxRows_U8);i++)
    {
        GPIO_PinWrite(A_RowsPins_U8[i],LOW);

        for(j=0; (j<C_MaxCols_U8); j++)
        {
            if(GPIO_PinRead(A_ColsPins_U8[j]) == 0)
            {
                v_KeyPressed_u8 = 1;
                break;
            }
        } 

        if(v_KeyPressed_u8 ==1)
        {
            break;
        }

        GPIO_PinWrite(A_RowsPins_U8[i],HIGH);
    }

    if(i<C_MaxRows_U8)
        v_KeyPressed_u8 = A_KeyLookUptable_U8[i][j];
    else
        v_KeyPressed_u8 = C_DefaultKey_U8;


    return v_KeyPressed_u8;
}
