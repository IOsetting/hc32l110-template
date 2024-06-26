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

#ifndef __FW_RNF24L01_H__
#define __FW_RNF24L01_H__

#include "ddl.h"
#include "spi.h"
#include "string.h"

// CSN P14
#define NRF_CSN_PORT    1
#define NRF_CSN_PIN     4
// CE  P26
#define NRF_CE_PORT     2
#define NRF_CE_PIN      6
// IRQ P32
#define NRF_IRQ_PORT    3
#define NRF_IRQ_PIN     2
// MISO P23
// MOSI P24
// SCK  P25

#define NRF_CE_Low()    GPIO_SetPinOutLow(NRF_CE_PORT, NRF_CE_PIN)
#define NRF_CE_High()   GPIO_SetPinOutHigh(NRF_CE_PORT, NRF_CE_PIN)
#define IRQ()           GPIO_GetPinIn(NRF_IRQ_PORT, NRF_IRQ_PIN)

/**********  SPI(nRF24L01) commands  ***********/
// 
#define NRF24L01_CMD_R_REGISTER     0x00 // [000A AAAA] Register read
#define NRF24L01_CMD_W_REGISTER     0x20 // [001A AAAA] Register write
#define NRF24L01_CMD_R_RX_PAYLOAD   0x61 // Read RX payload
#define NRF24L01_CMD_W_TX_PAYLOAD   0xA0 // Write TX payload
#define NRF24L01_CMD_FLUSH_TX       0xE1 // Flush TX FIFO
#define NRF24L01_CMD_FLUSH_RX       0xE2 // Flush RX FIFO
#define NRF24L01_CMD_REUSE_TX_PL    0xE3 // Reuse TX payload
#define NRF24L01_CMD_R_RX_PL_WID    0x60 // Read RX-payload width for the top R_RX_PAYLOAD in the RX FIFO.
#define NRF24L01_CMD_W_ACK_PAYLOAD  0xA8 // [1010 1PPP] Write ACK Payload to be with ACK packet on PIPE PPP
#define NRF24L01_CMD_W_TX_PAYLOAD_NOACK 0xB0 //Write TX payload and disable AUTOACK
#define NRF24L01_CMD_NOP            0xFF // No operation (used for reading status register)

#define NRF24L01_CMD_ACTIVATE       0x50 // (De)Activates R_RX_PL_WID, W_ACK_PAYLOAD, W_TX_PAYLOAD_NOACK features
#define NRF24L01_CMD_LOCK_UNLOCK    0x50 // Lock/unlock exclusive features

// SPI(nRF24L01) register address definitions
#define NRF24L01_REG_CONFIG         0x00 // Configuration register
#define NRF24L01_REG_EN_AA          0x01 // Enable "Auto acknowledgment"
#define NRF24L01_REG_EN_RXADDR      0x02 // Enable RX addresses
#define NRF24L01_REG_SETUP_AW       0x03 // Setup of address widths
#define NRF24L01_REG_SETUP_RETR     0x04 // Setup of automatic re-transmit
#define NRF24L01_REG_RF_CH          0x05 // RF channel
#define NRF24L01_REG_RF_SETUP       0x06 // RF setup
#define NRF24L01_REG_STATUS         0x07 // Status register
#define NRF24L01_REG_OBSERVE_TX     0x08 // Transmit observe register
#define NRF24L01_REG_RPD            0x09 // Received power detector
#define NRF24L01_REG_RX_ADDR_P0     0x0A // Receive address data pipe 0
#define NRF24L01_REG_RX_ADDR_P1     0x0B // Receive address data pipe 1
#define NRF24L01_REG_RX_ADDR_P2     0x0C // Receive address data pipe 2
#define NRF24L01_REG_RX_ADDR_P3     0x0D // Receive address data pipe 3
#define NRF24L01_REG_RX_ADDR_P4     0x0E // Receive address data pipe 4
#define NRF24L01_REG_RX_ADDR_P5     0x0F // Receive address data pipe 5
#define NRF24L01_REG_TX_ADDR        0x10 // Transmit address
#define NRF24L01_REG_RX_PW_P0       0x11 // Number of bytes in RX payload in data pipe 0
#define NRF24L01_REG_RX_PW_P1       0x12 // Number of bytes in RX payload in data pipe 1
#define NRF24L01_REG_RX_PW_P2       0x13 // Number of bytes in RX payload in data pipe 2
#define NRF24L01_REG_RX_PW_P3       0x14 // Number of bytes in RX payload in data pipe 3
#define NRF24L01_REG_RX_PW_P4       0x15 // Number of bytes in RX payload in data pipe 4
#define NRF24L01_REG_RX_PW_P5       0x16 // Number of bytes in RX payload in data pipe 5
#define NRF24L01_REG_FIFO_STATUS    0x17 // FIFO status register
#define NRF24L01_REG_DYNPD          0x1C // Enable dynamic payload length
#define NRF24L01_REG_FEATURE        0x1D // Feature register

