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
#include "main.h"

#include "drv_led.h"
#include "drv_button.h"
#include "drv_uart.h"
#include "ring_buffer.h"

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
   * Set PCLK = HCLK = Clock source to 24MHz
   */
  Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);
  // Enable peripheral clock
  CLK_EnablePeripheralClk(ClkPeripheralBaseTim);
  // GPIO clock is required
  CLK_EnablePeripheralClk(ClkPeripheralGpio);
  // Enable systick interrupt
  CLK_EnableSysTickIrq();

  DRV_UART_Init();

  Gpio_InitIOExt(3, 4, GpioDirOut, FALSE, FALSE, FALSE, FALSE);
  Gpio_InitIOExt(3, 5, GpioDirOut, FALSE, FALSE, FALSE, FALSE);
  DRV_LED_Init(0, 3, 4, DRV_LED_PATTERN_BLINK_SLOW, DRV_LED_ON);
  DRV_LED_Init(1, 3, 5, DRV_LED_PATTERN_BLINK_NORM, DRV_LED_ON);

  Gpio_InitIOExt(3, 3,  GpioDirIn, TRUE, FALSE, FALSE, FALSE);
  DRV_Button_Init(0, 3, 3);

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