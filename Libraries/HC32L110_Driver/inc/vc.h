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
/** \file vc.h
 **
 ** Headerfile for Voltage Comparator functions
 ** @link VC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

#ifndef __VC_H__
#define __VC_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup VcGroup Voltage Comparator (VC)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief VC通道
 *****************************************************************************/
typedef enum en_vc_channel
{
    VcChannel0,                 ///< 通道0
    VcChannel1,                 ///< 通道1
}en_vc_channel_t;


/**
 ******************************************************************************
 ** \brief VC迟滞
 *****************************************************************************/
typedef enum en_vc_cmp_delay
{
    VcDelayoff,             ///< 迟滞关闭
    VcDelay10mv,            ///< 迟滞10mv
    VcDelay20mv,            ///< 迟滞20mv
    VcDelay30mv,            ///< 迟滞30mv
}en_vc_cmp_delay_t;

/**
 ******************************************************************************
 ** \brief VC偏置电流
 *****************************************************************************/
typedef enum en_vc_bias_current
{
    VcBias300na,            ///< 偏置电流300na
    VcBias1200na,           ///< 偏置电流1.2ua
    VcBias10ua,             ///< 偏置电流10ua
    VcBias20ua,             ///< 偏置电流20ua
}en_vc_bias_current_t;

/**
 ******************************************************************************
 ** \brief VC输出滤波时间
 *****************************************************************************/
typedef enum en_vc_resp_filter
{
    VcFilter7us,            ///< 输出滤波时间7us
    VcFilter14us,           ///< 输出滤波时间14us
    VcFilter28us,           ///< 输出滤波时间28us
    VcFilter112us,          ///< 输出滤波时间112us
    VcFilter450us,          ///< 输出滤波时间450us
    VcFilter1800us,         ///< 输出滤波时间1.8ms
    VcFilter7200us,         ///< 输出滤波时间7.2ms
    VcFilter28800us,        ///< 输出滤波时间28.8ms
}en_vc_resp_filter_t;

/**
 ******************************************************************************
 ** \brief VC P端输入
 *****************************************************************************/
typedef enum en_vc_input_p_src
{
    VcInPCh0,                ///< 输入通道0 P2.3
    VcInPCh1,                ///< 输入通道1 P2.5
    VcInPCh2,                ///< 输入通道2 P3.2
    VcInPCh3,                ///< 输入通道3 P3.3
    VcInPCh4,                ///< 输入通道4 P3.4
    VcInPCh5,                ///< 输入通道5 P3.5
    VcInPCh6,                ///< 输入通道6 P3.6
    VcInPCh7,                ///< 输入通道7 P0.1
}en_vc_input_p_src_t;

/**
 ******************************************************************************
 ** \brief VC N端输入
 *****************************************************************************/
typedef enum en_vc_input_n_src
{
    VcInNCh0,         ///< 输入通道0 P2.3
    VcInNCh1,         ///< 输入通道1 P2.5
    VcInNCh2,         ///< 输入通道2 P3.2
    VcInNCh3,         ///< 输入通道3 P3.3
    VcInNCh4,         ///< 输入通道4 P3.4
    VcInNCh5,         ///< 输入通道5 P3.5
    VcInNCh6,         ///< 输入通道6 P3.6
    VcInNCh7,         ///< 输入通道7 P0.1
    ResDivOut,        ///< Vcc分压
    AiTs,             ///< 温度传感器
    AiBg1p2,          ///< BGR 1.2V
    AiVcRef2p5,       ///< REF 2.5V
    AiLdo,            ///< LDO
}en_vc_input_n_src_t;

/**
 ******************************************************************************
 ** \brief VC中断触发方式
 *****************************************************************************/
typedef enum en_vc_irq_sel
{
    VcIrqRise,            ///< 上升沿触发
    VcIrqFall,            ///< 下降沿触发
    VcIrqHigh,            ///< 高电平触发
    VcIrqNone,            ///< 无中断
}en_vc_irq_sel_t;

/**
 ******************************************************************************
 ** \brief VC状态
 *****************************************************************************/
typedef enum en_vc_stat
{
    VcCmpResult,                ///< VC比较输出结果
    VcIntrResult,               ///< VC中断状态
}en_vc_stat_t;

/**
 ******************************************************************************
 ** \brief VC输出配置
 *****************************************************************************/
