/*************************************************************************************
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
/******************************************************************************/
/** \file uart.c
 **
 ** UART function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "uart.h"
/**
 ******************************************************************************
 ** \addtogroup UartGroup
 ******************************************************************************/
//@{
/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/

#define IS_VALID_CH(x)          ((UARTCH0 == (x)) ||\
                                 (UARTCH1 == (x)))

#define IS_VALID_IRQSEL(x)      ((UartTxIrq == (x)) ||\
                                 (UartRxIrq == (x))) 

#define IS_VALID_MODE(x)        ((UartMode0==(x))||\
                                 (UartMode1==(x))||\
                                 (UartMode2==(x))||\
                                 (UartMode3==(x)))

#define IS_VALID_STATUS(x)      ((UartRFRAMEError == (x))||\
                                 (UartRxFull == (x))||\
                                 (UartTxEmpty == (x)))
/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/
static stc_uart_instance_data_t* UartGetInternDataPtr(uint8_t u8Idx);
static void UartInitNvic(uint8_t u8Idx);
static void UartDeInitNvic(uint8_t u8Idx);
/******************************************************************************/
/* Local variable definitions ('static')                                       */
/******************************************************************************/
static stc_uart_instance_data_t m_astcUartInstanceDataLut[] =
{
    {
        UARTCH0,
        M0P_UART0,       /* pstcInstance */
        {NULL,NULL,NULL},     
    },
    {
        UARTCH1,
        M0P_UART1,       /* pstcInstance */
       {NULL,NULL,NULL},    
    },
};
/**
 ******************************************************************************
 ** \brief  UART0/1通道 相关地址获取
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 通道对应的地址结构
 **
 ******************************************************************************/
static stc_uart_instance_data_t* UartGetInternDataPtr(uint8_t u8Idx)
{
    stc_uart_instance_data_t* pstcData = NULL;
    uint8_t u8i = 0;
    for (u8i = 0; u8i < ARRAY_SZ(m_astcUartInstanceDataLut); u8i++)
    {
        if (u8Idx == m_astcUartInstanceDataLut[u8i].u32Idx)
        {
            pstcData = &m_astcUartInstanceDataLut[u8i];
            break;
        }
    }

    return (pstcData);
}

/**
 ******************************************************************************
 ** \brief  UART通道4种模式配置
 **
 ** \param [in] u8Idx通道号，mode哪种模式
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetMode(uint8_t u8Idx,en_uart_mode_t enMode)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    ASSERT(IS_VALID_MODE(enMode));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    } 
    pstcData->pstcInstance->SCON_f.SM01 = enMode;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式配置
 **
 ** \param [in] u8Idx通道号，stcMultiConfig多主机模式结构
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetMultiMode(uint8_t u8Idx,stc_uart_multimode_t* pstcMultiConfig)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    if(NULL != pstcMultiConfig)
    {
        pstcData->pstcInstance->SCON_f.SM2 = pstcMultiConfig->enMulti_mode;
        if(pstcMultiConfig->enMulti_mode == UartMulti)
        {
            pstcData->pstcInstance->SADDR = pstcMultiConfig->u8SlaveAddr;
            pstcData->pstcInstance->SADEN = pstcMultiConfig->u8SaddEn;
        }
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式发送数据/地址帧或者奇偶校验配置TB8
 **
 ** \param [in] u8Idx通道号，tb8数据or地址帧或者奇偶校验
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetMMDOrCk(uint8_t u8Idx,en_uart_mmdorck_t enTb8)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    pstcData->pstcInstance->SCON_f.TB8 = enTb8;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief 获取RB8数值
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval RB8
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
boolean_t Uart_GetRb8(uint8_t u8Idx)
{
     stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    return (pstcData->pstcInstance->SCON_f.RB8);
}
/**
 ******************************************************************************
 ** \brief 计算字节数据1的个数
 **
 ** \param u8Data计算数据
 **
 ** \retval 个数
 ******************************************************************************/
