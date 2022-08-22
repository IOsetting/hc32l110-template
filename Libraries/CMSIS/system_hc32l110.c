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
/** \file system_hc32l110.c
 **
 ** System clock initialization.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2016-02-16  1.0  QianCP First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"
#include "hc32l110.h"
#include "system_hc32l110.h"
#include "ddl.h"

/**
 ******************************************************************************
 ** System Clock Frequency (Core Clock) Variable according CMSIS
 ******************************************************************************/
uint32_t SystemCoreClock = 4000000;


//add clock source.
void SystemCoreClockUpdate (void) // Update SystemCoreClock variable
{
    SystemCoreClock = Clk_GetHClkFreq();
}


/**
 ******************************************************************************
 ** \brief  对MCU未引出IO端口进行默认配置.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
static void _HidePinInit(void)
{
#if !defined(HC32L110Cxxx)       //20PIN MCU	
    uint32_t tmpReg = M0P_CLOCK->PERI_CLKEN;
	
	M0P_CLOCK->PERI_CLKEN_f.GPIO = 1;
    
  #if defined(HC32L110Bxxx)	     //16PIN MCU
    M0P_GPIO->P0ADS &= 0x07;     ///< P03配置为数字端口
	M0P_GPIO->P3ADS &= 0xE3;     ///< P32/P33/P34配置为数字端口
	
    M0P_GPIO->P0DIR	|= 0xF8;     ///< P03配置为端口输入
    M0P_GPIO->P3DIR	|= 0x1C;     ///< P32/P33/P34配置为端口输入
	
	M0P_GPIO->P0PU  |= 0xF8;     ///< P03配置为上拉
	M0P_GPIO->P3PU  |= 0x1C;     ///< P32/P33/P34配置为上拉
    
  #endif
	  M0P_CLOCK->PERI_CLKEN = tmpReg;
#endif
}


/**
 ******************************************************************************
 ** \brief  Setup the microcontroller system. Initialize the System and update
 ** the SystemCoreClock variable.
 **
 ** \param  none
 ** \return none
 ******************************************************************************/
void SystemInit(void)
{
    stc_clk_systickcfg_t stcCfg;

    // TODO load trim from flash and enable RCH
    //hcr 4MHz manual trim.
    Clk_SetRCHFreq(ClkFreq4Mhz);
    Clk_Enable(ClkRCH, TRUE);    
                                                
    SystemCoreClockUpdate();
	  
	_HidePinInit();

    DDL_ZERO_STRUCT(stcCfg);
    stcCfg.bNoRef = TRUE;
    stcCfg.u32LoadVal = 0xFFFFFF;
    Clk_SysTickConfig(&stcCfg);
}


