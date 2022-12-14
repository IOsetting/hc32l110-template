/*******************************************************************************
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
/** \file clk.h
 **
 ** Headerfile for CLK functions
 ** @link CLK Group Some description @endlink 
 **
 ** History:
 **   - 2017-05-02   Ronnie     First Version
 **
 ******************************************************************************/

#ifndef __CLK_H__
#define __CLK_H__

/*******************************************************************************
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
 ** \defgroup ClkGroup Clock (CLK)
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
#define CLK_RCH_VAL             (4*1000*1000)       ///< ???????????????????????????
#define CLK_RCL_VAL             (38400)             ///< ???????????????????????????
#define CLK_XTL_VAL             (32768)             ///< ???????????????????????????
#ifndef CLK_XTH_VAL
#define CLK_XTH_VAL             (32*1000*1000)      ///< ????????????????????????????????????
#endif
/**
 *******************************************************************************
 ** \brief ?????????????????????
 ** \note
 ******************************************************************************/
typedef enum en_clk_source
{
    ClkRCH  = 0u,               ///< Internal High Speed
    ClkXTH  = 1u,               ///< External High Speed
    ClkRCL  = 2u,               ///< Internal Low Speed
    ClkXTL  = 3u,               ///< External Low Speed
}en_clk_source_t;

/**
 *******************************************************************************
 ** \brief ??????????????????
 ******************************************************************************/
typedef enum en_clk_div
{
    ClkDiv1 = 1,                ///< ?????????
    ClkDiv2 = 2,                ///< 2 ??????
    ClkDiv4 = 4,                ///< 4 ??????
    ClkDiv8 = 8,                ///< 8 ??????
    ClkDiv16 = 16,              ///< 16 ??????
    ClkDiv32 = 32,              ///< 32 ??????
    ClkDiv64 = 64,              ///< 64 ??????
    ClkDiv128 = 128,            ///< 128 ??????
}en_clk_div_t;

/**
 *******************************************************************************
 ** \brief ???????????????
 ******************************************************************************/
typedef enum en_clk_cycle
{
    ClkCycle4,                  ///< 4 ????????????
    ClkCycle16,                 ///< 16 ????????????
    ClkCycle64,                 ///< 64 ????????????
    ClkCycle256,                ///< 256 ????????????
    ClkCycle1024,               ///< 1024 ????????????
    ClkCycle4096,               ///< 4096 ????????????
    ClkCycle16384,              ///< 16384 ????????????
}en_clk_cycle_t;

/**
 *******************************************************************************
 ** \brief Clock Frequencies
 ******************************************************************************/
typedef enum en_clk_freq
{
    ClkFreq32768,               ///< 32.8KHz
    ClkFreq38_4K,               ///< 38.4KHz
    ClkFreq4Mhz,                ///< 4MHz
    ClkFreq8Mhz,                ///< 8MHz
    ClkFreq16Mhz,               ///< 16MHz
    ClkFreq22_12Mhz,            ///< 22.12MHz
    ClkFreq24Mhz,               ///< 24MHz
}en_clk_freq_t;

/**
 *******************************************************************************
 ** \brief ????????????????????????????????????
 ******************************************************************************/
typedef enum en_clk_func
{
    ClkFuncWkupRCH,                     ///< ???????????????RCH??????
    ClkFuncXTHEn,                       ///< ????????????????????????????????????
    ClkFuncXTLEn,                       ///< ???????????????????????????????????????
    ClkFuncXTLAWSON,                    ///< ????????????????????????????????????
    ClkFuncFaultEn,                     ///< ????????????????????????
    ClkFuncRtcLPWEn,                    ///< ??????RTC???????????????
    ClkFuncLockUpEn,                    ///< ????????????????????????
    ClkFuncRstPinIOEn,                  ///< reset?????????IO
    ClkFuncSwdPinIOEn,                  ///< swd?????????IO
}en_clk_func_t;

/**
 *******************************************************************************
 ** \brief ????????????????????????????????????
 ******************************************************************************/
typedef enum en_clk_peripheral_gate
{
    ClkPeripheralUart0      = 0u,       ///< ??????0
    ClkPeripheralUart1      = 1u,       ///< ??????1
    ClkPeripheralLpUart     = 2u,       ///< ???????????????
    ClkPeripheralI2c        = 4u,       ///< I2C
    ClkPeripheralSpi        = 6u,       ///< SPI
    ClkPeripheralBaseTim    = 8u,       ///< ????????????
    ClkPeripheralLpTim      = 9u,       ///< ???????????????
    ClkPeripheralAdt        = 10u,      ///< ????????????
    ClkPeripheralPca        = 14u,      ///< ?????????????????????
    ClkPeripheralWdt        = 15u,      ///< ?????????
    ClkPeripheralAdcBgr     = 16u,      ///< ADC
    ClkPeripheralVcLvd      = 17u,      ///< ??????????????????????????????
    ClkPeripheralRtc        = 20u,      ///< RTC
    ClkPeripheralClkTrim    = 21u,      ///< ????????????
    ClkPeripheralTick       = 24u,      ///< ???????????????
    ClkPeripheralCrc        = 26u,      ///< CRC
    ClkPeripheralGpio       = 28u,      ///< GPIO
    ClkPeripheralFlash      = 31u,      ///< Flash
}en_clk_peripheral_gate_t;

