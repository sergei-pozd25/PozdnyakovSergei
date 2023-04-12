#include "stm32f207xx.h"
#include "stm32f2xx.h"                 // Device header
#include "core_cm3.h"

void delay(int delay)
{
	int i = 0;
	for(i=0; i < delay; i++) {}
}


 void EXTI0_IRQHandler() {
	delay(2000000);
	SCB->SCR ^= SCB_SCR_SLEEPONEXIT_Msk;
	EXTI->RTSR ^= EXTI_RTSR_TR0;
	EXTI->FTSR ^= EXTI_FTSR_TR0;
	EXTI->PR |= EXTI_PR_PR0;
}


void TIM6_DAC_IRQHandler() {
	if(!(TIM6->SR & TIM_SR_UIF)) {
		return;} 
	if (TIM6->CNT) {
		return;}
	GPIOG->ODR ^= GPIO_ODR_ODR_6 | GPIO_ODR_ODR_7;
	TIM6->SR &= ~TIM_SR_UIF;
}


int main ()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN | RCC_AHB1ENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	delay(10);
		
	GPIOG->MODER |= (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);
	GPIOG->MODER &= ~(GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1);
		
	GPIOG->OTYPER &= ~GPIO_OTYPER_OT_6 | ~GPIO_OTYPER_OT_7;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7;
	
	GPIOG->ODR |= GPIO_ODR_ODR_6;
	GPIOG->ODR &= ~GPIO_ODR_ODR_7;	
		
	GPIOA->MODER &= ~GPIO_MODER_MODER0;

	EXTI->IMR |= EXTI_IMR_MR0;
	
	EXTI->RTSR |= EXTI_RTSR_TR0;
	EXTI->FTSR &= ~EXTI_RTSR_TR0;
		
	TIM6->PSC = 8400-1;
	TIM6->CNT = 0;
	TIM6->ARR = 1000-1;
	TIM6->DIER = TIM_DIER_UIE;
	TIM6->CR1 |= TIM_CR1_CEN;
	
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
	
	//{
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	PWR->CR &= PWR_CR_PDDS;
	PWR->CR |= PWR_CR_LPDS;
	//}
	
	//{
	NVIC_SetPriorityGrouping(5);
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(TIM6_DAC_IRQn, 4);
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	//}
	
	while(1) {}
}

