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
/** \\file HC32L110.h
**
** Auto generate.
** Headerfile for HC32L110 series MCU
**
** History:
**
**   - 2018-09-13  0.1   First version for Device Driver Library of Module.
**
******************************************************************************/

#ifndef __HC32L110_H__
#define __HC32L110_H__

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Configuration of the Cortex-M0P Processor and Core Peripherals
******************************************************************************/
#define __MPU_PRESENT           0 /* No MPU                                       */
#define __NVIC_PRIO_BITS        2 /* M0P uses 2 Bits for the Priority Levels      */
#define __Vendor_SysTickConfig  0 /* Set to 1 if different SysTick Config is used */

/******************************************************************************
* Interrupt Number Definition
******************************************************************************/
typedef enum IRQn
{
    NMI_IRQn            = -14, /*  2 Non Maskable                            */
    HardFault_IRQn      = -13, /*  3 Hard Fault                              */
    SVC_IRQn            = -5,  /* 11 SV Call                                 */
    PendSV_IRQn         = -2,  /* 14 Pend SV                                 */
    SysTick_IRQn        = -1,  /* 15 System Tick                             */
    
    PORT0_IRQn          = 0 ,
    PORT1_IRQn          = 1 ,
    PORT2_IRQn          = 2 ,
    PORT3_IRQn          = 3 ,
    UART0_IRQn          = 6 ,
    UART1_IRQn          = 7 ,
    LPUART_IRQn         = 8 ,
    SPI_IRQn            = 10,
    I2C_IRQn            = 12,
    TIM0_IRQn           = 14,
    TIM1_IRQn           = 15,
    TIM2_IRQn           = 16,
    LPTIM_IRQn          = 17,
    TIM4_IRQn           = 18,
    TIM5_IRQn           = 19,
    TIM6_IRQn           = 20,
    PCA_IRQn            = 21,
    WDT_IRQn            = 22,
    RTC_IRQn            = 23,
    ADC_IRQn            = 24,
    VC0_IRQn            = 26,
    VC1_IRQn            = 27,
    LVD_IRQn            = 28,
    FLASH_RAM_IRQn      = 30,
    CLK_TRIM_IRQn       = 31,
    
    
} IRQn_Type;


#include <core_cm0plus.h>
#include <stdint.h>

#define SUCCESS         (0)
#define ERROR           (-1)

#ifndef NULL
#define NULL            (0)
#endif


