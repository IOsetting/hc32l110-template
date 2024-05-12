/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file uart.h
 **
 ** Headerfile for UART functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __UART_H__
#define __UART_H__
/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup UartGroup Universal Asynchronous Receiver/Transmitter (UART)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
 /**
 ******************************************************************************
 **\brief uart通道选择
 ******************************************************************************/

typedef enum en_uart_channel
{
    UARTCH0 = 0u, ///<串口0
    UARTCH1 = 1u, ///<串口1
}en_uart_channel_t;


/**
 ******************************************************************************
 ** \brief uart多主机模式地址帧/数据帧或者奇偶校验
 ******************************************************************************/
typedef enum en_uart_mmdorck
{
    Data = 0u, ///<多主机模式时，数据帧TB8标记   
    Addr = 1u, ///<多主机模式时，地址帧TB8标记   
}en_uart_mmdorck_t;
/**
 ******************************************************************************
 ** \brief uart奇偶校验
 ******************************************************************************/
typedef enum en_uart_check
{
    Even = 0u, ///<偶校验
    Odd  = 1u, ///<奇校验
}en_uart_check_t;
/**
 ******************************************************************************
 ** \brief uart多主机模式配置
 ******************************************************************************/
typedef enum en_uart_multimode
{
    UartNormal = 0u, ///<正常工作模式
    UartMulti  = 1u, ///<多主机工作模式
}en_uart_multimode_t;
/**
 ******************************************************************************
 ** \brief uart多主机模式及从机地址和地址掩码配置
 ******************************************************************************/

typedef struct stc_uart_multimode
{
    en_uart_multimode_t enMulti_mode; ///<多主机模式配置
    uint8_t             u8SlaveAddr;  ///<从机地址
    uint8_t                u8SaddEn;  ///<从及地址掩码
}stc_uart_multimode_t;

/**
 ******************************************************************************
 ** \brief uart 四种工作模式选择
 ******************************************************************************/

typedef enum en_uart_mode
{
    UartMode0 = 0u, // Mode0, 8-bit-width, sync, fixed baudrate = Fpclk / 12
    UartMode1 = 1u, // Mode1, 10-bit-width, async, clocked by timer, baudrate = (DBAUD+1)*Fpclk / 32 / (65536 - Timer_Period)
    UartMode2 = 2u, // Mode2, 11-bit-width, async, clocked by itself, baudrate = (DBAUD+1)*Fpclk / 64
    UartMode3 = 3u, // Mode3, 11-bit-width, async, clocked by timer, baudrate = (DBAUD+1)*Fpclk / 32 / (65536 - Timer_Period)
} en_uart_mode_t;
/**
 ******************************************************************************
 ** \brief uart 发送接收功能使能
 ******************************************************************************/
typedef enum en_uart_func
{
    UartTx = 0u, ///< mode0: TX    
    UartRx = 1u, ///< mode0: RX; mode1,mode2,mode3:RX & TX
}en_uart_func_t;
/**
 ******************************************************************************
 ** \brief uart发送接收中断使能
 ******************************************************************************/
typedef enum en_uart_irq_sel
{
    UartTxIrq = 0u,  ///<发送中断使能        
    UartRxIrq = 1u,  ///<接收中断使能
}en_uart_irq_sel_t;
/**
 ******************************************************************************
 ** \brief uart发送接收中断处理函数接口
 ******************************************************************************/

typedef struct stc_uart_irq_cb
{
    func_ptr_t pfnTxIrqCb;    ///<发送中断服务函数     
    func_ptr_t pfnRxErrIrqCb; ///<接收错误中断服务函数
    func_ptr_t pfnRxIrqCb;    ///<接收中断服务函数     
}stc_uart_irq_cb_t;
/**
 ******************************************************************************
 ** \brief uart 状态标志位
 ******************************************************************************/
