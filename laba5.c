#include "stm32f2xx_hal.h"

#define DACx_CHANNEL1_GPIO_CLK_ENABLE() __GPIOA_CLK_ENABLE()
#define DMAx_CLK_ENABLE() __DMA1_CLK_ENABLE()

#define DACx_CHANNEL1_PIN GPIO_PIN_4
#define DACx_CHANNEL1_GPIO_PORT GPIOA

#define DACx_CHANNEL1 DAC_CHANNEL_1

#define DACx_DMA_CHANNEL1 DMA_CHANNEL_7
#define DACx_DMA_STREAM1 DMA1_Stream5

DAC_HandleTypeDef DacHandle;
static DAC_ChannelConfTypeDef sConfig;
int i;
const uint8_t Wave[6] = {0x00, 0x33, 0x66,  0x99, 0xCC, 0xFF}; 

static void DAC_Ch1_WaveConfig(void);
static void TIM6_Config(void);
static void SystemClock_Config(void);

void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{
 GPIO_InitTypeDef GPIO_InitStruct;
 static DMA_HandleTypeDef hdma_dac1;

 __DAC_CLK_ENABLE();

 DACx_CHANNEL1_GPIO_CLK_ENABLE();

 DMAx_CLK_ENABLE();

 GPIO_InitStruct.Pin = DACx_CHANNEL1_PIN;
 GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 HAL_GPIO_Init(DACx_CHANNEL1_GPIO_PORT, & GPIO_InitStruct);

 hdma_dac1.Instance = DACx_DMA_STREAM1;
 hdma_dac1.Init.Channel = DACx_DMA_CHANNEL1;
 hdma_dac1.Init.Direction = DMA_MEMORY_TO_PERIPH;
 hdma_dac1.Init.PeriphInc = DMA_PINC_DISABLE;
 hdma_dac1.Init.MemInc = DMA_MINC_ENABLE;
 hdma_dac1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
 hdma_dac1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
 hdma_dac1.Init.Mode = DMA_CIRCULAR;
 hdma_dac1.Init.Priority = DMA_PRIORITY_HIGH; 
 
 hdma_dac1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
 hdma_dac1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
 hdma_dac1.Init.MemBurst = DMA_MBURST_SINGLE;
 hdma_dac1.Init.PeriphBurst = DMA_PBURST_SINGLE;
 HAL_DMA_Init(& hdma_dac1);

 __HAL_LINKDMA(hdac, DMA_Handle1, hdma_dac1);}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim){
 __TIM6_CLK_ENABLE();}

int main(void){
 HAL_Init();
 SystemClock_Config();
 DacHandle.Instance = DAC;
 TIM6_Config();
 DAC_Ch1_WaveConfig();
 while (1) {}}

static void SystemClock_Config(void){
 RCC_ClkInitTypeDef RCC_ClkInitStruct;
 RCC_OscInitTypeDef RCC_OscInitStruct;
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
 
 HAL_RCC_ClockConfig(& RCC_ClkInitStruct, FLASH_LATENCY_3);}

 static void DAC_Ch1_WaveConfig(void){
 HAL_DAC_Init(& DacHandle);
 sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
 sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
 HAL_DAC_ConfigChannel(& DacHandle, & sConfig, DACx_CHANNEL1);

 HAL_DAC_Start_DMA(& DacHandle, DACx_CHANNEL1, (uint32_t *)Wave, 6, DAC_ALIGN_12B_R);
 HAL_DAC_Start(& DacHandle, DACx_CHANNEL1);

 HAL_DAC_SetValue(& DacHandle, DACx_CHANNEL1, DAC_ALIGN_12B_R, 0x100);}

void TIM6_Config(void){
 static TIM_HandleTypeDef htim;
 TIM_MasterConfigTypeDef MasterConfig;

 htim.Instance = TIM6;
 htim.Init.Period = 0x7FF;
 htim.Init.Prescaler = 0;
 htim.Init.ClockDivision = 0;
 htim.Init.CounterMode = TIM_COUNTERMODE_UP;
 HAL_TIM_Base_Init(& htim);
	
 MasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
 MasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
 HAL_TIMEx_MasterConfigSynchronization(& htim, & MasterConfig);

 HAL_TIM_Base_Start(& htim);}