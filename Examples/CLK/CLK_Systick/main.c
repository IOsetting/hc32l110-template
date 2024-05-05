/**
 * SysTick Interrupt Example
 * 
 * Wiring:
 *   P34   -> + LED1 -  -> GND
 *   P35   -> + LED2 -  -> GND
*/
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

int main(void) {
    // Set P34 and P35 as output
    Gpio_InitIOExt(3, 4, GpioDirOut, FALSE, FALSE, FALSE, FALSE);
    Gpio_InitIOExt(3, 5, GpioDirOut, FALSE, FALSE, FALSE, FALSE);
    // Turn both off
    GPIO_SetPinOutLow(3, 4);
    GPIO_SetPinOutLow(3, 5);

    /*
     * Note: don't enable systick interrupt if SysTick_Handler() is not defined
     */
    // Enable Systick Interrupt
    CLK_EnableSysTickIrq();

    // Toggle LED blink
    while (1)
    {
        GPIO_TogglePinOut(3, 5);
        delay1ms(500);
    }
}

