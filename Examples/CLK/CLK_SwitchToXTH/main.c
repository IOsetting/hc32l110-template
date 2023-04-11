/**
 * Switch system clock to external high speed oscillator
 * 
 * Wiring:
 *   P01 & P02  -> 32MHz Quartz OSC
 *   P34        -> + LED1 -  -> GND
 *   P35(TX)    -> USB2TTL RX
*/
#include "gpio.h"
#include "bsp_printf.h"

int main(void) 
{
    uint32_t u32Val;
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
