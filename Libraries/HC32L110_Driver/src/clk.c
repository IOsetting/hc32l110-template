/******************************************************************************
*Copyright(C)2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd("HDSC").
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

/** \file clk.c
 **
 ** Common API of clk.
 ** @link clkGroup Some description @endlink
 **
 **   - 2017-05-04
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "clk.h"

/**
 *******************************************************************************
 ** \addtogroup ClkGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CLK_TIMEOUT             (1000000u)

#define IS_VALID_SRC(x)         (   ClkRCH == (x)||\
                                    ClkXTH == (x)||\
                                    ClkRCL == (x)||\
                                    ClkXTL == (x) )


#define IS_VALID_FUNC(x)        (   ClkFuncWkupRCH == (x)||\
                                    ClkFuncXTHEn == (x)||\
                                    ClkFuncXTLEn == (x)||\
                                    ClkFuncXTLAWSON == (x)||\
                                    ClkFuncFaultEn == (x)||\
                                    ClkFuncRtcLPWEn == (x)||\
                                    ClkFuncLockUpEn == (x)||\
                                    ClkFuncRstPinIOEn == (x)||\
                                    ClkFuncSwdPinIOEn == (x) )

#define RCH_CR_TRIM_24M_VAL         (*((volatile uint16_t*) (0x00100C00ul)))
#define RCH_CR_TRIM_22_12M_VAL      (*((volatile uint16_t*) (0x00100C02ul)))
#define RCH_CR_TRIM_16M_VAL         (*((volatile uint16_t*) (0x00100C04ul)))
#define RCH_CR_TRIM_8M_VAL          (*((volatile uint16_t*) (0x00100C06ul)))
#define RCH_CR_TRIM_4M_VAL          (*((volatile uint16_t*) (0x00100C08ul)))

#define RCL_CR_TRIM_38_4K_VAL       (*((volatile uint16_t*) (0x00100C20ul)))
#define RCL_CR_TRIM_32_8K_VAL       (*((volatile uint16_t*) (0x00100C22ul)))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern uint32_t SystemCoreClock;

/**
 *******************************************************************************
 ** \brief 时钟功能设定
 ** \param [in]  enFunc     功能枚举类型
 ** \param [in]  bFlag      开关
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetFunc(en_clk_func_t enFunc, boolean_t bFlag)
{
    en_result_t enRet = Ok;

    CLK_Unlock();
    bFlag = !!bFlag;

    switch (enFunc)
    {
        case ClkFuncWkupRCH:
            M0P_CLOCK->SYSCTRL0_f.WAKEUP_BYRCH = bFlag;
            break;
        case ClkFuncXTHEn:
            M0P_CLOCK->SYSCTRL1_f.EXTH_EN = bFlag;
            break;
        case ClkFuncXTLEn:
            M0P_CLOCK->SYSCTRL1_f.EXTL_EN = bFlag;
            break;
        case ClkFuncXTLAWSON:
            M0P_CLOCK->SYSCTRL1_f.XTL_ALWAYSON = bFlag;
            break;
        case ClkFuncFaultEn:
            M0P_CLOCK->SYSCTRL1_f.CLOCK_FT_EN = bFlag;
            break;
        case ClkFuncRtcLPWEn:
            M0P_CLOCK->SYSCTRL1_f.RTC_LPW = bFlag;
            break;
        case ClkFuncLockUpEn:
            M0P_CLOCK->SYSCTRL1_f.LOCK_EN = bFlag;
            break;
        case ClkFuncRstPinIOEn:
            M0P_CLOCK->SYSCTRL1_f.RES_UIO = bFlag;
            break;
        case ClkFuncSwdPinIOEn:
            M0P_CLOCK->SYSCTRL1_f.SWD_UIO = bFlag;
            break;
        default:
            CLK_DummyWrite();
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}


/**
 *******************************************************************************
 ** \brief 时钟源切换
 ** \param [in]  enSource   新时钟源
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SwitchTo(en_clk_source_t enSource)
{
    en_clk_source_t ClkOld;
    en_clk_source_t ClkNew = enSource;


    ClkOld = (en_clk_source_t)M0P_CLOCK->SYSCTRL0_f.CLK_SW4_SEL;
    //set wait
    switch (ClkNew)
    {
        case ClkRCH:
            break;
        case ClkXTH:
            Clk_SetXTH_StableTime(ClkCycle16384);
            break;
        case ClkRCL:
            Clk_SetRCL_StableTime(ClkCycle256);
            break;
        case ClkXTL:
            Clk_SetXTL_StableTime(ClkCycle4096);
            break;
        default:
            return ErrorInvalidParameter;
    }

    //如果当前时钟或目标时钟有一个大于24MHz,则开启FLASH读等待周期
    //add flash wait
    M0P_FLASH->BYPASS = 0x5A5A;
    M0P_FLASH->BYPASS = 0xA5A5;
    if (((ClkXTH == ClkNew) || (ClkXTH == ClkOld)) && (CLK_XTH_VAL > (24 * 1000 * 1000)))
    {
        M0P_FLASH->CR_f.WAIT = TRUE;
    }

    Clk_Enable(ClkNew, TRUE);

    while (FALSE == Clk_GetClkRdy(ClkNew))
    {
        ;
    }

    //switch
    Clk_SetSource(ClkNew);

    //close old
    Clk_Enable(ClkOld, FALSE);

    // 如果当前时钟非外部高速（即不大于24MHz）则不增加读等待周期
    if(ClkXTH != ClkNew)
    {
        M0P_FLASH->CR_f.WAIT = FALSE;
    }

    SystemCoreClockUpdate();

    return Ok;
}


/**
 *******************************************************************************
 ** \brief Get System Clock(HCLK) Frequency
 ** \param [in]     
 ** \retval      uint32_t         HCLK Frequency
 **
 ******************************************************************************/
