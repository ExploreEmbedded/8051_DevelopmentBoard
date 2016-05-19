/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   gpio.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the the gpio pin number configuration and  
                function prototypes for the gpio routines
 
The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 
 
 
GNU GENERAL PUBLIC LICENSE: 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 
 
Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/
 
 
/***************************************************************************************************
                             Revision History
****************************************************************************************************                   
15.0: Initial version 
***************************************************************************************************/
 
#ifndef _GPIO_H
#define _GPIO_H

#include"stdutils.h"


typedef enum
{
    P0_0,P0_1,P0_2,P0_3,P0_4,P0_5,P0_6,P0_7,
    P1_0,P1_1,P1_2,P1_3,P1_4,P1_5,P1_6,P1_7,
    P2_0,P2_1,P2_2,P2_3,P2_4,P2_5,P2_6,P2_7,
    P3_0,P3_1,P3_2,P3_3,P3_4,P3_5,P3_6,P3_7,
    P_NC = 0xff
}gpioPins_et;




/***************************************************************************************************
                             Function prototypes
***************************************************************************************************/
#define  GPIO_PinDirection GPIO_PinWrite
void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t v_pinValue_u8);
uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber);

/**************************************************************************************************/
#endif