/******************************************************************************/
/*                Device Specific Peripheral Registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

typedef struct
{
    __IO uint32_t ADCEN                     : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t CLKSEL                    : 2;
    __IO uint32_t SEL                       : 4;
    __IO uint32_t SREF                      : 2;
    __IO uint32_t BUFEN                     : 1;
    __IO uint32_t SAM                       : 2;
    uint32_t RESERVED13                     : 1;
    __IO uint32_t IE                        : 1;
    __IO uint32_t STATERST                  : 1;
} stc_adc_cr0_field_t;

typedef struct
{
    __IO uint32_t TRIGS0                    : 5;
    __IO uint32_t TRIGS1                    : 5;
    __IO uint32_t CT                        : 1;
    __IO uint32_t RACC_EN                   : 1;
    __IO uint32_t LTCMP                     : 1;
    __IO uint32_t HTCMP                     : 1;
    __IO uint32_t REGCMP                    : 1;
    __IO uint32_t RACC_CLR                  : 1;
} stc_adc_cr1_field_t;

typedef struct
{
    __IO uint32_t CH0EN                     : 1;
    __IO uint32_t CH1EN                     : 1;
    __IO uint32_t CH2EN                     : 1;
    __IO uint32_t CH3EN                     : 1;
    __IO uint32_t CH4EN                     : 1;
    __IO uint32_t CH5EN                     : 1;
    __IO uint32_t CH6EN                     : 1;
    __IO uint32_t CH7EN                     : 1;
    __IO uint32_t ADCCNT                    : 8;
} stc_adc_cr2_field_t;

typedef struct
{
    __IO uint32_t RESULT0                   :12;
} stc_adc_result0_field_t;

typedef struct
{
    __IO uint32_t RESULT1                   :12;
} stc_adc_result1_field_t;

typedef struct
{
    __IO uint32_t RESULT2                   :12;
} stc_adc_result2_field_t;

typedef struct
{
    __IO uint32_t RESULT3                   :12;
} stc_adc_result3_field_t;

typedef struct
{
    __IO uint32_t RESULT4                   :12;
} stc_adc_result4_field_t;

typedef struct
{
    __IO uint32_t RESULT5                   :12;
} stc_adc_result5_field_t;

typedef struct
{
    __IO uint32_t RESULT6                   :12;
} stc_adc_result6_field_t;

typedef struct
{
    __IO uint32_t RESULT7                   :12;
} stc_adc_result7_field_t;

typedef struct
{
    __IO uint32_t RESULT8                   :12;
} stc_adc_result8_field_t;

typedef struct
{
    __IO uint32_t RESULT_ACC                :20;
} stc_adc_result_acc_field_t;

typedef struct
{
    __IO uint32_t HT                        :12;
} stc_adc_ht_field_t;

typedef struct
{
    __IO uint32_t LT                        :12;
} stc_adc_lt_field_t;

typedef struct
{
    __IO uint32_t LLT_INTF                  : 1;
    __IO uint32_t HHT_INTF                  : 1;
    __IO uint32_t REG_INTF                  : 1;
    __IO uint32_t CONT_INTF                 : 1;
} stc_adc_ifr_field_t;

typedef struct
{
    __IO uint32_t LLT_INTC                  : 1;
    __IO uint32_t HHT_INTC                  : 1;
    __IO uint32_t REG_INTC                  : 1;
    __IO uint32_t CONT_INTC                 : 1;
} stc_adc_iclr_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :12;
} stc_adc_result_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_adt_cnter_field_t;

typedef struct
{
    __IO uint32_t PERA                      :16;
} stc_adt_perar_field_t;

typedef struct
{
    __IO uint32_t PERB                      :16;
} stc_adt_perbr_field_t;

typedef struct
{
    __IO uint32_t GCMA                      :16;
} stc_adt_gcmar_field_t;

typedef struct
{
    __IO uint32_t GCMB                      :16;
} stc_adt_gcmbr_field_t;

typedef struct
{
    __IO uint32_t GCMC                      :16;
} stc_adt_gcmcr_field_t;

typedef struct
{
    __IO uint32_t GCMD                      :16;
} stc_adt_gcmdr_field_t;

typedef struct
{
    __IO uint32_t DTUA                      :16;
} stc_adt_dtuar_field_t;

typedef struct
{
    __IO uint32_t DTDA                      :16;
} stc_adt_dtdar_field_t;

typedef struct
{
    __IO uint32_t START                     : 1;
    __IO uint32_t MODE                      : 3;
    __IO uint32_t CKDIV                     : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t DIR                       : 1;
    uint32_t RESERVED9                      : 7;
    __IO uint32_t ZMSKREV                   : 1;
    __IO uint32_t ZMSKPOS                   : 1;
    __IO uint32_t ZMSK                      : 2;
} stc_adt_gconr_field_t;

typedef struct
{
    __IO uint32_t INTENA                    : 1;
    __IO uint32_t INTENB                    : 1;
    __IO uint32_t INTENC                    : 1;
    __IO uint32_t INTEND                    : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t INTENOVF                  : 1;
    __IO uint32_t INTENUDF                  : 1;
    __IO uint32_t INTENDE                   : 1;
} stc_adt_iconr_field_t;

typedef struct
{
    __IO uint32_t CAPCA                     : 1;
    __IO uint32_t STACA                     : 1;
    __IO uint32_t STPCA                     : 1;
    __IO uint32_t STASTPSA                  : 1;
    __IO uint32_t CMPCA                     : 2;
    __IO uint32_t PERCA                     : 2;
    __IO uint32_t OUTENA                    : 1;
    __IO uint32_t DISSELA                   : 2;
    __IO uint32_t DISVALA                   : 2;
    uint32_t RESERVED13                     : 3;
    __IO uint32_t CAPCB                     : 1;
    __IO uint32_t STACB                     : 1;
    __IO uint32_t STPCB                     : 1;
    __IO uint32_t STASTPSB                  : 1;
    __IO uint32_t CMPCB                     : 2;
    __IO uint32_t PERCB                     : 2;
    __IO uint32_t OUTENB                    : 1;
    __IO uint32_t DISSELB                   : 2;
    __IO uint32_t DISVALB                   : 2;
} stc_adt_pconr_field_t;

typedef struct
{
    __IO uint32_t BENA                      : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t BENB                      : 1;
    uint32_t RESERVED3                      : 5;
    __IO uint32_t BENP                      : 1;
} stc_adt_bconr_field_t;

typedef struct
{
    __IO uint32_t DTCEN                     : 1;
    uint32_t RESERVED1                      : 7;
    __IO uint32_t SEPA                      : 1;
} stc_adt_dconr_field_t;

typedef struct
{
    __IO uint32_t NOFIENGA                  : 1;
    __IO uint32_t NOFICKGA                  : 2;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t NOFIENGB                  : 1;
    __IO uint32_t NOFICKGB                  : 2;
    uint32_t RESERVED7                      : 9;
    __IO uint32_t NOFIENTA                  : 1;
    __IO uint32_t NOFICKTA                  : 2;
    uint32_t RESERVED19                     : 1;
    __IO uint32_t NOFIENTB                  : 1;
    __IO uint32_t NOFICKTB                  : 2;
    uint32_t RESERVED23                     : 1;
    __IO uint32_t NOFIENTC                  : 1;
    __IO uint32_t NOFICKTC                  : 2;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t NOFIENTD                  : 1;
    __IO uint32_t NOFICKTD                  : 2;
} stc_adt_fconr_field_t;

typedef struct
{
    __IO uint32_t GEPERIA                   : 1;
    __IO uint32_t GEPERIB                   : 1;
    __IO uint32_t GEPERIC                   : 1;
    __IO uint32_t GEPERID                   : 1;
    uint32_t RESERVED4                      :12;
    __IO uint32_t PCNTE                     : 2;
    __IO uint32_t PCNTS                     : 3;
} stc_adt_vperr_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    uint32_t RESERVED9                      :12;
    __IO uint32_t VPERNUM                   : 3;
    uint32_t RESERVED24                     : 7;
    __IO uint32_t DIRF                      : 1;
} stc_adt_stflr_field_t;

typedef struct
{
    __IO uint32_t HSTA0                     : 1;
    __IO uint32_t HSTA1                     : 1;
    __IO uint32_t HSTA2                     : 1;
    __IO uint32_t HSTA3                     : 1;
    __IO uint32_t HSTA4                     : 1;
    __IO uint32_t HSTA5                     : 1;
    __IO uint32_t HSTA6                     : 1;
    __IO uint32_t HSTA7                     : 1;
    __IO uint32_t HSTA8                     : 1;
    __IO uint32_t HSTA9                     : 1;
    __IO uint32_t HSTA10                    : 1;
    __IO uint32_t HSTA11                    : 1;
    __IO uint32_t HSTA12                    : 1;
    __IO uint32_t HSTA13                    : 1;
    __IO uint32_t HSTA14                    : 1;
    __IO uint32_t HSTA15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STARTS                    : 1;
} stc_adt_hstar_field_t;

typedef struct
{
    __IO uint32_t HSTP0                     : 1;
    __IO uint32_t HSTP1                     : 1;
    __IO uint32_t HSTP2                     : 1;
    __IO uint32_t HSTP3                     : 1;
    __IO uint32_t HSTP4                     : 1;
    __IO uint32_t HSTP5                     : 1;
    __IO uint32_t HSTP6                     : 1;
    __IO uint32_t HSTP7                     : 1;
    __IO uint32_t HSTP8                     : 1;
    __IO uint32_t HSTP9                     : 1;
    __IO uint32_t HSTP10                    : 1;
    __IO uint32_t HSTP11                    : 1;
    __IO uint32_t HSTP12                    : 1;
    __IO uint32_t HSTP13                    : 1;
    __IO uint32_t HSTP14                    : 1;
    __IO uint32_t HSTP15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t STOPS                     : 1;
} stc_adt_hstpr_field_t;

typedef struct
{
    __IO uint32_t HCEL0                     : 1;
    __IO uint32_t HCEL1                     : 1;
    __IO uint32_t HCEL2                     : 1;
    __IO uint32_t HCEL3                     : 1;
    __IO uint32_t HCEL4                     : 1;
    __IO uint32_t HCEL5                     : 1;
    __IO uint32_t HCEL6                     : 1;
    __IO uint32_t HCEL7                     : 1;
    __IO uint32_t HCEL8                     : 1;
    __IO uint32_t HCEL9                     : 1;
    __IO uint32_t HCEL10                    : 1;
    __IO uint32_t HCEL11                    : 1;
    __IO uint32_t HCEL12                    : 1;
    __IO uint32_t HCEL13                    : 1;
    __IO uint32_t HCEL14                    : 1;
    __IO uint32_t HCEL15                    : 1;
    uint32_t RESERVED16                     :15;
    __IO uint32_t CLEARS                    : 1;
} stc_adt_hcelr_field_t;

typedef struct
{
    __IO uint32_t HCPA0                     : 1;
    __IO uint32_t HCPA1                     : 1;
    __IO uint32_t HCPA2                     : 1;
    __IO uint32_t HCPA3                     : 1;
    __IO uint32_t HCPA4                     : 1;
    __IO uint32_t HCPA5                     : 1;
    __IO uint32_t HCPA6                     : 1;
    __IO uint32_t HCPA7                     : 1;
    __IO uint32_t HCPA8                     : 1;
    __IO uint32_t HCPA9                     : 1;
    __IO uint32_t HCPA10                    : 1;
    __IO uint32_t HCPA11                    : 1;
    __IO uint32_t HCPA12                    : 1;
    __IO uint32_t HCPA13                    : 1;
    __IO uint32_t HCPA14                    : 1;
    __IO uint32_t HCPA15                    : 1;
} stc_adt_hcpar_field_t;

typedef struct
{
    __IO uint32_t HCPB0                     : 1;
    __IO uint32_t HCPB1                     : 1;
    __IO uint32_t HCPB2                     : 1;
    __IO uint32_t HCPB3                     : 1;
    __IO uint32_t HCPB4                     : 1;
    __IO uint32_t HCPB5                     : 1;
    __IO uint32_t HCPB6                     : 1;
    __IO uint32_t HCPB7                     : 1;
    __IO uint32_t HCPB8                     : 1;
    __IO uint32_t HCPB9                     : 1;
    __IO uint32_t HCPB10                    : 1;
    __IO uint32_t HCPB11                    : 1;
    __IO uint32_t HCPB12                    : 1;
    __IO uint32_t HCPB13                    : 1;
    __IO uint32_t HCPB14                    : 1;
    __IO uint32_t HCPB15                    : 1;
} stc_adt_hcpbr_field_t;

typedef struct
{
    __IO uint32_t HCUP0                     : 1;
    __IO uint32_t HCUP1                     : 1;
    __IO uint32_t HCUP2                     : 1;
    __IO uint32_t HCUP3                     : 1;
    __IO uint32_t HCUP4                     : 1;
    __IO uint32_t HCUP5                     : 1;
    __IO uint32_t HCUP6                     : 1;
    __IO uint32_t HCUP7                     : 1;
    __IO uint32_t HCUP8                     : 1;
    __IO uint32_t HCUP9                     : 1;
    __IO uint32_t HCUP10                    : 1;
    __IO uint32_t HCUP11                    : 1;
    __IO uint32_t HCUP12                    : 1;
    __IO uint32_t HCUP13                    : 1;
    __IO uint32_t HCUP14                    : 1;
    __IO uint32_t HCUP15                    : 1;
    __IO uint32_t HCUP16                    : 1;
    __IO uint32_t HCUP17                    : 1;
    __IO uint32_t HCUP18                    : 1;
    __IO uint32_t HCUP19                    : 1;
} stc_adt_hcupr_field_t;

typedef struct
{
    __IO uint32_t HCDO0                     : 1;
    __IO uint32_t HCDO1                     : 1;
    __IO uint32_t HCDO2                     : 1;
    __IO uint32_t HCDO3                     : 1;
    __IO uint32_t HCDO4                     : 1;
    __IO uint32_t HCDO5                     : 1;
    __IO uint32_t HCDO6                     : 1;
    __IO uint32_t HCDO7                     : 1;
    __IO uint32_t HCDO8                     : 1;
    __IO uint32_t HCDO9                     : 1;
    __IO uint32_t HCDO10                    : 1;
    __IO uint32_t HCDO11                    : 1;
    __IO uint32_t HCDO12                    : 1;
    __IO uint32_t HCDO13                    : 1;
    __IO uint32_t HCDO14                    : 1;
    __IO uint32_t HCDO15                    : 1;
    __IO uint32_t HCDO16                    : 1;
    __IO uint32_t HCDO17                    : 1;
    __IO uint32_t HCDO18                    : 1;
    __IO uint32_t HCDO19                    : 1;
} stc_adt_hcdor_field_t;

typedef struct
{
    __IO uint32_t CMAF                      : 1;
    __IO uint32_t CMBF                      : 1;
    __IO uint32_t CMCF                      : 1;
    __IO uint32_t CMDF                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFF                      : 1;
    __IO uint32_t UDFF                      : 1;
    __IO uint32_t DTEF                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLF                     : 1;
    __IO uint32_t SAMHF                     : 1;
} stc_adt_ifr_field_t;

typedef struct
{
    __IO uint32_t CMAC                      : 1;
    __IO uint32_t CMBC                      : 1;
    __IO uint32_t CMCC                      : 1;
    __IO uint32_t CMDC                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFC                      : 1;
    __IO uint32_t UDFC                      : 1;
    __IO uint32_t DTEC                      : 1;
    uint32_t RESERVED9                      : 5;
    __IO uint32_t SAMLC                     : 1;
    __IO uint32_t SAMHC                     : 1;
} stc_adt_iclr_field_t;

typedef struct
{
    __IO uint32_t CMAE                      : 1;
    __IO uint32_t CMBE                      : 1;
    __IO uint32_t CMCE                      : 1;
    __IO uint32_t CMDE                      : 1;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t OVFE                      : 1;
    __IO uint32_t UDFE                      : 1;
    __IO uint32_t DITENA                    : 1;
    __IO uint32_t DITENB                    : 1;
    __IO uint32_t DITENS                    : 1;
} stc_adt_cr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
    __IO uint32_t BFILTS                    : 2;
    __IO uint32_t BFILTEN                   : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t SOFTBK                    : 1;
    __IO uint32_t SML0                      : 1;
    __IO uint32_t SML1                      : 1;
    __IO uint32_t SML2                      : 1;
    __IO uint32_t SMH0                      : 1;
    __IO uint32_t SMH1                      : 1;
    __IO uint32_t SMH2                      : 1;
} stc_adt_aossr_field_t;

typedef struct
{
    __IO uint32_t FBRAKE                    : 1;
    __IO uint32_t FSAME                     : 1;
} stc_adt_aoscl_field_t;

typedef struct
{
    __IO uint32_t EN0                       : 1;
    __IO uint32_t EN1                       : 1;
    __IO uint32_t EN2                       : 1;
    __IO uint32_t EN3                       : 1;
    __IO uint32_t EN4                       : 1;
    __IO uint32_t EN5                       : 1;
    __IO uint32_t EN6                       : 1;
    __IO uint32_t EN7                       : 1;
    __IO uint32_t EN8                       : 1;
    __IO uint32_t EN9                       : 1;
    __IO uint32_t EN10                      : 1;
    __IO uint32_t EN11                      : 1;
    __IO uint32_t EN12                      : 1;
    __IO uint32_t EN13                      : 1;
    __IO uint32_t EN14                      : 1;
    __IO uint32_t EN15                      : 1;
} stc_adt_ptbks_field_t;

typedef struct
{
    __IO uint32_t TRIGAS                    : 4;
    __IO uint32_t TRIGBS                    : 4;
    __IO uint32_t TRIGCS                    : 4;
    __IO uint32_t TRIGDS                    : 4;
} stc_adt_ttrig_field_t;

typedef struct
{
    __IO uint32_t IAOS0S                    : 4;
    __IO uint32_t IAOS1S                    : 4;
    __IO uint32_t IAOS2S                    : 4;
    __IO uint32_t IAOS3S                    : 4;
} stc_adt_itrig_field_t;

typedef struct
{
    __IO uint32_t POL0                      : 1;
    __IO uint32_t POL1                      : 1;
    __IO uint32_t POL2                      : 1;
    __IO uint32_t POL3                      : 1;
    __IO uint32_t POL4                      : 1;
    __IO uint32_t POL5                      : 1;
    __IO uint32_t POL6                      : 1;
    __IO uint32_t POL7                      : 1;
    __IO uint32_t POL8                      : 1;
    __IO uint32_t POL9                      : 1;
    __IO uint32_t POL10                     : 1;
    __IO uint32_t POL11                     : 1;
    __IO uint32_t POL12                     : 1;
    __IO uint32_t POL13                     : 1;
    __IO uint32_t POL14                     : 1;
    __IO uint32_t POL15                     : 1;
} stc_adt_ptbkp_field_t;

typedef struct
{
    __IO uint32_t SSTA0                     : 1;
    __IO uint32_t SSTA1                     : 1;
    __IO uint32_t SSTA2                     : 1;
} stc_adt_sstar_field_t;

typedef struct
{
    __IO uint32_t SSTP0                     : 1;
    __IO uint32_t SSTP1                     : 1;
    __IO uint32_t SSTP2                     : 1;
} stc_adt_sstpr_field_t;

typedef struct
{
    __IO uint32_t SCLR0                     : 1;
    __IO uint32_t SCLR1                     : 1;
    __IO uint32_t SCLR2                     : 1;
} stc_adt_sclrr_field_t;

typedef struct
{
    __IO uint32_t BGR_EN                    : 1;
    __IO uint32_t TS_EN                     : 1;
} stc_bgr_cr_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_bt_arr_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_bt_cnt_field_t;

typedef struct
{
    __IO uint32_t CNT32                     :32;
} stc_bt_cnt32_field_t;

typedef struct
{
    __IO uint32_t TR                        : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOG_EN                    : 1;
    __IO uint32_t PRS                       : 3;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATE_P                    : 1;
    __IO uint32_t IE                        : 1;
} stc_bt_cr_field_t;

typedef struct
{
    __IO uint32_t TF                        : 1;
} stc_bt_ifr_field_t;

typedef struct
{
    __IO uint32_t TFC                       : 1;
} stc_bt_iclr_field_t;

typedef struct
{
    __IO uint32_t TRIM_START                : 1;
    __IO uint32_t REFCLK_SEL                : 3;
    __IO uint32_t CALCLK_SEL                : 2;
    __IO uint32_t MON_EN                    : 1;
    __IO uint32_t IE                        : 1;
} stc_clk_trim_cr_field_t;

typedef struct
{
    __IO uint32_t RCNTVAL                   :32;
} stc_clk_trim_refcon_field_t;

typedef struct
{
    __IO uint32_t REFCNT                    :32;
} stc_clk_trim_refcnt_field_t;

typedef struct
{
    __IO uint32_t CALCNT                    :32;
} stc_clk_trim_calcnt_field_t;

typedef struct
{
    __IO uint32_t STOP                      : 1;
    __IO uint32_t CALCNT_OF                 : 1;
    __IO uint32_t XTL_FAULT                 : 1;
    __IO uint32_t XTH_FAULT                 : 1;
} stc_clk_trim_ifr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 2;
    __IO uint32_t XTL_FAULT_CLR             : 1;
    __IO uint32_t XTH_FAULT_CLR             : 1;
} stc_clk_trim_iclr_field_t;

typedef struct
{
    __IO uint32_t CCNTVAL                   :32;
} stc_clk_trim_calcon_field_t;

typedef struct
{
    __IO uint32_t RCH_EN                    : 1;
    __IO uint32_t XTH_EN                    : 1;
    __IO uint32_t RCL_EN                    : 1;
    __IO uint32_t XTL_EN                    : 1;
    __IO uint32_t CLK_SW4_SEL               : 2;
    __IO uint32_t HCLK_PRS                  : 3;
    __IO uint32_t PCLK_PRS                  : 2;
    uint32_t RESERVED11                     : 4;
    __IO uint32_t WAKEUP_BYRCH              : 1;
} stc_clock_sysctrl0_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t EXTH_EN                   : 1;
    __IO uint32_t EXTL_EN                   : 1;
    __IO uint32_t XTL_ALWAYSON              : 1;
    __IO uint32_t CLOCK_FT_EN               : 1;
    __IO uint32_t RTC_LPW                   : 1;
    __IO uint32_t LOCK_EN                   : 1;
    __IO uint32_t RES_UIO                   : 1;
    __IO uint32_t SWD_UIO                   : 1;
    __IO uint32_t RTC_FREQ_ADJUST           : 3;
} stc_clock_sysctrl1_field_t;

typedef struct
{
    __IO uint32_t SYSCTRL2                  :16;
} stc_clock_sysctrl2_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :11;
    __IO uint32_t STABLE                    : 1;
} stc_clock_rch_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 4;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
} stc_clock_xth_cr_field_t;

typedef struct
{
    __IO uint32_t TRIM                      :10;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
} stc_clock_rcl_cr_field_t;

typedef struct
{
    __IO uint32_t DRIVER                    : 4;
    __IO uint32_t STARTUP                   : 2;
    __IO uint32_t STABLE                    : 1;
} stc_clock_xtl_cr_field_t;

typedef struct
{
    __IO uint32_t UART0                     : 1;
    __IO uint32_t UART1                     : 1;
    __IO uint32_t LPUART                    : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t I2C                       : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t SPI                       : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t BASETIM                   : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t ADVTIM                    : 1;
    uint32_t RESERVED11                     : 3;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t WDT                       : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VC                        : 1;
    uint32_t RESERVED18                     : 2;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t TRIM                      : 1;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t TICK                      : 1;
    uint32_t RESERVED25                     : 1;
    __IO uint32_t CRC                       : 1;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t GPIO                      : 1;
    uint32_t RESERVED29                     : 2;
    __IO uint32_t FLASH                     : 1;
} stc_clock_peri_clken_field_t;

typedef struct
{
    __IO uint32_t STCALIB                   :24;
    __IO uint32_t SKEW                      : 1;
    __IO uint32_t NOREF                     : 1;
    __IO uint32_t CLK_SEL                   : 2;
} stc_clock_systick_cr_field_t;

typedef struct
{
    __IO uint32_t TIM0                      : 1;
    __IO uint32_t TIM1                      : 1;
    __IO uint32_t TIM2                      : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t WDT                       : 1;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t TICK                      : 1;
} stc_clock_debug_active_field_t;

typedef struct
{
    __IO uint32_t RESULT                    :16;
    __IO uint32_t FLAG                      : 1;
} stc_crc_result_field_t;

typedef struct
{
    __IO uint32_t DATA                      :32;
} stc_crc_data_field_t;

typedef struct
{
    __IO uint32_t TNVS                      : 9;
} stc_flash_tnvs_field_t;

typedef struct
{
    __IO uint32_t TPGS                      : 8;
} stc_flash_tpgs_field_t;

typedef struct
{
    __IO uint32_t TPROG                     : 8;
} stc_flash_tprog_field_t;

typedef struct
{
    __IO uint32_t TSERASE                   :18;
} stc_flash_tserase_field_t;

typedef struct
{
    __IO uint32_t TMERASE                   :21;
} stc_flash_tmerase_field_t;

typedef struct
{
    __IO uint32_t TPRCV                     :12;
} stc_flash_tprcv_field_t;

typedef struct
{
    __IO uint32_t TSRCV                     :12;
} stc_flash_tsrcv_field_t;

typedef struct
{
    __IO uint32_t TMRCV                     :13;
} stc_flash_tmrcv_field_t;

typedef struct
{
    __IO uint32_t OP                        : 2;
    __IO uint32_t WAIT                      : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t BUSY                      : 1;
    __IO uint32_t IE                        : 2;
} stc_flash_cr_field_t;

typedef struct
{
    __IO uint32_t IF0                       : 1;
    __IO uint32_t IF1                       : 1;
} stc_flash_ifr_field_t;

typedef struct
{
    __IO uint32_t ICLR0                     : 1;
    __IO uint32_t ICLR1                     : 1;
} stc_flash_iclr_field_t;

typedef struct
{
    __IO uint32_t BYSEQ                     :16;
} stc_flash_bypass_field_t;

typedef struct
{
    __IO uint32_t SLOCK                     :16;
} stc_flash_slock_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p01_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p02_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p03_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p14_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p15_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p23_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p24_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p25_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p26_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p27_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p31_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p32_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p33_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p34_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p35_sel_field_t;

typedef struct
{
    __IO uint32_t SEL                       : 3;
} stc_gpio_p36_sel_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0dir_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0in_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0out_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0ads_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0dr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0pu_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0pd_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0od_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0hie_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0lie_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0rie_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0fie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1dir_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1in_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1out_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1ads_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1dr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1pu_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1pd_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1od_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1hie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1lie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1rie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1fie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2dir_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2in_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2out_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2ads_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2dr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2pu_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2pd_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2od_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2hie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2lie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2rie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2fie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3dir_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3in_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3out_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3ads_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3dr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3pu_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3pd_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3od_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3hie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3lie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3rie_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3fie_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0stat_field_t;

typedef struct
{
    __IO uint32_t P00                       : 1;
    __IO uint32_t P01                       : 1;
    __IO uint32_t P02                       : 1;
    __IO uint32_t P03                       : 1;
} stc_gpio_p0iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1stat_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t P14                       : 1;
    __IO uint32_t P15                       : 1;
} stc_gpio_p1iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2stat_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 3;
    __IO uint32_t P23                       : 1;
    __IO uint32_t P24                       : 1;
    __IO uint32_t P25                       : 1;
    __IO uint32_t P26                       : 1;
    __IO uint32_t P27                       : 1;
} stc_gpio_p2iclr_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3stat_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t P31                       : 1;
    __IO uint32_t P32                       : 1;
    __IO uint32_t P33                       : 1;
    __IO uint32_t P34                       : 1;
    __IO uint32_t P35                       : 1;
    __IO uint32_t P36                       : 1;
} stc_gpio_p3iclr_field_t;

typedef struct
{
    __IO uint32_t IESEL                     : 1;
} stc_gpio_ctrl0_field_t;

typedef struct
{
    __IO uint32_t EXT_CLK_SEL               : 4;
    __IO uint32_t SSN_SEL                   : 4;
    __IO uint32_t PCLK_SEL                  : 2;
    __IO uint32_t HCLK_SEL                  : 2;
    __IO uint32_t PCLK_EN                   : 1;
    __IO uint32_t HCLK_EN                   : 1;
    __IO uint32_t IR_POL                    : 1;
} stc_gpio_ctrl1_field_t;

typedef struct
{
    __IO uint32_t PCA_CAP0_SEL              : 2;
    __IO uint32_t PCA_CAP1_SEL              : 2;
    __IO uint32_t PCA_CAP2_SEL              : 2;
    __IO uint32_t PCA_CAP3_SEL              : 2;
    __IO uint32_t PCA_CAP4_SEL              : 2;
} stc_gpio_ctrl2_field_t;

typedef struct
{
    __IO uint32_t TM4_B_SEL                 : 2;
    __IO uint32_t TM5_B_SEL                 : 2;
    __IO uint32_t TM6_B_SEL                 : 2;
    __IO uint32_t TM4_A_SEL                 : 2;
    __IO uint32_t TM5_A_SEL                 : 2;
    __IO uint32_t TM6_A_SEL                 : 2;
} stc_gpio_ctrl3_field_t;

typedef struct
{
    __IO uint32_t TM0_GATE_SEL              : 2;
    __IO uint32_t TM1_GATE_SEL              : 2;
    __IO uint32_t TM2_GATE_SEL              : 2;
    __IO uint32_t TM3_GATE_SEL              : 2;
} stc_gpio_ctrl4_field_t;

typedef struct
{
    __IO uint32_t TME                       : 1;
} stc_i2c_tmrun_field_t;

typedef struct
{
    __IO uint32_t TM                        : 8;
} stc_i2c_tm_field_t;

typedef struct
{
    __IO uint32_t H1M                       : 1;
    uint32_t RESERVED1                      : 1;
    __IO uint32_t AA                        : 1;
    __IO uint32_t SI                        : 1;
    __IO uint32_t STO                       : 1;
    __IO uint32_t STA                       : 1;
    __IO uint32_t ENS                       : 1;
} stc_i2c_cr_field_t;

typedef struct
{
    __IO uint32_t I2CDAT                    : 8;
} stc_i2c_data_field_t;

typedef struct
{
    __IO uint32_t GC                        : 1;
    __IO uint32_t I2CADR                    : 7;
} stc_i2c_addr_field_t;

typedef struct
{
    __IO uint32_t I2CSTA                    : 8;
} stc_i2c_stat_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_lptimer_cnt_field_t;

typedef struct
{
    __IO uint32_t ARR                       :16;
} stc_lptimer_arr_field_t;

typedef struct
{
    __IO uint32_t TR                        : 1;
    __IO uint32_t MD                        : 1;
    __IO uint32_t CT                        : 1;
    __IO uint32_t TOG_EN                    : 1;
    __IO uint32_t TCK_SEL                   : 2;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t WT_FLAG                   : 1;
    __IO uint32_t GATE                      : 1;
    __IO uint32_t GATE_P                    : 1;
    __IO uint32_t IE                        : 1;
} stc_lptimer_cr_field_t;

typedef struct
{
    __IO uint32_t TF                        : 1;
} stc_lptimer_ifr_field_t;

typedef struct
{
    __IO uint32_t TFC                       : 1;
} stc_lptimer_iclr_field_t;

typedef struct
{
    __IO uint32_t SBUF                      : 8;
} stc_lpuart_sbuf_field_t;

typedef struct
{
    __IO uint32_t RIEN                      : 1;
    __IO uint32_t TIEN                      : 1;
    __IO uint32_t RB8                       : 1;
    __IO uint32_t TB8                       : 1;
    __IO uint32_t REN                       : 1;
    __IO uint32_t SM2                       : 1;
    __IO uint32_t SM01                      : 2;
    __IO uint32_t TEEN                      : 1;
    __IO uint32_t DBAUD                     : 1;
    __IO uint32_t LPMODE                    : 1;
    __IO uint32_t SCLKSEL                   : 2;
    __IO uint32_t PRS                       : 3;
} stc_lpuart_scon_field_t;

typedef struct
{
    __IO uint32_t SADDR                     : 8;
} stc_lpuart_saddr_field_t;

typedef struct
{
    __IO uint32_t SADEN                     : 8;
} stc_lpuart_saden_field_t;

typedef struct
{
    __IO uint32_t RI                        : 1;
    __IO uint32_t TI                        : 1;
    __IO uint32_t FE                        : 1;
    __IO uint32_t TE                        : 1;
} stc_lpuart_isr_field_t;

typedef struct
{
    __IO uint32_t RICLR                     : 1;
    __IO uint32_t TICLR                     : 1;
    __IO uint32_t FECLR                     : 1;
} stc_lpuart_icr_field_t;

typedef struct
{
    __IO uint32_t LVDEN                     : 1;
    __IO uint32_t ACT                       : 1;
    __IO uint32_t SOURCE_SEL                : 2;
    __IO uint32_t VTDS                      : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FTEN                      : 1;
    __IO uint32_t RTEN                      : 1;
    __IO uint32_t HTEN                      : 1;
    __IO uint32_t IE                        : 1;
} stc_lvd_cr_field_t;

typedef struct
{
    __IO uint32_t INTF                      : 1;
} stc_lvd_ifr_field_t;

typedef struct
{
    __IO uint32_t CCF0                      : 1;
    __IO uint32_t CCF1                      : 1;
    __IO uint32_t CCF2                      : 1;
    __IO uint32_t CCF3                      : 1;
    __IO uint32_t CCF4                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t CR                        : 1;
    __IO uint32_t CF                        : 1;
} stc_pca_ccon_field_t;

typedef struct
{
    __IO uint32_t CFIE                      : 1;
    __IO uint32_t CPS                       : 3;
    uint32_t RESERVED4                      : 2;
    __IO uint32_t WDTE                      : 1;
    __IO uint32_t CIDL                      : 1;
} stc_pca_cmod_field_t;

typedef struct
{
    __IO uint32_t CNT                       :16;
} stc_pca_cnt_field_t;

typedef struct
{
    __IO uint32_t CCF0                      : 1;
    __IO uint32_t CCF1                      : 1;
    __IO uint32_t CCF2                      : 1;
    __IO uint32_t CCF3                      : 1;
    __IO uint32_t CCF4                      : 1;
    uint32_t RESERVED5                      : 2;
    __IO uint32_t CF                        : 1;
} stc_pca_iclr_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm0_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm1_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm2_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm3_field_t;

typedef struct
{
    __IO uint32_t CCIE                      : 1;
    __IO uint32_t PWM                       : 1;
    __IO uint32_t TOG                       : 1;
    __IO uint32_t MAT                       : 1;
    __IO uint32_t CAPN                      : 1;
    __IO uint32_t CAPP                      : 1;
    __IO uint32_t ECOM                      : 1;
} stc_pca_ccapm4_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     : 8;
} stc_pca_ccap0h_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     : 8;
} stc_pca_ccap0l_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     : 8;
} stc_pca_ccap1h_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     : 8;
} stc_pca_ccap1l_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     : 8;
} stc_pca_ccap2h_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     : 8;
} stc_pca_ccap2l_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     : 8;
} stc_pca_ccap3h_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     : 8;
} stc_pca_ccap3l_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     : 8;
} stc_pca_ccap4h_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     : 8;
} stc_pca_ccap4l_field_t;

typedef struct
{
    __IO uint32_t CCAPO0                    : 1;
    __IO uint32_t CCAPO1                    : 1;
    __IO uint32_t CCAPO2                    : 1;
    __IO uint32_t CCAPO3                    : 1;
    __IO uint32_t CCAPO4                    : 1;
} stc_pca_ccapo_field_t;

typedef struct
{
    __IO uint32_t CCAP0                     :16;
} stc_pca_ccap0_field_t;

typedef struct
{
    __IO uint32_t CCAP1                     :16;
} stc_pca_ccap1_field_t;

typedef struct
{
    __IO uint32_t CCAP2                     :16;
} stc_pca_ccap2_field_t;

typedef struct
{
    __IO uint32_t CCAP3                     :16;
} stc_pca_ccap3_field_t;

typedef struct
{
    __IO uint32_t CCAP4                     :16;
} stc_pca_ccap4_field_t;

typedef struct
{
    __IO uint32_t CHKEN                     : 1;
    __IO uint32_t IE                        : 1;
} stc_ram_cr_field_t;

typedef struct
{
    __IO uint32_t ERRADDR                   :12;
} stc_ram_erraddr_field_t;

typedef struct
{
    __IO uint32_t ERR                       : 1;
} stc_ram_ifr_field_t;

typedef struct
{
    __IO uint32_t ERRCLR                    : 1;
} stc_ram_iclr_field_t;

typedef struct
{
    __IO uint32_t POR5V                     : 1;
    __IO uint32_t POR15V                    : 1;
    __IO uint32_t LVD                       : 1;
    __IO uint32_t WDT                       : 1;
    __IO uint32_t PCA                       : 1;
    __IO uint32_t LOCKUP                    : 1;
    __IO uint32_t SYSREQ                    : 1;
    __IO uint32_t RSTB                      : 1;
} stc_reset_reset_flag_field_t;

typedef struct
{
    __IO uint32_t UART0                     : 1;
    __IO uint32_t UART1                     : 1;
    __IO uint32_t LPUART                    : 1;
    uint32_t RESERVED3                      : 1;
    __IO uint32_t I2C                       : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t SPI                       : 1;
    uint32_t RESERVED7                      : 1;
    __IO uint32_t BASETIM                   : 1;
    __IO uint32_t LPTIM                     : 1;
    __IO uint32_t ADVTIM                    : 1;
    uint32_t RESERVED11                     : 3;
    __IO uint32_t PCA                       : 1;
    uint32_t RESERVED15                     : 1;
    __IO uint32_t ADC                       : 1;
    __IO uint32_t VC                        : 1;
    uint32_t RESERVED18                     : 2;
    __IO uint32_t RTC                       : 1;
    __IO uint32_t TRIM                      : 1;
    uint32_t RESERVED22                     : 2;
    __IO uint32_t TICK                      : 1;
    uint32_t RESERVED25                     : 1;
    __IO uint32_t CRC                       : 1;
    uint32_t RESERVED27                     : 1;
    __IO uint32_t GPIO                      : 1;
} stc_reset_prei_reset_field_t;

typedef struct
{
    __IO uint32_t PRDS                      : 3;
    __IO uint32_t AMPM                      : 1;
    uint32_t RESERVED4                      : 1;
    __IO uint32_t HZ1OE                     : 1;
    __IO uint32_t HZ1SEL                    : 1;
    __IO uint32_t START                     : 1;
    __IO uint32_t PRDX                      : 6;
    __IO uint32_t PRDSEL                    : 1;
} stc_rtc_cr0_field_t;

typedef struct
{
    __IO uint32_t WAIT                      : 1;
    __IO uint32_t WAITF                     : 1;
    uint32_t RESERVED2                      : 1;
    __IO uint32_t PRDF                      : 1;
    __IO uint32_t ALMF                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t ALMIE                     : 1;
    __IO uint32_t ALMEN                     : 1;
    __IO uint32_t CKSEL                     : 3;
} stc_rtc_cr1_field_t;

typedef struct
{
    __IO uint32_t SECL                      : 4;
    __IO uint32_t SECH                      : 3;
} stc_rtc_sec_field_t;

typedef struct
{
    __IO uint32_t MINL                      : 4;
    __IO uint32_t MINH                      : 3;
} stc_rtc_min_field_t;

typedef struct
{
    __IO uint32_t HOURL                     : 4;
    __IO uint32_t HOURH                     : 2;
} stc_rtc_hour_field_t;

typedef struct
{
    __IO uint32_t WEEK                      : 3;
} stc_rtc_week_field_t;

typedef struct
{
    __IO uint32_t DAYL                      : 4;
    __IO uint32_t DAYH                      : 2;
} stc_rtc_day_field_t;

typedef struct
{
    __IO uint32_t MON                       : 5;
} stc_rtc_mon_field_t;

typedef struct
{
    __IO uint32_t YEARL                     : 4;
    __IO uint32_t YEARH                     : 4;
} stc_rtc_year_field_t;

typedef struct
{
    __IO uint32_t ALMMINL                   : 4;
    __IO uint32_t ALMMINH                   : 3;
} stc_rtc_almmin_field_t;

typedef struct
{
    __IO uint32_t ALMHOURL                  : 4;
    __IO uint32_t ALMHOURH                  : 2;
} stc_rtc_almhour_field_t;

typedef struct
{
    __IO uint32_t ALMWEEK                   : 7;
} stc_rtc_almweek_field_t;

typedef struct
{
    __IO uint32_t CR                        : 9;
    uint32_t RESERVED9                      : 6;
    __IO uint32_t EN                        : 1;
} stc_rtc_compen_field_t;

typedef struct
{
    __IO uint32_t SPR0                      : 1;
    __IO uint32_t SPR1                      : 1;
    __IO uint32_t CPHA                      : 1;
    __IO uint32_t CPOL                      : 1;
    __IO uint32_t MSTR                      : 1;
    uint32_t RESERVED5                      : 1;
    __IO uint32_t SPEN                      : 1;
    __IO uint32_t SPR2                      : 1;
} stc_spi_cr_field_t;

typedef struct
{
    __IO uint32_t SSN                       : 1;
} stc_spi_ssn_field_t;

typedef struct
{
    uint32_t RESERVED0                      : 4;
    __IO uint32_t MDF                       : 1;
    __IO uint32_t SSERR                     : 1;
    __IO uint32_t WCOL                      : 1;
    __IO uint32_t SPIF                      : 1;
} stc_spi_stat_field_t;

typedef struct
{
    __IO uint32_t SPDAT                     : 8;
} stc_spi_data_field_t;

typedef struct
{
    __IO uint32_t SBUF                      : 8;
} stc_uart_sbuf_field_t;

typedef struct
{
    __IO uint32_t RIEN                      : 1;
    __IO uint32_t TIEN                      : 1;
    __IO uint32_t RB8                       : 1;
    __IO uint32_t TB8                       : 1;
    __IO uint32_t REN                       : 1;
    __IO uint32_t SM2                       : 1;
    __IO uint32_t SM01                      : 2;
    uint32_t RESERVED8                      : 1;
    __IO uint32_t DBAUD                     : 1; /* Double baudrate, 0:single, 1:double */
} stc_uart_scon_field_t;

