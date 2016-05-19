/***************************************************************************************************
                                              ExploreEmbedded Copyright Notice 
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to demonstrate a four digit decimal up counter. 

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
#include "reg51.h"

#define SegOne   0xfe
#define SegTwo   0xfd
#define SegThree 0xfb
#define SegFour  0xf7	

void DELAY_ms(unsigned int ms_Count) 
{
    unsigned int i, j;
    for (i = 0; i < ms_Count; i++) 
    {
        for (j = 0; j < 100; j++);
    }
}

int main() {
    char seg_code[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
    int cnt, num, temp,i;


    while (1) 
    {
        for (cnt = 0x00; cnt <= 9999; cnt++) // loop to display 0-F
        {
            for (i = 0; i < 100; i++)
            {
                num = cnt;
                temp = num / 1000;
                num = num % 1000;
                P0 = SegOne; 
                P2 = seg_code[temp];               
                DELAY_ms(1);

                temp = num / 100;
                num = num % 100;
                P0 = SegTwo; 
                P2 = seg_code[temp];
                DELAY_ms(1);

                temp = num / 10;
                P0 = SegThree;
                P2 = seg_code[temp];
                DELAY_ms(1);

                temp = num % 10;
                P0 = SegFour;
                P2 = seg_code[temp];
                DELAY_ms(1);                              
            }
        }
    }
}
