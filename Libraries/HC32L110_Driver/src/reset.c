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

/** \file reset.c
 **
 ** Common API of reset.
 ** @link resetGroup Some description @endlink
 **
 **   - 2017-05-04
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "reset.h"

/**
 *******************************************************************************
 ** \addtogroup ResetGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/


/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/


/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 *******************************************************************************
 ** \brief 获取复位源类型.
 **
 ** \param [out]  pstcOut  复位源类型列表     
 ** 
 ** \retval  Ok         操作成功
 **          其他       操作失败
 ******************************************************************************/
en_result_t Reset_GetCause(stc_reset_cause_t *pstcOut)
{
        uint8_t u8val = 0;
    if (NULL == pstcOut)
    {
        return ErrorInvalidParameter;
    }
    
    u8val = M0P_RESET->RESET_FLAG;
    
    *pstcOut = *((stc_reset_cause_t*)&u8val);
    return Ok;
}


/**
 *******************************************************************************
 ** \brief 清除复位源类型.
 **
 ** \param [in]  stcval  复位源类型列表，对应标志位写0清除。
 ** 
 ** \retval  Ok         操作成功
 **          其他       操作失败
 ******************************************************************************/
en_result_t Reset_Clear(stc_reset_cause_t stcval)
{
    uint8_t u8val = *((uint8_t*)&stcval);

    M0P_RESET->RESET_FLAG = u8val;

    return Ok;
}


/**
 *******************************************************************************
 ** \brief 设置外设复位源开关.
 **
 ** \param [in]  enPeri  复位源类型列表
 ** \param [in]  bFlag   复位开关
 ** 
 ** \retval  Ok         操作成功
 **          其他       操作失败
 ******************************************************************************/
en_result_t Reset_SetPeripheralReset(en_reset_peripheral_t enPeri,boolean_t bFlag)
{

    bFlag = !!bFlag;

    switch (enPeri)
    {
        case ResetGpio:
            M0P_RESET->PREI_RESET_f.GPIO = bFlag;
            break;
        case ResetCrc:
            M0P_RESET->PREI_RESET_f.CRC = bFlag;
            break;
        case ResetTick:
            M0P_RESET->PREI_RESET_f.TICK = bFlag;
            break;
        case ResetTrim:
            M0P_RESET->PREI_RESET_f.TRIM = bFlag;
            break;
        case ResetRtc:
            M0P_RESET->PREI_RESET_f.RTC = bFlag;
            break;
        case ResetVc:
            M0P_RESET->PREI_RESET_f.VC = bFlag;
            break;
        case ResetAdc:
            M0P_RESET->PREI_RESET_f.ADC = bFlag;
            break;
        case ResetPca:
            M0P_RESET->PREI_RESET_f.PCA = bFlag;
            break;
        case ResetAdcTim:
            M0P_RESET->PREI_RESET_f.ADVTIM = bFlag;
            break;
        case ResetLpTim:
            M0P_RESET->PREI_RESET_f.LPTIM = bFlag;
            break;
        case ResetBaseTim:
            M0P_RESET->PREI_RESET_f.BASETIM = bFlag;
            break;
        case ResetSpi:
            M0P_RESET->PREI_RESET_f.SPI = bFlag;
            break;
        case ResetI2c:
            M0P_RESET->PREI_RESET_f.I2C = bFlag;
            break;
        case ResetLpUart:
            M0P_RESET->PREI_RESET_f.LPUART = bFlag;
            break;
        case ResetUart1:
            M0P_RESET->PREI_RESET_f.UART1 = bFlag;
            break;
        case ResetUart0:
            M0P_RESET->PREI_RESET_f.UART0 = bFlag;
            break;
        default:
            return ErrorInvalidParameter;
    }
    return Ok;
}





//@} // ResetGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