typedef struct
{
    __IO uint32_t SADDR                     : 8;
} stc_uart_saddr_field_t;

typedef struct
{
    __IO uint32_t SADEN                     : 8;
} stc_uart_saden_field_t;

typedef struct
{
    __IO uint32_t RI                        : 1; // Rx Interrupt
    __IO uint32_t TI                        : 1; // Tx Interrupt
    __IO uint32_t FE                        : 1; // Frame Error Interrupt
    __IO uint32_t TE                        : 1;
} stc_uart_isr_field_t;

typedef struct
{
    __IO uint32_t RICLR                     : 1;
    __IO uint32_t TICLR                     : 1;
    __IO uint32_t FECLR                     : 1;
} stc_uart_icr_field_t;

typedef struct
{
    __IO uint32_t DIV                       : 6;
    __IO uint32_t DIV_EN                    : 1;
    __IO uint32_t REF2P5_SEL                : 1;
    __IO uint32_t VC0_BIAS_SEL              : 2;
    __IO uint32_t VC0_HYS_SEL               : 2;
    __IO uint32_t VC1_BIAS_SEL              : 2;
    __IO uint32_t VC1_HYS_SEL               : 2;
} stc_vc_cr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t P_SEL                     : 3;
    __IO uint32_t N_SEL                     : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
} stc_vc_vc0_cr_field_t;

