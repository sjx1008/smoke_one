#include "APP_Sleeping.h"
#include "main_2.h"
#include "main.h"
#include "adc.h"
#include "crc.h"
#include "dma.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"
#include "WM_Disp.h"
#include "GUI.h"
#include "GUI_Private.h"
#include "WM.h"
//#include "malloc.h"
u16	R_SleepTim;
#define	d_SleepTim_max	600

void (*Disp_Sleep)(void)=Disp_Sleep_NOP;				//ÊòæÁ§∫ËøõÂÖ•‰ºëÁú†Êó∂ÁöÑÈí©Â≠êÂáΩÊï∞
void	Disp_Sleep_NOP(void)
{
	__NOP();
}


vu8	B_fast_Sleep=0;
u8	B_USB_inquiry=0;
void	Sleeping_Peripheral(void)
{
	LL_GPIO_InitTypeDef   GPIO_InitStructure;
	LL_EXTI_InitTypeDef   EXTI_InitStructure;

	LL_EXTI_DeInit();
	USB_DISABLE_transmission();
	Watchdog_OFF();

	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA | LL_AHB1_GRP1_PERIPH_GPIOB | LL_AHB1_GRP1_PERIPH_GPIOC | LL_AHB1_GRP1_PERIPH_GPIOD | LL_AHB1_GRP1_PERIPH_GPIOH);

	LL_GPIO_WriteOutputPort(GPIOA,0x8000);
	LL_GPIO_WriteOutputPort(GPIOB,0x0008);
	LL_GPIO_WriteOutputPort(GPIOC,0x1C00);
	LL_GPIO_WriteOutputPort(GPIOD,0x0004);
	LL_GPIO_WriteOutputPort(GPIOH,0x0000);

	GPIO_InitStructure.Mode=LL_GPIO_MODE_ANALOG;
	GPIO_InitStructure.OutputType=LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStructure.Pull=LL_GPIO_PULL_NO;
	GPIO_InitStructure.Speed=LL_GPIO_SPEED_FREQ_LOW;

	GPIO_InitStructure.Pin=0x7F7F;
	LL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.Pin=0xFFF7;
	LL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.Pin=0x23FF;
	LL_GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.Pin=0x0003;
	LL_GPIO_Init(GPIOH, &GPIO_InitStructure);

	GPIO_InitStructure.Mode=LL_GPIO_MODE_OUTPUT;
	GPIO_InitStructure.Pull=LL_GPIO_PULL_UP;
	GPIO_InitStructure.Pin=0x0008;
	LL_GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.Pin=0x0004;
	LL_GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_InitStructure.Mode=LL_GPIO_MODE_INPUT;

	GPIO_InitStructure.Pin=0x1000;
	LL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.Pull=LL_GPIO_PULL_NO;
	GPIO_InitStructure.Pin=0x0080;
	LL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1),LL_ADC_PATH_INTERNAL_NONE);
	LL_DMA_DeInit(DMA2,LL_DMA_STREAM_ALL);
	LL_DMA_DeInit(DMA1,LL_DMA_STREAM_ALL);
	LL_SPI_DeInit(SPI1);
	LL_ADC_DeInit(ADC1);
	LL_TIM_DeInit(TIM1);
	LL_TIM_DeInit(TIM2);
	LL_TIM_DeInit(TIM3);
	LL_TIM_DeInit(TIM4);
	LL_TIM_DeInit(TIM10);
	LL_ADC_CommonDeInit(ADC1_COMMON);
	LL_ADC_DisableIT_AWD1(ADC1);

	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);
	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM3);
	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM4);
	LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM1);
	LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM10);
	LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_CRC);
	LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ADC1);
	LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);


	LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPIOA | LL_AHB1_GRP1_PERIPH_GPIOB | LL_AHB1_GRP1_PERIPH_GPIOC | LL_AHB1_GRP1_PERIPH_GPIOD | LL_AHB1_GRP1_PERIPH_GPIOH);
	/* Enable SYSCFG clock */
	__HAL_RCC_SYSCFG_CLK_ENABLE();

	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE12);
	LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE7);
	/**/
	EXTI_InitStructure.Line_0_31 = LL_EXTI_LINE_7|LL_EXTI_LINE_12;
	EXTI_InitStructure.LineCommand = ENABLE;
	EXTI_InitStructure.Mode = LL_EXTI_MODE_IT;
	EXTI_InitStructure.Trigger = LL_EXTI_TRIGGER_RISING_FALLING;
	LL_EXTI_Init(&EXTI_InitStructure);
	/* EXTI interrupt init*/
	NVIC_SetPriority(EXTI9_5_IRQn, 0);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_SetPriority(EXTI15_10_IRQn, 0);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
	LL_EXTI_DeInit();
	SystemClock_Config();
	LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_7|LL_EXTI_LINE_12);
	/* EXTI interrupt init*/
	NVIC_DisableIRQ(EXTI9_5_IRQn);
	NVIC_DisableIRQ(EXTI15_10_IRQn);

	NVIC_DisableIRQ(EXTI15_10_IRQn);
	NVIC_DisableIRQ(ADC_IRQn);
}

