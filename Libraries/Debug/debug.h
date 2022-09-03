#ifndef  __DDL_DEBUG_H__
#define  __DDL_DEBUG_H__

#define DEBUG_UART0         0
#define DEBUG_UART1         1

#define DEBUG_UART_P01P02   0
#define DEBUG_UART_P35P36   1

// UART port for printf output
#define DEBUG_UARTx         DEBUG_UART1
// UART port pins for printf output
#define DEBUG_UART_PORT     DEBUG_UART_P01P02

void Debug_PrinfInit(void);

#endif /* __DDL_DEBUG_H__ */