uint32_t Clk_GetHClkFreq(void)
{
    uint32_t u32Val = 0;
    uint16_t u16TrimVal22_12 = 0;
    const uint32_t u32lcr_tbl[] = {32768, 38400};
    const uint32_t u32hcr_tbl[] = {4000000UL, 8000000UL, 16000000UL, 24000000UL};
    en_clk_source_t enSrc;

    //1. get current input source
    enSrc = (en_clk_source_t)M0P_CLOCK->SYSCTRL0_f.CLK_SW4_SEL;

    switch (enSrc)
    {
        case ClkRCH:
            u32Val = u32hcr_tbl[(M0P_CLOCK->RCH_CR_f.TRIM & 0x600U) >> 9u];
            if(24000000u == u32Val)
			{
                u16TrimVal22_12 = RCH_CR_TRIM_22_12M_VAL;
				if(u16TrimVal22_12 == M0P_CLOCK->RCH_CR_f.TRIM)
				{
					u32Val = 22120000u;
				}
			}
            break;
        case ClkRCL:
            u32Val = u32lcr_tbl[(M0P_CLOCK->RCL_CR_f.TRIM & 0x200U) >> 9u];
            break;
        case ClkXTH:
            u32Val = CLK_XTH_VAL;
            break;
        case ClkXTL:
            u32Val = CLK_XTL_VAL;
            break;
        default:
            u32Val = 0u;
            break;
    }

    u32Val = u32Val >> M0P_CLOCK->SYSCTRL0_f.HCLK_PRS;

    return u32Val;
}

/**
 *******************************************************************************
 ** \brief Get Peripheral Clock (PCLK) Frequency
 ** \param [in]     
 ** \retval      uint32_t         PCLK Frequency
 **
 ******************************************************************************/
uint32_t Clk_GetPClkFreq(void)
{
    uint32_t u32Val = 0;

    u32Val = Clk_GetHClkFreq();
    u32Val = u32Val >> M0P_CLOCK->SYSCTRL0_f.PCLK_PRS;

    return u32Val;
}

/**
 * @brief Switch clock speed and set hclk pclk divs
 * 
 * @param clkFreq 
 * @param hclkDiv 
 * @param pclkDiv 
 * @return en_result_t 
 */
