#include <stdio.h>
#include <stdint.h>
#include "stm32f411xe.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"



#define GPIOAEN				   (1U<<0)
#define PIN5				   (1U<<5)

#define LED				   		PIN5

int main(void)
{


	/*1.Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*2.Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);



	uart2_tx_init();
	timer2_1hz_init();


	while(1)
	{
		/*wait for update interrupt flag*/
		while(!(TIM2->SR & TIMX_SR_UIF)){}

		/*clear UIF*/
		TIM2->SR &= ~TIMX_SR_UIF;


		printf("A second passed !! \n\r");
		GPIOA->ODR ^=LED;

	}

}




