#include "gpio.h"

int main(void) {
    // Set P33 as input
    Gpio_InitIO(3, 3, GpioDirIn);
    // Set GPIO P34 and P35 as output
    Gpio_InitIOExt(3, 4, GpioDirOut, TRUE, FALSE, TRUE, FALSE);
    Gpio_InitIOExt(3, 5, GpioDirOut, TRUE, FALSE, TRUE, FALSE);
    GPIO_SetPinOutLow(3, 4);
    GPIO_SetPinOutLow(3, 5);

    // Press key to continue
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