typedef struct
{
    __IO uint32_t EN                        : 1;
    __IO uint32_t P_SEL                     : 3;
    __IO uint32_t N_SEL                     : 4;
    __IO uint32_t FLTEN                     : 1;
    __IO uint32_t DEBOUNCE_TIME             : 3;
    __IO uint32_t FALLING                   : 1;
    __IO uint32_t RISING                    : 1;
    __IO uint32_t LEVEL                     : 1;
    __IO uint32_t IE                        : 1;
} stc_vc_vc1_cr_field_t;

typedef struct
{
    __IO uint32_t INV_TIMER                 : 1;
    __IO uint32_t TIM0G                     : 1;
    __IO uint32_t TIM1G                     : 1;
    __IO uint32_t TIM2G                     : 1;
    __IO uint32_t TIM3G                     : 1;
    __IO uint32_t TIM3ECLK                  : 1;
    __IO uint32_t INV_PCA                   : 1;
    __IO uint32_t PCACAP0                   : 1;
    __IO uint32_t PCAECI                    : 1;
    __IO uint32_t INV_TIM4                  : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t INV_TIM5                  : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t INV_TIM6                  : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t BRAKE                     : 1;
} stc_vc_vc0_out_cfg_field_t;

typedef struct
{
    __IO uint32_t INV_TIMER                 : 1;
    __IO uint32_t TIM0G                     : 1;
    __IO uint32_t TIM1G                     : 1;
    __IO uint32_t TIM2G                     : 1;
    __IO uint32_t TIM3G                     : 1;
    __IO uint32_t TIM3ECLK                  : 1;
    __IO uint32_t INV_PCA                   : 1;
    __IO uint32_t PCACAP0                   : 1;
    __IO uint32_t PCAECI                    : 1;
    __IO uint32_t INV_TIM4                  : 1;
    __IO uint32_t TIM4                      : 1;
    __IO uint32_t INV_TIM5                  : 1;
    __IO uint32_t TIM5                      : 1;
    __IO uint32_t INV_TIM6                  : 1;
    __IO uint32_t TIM6                      : 1;
    __IO uint32_t BRAKE                     : 1;
} stc_vc_vc1_out_cfg_field_t;

