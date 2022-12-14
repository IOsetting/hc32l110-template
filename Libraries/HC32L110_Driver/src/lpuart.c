/*************************************************************************************
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
/** \file lpuart.c
 **
 ** LPUART function driver API.
 ** @link SampleGroup Some description @endlink
 **
 **   - 2017-05-17  1.0  CJ First version for Device Driver Library of Module.
 **
 ******************************************************************************/

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "lpuart.h"
/**
 *******************************************************************************
 ** \addtogroup LpuartGroup
 ******************************************************************************/
//@{

/******************************************************************************/
/* Local pre-processor symbols/macros ('#define')                             */
/******************************************************************************/
#define IS_VALID_IRQSEL(x)  ((LPUartTxIrq == (x)) ||\
                             (LPUartRxIrq == (x))||\
                             (LPUartTxShiftNull ==(x)))

#define IS_VALID_MODE(x)    ((LPUartMode0==(x))||\
                             (LPUartMode1==(x))||\
                             (LPUartMode2==(x))||\
                             (LPUartMode3==(x)))

#define IS_VALID_STATUS(x)   ((LPUartRFRAMEError == (x))||\
                              (LPUartRxFull == (x))||\
                              (LPUartTxEmpty == (x)))

#define IS_VALID_CLK(x)      ((LPUart_Pclk==(x))||\
                              (LPUart_Pclk_1==(x))||\
                              (LPUart_Xtl==(x))||\
                              (LPUart_Rcl==(x))) 

#define IS_VALID_PRS(x)       ((LPUartDiv128==(x))||\
                               (LPUartDiv64==(x))||\
                               (LPUartDiv32==(x))||\
                               (LPUartDiv16==(x))||\
                               (LPUartDiv8==(x))||\
                               (LPUartDiv4==(x))||\
                               (LPUartDiv2==(x))||\
                               (LPUartDiv1==(x)))

/******************************************************************************/
/* Local function prototypes ('static')                                       */
/******************************************************************************/
static stc_lpuart_intern_cb_t* LPUartGetInternDataCb(void); 
static stc_lpuart_intern_cb_t stcLPUartIrqCb;

/**
 ******************************************************************************
 ** \brief lpuart??????or??????????????????.
 **
 ** \param enIrqSel??????or??????
 **
 ** \retval Ok ????????????
 **\retval ErrorInvalidParameter????????????
 ******************************************************************************/