en_result_t Clk_Init(en_clk_freq_t clkFreq, en_clk_div_t hclkDiv, en_clk_div_t pclkDiv)
{
    ASSERT(hclkDiv <= ClkDiv128);
    ASSERT(pclkDiv <= ClkDiv8);
    /**
     * Switch clock speed.
     * - When power on, default clock source is internal high speed RC clock at 4MHz
     * - Sugguested in User Manual
     *   - option 1: change the frequency step by step without changing the clock source
     *   - option 2: switch to low speed clock source, change the frequency, then switch back
     */
    Clk_SwitchTo(ClkRCL); // Switch to internal low speed clock source
    Clk_SetRCHFreq(clkFreq);
    Clk_SwitchTo(ClkRCH);
    Clk_SetHClkDiv(ClkDiv1);
    Clk_SetPClkDiv(ClkDiv1);
    return Ok;
}

/**
 *******************************************************************************
 ** \brief 时钟去初始化函数
 ** \param [in]  
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_DeInit(void)
{
    //set clock to HCR 4Mhz
    Clk_SetRCHFreq(ClkFreq4Mhz);
    Clk_SwitchTo(ClkRCH);    
    Clk_SetHClkDiv(ClkDiv1);
    Clk_SetPClkDiv(ClkDiv1);
    return Ok;
}


/**
 *******************************************************************************
 ** \brief 时钟源设定
 ** \note  需配合其他操作,生效设定
 ** \param [in]  enSource   目标时钟源
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetSource(en_clk_source_t enSource)
{
    en_result_t enRet = Ok;

    CLK_Unlock();

    switch (enSource)
    {
        case ClkRCH:
        case ClkRCL:
        case ClkXTH:
        case ClkXTL:
            M0P_CLOCK->SYSCTRL0_f.CLK_SW4_SEL = enSource;
            break;
        default:
            CLK_DummyWrite();
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 获得时钟源稳定标志
 ** \param [in]  enSource   目标时钟源
 ** \retval      TRUE       稳定
 **              FALSE      未稳定
 ******************************************************************************/
boolean_t Clk_GetClkRdy(en_clk_source_t enSource)
{
    boolean_t bFlag = FALSE;

    switch (enSource)
    {
        case ClkRCH:
            bFlag = M0P_CLOCK->RCH_CR_f.STABLE;
            break;
        case ClkXTH:
            bFlag = M0P_CLOCK->XTH_CR_f.STABLE;
            break;
        case ClkRCL:
            bFlag = M0P_CLOCK->RCL_CR_f.STABLE;
            break;
        case ClkXTL:
            bFlag = M0P_CLOCK->XTL_CR_f.STABLE;
            break;
        default:
            break;
    }
    return bFlag;
}


/**
 *******************************************************************************
 ** \brief 内部高速时钟频率设定
 ** \param [in]  enVal      设定的频率值
 ** \retval      Ok         设定成功
 **             其他        设定失败或时钟未稳定
 ******************************************************************************/
en_result_t Clk_SetRCHFreq(en_clk_freq_t enVal)
{
    en_result_t enRet = Ok;

    switch (enVal)
    {
        case ClkFreq4Mhz:
            M0P_CLOCK->RCH_CR_f.TRIM = RCH_CR_TRIM_4M_VAL;
            break;
        case ClkFreq8Mhz:
            M0P_CLOCK->RCH_CR_f.TRIM = RCH_CR_TRIM_8M_VAL;
            break;
        case ClkFreq16Mhz:
            M0P_CLOCK->RCH_CR_f.TRIM = RCH_CR_TRIM_16M_VAL;
            break;
        case ClkFreq22_12Mhz:
            M0P_CLOCK->RCH_CR_f.TRIM = RCH_CR_TRIM_22_12M_VAL;
            break;
        case ClkFreq24Mhz:
            M0P_CLOCK->RCH_CR_f.TRIM = RCH_CR_TRIM_24M_VAL;
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }
    
    return enRet;
}


