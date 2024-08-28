#include "stm32f411xe.h"

#define RCC_APB1ENR_TIMER2		(1U<<0)
#define TIMX_CR1				(1U<<0)
#define OC_TOGGLE				((1U<<4) | (1U<<5))
#define CCER_CC1E				(1U<<0)

#define GPIOAEN					(1U<<0)

#define AFR5_TIM				(1U<<20)

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

void timer2_pa5_output_compare (void)
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*Set PA5 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |= (1U<<11);
	/*Set PA5 alternate function type to TIM2_CH1 (af01)*/
	GPIOA->AFR[0] |= AFR5_TIM;
	/*Enable clock access to timer2*/
	RCC->APB1ENR |= RCC_APB1ENR_TIMER2;
	/*Set prescaler value*/
	TIM2->PSC = 1600 - 1; // 16 000 000 / 1 600 = 10 000
	/*Set auto-reload value*/
	TIM2->ARR = 10000 - 1;

	/*Set output compare toggle mode*/
	TIM2->CCMR1 = OC_TOGGLE;
	/*Enable tim2 ch1 in compare mode*/
	TIM2->CCER |= CCER_CC1E;

	/*Clear counter*/
	TIM2->CNT = 0;
	/*Enable timer*/
	TIM2->CR1 |= TIMX_CR1;
}
