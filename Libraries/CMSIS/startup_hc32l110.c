#include <stdint.h>

extern uint32_t SystemCoreClock;
extern uint32_t PeripheralCoreClock;

extern uint32_t __data_start;
extern uint32_t __data_end;
extern uint32_t __data_load;

extern uint32_t __bss_start;
extern uint32_t __bss_end;

extern uint32_t __heap_start;
extern uint32_t __stacktop;

extern int main(void);
extern void SystemInit(void);

#define WEAK_ALIAS(x) __attribute__ ((weak, alias(#x)))

/* Cortex M3 core interrupt handlers */
void Reset_Handler(void);
void NMI_Handler(void) WEAK_ALIAS(Dummy_Handler);
void HardFault_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SVC_Handler(void) WEAK_ALIAS(Dummy_Handler);
void PendSV_Handler(void) WEAK_ALIAS(Dummy_Handler);
void SysTick_Handler(void) WEAK_ALIAS(Dummy_Handler);

void IRQ00_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ01_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ02_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ03_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ04_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ05_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ06_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ07_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ08_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ09_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ10_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ11_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ12_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ13_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ14_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ15_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ16_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ17_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ18_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ19_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ20_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ21_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ22_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ23_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ24_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ25_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ26_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ27_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ28_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ29_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ30_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ31_Handler(void) WEAK_ALIAS(Dummy_Handler);

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
    IRQ00_Handler,
    IRQ01_Handler,
    IRQ02_Handler,
    IRQ03_Handler,
    IRQ04_Handler,
    IRQ05_Handler,
    IRQ06_Handler,
    IRQ07_Handler,
    IRQ08_Handler,
    IRQ09_Handler,
    IRQ10_Handler,
    IRQ11_Handler,
    IRQ12_Handler,
    IRQ13_Handler,
    IRQ14_Handler,
    IRQ15_Handler,
    IRQ16_Handler,
    IRQ17_Handler,
    IRQ18_Handler,
    IRQ19_Handler,
    IRQ20_Handler,
    IRQ21_Handler,
    IRQ22_Handler,
    IRQ23_Handler,
    IRQ24_Handler,
    IRQ25_Handler,
    IRQ26_Handler,
    IRQ27_Handler,
    IRQ28_Handler,
    IRQ29_Handler,
    IRQ30_Handler,
    IRQ31_Handler};


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
    main();
}

void Dummy_Handler(void)
{
    while (1);
}
