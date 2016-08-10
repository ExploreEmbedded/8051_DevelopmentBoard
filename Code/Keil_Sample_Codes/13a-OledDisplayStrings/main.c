/***************************************************************************************************
                                   ExploreEmbedded Copyright Notice 
 ****************************************************************************************************
 * File:   oled_i2c.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: SSD1306 I2C OLED library to display strings, numbers, graphs and logos

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
#include "oled_i2c.h"

int main()
{		 
    OLED_Init();		  // Check oled_i2c.c file for SCL,SDA pin connection
    OLED_SetCursor(2,0);  //Set cursor at 2nd-line 0th-Position
    OLED_DisplayString("Oled Interface");	
    
    OLED_SetCursor(4,20); //Set cursor at 4th-line 20th-Position
    OLED_DisplayString("With 8051 From");
    
    OLED_SetCursor(6,30); //Set cursor at 6th-line 30th-Position
    OLED_DisplayString("Exploreembedded");    

    while(1);
}