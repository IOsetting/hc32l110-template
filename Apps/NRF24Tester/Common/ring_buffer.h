#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H

#include <stdint.h>

/* 
 * Max data length = RING_BUFFER_SIZE - 1
 */
#define RING_BUFFER_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif


void ring_buffer_clear(void);
/**
 * Push one char to the end of the ring
*/
void ring_buffer_push(uint8_t c);
/**
 * Pop one char from the end of the ring
*/
uint8_t ring_buffer_pop(uint8_t *ch);
/**
 * Read one char from specified position, negative for backward lookup
*/
uint16_t ring_buffer_fetch(int16_t index, uint8_t *ch);
/**
 * Read one char from specified position, without check if index is valid
*/
uint8_t ring_buffer_fetch_uncheck(int16_t index);
/**
 * Get the data size
*/
uint16_t ring_buffer_size(void);
/**
 * Read the whole buffer
*/
uint16_t ring_buffer_read(uint8_t *buf);

#ifdef __cplusplus
}
#endif

#endif /* __RING_BUFFER_H */