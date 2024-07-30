#include "uart.h"
#include <stdint.h>
#include <stdio.h>


#define GPIOAEN          (1U<<0)
#define UART2EN          (1U<<17)

#define LED_SET          (1U<<5)

char key;

int main(void)
{
	//CLOCK ACCESS FOR GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//SET PA5 AS OUTPUT PIN
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11);

	uart2_RX_TX_init();

	while(1)
	{
		if(key == '1')
			GPIOA->ODR |= LED_SET;
		else
			GPIOA->ODR &=~LED_SET;

	}


}


