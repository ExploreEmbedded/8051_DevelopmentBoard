/***************************************************************************************************
                                              ExploreEmbedded Copyright Notice 
 ****************************************************************************************************
 * File:   timer.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the functions for configuring and using the 8051 timers.


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
#include "timers.h"
#include "stdutils.h"




#if (TIMER_0_INTR_ENABLE == 1)
uint16_t v_Timer0_ReloadValue_U16=0;
uint16_t v_Timer0_OvfCount_U16=0;
isrFunPtr_t Timer0_UserCallBack= NULL;
#endif


#if (TIMER_1_INTR_ENABLE == 1)
uint16_t v_Timer1_ReloadValue_U16=0;
uint16_t v_Timer1_OvfCount_U16=0;
isrFunPtr_t Timer1_UserCallBack= NULL;
#endif


#if (TIMER_2_INTR_ENABLE == 1)
uint16_t v_Timer2_ReloadValue_U16=0;
uint16_t v_Timer2_OvfCount_U16=0;
isrFunPtr_t Timer2_UserCallBack= NULL;
#endif











/***************************************************************************************************
            void TIMER_Init(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32)
 ****************************************************************************************************
 * I/P Arguments:
                uint8_t: Timer number(0-2) that needs to be initialized.
                uint32_t: Timer tick value, Delay time in us.


 * Return value: none

 * description :This function initializes the timer with specfied delay.
                The requested timer should be within rage(0,2).
                The delay time is multiple of uSec.

 ##Note: This function will only initialize the timers with required delay.
         TIMER_Start() fuctions needs to be called to start the timer.
 ****************************************************************************************************/

void TIMER_Init(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32)
{
    TIMER_SetTime(timerNumber_u8,timerIntervalInUs_u32);
}




/***************************************************************************************************
                           void TIMER_Start(uint8_t timerNumber_u8)
 ****************************************************************************************************
 * I/P Arguments:
                uint8_t: Timer number(0-2) that needs to be started.

 * Return value: none

 * description :This function turns on the timer and it starts incrementing.

 ##Note: Before calling the TIMER_Start function the timers should to be initialized by calling TIMER_Init()
 ****************************************************************************************************/
void TIMER_Start(uint8_t timerNumber_u8)
{
    switch(timerNumber_u8)
    {
#if (TIMER_0_INTR_ENABLE == 1)
    case 0 :
        v_Timer0_OvfCount_U16 = 0;
        TMOD |= 0x01;                               // Timer0 MODE1(16-bit timer)
        TL0 = (v_Timer0_ReloadValue_U16 & 0xFF);    // Load the lower 8-bits of timer value to TL0
        TH0 = (v_Timer0_ReloadValue_U16>>8) & 0xFF; // Load the higher 8-bits of timer value to TH0
        TR0 = 1;  // Start Timer
        ET0 = 1;  // Enable the Interrupt
        break;
#endif


#if (TIMER_1_INTR_ENABLE == 1)
    case 1 :
        v_Timer0_OvfCount_U16 = 0;
        TMOD|=0x10;                                 // Timer1 MODE1(16-bit timer)
        TL1 = (v_Timer1_ReloadValue_U16 & 0xFF);    // Load the lower 8-bits of timer value
        TH1 = (v_Timer1_ReloadValue_U16>>8) & 0xFF; // Load the higher 8-bits of timer value
        TR1 = 1;  // Start Timer
        ET1 = 1;  // Enable the Interrupt
        break;
#endif


#if (TIMER_2_INTR_ENABLE == 1)
    case 2 :
        v_Timer2_OvfCount_U16 = 0;
        RCAP2L = (v_Timer2_ReloadValue_U16 & 0xFF);    // Load the lower 8-bits of timer value
        RCAP2H = (v_Timer2_ReloadValue_U16>>8) & 0xFF; // Load the higher 8-bits of timer value
        TR2 = 1;  // Start Timer
        ET2 = 1;  // Enable the Interrupt
        break;
#endif
    }
}






/***************************************************************************************************
            void TIMER_Stop(uint8_t timerNumber_u8)
 ****************************************************************************************************
 * I/P Arguments:
                uint8_t: Timer number(0-2) that needs to be stopped.

 * Return value: none

 * description :This function turns OFF the timer incrementing.
 ****************************************************************************************************/
void TIMER_Stop(uint8_t timerNumber_u8)
{
    switch(timerNumber_u8)
    {
#if (TIMER_0_INTR_ENABLE == 1)
    case 0 :
        TR0 = 0;   //Stop the timer
        break;
#endif


#if (TIMER_1_INTR_ENABLE == 1)
    case 1 :
        TR1 = 0;   //Stop the timer
        break;
#endif


#if (TIMER_2_INTR_ENABLE == 1)
    case 2 :
        TR2 = 0;   //Stop the timer
        break;
#endif
    }
}





/***************************************************************************************************
            void TIMER_AttachInterrupt(uint8_t timerNumber_u8,timerFunPtr funPtr)
 ****************************************************************************************************
 * I/P Arguments:
                uint8_t: Timer number(0-2) for which the user callback function needs to be hooked.
                timerFunPtr: Function name thats needs to be called by the ISR.
                             The function parameter and return type should be void as shown below.
                             void MyFunToBeCalledByISR(void);

 * Return value: none

 * description :This functions attaches/hookes the user callback function to ISR.
                Ever time the interrupt occurs the ISR will call the user CallBack function.
 ****************************************************************************************************/
