#include "pca.h"
#include "lpm.h"
#include "gpio.h"

#define THRESHOLD    0x80

static volatile uint32_t u32PcaTestFlag = 0;

int main(void)
{
    stc_pca_config_t pcaConfig;
    stc_pca_capmodconfig_t pcaModConfig;
    uint8_t          period = THRESHOLD, dir = 0;

    CLK_EnablePeripheralClk(ClkPeripheralPca);
    CLK_EnablePeripheralClk(ClkPeripheralGpio);

    // Set P34 as PCA channel0, direction:output, (0:output, 1:input)
    Gpio_SetFunc_PCA_CH0_P34(0);

    // Proceed in idle mode
    pcaConfig.enCIDL = IdleGoon; 
    // Turn off WDT (module4)
    pcaConfig.enWDTE = PCAWDTDisable;
    // Frequency divider
    pcaConfig.enCPS  = PCAPCLKDiv32;
    Pca_Init(&pcaConfig);

    // Enable comparator for PWM
    pcaModConfig.enECOM = ECOMEnable;
    // Rise capture: off
    pcaModConfig.enCAPP = CAPPDisable;
    // Falling capture: off
    pcaModConfig.enCAPN = CAPNDisable;
    // Counter match interrupt: off
    pcaModConfig.enMAT  = MATDisable;
    // Counter match reverse: off
    pcaModConfig.enTOG  = TOGDisable;
    // CCPx Pin as PWM output
    pcaModConfig.enPWM  = PCAPWMEnable;
    Pca_CapModConfig(Module0, &pcaModConfig);
    // High 8-bit will be loaded to low 8-bit when overflow
    Pca_CapDataLSet(Module0, period);
    Pca_CapDataHSet(Module0, period);
    Pca_Run();

    while (1)
    {
        if (dir == 0)
        {
            Pca_CapDataHSet(Module0, period++);
            if (period == 0xFF) dir = 1;
        }
        else
        {
            Pca_CapDataHSet(Module0, period--);
            if (period == THRESHOLD) dir = 0;
        }
        delay1ms(10);
    }
}
