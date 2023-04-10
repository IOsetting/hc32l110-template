/**
 * LED Blink Demo
 * 
 * Wiring:
 *   P34   -> + LED1 -  -> GND
 *   P35   -> + LED2 -  -> GND
*/
#include "gpio.h"

int main(void) {
    /**
     * Set P34 and P35 as output
    */
    Gpio_InitIOExt(3, 4, 
                    GpioDirOut, // Output
                    FALSE,      // No pull up
                    FALSE,      // No pull down
                    FALSE,      // No open drain
                    FALSE);     // High driver capability
    Gpio_InitIOExt(3, 5, GpioDirOut, FALSE, FALSE, FALSE, FALSE);

    // Toggle LED blink
    while (1)
    {
        GPIO_SetPinOutHigh(3, 4);
        GPIO_SetPinOutLow(3, 5);
        delay1ms(1000);

        GPIO_SetPinOutLow(3, 4);
        GPIO_SetPinOutHigh(3, 5);
        delay1ms(1000);
    }
}

