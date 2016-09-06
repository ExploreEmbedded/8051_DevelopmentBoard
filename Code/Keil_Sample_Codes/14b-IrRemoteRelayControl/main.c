/***************************************************************************************************
                                              ExploreEmbedded Copyright Notice 
 ****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Sample program to decode NEC IR Remote and turn ON/OFF the bulb.

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

#include <reg51.h>
#include "stdutils.h"
#include "nec_ir.h"

sbit RELAY_PIN = P0^0;

void main()
{
    uint32_t key;
	RELAY_PIN = 0;	  // Turn OFF the relay during Init
    IR_RemoteInit();  // Initialtile the INTO and Timer0 for decoding the IR pulses

    while(1)
    {
        key = IR_RemoteGetKey();  // Read the key press, it returns key code if key press is detected, else it returns 0

        switch(key)
        {
        case IR_CODE_1: RELAY_PIN = 1; break; /* Turn On Relay(Bulb) if 1 is pressed*/
        case IR_CODE_0: RELAY_PIN = 0; break; /* Turn OFF Relay(Bulb) if 0 is pressed*/
        default: break;
        }
    }		
}	  