typedef enum en_vc_output_config
{
    VcOutInvTimer,              ///< 结果输出负向到各Timer0,1,2,3
    VcOutTm0Gate,               ///< 结果使能输出到TM0 Gate
    VcOutTm1Gate,               ///< 结果使能输出到TM1 Gate
    VcOutTm2Gate,               ///< 结果使能输出到TM2 Gate
    VcOutTm3Gate,               ///< 结果使能输出到LPTIMER3 Gate
    VcOutTm3ExtClk,             ///< 结果使能输出到LPTIMER 外部时钟
    VcOutInvPca,                ///< 结果输出负向到PCA
    VcOutPcaCap0,               ///< 结果使能输出到PCA 捕获模式0
    VcOutPcaExtClk,             ///< 结果使能输出到PCA 外部时钟
    VcOutInvTm4,                ///< 结果输出负向到Timer4
    VcOutTm4,                   ///< 结果使能输出到TM4 捕获模式
    VcOutInvTm5,                ///< 结果输出负向到Timer5
    VcOutTm5,                   ///< 结果使能输出到TM5 捕获模式
    VcOutInvTm6,                ///< 结果输出负向到Timer6
    VcOutTm6,                   ///< 结果使能输出到TM6 捕获模式
    VcOutBrake,                 ///< 刹车控制
    VcOutDisable,               ///< 结果输出除能
}en_vc_output_config_t;

/**
 ******************************************************************************
 ** \brief VC DIV参考电压Vref选择
 *****************************************************************************/
typedef enum en_vc_div_vref
{
    VcDivVrefAvcc,              ///< AVCC
    VcDivVrefAdc,               ///< ADC_CR0 SREF选择参考电压
}en_vc_div_vref_t;

/**
 ******************************************************************************
 ** \brief VC模块配置
 *****************************************************************************/
typedef struct stc_vc_general_config
{
    boolean_t           bDivEn;       ///< 使能/除能 6-bit VCC divider
    uint8_t             u8DivVal;     ///< 6-bit VCC divider设置值
    en_vc_div_vref_t    enDivVref;    ///< 6-bit VCC divider输入参考电压选择
}stc_vc_general_config_t;

/**
 ******************************************************************************
 ** \brief VC通道配置
 *****************************************************************************/
typedef struct stc_vc_channel_config
{
    en_vc_channel_t         enVcChannel;        ///< VC通道选择
    en_vc_cmp_delay_t       enVcCmpDly;         ///< VC迟滞
    en_vc_bias_current_t    enVcBiasCurrent;    ///< VC偏转电流
    en_vc_resp_filter_t     enVcFilterTime;     ///< 输出滤波时间
    en_vc_input_p_src_t     enVcInPin_P;        ///< P端输入
    en_vc_input_n_src_t     enVcInPin_N;        ///< N端输入
    en_vc_output_config_t   enVcOutConfig;      ///< 输出配置
    en_vc_irq_sel_t         enVcIrqSel;         ///< 中断触发方式
    func_ptr_t              pfnAnalogCmpCb;     ///< 中断回调函数
}stc_vc_channel_config_t;

/******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//get stat
boolean_t Vc_GetStat(en_vc_channel_t enChannel, en_vc_stat_t enStat);
//clear stat
void Vc_ClearIrq(en_vc_channel_t enChannel);

//irq enable/disable
en_result_t Vc_EnableIrq(en_vc_channel_t enChannel);
en_result_t Vc_DisableIrq(en_vc_channel_t enChannel);
en_result_t Vc_ConfigIrq(en_vc_channel_t enChannel, en_vc_irq_sel_t enSel);

//VC init/deinit
en_result_t Vc_GeneralInit(stc_vc_general_config_t *pstcGeneralConfig);
void Vc_GeneralDeInit(void);
en_result_t Vc_ChannelInit(en_vc_channel_t enChannel,
                            stc_vc_channel_config_t *pstcChannelConfig);
en_result_t Vc_ChannelDeInit(en_vc_channel_t enChannel);

//VC function enable/disable
en_result_t Vc_EnableChannel(en_vc_channel_t enChannel);
en_result_t Vc_DisableChannel(en_vc_channel_t enChannel);

//VC filter enable/disable
en_result_t Vc_EnableFilter(en_vc_channel_t enChannel);
en_result_t Vc_DisableFilter(en_vc_channel_t enChannel);

//@} // VcGroup

#ifdef __cplusplus
}
#endif

#endif /* __VC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

