#ifndef __DRV_LED_H
#define __DRV_LED_H

#include "gpio.h"

#define DRV_LED_ON               1
#define DRV_LED_OFF              0

#define DRV_LED_PATTERN_BLINK_FAST      0
#define DRV_LED_PATTERN_BLINK_NORM      1
#define DRV_LED_PATTERN_BLINK_SLOW      2
#define DRV_LED_PATTERN_FLASH_NORM      3
#define DRV_LED_PATTERN_FLASH_SLOW      4
#define DRV_LED_PATTERN_LONG_ON         5
#define DRV_LED_PATTERN_LONG_OFF        6
#define DRV_LED_PATTERN_ONE_FLASH       7

#ifdef __cplusplus
extern "C" {
#endif

void DRV_LED_Init(uint8_t index, uint8_t port, uint8_t pin, uint8_t pattern, uint8_t continuous, uint8_t enabled);
void DRV_LED_Tick(void);
void DRV_LED_SetState(uint8_t index, uint8_t enabled);
void DRV_LED_SetPattern(uint8_t index, uint8_t pattern);

#ifdef __cplusplus
}
#endif

#endif // __DRV_LED_H
