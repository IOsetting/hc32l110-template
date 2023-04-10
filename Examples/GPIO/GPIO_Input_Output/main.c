/**
 * GPIO Demo
 *   LED1 and LED2 will start blinking after key is pressed
 * 
 * Wiring:
 *   P33   ->   KEY     -> (1KR ~ 10KR) -> GND
 *   P34   -> + LED1 -  -> GND
 *   P35   -> + LED2 -  -> GND
 * 
 * 
*/
#include "gpio.h"

int main(void) {
    /**
     * Set P33 as input
    */
    Gpio_InitIOExt(3, 3, 
                    GpioDirIn,  // Input
                    TRUE,       // Pull up
                    FALSE,      // No pull down
                    FALSE,      // No open drain
                    TRUE        // Normal driver capability
                    );
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

    GPIO_SetPinOutLow(3, 4);
    GPIO_SetPinOutLow(3, 5);

    /**
     * Hold when input is high, break when input is low(key is pressed)
    */
    while (GPIO_GetPinIn(3, 3) == TRUE);

    // Toggle LED blink
    GPIO_SetPinOutHigh(3, 4);
    GPIO_SetPinOutLow(3, 5);
    while (1)
    {
        GPIO_TogglePinOut(3, 4);
        GPIO_TogglePinOut(3, 5);
        delay1ms(1000);
    }
}