typedef struct
{
    __IO uint32_t VC0_INTF                  : 1;
    __IO uint32_t VC1_INTF                  : 1;
    __IO uint32_t VC0_FILTER                : 1;
    __IO uint32_t VC1_FILTER                : 1;
} stc_vc_ifr_field_t;

typedef struct
{
    __IO uint32_t WDTRST                    : 8;
} stc_wdt_rst_field_t;

typedef struct
{
    __IO uint32_t WOV                       : 4;
    __IO uint32_t WDTR                      : 1;
    __IO uint32_t WINT_EN                   : 1;
    uint32_t RESERVED6                      : 1;
    __IO uint32_t WDINT                     : 1;
    __IO uint32_t WCNTL                     : 8;
} stc_wdt_con_field_t;


typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t CR0;
        stc_adc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_adc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        stc_adc_cr2_field_t CR2_f;
    };
    uint8_t RESERVED3[32];
    union
    {
        __IO uint32_t RESULT0;
        stc_adc_result0_field_t RESULT0_f;
    };
    union
    {
        __IO uint32_t RESULT1;
        stc_adc_result1_field_t RESULT1_f;
    };
    union
    {
        __IO uint32_t RESULT2;
        stc_adc_result2_field_t RESULT2_f;
    };
    union
    {
        __IO uint32_t RESULT3;
        stc_adc_result3_field_t RESULT3_f;
    };
    union
    {
        __IO uint32_t RESULT4;
        stc_adc_result4_field_t RESULT4_f;
    };
    union
    {
        __IO uint32_t RESULT5;
        stc_adc_result5_field_t RESULT5_f;
    };
    union
    {
        __IO uint32_t RESULT6;
        stc_adc_result6_field_t RESULT6_f;
    };
    union
    {
        __IO uint32_t RESULT7;
        stc_adc_result7_field_t RESULT7_f;
    };
    union
    {
        __IO uint32_t RESULT8;
        stc_adc_result8_field_t RESULT8_f;
    };
    union
    {
        __IO uint32_t RESULT_ACC;
        stc_adc_result_acc_field_t RESULT_ACC_f;
    };
    union
    {
        __IO uint32_t HT;
        stc_adc_ht_field_t HT_f;
    };
    union
    {
        __IO uint32_t LT;
        stc_adc_lt_field_t LT_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_adc_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_adc_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t RESULT;
        stc_adc_result_field_t RESULT_f;
    };
}M0P_ADC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CNTER;
        stc_adt_cnter_field_t CNTER_f;
    };
    union
    {
        __IO uint32_t PERAR;
        stc_adt_perar_field_t PERAR_f;
    };
    union
    {
        __IO uint32_t PERBR;
        stc_adt_perbr_field_t PERBR_f;
    };
    uint8_t RESERVED3[4];
    union
    {
        __IO uint32_t GCMAR;
        stc_adt_gcmar_field_t GCMAR_f;
    };
    union
    {
        __IO uint32_t GCMBR;
        stc_adt_gcmbr_field_t GCMBR_f;
    };
    union
    {
        __IO uint32_t GCMCR;
        stc_adt_gcmcr_field_t GCMCR_f;
    };
    union
    {
        __IO uint32_t GCMDR;
        stc_adt_gcmdr_field_t GCMDR_f;
    };
    uint8_t RESERVED7[32];
    union
    {
        __IO uint32_t DTUAR;
        stc_adt_dtuar_field_t DTUAR_f;
    };
    union
    {
        __IO uint32_t DTDAR;
        stc_adt_dtdar_field_t DTDAR_f;
    };
    uint8_t RESERVED9[8];
    union
    {
        __IO uint32_t GCONR;
        stc_adt_gconr_field_t GCONR_f;
    };
    union
    {
        __IO uint32_t ICONR;
        stc_adt_iconr_field_t ICONR_f;
    };
    union
    {
        __IO uint32_t PCONR;
        stc_adt_pconr_field_t PCONR_f;
    };
    union
    {
        __IO uint32_t BCONR;
        stc_adt_bconr_field_t BCONR_f;
    };
    union
    {
        __IO uint32_t DCONR;
        stc_adt_dconr_field_t DCONR_f;
    };
    uint8_t RESERVED14[4];
    union
    {
        __IO uint32_t FCONR;
        stc_adt_fconr_field_t FCONR_f;
    };
    union
    {
        __IO uint32_t VPERR;
        stc_adt_vperr_field_t VPERR_f;
    };
    union
    {
        __IO uint32_t STFLR;
        stc_adt_stflr_field_t STFLR_f;
    };
    union
    {
        __IO uint32_t HSTAR;
        stc_adt_hstar_field_t HSTAR_f;
    };
    union
    {
        __IO uint32_t HSTPR;
        stc_adt_hstpr_field_t HSTPR_f;
    };
    union
    {
        __IO uint32_t HCELR;
        stc_adt_hcelr_field_t HCELR_f;
    };
    union
    {
        __IO uint32_t HCPAR;
        stc_adt_hcpar_field_t HCPAR_f;
    };
    union
    {
        __IO uint32_t HCPBR;
        stc_adt_hcpbr_field_t HCPBR_f;
    };
    union
    {
        __IO uint32_t HCUPR;
        stc_adt_hcupr_field_t HCUPR_f;
    };
    union
    {
        __IO uint32_t HCDOR;
        stc_adt_hcdor_field_t HCDOR_f;
    };
    uint8_t RESERVED24[112];
    union
    {
        __IO uint32_t IFR;
        stc_adt_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_adt_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_adt_cr_field_t CR_f;
    };
    uint8_t RESERVED27[4];
    union
    {
        __IO uint32_t AOSSR;
        stc_adt_aossr_field_t AOSSR_f;
    };
    union
    {
        __IO uint32_t AOSCL;
        stc_adt_aoscl_field_t AOSCL_f;
    };
    union
    {
        __IO uint32_t PTBKS;
        stc_adt_ptbks_field_t PTBKS_f;
    };
    union
    {
        __IO uint32_t TTRIG;
        stc_adt_ttrig_field_t TTRIG_f;
    };
    union
    {
        __IO uint32_t ITRIG;
        stc_adt_itrig_field_t ITRIG_f;
    };
    union
    {
        __IO uint32_t PTBKP;
        stc_adt_ptbkp_field_t PTBKP_f;
    };
    uint8_t RESERVED33[716];
    union
    {
        __IO uint32_t SSTAR;
        stc_adt_sstar_field_t SSTAR_f;
    };
    union
    {
        __IO uint32_t SSTPR;
        stc_adt_sstpr_field_t SSTPR_f;
    };
    union
    {
        __IO uint32_t SCLRR;
        stc_adt_sclrr_field_t SCLRR_f;
    };
}M0P_ADT_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_bgr_cr_field_t CR_f;
    };
}M0P_BGR_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t ARR;
        stc_bt_arr_field_t ARR_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_bt_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t CNT32;
        stc_bt_cnt32_field_t CNT32_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_bt_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_bt_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_bt_iclr_field_t ICLR_f;
    };
}M0P_BT_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_clk_trim_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t REFCON;
        stc_clk_trim_refcon_field_t REFCON_f;
    };
    union
    {
        __IO uint32_t REFCNT;
        stc_clk_trim_refcnt_field_t REFCNT_f;
    };
    union
    {
        __IO uint32_t CALCNT;
        stc_clk_trim_calcnt_field_t CALCNT_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_clk_trim_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_clk_trim_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CALCON;
        stc_clk_trim_calcon_field_t CALCON_f;
    };
}M0P_CLK_TRIM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SYSCTRL0;
        stc_clock_sysctrl0_field_t SYSCTRL0_f;
    };
    union
    {
        __IO uint32_t SYSCTRL1;
        stc_clock_sysctrl1_field_t SYSCTRL1_f;
    };
    union
    {
        __IO uint32_t SYSCTRL2;
        stc_clock_sysctrl2_field_t SYSCTRL2_f;
    };
    union
    {
        __IO uint32_t RCH_CR;
        stc_clock_rch_cr_field_t RCH_CR_f;
    };
    union
    {
        __IO uint32_t XTH_CR;
        stc_clock_xth_cr_field_t XTH_CR_f;
    };
    union
    {
        __IO uint32_t RCL_CR;
        stc_clock_rcl_cr_field_t RCL_CR_f;
    };
    union
    {
        __IO uint32_t XTL_CR;
        stc_clock_xtl_cr_field_t XTL_CR_f;
    };
    uint8_t RESERVED7[4];
    union
    {
        __IO uint32_t PERI_CLKEN;
        stc_clock_peri_clken_field_t PERI_CLKEN_f;
    };
    uint8_t RESERVED8[16];
    union
    {
        __IO uint32_t SYSTICK_CR;
        stc_clock_systick_cr_field_t SYSTICK_CR_f;
    };
    union
    {
        __IO uint32_t DEBUG_ACTIVE;
        stc_clock_debug_active_field_t DEBUG_ACTIVE_f;
    };
}M0P_CLOCK_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t RESULT;
        stc_crc_result_field_t RESULT_f;
    };
    uint8_t RESERVED1[120];
    union
    {
        __IO uint32_t DATA;
        stc_crc_data_field_t DATA_f;
    };
}M0P_CRC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t TNVS;
        stc_flash_tnvs_field_t TNVS_f;
    };
    union
    {
        __IO uint32_t TPGS;
        stc_flash_tpgs_field_t TPGS_f;
    };
    union
    {
        __IO uint32_t TPROG;
        stc_flash_tprog_field_t TPROG_f;
    };
    union
    {
        __IO uint32_t TSERASE;
        stc_flash_tserase_field_t TSERASE_f;
    };
    union
    {
        __IO uint32_t TMERASE;
        stc_flash_tmerase_field_t TMERASE_f;
    };
    union
    {
        __IO uint32_t TPRCV;
        stc_flash_tprcv_field_t TPRCV_f;
    };
    union
    {
        __IO uint32_t TSRCV;
        stc_flash_tsrcv_field_t TSRCV_f;
    };
    union
    {
        __IO uint32_t TMRCV;
        stc_flash_tmrcv_field_t TMRCV_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_flash_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_flash_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_flash_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t BYPASS;
        stc_flash_bypass_field_t BYPASS_f;
    };
    union
    {
        __IO uint32_t SLOCK;
        stc_flash_slock_field_t SLOCK_f;
    };
}M0P_FLASH_TypeDef;

