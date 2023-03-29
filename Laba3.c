#include "stm32fxx.h"

void delay() {
	unsigned long i = 0;
	for (i = 0; i < 2000000; i++) {}
}

int main () {
	RCC->AHB1ENR |= lul<<6;
	RCC->AHB1ENR |= lul<<0;
	GPIOG->MODER = (GPIOG->MODER & ~lul<<15) | lul<<14;
	GPIOG->MODER = ()
	for (;;) {
		GPIOG->ODR |= lul<<7;
		delay();
		GPIOG->ODR &= ~lul<<7;
		delay();
	}
}