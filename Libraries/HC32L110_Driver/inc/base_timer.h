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
}stc_bt_config_t;

#define BASE_TIM0_GetIntFlag()          (M0P_BT0->IFR_f.TF)
#define BASE_TIM1_GetIntFlag()          (M0P_BT1->IFR_f.TF)
#define BASE_TIM2_GetIntFlag()          (M0P_BT2->IFR_f.TF)

#define BASE_TIM0_ClearIntFlag()        (M0P_BT0->ICLR_f.TFC = 0)
#define BASE_TIM1_ClearIntFlag()        (M0P_BT1->ICLR_f.TFC = 0)
#define BASE_TIM2_ClearIntFlag()        (M0P_BT2->ICLR_f.TFC = 0)

#define BASE_TIM0_EnableIrq()           (M0P_BT0->CR_f.IE = 1)
#define BASE_TIM1_EnableIrq()           (M0P_BT1->CR_f.IE = 1)
#define BASE_TIM2_EnableIrq()           (M0P_BT2->CR_f.IE = 1)

#define BASE_TIM0_DisableIrq()          (M0P_BT0->CR_f.IE = 0)
#define BASE_TIM1_DisableIrq()          (M0P_BT1->CR_f.IE = 0)
#define BASE_TIM2_DisableIrq()          (M0P_BT2->CR_f.IE = 0)

#define BASE_TIM0_SetARR(__U16_DATA__)  (M0P_BT0->ARR_f.ARR = __U16_DATA__)
#define BASE_TIM1_SetARR(__U16_DATA__)  (M0P_BT1->ARR_f.ARR = __U16_DATA__)
#define BASE_TIM2_SetARR(__U16_DATA__)  (M0P_BT2->ARR_f.ARR = __U16_DATA__)

#define BASE_TIM0_GetARR()              (M0P_BT0->ARR_f.ARR)
#define BASE_TIM1_GetARR()              (M0P_BT1->ARR_f.ARR)
#define BASE_TIM2_GetARR()              (M0P_BT2->ARR_f.ARR)

#define BASE_TIM0_SetCounter16(__U16_DATA__)    (M0P_BT0->CNT_f.CNT = __U16_DATA__)
#define BASE_TIM1_SetCounter16(__U16_DATA__)    (M0P_BT1->CNT_f.CNT = __U16_DATA__)
#define BASE_TIM2_SetCounter16(__U16_DATA__)    (M0P_BT2->CNT_f.CNT = __U16_DATA__)

#define BASE_TIM0_GetCounter16()        (M0P_BT0->CNT_f.CNT)
#define BASE_TIM1_GetCounter16()        (M0P_BT1->CNT_f.CNT)
#define BASE_TIM2_GetCounter16()        (M0P_BT2->CNT_f.CNT)

#define BASE_TIM0_SetCounter32(__U32_DATA__)    (M0P_BT0->CNT32_f.CNT32 = __U32_DATA__)
#define BASE_TIM1_SetCounter32(__U32_DATA__)    (M0P_BT1->CNT32_f.CNT32 = __U32_DATA__)
#define BASE_TIM2_SetCounter32(__U32_DATA__)    (M0P_BT2->CNT32_f.CNT32 = __U32_DATA__)

#define BASE_TIM0_GetCounter32()        (M0P_BT0->CNT32_f.CNT32)
#define BASE_TIM1_GetCounter32()        (M0P_BT1->CNT32_f.CNT32)
#define BASE_TIM2_GetCounter32()        (M0P_BT2->CNT32_f.CNT32)

#define BASE_TIM0_SetFunction(__FUNC__) (M0P_BT0->CR_f.TR = __FUNC__)
#define BASE_TIM1_SetFunction(__FUNC__) (M0P_BT1->CR_f.TR = __FUNC__)
#define BASE_TIM2_SetFunction(__FUNC__) (M0P_BT2->CR_f.TR = __FUNC__)
#define BASE_TIM0_SetMode(__MODE__)     (M0P_BT0->CR_f.MD = __MODE__)
#define BASE_TIM1_SetMode(__MODE__)     (M0P_BT1->CR_f.MD = __MODE__)
#define BASE_TIM2_SetMode(__MODE__)     (M0P_BT2->CR_f.MD = __MODE__)
#define BASE_TIM0_Run()                 (M0P_BT0->CR_f.TR = 1)
#define BASE_TIM1_Run()                 (M0P_BT1->CR_f.TR = 1)
#define BASE_TIM2_Run()                 (M0P_BT2->CR_f.TR = 1)
#define BASE_TIM0_Stop()                (M0P_BT0->CR_f.TR = 0)
#define BASE_TIM1_Stop()                (M0P_BT1->CR_f.TR = 0)
#define BASE_TIM2_Stop()                (M0P_BT2->CR_f.TR = 0)

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
void BaseTim0_Init(stc_bt_config_t* baseTimerConfig);
void BaseTim1_Init(stc_bt_config_t* baseTimerConfig);
void BaseTim2_Init(stc_bt_config_t* baseTimerConfig);

#ifdef __cplusplus
}
#endif


#endif /* __BASE_TIMER_H__ */
