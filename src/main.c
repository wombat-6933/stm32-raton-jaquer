#include "main.h"
#include "led.h"
#include "usb_rj_mouse.h"
#include "random.h"
#include <libopencm3/stm32/f1/rcc.h>

int main(void) {

   init_rcc_configuration();
   random_init();
   setup_led_debug();

   led_debug_on();
   usb_rj_init();
   led_debug_off();

   random_generate_seed();

   usb_rj_run();

   ERROR_HALT_BLINK();
   return -1;
}

void init_rcc_configuration (void)
{
   const struct rcc_clock_scale clock =
   {
      .pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
      .pll_mul = RCC_CFGR_PLLMUL_PLL_CLK_MUL6,
      .usbpre = RCC_CFGR_USBPRE_PLL_CLK_NODIV,
      .hpre = RCC_CFGR_HPRE_DIV2,
      .ppre1 = RCC_CFGR_PPRE_NODIV,
      .ppre2 = RCC_CFGR_PPRE_NODIV,
      .adcpre = RCC_CFGR_ADCPRE_DIV6,
      .flash_waitstates = 0,

      .ahb_frequency = 24e6,
      .apb1_frequency = 24e6,
      .apb2_frequency = 24e6,
   };

   rcc_clock_setup_pll(&clock);
   return;
}
