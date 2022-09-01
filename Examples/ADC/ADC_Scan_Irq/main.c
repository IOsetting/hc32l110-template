#include "base_timer.h"
#include "adc.h"
#include "gpio.h"
#include "uart.h"

static  uint8_t   i, j;
static  uint16_t  u16ScanResult[8];

void AdcContIrqCallback(void)
{
    // Interrupt clear will be handled by Adc_IRQHandler();
    for (i = 0; i < 8; i++)
    {
        u16ScanResult[i] = ADC_GetScanResult(i);
    }
}

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
    stc_adc_cfg_t             stcAdcCfg;
    stc_adc_scan_cfg_t        stcAdcScanCfg;
    stc_adc_irq_t             stcAdcIrq;
    stc_adc_irq_calbakfn_pt_t stcAdcIrqCalbaks;

    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);
    
    DDL_ZERO_STRUCT(stcAdcCfg);
    DDL_ZERO_STRUCT(stcAdcScanCfg);
    DDL_ZERO_STRUCT(stcAdcIrq);
    DDL_ZERO_STRUCT(stcAdcIrqCalbaks);

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
    M0P_BGR->CR_f.BGR_EN = 1;
    // Enable internal temperature sensor
    M0P_BGR->CR_f.TS_EN = 0;
    // Wait 20us+ for above become stable
    delay100us(1);

    // Scan mode
    stcAdcCfg.enAdcOpMode = AdcScanMode;
    // ADC Clock
    stcAdcCfg.enAdcClkSel = AdcClkSysTDiv1;
    // Sample time 8 clocks
    stcAdcCfg.enAdcSampTimeSel = AdcSampTime8Clk;
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

    // Enable interrupt callbacks
    stcAdcIrq.bAdcIrq = TRUE;
    stcAdcIrq.bAdcRegCmp = FALSE;
    stcAdcIrq.bAdcHhtCmp = FALSE;
    stcAdcIrq.bAdcLltCmp = FALSE;
    // Callback functions
    stcAdcIrqCalbaks.pfnAdcContIrq = AdcContIrqCallback;
    stcAdcIrqCalbaks.pfnAdcRegIrq = NULL;
    stcAdcIrqCalbaks.pfnAdcHhtIrq = NULL;
    stcAdcIrqCalbaks.pfnAdcLltIrq = NULL;
    Adc_ConfigIrq(&stcAdcIrq, &stcAdcIrqCalbaks);
    Adc_EnableIrq();
    Adc_CmpCfg(&stcAdcIrq);

    stcAdcScanCfg.u8AdcScanModeCh = ADC_SCAN_CH0_EN  | ADC_SCAN_CH1_EN | ADC_SCAN_CH2_EN
                                    | ADC_SCAN_CH3_EN | ADC_SCAN_CH4_EN | ADC_SCAN_CH6_EN;

    stcAdcScanCfg.u8AdcSampCnt = 0x5;
    Adc_ConfigScanMode(&stcAdcCfg, &stcAdcScanCfg);

    while(1)
    {
        ADC_Start();
        delay1ms(200);
        for (j = 0; j < 8; j++)
        {
            Uart1_TxHex((uint8_t *)&u16ScanResult[j], 2);
            Uart1_TxChar(' ');
        }
        Uart1_TxChar('\n');
    }
}