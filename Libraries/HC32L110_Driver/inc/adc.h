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
/** \file adc.h
 **
 ** Header file for AD Converter functions
 ** @link ADC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l110.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup AdcGroup AD Converter (ADC)
  **
 ******************************************************************************/
 
//@{

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define ADC_SCAN_CH0_EN     (0x1u)           /*!< SCAN模式使用ADC CH0 */
#define ADC_SCAN_CH1_EN     (0x1u<<1)        /*!< SCAN模式使用ADC CH1 */
#define ADC_SCAN_CH2_EN     (0x1u<<2)        /*!< SCAN模式使用ADC CH2 */
#define ADC_SCAN_CH3_EN     (0x1u<<3)        /*!< SCAN模式使用ADC CH3 */
#define ADC_SCAN_CH4_EN     (0x1u<<4)        /*!< SCAN模式使用ADC CH4 */
#define ADC_SCAN_CH5_EN     (0x1u<<5)        /*!< SCAN模式使用ADC CH5 */
#define ADC_SCAN_CH6_EN     (0x1u<<6)        /*!< SCAN模式使用ADC CH6 */
#define ADC_SCAN_CH7_EN     (0x1u<<7)        /*!< SCAN模式使用ADC CH7 */


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

 /**
 ******************************************************************************
 ** \brief ADC采样模式
 *****************************************************************************/
typedef enum en_adc_op_mode
{
    AdcNormalMode  = 0,        /*!< 单输入通道单次采样模式 */
    AdcContMode    = 1,        /*!< 单输入通道连续采样模式 */
    AdcScanMode    = 2,        /*!< 多输入通道扫描采样模式*/

} en_adc_op_mode_t;

/**
 ******************************************************************************
 ** \brief ADC时钟选择
 *****************************************************************************/
typedef enum en_adc_clk_sel
{
    AdcClkSysTDiv1  = 0,        /*!< PCLK */
    AdcClkSysTDiv2  = 1,        /*!< 1/2 PCLK */
    AdcClkSysTDiv4  = 2,        /*!< 1/4 PCLK */
    AdcClkSysTDiv8  = 3,        /*!< 1/8 PCLK */

} en_adc_clk_sel_t;

/**
 ******************************************************************************
 ** \brief ADC参考电压
 *****************************************************************************/
typedef enum en_adc_ref_vol_sel
{
    RefVolSelInBgr1p5 = 0,        /*!<内部参考电压1.5V(SPS<=200kHz)*/
    RefVolSelInBgr2p5 = 1,        /*!<内部参考电压2.5V(avdd>3V,SPS<=200kHz)*/
    RefVolSelExtern1  = 2,        /*!<外部输入(max avdd)   P3.6*/
    RefVolSelAVDD     = 3,        /*!<AVDD*/

}en_adc_ref_vol_sel_t;

/**
 ******************************************************************************
 ** \brief ADC采样通道选择
 *****************************************************************************/
typedef enum en_adc_samp_ch_sel
{
    AdcExInputCH0    =  0,        /*!<使用通道0输入P2.4*/
    AdcExInputCH1    =  1,        /*!<使用通道1输入P2.6*/
    AdcExInputCH2    =  2,        /*!<使用通道2输入P3.2*/
    AdcExInputCH3    =  3,        /*!<使用通道3输入P3.3*/
    AdcExInputCH4    =  4,        /*!<使用通道4输入P3.4*/
    AdcExInputCH5    =  5,        /*!<使用通道5输入P3.5*/
    AdcExInputCH6    =  6,        /*!<使用通道6输入P3.6*/
    AdcExInputCH7    =  7,        /*!<使用通道7输入P0.1*/
    AdcExInputCH8    =  8,        /*!<使用通道8输入P0.2*/
    AdcAVccDiV3Input =  9,        /*!<使用1/3 AVCC(必须使用输入增益)*/
    AdcAiTsInput     =  10,       /*!<使用AI_TS(必须使用输入增益)*/
    AdcVref1P2Input  =  11,       /*!<使用Vref1P2(必须使用输入增益)*/

}en_adc_samp_ch_sel_t;

/**
 ******************************************************************************
 ** \brief ADC采样周期数选择
 *****************************************************************************/
typedef enum en_adc_samp_time_sel
{
    AdcSampTime4Clk  =  0,        /*!<4个采样时钟*/
    AdcSampTime6Clk  =  1,        /*!<6个采样时钟*/
    AdcSampTime8Clk  =  2,        /*!<8个采样时钟*/
    AdcSampTime12Clk =  3,        /*!<12个采样时钟*/

}en_adc_samp_time_sel_t;