en_result_t Uart_SetTb8(uint8_t u8Idx,en_uart_check_t enCheck,uint8_t u8Data)
{
	uint8_t cnt=0,i;
	stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }	
	for(i=0;i<8;i++)
	{
		if((u8Data&0x80)==0x80)
		{
			cnt++;
		}
		u8Data<<=1;
	}
	if(enCheck == Even)
	{
		if(cnt%2!=0)
		{
			pstcData->pstcInstance->SCON_f.TB8 = 1;
		}
		else
		{
			pstcData->pstcInstance->SCON_f.TB8 = 0;
		}
	}
	else
	{
		if(cnt%2!=0)
		{
			pstcData->pstcInstance->SCON_f.TB8 = 0;
		}
		else
		{
			pstcData->pstcInstance->SCON_f.TB8 = 1;
		}
	}
	return Ok;
}
/**
 ******************************************************************************
 ** \brief 计算接收字节奇偶校验是否正确
 **
 ** \param u8Idx通道，enCheck奇偶校验方式，u8Recv校验数据
 **
 ** \retval Error或者成功Ok
 ******************************************************************************/
en_result_t Uart_CheckEvenOrOdd(uint8_t u8Idx,en_uart_check_t enCheck,uint8_t u8Recv)
{
	uint8_t cnt=0,i;
	stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
	for(i=0;i<8;i++)
	{
		if((u8Recv&0x80)==0x80)
		{
			cnt++;
		}
		u8Recv<<=1;
	}
	if(enCheck == Even)
	{
		if(cnt%2!=0)
		{
			if(pstcData->pstcInstance->SCON_f.RB8 != 1)
			{
				return Error;
			}
		}
		else
		{
			if(pstcData->pstcInstance->SCON_f.RB8 != 0)
			{
				return Error;
			}
		}
	}
	else
	{
		if(cnt%2!=0)
		{
			if(pstcData->pstcInstance->SCON_f.RB8 != 0)
			{
				return Error;
			}
		}
		else
		{
			if(pstcData->pstcInstance->SCON_f.RB8 != 1)
			{
				return Error;
			}
		}
	}
	return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式从机地址配置函数
 **
 ** \param [in] u8Idx通道号，addr地址
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetSaddr(uint8_t u8Idx,uint8_t u8Addr)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    pstcData->pstcInstance->SADDR = u8Addr;
    return Ok;
}
/**
 ******************************************************************************
 ** \brief  UART通道多主机模式从机掩码配置函数
 **
 ** \param [in] u8Idx通道号，addren地址掩码
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_SetSaddrEn(uint8_t u8Idx,uint8_t u8Addren)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    pstcData->pstcInstance->SADEN = u8Addren;
    return Ok;  
}
/**
 ******************************************************************************
 ** \brief  UART通道波特率配置
 **
 ** \param [in] u8Idx通道号，u32pclk时钟源，stcBaud波特率配置结构
 **
 ** \retval 定时器配置值
 ** \retval 0,获取值失败
 ******************************************************************************/
uint16_t Uart_SetBaudRate(uint8_t u8Idx,uint32_t u32pclk,stc_uart_baud_config_t* pstcBaud)
{
    uint16_t u16tmload=0;
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if ((NULL == pstcData)||(NULL == pstcBaud))
    {
        return 0;//test
    }
    pstcData->pstcInstance->SCON_f.DBAUD = pstcBaud->bDbaud;
    switch(pstcBaud->u8Mode)
    {
        case UartMode0:
        case UartMode2:
            break;
        case UartMode1:
        case UartMode3:
            u16tmload = 0x10000-((u32pclk*(pstcBaud->bDbaud+1))/(pstcBaud->u32Baud*32));//单双倍波特率，定时器配置
            break;
        default:
            break; 
    }
    return u16tmload;
}

/**
 ******************************************************************************
 ** \brief  UART通道通信状态获取
 **
 ** \param [in] u8Idx通道号，enStatus获取哪个状态
 **
 ** \retval 状态值
 **\retval ErrorInvalidParameter获取失败
 ******************************************************************************/
boolean_t Uart_GetStatus(uint8_t u8Idx,en_uart_status_t enStatus)
{
    boolean_t bStatus=FALSE;
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    ASSERT(IS_VALID_STATUS(enStatus));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;//4，用户只需判断0或1
    }
    switch(enStatus)
    {
        case UartRFRAMEError:
            bStatus = (pstcData->pstcInstance->ISR_f.FE == 1) ? TRUE : FALSE;
            break;
        case UartRxFull:
            bStatus = (pstcData->pstcInstance->ISR_f.RI == 1) ? TRUE : FALSE;
            break;
        case UartTxEmpty:
            bStatus = (pstcData->pstcInstance->ISR_f.TI == 1) ? TRUE : FALSE;
            break;
        default:
            break; 
    }
    return bStatus;
}
/**
 ******************************************************************************
 ** \brief  UART通道通信状态清除
 **
 ** \param [in] u8Idx通道号，enStatus清除哪个状态
 **
 ** \retval 状态值
 **\retval ErrorInvalidParameter清除失败
 ******************************************************************************/
