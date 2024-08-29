#include <stdio.h>
#include <stdint.h>
#include "stm32f411xe.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"


int timestamp = 0;
/*HARDWARE Set up: Connect a jumper wire from PA5 to PA6*/
int main(void)
{
	timer2_pa5_output_compare();
	timer3_pa6_input_capture();

	while(1)
	{
		/*Wait until edge is captured*/
		while(!(TIM3->SR & TIMX_SR_CC1IF)){}
		/*Read captured Value*/
		timestamp = TIM3->CCR1;
	}
}




