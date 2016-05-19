/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   adc.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library function for ADC conversion
 
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
 
 
 
/***************************************************************************************************
                             Revision History
****************************************************************************************************                   
15.0: Initial version 
***************************************************************************************************/

#include"adc.h"
#include"delay.h"
#include"stdutils.h"





/***************************************************************************************************
                         void ADC_Init()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function initializes the ADC module.
***************************************************************************************************/
void ADC_Init()
{

         adc_Start=0;                //Initialize all the control lines to zero.
         adc_ALE=0;
         adc_OE=0;
         adc_EOC=1;                  //Configure the EOC pin as I/P
       adc_databus=0xff;             //configure adc_databus as input
}




/***************************************************************************************************
                    uint16_t ADC_GetAdcValue(uint8_t var_adcChannel_u8);
****************************************************************************************************
 * I/P Arguments: uint8_t(channel number).
 * Return value    : uint16_t(16 bit ADC result)

 * description  :This function does the ADC conversion for the Selected Channel
                 and returns the converted 16bit result.
                 The adc value per bit depends on the resolution of the ADC. 
                 For ADC0809(8-bit ADC)) the adc value per lsb will be 5/255=0.0196V.
                 For AVR/PIC(10-bit adc) the adc value per lsb will be 5/1023=0048v

              ___     ___     ___     ___     ___     ___     ___     ___     ___
         |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
Clock:   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |___|   |__

Address  ----------(Address A,B,C)--------------------------------------------------
(Channel number)                    ______
                                   |      |
ALE:     __________________________|      |_________________________________________
                                       _______
                                      |       |
Start;   _____________________________|       |_____________________________________
         __________________________________________          ______________________
                                                   |        |
EOC:                                               |________|
                                                                 _______________
                                                                |               |
OE;     ________________________________________________________|               |____

Data:   -----------------------------------------------------------(adc result)-----

***************************************************************************************************/
uint16_t ADC_GetAdcValue(uint8_t v_adcChannel_u8)
{
        uint16_t adc_result;

        adc_A=((v_adcChannel_u8>>0) & 0x01);   //Selectthe channel
        adc_B=((v_adcChannel_u8>>1) & 0x01);   //for which the conversion needs to be done
        adc_C=((v_adcChannel_u8>>2) & 0x01);

        adc_ALE=1;         // Latch the address by making the ALE high.
        DELAY_us(50);
        adc_Start=1;       //Start the conversion after latching the channel address
        DELAY_us(25);

        adc_ALE=0;         //Pull ALE line to zero after starting the conversion.
        DELAY_us(50);
        adc_Start=0;       //Pull Start line to zero after starting the conversion.

     while(adc_EOC==0);    // Wait till the ADC conversion is completed,
                           // EOC will be pulled to HIGH by the hardware(ADC0809)
                           // once conversion is completed.

         adc_OE=1;         //Make the Output Enable high
                           //to bring the ADC data to port pins
         DELAY_us(25);
     adc_result=adc_databus;  //Read the ADC data from ADC bus
          adc_OE=0;           //After reading the data, disable th ADC output line.

      return(adc_result) ;

  }
