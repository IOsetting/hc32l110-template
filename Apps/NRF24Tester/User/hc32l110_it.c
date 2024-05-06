#include "main.h"
#include "drv_led.h"
#include "drv_button.h"


__IO static uint16_t tick_counter = 0;

void SysTick_Handler(void)
{
  if (tick_counter++ == APP_TICK_INTERVAL)
  {
    tick_counter = 0;
    DRV_LED_Tick();
    DRV_Button_Tick();
  }
}
