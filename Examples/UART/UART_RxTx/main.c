#include "uart.h"
#include "base_timer.h"

uint8_t u8RxData[2] = {0x55, 0x00};
uint8_t u8RxFlg = 0;

void RxIntCallback(void)
{
    u8RxData[1] = UART1_RxReceive();
    u8RxFlg = 1;
}

int main(void)
{
    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);

    // Enable peripheral clock
    CLK_EnablePeripheralClk(ClkPeripheralBaseTim);
    CLK_EnablePeripheralClk(ClkPeripheralGpio); // GPIO clock is required, equal to M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;
    CLK_EnablePeripheralClk(ClkPeripheralUart1);
    // Set UART port
    Gpio_SetFunc_UART1TX_P35();
    Gpio_SetFunc_UART1RX_P36();
    // Config UART1
    Uart1_TxRx_Init(115200, RxIntCallback);

    while (1)
    {
        if (u8RxFlg)
        {
            u8RxFlg = 0;
            Uart1_TxChar(u8RxData[0]);
            Uart1_TxChar(u8RxData[1]);
        }
        delay1ms(10);
    }
}