typedef enum en_uart_status
{
    UartRFRAMEError = 0u,  ///<帧错误标记
    UartRxFull      = 1u,  ///<接收数据完成标记
    UartTxEmpty     = 2u,  ///<发送数据完成标记
   
}en_uart_status_t;
/**
 ******************************************************************************
 ** \brief uart 通道地址及中断函数地址结构
 ******************************************************************************/
typedef struct stc_uart_instance_data
{   
    uint32_t               u32Idx;               ///< 通道号
    M0P_UART_TypeDef       *pstcInstance;        ///< 通道寄存器地址
    stc_uart_irq_cb_t      stcUartInternIrqCb;   ///< 通道中断服务函数
} stc_uart_instance_data_t;
/**
 ******************************************************************************
 ** \brief uart 通道波特率配置
 ******************************************************************************/
typedef struct stc_uart_baud_config
{
    uint8_t u8Mode;   ///<四种工作模式
    boolean_t bDbaud; ///<是否双倍波特率
    uint32_t u32Baud; ///<波特率
}stc_uart_baud_config_t;
/**
 ******************************************************************************
 ** \uart 总体配置
 ******************************************************************************/
typedef struct stc_uart_config
{
    en_uart_mode_t       enRunMode;      ///< 四种模式配置
    stc_uart_multimode_t* pstcMultiMode; ///<多主机模式配置
    stc_uart_irq_cb_t*  pstcIrqCb;       ///<中断服务函数          
    boolean_t           bTouchNvic;      ///<NVIC中断使能    
} stc_uart_config_t;

#define UART0_SetMode(__UART_MODE__)    (M0P_UART0->SCON_f.SM01 = __UART_MODE__)
#define UART1_SetMode(__UART_MODE__)    (M0P_UART1->SCON_f.SM01 = __UART_MODE__)

#define UART0_SetDoubleBaud(__STATE__)    (M0P_UART0->SCON_f.DBAUD = __STATE__)
#define UART1_SetDoubleBaud(__STATE__)    (M0P_UART1->SCON_f.DBAUD = __STATE__)
// Calculate timer period, for UART mode1 and mode3 only
#define UARTx_CalculatePeriod(__PCLK__, __DOUBLE_BAUD__, __BAUD__) (0x10000 - ((__PCLK__ * (__DOUBLE_BAUD__ + 1)) / __BAUD__ / 32))

#define UART0_EnableTx()                (M0P_UART0->SCON_f.REN = 0)
#define UART0_EnableRx()                (M0P_UART0->SCON_f.REN = 1)
#define UART1_EnableTx()                (M0P_UART1->SCON_f.REN = 0)
#define UART1_EnableRx()                (M0P_UART1->SCON_f.REN = 1)

#define UART0_SetMultiModeOff()         (M0P_UART0->SCON_f.SM2 = 0)
#define UART1_SetMultiModeOff()         (M0P_UART1->SCON_f.SM2 = 0)

#define UART0_SetMultiMode(__U8_SLA_ADD__, __U8_ADD_MASK__)     do{         \
                                        M0P_UART0->SCON_f.SM2 = 1;          \
                                        M0P_UART0->SADDR = __U8_SLA_ADD__;  \
                                        M0P_UART0->SADEN = __U8_ADD_MASK__; \
                                    } while(0);

#define UART1_SetMultiMode(__U8_SLA_ADD__, __U8_ADD_MASK__)     do{         \
                                        M0P_UART1->SCON_f.SM2 = 1;          \
                                        M0P_UART1->SADDR = __U8_SLA_ADD__;  \
                                        M0P_UART1->SADEN = __U8_ADD_MASK__; \
                                    } while(0);

#define UART0_EnableTxSentIrq()         (M0P_UART0->SCON_f.TIEN = 1)
#define UART0_EnableRxReceivedIrq()     (M0P_UART0->SCON_f.RIEN = 1)
#define UART1_EnableTxSentIrq()         (M0P_UART1->SCON_f.TIEN = 1)
#define UART1_EnableRxReceivedIrq()     (M0P_UART1->SCON_f.RIEN = 1)