/**
 *******************************************************************************
 ** \brief ????????????????????????
 ** \note ?????????????????????????????????????????????????????????
 ******************************************************************************/
typedef enum
{
    ClkDBGTim0,             ///<  ??????0
    ClkDBGTim1,             ///<  ??????1
    ClkDBGTim2,             ///<  ??????2
    ClkDBGLpTim,            ///<  ???????????????
    ClkDBGTim4,             ///<  ??????4
    ClkDBGTim5,             ///<  ??????5 
    ClkDBGTim6,             ///<  ??????6 
    ClkDBGTPca,             ///<  ?????????????????????
    ClkDBGTWdt,             ///<  ?????????
    ClkDBGTRtc,             ///<  RTC
    ClkDBGTTick,            ///<  systick
}en_clk_debug_t;

/**
 *******************************************************************************
 ** \brief Systick??????
 ** \note ??????systick???ARM???systick????????????????????????systick?????????????????????????????????
 ******************************************************************************/
typedef struct
{
    en_clk_source_t     enClk;      ///< ???????????????
                                    ///< XTL  -> XTL
                                    ///< RCL  -> 38.5k
                                    ///< RCH  -> hclk/8
                                    ///< XTH  -> XTH
    boolean_t           bNoRef;     ///< ??????????????????
                                    ///< TRUE  :  ??????????????????HCLK 
                                    ///< FALSE :  ??????enClk
    uint32_t            u32LoadVal; ///< ???????????????
}stc_clk_systickcfg_t;

#define CLK_Unlock()                do {                                            \
                                        M0P_CLOCK->SYSCTRL2 = 0x5A5A;               \
                                        M0P_CLOCK->SYSCTRL2 = 0xA5A5;               \
                                    } while(0)

#define CLK_DummyWrite()            (M0P_CLOCK->SYSCTRL0_f.RESERVED11 = 0x0)

#define CLK_EnablePeripheralClk(__PERIPHERAL_GATE_T__)      setBit(&M0P_CLOCK->PERI_CLKEN, __PERIPHERAL_GATE_T__, 1)
#define CLK_DisablePeripheralClk(__PERIPHERAL_GATE_T__)     setBit(&M0P_CLOCK->PERI_CLKEN, __PERIPHERAL_GATE_T__, 0)


/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< Clock Initialize
en_result_t Clk_Init(en_clk_freq_t clkFreq, en_clk_div_t hclkDiv, en_clk_div_t pclkDiv);
en_result_t Clk_DeInit(void);

///< ????????????????????????
en_result_t Clk_Enable(en_clk_source_t enSource, boolean_t bFlag);
en_result_t Clk_SetSource(en_clk_source_t enSource);
boolean_t Clk_GetClkRdy(en_clk_source_t enSource);
en_result_t Clk_SetXTH_StableTime(en_clk_cycle_t enCycle);
en_result_t Clk_SetRCL_StableTime(en_clk_cycle_t enCycle);
en_result_t Clk_SetXTL_StableTime(en_clk_cycle_t enCycle);

///< ???????????????
en_result_t Clk_SwitchTo(en_clk_source_t enSource);

///< ??????????????????
en_result_t Clk_SetRCHFreq(en_clk_freq_t enVal);
en_result_t Clk_SetRCLFreq(en_clk_freq_t enVal);

///< ??????????????????
en_result_t Clk_SetHClkDiv(uint8_t u8Div);
en_result_t Clk_SetPClkDiv(uint8_t u8Div);

///< ??????????????????
uint32_t Clk_GetHClkFreq(void);
uint32_t Clk_GetPClkFreq(void);

///< ????????????????????????
boolean_t Clk_GetPeripheralGate(en_clk_peripheral_gate_t enPeripheral);


///< ??????????????????
en_result_t Clk_SetFunc(en_clk_func_t enFunc, boolean_t bFlag);

///< systick ??????
en_result_t Clk_SysTickConfig(stc_clk_systickcfg_t *pstcCfg);
en_result_t Clk_DebugClk(en_clk_debug_t enPeri, boolean_t bFlag);

en_result_t Clk_SetRTCAdjustClkFreq(uint32_t u32val);

//Systick SKEW ??????
boolean_t Clk_SysTickSkewGet(void);
//Systick CALIB ??????
uint32_t Clk_SysTickStcalibGet(void);
//@} // ClkGroup

#ifdef __cplusplus
}
#endif


#endif /* __CLK_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


