#include "ddl.h"
#include "uart.h"
#include "bt.h"
#include "lpm.h"
#include "gpio.h"

uint8_t u8RxData[2] = {0x55, 0x00};
uint8_t u8RxFlg = 0;

void RxIntCallback(void)
{
    u8RxData[1] = M0P_UART1->SBUF;
    u8RxFlg = 1;
}

void ErrIntCallback(void)
{
}

int main(void)
{
    uint16_t timer = 0;
    uint32_t pclk = 0;

    stc_uart_config_t stcConfig;
    stc_uart_irq_cb_t stcUartIrqCb;
    stc_uart_multimode_t stcMulti;
    stc_uart_baud_config_t stcBaud;
    stc_bt_config_t stcBtConfig;

    DDL_ZERO_STRUCT(stcUartIrqCb);
    DDL_ZERO_STRUCT(stcMulti);
    DDL_ZERO_STRUCT(stcBaud);
    DDL_ZERO_STRUCT(stcBtConfig);

    Gpio_InitIOExt(3, 5, GpioDirOut, TRUE, FALSE, FALSE, FALSE);
    Gpio_InitIOExt(3, 6, GpioDirOut, TRUE, FALSE, FALSE, FALSE);

    // Set UART port
    Gpio_SetFunc_UART1TX_P35();
    Gpio_SetFunc_UART1RX_P36();

    // Enable peripheral clock
    Clk_SetPeripheralGate(ClkPeripheralBt, TRUE); //模式0/2可以不使能
    Clk_SetPeripheralGate(ClkPeripheralUart1, TRUE);

    stcUartIrqCb.pfnRxIrqCb = RxIntCallback;
    stcUartIrqCb.pfnTxIrqCb = NULL;
    stcUartIrqCb.pfnRxErrIrqCb = ErrIntCallback;
    stcConfig.pstcIrqCb = &stcUartIrqCb;
    stcConfig.bTouchNvic = TRUE;

    stcConfig.enRunMode = UartMode3;    //测试项，更改此处来转换4种模式测试
    stcMulti.enMulti_mode = UartNormal; //测试项，更改此处来转换多主机模式，mode2/3才有多主机模式
    stcConfig.pstcMultiMode = &stcMulti;

    stcBaud.bDbaud = 0u;        // 双倍波特率功能
    stcBaud.u32Baud = 9600u;    // Baud
    stcBaud.u8Mode = UartMode3; // 计算波特率需要模式参数
    pclk = Clk_GetPClkFreq();
    timer = Uart_SetBaudRate(UARTCH1, pclk, &stcBaud);

    stcBtConfig.enMD = BtMode2;
    stcBtConfig.enCT = BtTimer;
    Bt_Init(TIM1, &stcBtConfig); // 调用basetimer1设置函数产生波特率
    Bt_ARRSet(TIM1, timer);
    Bt_Cnt16Set(TIM1, timer);
    Bt_Run(TIM1);

    Uart_Init(UARTCH1, &stcConfig);
    Uart_EnableIrq(UARTCH1, UartRxIrq);
    Uart_ClrStatus(UARTCH1, UartRxFull);
    Uart_EnableFunc(UARTCH1, UartRx);

    Uart_SendData(UARTCH1, 'S');
    Uart_SendData(UARTCH1, 'T');
    Uart_SendData(UARTCH1, 'A');
    Uart_SendData(UARTCH1, 'R');
    Uart_SendData(UARTCH1, 'T');
    Uart_SendData(UARTCH1, ':');
    while (1)
    {
        if (u8RxFlg)
        {
            u8RxFlg = 0;
            Uart_SendData(UARTCH1, u8RxData[0]);
            Uart_SendData(UARTCH1, u8RxData[1]);
        }
        // Avoid compiler optimization
        delay1ms(1);
    }
}
