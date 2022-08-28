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
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED   , ARISING BY LAW OR OTHERWISE,
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
/** \file spi.h
 **
 ** Headerfile for SPI functions
 **  
 **
 ** History:
 **   - 2017-05-17  1.0  Devi     First Version
 **
 *****************************************************************************/
#ifndef __SPI_H__
#define __SPI_H__

/******************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \brief SPI 功能使能设置
 ******************************************************************************/ 
typedef enum en_spi_en
{
    SpiEnable     = 1u,  ///< SPI模块使能
    SpiDisable    = 0u,  ///< SPI模块禁止
}en_spi_en_t;

/**
 ******************************************************************************
 ** \brief SPI Mode
 ******************************************************************************/ 
typedef enum en_spi_mode
{
    SpiMaster = 1u,  // Master mode
    SpiSlave  = 0u,  // Slave mode
}en_spi_mode_t;

/**
 ******************************************************************************
 ** \brief SPI Clock Polarity
 ******************************************************************************/ 
typedef enum en_spi_cpol
{
    SpiClockPolarityLow   = 0u,  // Clock low when idle
    SpiClockPolarityHigh  = 1u,  // Clock high when idle
}en_spi_cpol_t;

/**
 ******************************************************************************
 ** \brief SPI Clock Phase
 ******************************************************************************/ 
typedef enum en_spi_cpha
{
    SpiClockPhaseFirst   = 0u,  // Transfer driven by leading edge of SCLK
    SpiClockPhaseSecond  = 1u,  // Transfer driven by trailing edge of SCLK
}en_spi_cpha_t;

/**
 ******************************************************************************
 ** \brief SPI Clock Divider
 *****************************************************************************/
typedef enum en_spi_clk_div
{
    SpiClkDiv2   = 0u,   ///<2分频       
    SpiClkDiv4   = 1u,   ///<4分频            
    SpiClkDiv8   = 2u,   ///<8分频            
    SpiClkDiv16  = 3u,   ///<16分频            
    SpiClkDiv32  = 4u,   ///<32分频            
    SpiClkDiv64  = 5u,   ///<64分频            
    SpiClkDiv128 = 6u,   ///<128分频            
}en_spi_clk_div_t;

/**
 ******************************************************************************
 ** \brief SPI 总体配置结构体
 *****************************************************************************/
typedef struct stc_spi_config
{
    boolean_t           bMasterMode;     ///< 主从模式选择
    uint8_t             u8ClkDiv;        ///< 波特率设置
    boolean_t           bCPOL;           ///< 时钟极性选择
    boolean_t           bCPHA;           ///< 时钟相位选择
    boolean_t           bIrqEn;          ///< 中断使能
    func_ptr_t          pfnIrqCb;        ///< 中断回调函数
}stc_spi_config_t;

#define SPI_SetCsLow()              (M0P_SPI->SSN = 0)
#define SPI_SetCsHigh()             (M0P_SPI->SSN = 1)
// Transfer finished flag
#define SPI_GetFlagTxFinished()     (M0P_SPI->STAT_f.SPIF)
// Write conflict flag
#define SPI_GetFlagWriteConflict()  (M0P_SPI->STAT_f.WCOL)
// Slave mode error flag
#define SPI_GetFlagSlaveError()     (M0P_SPI->STAT_f.SSERR)
// Master mode error flag
#define SPI_GetFlagMasterError()    (M0P_SPI->STAT_f.MDF)

//SPI 中断
void Spi_IRQHandler(uint8_t u8Param);
//SPI初始化函数
en_result_t Spi_Init(stc_spi_config_t* pstcSpiConfig);
//SPI关闭函数
en_result_t Spi_DeInit(void);
// SPI exchange one byte
uint8_t Spi_TxRx(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */
