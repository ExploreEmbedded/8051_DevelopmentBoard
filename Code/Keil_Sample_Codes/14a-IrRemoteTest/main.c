/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice 
****************************************************************************************************
 * File:   necIrRemoteExample1.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Sample program to decode NEC IR Remote pulses and display on LCD using 8051 controller.
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

/*************************
  NEC IR Remote Codes 
**************************  
0xFFA25D: CH-       
0xFF629D: CH        
0xFFE21D: CH+       
0xFF22DD: PREV      
0xFF02FD: NEXT      
0xFFC23D: PLAY/PAUSE
0xFFE01F: VOL-      
0xFFA857: VOL+      
0xFF906F: EQ        
0xFF6897: 0         
0xFF9867: 100+      
0xFFB04F: 200+      
0xFF30CF: 1         
0xFF18E7: 2         
0xFF7A85: 3         
0xFF10EF: 4         
0xFF38C7: 5         
0xFF5AA5: 6         
0xFF42BD: 7         
0xFF4AB5: 8         
0xFF52AD: 9 
**************************/

#include <reg51.h>
#include "lcd.h"
#include "stdutils.h"

uint32_t bitPattern=0,newKey=0;
uint8_t timerValue;
uint8_t msCount=0;
char pulseCount=0;


void timer0_isr() interrupt 1
{
    if(msCount<50)
        msCount++;

    TH0 = 0xFC;   // Reload the timer value for 1ms Delay
    TL0 = 0x67;
}



void externalIntr0_ISR()  interrupt 0
{
    timerValue = msCount;
    msCount = 0;

    TH0 = 0xFC;  // Reload the timer value for 1ms Delay
    TL0 = 0x67;

    pulseCount++;

    if((timerValue>=50)) // If the pulse width is greater than 50ms, this will mark the SOF
    { 
        pulseCount = -2; // First 2 counts needs to be skipped hence pulse count is set to -2 
        bitPattern = 0;
    }
    else if((pulseCount>=0) && (pulseCount<32)) //Accumulate the bit values between 0-31.
    {  
        if(timerValue>=2)                      //pulse width greater than 2ms is considered as LOGIC1
        {
            bitPattern |=(uint32_t)1<<(31-pulseCount);
        }
        else
        {

        }
    }
    else if(pulseCount>=32)                  //This will mark the End of frame as 32 pulses are received
    {
        newKey = bitPattern;                // Copy the newKey(patter) and set the pulse count to 0;
        pulseCount = 0;
    }
}


void main()
{

    /*Connect RS->P0.0, RW->P0.1, EN->P0.2 and data bus to P0.4 to P0.7*/
    LCD_SetUp(P0_0,P0_1,P0_2,P_NC,P_NC,P_NC,P_NC,P0_4,P0_5,P0_6,P0_7);
    LCD_Init(2,16);

    TMOD |= 0x01; // Timer0 MODE1(16-bit timer)
    TH0 = 0xFC;   //Timer value for 1ms at 11.0592Mhz clock
    TL0 = 0x67;
    TR0 = 1;       // Start the Timer
    ET0 = 1;       // Enable the Timer0 Interrupt
    
    IT0 = 1;       // Configure INT0 falling edge interrupt
    EX0 = 1;       // Enable the INT0 External Interrupt
    
    EA  = 1;       // Enable the Global Interrupt bit

    LCD_DisplayString("Init Done");
    while(1)
    {
        if(newKey!=0)		 //Wait till newKey press is detected
        {  
            LCD_Clear();	 //Clear the LCD and Display the new Key Code
            LCD_Printf("newKey:%X",newKey);
            newKey = 0;		 //CLear the newKey value for next cycle
        }
    }		
}	  
