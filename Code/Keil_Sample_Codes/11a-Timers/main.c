/***************************************************************************************************
                                              ExploreEmbedded Copyright Notice 
 ****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the sample program to demonstaracte the usage of 8051 timer library.


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


#include <reg51.h>
#include "timers.h" 


volatile uint8_t value =0;

void  myTimerIsr_0(void)
{
    
     util_BitToggle(value,0);
}

void  myTimerIsr_1(void)
{
    util_BitToggle(value,1);
}

void  myTimerIsr_2(void)
{
    util_BitToggle(value,2);
}




int main (void)
{
    
    TIMER_Init(0,1000);                     /* Configure timer0 to generate 1ms(1000us) delay*/
    TIMER_AttachInterrupt(0,myTimerIsr_0);  /* myTimerIsr_0 will be called by TIMER2_ISR */
    TIMER_Start(0);
    
    TIMER_Init(1,2000);                     /* Configure timer1 to generate 2ms(2000us) delay*/
    TIMER_AttachInterrupt(1,myTimerIsr_1);  /* myTimerIsr_1 will be called by TIMER2_ISR */
    TIMER_Start(1);     
    

    TIMER_Init(2,4000);                     /* Configure timer2 to generate 4ms(4000us) delay*/
    TIMER_AttachInterrupt(2,myTimerIsr_2);  /* myTimerIsr_2 will be called by TIMER2_ISR */
    TIMER_Start(2);

    EnableGlobalInterrupts();


    while(1)
    {        
        P2 = value;        
    }
}


