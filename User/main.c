#include "gpio.h"

int main(void) {
    // Set P33 as input
    Gpio_InitIO(3, 3, GpioDirIn);

    // Set GPIO P34 and P35 as output
    Gpio_InitIOExt(3, 4, GpioDirOut, TRUE, FALSE, TRUE, FALSE);
    Gpio_InitIOExt(3, 5, GpioDirOut, TRUE, FALSE, TRUE, FALSE);
    // Toggle LED blink
    while (1)
    {
        Gpio_SetIO(3, 4, TRUE);
        Gpio_SetIO(3, 5, FALSE);
        delay1ms(1000);

        Gpio_SetIO(3, 4, FALSE);
        Gpio_SetIO(3, 5, TRUE);
        delay1ms(1000);
    }
}

