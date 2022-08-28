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
/** \file bt.h
 **
 ** 基本定时器数据结构及API声明
 ** @link BT Group Some description @endlink
 **
 ** History:
 **   - 2017-05-10   Lux     V1.0
 **
 *****************************************************************************/

#ifndef __BASE_TIMER_H__
#define __BASE_TIMER_H__

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
 ** \defgroup BtGroup Base Timer (BT)
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
 ** \brief 定时器选择数据类型重定义
 *****************************************************************************/
typedef enum en_bt_unit
{
    TIM0    = 0u,           ///< Timer 0
    TIM1    = 1u,           ///< Timer 1
    TIM2    = 2u,           ///< Timer 2
}en_bt_unit_t;

/**
 ******************************************************************************
 ** \brief 极性控制数据类型重定义 (GATE_P)
 *****************************************************************************/
typedef enum en_bt_gatep
{
    BtGateEnabledHigh = 0u,            // Triggered by high voltage level
    BtGateEnabledLow  = 1u,            // Triggered by low voltage level
}en_bt_gatep_t;

/**
 ******************************************************************************
 ** \brief Timer Gate Control (GATE)
 *****************************************************************************/
typedef enum en_bt_gate
{
    BtGateDisable = 0u,            // Gate control is off
    BtGateEnable  = 1u,            // Gate control is on, timer runs when TR=1 and gate is triggered
}en_bt_gate_t;

/**
 ******************************************************************************
 ** \brief TIM 预除频选择 (PRS)
 *****************************************************************************/
typedef enum en_bt_timclkdiv
{
    BtPCLKDiv1   = 0u,           ///< Div 1
    BtPCLKDiv2   = 1u,           ///< Div 2
    BtPCLKDiv4   = 2u,           ///< Div 4
    BtPCLKDiv8   = 3u,           ///< Div 8
    BtPCLKDiv16  = 4u,           ///< Div 16
    BtPCLKDiv32  = 5u,           ///< Div 32
    BtPCLKDiv64  = 6u,           ///< Div 64
    BtPCLKDiv256 = 7u,           ///< Div 256
}en_bt_timclkdiv_t;

/**
 ******************************************************************************
 ** \brief Reverse output (TOG_EN)
 *****************************************************************************/
typedef enum en_bt_toggle
{
    BtTogDisable = 0u,            // TOG,TOGN output same level
    BtTogEnable  = 1u,            // TOG,TOGN output reversed level
}en_bt_toggle_t;

/**
 ******************************************************************************
 ** \brief Timer or counter function (CT)
 *****************************************************************************/
typedef enum en_bt_function
{
    BtTimer   = 0u,            // Timer function
    BtCounter = 1u,            // Counter function
}en_bt_function_t;

/**
 ******************************************************************************
 ** \brief Timer Mode(MD)
 *****************************************************************************/
typedef enum en_bt_mode
{
    BtMode1  = 0u,         // 32-bit timer/counter, restart from 0 when overflow
    BtMode2  = 1u,         // 16-bit auto-reload timer/counter
}en_bt_mode_t;

/**
 ******************************************************************************
 ** \brief 定时器运行控制数据类型重定义 (TR)
 *****************************************************************************/
typedef enum en_bt_start
{
    BtTRDisable = 0u,            ///< 停止
    BtTREnable  = 1u,            ///< 运行
}en_bt_start_t;

/**
 ******************************************************************************
 ** \brief Timer 配置结构体定义 
 *****************************************************************************/
typedef struct stc_bt_config
{
    en_bt_gatep_t     enGateP;          ///< 门控极性控制
    en_bt_gate_t      enGate;           ///< 门控使能
    en_bt_timclkdiv_t enPRS;            ///< 预除频配置
    en_bt_toggle_t    enTog;            ///< 反转输出使能
    en_bt_function_t  enCT;             ///< 定时/计数功能选择
    en_bt_mode_t      enMD;             ///< 计数模式配置
    
    func_ptr_t        pfnTim0Cb;        ///< Timer0中断服务回调函数[void function(void)]
    func_ptr_t        pfnTim1Cb;        ///< Timer1中断服务回调函数[void function(void)]
    func_ptr_t        pfnTim2Cb;        ///< Timer2中断服务回调函数[void function(void)]
}stc_bt_config_t;


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//中断相关函数 
//中断标志获取
boolean_t Bt_GetIntFlag(en_bt_unit_t enUnit);
//中断标志清除
en_result_t Bt_ClearIntFlag(en_bt_unit_t enUnit);
//中断使能/禁止
en_result_t Bt_EnableIrq (en_bt_unit_t enUnit);
en_result_t Bt_DisableIrq(en_bt_unit_t enUnit);

//初始化及相关功能操作
//timer配置及初始化
en_result_t Bt_Init(en_bt_unit_t enUnit, stc_bt_config_t* pstcConfig);
//Lptimer 启动/停止
en_result_t Bt_Run(en_bt_unit_t enUnit);
en_result_t Bt_Stop(en_bt_unit_t enUnit);
//重载值设置
en_result_t Bt_ARRSet(en_bt_unit_t enUnit, uint16_t u16Data);
//16位计数值设置/获取
en_result_t Bt_Cnt16Set(en_bt_unit_t enUnit, uint16_t u16Data);
uint16_t Bt_Cnt16Get(en_bt_unit_t enUnit);
//32位计数值设置/获取
en_result_t Bt_Cnt32Set(en_bt_unit_t enUnit, uint32_t u32Data);
uint32_t Bt_Cnt32Get(en_bt_unit_t enUnit); 

//@} // BtGroup

#ifdef __cplusplus
#endif


#endif /* __BASE_TIMER_H__ */
