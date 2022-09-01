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
/******************************************************************************/
/** \file interrupts_hc32l110.c
 **
 ** Interrupt management
 ** @link Driver Group Some description @endlink
 **
 **   - 2017-04-29  1.0  Ronnie     First version.
 **
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

__attribute__((weak)) void PORT0_IRQHandler(void);
__attribute__((weak)) void PORT1_IRQHandler(void);
__attribute__((weak)) void PORT2_IRQHandler(void);
__attribute__((weak)) void PORT3_IRQHandler(void);
__attribute__((weak)) void UART0_IRQHandler(void);
__attribute__((weak)) void UART1_IRQHandler(void);
__attribute__((weak)) void LPUART_IRQHandler(void);

__attribute__((weak)) void Spi_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void I2c_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void BaseTim0_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void BaseTim1_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void BaseTim2_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void Adt_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void LpTim_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void Pca_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void Wdt_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void Vc_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void Rtc_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void Adc_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void Lvd_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void EfRam_IRQHandler(uint8_t u8Param);
__attribute__((weak)) void ClkTrim_IRQHandler(uint8_t u8Param);

/**
 *******************************************************************************
 ** \brief NVIC 中断使能
 **
 ** \param [in]  u32Irq         中断号
 ** \param [in]  u8Level        中断优先级
 ** \param [in]  bEn            中断开关
 ** \retval    Ok       设置成功
 **            其他值   设置失败
 ******************************************************************************/
void EnableNvic(uint32_t u32Irq,uint8_t u8Level,boolean_t bEn)
{
    IRQn_Type enIrq = (IRQn_Type)u32Irq;

    NVIC_ClearPendingIRQ(enIrq);
    NVIC_SetPriority(enIrq, u8Level);
    if (TRUE == bEn)
    {
        NVIC_EnableIRQ(enIrq);
    }else{
        NVIC_DisableIRQ(enIrq);
    }
}

/**
 *******************************************************************************
 ** \brief NVIC hardware fault 中断实现
 **        用于单步调试功能
 **
 ** \retval
 ******************************************************************************/
void HardFault_Handler(void)
{
    volatile int a = 0;

    while( 0 == a)
    {
        ;
    }
}

/**
 *******************************************************************************
 ** \brief GPIO SPI 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void SPI_IRQHandler(void)
{
    Spi_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO I2C 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void I2C_IRQHandler(void)
{
    I2c_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief Base Timer0 Interrupt Handler
 ** 
 ** \retval
 ******************************************************************************/
void TIM0_IRQHandler(void)
{
    BaseTim0_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief Base Timer1 Interrupt Handler
 ** 
 ** \retval
 ******************************************************************************/
void TIM1_IRQHandler(void)
{
    BaseTim1_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief Base Timer2 Interrupt Handler
 ** 
 ** \retval
 ******************************************************************************/
void TIM2_IRQHandler(void)
{
    BaseTim2_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO 低功耗时钟 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void LPTIM_IRQHandler(void)
{
    LpTim_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO 高级时钟4 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM4_IRQHandler(void)
{
    Adt_IRQHandler(4);
}

/**
 *******************************************************************************
 ** \brief GPIO 高级时钟5 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM5_IRQHandler(void)
{
    Adt_IRQHandler(5);
}

/**
 *******************************************************************************
 ** \brief GPIO 高级时钟6 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void TIM6_IRQHandler(void)
{
    Adt_IRQHandler(6);
}

/**
 *******************************************************************************
 ** \brief GPIO PCA 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void PCA_IRQHandler(void)
{
    Pca_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO WDT 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void WDT_IRQHandler(void)
{
    Wdt_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO RTC 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void RTC_IRQHandler(void)
{
    Rtc_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO ADC 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void ADC_IRQHandler(void)
{
    Adc_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO 电压比较0 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void VC0_IRQHandler(void)
{
    Vc_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO 电压比较1 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void VC1_IRQHandler(void)
{
    Vc_IRQHandler(1);
}

/**
 *******************************************************************************
 ** \brief GPIO 低电压检测 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void LVD_IRQHandler(void)
{
    Lvd_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO RAM 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void EF_RAM_IRQHandler(void)
{
    EfRam_IRQHandler(0);
}

/**
 *******************************************************************************
 ** \brief GPIO 时钟校准 中断处理函数
 ** 
 ** \retval
 ******************************************************************************/
void CLKTRIM_IRQHandler(void)
{
    ClkTrim_IRQHandler(0);
}



/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
