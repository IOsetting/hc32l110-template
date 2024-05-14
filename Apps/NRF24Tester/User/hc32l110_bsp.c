/**
 * 
 * LED1 (RED): P34
 * LED2 (GRE): P35
 * BUTTON    : P33, active = low
 * UART1 TX  : P01
 * UART1 RX  : P02
 * SPI CS    : P14
 * SPI MISO  : P23
 * SPI MOSI  : P24
 * SPI CLK   : P25
 * CE        : P26
 * IRQ       : P32
*/
#include "hc32l110_bsp.h"
#include "ring_buffer.h"

__IO uint8_t uart_rx_flag = 0;
uint8_t uart_rx_buff[RING_BUFFER_SIZE];

void BSP_UART_RX_Callback(void);

void BSP_GPIO_Init(void)
{
  // Button
  Gpio_InitIOExt(3, 3,  GpioDirIn, TRUE, FALSE, FALSE, FALSE);
  // LED
  Gpio_InitIOExt(3, 4, GpioDirOut, FALSE, FALSE, FALSE, FALSE);
  // LED
  Gpio_InitIOExt(3, 5, GpioDirOut, FALSE, FALSE, FALSE, FALSE);
  // NRF24L01 CE
  Gpio_InitIOExt(2, 6, GpioDirOut, TRUE, FALSE, FALSE, FALSE);
  // NRF24L01 IRQ
  Gpio_InitIOExt(3, 2, GpioDirIn, TRUE, FALSE, FALSE, FALSE);
}

void BSP_UART_Init(void)
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
  Uart1_TxRx_Init(115200, BSP_UART_RX_Callback);
}

void BSP_SPI_Init(void)
{
  stc_spi_config_t  SPIConfig;

  Gpio_SetFunc_SPI_CS_P14();
  Gpio_SetFunc_SPI_MISO_P23();
  Gpio_SetFunc_SPI_MOSI_P24();
  Gpio_SetFunc_SPI_CLK_P25();

  SPIConfig.bCPHA = SpiClockPhaseFirst;
  SPIConfig.bCPOL = SpiClockPolarityLow;
  // Turn off interrupts
  SPIConfig.bIrqEn = FALSE;
  // Master mode
  SPIConfig.bMasterMode = SpiMaster;
  // Clock source, PCLK/2
  SPIConfig.u8ClkDiv = SpiClkDiv2;
  // No callback
  SPIConfig.pfnIrqCb = NULL;
  Spi_Init(&SPIConfig);
}

void BSP_UART_RX_Callback(void)
{
  uint8_t ch = UART1_RxReceive();
  if (ch == '\n')
  {
    if (ring_buffer_size() > 0)
    {
      ring_buffer_read(uart_rx_buff);
      ring_buffer_clear();
      uart_rx_flag = 1;
    }
  }
  else if (ch != '\r')
  {
    ring_buffer_push(ch);
  }
}