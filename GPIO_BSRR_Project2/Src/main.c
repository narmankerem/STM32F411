#include "stm32f411xe.h"

#define GPIOAEN          (1U<<0)
#define LED_PIN_SET      (1U<<5)
#define LED_PIN_RESET    (1U<<21)

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	while(1)
	{
		GPIOA->BSRR = LED_PIN_SET;
		for(int i = 0; i <= 100000; i++){}

		GPIOA->BSRR = LED_PIN_RESET;
		for(int i = 0; i <= 100000; i++){}
	}
}
