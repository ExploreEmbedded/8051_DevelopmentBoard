/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   adc.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the Function prototypes for the ADC routines
 
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
****************************************************************************************************                   
15.0: Initial version 
***************************************************************************************************/
 
#ifndef _ADC_H
#define _ADC_H

#include<reg51.h>
#include"stdutils.h"

/***************************************************************************************************
                                  ADC pin configuration
***************************************************************************************************/
#define adc_databus P2

sbit adc_A    = P1^0;
sbit adc_B    = P1^1;
sbit adc_C    = P1^2;
sbit adc_ALE  = P1^3;
sbit adc_Start= P1^4;
sbit adc_EOC  = P1^5;
sbit adc_OE   = P1^6;
/**************************************************************************************************/



/***************************************************************************************************
                             Function prototypes
***************************************************************************************************/
void ADC_Init();
uint16_t ADC_GetAdcValue(uint8_t v_adcChannel_u8);
/**************************************************************************************************/

#endif