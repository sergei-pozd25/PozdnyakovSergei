#include "stm32f2xx_hal.h"              // Keil::Device:STM32Cube HAL:Common


DAC_HandleTypeDef DacHandle; 
DAC_ChannelConfTypeDef sConfig; 

RCC_ClkInitTypeDef RCC_ClkInitStruct;
RCC_OscInitTypeDef RCC_OscInitStruct;

GPIO_InitTypeDef GPIO_InitStruct; 


void SystemClock_Config(void) {
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 240;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  HAL_RCC_OscConfig(& RCC_OscInitStruct); 
	
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK |
  RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(& RCC_ClkInitStruct, FLASH_LATENCY_3); 
}


void HAL_DAC_MspInit(DAC_HandleTypeDef *hdac) {
  __GPIOA_CLK_ENABLE(); 
  __DAC_CLK_ENABLE(); 
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, & GPIO_InitStruct); 
}


int main(void) {
	HAL_Init();
	SystemClock_Config();
	DacHandle.Instance = DAC;
	HAL_DAC_Init(& DacHandle);
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;

	HAL_DAC_ConfigChannel(& DacHandle, & sConfig, DAC_CHANNEL_1);
	HAL_DAC_SetValue(& DacHandle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2730);  //4095 quantization levels
	
	HAL_DAC_Start(& DacHandle, DAC_CHANNEL_1); 

	while(1) {}
}