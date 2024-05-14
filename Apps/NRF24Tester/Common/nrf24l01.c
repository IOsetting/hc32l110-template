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

uint16_t NRF24L01_rxsn = 0;

void NRF24L01_Init(void)
{
    SPI_SetCsHigh();
}

/**
* Read a 1-bit register
*/
uint8_t NRF24L01_ReadReg(uint8_t reg)
{
    uint8_t ret;
    SPI_SetCsLow();
    Spi_TxRx(reg);
    ret = Spi_TxRx(NRF24L01_CMD_NOP);
    SPI_SetCsHigh();
    return ret;
}

/**
* Write a 1-byte register
*/
uint8_t NRF24L01_WriteReg(uint8_t reg, uint8_t value)
{
    uint8_t status;
    SPI_SetCsLow();
    if (reg < NRF24L01_CMD_W_REGISTER)
    {
        // This is a register access
        status = Spi_TxRx(NRF24L01_CMD_W_REGISTER | (reg & NRF24L01_MASK_REG_MAP));
        Spi_TxRx(value);
    }
    else
    {
        // This is a single byte command or future command/register
        status = Spi_TxRx(reg);
        if ((reg != NRF24L01_CMD_FLUSH_TX) 
            && (reg != NRF24L01_CMD_FLUSH_RX) 
            && (reg != NRF24L01_CMD_REUSE_TX_PL) 
            && (reg != NRF24L01_CMD_NOP)) {
            // Send register value
            Spi_TxRx(value);
        }
    }
    SPI_SetCsHigh();
    return status; 
}

/**
* Read a multi-byte register
*  reg  - register to read
*  buf  - pointer to the buffer to write
*  len  - number of bytes to read
*/
uint8_t NRF24L01_ReadToBuf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
    SPI_SetCsLow();
    uint8_t status = Spi_TxRx(reg);
    Spi_TxRxBytes(pBuf, len);
    SPI_SetCsHigh();
    return status;
}

/**
* Write a multi-byte register
*  reg - register to write
*  buf - pointer to the buffer with data
*  len - number of bytes to write
*/
void NRF24L01_WriteFromBuf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
    SPI_SetCsLow();
    Spi_TxRx(reg);
    Spi_TxBytes(pBuf, len);
    SPI_SetCsHigh();
}

uint8_t NRF24L01_SPI_Check(void)
{
    uint8_t i, addr[NRF24L01_ADDR_WIDTH];
    uint8_t *ptr = (uint8_t *)NRF24L01_TEST_ADDR;
    NRF24L01_WriteFromBuf(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_TX_ADDR, ptr, NRF24L01_ADDR_WIDTH);
    NRF24L01_ReadToBuf(NRF24L01_CMD_R_REGISTER | NRF24L01_REG_TX_ADDR, addr, NRF24L01_ADDR_WIDTH);
    for (i = 0; i < NRF24L01_ADDR_WIDTH; i++) 
    {
        Uart1_TxHex8Bit(addr[i]);
        if (addr[i] != *ptr++) return 1;
    }
    Uart1_TxChar(' ');
    return 0;
}

/**
* Flush the RX FIFO
*/
void NRF24L01_FlushRX(void)
{
    NRF24L01_WriteReg(NRF24L01_CMD_FLUSH_RX, NRF24L01_CMD_NOP);
}

/**
* Flush the TX FIFO
*/
void NRF24L01_FlushTX(void)
{
    NRF24L01_WriteReg(NRF24L01_CMD_FLUSH_TX, NRF24L01_CMD_NOP);
}


void NRF24L01_ResetTX(void)
{
    //Clear max retry flag
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_STATUS, NRF24L01_FLAG_MAX_RT);
    NRF_CE_Low();
    __NOP();
    NRF_CE_High();
}

