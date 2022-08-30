#include "base_timer.h"
#include "adc.h"
#include "gpio.h"
#include "uart.h"

void Uart1_Init(void)
{
    uint16_t period;
    uint32_t pclk;
    stc_bt_config_t baseTimerConfig;
    // Config UART1
    UART1_SetDoubleBaud(TRUE);
    UART1_SetMode(UartMode1);
    UART1_SetMultiModeOff();
    UART1_EnableRxReceivedIrq();
    UART1_ClearRxReceivedStatus();
    UART1_ClearTxSentStatus();
    UART1_EnableRx();

    // Config timer1 as baudrate source
    baseTimerConfig.enMD = BtMode2;
    baseTimerConfig.enCT = BtTimer;
    BaseTim1_Init(&baseTimerConfig);

    // Set timer period
    pclk = Clk_GetPClkFreq();
    period = UARTx_CalculatePeriod(pclk, 1, 115200);
    BASE_TIM1_SetARR(period);
    BASE_TIM1_SetCounter16(period);
    // Start timer
    BASE_TIM1_Run();
}

int main(void)
{
    stc_adc_cfg_t      stcAdcCfg;
    stc_adc_scan_cfg_t stcAdcScanCfg;
    uint8_t            i;
    uint16_t           adcResult;

    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);

    DDL_ZERO_STRUCT(stcAdcCfg);
    DDL_ZERO_STRUCT(stcAdcScanCfg);

    // Enable peripheral clock
    CLK_EnablePeripheralClk(ClkPeripheralBaseTim);
    CLK_EnablePeripheralClk(ClkPeripheralGpio);
    CLK_EnablePeripheralClk(ClkPeripheralUart1);
    CLK_EnablePeripheralClk(ClkPeripheralAdcBgr);
    // Set P01,P02 as UART1 TX,RX
    Gpio_SetFunc_UART1_TXD_P01();
    Gpio_SetFunc_UART1_RXD_P02();

    Uart1_Init();

    Gpio_SetAnalog(2, 4, TRUE); // AIN0
    Gpio_SetAnalog(2, 6, TRUE); // AIN1
    Gpio_SetAnalog(3, 2, TRUE); // AIN2
    Gpio_SetAnalog(3, 3, TRUE); // AIN3 +
    Gpio_SetAnalog(3, 4, TRUE); // AIN4
    // P35:AIN5, 
    Gpio_SetAnalog(3, 6, TRUE); // AIN6
    // P01:AIN7
    // P02:AIN8

    ADC_Enable();
    // Enable Reference Voltage for ADC
    M0P_BGR->CR_f.BGR_EN = 0x1u;
    // Enable internal temperature sensor
    M0P_BGR->CR_f.TS_EN = 0x1u;
    // Wait 20us+ for above become stable
    delay100us(1);

    // Scan mode
    stcAdcCfg.enAdcOpMode = AdcScanMode;
    // ADC Clock
    stcAdcCfg.enAdcClkSel = AdcClkSysTDiv2;
    stcAdcCfg.enAdcSampTimeSel = AdcSampTime4Clk;
    // Reference voltage: internal 2.5V(avdd>3V,SPS<=200kHz)
    //stcAdcCfg.enAdcRefVolSel = RefVolSelInBgr2p5;
    // Reference voltage: AVDD
    stcAdcCfg.enAdcRefVolSel = RefVolSelAVDD;
    // Amplifier for small signals: off
    stcAdcCfg.bAdcInBufEn = FALSE;
    // auto convert trigger
    stcAdcCfg.enAdcTrig0Sel = AdcTrigDisable;
    stcAdcCfg.enAdcTrig1Sel = AdcTrigDisable;
    Adc_Init(&stcAdcCfg);

    stcAdcScanCfg.u8AdcScanModeCh = ADC_SCAN_CH0_EN  | ADC_SCAN_CH1_EN | ADC_SCAN_CH2_EN
                                    | ADC_SCAN_CH3_EN | ADC_SCAN_CH4_EN | ADC_SCAN_CH6_EN;

    // Number of conversions = channels * N - 1
    // For 6 channels, 1 round = 5, 2 rounds = 11, ...
    stcAdcScanCfg.u8AdcSampCnt = 0x11;
    Adc_ConfigScanMode(&stcAdcCfg, &stcAdcScanCfg);    

    while(1)
    {
        ADC_Start();
        while(FALSE == M0P_ADC->IFR_f.CONT_INTF);
        M0P_ADC->ICLR_f.CONT_INTC = 0;
        for (i = 0; i < 9; i++)
        {
            adcResult = ADC_GetScanResult(i);
            Uart1_TxHex((uint8_t *)&adcResult, 2);
            Uart1_TxChar(' ');
        }
        Uart1_TxChar('\n');
        delay1ms(100);
    }
}
