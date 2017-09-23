#include "glcd.h"   
#include "delay.h"

#define DELAY_TIME 3000

void main() 
{
    int num = 1234;
    GLCD_Init();

    while (1) 
    {
        GLCD_Clear();
        GLCD_DisplayLogo(LogoBitMap);
        DELAY_ms(DELAY_TIME);

        GLCD_Clear();
        GLCD_Printf("Dec:%d \nHex:%x \nBin:%b \nFloat:%f", num, num, num, 4567.89);
        DELAY_ms(DELAY_TIME);

        GLCD_Clear();
        GLCD_HorizontalGraph(0, 45);
        GLCD_HorizontalGraph(1, 50);
        GLCD_HorizontalGraph(2, 82);
        GLCD_HorizontalGraph(3, 74);
        DELAY_ms(DELAY_TIME);

        GLCD_Clear();
        GLCD_VerticalGraph(0, 45);
        GLCD_VerticalGraph(1, 50);
        GLCD_VerticalGraph(2, 82);
        GLCD_VerticalGraph(3, 74);
        DELAY_ms(DELAY_TIME);
    }
}