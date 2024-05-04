/**
 * Switch system clock to external high speed oscillator
 * 
 * Wiring:
 *   P01 & P02  -> 32MHz XTAL OSC
 *   P34        -> + LED1 -  -> GND
 *   P35(TX)    -> USB2TTL RX
 * 
 * XTAL OSC port(P01 & P02) conflict with UART port, need to change UART port to P35 & P36
 * 
 * Edit bsp_printf.h, change `DEBUG_UART_PORT` to DEBUG_UART_P35P36
 * ```
 *   #define DEBUG_UART_PORT     DEBUG_UART_P35P36
 * ```
*/
#include "gpio.h"
#include "bsp_printf.h"

int main(void) 
{
    uint32_t u32Val;

    delay1ms(2000);
    /**
     * Switch to external high speed oscillator
     * 
     * Edit "CLK_XTH_VAL" in clk.h to change the frequency
    */
    Clk_SwitchTo(ClkXTH);
    u32Val = Clk_GetHClkFreq();

    Bsp_PrinfInit(115200);

    /**
     * Set P34 as output
    */
    Gpio_InitIOExt(3, 4, 
                    GpioDirOut, // Output
                    FALSE,      // No pull up
                    FALSE,      // No pull down
                    FALSE,      // No open drain
                    FALSE);     // High driver capability

    // Toggle LED blink
    while (1)
    {
        printf("Sysclk %ld\r\n", u32Val);
        GPIO_TogglePinOut(3, 4);
        delay1ms(1000);
    }
}
