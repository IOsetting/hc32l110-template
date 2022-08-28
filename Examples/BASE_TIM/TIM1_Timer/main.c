#include "ddl.h"
#include "base_timer.h"
#include "lpm.h"
#include "gpio.h"

static volatile uint8_t ledState = 0;

void Tim1Callback(void)
{
    if (M0P_BT1->IFR_f.TF)
    {
        M0P_BT1->ICLR_f.TFC = 0;
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
    stc_bt_config_t stcConfig;
    stcConfig.pfnTim1Cb = Tim1Callback;
    // No gate control
    stcConfig.enGate  = BtGateDisable;
    // Clock source = PCLK / 16
    stcConfig.enPRS   = BtPCLKDiv16;
    // No reverse output on TOGN
    stcConfig.enTog   = BtTogDisable;
    // Run as timer
    stcConfig.enCT    = BtTimer;
    // Mode2: 16-bit auto-reload
    stcConfig.enMD    = BtMode2;
    Bt_Init(TIM1, &stcConfig);

    // Enable Timer1 interrupt
    Bt_ClearIntFlag(TIM1);
    Bt_EnableIrq(TIM1);
    EnableNvic(TIM1_IRQn, 3, TRUE);

    // Set timer period
    Bt_ARRSet(TIM1, 0x0);
    Bt_Cnt16Set(TIM1, 0x0);
    // Start timer
    Bt_Run(TIM1);

    while (1);
}
