/**
  ******************************************************************************
  * @file      startup_hc32l110.s
  * @brief     HC32L110 devices vector table for GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually calls main()).
  *            After Reset the Cortex-M0 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m0plus
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors. Remove this line if compile with `-nostartfiles` reports error */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval : None
*/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  0
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler
  .word  PORT0_IRQHandler
  .word  PORT1_IRQHandler
  .word  PORT2_IRQHandler
  .word  PORT3_IRQHandler
  .word  IRQ004_Handler
  .word  IRQ005_Handler
  .word  UART0_IRQHandler
  .word  UART1_IRQHandler
  .word  LPUART_IRQHandler
  .word  IRQ009_Handler
  .word  SPI_IRQHandler
  .word  IRQ011_Handler
  .word  I2C_IRQHandler
  .word  IRQ013_Handler
  .word  TIM0_IRQHandler
  .word  TIM1_IRQHandler
  .word  TIM2_IRQHandler
  .word  LPTIM_IRQHandler
  .word  IRQ018_Handler
  .word  IRQ019_Handler
  .word  IRQ020_Handler
  .word  IRQ021_Handler
  .word  IRQ022_Handler
  .word  IRQ023_Handler
  .word  IRQ024_Handler
  .word  IRQ025_Handler
  .word  IRQ026_Handler
  .word  IRQ027_Handler
  .word  IRQ028_Handler
  .word  IRQ029_Handler
  .word  IRQ030_Handler
  .word  IRQ031_Handler

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      PORT0_IRQHandler
  .thumb_set PORT0_IRQHandler,Default_Handler

  .weak      PORT1_IRQHandler
  .thumb_set PORT1_IRQHandler,Default_Handler

  .weak      PORT2_IRQHandler
  .thumb_set PORT2_IRQHandler,Default_Handler

  .weak      PORT3_IRQHandler
  .thumb_set PORT3_IRQHandler,Default_Handler

  .weak      IRQ004_Handler
  .thumb_set IRQ004_Handler,Default_Handler

  .weak      IRQ005_Handler
  .thumb_set IRQ005_Handler,Default_Handler

  .weak      UART0_IRQHandler
  .thumb_set UART0_IRQHandler,Default_Handler

  .weak      UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler

  .weak      LPUART_IRQHandler
  .thumb_set LPUART_IRQHandler,Default_Handler

  .weak      IRQ009_Handler
  .thumb_set IRQ009_Handler,Default_Handler

  .weak      SPI_IRQHandler
  .thumb_set SPI_IRQHandler,Default_Handler

  .weak      IRQ011_Handler
  .thumb_set IRQ011_Handler,Default_Handler

  .weak      I2C_IRQHandler
  .thumb_set I2C_IRQHandler,Default_Handler

  .weak      IRQ013_Handler
  .thumb_set IRQ013_Handler,Default_Handler

  .weak      TIM0_IRQHandler
  .thumb_set TIM0_IRQHandler,Default_Handler

  .weak      TIM1_IRQHandler
  .thumb_set TIM1_IRQHandler,Default_Handler

  .weak      TIM2_IRQHandler
  .thumb_set TIM2_IRQHandler,Default_Handler

  .weak      LPTIM_IRQHandler
  .thumb_set LPTIM_IRQHandler,Default_Handler

  .weak      IRQ018_Handler
  .thumb_set IRQ018_Handler,Default_Handler

  .weak      IRQ019_Handler
  .thumb_set IRQ019_Handler,Default_Handler

  .weak      IRQ020_Handler
  .thumb_set IRQ020_Handler,Default_Handler

  .weak      IRQ021_Handler
  .thumb_set IRQ021_Handler,Default_Handler

  .weak      IRQ022_Handler
  .thumb_set IRQ022_Handler,Default_Handler

  .weak      IRQ023_Handler
  .thumb_set IRQ023_Handler,Default_Handler

  .weak      IRQ024_Handler
  .thumb_set IRQ024_Handler,Default_Handler

  .weak      IRQ025_Handler
  .thumb_set IRQ025_Handler,Default_Handler

  .weak      IRQ026_Handler
  .thumb_set IRQ026_Handler,Default_Handler

  .weak      IRQ027_Handler
  .thumb_set IRQ027_Handler,Default_Handler

  .weak      IRQ028_Handler
  .thumb_set IRQ028_Handler,Default_Handler

  .weak      IRQ029_Handler
  .thumb_set IRQ029_Handler,Default_Handler

  .weak      IRQ030_Handler
  .thumb_set IRQ030_Handler,Default_Handler

  .weak      IRQ032_Handler
  .thumb_set IRQ031_Handler,Default_Handler
