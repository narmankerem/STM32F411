#include "uart.h"
#include <stdint.h>

#define GPIOAEN          (1U<<0)
#define UART2EN          (1U<<17)

#define CR1_TE           (1U<<3)
#define CR1_RE           (1U<<2)
#define CR1_UE           (1U<<13)

#define USART2_SR_TXE    (1U<<7)
#define USART2_SR_RXE    (1U<<5)

#define SYS_FREQ         16000000
#define APB1_CLK		 SYS_FREQ

#define BAUDRATE         115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_UART_bd(uint32_t PeriphClk, uint32_t BaudRate);

static void uart2_write(int ch);


int __io_putchar(int ch)
{
	uart2_write(ch);
	return (ch);
}

void uart2_RX_TX_init(void)
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

	/*Set PA3 mode to alternate function mode*/
	GPIOA->MODER &=~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	/*Set PA3 alternate function type to UART_RXTX (AF07)*/
	GPIOA->AFR[0] |= (1U<<12);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] &= ~(1U<<15);


	/****************Configure UART module ***************/
	/*Enable clock access to uart2 */
	RCC->APB1ENR |= UART2EN;

	/*Configure Baud Rate*/
	uart_set_baudrate(USART2, APB1_CLK, BAUDRATE);

	/*Configure transfer direction*/
	USART2->CR1 = (CR1_TE | CR1_RE);

	/*Enable UART2*/
	USART2->CR1 |= CR1_UE;
}

char uart2_read(void)
{
	/*Make sure receive data register is not empty*/
	while(!(USART2->SR & USART2_SR_RXE)){}
	/*Write to transmit data register*/
	return (USART2->DR);
}

void uart2_write(int ch)
{
	/*Make sure transmit data register is empty*/
	while(!(USART2->SR & USART2_SR_TXE)){}
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
