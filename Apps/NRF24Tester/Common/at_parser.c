#include "at_parser.h"
#include "nrf24l01.h"


void AT_HandleAddr(char *argv, char *val);
void AT_HandleUint8(char *argv, char *val);

void str_to_ints(const char *str, uint32_t *ints, uint16_t size);

AT_Command_t AT_Parse(char *argv)
{
  char *pos = argv;

  if (strstr(pos, AT_PREFIX) == pos) // start with AT+
  {
    pos += strlen(AT_PREFIX);
    if (strstr(pos, AT_SET_RX_MODE)) // AT+RXMODE
    {
      return AT_Command_SetRxMode;
    }
    else if (strstr(pos, AT_SET_TX_MODE)) // AT+TXMODE
    {
      return AT_Command_SetTxMode;
    }
    else if (strstr(pos, AT_SET_RX_ADDR)) // AT+RXADDR=
    {
      pos += strlen(AT_SET_RX_ADDR);
      AT_HandleAddr(argv, pos);
      return AT_Command_SetRxAddr;
    }
    else if (strstr(pos, AT_SET_TX_ADDR)) // AT+TXADDR=
    {
      pos += strlen(AT_SET_TX_ADDR);
      AT_HandleAddr(argv, pos);
      return AT_Command_SetTxAddr;
    }
    else if (strstr(pos, AT_SET_RF_CHAN)) // AT+RFCH=
    {
      pos += strlen(AT_SET_RF_CHAN);
      AT_HandleUint8(argv, pos);
      return AT_Command_SetRfCh;
    }
    else if (strstr(pos, AT_SET_RF_RATE)) // AT+RFRATE=
    {
      pos += strlen(AT_SET_RF_RATE);
      AT_HandleUint8(argv, pos);
      return AT_Command_SetRfRate;
    }
    else if (strstr(pos, AT_SET_RF_POWER)) // AT+RFPOWER=
    {
      pos += strlen(AT_SET_RF_POWER);
      AT_HandleUint8(argv, pos);
      return AT_Command_SetRfPower;
    }

    else if (strstr(pos, AT_GET_STATUS)) // AT+STATUS
    {
      return AT_Command_GetTStatus;
    }
    else if (strstr(pos, AT_GET_RX_ADDR)) // AT+RXADDR
    {
      return AT_Command_GetRxAddr;
    }
    else if (strstr(pos, AT_GET_TX_ADDR)) // AT+TXADDR
    {
      return AT_Command_GetTxAddr;
    }
    else
    {
      return AT_Command_Unknown;
    }
  }
  return AT_Command_None;
}

void AT_HandleAddr(char *argv, char *val)
{
  uint8_t i;
  uint32_t int_vals[5];

  // convert str to integer array
  str_to_ints(val, int_vals, 5);

  for (i = 0; i < 5; i++)
  {
    *(argv + i) = (uint8_t)int_vals[i];
  }
}

void AT_HandleUint8(char *argv, char *val)
{
  uint8_t int_val = 0, idx = 0;

  while(*val != 0 && idx < 3)
  {
    if (*val >= '0' && *val <= '9')
    {
      int_val = int_val * 10 + (*val - '0');
      idx++;
    }
    val++;
  }
  *argv = int_val;
}


void str_to_ints(const char *str, uint32_t *ints, uint16_t size)
{
  uint8_t flag = 0;
  uint16_t idx = 0;
  char *pos = (char *)str;
  while (*pos)
  {
    if (flag)
    {
      if (*pos >= '0' && *pos <= '9')
      {
        *ints = (*ints << 4) + (*pos & 0x0F);
      }
      else if ((*pos >= 'A' && *pos <= 'F') || (*pos >= 'a' && *pos <= 'f'))
      {
        *ints = (*ints << 4) + (*pos & 0x0F) + 9;
      }
      else
      {
        ints++; idx++;
        flag = 0;
        if (idx == size) break;
        if (*pos == 0) break;
      }
      pos++;
    }
    else
    {
      if (*pos == 0 || *(pos + 1) == 0) break;
      if (*pos == '0' && (*(pos+1) == 'x' || *(pos+1) == 'X'))
      {
        flag = 1;
        *ints = 0U;
        pos = pos + 2;
      }
      else
      {
        pos++;
      }
    }
  }
}

void str_shift_left(char *str, uint32_t i)
{
  // if i > str length, str becomes empty
  if (i < strlen(str)) 
  {
    while(*(str + i))
    {
      *str = *(str + i);
      str++;
    }
  }
  // add the trailing '\0'
  *str = 0;
}