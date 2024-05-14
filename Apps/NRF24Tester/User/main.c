#include "main.h"

#include "drv_led.h"
#include "drv_button.h"
#include "hc32l110_bsp.h"
#include "ring_buffer.h"
#include "nrf24l01.h"
#include "at_parser.h"

typedef enum {
  APP_MODE_INIT,
  APP_MODE_TX,
  APP_MODE_RX
} APP_ModeType_t;

extern __IO uint8_t uart_rx_flag;
extern uint8_t uart_rx_buff[RING_BUFFER_SIZE];

uint8_t rx_buff[NRF24L01_PLOAD_WIDTH];
APP_ModeType_t app_mode, app_mode_next;


static APP_ModeType_t APP_Init(void);
static void APP_ModeSwitchTo(APP_ModeType_t mode);
static APP_ModeType_t APP_RxMode(void);
static APP_ModeType_t APP_TxMode(void);
static APP_ModeType_t APP_HandleCommand(APP_ModeType_t mode, AT_Command_t cmd);

static void APP_SetRxAddr(uint8_t *data);
static void APP_SetTxAddr(uint8_t *data);
static void APP_SetRfChannel(uint8_t *data);
static void APP_SetRfRate(uint8_t *data);
static void APP_SetRfPower(uint8_t *data);


int main(void)
{
  app_mode = APP_Init();
  app_mode_next = app_mode;
  APP_ModeSwitchTo(app_mode);

  while (1)
  {
    if (app_mode != app_mode_next)
    {
      APP_ModeSwitchTo(app_mode_next);
      app_mode = app_mode_next;
    }

    switch (app_mode)
    {
    case APP_MODE_RX:
      app_mode_next = APP_RxMode();
      break;
    case APP_MODE_TX:
    default:
      app_mode_next = APP_TxMode();
      break;
    }
  }
}

static APP_ModeType_t APP_Init(void)
{
  /**
   * Internal high speed 24MHz
   */
  Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);
  // Peripheral clock
  CLK_EnablePeripheralClk(ClkPeripheralBaseTim);
  // GPIO clock
  CLK_EnablePeripheralClk(ClkPeripheralGpio);
  // SPI clock
  CLK_EnablePeripheralClk(ClkPeripheralSpi);

  // Enable systick interrupt
  CLK_EnableSysTickIrq();

  BSP_GPIO_Init();
  BSP_UART_Init();
  BSP_SPI_Init();

  DRV_LED_Init(0, 3, 4, DRV_LED_PATTERN_LONG_OFF, DRV_LED_ON); // RED
  DRV_LED_Init(1, 3, 5, DRV_LED_PATTERN_LONG_OFF, DRV_LED_ON); // GREEN
  DRV_Button_Init(0, 3, 3);

  Uart1_TxString("SPI Check ...");
  while (NRF24L01_SPI_Check() == 1)
  {
    Uart1_TxString("failed\r\n");
    delay1ms(1000);
  }
  printf("succ\r\n");
  NRF24L01_Config();

  return APP_MODE_RX;
}

static void APP_ModeSwitchTo(APP_ModeType_t mode)
{
  switch (mode)
  {
  case APP_MODE_RX:
    delay1ms(200);
    DRV_LED_SetPattern(0, DRV_LED_PATTERN_LONG_OFF);
    DRV_LED_SetPattern(1, DRV_LED_PATTERN_FLASH_SLOW);
    NRF24L01_SetRxMode();
    NRF24L01_ClearIRQFlags();
    NRF24L01_DumpConfig();
    DRV_Button_ClearState(0);
    break;

  case APP_MODE_TX:
  default:
    delay1ms(200);
    DRV_LED_SetPattern(0, DRV_LED_PATTERN_FLASH_SLOW);
    DRV_LED_SetPattern(1, DRV_LED_PATTERN_LONG_OFF);
    NRF24L01_SetTxMode();
    NRF24L01_FlushTX();
    NRF24L01_ClearIRQFlags();
    NRF24L01_DumpConfig();
    DRV_Button_ClearState(0);
    break;
  }
}

static APP_ModeType_t APP_RxMode(void)
{
  uint8_t pipe, length;

  if (DRV_Button_GetPressState(0) == DRV_BUTTON_PRESSED)
  {
    return APP_MODE_TX;
  }

  if (uart_rx_flag)
  {
    uart_rx_flag = 0;
    // Uart1_TxString((char *)uart_rx_buff);
    // Uart1_TxString("\r\n");
    AT_Command_t atcmd = AT_Parse((char *)uart_rx_buff);
    APP_ModeType_t mode = APP_HandleCommand(app_mode, atcmd);
    if (mode != app_mode)
    {
      return mode;
    }
  }
  // RX
  pipe = NRF24L01_ReadReg(NRF24L01_REG_STATUS);
  if (NRF24L01_RXFIFO_GetStatus() != NRF24L01_RXFIFO_STATUS_EMPTY)
  {
    pipe = NRF24L01_ReadPayload(rx_buff, &length, 0);
    Uart1_TxString("P:0x");
    Uart1_TxHex8Bit(pipe);
    Uart1_TxString(",L:0x");
    Uart1_TxHex8Bit(length);
    Uart1_TxChar(':');
    Uart1_TxHexArray(rx_buff, length);
    Uart1_TxString("\r\n");
  }
  NRF24L01_ClearIRQFlags();
  delay1ms(10);
  return app_mode;
}

