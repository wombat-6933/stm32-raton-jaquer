#ifndef _RANDOM_RJ_
#define _RANDOM_RJ_
#include <timer>

void random_init(void);
void random_generate_seed (void);
uint16_t random_generate_number (uint16_t seed);
#endif