// Register bits definitions
#define NRF24L01_CONFIG_PRIM_RX     0x01 // PRIM_RX bit in CONFIG register
#define NRF24L01_CONFIG_PWR_UP      0x02 // PWR_UP bit in CONFIG register
#define NRF24L01_FEATURE_EN_DYN_ACK 0x01 // EN_DYN_ACK bit in FEATURE register
#define NRF24L01_FEATURE_EN_ACK_PAY 0x02 // EN_ACK_PAY bit in FEATURE register
#define NRF24L01_FEATURE_EN_DPL     0x04 // EN_DPL bit in FEATURE register
#define NRF24L01_FLAG_RX_DREADY     0x40 // RX_DR bit (data ready RX FIFO interrupt)
#define NRF24L01_FLAG_TX_DSENT      0x20 // TX_DS bit (data sent TX FIFO interrupt)
#define NRF24L01_FLAG_MAX_RT        0x10 // MAX_RT bit (maximum number of TX re-transmits interrupt)
#define NRF24L01_FLAG_TX_FULL       0x01 // 1:TX FIFO full

// Register masks definitions
#define NRF24L01_MASK_REG_MAP       0x1F // Mask bits[4:0] for CMD_RREG and CMD_WREG commands
#define NRF24L01_MASK_CRC           0x0C // Mask for CRC bits [3:2] in CONFIG register
#define NRF24L01_MASK_STATUS_IRQ    0x70 // Mask for all IRQ bits in STATUS register
#define NRF24L01_MASK_RF_PWR        0x06 // Mask RF_PWR[2:1] bits in RF_SETUP register
#define NRF24L01_MASK_RX_P_NO       0x0E // Mask RX_P_NO[3:1] bits in STATUS register
#define NRF24L01_MASK_DATARATE      0x28 // Mask RD_DR_[5,3] bits in RF_SETUP register
#define NRF24L01_MASK_EN_RX         0x3F // Mask ERX_P[5:0] bits in EN_RXADDR register
#define NRF24L01_MASK_RX_PW         0x3F // Mask [5:0] bits in RX_PW_Px register
#define NRF24L01_MASK_RETR_ARD      0xF0 // Mask for ARD[7:4] bits in SETUP_RETR register
#define NRF24L01_MASK_RETR_ARC      0x0F // Mask for ARC[3:0] bits in SETUP_RETR register
#define NRF24L01_MASK_RXFIFO        0x03 // Mask for RX FIFO status bits [1:0] in FIFO_STATUS register
#define NRF24L01_MASK_TXFIFO        0x30 // Mask for TX FIFO status bits [5:4] in FIFO_STATUS register
#define NRF24L01_MASK_PLOS_CNT      0xF0 // Mask for PLOS_CNT[7:4] bits in OBSERVE_TX register
#define NRF24L01_MASK_ARC_CNT       0x0F // Mask for ARC_CNT[3:0] bits in OBSERVE_TX register

// Register masks definitions
#define NRF24L01_MASK_REG_MAP       0x1F // Mask bits[4:0] for CMD_RREG and CMD_WREG commands

