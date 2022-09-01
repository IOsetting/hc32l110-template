/******************************************************************************
* Copyright (C) 2016, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file spi.c
 **
 ** SPI driver API.
 ** @link Driver Group Some description @endlink
 **
 **   - 2017-05-17  1.0  Devi First version for Device Driver Library of
 **                      Module.
 **
 *****************************************************************************/

/******************************************************************************
 * Include files
 *****************************************************************************/
#include "spi.h"

/**
 ******************************************************************************
 ** \addtogroup SpiGroup
 *****************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 *****************************************************************************/

#define IS_VALID_STAT(x)            (   SpiIf == (x)||\
                                        SpiWcol == (x)||\
                                        SpiSserr == (x)||\
                                        SpiMdf == (x) )


/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/

/******************************************************************************/
/* Local variable prototypes ('static')                                       */
/******************************************************************************/
static func_ptr_t pfnSpiCallback = NULL; ///< callback function pointer for SPI Irq
/**
 ******************************************************************************
 ** \brief  SPI 中断处理函数
 **
 ** \param [in] 无
 **
 ** \retval 无
 ** 
 ******************************************************************************/
void SPI_IRQHandler(void)
{
    pfnSpiCallback(); 
}

/**
 ******************************************************************************
 ** \brief  SPI 总体初始化函数
 **
 ** \param [in] 
            pstcSpiConfig初始化结构
 **
 ** \retval Ok初始化成功
 ** \retval ErrorInvalidParameter 初始化错误
 ******************************************************************************/
en_result_t Spi_Init(stc_spi_config_t *pstcSpiConfig)
{
    ASSERT(NULL != pstcSpiConfig);

    M0P_SPI->CR = 0x00;
    
    M0P_SPI->CR_f.MSTR = pstcSpiConfig->bMasterMode;
    M0P_SPI->CR_f.CPOL = pstcSpiConfig->bCPOL;
    M0P_SPI->CR_f.CPHA = pstcSpiConfig->bCPHA;
    if(pstcSpiConfig->u8ClkDiv > SpiClkDiv16)
    {
        M0P_SPI->CR_f.SPR2 = 1;      
    }
    M0P_SPI->CR |= (pstcSpiConfig->u8ClkDiv & 0x03u);    
    
    M0P_SPI->STAT = 0x00;
   
    M0P_SPI->CR_f.SPEN = TRUE;
    if (TRUE == pstcSpiConfig->bIrqEn)
    {
        EnableNvic(SPI_IRQn,DDL_IRQ_LEVEL_DEFAULT,TRUE);
    }
    else
    {
        EnableNvic(SPI_IRQn,DDL_IRQ_LEVEL_DEFAULT,FALSE);
    }
    if(NULL != pstcSpiConfig->pfnIrqCb)
    {
        pfnSpiCallback = pstcSpiConfig->pfnIrqCb;
    }
    return Ok;
}

/**
 ******************************************************************************
 ** \brief  SPI 禁止函数
 **
 ** \param [in] 无
 **
 ** \retval Ok禁止设置成功
 ** 
 ******************************************************************************/
en_result_t Spi_DeInit(void)
{
    M0P_SPI->DATA  = 0x00;   
    M0P_SPI->STAT  = 0x00;
    M0P_SPI->CR  = 0x00;
    pfnSpiCallback  = NULL;
    EnableNvic(SPI_IRQn,DDL_IRQ_LEVEL_DEFAULT,FALSE);
    return Ok;
}

uint8_t Spi_TxRx(uint8_t data)
{
    uint16_t timeout = 1000;
    M0P_SPI->DATA = data;
    while(!SPI_GetFlagTxFinished() && timeout--);
    return M0P_SPI->DATA;
}
