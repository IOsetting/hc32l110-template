#include "ring_buffer.h"

static uint8_t ring_buffer[RING_BUFFER_SIZE];
// from: inclusive, to: exclusive
static volatile uint16_t from, to;

void ring_buffer_clear(void)
{
    from = 0;
    to = 0;
}

void ring_buffer_push(uint8_t c)
{
    ring_buffer[to++] = c;
    if (to >= RING_BUFFER_SIZE)
    {
        to = 0;
    }
    if (to == from)
    {
        from++;
        if (from >= RING_BUFFER_SIZE)
        {
            from = 0;
        }
    }
}

uint8_t ring_buffer_pop(uint8_t *ch)
{
    if (to == from) return 0;

    to = (to > 0)? to - 1 : RING_BUFFER_SIZE - 1;
    *ch = ring_buffer[to];
    return 1;
}

uint16_t ring_buffer_fetch(int16_t index, uint8_t *ch)
{
    uint16_t pos, buffer_size = ring_buffer_size();
    if (index >= 0)
    {
        if (index > buffer_size - 1) return 0;
        pos = (from + index) % RING_BUFFER_SIZE;
    }
    else
    {
        if (-index > buffer_size) return 0;
        pos = (to + index + RING_BUFFER_SIZE) % RING_BUFFER_SIZE;
    }
    *ch = ring_buffer[pos];
    return pos;
}

uint8_t ring_buffer_fetch_uncheck(int16_t index)
{
    if (index >= 0)
    {
        return ring_buffer[(from + index) % RING_BUFFER_SIZE];
    }
    else
    {
        return ring_buffer[(to + index + RING_BUFFER_SIZE) % RING_BUFFER_SIZE];
    }
}

uint16_t ring_buffer_size(void)
{
    if (to >= from)
    {
        return to - from;
    }
    else
    {
        return RING_BUFFER_SIZE - from + to;
    }
}

uint16_t ring_buffer_read(uint8_t *buf)
{
    uint16_t pos;
    if (to >= from)
    {
        pos = from;
        while(pos < to)
        {
            *buf++ = ring_buffer[pos++];
        }
        // end of string
        *buf = 0;
        return to - from;
    }
    else
    {
        pos = from;
        while(pos < RING_BUFFER_SIZE)
        {
            *buf++ = ring_buffer[pos++];
        }
        pos = 0;
        while(pos < to)
        {
            *buf++ = ring_buffer[pos++];
        }
        // end of string
        *buf = 0;
        return RING_BUFFER_SIZE - from + to;
    }
}