en_result_t Uart_ClrStatus(uint8_t u8Idx,en_uart_status_t enStatus)
{
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    ASSERT(IS_VALID_STATUS(enStatus));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    switch(enStatus)
    {
        case UartRFRAMEError:
            pstcData->pstcInstance->ICR_f.FECLR = 0;
            break;
        case UartRxFull:
            pstcData->pstcInstance->ICR_f.RICLR = 0;
            break;
        case UartTxEmpty:
            pstcData->pstcInstance->ICR_f.TICLR = 0;
            break;
        default:
            return ErrorInvalidParameter; 
    }
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  UART通道中断处理函数
 **
 ** \param [in] u8Param通道号
 **
 ** \retval 无
 **
 ******************************************************************************/
void Uart_IRQHandler(uint8_t u8Param)
{
    stc_uart_instance_data_t *pstcData = NULL;
    pstcData = UartGetInternDataPtr(u8Param);
    if (NULL == pstcData)
    {
        return;
    }
    if(1 == pstcData->pstcInstance->ISR_f.FE)
    {
        Uart_ClrStatus(u8Param,UartRFRAMEError);
        if(NULL != pstcData->stcUartInternIrqCb.pfnRxErrIrqCb)
        {
            pstcData->stcUartInternIrqCb.pfnRxErrIrqCb();
        }
        return;//若奇偶校验出错则不进行后续数据处理
    }
    if(1 == pstcData->pstcInstance->ISR_f.RI)
    {
        Uart_ClrStatus(u8Param,UartRxFull);
        if(NULL != pstcData->stcUartInternIrqCb.pfnRxIrqCb)
        {
            pstcData->stcUartInternIrqCb.pfnRxIrqCb();
        }
    }
    if(1 == pstcData->pstcInstance->ISR_f.TI)
    {
        Uart_ClrStatus(u8Param,UartTxEmpty);
        if(NULL != pstcData->stcUartInternIrqCb.pfnTxIrqCb)
        {
            pstcData->stcUartInternIrqCb.pfnTxIrqCb();
        }
    }
}
/**
 ******************************************************************************
 ** \brief  UART通道使能内核NVIC中断
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 无
 **
 ******************************************************************************/
static void UartInitNvic(uint8_t u8Idx)
{
    IRQn_Type enIrqIndex;
    
    ASSERT(IS_VALID_CH(u8Idx));;
    enIrqIndex = (IRQn_Type)(UART0_IRQn + u8Idx);
    NVIC_ClearPendingIRQ(enIrqIndex);
    NVIC_SetPriority(enIrqIndex,DDL_IRQ_LEVEL_DEFAULT);
    NVIC_EnableIRQ(enIrqIndex);
    
}
/**
 ******************************************************************************
 ** \brief  UART通道禁止内核NVIC中断
 **
 ** \param [in] u8Idx通道号
 **
 ** \retval 无
 **
 ******************************************************************************/
static void UartDeInitNvic(uint8_t u8Idx)
{
    IRQn_Type enIrqIndex;

    ASSERT(IS_VALID_CH(u8Idx));
    enIrqIndex = (IRQn_Type)(UART0_IRQn + u8Idx);
    NVIC_ClearPendingIRQ(enIrqIndex);
    NVIC_SetPriority(enIrqIndex,DDL_IRQ_LEVEL_DEFAULT);
    NVIC_DisableIRQ(enIrqIndex);
}
/**
 ******************************************************************************
 ** \brief  UART通道初始化函数
 **
 ** \param [in] u8Idx通道号，pstcConfig初始化结构体
 **
 ** \retval OK配置成功
 **\retval ErrorInvalidParameter配置失败
 ******************************************************************************/
en_result_t Uart_Init(uint8_t u8Idx, stc_uart_config_t* pstcConfig)
{
    en_result_t enRet = Error;
    stc_uart_instance_data_t *pstcData = NULL;
    ASSERT(IS_VALID_CH(u8Idx));
    pstcData = UartGetInternDataPtr(u8Idx);
    if (NULL == pstcData)
    {
        return ErrorInvalidParameter;
    }
    if(NULL == pstcConfig)
    {
        return ErrorInvalidParameter;
    }
    enRet = Uart_SetMode(u8Idx,pstcConfig->enRunMode);

    if(NULL != pstcConfig->pstcMultiMode)
    {
        enRet = Uart_SetMultiMode(u8Idx,pstcConfig->pstcMultiMode);
    }
    if(NULL != pstcConfig->pstcIrqCb)
    {
        pstcData->stcUartInternIrqCb.pfnRxErrIrqCb = pstcConfig->pstcIrqCb->pfnRxErrIrqCb;
        pstcData->stcUartInternIrqCb.pfnRxIrqCb = pstcConfig->pstcIrqCb->pfnRxIrqCb;
        pstcData->stcUartInternIrqCb.pfnTxIrqCb = pstcConfig->pstcIrqCb->pfnTxIrqCb;
    }
    if(pstcConfig->bTouchNvic == TRUE)
    {
        UartInitNvic(u8Idx);
    }
    else
    {
        UartDeInitNvic(u8Idx);
    }
    enRet = Ok;
    return enRet;
}

static void Uart0_InitNvic(void)
{
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_SetPriority(UART0_IRQn,DDL_IRQ_LEVEL_DEFAULT);
    NVIC_EnableIRQ(UART0_IRQn);
}

static void Uart1_InitNvic(void)
{
    NVIC_ClearPendingIRQ(UART1_IRQn);
    NVIC_SetPriority(UART1_IRQn,DDL_IRQ_LEVEL_DEFAULT);
    NVIC_EnableIRQ(UART1_IRQn);
}

void Uart0_SetCallback(stc_uart_irq_cb_t *callbacks)
{
    stc_uart_instance_data_t *pstcData = &m_astcUartInstanceDataLut[0];
    pstcData->stcUartInternIrqCb.pfnRxErrIrqCb = callbacks->pfnRxErrIrqCb;
    pstcData->stcUartInternIrqCb.pfnRxIrqCb = callbacks->pfnRxIrqCb;
    pstcData->stcUartInternIrqCb.pfnTxIrqCb = callbacks->pfnTxIrqCb;
    Uart0_InitNvic();
}

void Uart1_SetCallback(stc_uart_irq_cb_t *callbacks)
{
    stc_uart_instance_data_t *pstcData = &m_astcUartInstanceDataLut[1];
    pstcData->stcUartInternIrqCb.pfnRxErrIrqCb = callbacks->pfnRxErrIrqCb;
    pstcData->stcUartInternIrqCb.pfnRxIrqCb = callbacks->pfnRxIrqCb;
    pstcData->stcUartInternIrqCb.pfnTxIrqCb = callbacks->pfnTxIrqCb;
    Uart1_InitNvic();
}

en_result_t Uart0_TxChar(uint8_t u8Data)
{
    M0P_UART0->ICR_f.TICLR = 0;
    M0P_UART0->SBUF = u8Data;

    while (TRUE != M0P_UART0->ISR_f.TI);
    M0P_UART0->ICR_f.TICLR = 0;
    return Ok;
}

en_result_t Uart1_TxChar(uint8_t u8Data)
{
    M0P_UART1->ICR_f.TICLR = 0;
    M0P_UART1->SBUF = u8Data;

    while (TRUE != M0P_UART1->ISR_f.TI);
    M0P_UART1->ICR_f.TICLR = 0;
    return Ok;
}

extern uint8_t HEX_TABLE[16];

void Uart0_TxHex(uint8_t *hex, uint8_t len)
{
    while (len--)
    {
        Uart0_TxChar(HEX_TABLE[*(hex + len) >> 4 & 0xF]);
        Uart0_TxChar(HEX_TABLE[*(hex + len) & 0xF]);
    }
}

void Uart1_TxHex(uint8_t *hex, uint8_t len)
{
    while (len--)
    {
        Uart1_TxChar(HEX_TABLE[*(hex + len) >> 4 & 0xF]);
        Uart1_TxChar(HEX_TABLE[*(hex + len) & 0xF]);
    }
}

void Uart0_TxString(char *str)
{
    while (*str) Uart0_TxChar(*str++);
}

void Uart1_TxString(char *str)
{
    while (*str) Uart1_TxChar(*str++);
}
//@} // UartGroup      
