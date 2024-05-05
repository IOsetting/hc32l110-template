#include "gpio.h"



uint8_t led_state = 0;
uint16_t ticks_count = 0;

void SysTick_Handler(void)
{
    ticks_count++;
    if (ticks_count == 1000)
    {
        GPIO_SetPinOut(3, 4, led_state);
        led_state = 1 - led_state;
        ticks_count = 0;
    }
}
