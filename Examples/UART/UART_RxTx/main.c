#include "uart.h"
#include "base_timer.h"

volatile uint8_t u8RxData[16] = {0x00}, u8RxFlg = 0, u8RxPos = 0;

void RxIntCallback(void)
{
    u8RxData[u8RxPos++] = UART1_RxReceive();
    u8RxPos = u8RxPos % 16;
    u8RxFlg = 1;
}

int main(void)
{
    uint8_t i;

    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);
    // Enable peripheral clock
    CLK_EnablePeripheralClk(ClkPeripheralBaseTim);
    CLK_EnablePeripheralClk(ClkPeripheralGpio); // GPIO clock is required, equal to M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;
    CLK_EnablePeripheralClk(ClkPeripheralUart1);
    /* 
     * Set P01,P02 as UART1 TX,RX, or use P35,P36
        Gpio_InitIOExt(3,5,GpioDirOut,TRUE,FALSE,FALSE,FALSE);   
        Gpio_InitIOExt(3,6,GpioDirOut,TRUE,FALSE,FALSE,FALSE); 
        Gpio_SetFunc_UART1_TX_P35();
        Gpio_SetFunc_UART1_RX_P36();
     */
    Gpio_InitIOExt(0,1,GpioDirOut,TRUE,FALSE,FALSE,FALSE);
    Gpio_InitIOExt(0,2,GpioDirOut,TRUE,FALSE,FALSE,FALSE);
    Gpio_SetFunc_UART1_TXD_P01();
    Gpio_SetFunc_UART1_RXD_P02();
    // Config UART1
    Uart1_TxRx_Init(115200, RxIntCallback);

    Uart1_TxString("Please input string and return\r\n");
    while (1)
    {
        if (u8RxFlg)
        {
            u8RxFlg = 0;
            for (i = 0; i < u8RxPos; i++)
            {
                Uart1_TxChar(u8RxData[i]);
            }
            Uart1_TxString("\r\n");
        }
        delay1ms(200);
    }
}
