#include "uart.h"
#include "gpio.h"
#include "base_timer.h"

#include "drv_uart.h"
#include "ring_buffer.h"

extern __IO uint8_t opflag;
extern uint8_t opcommand[RING_BUFFER_SIZE];


int main(void)
{
    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);
    // Enable peripheral clock
    CLK_EnablePeripheralClk(ClkPeripheralBaseTim);
    // GPIO clock is required
    CLK_EnablePeripheralClk(ClkPeripheralGpio);
    // Enable systick interrupt
    CLK_EnableSysTickIrq();

    DRV_UART_Init();

    Gpio_InitIOExt(3, 4, GpioDirOut, FALSE, FALSE, FALSE, FALSE);

    Uart1_TxString("Please input string and return\r\n");

    while (1)
    {
        if (opflag)
        {
            opflag = 0;
            Uart1_TxString((char *)opcommand);
            Uart1_TxString("\r\n");
        }
        delay1ms(50);
    }
}