void	Sleeping_Module(void)
{
//	static u8 B_Sleeping;

//	NVIC_InitTypeDef   NVIC_InitStructure;

	if(R_Bright_screen_Time || (B_BAT_Charge && (!B_BAT_Congman || !B_BAT_Congman2)))
	{
		if(B_System_off!=d_System_Normal)
		{
			R_SleepTim=20;
		}
		else
		{
			if(R_BATT_Actual<(d_Bat_OUT_Volt_min-15) && !R_XY_Tim_yanshi)
				B_fast_Sleep=1;
			else if(R_BATT_Actual>(d_Bat_OUT_Volt_min-10))
				B_fast_Sleep=0;
			if(B_fast_Sleep && !B_BAT_Charge)
			{
				if(R_Bright_screen_Time+10<R_Bright_screen_TimeMAX)
					R_Bright_screen_Time=0;
				if(B_USB_RinBit)
					R_SleepTim=d_SleepTim_max;
				else
					R_SleepTim=20;
			}
			else
			{
				if(R_Bright_screen_TimeMAX+20>d_SleepTim_max)
					R_SleepTim=20;
				else
					R_SleepTim=d_SleepTim_max-R_Bright_screen_TimeMAX;
			}
		}
	}
	if(!B_USB_RinBit)
		B_USB_inquiry=0;
	if(B_USB_RinBit && B_USB_inquiry)
		return;
	if(!R_SleepTim)
	{
		if(R_Res_Initial>=d_Res_min && R_Res_Initial<d_Res_max && B_Sleep_YES!=1 && !B_BAT_error)
		{
			B_Sleep_YES=1;
			Enable_VoutADC_Use();
			R_Res_Sleep=Read_L_1C();
		}
//		OUT_12V_EN_OFF();
//		B_Sleeping=1;
//		if(!B_BAT_Charge || (B_BAT_Congman && B_BAT_Congman2))
		#if 1
		{
			Sleeping_Peripheral();
			R_SleepTim=20;								//–›√ﬂ ±º‰ºƒ¥Ê∆˜∏≥÷µ
			B_Skinning_init=1;
			B_Proportion_Init=0;
			B_KEY_JC=1;
			B_Again_Read=1;
			R_Read_Rtim=10;


			MX_GPIO_Init(1);
			TFT_LCD_RESET();
			MX_ADC1_Init();
			MX_SPI3_Init();
			MX_OUT_PWM_Init();
			MX_CHG_PWM_Init();
			MX_BL_PWM_Init();
			MX_LED_PWM_Init();
			MX_MOTOR_PWM_Init();
			USB_ENABLE_transmission();
			MX_CRC_Init();
			Flash_Init();
			Enable_VoutADC_Use();
			TFT_ST7789S_Init();
			Bring_AUTO_Init();
			Watchdog_ON();
		}
		#endif
	}
//	if(R_SleepTim)
//	{
//		OUT_12V_EN_ON();
//		if(B_Sleeping)
//		{
//			B_Sleeping=0;
//			Delay_Nms(40);
//		}
//	}
}



