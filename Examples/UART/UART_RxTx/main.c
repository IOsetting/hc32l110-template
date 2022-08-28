#include "uart.h"
#include "base_timer.h"

uint8_t u8RxData[2] = {0x55, 0x00};
uint8_t u8RxFlg = 0;

void RxIntCallback(void)
{
    u8RxData[1] = UART1_RxReceive();
    u8RxFlg = 1;
}

int main(void)
{
    uint16_t period;
    uint32_t hclk, pclk;

    stc_uart_irq_cb_t stcUartIrqCb;
    stc_bt_config_t baseTimerConfig;

    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);

    // Enable peripheral clock
    CLK_EnablePeripheralClk(ClkPeripheralBaseTim);
    CLK_EnablePeripheralClk(ClkPeripheralGpio); // GPIO clock is required, equal to M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;
    CLK_EnablePeripheralClk(ClkPeripheralUart1);
    // Set UART port
    Gpio_SetFunc_UART1TX_P35();
    Gpio_SetFunc_UART1RX_P36();
    // Config UART1
    UART1_SetDoubleBaud(TRUE);
    UART1_SetMode(UartMode1);
    UART1_SetMultiModeOff();
    stcUartIrqCb.pfnRxIrqCb = RxIntCallback;
    stcUartIrqCb.pfnTxIrqCb = NULL;
    stcUartIrqCb.pfnRxErrIrqCb = NULL;
    Uart1_SetCallback(&stcUartIrqCb);
    UART1_EnableRxReceivedIrq();
    UART1_ClearRxReceivedStatus();
    UART1_ClearTxSentStatus();
    UART1_EnableRx();

    // Config timer1 as baudrate source
    baseTimerConfig.enMD = BtMode2;
    baseTimerConfig.enCT = BtTimer;
    BaseTim1_Init(&baseTimerConfig);
    // Set timer period
    hclk = Clk_GetHClkFreq();
    pclk = Clk_GetPClkFreq();
    period = UARTx_CalculatePeriod(pclk, 1, 115200);
    BASE_TIM1_SetARR(period);
    BASE_TIM1_SetCounter16(period);
    // Start timer
    BASE_TIM1_Run();


    delay1ms(100);
    Uart1_TxString("HCLK:");
    Uart1_TxHex((uint8_t *)&hclk, 4);
    Uart1_TxChar(':');
    Uart1_TxHex((uint8_t *)&pclk, 4);
    Uart1_TxChar(':');
    while (1)
    {
        if (u8RxFlg)
        {
            u8RxFlg = 0;
            Uart1_TxChar(u8RxData[0]);
            Uart1_TxChar(u8RxData[1]);
        }
        // Avoid compiler optimization
        delay1ms(1);
    }
}
