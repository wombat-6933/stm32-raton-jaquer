#ifndef _RANDOM_RJ_
#define _RANDOM_RJ_
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>

void random_init(void);
void random_generate_seed (void);
uint16_t random_generate_number (void);
#endif
