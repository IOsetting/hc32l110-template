#include "uart.h"
#include "base_timer.h"
#include "ring_buffer.h"

uint8_t opflag = 0, opcommand[RING_BUFFER_SIZE];

void APP_UART_RX_Callback(void)
{
    uint8_t ch = UART1_RxReceive();
    if (ch == '\n')
    {
        /*
        while (ring_buffer_fetch_uncheck(-1) == '\r')
        {
            ring_buffer_pop(&ch);
        }
        */
        if (ring_buffer_size() > 0)
        {
            ring_buffer_read(opcommand);
            opflag = 1;
            ring_buffer_clear();
        }
    }
    else if (ch != '\r')
    {
        ring_buffer_push(ch);
    }
}

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
    Uart1_TxRx_Init(115200, APP_UART_RX_Callback);

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
