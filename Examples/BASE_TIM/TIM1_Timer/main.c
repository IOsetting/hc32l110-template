#include "base_timer.h"

static volatile uint8_t ledState = 0;

void BaseTim1_IRQHandler(uint8_t u8Param)
{
    if (BASE_TIM1_GetIntFlag())
    {
        BASE_TIM1_ClearIntFlag();
        Gpio_SetIO(3, 4, ledState);
        ledState = 1 - ledState;
    }
}

int main(void)
{
    // Enable GPIO and Base Timer clock
    CLK_EnablePeripheralClk(ClkPeripheralGpio);
    CLK_EnablePeripheralClk(ClkPeripheralBaseTim);

    // Set GPIO P34 as output
    Gpio_InitIOExt(3, 4, GpioDirOut, TRUE, FALSE, FALSE, FALSE);

    // Timer1 configuration
    stc_bt_config_t timerConfig;
    // No gate control
    timerConfig.enGate  = BtGateDisable;
    // Clock source = PCLK / 16
    timerConfig.enPRS   = BtPCLKDiv16;
    // No reverse output on TOGN
    timerConfig.enTog   = BtTogDisable;
    // Run as timer
    timerConfig.enCT    = BtTimer;
    // Mode2: 16-bit auto-reload
    timerConfig.enMD    = BtMode2;
    BaseTim1_Init(&timerConfig);

    // Enable Timer1 interrupt
    BASE_TIM1_ClearIntFlag();
    BASE_TIM1_EnableIrq();
    EnableNvic(TIM1_IRQn, 3, TRUE);

    // Set timer period
    BASE_TIM1_SetARR(0x00);
    BASE_TIM1_SetCounter16(0x00);
    // Start timer
    BASE_TIM1_Run();

    while (1);
}
