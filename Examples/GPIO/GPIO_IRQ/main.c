#include "gpio.h"

#define KEY_PORT       (3)
#define KEY_PIN        (3)

#define LED_PORT       (3)
#define LED_PIN        (4)

volatile uint8_t flag;

void PORT3_IRQHandler(void)
{
    /** Clear interrupt flag before handling, otherwise it will be triggered twice */
    Gpio_ClearIrq(KEY_PORT, KEY_PIN); //M0P_GPIO->P3ICLR_f.P33 = 0U;
    if (Gpio_GetIrqStat(KEY_PORT, KEY_PIN)) // if (TRUE == M0P_GPIO->P3STAT_f.P33)
    {
        GPIO_SetPinOutHigh(LED_PORT, LED_PIN);
        delay1ms(1000);
        GPIO_SetPinOutLow(LED_PORT, LED_PIN);
    }
}

int main(void)
{
    // LED
    Gpio_InitIO(LED_PORT, LED_PIN, GpioDirOut);
    GPIO_SetPinOutHigh(LED_PORT, LED_PIN);
    delay1ms(500);
    GPIO_SetPinOutLow(LED_PORT, LED_PIN);

    // Key
    Gpio_InitIOExt(KEY_PORT, KEY_PIN, GpioDirIn, TRUE, FALSE, FALSE, 0);
    Gpio_ClearIrq(KEY_PORT, KEY_PIN);
    Gpio_EnableIrq(KEY_PORT, KEY_PIN, GpioIrqLow);
    EnableNvic(PORT3_IRQn, DDL_IRQ_LEVEL_DEFAULT, TRUE);

    while (1);
}