// RXFIFO status
#define NRF24L01_RXFIFO_STATUS_DATA  0x00 // The RX FIFO contains data and available locations
#define NRF24L01_RXFIFO_STATUS_EMPTY 0x01 // The RX FIFO is empty
#define NRF24L01_RXFIFO_STATUS_FULL  0x02 // The RX FIFO is full
#define NRF24L01_RXFIFO_STATUS_ERROR 0x03 // Impossible state: RX FIFO cannot be empty and full at the same time

#define NRF24L01_ADDR_WIDTH         5    // RX/TX address width
#define NRF24L01_PLOAD_WIDTH        32   // Payload width
#define NRF24L01_TEST_ADDR          "nRF24"

typedef enum
{
    NRF24L01_MODE_RX  = 0x00,
    NRF24L01_MODE_TX  = 0x01
} NRF24L01_MODE;

typedef enum
{
    NRF24L01_SCEN_RX          = 0x00,
    NRF24L01_SCEN_TX          = 0x01,
    NRF24L01_SCEN_HALF_DUPLEX = 0x02
} NRF24L01_SCEN;

#ifdef __cplusplus
extern "C" {
#endif

void NRF24L01_Init(void);
uint8_t NRF24L01_ReadReg(uint8_t reg);
uint8_t NRF24L01_WriteReg(uint8_t reg, uint8_t value);

uint8_t NRF24L01_ReadToBuf(uint8_t reg, uint8_t *pBuf, uint8_t len);
void NRF24L01_WriteFromBuf(uint8_t reg, uint8_t *pBuf, uint8_t len);

uint8_t NRF24L01_SPI_Check(void);
/**
* Flush the RX FIFO
*/
void NRF24L01_FlushRX(void);

/**
* Flush the TX FIFO
*/
void NRF24L01_FlushTX(void);

void NRF24L01_ResetTX(void);

void NRF24L01_CheckFlag(uint8_t *tx_ds, uint8_t *max_rt, uint8_t *rx_dr);
uint8_t NRF24L01_RxAvailable(uint8_t* pipe_num);

void NRF24L01_Tx(uint8_t *pBuf);
uint8_t NRF24L01_TxFast(void* pBuf);


void NRF24L01_Config(void);


/**
* Set RF Channel
* @param channel: 0 ~ 125
*/
void NRF24L01_SetRfChannel(uint8_t channel);
/**
* Set RF data rate
* @param rate: 0:1Mbps, 1:2Mbps, 2:250Kbps
*/
void NRF24L01_SetRfDataRate(uint8_t rate);
/**
* Set RF power
* @param power: 0:-18dBm, 1:-12dBm, 2:-6dBm, 3:0dBm
*/
void NRF24L01_SetRfPower(uint8_t power);
/**
* Set TX address
*/
void NRF24L01_SetTxAddr(uint8_t *txAddr);
/**
* Set RX address of specified pipe
*/
void NRF24L01_SetRxAddr(uint8_t pipe, uint8_t *rxAddr);
/**
* Switch to TX mode
*/
void NRF24L01_SetTxMode(void);
/**
* Switch to RX mode
*/
void NRF24L01_SetRxMode(void);


uint8_t NRF24L01_RX_GetPayloadWidth(void);

uint8_t NRF24L01_RXFIFO_GetStatus(void);

uint8_t NRF24L01_ReadPayload(uint8_t *pBuf, uint8_t *length, uint8_t dpl);
/**
* Clear IRQ bit of the STATUS register
*   reg - NRF24L01_FLAG_RX_DREADY
*         NRF24L01_FLAG_TX_DSENT
*         NRF24L01_FLAG_MAX_RT
*/
void NRF24L01_ClearIRQFlag(uint8_t reg);
/**
* Clear RX_DR, TX_DS and MAX_RT bits of the STATUS register
*/
void NRF24L01_ClearIRQFlags(void);

void NRF24L01_DumpConfig(void);

#ifdef __cplusplus
}
#endif

#endif
