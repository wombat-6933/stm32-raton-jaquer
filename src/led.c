#include "led.h"

void setup_led_debug(void)
{
   //Enable GPIO port C
   RCC_APB2ENR = RCC_APB2ENR_IOPCEN;

   // manual configuration
//   GPIOC_CRH = 0x44244444;
   gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ,
              GPIO_CNF_OUTPUT_PUSHPULL,  GPIO13);

   return;
}

//void led_debug_on() { GPIOC_ODR |= (1 << 13); }
void led_debug_off() { gpio_set (GPIOC, GPIO13); }
void led_debug_on() { gpio_clear (GPIOC, GPIO13); }
void led_debug_blink_ms(uint32_t time_ms)
{
   uint32_t wait = time_ms * APROX_1_MS;
   uint32_t i = 0;

   led_debug_off();
   for (i = 0; i < wait; i++);
   led_debug_on();
   for (i = 0; i < wait; i++);
}

