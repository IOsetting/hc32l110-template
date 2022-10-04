#include "nrf24l01.h"
#include "gpio.h"
#include "debug.h"

#define TX_MODE     0

#define LED_PORT       (3)
#define LED_PIN        (4)

const uint8_t TX_ADDRESS[NRF24_ADDR_WIDTH] = {0x32,0x4E,0x6F,0x64,0x22};
const uint8_t RX_ADDRESS[NRF24_ADDR_WIDTH] = {0x32,0x4E,0x6F,0x64,0x65};
extern uint8_t xbuf[NRF24_PLOAD_WIDTH];

void PORT3_IRQHandler(void)
{
    /** Clear interrupt flag before handling, otherwise it will be triggered twice */
    Gpio_ClearIrq(NRF_IRQ_PORT, NRF_IRQ_PIN);
    if (Gpio_GetIrqStat(NRF_IRQ_PORT, NRF_IRQ_PIN))
    {
        GPIO_SetPinOutHigh(LED_PORT, LED_PIN);
        NRF24L01_HandelIrqFlag();
        GPIO_SetPinOutLow(LED_PORT, LED_PIN);
    }
}

void SPI_Init(void)
{
    stc_spi_config_t  SPIConfig;

    CLK_EnablePeripheralClk(ClkPeripheralSpi);

    Gpio_SetFunc_SPI_CS_P14();
    Gpio_SetFunc_SPI_MISO_P23();
    Gpio_SetFunc_SPI_MOSI_P24();
    Gpio_SetFunc_SPI_CLK_P25();

    SPIConfig.bCPHA = SpiClockPhaseFirst;
    SPIConfig.bCPOL = SpiClockPolarityLow;
    // Turn off interrupts
    SPIConfig.bIrqEn = FALSE;
    // Master mode
    SPIConfig.bMasterMode = SpiMaster;
    // Clock source, PCLK/2
    SPIConfig.u8ClkDiv = SpiClkDiv2;
    // No callback
    SPIConfig.pfnIrqCb = NULL;
    Spi_Init(&SPIConfig);
}

int main(void)
{
#if TX_MODE == 1
    uint8_t tmp[] = {
        0x1F, 0x80, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x21, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x28,
        0x31, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x38,
        0x41, 0x12, 0x13, 0x14, 0x15, 0x16, 0x37, 0x48};
    uint8_t succ = 0, total = 0;
#endif
    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);

    CLK_EnablePeripheralClk(ClkPeripheralGpio);
    Debug_PrinfInit();
    printf("UART Initialized\r\n");

    SPI_Init();
    printf("SPI Initialized\r\n");

    // LED
    Gpio_InitIO(LED_PORT, LED_PIN, GpioDirOut);
    GPIO_SetPinOutHigh(LED_PORT, LED_PIN);
    delay1ms(200);
    GPIO_SetPinOutLow(LED_PORT, LED_PIN);

    while (NRF24L01_SPI_Check() == 1)
    {
        printf(" SPI Check failed\r\n");
        delay1ms(1000);
    }
    printf(" SPI Check succ\r\n");

    Gpio_InitIOExt(NRF_CE_PORT, NRF_CE_PIN, GpioDirOut, TRUE, FALSE, FALSE, 0);

    NRF24L01_Config();
    printf("NRF24L01 Configured\r\n");


#if TX_MODE == 1
    NRF24L01_TxMode((uint8_t *)TX_ADDRESS, (uint8_t *)RX_ADDRESS);
    printf("NRF24L01 TX Mode\r\n");
    while (1)
    {
        tmp[NRF24_PLOAD_WIDTH - 1] = total;
        if (NRF24L01_TxFast(tmp) != 0)
        {
            NRF24L01_TxReset();
        }
        else
        {
            succ++;
        }
        total++;
        if (total == 255)
        {
            printf("Succ: %d\r\n", succ);
            total = 0;
            succ = 0;
            NRF24L01_DumpConfig();
        }
        delay1ms(100);
    }

#else
    NRF24L01_RxMode((uint8_t *)RX_ADDRESS, (uint8_t *)TX_ADDRESS);
    printf("NRF24L01 RX Mode\r\n");
    Gpio_InitIOExt(NRF_IRQ_PORT, NRF_IRQ_PIN, GpioDirIn, FALSE, FALSE, FALSE, 0);
    Gpio_ClearIrq(NRF_IRQ_PORT, NRF_IRQ_PIN);
    Gpio_EnableIrq(NRF_IRQ_PORT, NRF_IRQ_PIN, GpioIrqLow);
    EnableNvic(PORT3_IRQn, DDL_IRQ_LEVEL_DEFAULT, TRUE);
    while(1)
    {
        NRF24L01_DumpConfig();
        delay1ms(5000);
    }
#endif

}
