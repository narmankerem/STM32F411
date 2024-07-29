#include "uart.h"
#include <stdio.h>

int main(void)
{

	uart2TX_init();
	while(1)
	{
		printf("Hello from STM32F411...\n\r");

	}


}