en_result_t LPUart_EnableIrq(en_lpuart_irq_sel_t enIrqSel)
{
    ASSERT(IS_VALID_IRQSEL(enIrqSel));
    switch(enIrqSel)
    {
        case  LPUartTxIrq:
            M0P_LPUART->SCON_f.TIEN= 1u;
            break;
        case  LPUartRxIrq:
            M0P_LPUART->SCON_f.RIEN = 1u;
            break;
        case LPUartTxShiftNull:
            M0P_LPUART->SCON_f.TEEN = 1u;
            break;
        default:
            return (ErrorInvalidParameter);       
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief lpuart?????????????????????
 **
 ** \param enClk ???????????????
 **
 ** \retval Ok ????????????
 **\retval ErrorInvalidParameter????????????
 ******************************************************************************/
en_result_t LPUart_SelSclk(en_lpuart_sclksel_t enClk)
{
    ASSERT(IS_VALID_CLK(enClk));
    switch(enClk)
    {
        case LPUart_Pclk:
        case LPUart_Pclk_1:
        case LPUart_Xtl:
        case LPUart_Rcl:
            M0P_LPUART->SCON_f.SCLKSEL = enClk;
            break;
        default:
            return (ErrorInvalidParameter);
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief lpuart????????????????????????
 **
 ** \param enPrs?????????????????????
 **
 ** \retval Ok ????????????
 **
 ******************************************************************************/
en_result_t LPUart_SelSclkPrs(en_lpuart_sclkprs_t enPrs)
{
    en_result_t enRet = Error;
    ASSERT(IS_VALID_PRS(enPrs));
    M0P_LPUART->SCON_f.PRS = enPrs;
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief lpuart???????????????????????????????????????
 **
 ** \param enIrqSel?????????????????????
 **
 ** \retval Ok ????????????
 **\retval ErrorInvalidParameter????????????
 ******************************************************************************/
en_result_t LPUart_DisableIrq(en_lpuart_irq_sel_t enIrqSel)
{
    ASSERT(IS_VALID_IRQSEL(enIrqSel));
    switch(enIrqSel)
    {
        case  LPUartTxIrq:
            M0P_LPUART->SCON_f.TIEN = 0u;
            break;
        case  LPUartRxIrq:
            M0P_LPUART->SCON_f.RIEN = 0u;
            break;
        case LPUartTxShiftNull:
            M0P_LPUART->SCON_f.TEEN = 0u;
            break;
        default:
            return (ErrorInvalidParameter);       
    }  
    return Ok;
}
/**
 ******************************************************************************
 ** \brief lpuart??????4???????????????
 **
 ** \param enMode????????????
 **
 ** \retval Ok ????????????
 **
 ******************************************************************************/
en_result_t LPUart_SetMode(stc_lpuart_mode_t* pstcMode)
{
    en_result_t enRet = Error;
    ASSERT(IS_VALID_MODE(pstcMode->enMode));
    M0P_LPUART->SCON_f.LPMODE = pstcMode->enLpMode;
    if(LPUartLPMode == M0P_LPUART->SCON_f.LPMODE)//?????????????????????
    {   
        switch(pstcMode->enMode)
        {
            //case LPUartMode0:
            //case LPUartMode2:
               // return (ErrorInvalidParameter); 
//                break;
            case LPUartMode1:
            case LPUartMode3:  
                M0P_LPUART->SCON_f.SM01 = pstcMode->enMode;
                break;
            default:
                return (ErrorInvalidParameter); 
        }
    }
    else
    {
      M0P_LPUART->SCON_f.SM01 = pstcMode->enMode; 
    }
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief lpuart??????????????????????????????
 **
 ** \param pstcMultiConfig???????????????????????????
 **
 ** \retval Ok ????????????
 **
 ******************************************************************************/
en_result_t LPUart_SetMultiMode(stc_lpuart_multimode_t* pstcMultiConfig)
{
    en_result_t enRet = Error;
    M0P_LPUART->SCON_f.SM2 = pstcMultiConfig->enMulti_mode;
    if(LPUartMulti == pstcMultiConfig->enMulti_mode)
    {
        M0P_LPUART->SADDR = pstcMultiConfig->u8SlaveAddr;
        M0P_LPUART->SADEN = pstcMultiConfig->u8SaddEn;
    }
    enRet = Ok;
    return enRet;
}

/**
 ******************************************************************************
 ** \brief lpuart???????????????????????????
 **
 ** \param u8Addr?????????
 **
 ** \retval Ok ????????????
 **
 ******************************************************************************/
en_result_t LPUart_SetSaddr(uint8_t u8Addr)
{
    en_result_t enRet = Error;
    M0P_LPUART->SADDR = u8Addr;
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief lpuart?????????????????????Or???????????????
 **
 ** \param enTb8??????or??????
 **
 ** \retval Ok ????????????
 **
 ******************************************************************************/
en_result_t LPUart_SetMMDOrCk(en_lpuart_mmdorck_t enTb8)
{
  en_result_t enRet = Error;
  M0P_LPUART->SCON_f.TB8 = enTb8;
  enRet = Ok;
  return enRet;
}
/**
 ******************************************************************************
 ** \brief ??????RB8??????
 **
 ** \param [in] u8Idx?????????
 **
 ** \retval RB8
 **\retval ErrorInvalidParameter????????????
 ******************************************************************************/
boolean_t LPUart_GetRb8(void)
{
    return (M0P_LPUART->SCON_f.RB8);
}
/**
 ******************************************************************************
 ** \brief ??????????????????1?????????
 **
 ** \param u8Data????????????
 **
 ** \retval ??????
 ******************************************************************************/
en_result_t LPUart_SetTb8(en_uart_check_t enCheck,uint8_t u8Data)
{
	uint8_t cnt=0,i;	
	for(i=0;i<8;i++)
	{
		if((u8Data&0x80)==0x80)
		{
			cnt++;
		}
		u8Data<<=1;
	}
	if(enCheck == Even)
	{
		if(cnt%2!=0)
		{
			M0P_LPUART->SCON_f.TB8 = 1;
		}
		else
		{
			M0P_LPUART->SCON_f.TB8 = 0;
		}
	}
	else
	{
		if(cnt%2!=0)
		{
			M0P_LPUART->SCON_f.TB8 = 0;
		}
		else
		{
			M0P_LPUART->SCON_f.TB8 = 1;
		}
	}
	return Ok;
}
/**
 ******************************************************************************
 ** \brief ??????????????????????????????????????????
 **
 ** \param enCheck?????????????????????u8Recv????????????
 **
 ** \retval Error????????????Ok
 ******************************************************************************/
en_result_t LPUart_CheckEvenOrOdd(en_uart_check_t enCheck,uint8_t u8Recv)
{
	uint8_t cnt=0,i;

	for(i=0;i<8;i++)
	{
		if((u8Recv&0x80)==0x80)
		{
			cnt++;
		}
		u8Recv<<=1;
	}
	if(enCheck == Even)
	{
		if(cnt%2!=0)
		{
			if(M0P_LPUART->SCON_f.RB8 != 1)
			{
				return Error;
			}
		}
		else
		{
			if(M0P_LPUART->SCON_f.RB8 != 0)
			{
				return Error;
			}
		}
	}
	else
	{
		if(cnt%2!=0)
		{
			if(M0P_LPUART->SCON_f.RB8 != 0)
			{
				return Error;
			}
		}
		else
		{
			if(M0P_LPUART->SCON_f.RB8 != 1)
			{
				return Error;
			}
		}
	}
	return Ok;
}
/**
 ******************************************************************************
 ** \brief lpuart???????????????????????????????????????
 **
 ** \param u8Addren??????????????????
 **
 ** \retval Ok ????????????
 **
 ******************************************************************************/
en_result_t LPUart_SetSaddrEn(uint8_t u8Addren)
{
  en_result_t enRet = Error;
  M0P_LPUART->SADEN = u8Addren;
  enRet = Ok;
  return enRet;  
}
/**
 ******************************************************************************
 ** \brief lpuart???????????????
 **
 ** \param u32pclk pclk?????????pstcBaud?????????????????????
 **
 ** \retval ??????????????????
 **\retval 0????????????
 ******************************************************************************/
uint16_t LPUart_SetBaudRate(uint32_t u32pclk,en_lpuart_sclkprs_t enprs,stc_lpuart_baud_config_t* pstcBaud)
{
    uint16_t u16tmload=0;
    if (NULL == pstcBaud)
    {
        return 0;//test
    }
    M0P_LPUART->SCON_f.DBAUD = pstcBaud->bDbaud;
    switch(pstcBaud->u8Mode)
    {
        case LPUartMode0:
        case LPUartMode2:
            u16tmload = 0;
            break;
        case LPUartMode1:
        case LPUartMode3:
            if(LPUartNoLPMode == pstcBaud->u8LpMode)
            {
                u16tmload = 0x10000-((u32pclk*(pstcBaud->bDbaud+1))/(pstcBaud->u32Baud*32));//????????????????????????????????????
            }
            else
            {
                return 0;//???????????????
            }
            break;
        default:
            break; 
    }
    return u16tmload;
}
/**
 ******************************************************************************
 ** \brief lpuart???????????????
 **
 ** \param ???
 **
 ** \retval ??????????????????mode1/mode3????????????????????????
 ** \retval ????????????
 ******************************************************************************/
uint32_t LPUart_GetBaudRate(void)
{
    uint32_t u32sclk = 0;
    uint32_t u32baud = 0;
    
    if(LPUart_Xtl == M0P_LPUART->SCON_f.SCLKSEL)
    {
      u32sclk = 32768;
    }
    else if(0x000 == (M0P_CLOCK->RCL_CR_f.TRIM&0x200u))
    {
      u32sclk = 32768;
    }
    else if(0x200 == (M0P_CLOCK->RCL_CR_f.TRIM&0x200u))
    {
      u32sclk = 38400;
    }
    else
    {
      return 0;
    }
    u32baud = u32sclk/((1<<(7-M0P_LPUART->SCON_f.PRS))*4);
    return u32baud;
}
/**
 ******************************************************************************
 ** \brief lpuart???????????????????????????
 **
 ** \param enFunc???????????????
 **
 ** \retval OK????????????
 **
 ******************************************************************************/
en_result_t LPUart_EnableFunc(en_lpuart_func_t enFunc)
{
    en_result_t enRet = Error;
    M0P_LPUART->SCON_f.REN = enFunc;
    enRet = Ok;
    return enRet;  
}
/**
 ******************************************************************************
 ** \brief lpuart??????????????????????????????
 ** 
 ** \param enStatus??????????????????
 **
 ** \retval ?????????
 **
 ******************************************************************************/
boolean_t LPUart_GetStatus(en_lpuart_status_t enStatus)
{
    boolean_t status=FALSE;
    ASSERT(IS_VALID_STATUS(enStatus));
    switch(enStatus)
    {
        case LPUartRFRAMEError:
            status = (M0P_LPUART->ISR_f.FE == 1) ? TRUE : FALSE;
            break;
        case LPUartRxFull:
            status = (M0P_LPUART->ISR_f.RI == 1) ? TRUE : FALSE;
            break;
        case LPUartTxEmpty:
            status = (M0P_LPUART->ISR_f.TI == 1) ? TRUE : FALSE;
            break;
        default:
            break; 
    }
    return status;
}
/**
 ******************************************************************************
 ** \brief lpuart??????????????????????????????
 ** 
 ** \param enStatus??????????????????
 **
 ** \retval Ok ????????????
 ** \retval ErrorInvalidParameter????????????
 **
 ******************************************************************************/
en_result_t LPUart_ClrStatus(en_lpuart_status_t enStatus)
{
    ASSERT(IS_VALID_STATUS(enStatus));
    switch(enStatus)
    {
        case LPUartRFRAMEError:
            M0P_LPUART->ICR_f.FECLR = 0;
            break;
        case LPUartRxFull:
            M0P_LPUART->ICR_f.RICLR = 0;
            break;
        case LPUartTxEmpty:
            M0P_LPUART->ICR_f.TICLR = 0;
            break;
        default:
            return ErrorInvalidParameter; 
    }
    return Ok;
}
/**
 ******************************************************************************
 ** \brief lpuart????????????????????????,?????????????????????????????????????????????
 ** 
 ** \param u32Data????????????
 **
 ** \retval Ok ????????????
 **
 ******************************************************************************/
en_result_t LPUart_SendData(uint8_t u8Data)
{
    en_result_t enRet = Error;
    LPUart_ClrStatus(LPUartTxEmpty);
    M0P_LPUART->SBUF = u8Data;
    while(FALSE == LPUart_GetStatus(LPUartTxEmpty))
    {}
    LPUart_ClrStatus(LPUartTxEmpty);
    enRet = Ok;
    return enRet;
}
/**
 ******************************************************************************
 ** \brief lpuart????????????????????????
 ** 
 ** \param ???
 **
 ** \retval ??????????????????
 **
 ******************************************************************************/
uint8_t LPUart_ReceiveData(void)
{
    return (M0P_LPUART->SBUF);
}
/**
 ******************************************************************************
 ** \brief lpuart??????????????????????????????
 ** 
 ** \param ???
 **
 ** \retval ????????????????????????
 **
 ******************************************************************************/
static stc_lpuart_intern_cb_t* LPUartGetInternDataCb(void)
{
    return &stcLPUartIrqCb;
}
/**
 ******************************************************************************
 ** \brief lpuart??????????????????
 ** 
 ** \param ???
 **
 ** \retval ???
 **
 ******************************************************************************/
void LPUART_IRQHandler(void)
{
    if(1 == M0P_LPUART->ISR_f.FE)
    {
        LPUart_ClrStatus(LPUartRFRAMEError);
        if(NULL != stcLPUartIrqCb.pfnRxErrIrqCb)
        {
            stcLPUartIrqCb.pfnRxErrIrqCb();
        }
    }
    if(1 == M0P_LPUART->ISR_f.RI)
    {
        LPUart_ClrStatus(LPUartRxFull);
        if(NULL != stcLPUartIrqCb.pfnRxIrqCb)
        {
            stcLPUartIrqCb.pfnRxIrqCb();
        }
    }
    if(1 == M0P_LPUART->ISR_f.TI)
    {
        LPUart_ClrStatus(LPUartTxEmpty);
        if(NULL != stcLPUartIrqCb.pfnTxIrqCb)
        {
            stcLPUartIrqCb.pfnTxIrqCb();
        }
    }
}
/**
 ******************************************************************************
 ** \brief lpuart??????NVIC??????????????????
 ** 
 ** \param ???
 **
 ** \retval ???
 **
 ******************************************************************************/
static void LPUartInitNvic(void)
{
    NVIC_ClearPendingIRQ(LPUART_IRQn);
    NVIC_SetPriority(LPUART_IRQn,DDL_IRQ_LEVEL_DEFAULT);
    NVIC_EnableIRQ(LPUART_IRQn);
    
}
/**
 ******************************************************************************
 ** \brief lpuart??????NVIC??????????????????
 ** 
 ** \param ???
 **
 ** \retval ???
 **
 ******************************************************************************/
static void LPUartDeInitNvic(void)
{
    NVIC_ClearPendingIRQ(LPUART_IRQn);
    NVIC_SetPriority(LPUART_IRQn,DDL_IRQ_LEVEL_DEFAULT);
    NVIC_DisableIRQ(LPUART_IRQn);
    
}
/**
 ******************************************************************************
 ** \brief lpuart???????????????
 ** 
 ** \param pstcConfig???????????????
 **
 ** \retval Ok ????????????
 ** \retval ErrorInvalidParameter????????????
 ******************************************************************************/
en_result_t LPUart_Init(stc_lpuart_config_t* pstcConfig)
{
    stc_lpuart_irq_cb_t* pstcLPUartInternCb;
    pstcLPUartInternCb = LPUartGetInternDataCb();
    if(NULL == pstcConfig)
    {
        return ErrorInvalidParameter;
    }
    if(NULL != pstcConfig->pstcLpuart_clk)
    {
        LPUart_SelSclk(pstcConfig->pstcLpuart_clk->enSclk_sel);
        LPUart_SelSclkPrs(pstcConfig->pstcLpuart_clk->enSclk_Prs);
    }
    LPUart_SetMode(pstcConfig->pstcRunMode);
    if(NULL != pstcConfig->pstcMultiMode)
    {
        LPUart_SetMultiMode(pstcConfig->pstcMultiMode);
    }
    if(NULL != pstcConfig->pstcIrqCb)
    {
        pstcLPUartInternCb->pfnRxErrIrqCb= pstcConfig->pstcIrqCb->pfnRxErrIrqCb;
        pstcLPUartInternCb->pfnRxIrqCb = pstcConfig->pstcIrqCb->pfnRxIrqCb;
        pstcLPUartInternCb->pfnTxIrqCb = pstcConfig->pstcIrqCb->pfnTxIrqCb;
    }
    if(pstcConfig->bTouchNvic == TRUE)
    {
        LPUartInitNvic();
    }
    else
    {
        LPUartDeInitNvic();
    }
    return Ok;
}
//@} // LpuartGroup     
      
      

