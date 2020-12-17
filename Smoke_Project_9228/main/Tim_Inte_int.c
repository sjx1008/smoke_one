#include "main.h"
void TIM_Clk_int(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure;
	
	NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPriority = 3; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 5310;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;

	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM7,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM7,TIM_FLAG_Update);  
	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);   
	TIM_Cmd(TIM7,ENABLE);    
}

