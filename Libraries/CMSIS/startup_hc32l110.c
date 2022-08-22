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

void IRQ000_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ001_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ002_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ003_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ004_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ005_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ006_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ007_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ008_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ009_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ010_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ011_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ012_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ013_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ014_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ015_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ016_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ017_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ018_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ019_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ020_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ021_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ022_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ023_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ024_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ025_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ026_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ027_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ028_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ029_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ030_Handler(void) WEAK_ALIAS(Dummy_Handler);
void IRQ031_Handler(void) WEAK_ALIAS(Dummy_Handler);

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
    IRQ000_Handler,
    IRQ001_Handler,
    IRQ002_Handler,
    IRQ003_Handler,
    IRQ004_Handler,
    IRQ005_Handler,
    IRQ006_Handler,
    IRQ007_Handler,
    IRQ008_Handler,
    IRQ009_Handler,
    IRQ010_Handler,
    IRQ011_Handler,
    IRQ012_Handler,
    IRQ013_Handler,
    IRQ014_Handler,
    IRQ015_Handler,
    IRQ016_Handler,
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
    main();
}

void Dummy_Handler(void)
{
    while (1);
}