#define UART0_DisableTxSentIrq()         (M0P_UART0->SCON_f.TIEN = 0)
#define UART0_DisableRxReceivedIrq()     (M0P_UART0->SCON_f.RIEN = 0)
#define UART1_DisableTxSentIrq()         (M0P_UART1->SCON_f.TIEN = 0)
#define UART1_DisableRxReceivedIrq()     (M0P_UART1->SCON_f.RIEN = 0)

#define UART0_ClearRxReceivedStatus()   (M0P_UART0->ICR_f.RICLR = 0)
#define UART0_ClearTxSentStatus()       (M0P_UART0->ICR_f.TICLR = 0)
#define UART0_ClearFrameErrroStatus()   (M0P_UART0->ICR_f.FECLR = 0)
#define UART1_ClearRxReceivedStatus()   (M0P_UART1->ICR_f.RICLR = 0)
#define UART1_ClearTxSentStatus()       (M0P_UART1->ICR_f.TICLR = 0)
#define UART1_ClearFrameErrroStatus()   (M0P_UART1->ICR_f.FECLR = 0)
// UART0: read one byte received
#define UART0_RxReceive()               (M0P_UART0->SBUF)
// UART1: read one byte received
#define UART1_RxReceive()               (M0P_UART1->SBUF)

void Uart0_SetCallback(stc_uart_irq_cb_t *callbacks);
void Uart1_SetCallback(stc_uart_irq_cb_t *callbacks);

en_result_t Uart_DeInit(uint8_t u8Idx, boolean_t bTouchNvic);
//工作模式配置、多主机模式下从机地址和地址掩码设置
en_result_t Uart_SetMode(uint8_t u8Idx,en_uart_mode_t enMode);
en_result_t Uart_SetMultiMode(uint8_t u8Idx,stc_uart_multimode_t* pstcMultiConfig);
en_result_t Uart_SetMMDOrCk(uint8_t u8Idx,en_uart_mmdorck_t enTb8);
en_result_t Uart_SetSaddr(uint8_t u8Idx,uint8_t u8Addr);
en_result_t Uart_SetSaddrEn(uint8_t u8Idx,uint8_t u8Addren);
//获取Rb8位
boolean_t Uart_GetRb8(uint8_t u8Idx);
//设置TB8
en_result_t Uart_SetTb8(uint8_t u8Idx,en_uart_check_t enCheck,uint8_t u8Data);

en_result_t Uart_CheckEvenOrOdd(uint8_t u8Idx,en_uart_check_t enCheck,uint8_t u8Recv);

// 波特率设置
uint16_t Uart_SetBaudRate(uint8_t u8Idx,uint32_t u32pclk,stc_uart_baud_config_t* pstcBaud);

//状态位的获取和清除
boolean_t Uart_GetStatus(uint8_t u8Idx,en_uart_status_t enStatus);
en_result_t Uart_ClrStatus(uint8_t u8Idx,en_uart_status_t enStatus);
//数据查询方式的收发操作
//en_result_t  Uart_MultiSendFirstData(uint8_t U8Addr);

void Uart0_Init(uint32_t baud);
void Uart1_Init(uint32_t baud);
void Uart0_TxRx_Init(uint32_t baud, func_ptr_t rxCallback);
void Uart1_TxRx_Init(uint32_t baud, func_ptr_t rxCallback);

en_result_t Uart0_TxChar(uint8_t u8Data);
en_result_t Uart1_TxChar(uint8_t u8Data);

void Uart0_TxHex8Bit(uint8_t hex);
void Uart1_TxHex8Bit(uint8_t hex);

void Uart0_TxHexArray(uint8_t *hex, uint8_t len);
void Uart1_TxHexArray(uint8_t *hex, uint8_t len);

void Uart0_TxString(char *str);
void Uart1_TxString(char *str);

//@} // UartGroup

#ifdef __cplusplus
}
#endif

#endif /* __UART_H__ */
