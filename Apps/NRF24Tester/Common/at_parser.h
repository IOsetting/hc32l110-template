#ifndef __AT_PARSER_H
#define __AT_PARSER_H

#include "main.h"

#define AT_PREFIX           "AT+"
#define AT_SET_RX_MODE      "RXMODE"
#define AT_SET_TX_MODE      "TXMODE"
#define AT_SET_RX_ADDR      "RXADDR="
#define AT_SET_TX_ADDR      "TXADDR="
#define AT_SET_RF_CHAN      "RFCH="
#define AT_SET_RF_RATE      "RFRATE="
#define AT_SET_RF_POWER     "RFPOWER="

#define AT_GET_RX_ADDR      "RXADDR"
#define AT_GET_TX_ADDR      "TXADDR"

typedef enum
{
    AT_Command_None,
    AT_Command_Unknown,

    AT_Command_SetRxMode,
    AT_Command_SetTxMode,
    AT_Command_SetRxAddr,
    AT_Command_SetTxAddr,
    AT_Command_SetRfCh,
    AT_Command_SetRfRate,
    AT_Command_SetRfPower,

    AT_Command_GetRxAddr,
    AT_Command_GetTxAddr,
} AT_Command_t;

#ifdef __cplusplus
extern "C" {
#endif


AT_Command_t AT_Parse(char *argv);

#ifdef __cplusplus
}
#endif

#endif // __AT_PARSER_H
