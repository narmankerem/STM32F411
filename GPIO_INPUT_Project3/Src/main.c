#include "stm32f411xe.h"

#define GPIOAEN          (1U<<0)
#define GPIOCEN          (1U<<2)

#define BTN 			 (1U<<13)
#define LED_PIN_SET      (1U<<5)
#define LED_PIN_RESET    (1U<<21)

int main(void)
{
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;

	//CONFIGURE LED AS A OUTPUT
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	//CONFIGURE PUSH_BUTTON AS AN INPUT
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	while(1)
	{

		if(GPIOC->IDR & BTN)
			GPIOC->BSRR = LED_PIN_SET;
		else
			GPIOC->BSRR = LED_PIN_RESET;
	}
}
