/***************************************************************************************************
                                              ExploreEmbedded Copyright Notice 	
 ****************************************************************************************************
 * File:   keypad.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains hex-keypad port configurations

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
#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "gpio.h"
#include "stdutils.h"


/***************************************************************************************************
                                 Hex-Keypad Row/Col Configuration
 ***************************************************************************************************/
#define C_MaxRows_U8 (4)   
#define C_MaxCols_U8 (4)                 
#define C_DebounceTimeInMicroSecond_U16 (10)
#define C_DefaultKey_U8  ('x')
/**************************************************************************************************/




/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
uint8_t KEYPAD_GetKey();
void KEYPAD_Init(
        gpioPins_et row_0, 
        gpioPins_et row_1, 
        gpioPins_et row_2,
        gpioPins_et row_3, 
        gpioPins_et col_0,
        gpioPins_et col_1, 
        gpioPins_et col_2,
        gpioPins_et col_3 );
/**************************************************************************************************/

#endif
