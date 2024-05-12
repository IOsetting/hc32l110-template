// Copyright 2021 IOsetting <iosetting(at)outlook.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "nrf24l01.h"
#include "uart.h"

uint8_t xbuf[NRF24_PLOAD_WIDTH];
uint16_t NRF24L01_rxsn = 0;

uint8_t NRF24L01_WriteReg(uint8_t reg, uint8_t value)
{
    uint8_t ret;
    SPI_SetCsLow();
    ret = Spi_TxRx(reg);
    Spi_TxRx(value);
    SPI_SetCsHigh();
    return ret;
}

uint8_t NRF24L01_ReadReg(uint8_t reg)
{
    uint8_t ret;
    SPI_SetCsLow();
    Spi_TxRx(reg);
    ret = Spi_TxRx(NRF24_CMD_NOP);
    SPI_SetCsHigh();
    return ret;
}

void NRF24L01_ReadToBuf(uint8_t reg, uint8_t len)
{
    memset(xbuf, NRF24_CMD_NOP, NRF24_PLOAD_WIDTH);
    SPI_SetCsLow();
    Spi_TxRx(reg);
    Spi_TxRxBytes(xbuf, len);
    SPI_SetCsHigh();
}

void NRF24L01_WriteFromBuf(uint8_t reg, const uint8_t *pBuf, uint8_t len)
{
    memcpy(xbuf, pBuf, len);
    SPI_SetCsLow();
    Spi_TxRx(reg);
    Spi_TxRxBytes(xbuf, len);
    SPI_SetCsHigh();
}

void NRF24L01_PrintBuf(void)
{
    Uart1_TxHexArray(xbuf, NRF24_PLOAD_WIDTH);
    Uart1_TxString("\r\n");
}

/**
* Flush the RX FIFO
*/
void NRF24L01_RxFlush(void)
{
    NRF24L01_WriteReg(NRF24_CMD_FLUSH_RX, NRF24_CMD_NOP);
}

/**
* Flush the TX FIFO
*/
void NRF24L01_TxFlush(void)
{
    NRF24L01_WriteReg(NRF24_CMD_FLUSH_TX, NRF24_CMD_NOP);
}

uint8_t NRF24L01_RxAvailable(uint8_t *pipe_num)
{
    uint8_t dat, pipe;
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_STATUS);
    pipe = (dat >> 1) & 0x07;
    if (pipe > 5)
        return 1;
    // If the caller wants the pipe number, include that
    if (pipe_num)
        *pipe_num = pipe;

    return 0;
}

void NRF24L01_HandelIrqFlag(void)
{
    uint8_t dat, tx_ds, max_rt, rx_dr, pipe_num;
    dat = NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_STATUS, NRF24_FLAG_RX_DREADY|NRF24_FLAG_TX_DSENT|NRF24_FLAG_MAX_RT);
    tx_ds = dat & NRF24_FLAG_TX_DSENT;
    max_rt = dat & NRF24_FLAG_MAX_RT;
    rx_dr = dat & NRF24_FLAG_RX_DREADY;
    if (NRF24L01_RxAvailable(&pipe_num) == 0) 
    {
        NRF24L01_ReadToBuf(NRF24_CMD_R_RX_PAYLOAD, NRF24_PLOAD_WIDTH);
        NRF24L01_rxsn++;
        NRF24L01_PrintBuf();
    }
    printf("TxDS:%x MxRT:%x RxDR:%x Pipe:%d\r\n", tx_ds, max_rt, rx_dr, pipe_num);
}

void NRF24L01_Tx(uint8_t *pBuf)
{
    NRF_CE_Low();
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_CONFIG, 0x0E);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_TX_PAYLOAD, pBuf, NRF24_PLOAD_WIDTH);
    NRF_CE_High();
    delay1ms(10); // for reliable DS state when SETUP_RETR is 0x13
    NRF_CE_Low();
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_CONFIG, 0x0F);
    NRF_CE_High();
}

