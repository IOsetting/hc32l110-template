#ifndef __DRV_BUTTON_H
#define __DRV_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define DRV_BUTTON_RELEASED         0
#define DRV_BUTTON_PRESSED          1

void DRV_Button_Init(uint8_t index, uint8_t port, uint8_t pin);
void DRV_Button_Tick(void);
uint8_t DRV_Button_GetPressState(uint8_t index);
uint8_t DRV_Button_GetLongPressState(uint8_t index);
void DRV_Button_ClearState(uint8_t index);


#ifdef __cplusplus
}
#endif

#endif // __DRV_BUTTON_H
