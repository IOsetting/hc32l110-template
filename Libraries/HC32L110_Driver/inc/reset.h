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
/** \file reset.h
 **
 ** Headerfile for reset functions
 **  
 **
 ** History:
 **   - 2017-05-02   Ronnie     First Version
 **
 ******************************************************************************/

#ifndef __RESET_H__
#define __RESET_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup ResetGroup Reset (RST)
 **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/*******************************************************************************
 * Global definitions
 ******************************************************************************/


/**
 *******************************************************************************
 ** \brief 外设复位使能列表
 ** \note
 ******************************************************************************/
typedef enum
{
    ResetGpio,              ///< GPIO 复位
    ResetCrc,               ///< CRC 复位
    ResetTick,              ///< systick 复位
    ResetTrim,              ///< 时钟校准复位
    ResetRtc,               ///< RTC 复位
    ResetVc,                ///< 电压比较复位
    ResetAdc,               ///< ADC复位
    ResetPca,               ///< PCA 复位
    ResetAdcTim,            ///< ADC 复位
    ResetLpTim,             ///< 低功耗时钟复位
    ResetBaseTim,           ///< 基础时钟复位
    ResetSpi,               ///< SPI复位
    ResetI2c,               ///< I2C复位
    ResetLpUart,            ///< 低功耗串口复位
    ResetUart1,             ///< 串口1复位
    ResetUart0,             ///< 串口0复位
}en_reset_peripheral_t;



/**
 *******************************************************************************
 ** \brief 复位源显示
 **
 ** \note
 ******************************************************************************/
typedef struct
{
    uint8_t     u8Por5V     :1;         ///< 5V启动复位
    uint8_t     u8Por1_5V   :1;         ///< 1.5V启动复位
    uint8_t     u8Lvd       :1;         ///< 低电压检测复位
    uint8_t     u8Wdt       :1;         ///< 看门狗复位
    uint8_t     u8Pca       :1;         ///< PCA复位
    uint8_t     u8Lockup    :1;         ///< 系统异常复位
    uint8_t     u8Sysreq    :1;         ///< 软件复位
    uint8_t     u8RSTB      :1;         ///< RESET脚 复位
}stc_reset_cause_t;

/*******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

 
///< 获得复位源
en_result_t Reset_GetCause(stc_reset_cause_t *pstcOut);
///< 清除复位源
en_result_t Reset_Clear(stc_reset_cause_t stcval);

///< 设置复位外设
en_result_t Reset_SetPeripheralReset(en_reset_peripheral_t enPeri,boolean_t bFlag);

//@} // ResetGroup

#ifdef __cplusplus
#endif


#endif /* __RESET_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


