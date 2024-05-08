#ifndef __BSP_H
#define __BSP_H

#include "uart.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


void BSP_GPIO_Init(void);
void BSP_UART_Init(void);
void BSP_SPI_Init(void);


#ifdef __cplusplus
}
#endif

#endif // __BSP_H
