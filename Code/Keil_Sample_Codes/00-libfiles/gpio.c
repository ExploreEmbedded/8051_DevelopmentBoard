/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
*****************************************************************************************************
 * File:   gpio.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the the accessing the GPIO pins of a controller.
                First the GPIO pins needs to configured(Input/Output) and later used accordingly.

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


#include <reg51.h>
#include "stdutils.h"
#include "gpio.h"



/***************************************************************************************************
            void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t v_pinValue_u8)
****************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be updated.
                             Refer the gpio.h for pin numbering.
                gpioValue_et: Value to be updated(LOW/HIGH) on the selected pin.
                              

 * Return value    : none

 * description :This function updates the specified value on the selected pin.  
                Before updating the pins status, the pin function should be selected and then
                the pin should be configured as OUTPUT 
****************************************************************************************************/
void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t v_pinValue_u8)
{

    uint8_t v_portNumber_u8;


    v_portNumber_u8 =  (enm_pinNumber>>3);  // Divide the pin number by 8 go get the PORT number
    enm_pinNumber  =   enm_pinNumber & 0x07;  // lower 3-bits contains the bit number of a byte 

    /* Go to particular port after decoding from the pin number and 
        update the value of the specified pin*/
    switch(v_portNumber_u8)
    {
    case 0:
        util_UpdateBit(P0,enm_pinNumber,v_pinValue_u8);
        break;

    case 1:
        util_UpdateBit(P1,enm_pinNumber,v_pinValue_u8);
        break;

    case 2:
        util_UpdateBit(P2,enm_pinNumber,v_pinValue_u8);
        break;

    case 3:
        util_UpdateBit(P3,enm_pinNumber,v_pinValue_u8);
        break;
    }                
}








/***************************************************************************************************
                    uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber)
****************************************************************************************************
 * I/P Arguments: 
                gpioPins_et: pin number which needs to be read.
                             Refer the gpio.h for pin numbering.

 * Return value    : 
                 uint8_t:    Status of the specified pin.

 * description :This function returns the status of the selected pin.
                Before reading the pins status, the pin should be configured as INPUT 
****************************************************************************************************/
uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber)
{
    uint8_t v_portNumber_u8;
    uint8_t returnStatus = 0;

    v_portNumber_u8 =  (enm_pinNumber>>3); // Divide the pin number by 8 go get the PORT number
    enm_pinNumber  =     enm_pinNumber & 0x07; // lower 3-bits contains the bit number of a byte 

    /* Go to particular port after decoding from the pin number and read the pins status */
    switch(v_portNumber_u8)     
    {                             
    case 0: 
        returnStatus = util_IsBitSet(P0,enm_pinNumber);
        break;

    case 1:
        returnStatus = util_IsBitSet(P1,enm_pinNumber);
        break;

    case 2:
        returnStatus = util_IsBitSet(P2,enm_pinNumber);
        break;

    case 3:
        returnStatus = util_IsBitSet(P3,enm_pinNumber);
        break;
    }                         
    return returnStatus;
}