/**
* Clear IRQ bit of the STATUS register
*   reg - NRF24L01_FLAG_RX_DREADY
*         NRF24L01_FLAG_TX_DSENT
*         NRF24L01_FLAG_MAX_RT
*/
void NRF24L01_ClearIRQFlag(uint8_t reg)
{
    NRF24L01_WriteReg(NRF24L01_REG_STATUS, reg);
}

/**
* Clear RX_DR, TX_DS and MAX_RT bits of the STATUS register
*/
void NRF24L01_ClearIRQFlags(void) 
{
    uint8_t reg;
    reg  = NRF24L01_ReadReg(NRF24L01_REG_STATUS);
    reg |= NRF24L01_MASK_STATUS_IRQ;
    NRF24L01_WriteReg(NRF24L01_REG_STATUS, reg);
}

uint8_t NRF24L01_RxAvailable(uint8_t *pipe_num)
{
    uint8_t dat, pipe;
    dat = NRF24L01_ReadReg(NRF24L01_CMD_R_REGISTER | NRF24L01_REG_STATUS);
    pipe = (dat >> 1) & 0x07;
    if (pipe > 5)
        return 1;
    // If the caller wants the pipe number, include that
    if (pipe_num)
        *pipe_num = pipe;

    return 0;
}

void NRF24L01_Tx(uint8_t *pBuf)
{
    NRF_CE_Low();
    //NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_CONFIG, 0x0E);
    NRF24L01_WriteFromBuf(NRF24L01_CMD_W_TX_PAYLOAD, pBuf, NRF24L01_PLOAD_WIDTH);
    NRF_CE_High();
}

uint8_t NRF24L01_TxFast(void* pBuf)
{
    uint8_t dat;
    //Blocking only if FIFO is full. This will loop and block until TX is successful or fail
    do
    {
        dat = NRF24L01_ReadReg(NRF24L01_CMD_R_REGISTER | NRF24L01_REG_STATUS);
        if (dat & NRF24L01_FLAG_MAX_RT) return 1;
    } while (dat & NRF24L01_FLAG_TX_FULL);
    NRF24L01_WriteFromBuf(NRF24L01_CMD_W_TX_PAYLOAD, pBuf, NRF24L01_PLOAD_WIDTH);
    NRF_CE_High();
    return 0;
}

/**
* Common configurations
*/
void NRF24L01_Config(void)
{
    // RX P0 payload width
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RX_PW_P0, NRF24L01_PLOAD_WIDTH);
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RX_PW_P1, NRF24L01_PLOAD_WIDTH);
    // Enable auto ACK all pipes
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_EN_AA, 0x3f);
    // Enable RX all pipes
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_EN_RXADDR, 0x3f);
    // 0A:delay=250us,count=10, 1A:delay=500us,count=10
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_SETUP_RETR, 0x13);
    // RF channel 40 - 2.440GHz = 2.400G  + 0.040G
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RF_CH, 40);
    // 000+0+[0:1Mbps,1:2Mbps]+[00:-18dbm,01:-12dbm,10:-6dbm,11:0dbm]+[0:LNA_OFF,1:LNA_ON]
    // 01:1Mbps,-18dbm; 03:1Mbps,-12dbm; 05:1Mbps,-6dbm; 07:1Mbps,0dBm
    // 09:2Mbps,-18dbm; 0b:2Mbps,-12dbm; 0d:2Mbps,-6dbm; 0f:2Mbps,0dBm
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RF_SETUP, 0x07);

    NRF24L01_WriteFromBuf(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_TX_ADDR, (uint8_t *)NRF24L01_TEST_ADDR, NRF24L01_ADDR_WIDTH);
    NRF24L01_WriteFromBuf(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RX_ADDR_P0, (uint8_t *)NRF24L01_TEST_ADDR, NRF24L01_ADDR_WIDTH);
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RF_CH, 80);
}

/**
* Set RF Channel
* @param channel: 0 ~ 125 -> 2.400GHz ~ 2.525GHz
*/
void NRF24L01_SetRfChannel(uint8_t channel)
{
    if (channel > 125) channel = 125;
    // channel = 40 -> 2.400  + 0.040 = 2.440GHz
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RF_CH, channel);
}

