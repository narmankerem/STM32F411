#ifndef UART_H_
#define UART_H_

#include "stm32f411xe.h"

void uart2TX_init(void);
void uart2_RX_TX_init(void);
char uart2_read(void);

#endif /* UART_H_ */
