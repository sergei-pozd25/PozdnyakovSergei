#include "stm32f2xx.h"                  // Device header

void delay() {
	unsigned long i = 0;
	for (i = 0; i < 1000000; i++) {}
}

int main () {
	RCC->AHB1ENR |= 1ul<<6; // PORTS ACTIVATION
	RCC->AHB1ENR |= 1ul<<0;	
	RCC->AHB1ENR |= 1ul<<7;
		
	GPIOH->MODER = (GPIOH->MODER & ~1ul<<15) | 1ul<<14;  // OUTPUT PORTS
	GPIOH->MODER = (GPIOH->MODER & ~1ul<<13) | 1ul<<12;
	GPIOH->MODER = (GPIOH->MODER & ~1ul<<7) | 1ul<<6;
		
	GPIOG->MODER = (GPIOG->MODER & ~1ul<<31) & ~1ul<<30;  // INPUT PORTS
	GPIOA->MODER = (GPIOA->MODER & ~1ul<<1) & ~1ul<<0;
	
	for (;;) {
		
		GPIOH->ODR |= 1ul<<6;
		delay();
		GPIOH->ODR &= ~1ul<<6;
		delay();
	
	}
}