/**
 ******************************************************************************
 ** \brief ADC周边模块反射源选择
 *****************************************************************************/
typedef enum en_adc_trig_sel
{
    AdcTrigDisable    =  0,         /*!<禁用周边模块反射源*/
    AdcTrigTimer0     =  1,         /*!<选择timer0中断源，自动触发ADC采样*/
    AdcTrigTimer1     =  2,         /*!<选择timer1中断源，自动触发ADC采样*/
    AdcTrigTimer2     =  3,         /*!<选择timer2中断源，自动触发ADC采样*/
    AdcTrigLptimer    =  4,         /*!<选择lptimer中断源，自动触发ADC采样*/
    AdcTrigTimer4     =  5,         /*!<选择timer4中断源，自动触发ADC采样*/
    AdcTrigTimer5     =  6,         /*!<选择timer5中断源，自动触发ADC采样*/
    AdcTrigTimer6     =  7,         /*!<选择timer6中断源，自动触发ADC采样*/
    AdcTrigUart0      =  8,         /*!<选择uart0中断源，自动触发ADC采样*/
    AdcTrigUart1      =  9,         /*!<选择uart1中断源，自动触发ADC采样*/
    AdcTrigLpuart     =  10,        /*!<选择lpuart中断源，自动触发ADC采样*/
    AdcTrigVC1        =  11,        /*!<选择VC1中断源，自动触发ADC采样*/
    AdcTrigVC2        =  12,        /*!<选择VC2中断源，自动触发ADC采样*/
    AdcTrigRTC        =  13,        /*!<选择RTC中断源，自动触发ADC采样*/
    AdcTrigPCA        =  14,        /*!<选择PCA中断源，自动触发ADC采样*/
    AdcTrigSPI        =  15,        /*!<选择SPI中断源，自动触发ADC采样*/
    AdcTrigP01        =  16,        /*!<选择P01中断源，自动触发ADC采样*/
    AdcTrigP02        =  17,        /*!<选择P02中断源，自动触发ADC采样*/
    AdcTrigP03        =  18,        /*!<选择P03中断源，自动触发ADC采样*/
    AdcTrigP14        =  19,        /*!<选择P14中断源，自动触发ADC采样*/
    AdcTrigP15        =  20,        /*!<选择P15中断源，自动触发ADC采样*/
    AdcTrigP23        =  21,        /*!<选择P23中断源，自动触发ADC采样*/
    AdcTrigP24        =  22,        /*!<选择P24中断源，自动触发ADC采样*/
    AdcTrigP25        =  23,        /*!<选择P25中断源，自动触发ADC采样*/
    AdcTrigP26        =  24,        /*!<选择P26中断源，自动触发ADC采样*/
    AdcTrigP27        =  25,        /*!<选择P27中断源，自动触发ADC采样*/
    AdcTrigP31        =  26,        /*!<选择P31中断源，自动触发ADC采样*/
    AdcTrigP32        =  27,        /*!<选择P32中断源，自动触发ADC采样*/
    AdcTrigP33        =  28,        /*!<选择P33中断源，自动触发ADC采样*/
    AdcTrigP34        =  29,        /*!<选择P34中断源，自动触发ADC采样*/
    AdcTrigP35        =  30,        /*!<选择P35中断源，自动触发ADC采样*/
    AdcTrigP36        =  31,        /*!<选择P36中断源，自动触发ADC采样*/

}en_adc_trig_sel_t;

/******************************************************************************
 * Extern type definitions ('typedef')                                        *
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief  ADC配置
 *****************************************************************************/
typedef struct stc_adc_cfg
{
    /*! ADC操作模式*/
    en_adc_op_mode_t enAdcOpMode;

    /*! ADC时钟选择*/
    en_adc_clk_sel_t  enAdcClkSel;

    /*! ADC采样时间*/
    en_adc_samp_time_sel_t  enAdcSampTimeSel;

    /*! ADC参考电压*/
    en_adc_ref_vol_sel_t    enAdcRefVolSel;

    /*! ADC输入增益使能*/
    boolean_t    bAdcInBufEn;

    /*!ADC区间模式上限值*/
    uint32_t    u32AdcRegHighThd;

    /*!ADC区间模式下限值*/
    uint32_t    u32AdcRegLowThd;

    /*! ADC触发0选择*/
    en_adc_trig_sel_t enAdcTrig0Sel;

    /*! ADC触发1选择*/
    en_adc_trig_sel_t enAdcTrig1Sel;

}stc_adc_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC单次采样模式配置
 *****************************************************************************/
