#include <stdio.h>
#include "stm32f411xe.h"

#define GPIOAEN          (1U<<0)
#define UART2EN          (1U<<17)

#define SYS_FREQ         16000000
#define APB1_CLK		 SYS_FREQ

#define BAUDRATE         115200

#define CR1_TE           (1U<<3)
#define CR1_UE           (1U<<13)

#define USART2_TXE           (1U<<7)

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_UART_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart2TX_init(void);
void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return (ch);
}

int main(void)
{


	while(1)
	{
		printf("Hello from STM32....\n\r");

	}


}


void uart2TX_init(void)
{
	/****************Configure UART GPIOA pin***************/
	/*Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	/*Set PA2 alternate function type to UART_TX (AF07)*/
	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);


	/****************Configure UART module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure Baud Rate*/
	uart_set_baudrate(USART2, APB1_CLK, BAUDRATE);

	/*Configure transfer direction*/
	USART2->CR1 = CR1_TE;

	/*Enable UART2*/
	USART2->CR1 |= CR1_UE;
}

void uart2_write(int ch)
{
	/*Make sure transmit data register is empty*/
	while(!(USART2->SR & USART2_TXE)){}
	/*Write to transmit data register*/
	USART2->DR = (ch & 0XFF);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_UART_bd(PeriphClk, BaudRate);
}

static uint16_t compute_UART_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
}