uint8_t NRF24L01_TxFast(const void* pBuf)
{
    uint8_t dat;
    //Blocking only if FIFO is full. This will loop and block until TX is successful or fail
    do
    {
        dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_STATUS);
        if (dat & NRF24_FLAG_MAX_RT) return 1;
    } while (dat & NRF24_FLAG_TX_FULL);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_TX_PAYLOAD, pBuf, NRF24_PLOAD_WIDTH);
    NRF_CE_High();
    return 0;
}

void NRF24L01_TxReset(void)
{
    //Clear max retry flag
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_STATUS, NRF24_FLAG_MAX_RT);
    NRF_CE_Low();
    delay1ms(0);
    NRF_CE_High();
}

uint8_t NRF24L01_SPI_Check(void)
{
    uint8_t i;
    const uint8_t *ptr = (const uint8_t *)NRF24_TEST_ADDR;
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_TX_ADDR, ptr, NRF24_ADDR_WIDTH);
    NRF24L01_ReadToBuf(NRF24_CMD_R_REGISTER | NRF24_REG_TX_ADDR, NRF24_ADDR_WIDTH);
    for (i = 0; i < NRF24_ADDR_WIDTH; i++) {
        Uart1_TxHexArray(xbuf + i, 1);
        if (*(xbuf + i) != *ptr++) return 1;
    }
    return 0;
}

/**
* Common configurations
*/
void NRF24L01_Config(void)
{
    // RX P0 payload width
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_RX_PW_P0, NRF24_PLOAD_WIDTH);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_RX_PW_P1, NRF24_PLOAD_WIDTH);
    // Enable auto ACK all pipes
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_EN_AA, 0x3f);
    // Enable RX all pipes
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_EN_RXADDR, 0x3f);
    // 0A:delay=250us,count=10, 1A:delay=500us,count=10
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_SETUP_RETR, 0x13);
    // RF channel 40 - 2.440GHz = 2.400G  + 0.040G
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_RF_CH, 40);
    // 000+0+[0:1Mbps,1:2Mbps]+[00:-18dbm,01:-12dbm,10:-6dbm,11:0dbm]+[0:LNA_OFF,1:LNA_ON]
    // 01:1Mbps,-18dbm; 03:1Mbps,-12dbm; 05:1Mbps,-6dbm; 07:1Mbps,0dBm
    // 09:2Mbps,-18dbm; 0b:2Mbps,-12dbm; 0d:2Mbps,-6dbm; 0f:2Mbps,0dBm
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_RF_SETUP, 0x07);
}

/**
* Switch to TX mode
*/
void NRF24L01_TxMode(uint8_t *txAddr, uint8_t *rxAddr)
{
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_TX_ADDR, txAddr, NRF24_ADDR_WIDTH);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_RX_ADDR_P0, txAddr, NRF24_ADDR_WIDTH);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_RX_ADDR_P1, rxAddr, NRF24_ADDR_WIDTH);
    /**
    REG 0x00:
    0)PRIM_RX     0:TX             1:RX
    1)PWR_UP      0:OFF            1:ON
    2)CRCO        0:8bit CRC       1:16bit CRC
    3)EN_CRC      Enabled if any of EN_AA is high
    4)MASK_MAX_RT 0:IRQ low        1:NO IRQ
    5)MASK_TX_DS  0:IRQ low        1:NO IRQ
    6)MASK_RX_DR  0:IRQ low        1:NO IRQ
    7)Reserved    0
    */
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_CONFIG, 0x0E);
}

/**
* Switch to RX mode
*/
void NRF24L01_RxMode(uint8_t *txAddr, uint8_t *rxAddr)
{
    NRF_CE_Low();
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_TX_ADDR, txAddr, NRF24_ADDR_WIDTH);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_RX_ADDR_P0, txAddr, NRF24_ADDR_WIDTH);
    NRF24L01_WriteFromBuf(NRF24_CMD_W_REGISTER | NRF24_REG_RX_ADDR_P1, rxAddr, NRF24_ADDR_WIDTH);
    NRF24L01_WriteReg(NRF24_CMD_W_REGISTER | NRF24_REG_CONFIG, 0x0F);
    NRF_CE_High();
    NRF24L01_RxFlush();
}

