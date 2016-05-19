/***************************************************************************************************
                                              ExploreEmbedded Copyright Notice 
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to read 10bit ADC value from channel 0 and display the Raw and Equivalent volt on LCD.

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
#include "adc.h"
#include "lcd.h"

/********************************
  adc.h ADC0809 pin Connections
*********************************
adc_databus --> P2

adc_A    --> P1^0;
adc_B    --> P1^1;
adc_C    --> P1^2;
adc_ALE  --> P1^3;
adc_Start--> P1^4;
adc_EOC  --> P1^5;
adc_OE   --> P1^6;
*********************************/ 

int main() 
{
    int adcValue;
    float volt;
    
    ADC_Init();       /* Initialize the ADC module */
    
    /*Connect RS->P0.0, RW->P0.1, EN->P0.2 and data bus to P0.4 to P0.7*/
    LCD_SetUp(P0_0,P0_1,P0_2,P_NC,P_NC,P_NC,P_NC,P0_4,P0_5,P0_6,P0_7);
    LCD_Init(2,16);
    
    while(1)
    {
        adcValue = ADC_GetAdcValue(0); // Read the ADC value of channel zero
        volt = (adcValue*5.00)/255;
        LCD_GoToLine(0);
        LCD_Printf("ADC0 Value:%3d\nVolt:%f",adcValue,volt);     // Display Raw adc value and Equivalent temp on LCD
    }
    
    return (0);
}


