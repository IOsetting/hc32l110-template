#include "main.h"

#include "drv_led.h"
#include "drv_button.h"
#include "hc32l110_bsp.h"
#include "ring_buffer.h"
#include "nrf24l01.h"

typedef enum {
  APP_MODE_INIT,
  APP_MODE_TX,
  APP_MODE_RX
} APP_ModeType_t;

extern __IO uint8_t opflag;
extern uint8_t opcommand[RING_BUFFER_SIZE];

APP_ModeType_t app_mode, app_mode_next;


static APP_ModeType_t APP_Init(void);
static void APP_ModeSwitchTo(APP_ModeType_t mode);
static APP_ModeType_t APP_RxMode(void);
static APP_ModeType_t APP_TxMode(void);

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

  DRV_LED_Init(0, 3, 4, DRV_LED_PATTERN_BLINK_SLOW, DRV_LED_ON);
  DRV_LED_Init(1, 3, 5, DRV_LED_PATTERN_BLINK_NORM, DRV_LED_ON);
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
    Uart1_TxString("RX mode\r\n");
    delay1ms(200);
    DRV_Button_ClearState(0);
    break;

  case APP_MODE_TX:
  default:
    Uart1_TxString("TX mode\r\n");
    delay1ms(200);
    DRV_Button_ClearState(0);
    break;
  }
}

static APP_ModeType_t APP_RxMode(void)
{
  if (DRV_Button_GetPressState(0) == DRV_BUTTON_PRESSED)
  {
    return APP_MODE_TX;
  }

  if (opflag)
  {
    opflag = 0;
    Uart1_TxString((char *)opcommand);
    Uart1_TxString("\r\n");
  }
  delay1ms(50);
  return APP_MODE_RX;
}

static APP_ModeType_t APP_TxMode(void)
{
  if (DRV_Button_GetPressState(0) == DRV_BUTTON_PRESSED)
  {
    return APP_MODE_RX;
  }
  return APP_MODE_TX;
}