typedef struct
{
    uint8_t RESERVED0[4];
    union
    {
        __IO uint32_t P01_SEL;
        stc_gpio_p01_sel_field_t P01_SEL_f;
    };
    union
    {
        __IO uint32_t P02_SEL;
        stc_gpio_p02_sel_field_t P02_SEL_f;
    };
    union
    {
        __IO uint32_t P03_SEL;
        stc_gpio_p03_sel_field_t P03_SEL_f;
    };
    uint8_t RESERVED3[64];
    union
    {
        __IO uint32_t P14_SEL;
        stc_gpio_p14_sel_field_t P14_SEL_f;
    };
    union
    {
        __IO uint32_t P15_SEL;
        stc_gpio_p15_sel_field_t P15_SEL_f;
    };
    uint8_t RESERVED5[52];
    union
    {
        __IO uint32_t P23_SEL;
        stc_gpio_p23_sel_field_t P23_SEL_f;
    };
    union
    {
        __IO uint32_t P24_SEL;
        stc_gpio_p24_sel_field_t P24_SEL_f;
    };
    union
    {
        __IO uint32_t P25_SEL;
        stc_gpio_p25_sel_field_t P25_SEL_f;
    };
    union
    {
        __IO uint32_t P26_SEL;
        stc_gpio_p26_sel_field_t P26_SEL_f;
    };
    union
    {
        __IO uint32_t P27_SEL;
        stc_gpio_p27_sel_field_t P27_SEL_f;
    };
    uint8_t RESERVED10[36];
    union
    {
        __IO uint32_t P31_SEL;
        stc_gpio_p31_sel_field_t P31_SEL_f;
    };
    union
    {
        __IO uint32_t P32_SEL;
        stc_gpio_p32_sel_field_t P32_SEL_f;
    };
    union
    {
        __IO uint32_t P33_SEL;
        stc_gpio_p33_sel_field_t P33_SEL_f;
    };
    union
    {
        __IO uint32_t P34_SEL;
        stc_gpio_p34_sel_field_t P34_SEL_f;
    };
    union
    {
        __IO uint32_t P35_SEL;
        stc_gpio_p35_sel_field_t P35_SEL_f;
    };
    union
    {
        __IO uint32_t P36_SEL;
        stc_gpio_p36_sel_field_t P36_SEL_f;
    };
    uint8_t RESERVED16[36];
    union
    {
        __IO uint32_t P0DIR;
        stc_gpio_p0dir_field_t P0DIR_f;
    };
    union
    {
        __IO uint32_t P0IN;
        stc_gpio_p0in_field_t P0IN_f;
    };
    union
    {
        __IO uint32_t P0OUT;
        stc_gpio_p0out_field_t P0OUT_f;
    };
    union
    {
        __IO uint32_t P0ADS;
        stc_gpio_p0ads_field_t P0ADS_f;
    };
    uint8_t RESERVED20[12];
    union
    {
        __IO uint32_t P0DR;
        stc_gpio_p0dr_field_t P0DR_f;
    };
    union
    {
        __IO uint32_t P0PU;
        stc_gpio_p0pu_field_t P0PU_f;
    };
    union
    {
        __IO uint32_t P0PD;
        stc_gpio_p0pd_field_t P0PD_f;
    };
    uint8_t RESERVED23[4];
    union
    {
        __IO uint32_t P0OD;
        stc_gpio_p0od_field_t P0OD_f;
    };
    union
    {
        __IO uint32_t P0HIE;
        stc_gpio_p0hie_field_t P0HIE_f;
    };
    union
    {
        __IO uint32_t P0LIE;
        stc_gpio_p0lie_field_t P0LIE_f;
    };
    union
    {
        __IO uint32_t P0RIE;
        stc_gpio_p0rie_field_t P0RIE_f;
    };
    union
    {
        __IO uint32_t P0FIE;
        stc_gpio_p0fie_field_t P0FIE_f;
    };
    union
    {
        __IO uint32_t P1DIR;
        stc_gpio_p1dir_field_t P1DIR_f;
    };
    union
    {
        __IO uint32_t P1IN;
        stc_gpio_p1in_field_t P1IN_f;
    };
    union
    {
        __IO uint32_t P1OUT;
        stc_gpio_p1out_field_t P1OUT_f;
    };
    union
    {
        __IO uint32_t P1ADS;
        stc_gpio_p1ads_field_t P1ADS_f;
    };
    uint8_t RESERVED32[12];
    union
    {
        __IO uint32_t P1DR;
        stc_gpio_p1dr_field_t P1DR_f;
    };
    union
    {
        __IO uint32_t P1PU;
        stc_gpio_p1pu_field_t P1PU_f;
    };
    union
    {
        __IO uint32_t P1PD;
        stc_gpio_p1pd_field_t P1PD_f;
    };
    uint8_t RESERVED35[4];
    union
    {
        __IO uint32_t P1OD;
        stc_gpio_p1od_field_t P1OD_f;
    };
    union
    {
        __IO uint32_t P1HIE;
        stc_gpio_p1hie_field_t P1HIE_f;
    };
    union
    {
        __IO uint32_t P1LIE;
        stc_gpio_p1lie_field_t P1LIE_f;
    };
    union
    {
        __IO uint32_t P1RIE;
        stc_gpio_p1rie_field_t P1RIE_f;
    };
    union
    {
        __IO uint32_t P1FIE;
        stc_gpio_p1fie_field_t P1FIE_f;
    };
    union
    {
        __IO uint32_t P2DIR;
        stc_gpio_p2dir_field_t P2DIR_f;
    };
    union
    {
        __IO uint32_t P2IN;
        stc_gpio_p2in_field_t P2IN_f;
    };
    union
    {
        __IO uint32_t P2OUT;
        stc_gpio_p2out_field_t P2OUT_f;
    };
    union
    {
        __IO uint32_t P2ADS;
        stc_gpio_p2ads_field_t P2ADS_f;
    };
    uint8_t RESERVED44[12];
    union
    {
        __IO uint32_t P2DR;
        stc_gpio_p2dr_field_t P2DR_f;
    };
    union
    {
        __IO uint32_t P2PU;
        stc_gpio_p2pu_field_t P2PU_f;
    };
    union
    {
        __IO uint32_t P2PD;
        stc_gpio_p2pd_field_t P2PD_f;
    };
    uint8_t RESERVED47[4];
    union
    {
        __IO uint32_t P2OD;
        stc_gpio_p2od_field_t P2OD_f;
    };
    union
    {
        __IO uint32_t P2HIE;
        stc_gpio_p2hie_field_t P2HIE_f;
    };
    union
    {
        __IO uint32_t P2LIE;
        stc_gpio_p2lie_field_t P2LIE_f;
    };
    union
    {
        __IO uint32_t P2RIE;
        stc_gpio_p2rie_field_t P2RIE_f;
    };
    union
    {
        __IO uint32_t P2FIE;
        stc_gpio_p2fie_field_t P2FIE_f;
    };
    union
    {
        __IO uint32_t P3DIR;
        stc_gpio_p3dir_field_t P3DIR_f;
    };
    union
    {
        __IO uint32_t P3IN;
        stc_gpio_p3in_field_t P3IN_f;
    };
    union
    {
        __IO uint32_t P3OUT;
        stc_gpio_p3out_field_t P3OUT_f;
    };
    union
    {
        __IO uint32_t P3ADS;
        stc_gpio_p3ads_field_t P3ADS_f;
    };
    uint8_t RESERVED56[12];
    union
    {
        __IO uint32_t P3DR;
        stc_gpio_p3dr_field_t P3DR_f;
    };
    union
    {
        __IO uint32_t P3PU;
        stc_gpio_p3pu_field_t P3PU_f;
    };
    union
    {
        __IO uint32_t P3PD;
        stc_gpio_p3pd_field_t P3PD_f;
    };
    uint8_t RESERVED59[4];
    union
    {
        __IO uint32_t P3OD;
        stc_gpio_p3od_field_t P3OD_f;
    };
    union
    {
        __IO uint32_t P3HIE;
        stc_gpio_p3hie_field_t P3HIE_f;
    };
    union
    {
        __IO uint32_t P3LIE;
        stc_gpio_p3lie_field_t P3LIE_f;
    };
    union
    {
        __IO uint32_t P3RIE;
        stc_gpio_p3rie_field_t P3RIE_f;
    };
    union
    {
        __IO uint32_t P3FIE;
        stc_gpio_p3fie_field_t P3FIE_f;
    };
    union
    {
        __IO uint32_t P0STAT;
        stc_gpio_p0stat_field_t P0STAT_f;
    };
    uint8_t RESERVED65[12];
    union
    {
        __IO uint32_t P0ICLR;
        stc_gpio_p0iclr_field_t P0ICLR_f;
    };
    uint8_t RESERVED66[44];
    union
    {
        __IO uint32_t P1STAT;
        stc_gpio_p1stat_field_t P1STAT_f;
    };
    uint8_t RESERVED67[12];
    union
    {
        __IO uint32_t P1ICLR;
        stc_gpio_p1iclr_field_t P1ICLR_f;
    };
    uint8_t RESERVED68[44];
    union
    {
        __IO uint32_t P2STAT;
        stc_gpio_p2stat_field_t P2STAT_f;
    };
    uint8_t RESERVED69[12];
    union
    {
        __IO uint32_t P2ICLR;
        stc_gpio_p2iclr_field_t P2ICLR_f;
    };
    uint8_t RESERVED70[44];
    union
    {
        __IO uint32_t P3STAT;
        stc_gpio_p3stat_field_t P3STAT_f;
    };
    uint8_t RESERVED71[12];
    union
    {
        __IO uint32_t P3ICLR;
        stc_gpio_p3iclr_field_t P3ICLR_f;
    };
    uint8_t RESERVED72[44];
    union
    {
        __IO uint32_t CTRL0;
        stc_gpio_ctrl0_field_t CTRL0_f;
    };
    union
    {
        __IO uint32_t CTRL1;
        stc_gpio_ctrl1_field_t CTRL1_f;
    };
    union
    {
        __IO uint32_t CTRL2;
        stc_gpio_ctrl2_field_t CTRL2_f;
    };
    union
    {
        __IO uint32_t CTRL3;
        stc_gpio_ctrl3_field_t CTRL3_f;
    };
    union
    {
        __IO uint32_t CTRL4;
        stc_gpio_ctrl4_field_t CTRL4_f;
    };
}M0P_GPIO_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t TMRUN;
        stc_i2c_tmrun_field_t TMRUN_f;
    };
    union
    {
        __IO uint32_t TM;
        stc_i2c_tm_field_t TM_f;
    };
    union
    {
        __IO uint32_t CR;
        stc_i2c_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t DATA;
        stc_i2c_data_field_t DATA_f;
    };
    union
    {
        __IO uint32_t ADDR;
        stc_i2c_addr_field_t ADDR_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_i2c_stat_field_t STAT_f;
    };
}M0P_I2C_TypeDef;

