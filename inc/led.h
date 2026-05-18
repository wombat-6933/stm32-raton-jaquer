#ifndef LED__
#define LED__

#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/f1/memorymap.h>
#include <libopencm3/stm32/f1/gpio.h>
#include <libopencm3/stm32/f1/rcc.h>

#define APROX_1_MS 2000 // based on the APB freq = 24MHz

//pc13 gpio embedded in board used as debug led
void setup_led_debug(void);
void led_debug_on(void);
void led_debug_off(void);
void led_debug_blink_ms(uint32_t time_ms);

#endif
