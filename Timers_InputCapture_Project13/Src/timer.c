#include "stm32f411xe.h"

#define RCC_APB1ENR_TIMER2		(1U<<0)
#define RCC_APB1ENR_TIMER3		(1U<<1)
#define TIMX_CR1				(1U<<0)
#define OC_TOGGLE				((1U<<4) | (1U<<5))
#define CCER_CC1E				(1U<<0)

#define GPIOAEN					(1U<<0)

#define AFR5_TIM				(1U<<20)
#define AFR6_TIM				(1U<<25)
#define CCER_CC1S				(1U<<0)

void timer2_1hz_init (void)
{
	/*Enable clock access to timer2*/
	RCC->APB1ENR |= RCC_APB1ENR_TIMER2;
	/*Set Prescaler value*/
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
	/*Set Prescaler value*/
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

void timer3_pa6_input_capture (void)
{
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;
	/*Set PA6 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |= (1U<<13);
	/*Set PA6 alternate function type to TIM3_CH1 (af02)*/
	GPIOA->AFR[0] |= AFR6_TIM;
	/*Enable clock access to timer2*/
	RCC->APB1ENR |= RCC_APB1ENR_TIMER3;
	/*Set Prescaler value*/
	TIM3->PSC = 16000 - 1;
	/*Set CH1 to capture at every edge*/
	TIM3->CCMR1 = CCER_CC1S;
	/*Set CH1 to capture at rising edge*/
	TIM3->CCER |= CCER_CC1E;
	/*Enable TIM3*/
	TIM3->CR1 = TIMX_CR1;














}
