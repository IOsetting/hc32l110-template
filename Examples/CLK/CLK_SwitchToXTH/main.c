/**
 * Switch system clock to external high speed oscillator
 * 
 * Wiring:
 *   P01 & P02  -> 32MHz XTAL OSC
 *   P34        -> + LED1 -  -> GND
 * 
 * XTAL OSC port(P01 & P02) conflicts with UART port, if you are going to use printf, 
 * please change the UART port to P35 & P36 by editing bsp_printf.h, 
 * 
 * change `DEBUG_UART_PORT` to DEBUG_UART_P35P36
 * ```
 *   #define DEBUG_UART_PORT     DEBUG_UART_P35P36
 * ```
*/
#include "gpio.h"
#include "bsp_printf.h"

int main(void) 
{
    delay1ms(1000);
    /**
     * Switch to external high speed oscillator
     * 
     * Edit "CLK_XTH_VAL" in clk.h to change the frequency
    */
    Clk_SwitchTo(ClkXTH);

    // Set P34 as output
    Gpio_InitIOExt(3, 4, GpioDirOut, FALSE, FALSE, FALSE, FALSE);
    // Turn it off
    GPIO_SetPinOutLow(3, 4);

    // Toggle LED blink
    while (1)
    {
        GPIO_TogglePinOut(3, 4);
        delay1ms(500);
    }
}
