#include "drv_led.h"

#define DRV_LED_SIZE      2
#define DRV_LED_STEPS     6

typedef struct {
  uint16_t period;
  uint16_t pattern[DRV_LED_STEPS];
} DRV_LED_Pattern_TypeDef_t;

typedef struct {
  uint8_t state;
  uint16_t counter;
  uint8_t pattern;
  uint8_t pos;
  uint8_t port;
  uint8_t pin;
} DRV_LED_TypeDef_t;

const DRV_LED_Pattern_TypeDef_t ledpattern[] = {
  {  60, {  1,  10,  21,  30,  41,  50}}, // quick blink
  { 200, {  1,  20,  41,  60,  81, 100}}, // blink
  { 300, {  1, 150,   0,   0,   0,   0}}, // slow blink
  { 100, { 45,  50,   0,   0,   0,   0}}, // short flash
  { 300, {145, 150,   0,   0,   0,   0}}, // long flash
  { 200, {  1,  21,   0,   0,   0,   0}}, // always on
  { 200, {  2,  22,   0,   0,   0,   0}}, // always off
};

DRV_LED_TypeDef_t led[DRV_LED_SIZE];


/**
 * Initialize the LED object by specifying port and pin
*/
void DRV_LED_Init(uint8_t index, uint8_t port, uint8_t pin, uint8_t pattern, uint8_t led_on)
{
  led[index].port      = port;
  led[index].pin       = pin;
  led[index].pattern   = pattern;
  led[index].state     = led_on;
  led[index].counter   = 0;
  led[index].pos       = 0;
}

void DRV_LED_Tick(void)
{
  for (uint8_t i = 0; i < DRV_LED_SIZE; i++)
  {
    if (led[i].state == DRV_LED_OFF) continue;

    led[i].counter++;
    if (led[i].counter >= ledpattern[led[i].pattern].period)
    {
      led[i].counter = 0;
    }
    if (led[i].counter == ledpattern[led[i].pattern].pattern[led[i].pos])
    {
      //DEBUG_PRINTF("led_%d, counter:%d (period:%d), pos:%d\r\n", i, led[i].counter, ledpattern[led[i].pattern].period, led[i].pos);
      GPIO_SetPinOut(led[i].port, led[i].pin, ledpattern[led[i].pattern].pattern[led[i].pos] % 2);
      // Skip the 0-value pos till pos start over
      do
      {
        led[i].pos = (led[i].pos + 1) % DRV_LED_STEPS;
      } while (led[i].pos != 0 && ledpattern[led[i].pattern].pattern[led[i].pos] == 0);
    }
  }
}

/**
 * Enable or disable LED
 * - Set LED output state
 * - reset counter and pos
 * - or set pin voltage level to low in case the output is high
*/
void DRV_LED_SetState(uint8_t index, uint8_t led_state)
{
  led[index].state = led_state;
  if (led_state == DRV_LED_ON)
  {
    led[index].counter = 0;
    led[index].pos = 0;
  }
  else
  {
    GPIO_SetPinOutLow(led[index].port, led[index].pin);
  }
}

/**
 * Set LED pattern, reset counter and pos
*/
void DRV_LED_SetPattern(uint8_t index, uint8_t pattern)
{
  led[index].counter = 0;
  led[index].pattern = pattern;
  led[index].pos = 0;
}