typedef struct
{
    uint8_t RESERVED0[96];
    union
    {
        __IO uint32_t CNT;
        stc_lptimer_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t ARR;
        stc_lptimer_arr_field_t ARR_f;
    };
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t CR;
        stc_lptimer_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_lptimer_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_lptimer_iclr_field_t ICLR_f;
    };
}M0P_LPTIMER_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SBUF;
        stc_lpuart_sbuf_field_t SBUF_f;
    };
    union
    {
        __IO uint32_t SCON;
        stc_lpuart_scon_field_t SCON_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_lpuart_saddr_field_t SADDR_f;
    };
    union
    {
        __IO uint32_t SADEN;
        stc_lpuart_saden_field_t SADEN_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_lpuart_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_lpuart_icr_field_t ICR_f;
    };
}M0P_LPUART_TypeDef;

typedef struct
{
    uint8_t RESERVED0[40];
    union
    {
        __IO uint32_t CR;
        stc_lvd_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_lvd_ifr_field_t IFR_f;
    };
}M0P_LVD_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CCON;
        stc_pca_ccon_field_t CCON_f;
    };
    union
    {
        __IO uint32_t CMOD;
        stc_pca_cmod_field_t CMOD_f;
    };
    union
    {
        __IO uint32_t CNT;
        stc_pca_cnt_field_t CNT_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_pca_iclr_field_t ICLR_f;
    };
    union
    {
        __IO uint32_t CCAPM0;
        stc_pca_ccapm0_field_t CCAPM0_f;
    };
    union
    {
        __IO uint32_t CCAPM1;
        stc_pca_ccapm1_field_t CCAPM1_f;
    };
    union
    {
        __IO uint32_t CCAPM2;
        stc_pca_ccapm2_field_t CCAPM2_f;
    };
    union
    {
        __IO uint32_t CCAPM3;
        stc_pca_ccapm3_field_t CCAPM3_f;
    };
    union
    {
        __IO uint32_t CCAPM4;
        stc_pca_ccapm4_field_t CCAPM4_f;
    };
    union
    {
        __IO uint32_t CCAP0H;
        stc_pca_ccap0h_field_t CCAP0H_f;
    };
    union
    {
        __IO uint32_t CCAP0L;
        stc_pca_ccap0l_field_t CCAP0L_f;
    };
    union
    {
        __IO uint32_t CCAP1H;
        stc_pca_ccap1h_field_t CCAP1H_f;
    };
    union
    {
        __IO uint32_t CCAP1L;
        stc_pca_ccap1l_field_t CCAP1L_f;
    };
    union
    {
        __IO uint32_t CCAP2H;
        stc_pca_ccap2h_field_t CCAP2H_f;
    };
    union
    {
        __IO uint32_t CCAP2L;
        stc_pca_ccap2l_field_t CCAP2L_f;
    };
    union
    {
        __IO uint32_t CCAP3H;
        stc_pca_ccap3h_field_t CCAP3H_f;
    };
    union
    {
        __IO uint32_t CCAP3L;
        stc_pca_ccap3l_field_t CCAP3L_f;
    };
    union
    {
        __IO uint32_t CCAP4H;
        stc_pca_ccap4h_field_t CCAP4H_f;
    };
    union
    {
        __IO uint32_t CCAP4L;
        stc_pca_ccap4l_field_t CCAP4L_f;
    };
    union
    {
        __IO uint32_t CCAPO;
        stc_pca_ccapo_field_t CCAPO_f;
    };
    union
    {
        __IO uint32_t CCAP0;
        stc_pca_ccap0_field_t CCAP0_f;
    };
    union
    {
        __IO uint32_t CCAP1;
        stc_pca_ccap1_field_t CCAP1_f;
    };
    union
    {
        __IO uint32_t CCAP2;
        stc_pca_ccap2_field_t CCAP2_f;
    };
    union
    {
        __IO uint32_t CCAP3;
        stc_pca_ccap3_field_t CCAP3_f;
    };
    union
    {
        __IO uint32_t CCAP4;
        stc_pca_ccap4_field_t CCAP4_f;
    };
}M0P_PCA_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_ram_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t ERRADDR;
        stc_ram_erraddr_field_t ERRADDR_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_ram_ifr_field_t IFR_f;
    };
    union
    {
        __IO uint32_t ICLR;
        stc_ram_iclr_field_t ICLR_f;
    };
}M0P_RAM_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t RESET_FLAG;
        stc_reset_reset_flag_field_t RESET_FLAG_f;
    };
    uint8_t RESERVED1[8];
    union
    {
        __IO uint32_t PREI_RESET;
        stc_reset_prei_reset_field_t PREI_RESET_f;
    };
}M0P_RESET_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR0;
        stc_rtc_cr0_field_t CR0_f;
    };
    union
    {
        __IO uint32_t CR1;
        stc_rtc_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t SEC;
        stc_rtc_sec_field_t SEC_f;
    };
    union
    {
        __IO uint32_t MIN;
        stc_rtc_min_field_t MIN_f;
    };
    union
    {
        __IO uint32_t HOUR;
        stc_rtc_hour_field_t HOUR_f;
    };
    union
    {
        __IO uint32_t WEEK;
        stc_rtc_week_field_t WEEK_f;
    };
    union
    {
        __IO uint32_t DAY;
        stc_rtc_day_field_t DAY_f;
    };
    union
    {
        __IO uint32_t MON;
        stc_rtc_mon_field_t MON_f;
    };
    union
    {
        __IO uint32_t YEAR;
        stc_rtc_year_field_t YEAR_f;
    };
    union
    {
        __IO uint32_t ALMMIN;
        stc_rtc_almmin_field_t ALMMIN_f;
    };
    union
    {
        __IO uint32_t ALMHOUR;
        stc_rtc_almhour_field_t ALMHOUR_f;
    };
    union
    {
        __IO uint32_t ALMWEEK;
        stc_rtc_almweek_field_t ALMWEEK_f;
    };
    union
    {
        __IO uint32_t COMPEN;
        stc_rtc_compen_field_t COMPEN_f;
    };
}M0P_RTC_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t CR;
        stc_spi_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t SSN;
        stc_spi_ssn_field_t SSN_f;
    };
    union
    {
        __IO uint32_t STAT;
        stc_spi_stat_field_t STAT_f;
    };
    union
    {
        __IO uint32_t DATA;
        stc_spi_data_field_t DATA_f;
    };
}M0P_SPI_TypeDef;