typedef struct stc_adc_norm_cfg
{
    /*! ADC通道选择*/
    en_adc_samp_ch_sel_t    enAdcNormModeCh;
    /*! ADC结果累加使能*/
    boolean_t  bAdcResultAccEn;

}stc_adc_norm_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC单通道连续采样模式配置
 *****************************************************************************/
typedef struct stc_adc_cont_cfg
{
    /*! ADC通道选择*/
    en_adc_samp_ch_sel_t    enAdcContModeCh;
    /*! ADC采样次数*/
    uint8_t    u8AdcSampCnt;
    /*! ADC结果累加使能*/
    boolean_t  bAdcResultAccEn;

}stc_adc_cont_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC扫描采样模式配置
 *****************************************************************************/
typedef struct stc_adc_scan_cfg
{
    /*! ADC通道选择*/
    uint8_t    u8AdcScanModeCh;
    /*! ADC采样次数*/
    uint8_t    u8AdcSampCnt;

}stc_adc_scan_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC中断配置
 *****************************************************************************/
typedef struct stc_adc_irq
{
    /*!<ADC连续采样中断*/
    boolean_t  bAdcIrq;
    /*!ADC区间*/
    boolean_t  bAdcRegCmp;
    /*!ADC上超出区间*/
    boolean_t  bAdcHhtCmp;
    /*!ADC下超出区间*/
    boolean_t  bAdcLltCmp;

}stc_adc_irq_t;

/**
 ******************************************************************************
 ** \brief  ADC中断回调函数
 *****************************************************************************/
typedef struct stc_adc_irq_calbakfn_pt
{
    /*! ADC连续采样中断回调函数指针*/
    func_ptr_t  pfnAdcContIrq;
    /*! ADC区间中断回调函数指针*/
    func_ptr_t  pfnAdcRegIrq;
    /*! ADC上超出区间中断回调函数指针*/
    func_ptr_t  pfnAdcHhtIrq;
    /*! ADC下超出区间中断回调函数指针*/
    func_ptr_t  pfnAdcLltIrq;

}stc_adc_irq_calbakfn_pt_t;

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC initialization
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcConfig);
//ADC de-init
void Adc_DeInit(void);

//ADC conversion start
void Adc_Start(void);
//ADC conversion stop
void Adc_Stop(void);

//ADC conversion enable
void Adc_Enable(void);
//ADC conversion disable
void Adc_Disable(void);

//ADC normal mode configuration
en_result_t Adc_ConfigNormMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_norm_cfg_t* pstcAdcNormCfg);
//ADC continuous mode configuration
en_result_t Adc_ConfigContMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_cont_cfg_t* pstcAdcContCfg);
//ADC scan mode configuration
en_result_t Adc_ConfigScanMode(stc_adc_cfg_t* pstcAdcConfig, stc_adc_scan_cfg_t* pstcAdcScanCfg);

//ADC IRQ configuration
void Adc_ConfigIrq(stc_adc_irq_t* pstcAdcIrqCfg,
                   stc_adc_irq_calbakfn_pt_t* pstcAdcIrqCalbaks);
//ADC enable IRQ
void Adc_EnableIrq(void);
//ADC disable IRQ
void Adc_DisableIrq(void);
//ADC enable compare
void Adc_CmpCfg(stc_adc_irq_t* pstcAdcIrqCfg);
//ADC get IRQ state
void Adc_GetIrqState(stc_adc_irq_t* pstcAdcIrqState);
//ADC clear IRQ states
void Adc_ClrContIrqState(void);
void Adc_ClrRegIrqState(void);
void Adc_ClrHhtIrqState(void);
void Adc_ClrIrqLltState(void);

//查询ADC转换状态
boolean_t Adc_PollBusyState(void);
//获取采样值
en_result_t Adc_GetResult(uint16_t* pu16AdcResult);
//获取累加采样值
en_result_t Adc_GetAccResult(uint32_t* pu32AdcAccResult);
//clear ADC accumulated result
void Adc_ClrAccResult(void);
//get ADC scan channel result
en_result_t Adc_GetScanResult(uint8_t u8Channel, uint16_t* pu16AdcResult);
//获取通道8采样值
en_result_t Adc_GetCH8Result(uint16_t* pu16AdcResult);

en_result_t Adc_SetVref(en_adc_ref_vol_sel_t enAdcRefVolSel);

//@}
#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