/**
 *******************************************************************************
 ** \brief 内部低速时钟频率设定
 ** \param [in]  enVal      设定的频率值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetRCLFreq(en_clk_freq_t enVal)
{
    en_result_t enRet = Ok;

    switch (enVal)
    {
        case ClkFreq32768:
            M0P_CLOCK->RCL_CR_f.TRIM = RCL_CR_TRIM_32_8K_VAL;
            break;
        case ClkFreq38_4K:
            M0P_CLOCK->RCL_CR_f.TRIM = RCL_CR_TRIM_38_4K_VAL;
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 系统时钟（HCLK）分频设定
 ** \param [in]  u8Div      分频设定值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetHClkDiv(uint8_t u8Div)
{
    switch (u8Div)
    {
        case ClkDiv1:
        case ClkDiv2:
        case ClkDiv4:
        case ClkDiv8:
        case ClkDiv16:
        case ClkDiv32:
        case ClkDiv64:
        case ClkDiv128:
            CLK_Unlock();
            u8Div = Log2(u8Div);
            M0P_CLOCK->SYSCTRL0_f.HCLK_PRS = u8Div;
            break;
        default:
            return ErrorInvalidParameter;
    }

    return Ok;
}


/**
 *******************************************************************************
 ** \brief 外设时钟（PCLK）分频设定
 ** \param [in]  u8Div      分频设定值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetPClkDiv(uint8_t u8Div)
{

    switch (u8Div)
    {
        case ClkDiv1:
        case ClkDiv2:
        case ClkDiv4:
        case ClkDiv8:
            CLK_Unlock();
            u8Div = Log2(u8Div);
            M0P_CLOCK->SYSCTRL0_f.PCLK_PRS = u8Div;
            break;
        default:
            return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 *******************************************************************************
 ** \brief 外部高速时钟稳定时间设定
 ** \param [in]  enCycle     稳定时钟周期值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetXTH_StableTime(en_clk_cycle_t enCycle)
{
    en_result_t enRet = Ok;

    switch (enCycle)
    {
        case ClkCycle256:
            M0P_CLOCK->XTH_CR_f.STARTUP = 0u;
            break;
        case ClkCycle1024:
            M0P_CLOCK->XTH_CR_f.STARTUP = 1u;
            break;
        case ClkCycle4096:
            M0P_CLOCK->XTH_CR_f.STARTUP = 2u;
            break;
        case ClkCycle16384:
            M0P_CLOCK->XTH_CR_f.STARTUP = 3u;
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief 内部低速时钟稳定时间设定
 ** \param [in]  enCycle     稳定时钟周期值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetRCL_StableTime(en_clk_cycle_t enCycle)
{
    en_result_t enRet = Ok;

    switch (enCycle)
    {
        case ClkCycle4:
            M0P_CLOCK->RCL_CR_f.STARTUP = 0u;
            break;
        case ClkCycle16:
            M0P_CLOCK->RCL_CR_f.STARTUP = 1u;
            break;
        case ClkCycle64:
            M0P_CLOCK->RCL_CR_f.STARTUP = 2u;
            break;
        case ClkCycle256:
            M0P_CLOCK->RCL_CR_f.STARTUP = 3u;
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}


/**
 *******************************************************************************
 ** \brief 外部低速时钟稳定时间设定
 ** \param [in]  enCycle     稳定时钟周期值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetXTL_StableTime(en_clk_cycle_t enCycle)
{
    en_result_t enRet = Ok;

    switch (enCycle)
    {
        case ClkCycle256:
            M0P_CLOCK->XTL_CR_f.STARTUP = 0u;
            break;
        case ClkCycle1024:
            M0P_CLOCK->XTL_CR_f.STARTUP = 1u;
            break;
        case ClkCycle4096:
            M0P_CLOCK->XTL_CR_f.STARTUP = 2u;
            break;
        case ClkCycle16384:
            M0P_CLOCK->XTL_CR_f.STARTUP = 3u;
            break;
        default:
            enRet = ErrorInvalidParameter;
            break;
    }

    return enRet;
}


/**
 *******************************************************************************
 ** \brief 外部低速时钟驱动能力设定
 ** \param [in]  bHigh      是否高驱动能力
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetXTLDrive(boolean_t  bHigh)
{
    bHigh = !!bHigh;
    M0P_CLOCK->XTL_CR_f.DRIVER = bHigh;

    return Ok;
}

/**
   * \brief   Clk_Enable
   *          enable/disalbe to a paticular clock
   * \param   [in]  enSource  clock source
   * \param   [in]  u8Flag    TRUE:       enable
   *                          FALSE:      disable
   * \retval  en_result_t     Ok:         operation done.
   *                          ErrorInvalidParameter: invalid source type
   */
   