/**
 * Dump nRF24L01 configuration for debug
 */
void NRF24L01_DumpConfig(void)
{
    uint8_t dat, i, j;

    // CONFIG
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_CONFIG);
    printf("[0x%02X] 0x%02X MASK:%02X CRC:%02X PWR:%s MODE:%s\r\n",
           NRF24_REG_CONFIG, dat, dat >> 4, (dat & 0x0c) >> 2,
           (dat & 0x02) ? "ON" : "OFF",
           (dat & 0x01) ? "RX" : "TX");

    // EN_AA
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_EN_AA);
    printf("[0x%02X] 0x%02X ENAA: ", NRF24_REG_EN_AA, dat);
    for (j = 0; j < 6; j++)
    {
        printf("[P%1u%s]%s", j, (dat & (1 << j)) ? "+" : "-", (j == 5) ? "\r\n" : " ");
    }

    // EN_RXADDR
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_EN_RXADDR);
    printf("[0x%02X] 0x%02X EN_RXADDR: ", NRF24_REG_EN_RXADDR, dat);
    for (j = 0; j < 6; j++)
    {
        printf("[P%1u%s]%s", j,
               (dat & (1 << j)) ? "+" : "-",
               (j == 5) ? "\r\n" : " ");
    }

    // SETUP_AW
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_SETUP_AW);
    int8_t ww = (dat & 0x03) + 2;
    printf("[0x%02X] 0x%02X EN_RXADDR=%03X (address width = %u)\r\n",
           NRF24_REG_SETUP_AW, dat, dat & 0x03, ww);

    // SETUP_RETR
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_SETUP_RETR);
    printf("[0x%02X] 0x%02X ARD=%04X ARC=%04X (retr.delay=%uus, count=%u)\r\n",
           NRF24_REG_SETUP_RETR, dat, dat >> 4, dat & 0x0F, ((dat >> 4) * 250) + 250, dat & 0x0F);

    // RF_CH
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RF_CH);
    printf("[0x%02X] 0x%02X (%.3uGHz)\r\n", NRF24_REG_RF_CH, dat, 2400 + dat);

    // RF_SETUP
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RF_SETUP);
    printf("[0x%02X] 0x%02X CONT_WAVE:%s PLL_LOCK:%s DataRate=",
           NRF24_REG_RF_SETUP, dat,
           (dat & 0x80) ? "ON" : "OFF",
           (dat & 0x80) ? "ON" : "OFF");
    switch ((dat & 0x28) >> 3)
    {
    case 0x00:
        printf("1M");
        break;
    case 0x01:
        printf("2M");
        break;
    case 0x04:
        printf("250k");
        break;
    default:
        printf("???");
        break;
    }
    printf("pbs RF_PWR=");
    switch ((dat & 0x06) >> 1)
    {
    case 0x00:
        printf("-18");
        break;
    case 0x01:
        printf("-12");
        break;
    case 0x02:
        printf("-6");
        break;
    case 0x03:
        printf("0");
        break;
    default:
        printf("???");
        break;
    }
    printf("dBm\r\n");

    // STATUS
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_STATUS);
    printf("[0x%02X] 0x%02X IRQ:%03X RX_PIPE:%u TX_FULL:%s\r\n",
           NRF24_REG_STATUS, dat,
           (dat & 0x70) >> 4,
           (dat & 0x0E) >> 1,
           (dat & 0x01) ? "YES" : "NO");

    // OBSERVE_TX
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_OBSERVE_TX);
    printf("[0x%02X] 0x%02X PLOS_CNT=%u ARC_CNT=%u\r\n",
           NRF24_REG_OBSERVE_TX, dat, dat >> 4, dat & 0x0F);

    // RPD
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RPD);
    printf("[0x%02X] 0x%02X RPD=%s\r\n",
           NRF24_REG_RPD, dat, (dat & 0x01) ? "YES" : "NO");

    // RX_ADDR_P0
    NRF24L01_ReadToBuf(NRF24_REG_RX_ADDR_P0, NRF24_ADDR_WIDTH);
    printf("[0x%02X] RX_ADDR_P0 \"", NRF24_REG_RX_ADDR_P0);
    for (i = 0; i < NRF24_ADDR_WIDTH; i++)
        printf("%X ", xbuf[i]);
    printf("\"\r\n");

    // RX_ADDR_P1
    NRF24L01_ReadToBuf(NRF24_REG_RX_ADDR_P1, NRF24_ADDR_WIDTH);
    printf("[0x%02X] RX_ADDR_P1 \"", NRF24_REG_RX_ADDR_P1);
    for (i = 0; i < NRF24_ADDR_WIDTH; i++)
        printf("%X ", xbuf[i]);
    printf("\"\r\n");

    // RX_ADDR_P2
    printf("[0x%02X] RX_ADDR_P2 \"", NRF24_REG_RX_ADDR_P2);
    for (i = 0; i < NRF24_ADDR_WIDTH - 1; i++)
        printf("%X ", xbuf[i]);
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_ADDR_P2);
    printf("%X\"\r\n", dat);

    // RX_ADDR_P3
    printf("[0x%02X] RX_ADDR_P3 \"", NRF24_REG_RX_ADDR_P3);
    for (i = 0; i < NRF24_ADDR_WIDTH - 1; i++)
        printf("%X ", xbuf[i]);
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_ADDR_P3);
    printf("%X\"\r\n", dat);

    // RX_ADDR_P4
    printf("[0x%02X] RX_ADDR_P4 \"", NRF24_REG_RX_ADDR_P4);
    for (i = 0; i < NRF24_ADDR_WIDTH - 1; i++)
        printf("%X ", xbuf[i]);
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_ADDR_P4);
    printf("%X\"\r\n", dat);

    // RX_ADDR_P5
    printf("[0x%02X] RX_ADDR_P5 \"", NRF24_REG_RX_ADDR_P5);
    for (i = 0; i < NRF24_ADDR_WIDTH - 1; i++)
        printf("%X ", xbuf[i]);
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_ADDR_P5);
    printf("%X\"\r\n", dat);

    // TX_ADDR
    NRF24L01_ReadToBuf(NRF24_REG_TX_ADDR, NRF24_ADDR_WIDTH);
    printf("[0x%02X] TX_ADDR \"", NRF24_REG_TX_ADDR);
    for (i = 0; i < NRF24_ADDR_WIDTH; i++)
        printf("%02X ", xbuf[i]);
    printf("\"\r\n");

    // RX_PW_P0
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_PW_P0);
    printf("[0x%02X] RX_PW_P0=%u\r\n", NRF24_REG_RX_PW_P0, dat);

    // RX_PW_P1
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_PW_P1);
    printf("[0x%02X] RX_PW_P1=%u\r\n", NRF24_REG_RX_PW_P1, dat);

    // RX_PW_P2
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_PW_P2);
    printf("[0x%02X] RX_PW_P2=%u\r\n", NRF24_REG_RX_PW_P2, dat);

    // RX_PW_P3
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_PW_P3);
    printf("[0x%02X] RX_PW_P3=%u\r\n", NRF24_REG_RX_PW_P3, dat);

    // RX_PW_P4
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_PW_P4);
    printf("[0x%02X] RX_PW_P4=%u\r\n", NRF24_REG_RX_PW_P4, dat);

    // RX_PW_P5
    dat = NRF24L01_ReadReg(NRF24_CMD_R_REGISTER | NRF24_REG_RX_PW_P5);
    printf("[0x%02X] RX_PW_P5=%u\r\n", NRF24_REG_RX_PW_P5, dat);
}