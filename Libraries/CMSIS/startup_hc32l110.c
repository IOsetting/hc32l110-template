#include <stdint.h>

typedef void (*ptr_func_t)();

extern uint32_t SystemCoreClock;
extern uint32_t PeripheralCoreClock;

extern uint32_t __data_start;
extern uint32_t __data_end;
extern uint32_t __data_load;

extern uint32_t __bss_start;
extern uint32_t __bss_end;

extern uint32_t __heap_start;
extern uint32_t __stacktop;

extern ptr_func_t __init_array_start[];
extern ptr_func_t __init_array_end[];

extern int main(void);
extern void SystemInit(void);

#define WEAK_ALIAS(x) __attribute__ ((weak, alias(#x)))

/* Cortex M3 core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void)          WEAK_ALIAS(Dummy_Handler);
void HardFault_Handler(void)    WEAK_ALIAS(Dummy_Handler);
void SVC_Handler(void)          WEAK_ALIAS(Dummy_Handler);
void PendSV_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void SysTick_Handler(void)      WEAK_ALIAS(Dummy_Handler);

void PORT0_IRQHandler(void)     WEAK_ALIAS(Dummy_Handler);
void PORT1_IRQHandler(void)     WEAK_ALIAS(Dummy_Handler);
void PORT2_IRQHandler(void)     WEAK_ALIAS(Dummy_Handler);
void PORT3_IRQHandler(void)     WEAK_ALIAS(Dummy_Handler);
void IRQ004_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ005_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void UART0_IRQHandler(void)     WEAK_ALIAS(Dummy_Handler);
void UART1_IRQHandler(void)     WEAK_ALIAS(Dummy_Handler);
void LPUART_IRQHandler(void)    WEAK_ALIAS(Dummy_Handler);
void IRQ009_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void SPI_IRQHandler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ011_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void I2C_IRQHandler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ013_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void TIM0_IRQHandler(void)      WEAK_ALIAS(Dummy_Handler);
void TIM1_IRQHandler(void)      WEAK_ALIAS(Dummy_Handler);
void TIM2_IRQHandler(void)      WEAK_ALIAS(Dummy_Handler);
void IRQ017_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ018_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ019_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ020_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ021_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ022_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ023_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ024_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ025_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ026_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ027_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ028_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ029_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ030_Handler(void)       WEAK_ALIAS(Dummy_Handler);
void IRQ031_Handler(void)       WEAK_ALIAS(Dummy_Handler);

__attribute__((section(".stack"), used)) uint32_t *__stack_init = &__stacktop;

/* Stack top and vector handler table */
__attribute__ ((section(".vectors"), used)) void *vector_table[] = {
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SVC_Handler,
    0,
    0,
    PendSV_Handler,
    SysTick_Handler,
    PORT0_IRQHandler,
    PORT1_IRQHandler,
    PORT2_IRQHandler,
    PORT3_IRQHandler,
    IRQ004_Handler,
    IRQ005_Handler,
    UART0_IRQHandler,
    UART1_IRQHandler,
    LPUART_IRQHandler,
    IRQ009_Handler,
    SPI_IRQHandler,
    IRQ011_Handler,
    I2C_IRQHandler,
    IRQ013_Handler,
    TIM0_IRQHandler,
    TIM1_IRQHandler,
    TIM2_IRQHandler,
    IRQ017_Handler,
    IRQ018_Handler,
    IRQ019_Handler,
    IRQ020_Handler,
    IRQ021_Handler,
    IRQ022_Handler,
    IRQ023_Handler,
    IRQ024_Handler,
    IRQ025_Handler,
    IRQ026_Handler,
    IRQ027_Handler,
    IRQ028_Handler,
    IRQ029_Handler,
    IRQ030_Handler,
    IRQ031_Handler};


__attribute__((used)) void Reset_Handler(void)
{
    uint32_t *src, *dst;

    /* Copy data section from Flash to RAM */
    src = &__data_load;
    dst = &__data_start;
    while (dst < &__data_end) *dst++ = *src++;

    /* Clear the bss section */
    dst = &__bss_start;
    while (dst < &__bss_end) *dst++ = 0;

    SystemInit();

    for (const ptr_func_t *f = __init_array_start; f < __init_array_end; f++)
    {
        (*f)();
    }

    main();
}

void Dummy_Handler(void)
{
    while (1);
}