/**
 *******************************************************************************
 ** \brief 时钟使能
 ** \param [in]  enSource   目标时钟源
 ** \param [in]  bFlag      使能开关
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_Enable(en_clk_source_t enSource, boolean_t bFlag)
{
    en_result_t enRet = Ok;
    uint32_t u32Temp;
    
    CLK_Unlock();
    //force to 0/1
    bFlag = !!bFlag;

    u32Temp = M0P_CLOCK->PERI_CLKEN;
    switch (enSource)
    {
        case ClkXTL:
            M0P_CLOCK->PERI_CLKEN_f.GPIO = TRUE;
            M0P_GPIO->P1ADS_f.P14 = bFlag;
            M0P_GPIO->P1ADS_f.P15 = bFlag;
            M0P_CLOCK->XTL_CR_f.DRIVER = 0xF;
            M0P_CLOCK->SYSCTRL0_f.XTL_EN = bFlag;
            break;

        case ClkRCL:
            M0P_CLOCK->SYSCTRL0_f.RCL_EN = bFlag;
            break;

        case ClkXTH:
            M0P_CLOCK->PERI_CLKEN_f.GPIO = TRUE;
            M0P_GPIO->P0ADS_f.P01 = bFlag;
            M0P_GPIO->P0ADS_f.P02 = bFlag;
            M0P_CLOCK->XTH_CR_f.DRIVER = 0xF;
            M0P_CLOCK->SYSCTRL0_f.XTH_EN = bFlag;
            break;

        case ClkRCH:
            M0P_CLOCK->SYSCTRL0_f.RCH_EN = bFlag;
            break;

        default:
            CLK_DummyWrite();
            enRet = ErrorInvalidParameter;
            break;
    }
    M0P_CLOCK->PERI_CLKEN = u32Temp;
    return enRet;
}

/**
 *******************************************************************************
 ** \brief 获得外设时钟门控开关状态
 ** \param [in]  enPeripheral   目标外设
 ** \retval      TRUE           开
 **              FALSE          关
 ******************************************************************************/
boolean_t Clk_GetPeripheralGate(en_clk_peripheral_gate_t enPeripheral)
{
    return getBit(&M0P_CLOCK->PERI_CLKEN, enPeripheral);
}