/**
* Set RF data rate
* @param rate: 0:1Mbps, 1:2Mbps, 2:250Kbps
*/
void NRF24L01_SetRfDataRate(uint8_t rate)
{
    uint8_t dat = NRF24L01_ReadReg(NRF24L01_CMD_R_REGISTER | NRF24L01_REG_RF_SETUP);
    switch (rate)
    {
    case 0:
        dat = (dat & 0B11010111) | 0B00000000;
        break;
    case 1:
        dat = (dat & 0B11010111) | 0B00001000;
        break;
    case 2:
    default:
        dat = (dat & 0B11010111) | 0B00100000;
        break;
    }
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RF_SETUP, dat);
}

/**
* Set RF power
* @param power: 0:-18dBm, 1:-12dBm, 2:-6dBm, 3:0dBm
*/
void NRF24L01_SetRfPower(uint8_t power)
{
    uint8_t dat = NRF24L01_ReadReg(NRF24L01_CMD_R_REGISTER | NRF24L01_REG_RF_SETUP);
    dat = (dat & 0B11111001) | ((power & 0x03) << 1);
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_RF_SETUP, dat);
}

/**
* Set TX address
*/
void NRF24L01_SetTxAddr(uint8_t *txAddr)
{
    NRF24L01_WriteFromBuf(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_TX_ADDR, txAddr, NRF24L01_ADDR_WIDTH);
}

/**
* Set RX address of specified pipe
*/
void NRF24L01_SetRxAddr(uint8_t pipe, uint8_t *rxAddr)
{
    NRF24L01_WriteFromBuf(NRF24L01_CMD_W_REGISTER | (NRF24L01_REG_RX_ADDR_P0 + pipe), rxAddr, NRF24L01_ADDR_WIDTH);
}

/**
* Switch to TX mode
*/
void NRF24L01_SetTxMode(void)
{
    NRF_CE_Low();
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
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_CONFIG, 0x0E);
    NRF_CE_High();
}

/**
* Switch to RX mode
*/
void NRF24L01_SetRxMode(void)
{
    NRF_CE_Low();
    NRF24L01_WriteReg(NRF24L01_CMD_W_REGISTER | NRF24L01_REG_CONFIG, 0x0F);
    NRF_CE_High();
    NRF24L01_FlushRX();
}

uint8_t NRF24L01_RX_GetPayloadWidth(void)
{
    uint8_t value;
    NRF_CE_Low();
    value = NRF24L01_ReadReg(NRF24L01_CMD_R_RX_PL_WID);
    NRF_CE_High();
    return value;
}

uint8_t NRF24L01_RXFIFO_GetStatus(void)
{
    uint8_t reg = NRF24L01_ReadReg(NRF24L01_REG_FIFO_STATUS);
	return (reg & NRF24L01_MASK_RXFIFO);
}

uint8_t NRF24L01_ReadPayload(uint8_t *pBuf, uint8_t *length, uint8_t dpl)
{
    uint8_t status, pipe;

    // Extract a payload pipe number from the STATUS register
    status = NRF24L01_ReadReg(NRF24L01_REG_STATUS);
    pipe = (status & NRF24L01_MASK_RX_P_NO) >> 1;
    // RX FIFO empty?
    if (pipe < 6)
    {
        if (dpl)
        {
            // Get payload width
            *length = NRF24L01_RX_GetPayloadWidth();
            if (*length > 32)
            {
                // Error
                *length = 0;
                NRF24L01_FlushRX();
            }
        }
        else
        {
            *length = NRF24L01_ReadReg(NRF24L01_REG_RX_PW_P0 + pipe);
        }
        // Read a payload from the RX FIFO
        if (*length)
        {
            NRF24L01_ReadToBuf(NRF24L01_CMD_R_RX_PAYLOAD, pBuf, *length);
        }
        return pipe;
    }
    // pipe value = 110: Not Used, 111: RX FIFO Empty
    *length = 0;
    return pipe;
}

