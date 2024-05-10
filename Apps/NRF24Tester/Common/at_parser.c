#include "at_parser.h"


#define AT_PREFIX     "AT+"
#define AT_RX_ADDR    "RXADDR="

uint32_t int_vals[16];

void str_to_ints(const char *str, uint32_t *ints);

void AT_Parse(const char *argv)
{
  uint8_t j;
  char * pos = (char *)argv;

  if (strstr(pos, AT_PREFIX) == pos)
  {
    pos += strlen(AT_PREFIX);
    if (strstr(pos, AT_RX_ADDR))
    {
      pos += strlen(AT_RX_ADDR);
      // convert str to integer array
      str_to_ints(pos, int_vals);
      for (j = 0; j < 16; j++)
      {
        Uart1_TxHex((uint8_t *)&int_vals[j], 4);
        Uart1_TxChar(' ');
      }
      Uart1_TxString("\r\n");
    }
  }
}


void str_to_ints(const char *str, uint32_t *ints)
{
  uint8_t flag = 0;
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
        ints++;
        flag = 0;
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