static APP_ModeType_t APP_TxMode(void)
{
  if (DRV_Button_GetPressState(0) == DRV_BUTTON_PRESSED)
  {
    return APP_MODE_RX;
  }
  if (uart_rx_flag)
  {
    uart_rx_flag = 0;
    // Uart1_TxString((char *)uart_rx_buff);
    // Uart1_TxString("\r\n");
    AT_Command_t atcmd = AT_Parse((char *)uart_rx_buff);
    APP_ModeType_t mode = APP_HandleCommand(app_mode, atcmd);
    if (mode != app_mode)
    {
      return mode;
    }
  }

  delay1ms(20);
  return app_mode;
}

static APP_ModeType_t APP_HandleCommand(APP_ModeType_t mode, AT_Command_t cmd)
{
  switch (cmd)
  {
  case AT_Command_SetRxMode:
    if (mode == APP_MODE_RX)
    {
      Uart1_TxString("Already in RX mode\r\n");
    }
    else
    {
      return APP_MODE_RX;
    }
    break;
  case AT_Command_SetTxMode:
    if (mode == APP_MODE_TX)
    {
      Uart1_TxString("Already in TX mode\r\n");
    }
    else
    {
      return APP_MODE_TX;
    }
    break;
  case AT_Command_SetRxAddr:
    APP_SetRxAddr(uart_rx_buff);
    break;
  case AT_Command_SetTxAddr:
    APP_SetTxAddr(uart_rx_buff);
    break;
  case AT_Command_SetRfCh:
    APP_SetRfChannel(uart_rx_buff);
    break;
  case AT_Command_SetRfRate:
    APP_SetRfRate(uart_rx_buff);
    break;
  case AT_Command_SetRfPower:
    APP_SetRfPower(uart_rx_buff);
    break;
  case AT_Command_GetRxAddr:
    Uart1_TxString("Get RX addr\r\n");
    break;
  case AT_Command_GetTxAddr:
    Uart1_TxString("Get TX addr\r\n");
    break;
  case AT_Command_GetTStatus:
    NRF24L01_DumpConfig();
    break;
  case AT_Command_Unknown:
    Uart1_TxString("Unknown command\r\n");
    break;
  case AT_Command_None:
  default:
    if (mode == APP_MODE_TX)
    {
      NRF24L01_Tx(uart_rx_buff);
      Uart1_TxString("TX: ");
    }
    Uart1_TxString((char *)uart_rx_buff);
    Uart1_TxString("\r\n");
    break;
  }
  return mode;
}

static void APP_SetRxAddr(uint8_t *data)
{
  NRF24L01_SetRxAddr(1, data);
  Uart1_TxString("Set RX addr: ");
  for (uint8_t i = 0; i < 5; i++)
  {
    Uart1_TxHex8Bit(data[i]);
    Uart1_TxChar(' ');
  }
  Uart1_TxString("\r\n");
}

static void APP_SetTxAddr(uint8_t *data)
{
  NRF24L01_SetTxAddr(data);
  NRF24L01_SetRxAddr(0, data);
  Uart1_TxString("Set TX addr: ");
  for (uint8_t i = 0; i < 5; i++)
  {
    Uart1_TxHex8Bit(data[i]);
    Uart1_TxChar(' ');
  }
  Uart1_TxString("\r\n");
}

static void APP_SetRfChannel(uint8_t *data)
{
  if (*data > 125)
  {
    *data = 125;
  }
  NRF24L01_SetRfChannel(*data);
  Uart1_TxString("Set RF CH = ");
  Uart1_TxHex8Bit(*data);
  Uart1_TxString("\r\n");
}

static void APP_SetRfRate(uint8_t *data)
{
  NRF24L01_SetRfDataRate(*data);
  Uart1_TxString("Set RF Rate = ");
  switch (*data)
  {
    case 0:
      Uart1_TxString("1Mbps\r\n");
      break;
    case 1:
      Uart1_TxString("2Mbps\r\n");
      break;
    case 2:
    default:
      Uart1_TxString("250Kbps\r\n");
      break;
  }
}

static void APP_SetRfPower(uint8_t *data)
{
  NRF24L01_SetRfPower(*data);
  Uart1_TxString("Set RF Power = ");
  switch (*data)
  {
    case 0:
      Uart1_TxString("-18dBm\r\n");
      break;
    case 1:
      Uart1_TxString("-12dBm\r\n");
      break;
    case 2:
      Uart1_TxString("-6dBm\r\n");
      break;
    case 3:
    default:
      Uart1_TxString("0dBm\r\n");
      break;
  }
}
