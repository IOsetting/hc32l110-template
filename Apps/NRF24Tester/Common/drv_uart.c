#include "drv_uart.h"
#include "ring_buffer.h"

__IO uint8_t opflag = 0;
uint8_t opcommand[RING_BUFFER_SIZE];

void APP_UART_RX_Callback(void);

void DRV_UART_Init(void)
{
    CLK_EnablePeripheralClk(ClkPeripheralUart1);
    /* 
     * Set P01,P02 as UART1 TX,RX
     */
    Gpio_InitIOExt(0, 1, GpioDirOut, TRUE, FALSE, FALSE, FALSE);
    Gpio_InitIOExt(0, 2, GpioDirOut, TRUE, FALSE, FALSE, FALSE);
    Gpio_SetFunc_UART1_TXD_P01();
    Gpio_SetFunc_UART1_RXD_P02();
    // Config UART1
    Uart1_TxRx_Init(115200, APP_UART_RX_Callback);
}

void APP_UART_RX_Callback(void)
{
    uint8_t ch = UART1_RxReceive();
    if (ch == '\n')
    {
        if (ring_buffer_size() > 0)
        {
            ring_buffer_read(opcommand);
            ring_buffer_clear();
            opflag = 1;
        }
    }
    else if (ch != '\r')
    {
        ring_buffer_push(ch);
    }
}