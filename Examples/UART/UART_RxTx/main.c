#include "uart.h"
#include "base_timer.h"
#include "lpm.h"
#include "gpio.h"

uint8_t u8RxData[2] = {0x55, 0x00};
uint8_t u8RxFlg = 0;

void RxIntCallback(void)
{
    u8RxData[1] = UART1_RxReceive();
    u8RxFlg = 1;
}

void ErrIntCallback(void)
{
}

int main(void)
{
    uint16_t period;
    uint32_t hclk, pclk;

    stc_uart_config_t stcConfig;
    stc_uart_irq_cb_t stcUartIrqCb;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_config_t stcBaud;
    stc_bt_config_t stcBtConfig;

    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);

    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    DDL_ZERO_STRUCT(stcBtConfig);

    Gpio_InitIOExt(3, 5, GpioDirOut, TRUE, FALSE, FALSE, FALSE);
    Gpio_InitIOExt(3, 6, GpioDirOut, TRUE, FALSE, FALSE, FALSE);

    // Set UART port
    Gpio_SetFunc_UART1TX_P35();
    Gpio_SetFunc_UART1RX_P36();

    // Enable peripheral clock
    Clk_SetPeripheralGate(ClkPeripheralBt, TRUE);
    Clk_SetPeripheralGate(ClkPeripheralUart1, TRUE);

    stcUartIrqCb.pfnRxIrqCb = RxIntCallback;
    stcUartIrqCb.pfnTxIrqCb = NULL;
    stcUartIrqCb.pfnRxErrIrqCb = ErrIntCallback;
    stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;

    stcConfig.enRunMode = UartMode1;    // Mode 1, 10-bit frame (1 start + 8 data + 1 stop)
    stcMulti.enMulti_mode = UartNormal; // Single host mode
    stcConfig.pstcMultiMode = &stcMulti;

    stcBaud.bDbaud = 1;        // Double baudrate, 0:off, 1:on
    stcBaud.u32Baud = 115200;    // Baudrate
    stcBaud.u8Mode = stcConfig.enRunMode;
    hclk = Clk_GetHClkFreq();
    pclk = Clk_GetPClkFreq();
    period = Uart_SetBaudRate(UARTCH1, pclk, &stcBaud);

    stcBtConfig.enMD = BtMode2;
    stcBtConfig.enCT = BtTimer;
    Bt_Init(TIM1, &stcBtConfig); // Setup timer 1 as baudrate source
    Bt_ARRSet(TIM1, period);
    Bt_Cnt16Set(TIM1, period);
    Bt_Run(TIM1);

    Uart_Init(UARTCH1, &stcConfig);
    UART1_EnableRxReceivedIrq();
    UART1_ClearRxReceivedStatus();
    UART1_ClearTxSentStatus();
    UART1_EnableRx();

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
