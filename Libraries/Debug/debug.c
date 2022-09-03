#include "debug.h"
#include "ddl.h"
#include "uart.h"

void Debug_PrinfInit(void)
{
    CLK_EnablePeripheralClk(ClkPeripheralBaseTim);
    CLK_EnablePeripheralClk(ClkPeripheralGpio);
#if (DEBUG_UARTx == DEBUG_UART0)
    CLK_EnablePeripheralClk(ClkPeripheralUart0);
#if (DEBUG_UART_PORT == DEBUG_UART_P01P02)
    Gpio_SetFunc_UART0_RXD_P01();
    Gpio_SetFunc_UART0_TXD_P02();
#elif (DEBUG_UART_PORT == DEBUG_UART_P35P36)
    Gpio_SetFunc_UART0RX_P36();
    Gpio_SetFunc_UART0TX_P35();
#endif
    Uart0_TxRx_Init(115200, NULL);

#elif (DEBUG_UARTx == DEBUG_UART1)
    CLK_EnablePeripheralClk(ClkPeripheralUart1);
#if (DEBUG_UART_PORT == DEBUG_UART_P01P02)
    Gpio_SetFunc_UART1_TXD_P01();
    Gpio_SetFunc_UART1_RXD_P02();
#elif (DEBUG_UART_PORT == DEBUG_UART_P35P36)
    Gpio_SetFunc_UART1TX_P35();
    Gpio_SetFunc_UART1RX_P36();
#endif
    Uart1_TxRx_Init(115200, NULL);
#endif
}

int __io_putchar(int ch)
{
#if (DEBUG_UARTx == DEBUG_UART0)
    Uart0_TxChar((uint8_t)ch);
#elif (DEBUG_UARTx == DEBUG_UART1)
    Uart1_TxChar((uint8_t)ch);
#endif
    return ch;
}

int __io_getchar(void)
{
#if (DEBUG_UARTx == DEBUG_UART0)
    return UART0_RxReceive();
#elif (DEBUG_UARTx == DEBUG_UART1)
    return UART1_RxReceive();
#endif
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
    (void)file;
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        *ptr++ = __io_getchar();
    }
    return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    (void)file;
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}