void NRF24L01_DumpConfig(void)
{
    uint8_t i, aw, buf[5];

    // STATUS
    Uart1_TxString("STATUS:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_STATUS));
    Uart1_TxString(", ");
    // CONFIG
    Uart1_TxString("CONFIG:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_CONFIG));
    Uart1_TxString(", ");
    // EN_AA
    Uart1_TxString("EN_AA:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_EN_AA));
    Uart1_TxString(", ");
    // EN_RXADDR
    Uart1_TxString("EN_RXADDR:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_EN_RXADDR));
    Uart1_TxString("\r\n");
    // SETUP_AW
    Uart1_TxString("SETUP_AW:0x");
    i = NRF24L01_ReadReg(NRF24L01_REG_SETUP_AW);
    aw = (i & 0x03) + 2;
    Uart1_TxHex8Bit(i);
    Uart1_TxString(", ");
    // SETUP_RETR
    Uart1_TxString("SETUP_RETR:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_SETUP_RETR));
    Uart1_TxString(", ");
    // RF_CH
    Uart1_TxString("RF_CH:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_RF_CH));
    Uart1_TxString(", ");
    // RF_SETUP
    Uart1_TxString("RF_SETUP:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_RF_SETUP));
    Uart1_TxString("\r\n");
    // OBSERVE_TX
    Uart1_TxString("OBSERVE_TX:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_OBSERVE_TX));
    Uart1_TxString(", ");
    // RPD
    Uart1_TxString("RPD:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_RPD));
    Uart1_TxString("\r\n");

    // NRF24L01_REG_FIFO_STATUS
    Uart1_TxString("FIFO_STATUS:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_FIFO_STATUS));
    Uart1_TxString(", ");
    // NRF24L01_REG_DYNPD
    Uart1_TxString("DYNPD:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_DYNPD));
    Uart1_TxString(", ");
    // NRF24L01_REG_FEATURE
    Uart1_TxString("FEATURE:0x");
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_FEATURE));
    Uart1_TxString("\r\n");

    // TX_ADDR
    Uart1_TxString("TX:");
    NRF24L01_ReadToBuf(NRF24L01_REG_TX_ADDR, buf, aw);
    Uart1_TxHexArray(buf, aw);
    Uart1_TxString("\r\n");
    // RX_ADDR_P0
    Uart1_TxString("P0:");
    NRF24L01_ReadToBuf(NRF24L01_REG_RX_ADDR_P0, buf, aw);
    Uart1_TxHexArray(buf, aw);
    Uart1_TxString("\r\n");
    // RX_ADDR_P1
    Uart1_TxString("P1:");
    NRF24L01_ReadToBuf(NRF24L01_REG_RX_ADDR_P1, buf, aw);
    Uart1_TxHexArray(buf, aw);
    Uart1_TxString("\r\n");
    // RX_ADDR_P2
    Uart1_TxString("P2:");
    Uart1_TxHexArray(buf, aw - 1);
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_RX_ADDR_P2));
    Uart1_TxString("\r\n");
    // RX_ADDR_P3
    Uart1_TxString("P3:");
    Uart1_TxHexArray(buf, aw - 1);
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_RX_ADDR_P3));
    Uart1_TxString("\r\n");
    // RX_ADDR_P4
    Uart1_TxString("P4:");
    Uart1_TxHexArray(buf, aw - 1);
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_RX_ADDR_P4));
    Uart1_TxString("\r\n");
    // RX_ADDR_P5
    Uart1_TxString("P5:");
    Uart1_TxHexArray(buf, aw - 1);
    Uart1_TxHex8Bit(NRF24L01_ReadReg(NRF24L01_REG_RX_ADDR_P5));
    Uart1_TxString("\r\n");


}