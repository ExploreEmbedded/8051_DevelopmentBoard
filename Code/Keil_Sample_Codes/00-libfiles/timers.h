/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   timer.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the function declaration and the SFR bit number for configuring and using the LPC1768 timers.
                 

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
#ifndef _TIMERS_H_
#define _TIMERS_H_



#include "stdutils.h"





/*************************************************************************************************
                         Costants, Structures and Typedefs for timers 							   
**************************************************************************************************/
#define TIMER_0_INTR_ENABLE     0
#define TIMER_1_INTR_ENABLE     0
#define TIMER_2_INTR_ENABLE     0


/*Max delays in microsecs**/
#define TIMER_MAX_DELAY   71000

#define  TIMER_TICK   1.085  //11.0592/12 = 1.08592


typedef void (*isrFunPtr_t)(void);


/*************************************************************************************************/




/*************************************************************************************************
                                Function Prototypes 							   
*************************************************************************************************/
void TIMER_Init(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32);
void TIMER_Start(uint8_t timerNumber_u8);
void TIMER_Stop(uint8_t timerNumber_u8);
void TIMER_AttachInterrupt(uint8_t timerNumber_u8,isrFunPtr_t funPtr);
uint32_t TIMER_GetTime(uint8_t timerNumber_u8);
void TIMER_SetTime(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32);      
/*************************************************************************************************/


#endif
