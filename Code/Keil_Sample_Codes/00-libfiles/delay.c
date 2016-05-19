/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   delay.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains delay routines
 
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
***************************************************************************************************/


#include"delay.h"
/***************************************************************************************************
                         void DELAY_us(uint16_t us_count)
****************************************************************************************************
 * I/P Arguments: uint16_t.
 * Return value    : none

 * description :
         This function is used generate delay in us.
         It generates a delay of approximate 10us for each count,
         if 5000 is passed as the argument then it generates a delay of 50ms.          

***************************************************************************************************/
void DELAY_us(uint16_t us_count)
 {    
    while(us_count!=0)
      {
         us_count--;
       }
 }



/***************************************************************************************************
                         void DELAY_ms(uint16_t ms_count)
****************************************************************************************************
 * I/P Arguments: uint16_t.
 * Return value    : none

 * description:
     This function is used generate delay in ms.
     It generates a delay of 1ms for each count,
     if 1000 is passed as the argument then it generates delay of 1000ms(1sec)
***************************************************************************************************/
void DELAY_ms(uint16_t ms_count)
 {
     while(ms_count!=0)
      {
         DELAY_us(C_CountForOneMsDelay_U16);     //DELAY_us is called to generate 1ms delay
          ms_count--;
      }

 }






/***************************************************************************************************
                        void DELAY_sec(uint16_t sec_count)
****************************************************************************************************
  * I/P Arguments: uint16_t.
  * Return value    : none

  * description:
      This function is used generate delay in sec .
      It generates a approximate delay of 1sec for each count,
      if 10 is passed as the argument then it generates delay of 10sec
***************************************************************************************************/
 #if (ENABLE_DELAY_SEC == 1)
void DELAY_sec(uint16_t sec_count)
 {


     while(sec_count!=0)
      {
         DELAY_ms(1000);    //DELAY_ms is called to generate 1sec delay
         sec_count--;
        }
 }
 #endif