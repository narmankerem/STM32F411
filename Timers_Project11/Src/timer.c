#include "stm32f411xe.h"

#define RCC_APB1ENR_TIMER2		(1U<<0)
#define TIMX_CR1				(1U<<0)

void timer2_1hz_init (void)
{
	/*Enable clock access to timer2*/
	RCC->APB1ENR |= RCC_APB1ENR_TIMER2;
	/*Set prescaler value*/
	TIM2->PSC = 1600 - 1; // 16 000 000 / 1 600 = 10 000
	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1;
	/*Clear counter*/
	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 |= TIMX_CR1;
}
