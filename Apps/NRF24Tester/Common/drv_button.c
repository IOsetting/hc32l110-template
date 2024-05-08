#include "drv_button.h"


#define DRV_BUTTON_SIZE         1
#define PRESS_THRESHOLD         5
#define LONG_PRESS_THRESHOLD    100

typedef struct {
  uint8_t port;
  uint8_t pin;
  uint16_t counter;
  uint8_t pressed;
  uint8_t long_pressed;
} DRV_Key_TypeDef_t;

DRV_Key_TypeDef_t key[DRV_BUTTON_SIZE];

void DRV_Button_Init(uint8_t index, uint8_t port, uint8_t pin)
{
  key[index].port         = port;
  key[index].pin          = pin;
  key[index].counter      = 0;
  key[index].pressed      = 0;
  key[index].long_pressed = 0;
}

void DRV_Button_Tick(void)
{
  uint8_t i;
  for (i = 0; i < DRV_BUTTON_SIZE; i++)
  {
    if (GPIO_GetPinIn(key[i].port, key[i].pin) == 0 && key[i].counter < 0xFFFF)
    {
      key[i].counter++;
      if (key[i].counter > LONG_PRESS_THRESHOLD)
      {
        key[i].long_pressed = DRV_BUTTON_PRESSED;
      }
      else if (key[i].counter > PRESS_THRESHOLD)
      {
        key[i].pressed = DRV_BUTTON_PRESSED;
      }
    }
    else
    {
      key[i].counter = 0;
      key[i].pressed = DRV_BUTTON_RELEASED;
      key[i].long_pressed = DRV_BUTTON_RELEASED;
    }
  }
}

uint8_t DRV_Button_GetPressState(uint8_t index)
{
  return key[index].pressed;
}

uint8_t DRV_Button_GetLongPressState(uint8_t index)
{
  return key[index].long_pressed;
}

void DRV_Button_ClearState(uint8_t index)
{
  key[index].counter = 0;
  key[index].pressed = DRV_BUTTON_RELEASED;
  key[index].long_pressed = DRV_BUTTON_RELEASED;
}
