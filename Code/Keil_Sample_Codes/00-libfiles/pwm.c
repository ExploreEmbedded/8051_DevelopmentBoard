/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
 ****************************************************************************************************
 * File:   pwm.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library function for PWM generation for 8052 series of controllers
                As 8051/52 doesn't have inbuilt PWM, timer2 is used to generate the max of 2PWM ouputs.
                These can be enabled/disabled using the constants PWM_0_ENABLE/PWM_1_ENABLE, setting them to 1/0 will enable/disable the respective PWMs
                The PWM output pin can be set using PWM0_PIN/PWM1_PIN.
                By default the dutycyle is set to 50%.

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
#include "pwm.h"
#include "stdutils.h"



#if (PWM_0_ENABLE == 1)
uint8_t v_Pwm0_DutyCycle_U8=50;
uint8_t v_Pwm0_Enabled_U8=0;
#endif

#if (PWM_1_ENABLE == 1)
uint8_t v_Pwm1_DutyCycle_U8=50;
uint8_t v_Pwm1_Enabled_U8=0;
#endif


/***************************************************************************************************
                        void PWM_Init(void)
 ****************************************************************************************************
 * I/P Arguments   : none
 * Return value    : none

 * description :This function initializes the Timer2 module for generating the PWM using timers.
 ***************************************************************************************************/
void PWM_Init(void)
{
    RCAP2L = 200;  // Load the lower 8-bits of timer value
    RCAP2H = 0xFF; // Load the higher 8-bits of timer value
    ET2 = 1;       // Enable the Interrupt
}







/***************************************************************************************************
                         void PWM_SetDutyCycle( uint8_t channel, uint8_t dutyCycle )
 ****************************************************************************************************
 * I/P Arguments: uint8_t: channel number at which PWM needs to be generated.(0/1).
                  uint8_t : required dutyCycle at the pwm pin(0-100).
 * Return value    : none

 * description :This function is used the set the duty cycle for the required channel.
                Ensure the PWM_Init() function is called before calling this function.
                This function only sets the duty cycle, the actual PWM generation satarts after calling PWM_Start().

Note: By default the dutycyle is set to 50%.
 ***************************************************************************************************/
void PWM_SetDutyCycle(uint8_t channel,uint8_t dutyCycle)
{
    if(dutyCycle>100)
        dutyCycle = 100;

    switch (channel)
    {
#if (PWM_0_ENABLE == 1)
    case 0 :
        v_Pwm0_DutyCycle_U8 = dutyCycle;
        break;
#endif


#if (PWM_1_ENABLE == 1)
    case 1 :
        v_Pwm1_DutyCycle_U8 = dutyCycle;
        break;
#endif
    }
}






/***************************************************************************************************
                         void PWM_Start(uint8_t channel)
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to start the pwm generation for the required channel.
 ***************************************************************************************************/
void PWM_Start(uint8_t channel)
{
    switch (channel)
    {
#if (PWM_0_ENABLE == 1)
    case 0 :
        v_Pwm0_Enabled_U8 = 1;
        TR2 = 1;  // Start Timer
        EnableGlobalInterrupts();
        break;
#endif


#if (PWM_1_ENABLE == 1)
    case 1 :
        v_Pwm1_Enabled_U8 = 1;
        TR2 = 1;  // Start Timer
        EnableGlobalInterrupts();
        break;
#endif
    }
}




/***************************************************************************************************
                         void PWM_Start(uint8_t channel)
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to stop the pwm generation for the required channel.
 ***************************************************************************************************/
void PWM_Stop(uint8_t channel)
{
    uint8_t pwmEnableDisable=0;
    switch (channel)
    {
#if (PWM_0_ENABLE == 1)
    case 0 :
        v_Pwm0_Enabled_U8 = 0;
        break;
#endif


#if (PWM_1_ENABLE == 1)
    case 1 :
        v_Pwm1_Enabled_U8 = 0;
        break;
#endif
    }

#if (PWM_0_ENABLE == 1)
    pwmEnableDisable|=v_Pwm0_Enabled_U8;
#endif

#if (PWM_1_ENABLE == 1)
    pwmEnableDisable|=v_Pwm1_Enabled_U8;
#endif

    TR2 = pwmEnableDisable; // Keep the Timer2 Running as long as one of the PWM is enabled
}








/***************************************************************************************************
                         timer2_isr()
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This is the timer2 ISR used for generating the PWM.
 ***************************************************************************************************/
#if ((PWM_0_ENABLE == 1) || (PWM_1_ENABLE == 1))
volatile uint8_t cycleTime =0;
void timer2_isr() interrupt 5
{
    TF2 = 0;             //CLear the Interrupt Flag

    if(cycleTime >= 100) // Maintain the CycleTime between 0-100 
    {
        cycleTime = 0;
    }
    else
    {
        cycleTime++;
    }

#if (PWM_0_ENABLE == 1)
    if(v_Pwm0_Enabled_U8 == 1)  
    {
        if(cycleTime == v_Pwm0_DutyCycle_U8)  // If the DutyCycle is met then make the pin zero.
        {
            PWM0_PIN = 0;
        }
        else if(cycleTime == 0)
        {
            PWM0_PIN = 1;                     // Make pin high when the cycle time reaches zero
        }
    }
#endif


#if (PWM_1_ENABLE == 1)
    if(v_Pwm1_Enabled_U8 == 1)
    {
        if(cycleTime == v_Pwm1_DutyCycle_U8)
        {
            PWM1_PIN = 0;
        }
        else if(cycleTime == 0)
        {
            PWM1_PIN = 1;
        }
    }
#endif
}
#endif