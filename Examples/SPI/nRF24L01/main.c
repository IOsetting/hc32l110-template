#include "nrf24l01.h"
#include "gpio.h"
#include "debug.h"

extern uint8_t xbuf[NRF24_PLOAD_WIDTH];

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
    // uint8_t tmp[] = {
    //     0x1F, 0x80, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
    //     0x21, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x28,
    //     0x31, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x38,
    //     0x41, 0x12, 0x13, 0x14, 0x15, 0x16, 0x37, 0x48};
    // uint8_t succ = 0, err = 0;

    /**
     * Set PCLK = HCLK = Clock source to 24MHz
     */
    Clk_Init(ClkFreq24Mhz, ClkDiv1, ClkDiv1);

    CLK_EnablePeripheralClk(ClkPeripheralGpio);
    Debug_PrinfInit();
    printf("UART Initialized\r\n");

    SPI_Init();
    printf("SPI Initialized\r\n");

    Gpio_InitIOExt(NRF_CE_PORT, NRF_CE_PIN, GpioDirOut, TRUE, FALSE, FALSE, 0);
    Gpio_InitIOExt(NRF_IRQ_PORT, NRF_IRQ_PIN, GpioDirIn, TRUE, FALSE, FALSE, 0);

    while (NRF24L01_Check() == 1)
    {
        printf("Check failed\r\n");
        delay1ms(1000);
    }
    printf(" Checked\r\n");

    while(1);
}