void TIMER_AttachInterrupt(uint8_t timerNumber_u8,isrFunPtr_t funPtr)
{

    switch(timerNumber_u8)
    {
#if (TIMER_0_INTR_ENABLE == 1)
    case 0 :
        Timer0_UserCallBack= funPtr;
        break;
#endif


#if (TIMER_1_INTR_ENABLE == 1)
    case 1 :
        Timer1_UserCallBack= funPtr;
        break;
#endif


#if (TIMER_2_INTR_ENABLE == 1)
    case 2 :
        Timer2_UserCallBack= funPtr;
        break;
#endif
    }
}






/***************************************************************************************************
            uint32_t TIMER_GetTime(uint8_t timerNumber_u8)
 ****************************************************************************************************
 * I/P Arguments:
                uint8_t: Timer number(0-2) whose timer value needs to be read.

 * Return value: uint32_t: Timer/delay value in us.

 * description :This functions returns the current timer value(TC) of the requested timer.
 ****************************************************************************************************/
uint32_t TIMER_GetTime(uint8_t timerNumber_u8)
{
    uint32_t timerDelay = 0;
    uint16_t timerCount = 0;
    switch(timerNumber_u8)
    {
#if (TIMER_0_INTR_ENABLE == 1)
    case 0 :
        timerDelay = v_Timer0_ReloadValue_U16 * v_Timer0_OvfCount_U16;
        timerCount = ((uint16_t)TH0<<8) + TL0;
        if(timerCount>v_Timer0_ReloadValue_U16)
        {
            timerDelay = timerDelay + timerCount;
        }
        break;
#endif


#if (TIMER_1_INTR_ENABLE == 1)
    case 1 :
        timerDelay = v_Timer1_ReloadValue_U16 * v_Timer1_OvfCount_U16;
        timerCount = ((uint16_t)TH1<<8) + TL1;
        if(timerCount>v_Timer1_ReloadValue_U16)
        {
            timerDelay = timerDelay + timerCount;
        }
        break;
#endif


#if (TIMER_2_INTR_ENABLE == 1)
    case 2 :
        timerDelay = v_Timer2_ReloadValue_U16 * v_Timer2_OvfCount_U16;
        timerCount = ((uint16_t)RCAP2H<<8) + RCAP2L;
        if(timerCount>v_Timer2_ReloadValue_U16)
        {
            timerDelay = timerDelay + timerCount;
        }
        break;
#endif
    }

    timerDelay = timerDelay * TIMER_TICK;   // Mulitply the total count with TimerTick = 1.085;

    return timerDelay;
}







/***************************************************************************************************
            void TIMER_SetTime(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32)
 ****************************************************************************************************
 * I/P Arguments:
                uint8_t: Timer number(0-2) whose timer value needs to be set.
                uint32_t: Timer/delay value in us.

 * Return value: None

 * description :This functions sets the required/delay  timer value for the requested timer.
 
 ###Note: The request for the timer delays will be rejected if the reuested delay is greater than TIMER_MAX_DELAY  
 ****************************************************************************************************/
void TIMER_SetTime(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32)
{
    uint16_t reloadValue;
    if(timerIntervalInUs_u32 <= TIMER_MAX_DELAY)
    {
        reloadValue = (uint32_t)65536 - (timerIntervalInUs_u32/(TIMER_TICK));
        switch (timerNumber_u8)
        {
#if (TIMER_0_INTR_ENABLE == 1)
        case 0 :            
            v_Timer0_ReloadValue_U16 = reloadValue;
            break;
#endif


#if (TIMER_1_INTR_ENABLE == 1)
        case 1 :
            v_Timer1_ReloadValue_U16 = reloadValue;
            break;
#endif


#if (TIMER_2_INTR_ENABLE == 1)
        case 2 :
            v_Timer2_ReloadValue_U16 = reloadValue;
            break;
#endif
        }
    }
}



/***************************************************************************************************
                            TIMER_ISR's
 ****************************************************************************************************
 desc: The four ISR's will be called independently whenever the configured delay time is elapsed.
       In other words the ISR's will be called when the Timer Count(TC) reaches the Match Value(MR0).

       The ISR will clear the Interrupt bit as it is being served.(Setting the bit will clear the Corresponding ISR Bit)
       If the user CallBack Function is configured then it will be called.
 ****************************************************************************************************/
#if (TIMER_0_INTR_ENABLE == 1)
void timer0_isr() interrupt 1
{
    TL0 = (v_Timer0_ReloadValue_U16 & 0xFF);    // Load the lower 8-bits of timer value
    TH0 = (v_Timer0_ReloadValue_U16>>8) & 0xFF; // Load the higher 8-bits of timer value
    v_Timer0_OvfCount_U16++;

    if(Timer0_UserCallBack!= NULL)
    {
        Timer0_UserCallBack();
    }
}
#endif



#if (TIMER_1_INTR_ENABLE == 1)
void timer1_isr() interrupt 3
{
    TL1 = (v_Timer1_ReloadValue_U16 & 0xFF);    // Load the lower 8-bits of timer value
    TH1 = (v_Timer1_ReloadValue_U16>>8) & 0xFF; // Load the higher 8-bits of timer value
    v_Timer1_OvfCount_U16++;

    if(Timer1_UserCallBack!= NULL)
    {
        Timer1_UserCallBack();
    }
}
#endif



#if (TIMER_2_INTR_ENABLE == 1)
void timer2_isr() interrupt 5
{
    RCAP2L = (v_Timer2_ReloadValue_U16 & 0xFF);    // Load the lower 8-bits of timer value
    RCAP2H = (v_Timer2_ReloadValue_U16>>8) & 0xFF; // Load the higher 8-bits of timer value
    TF2 = 0;
    v_Timer2_OvfCount_U16++;
    if(Timer2_UserCallBack!= NULL)
    {
        Timer2_UserCallBack();
    }
}
#endif

/*************************************************************************************************
                                    END of  ISR's
 *************************************************************************************************/