/**
 *******************************************************************************
 ** \brief 设定RTC校准时钟频率
 ** \param [in]  u32val         频率值
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SetRTCAdjustClkFreq(uint32_t u32val)
{
    //en_result_t enRet = Ok;

    CLK_Unlock();

    if (u32val >= (32 * 1000 * 1000))
    {
        M0P_CLOCK->SYSCTRL1_f.RTC_FREQ_ADJUST = 7;
    } else if (u32val >= (24 * 1000 * 1000))
    {
        M0P_CLOCK->SYSCTRL1_f.RTC_FREQ_ADJUST = 6;
    } else if (u32val >= (20 * 1000 * 1000))
    {
        M0P_CLOCK->SYSCTRL1_f.RTC_FREQ_ADJUST = 5;
    } else if (u32val >= (16 * 1000 * 1000))
    {
        M0P_CLOCK->SYSCTRL1_f.RTC_FREQ_ADJUST = 4;
    } else if (u32val >= (12 * 1000 * 1000))
    {
        M0P_CLOCK->SYSCTRL1_f.RTC_FREQ_ADJUST = 3;
    } else if (u32val >= (8 * 1000 * 1000))
    {
        M0P_CLOCK->SYSCTRL1_f.RTC_FREQ_ADJUST = 2;
    } else if (u32val >= (6 * 1000 * 1000))
    {
        M0P_CLOCK->SYSCTRL1_f.RTC_FREQ_ADJUST = 1;
    } else if (u32val >= (4 * 1000 * 1000))
    {
        M0P_CLOCK->SYSCTRL1_f.RTC_FREQ_ADJUST = 0;
    } else
    {
        CLK_DummyWrite();
        return ErrorInvalidParameter;
    }

    return Ok;
}

/**
 *******************************************************************************
 ** \brief 设定Systick配置
 ** \param [in]  pstcCfg    systick配置参数
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_SysTickConfig(stc_clk_systickcfg_t *pstcCfg)
{
    if (NULL == pstcCfg)
    {
        return ErrorInvalidParameter;
    }

    M0P_CLOCK->PERI_CLKEN_f.TICK = 1;   // Enable peripheral clock on SysTick
    switch (pstcCfg->enClk)             // Select clock source if using enClk
    {
        case ClkRCH:
            M0P_CLOCK->SYSTICK_CR_f.CLK_SEL = 0x2;
            break;
        case ClkRCL:
            M0P_CLOCK->SYSTICK_CR_f.CLK_SEL = 0x1;
            break;
        case ClkXTH:
            M0P_CLOCK->SYSTICK_CR_f.CLK_SEL = 0x3;
            break;
        case ClkXTL:
            M0P_CLOCK->SYSTICK_CR_f.CLK_SEL = 0x0;
            break;
        default:
            return ErrorInvalidParameter;
    }

    M0P_CLOCK->SYSTICK_CR_f.NOREF = pstcCfg->bNoRef;

    SysTick->LOAD  = (uint32_t)(pstcCfg->u32LoadVal - 1UL);          // set reload value
    NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); // set Priority for SysTick Interrupt
    SysTick->VAL   = 0UL;                                            // Reset counter value
    SysTick->CTRL  = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk; // Turn on SysTick with Interrupt enabled

    return Ok;
}

/**
 *******************************************************************************
 ** \brief Systick SKEW 获取
 ** \param [in]  NULL
 ** \retval      SKEW值     （TRUE or FALSE）
 ******************************************************************************/
boolean_t Clk_SysTickSkewGet(void)
{
    return (boolean_t)M0P_CLOCK->SYSTICK_CR_f.SKEW;
}

/**
 *******************************************************************************
 ** \brief Systick CALIB 获取
 ** \param [in]  NULL
 ** \retval      CALIB值 (10ms校准值)
 ******************************************************************************/
uint32_t Clk_SysTickStcalibGet(void)
{
    return (uint32_t)M0P_CLOCK->SYSTICK_CR_f.STCALIB;
}

/**
 *******************************************************************************
 ** \brief 设定时钟外设调试开关
 ** \param [in]  enPeri     目标外设
 ** \param [in]  bFlag      状态开关
 ** \retval      Ok         设定成功
 **             其他        设定失败
 ******************************************************************************/
en_result_t Clk_DebugClk(en_clk_debug_t enPeri, boolean_t bFlag)
{
    switch (enPeri)
    {
        case ClkDBGTim0:
        case ClkDBGTim1:
        case ClkDBGTim2:
        case ClkDBGLpTim:
        case ClkDBGTim4:
        case ClkDBGTim5:
        case ClkDBGTim6:
        case ClkDBGTPca:
        case ClkDBGTWdt:
        case ClkDBGTRtc:
        case ClkDBGTTick:
            setBit(&M0P_CLOCK->DEBUG_ACTIVE, 1 << enPeri, bFlag);
            break;
        default:
            return ErrorInvalidParameter;
    }
    return Ok;
}

//@} // ClkGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
