#include "random.h"

uint16_t g_seed = 0;

void random_init(void)
{
   //init timer2
     rcc_periph_clock_enable(RCC_TIM2);
     timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT,
		    TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
     timer_set_period(TIM2, 0xFFFF);
     timer_enable_counter(TIM2);
   return;
}

void random_generate_seed (void)
{
   // check CTR value
   // seed = CTR value
   g_seed = TIM2_CNT;
   return;
}

uint16_t random_generate_number (void)
{
   // check CTR value
   // operate combining with seed XOR operation
   // update seed value
   // return num
   uint16_t num = 0;
   uint16_t cnt = TIM2_CNT;
   num = cnt ^ g_seed;
   g_seed = num;
   return num;
}
