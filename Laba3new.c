#include "stm32f2xx.h"                // Device header
#include "stm32f207xx.h"
#include "core_cm3.h"


void delay1() {
	unsigned long i = 0;
	for (i = 0; i < 1000000; i++) {}  // Delay
}


void delay2() {
	unsigned long i = 0;
	for (i = 0; i < 1000; i++) {}  // Delay
}


void EXTI0_IRQHandler() {
	unsigned int i = 0;
	for (i = 0; i < 5; i++) {
		GPIOG->ODR |= GPIO_ODR_OD6;
		delay1();
		GPIOG->ODR &= ~GPIO_ODR_OD6;
		delay1();
	}
	EXTI->PR |= EXTI_PR_PR0;
}


void EXTI15_10_IRQHandler() {
	unsigned int i = 0;
	for (i = 0; i < 5; i++) {
		GPIOG->ODR |= GPIO_ODR_OD8;
		delay1();
		GPIOG->ODR &= ~GPIO_ODR_OD8;
		delay1();
	}
	EXTI->PR |= EXTI_PR_PR15;
}


int main() {
	RCC->AHB1ENR |= 1ul << 6;
	RCC->AHB1ENR |= 1ul << 0;
	RCC->APB2ENR |= 1ul << 14;
	delay2();
	
	GPIOG->MODER |= GPIO_MODER_MODE6_0;
	GPIOG->MODER |= GPIO_MODER_MODE7_0;
	GPIOG->MODER |= GPIO_MODER_MODE8_0;
	GPIOG->MODER &= ~GPIO_MODER_MODE15_1;
	GPIOA->MODER &= ~GPIO_MODER_MODE0_1;
	
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->IMR |= EXTI_IMR_MR15;
	EXTI->FTSR |= EXTI_FTSR_TR0;
	EXTI->RTSR |= EXTI_RTSR_TR15;
	
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI15_PG;
	
	NVIC_SetPriority(6, 1);
	NVIC_SetPriority(40, 0);;
	NVIC_EnableIRQ(6);
	NVIC_EnableIRQ(40);
	
	for(;;) {
		GPIOG->ODR |= GPIO_ODR_OD7;
		delay1();
		GPIOG->ODR &= ~GPIO_ODR_OD7;
		delay1();
	}
}