typedef struct
{
    union
    {
        __IO uint32_t SBUF;
        stc_uart_sbuf_field_t SBUF_f;
    };
    union
    {
        __IO uint32_t SCON;
        stc_uart_scon_field_t SCON_f;
    };
    union
    {
        __IO uint32_t SADDR;
        stc_uart_saddr_field_t SADDR_f;
    };
    union
    {
        __IO uint32_t SADEN;
        stc_uart_saden_field_t SADEN_f;
    };
    union
    {
        __IO uint32_t ISR;
        stc_uart_isr_field_t ISR_f;
    };
    union
    {
        __IO uint32_t ICR;
        stc_uart_icr_field_t ICR_f;
    };
}M0P_UART_TypeDef;

typedef struct
{
    uint8_t RESERVED0[16];
    union
    {
        __IO uint32_t CR;
        stc_vc_cr_field_t CR_f;
    };
    union
    {
        __IO uint32_t VC0_CR;
        stc_vc_vc0_cr_field_t VC0_CR_f;
    };
    union
    {
        __IO uint32_t VC1_CR;
        stc_vc_vc1_cr_field_t VC1_CR_f;
    };
    union
    {
        __IO uint32_t VC0_OUT_CFG;
        stc_vc_vc0_out_cfg_field_t VC0_OUT_CFG_f;
    };
    union
    {
        __IO uint32_t VC1_OUT_CFG;
        stc_vc_vc1_out_cfg_field_t VC1_OUT_CFG_f;
    };
    union
    {
        __IO uint32_t IFR;
        stc_vc_ifr_field_t IFR_f;
    };
}M0P_VC_TypeDef;

typedef struct
{
    uint8_t RESERVED0[128];
    union
    {
        __IO uint32_t RST;
        stc_wdt_rst_field_t RST_f;
    };
    union
    {
        __IO uint32_t CON;
        stc_wdt_con_field_t CON_f;
    };
}M0P_WDT_TypeDef;



#define M0P_ADC                                ((M0P_ADC_TypeDef *)0x40002400UL)
#define M0P_ADT0                               ((M0P_ADT_TypeDef *)0x40003000UL)
#define M0P_ADT1                               ((M0P_ADT_TypeDef *)0x40003400UL)
#define M0P_ADT2                               ((M0P_ADT_TypeDef *)0x40003800UL)
#define M0P_BGR                                ((M0P_BGR_TypeDef *)0x40002400UL)
#define M0P_BT0                                ((M0P_BT_TypeDef *)0x40000C00UL)
#define M0P_BT1                                ((M0P_BT_TypeDef *)0x40000C20UL)
#define M0P_BT2                                ((M0P_BT_TypeDef *)0x40000C40UL)
#define M0P_CLK_TRIM                           ((M0P_CLK_TRIM_TypeDef *)0x40001800UL)
#define M0P_CLOCK                              ((M0P_CLOCK_TypeDef *)0x40002000UL)
#define M0P_CRC                                ((M0P_CRC_TypeDef *)0x40020900UL)
#define M0P_FLASH                              ((M0P_FLASH_TypeDef *)0x40020000UL)
#define M0P_GPIO                               ((M0P_GPIO_TypeDef *)0x40020C00UL)
#define M0P_I2C                                ((M0P_I2C_TypeDef *)0x40000400UL)
#define M0P_LPTIMER                            ((M0P_LPTIMER_TypeDef *)0x40000C00UL)
#define M0P_LPUART                             ((M0P_LPUART_TypeDef *)0x40000200UL)
#define M0P_LVD                                ((M0P_LVD_TypeDef *)0x40002400UL)
#define M0P_PCA                                ((M0P_PCA_TypeDef *)0x40001000UL)
#define M0P_RAM                                ((M0P_RAM_TypeDef *)0x40020400UL)
#define M0P_RESET                              ((M0P_RESET_TypeDef *)0x4000201CUL)
#define M0P_RTC                                ((M0P_RTC_TypeDef *)0x40001400UL)
#define M0P_SPI                                ((M0P_SPI_TypeDef *)0x40000800UL)
#define M0P_UART0                              ((M0P_UART_TypeDef *)0x40000000UL)
#define M0P_UART1                              ((M0P_UART_TypeDef *)0x40000100UL)
#define M0P_VC                                 ((M0P_VC_TypeDef *)0x40002400UL)
#define M0P_WDT                                ((M0P_WDT_TypeDef *)0x40000C00UL)


#ifdef __cplusplus
}
#endif

#endif /* __HC32L110_H__ */

