/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   timer.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the function declaration and the preprocessors for configuring and using the 8052 PWM.
                As 8051/52 doesn't have inbuilt PWM, timer2 is used to generate the max of 2PWM ouputs.
                These can be enabled/disabled using the constants PWM_0_ENABLE/PWM_1_ENABLE, setting them to 1/0 will enable/disable the respective PWMs
                The PWM output pin can be set using PWM0_PIN/PWM1_PIN.
                By default the dutycyle is set to 50%.

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
#ifndef _PWM_H_
#define _PWM_H_


#include <reg51.h>
#include "stdutils.h"





/*************************************************************************************************
                         Costants, Structures and Typedefs for timers                                
**************************************************************************************************/
#define PWM_0_ENABLE   1
#define PWM_1_ENABLE   1

sbit PWM0_PIN = P3^6;
sbit PWM1_PIN = P3^7;
/*************************************************************************************************/




/*************************************************************************************************
                                Function Prototypes                                
*************************************************************************************************/
void PWM_Init(void);
void PWM_SetDutyCycle(uint8_t channel,uint8_t dutyCycle);
void PWM_Start(uint8_t channel);
void PWM_Stop(uint8_t channel);   
/*************************************************************************************************/
#endif
