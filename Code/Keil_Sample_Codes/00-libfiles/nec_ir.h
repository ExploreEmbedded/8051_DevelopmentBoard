/***************************************************************************************************
                                              ExploreEmbedded Copyright Notice 
****************************************************************************************************
 * File:   nec_ir.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: NEC IR remote library to decode the Remote Keys.

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

/***************************************************************************************************
                             Revision History
****************************************************************************************************                   
16.0: Initial version 
***************************************************************************************************/
 
#ifndef _IR_REMOTE_H_
#define _IR_REMOTE_H_

#include"stdutils.h"


/********************************************
              NEC IR Remote Codes 
*********************************************/  
#define IR_CODE_CH_MINUS   0xFFA25D
#define IR_CODE_CH         0xFF629D
#define IR_CODE_CH_PLUS    0xFFE21D
#define IR_CODE_PREV       0xFF22DD
#define IR_CODE_NEXT       0xFF02FD
#define IR_CODE_PLAY_PAUSE 0xFFC23D
#define IR_CODE_VOL_MINUS  0xFFE01F
#define IR_CODE_VOL_PLUS   0xFFA857
#define IR_CODE_EQ         0xFF906F
#define IR_CODE_100_PLUS   0xFF9867
#define IR_CODE_200_PLUS   0xFFB04F
#define IR_CODE_0          0xFF6897
#define IR_CODE_1          0xFF30CF
#define IR_CODE_2          0xFF18E7
#define IR_CODE_3          0xFF7A85
#define IR_CODE_4          0xFF10EF
#define IR_CODE_5          0xFF38C7
#define IR_CODE_6          0xFF5AA5
#define IR_CODE_7          0xFF42BD
#define IR_CODE_8          0xFF4AB5
#define IR_CODE_9          0xFF52AD
/*********************************************/




/***************************************************************************************************
                             Function prototypes
***************************************************************************************************/
void IR_RemoteInit(void);
uint32_t IR_RemoteGetKey(void);
/**************************************************************************************************/
#endif

