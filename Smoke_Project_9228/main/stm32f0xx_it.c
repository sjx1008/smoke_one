/**
  ******************************************************************************
  * @file    GPIO_IOToggle/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
#include "WM_Disp.h"
/** @addtogroup STM32F072B_DISCOVERY_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
	NVIC_SystemReset();
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
		NVIC_SystemReset();
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
	NVIC_SystemReset();
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
	NVIC_SystemReset();
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(TimingDelay)
	{
		TimingDelay--; 
	}
	else
	{
		SysTick_CSR=0x06;// ??SysTick??? 
	}
}

void USB_IRQHandler(void)
{
  USB_Istr();
}


/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/
void TIM7_IRQHandler(void)
{
	static u8		B_Res_BAT_JC=0;
	static u8 	Tim10ms=0,Tim20ms=0,Tim100ms=0,Tim250ms=0;
	static u16	Tim1s=0;/*Tim500ms=0,Tim1s=0,Tim2s=0;*/
	TIM_ClearFlag(TIM7,TIM_FLAG_Update);
	
	Tim10ms++;
	Tim20ms++;
	Tim100ms++;
	Tim250ms++;
//	Tim500ms++;	
	Tim1s++;
//	Tim2s++;
	B_USB_PWER_JC=1;
	B_Charg_Jianche=1;
	B_Out_JC=1;
	if(USBovertime)
	{
		USBovertime--;
	}
	if(R_KEY_timi)
	{
		R_KEY_timi--;
	}
	if(R_Read_Rtim)
	{
		R_Read_Rtim--;
	}
	if(R_ADTCtim)
	{
		R_ADTCtim--;
	}
	if(Tim10ms>=10)
	{
		Tim10ms=0;
		/////////////////////////////
		if(R_Flash_WB)
			R_Flash_WB--;
		if(B_Out_Yes)
		{
			if(R_Custom_I_Set<d_Custom_I_MAX)
			{
				if(R_Custom_tim<50)
				{
					R_Custom_tim++;
				}
				else
				{
					R_Custom_I_Set++;
					R_Custom_tim=0;
				}
			}
		}
		else
		{
			R_Custom_tim=0;
			R_Custom_I_Set=0;
			if(R_again_Tim)
				R_again_Tim--;
		}
		///////////////////////
	}
	
	if(Tim20ms>=20)
	{
		Tim20ms=0;
		/////////////////////////////
		B_KEY_JC=1;
		B_load_JC=1;
		///////////////////////
	}
	
	if(Tim100ms>=100)
	{
		Tim100ms=0;
		/////////////////////////////
		if(R_Interface_maintain_Time)
			R_Interface_maintain_Time--;
		if(R_Bright_screen_Time)
			R_Bright_screen_Time--;
		if(R_USB_error_Tim)
			R_USB_error_Tim--;
		if(R_XY_Tim_yanshi)
			R_XY_Tim_yanshi--;
		if(B_Out_Yes)
		{
			if(R_Smoke_Tim<R_User_Smoke_Tim_max)
				R_Smoke_Tim++;
		}
		if(R_SleepTim)
		{
			R_SleepTim--;
		}
		Watchdog_Reset();
		///////////////////////
	}
	if(Tim250ms>=250)
	{
		Tim250ms=0;
			/////////////////////////////
//		
		B_Res_BAT_JC=!B_Res_BAT_JC;
		if(B_Res_BAT_JC)
		{
			B_BAT_Jianche=1;
		}
		B_Read_RTC=1;
		#ifdef	Gyroscope_ENABLE
			B_G3D_JC=1;
		#endif
		///////////////////////	
	}
			
//	if(Tim500ms>=500)
//	{
//		Tim500ms=0;
//		/////////////////////////////

//		///////////////////////
//	}
	
	if(Tim1s>=1000)
	{
		Tim1s=0;
		/////////////////////////////
		if(B_BAT_Charge && !B_Out_Yes)
		{
			if(R_Charging_Tim<d_Charging_Tim_Max)
				R_Charging_Tim++;
			if(R_Batter_Interface_Tim<d_Charging_Tim_Max && (!B_BAT_Congman || !B_BAT_Congman2))
				R_Batter_Interface_Tim++;
		}
		///////////////////////
	}
//	if(Tim2s>=2000)
//	{
//		Tim2s=0;
//		/////////////////////////////
//		
//		///////////////////////
//	}
}


void EXTI0_1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI4_15_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

////////////////////////±È½ÏÆ÷ÖÐ¶Ï
void ADC1_COMP_IRQHandler(void)
{
  if((EXTI_GetITStatus(EXTI_Line21) != RESET))
  {
    /* Check input voltage level: within the thresholds, above the upper threshold
       or under the lower threshold */
    
    /* Clear EXTI21 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line21);
		TIM1->CCR2 = 0;
		TIM1->CCR3 = OUT_PWM_Period;
		PWM_data=0;
		OUT_En_DCDC_OFF();
		COMP->CSR &= (uint32_t)(~((uint32_t)1<<COMP_Selection_COMP1));
		B_Smoking_mark=0;
		B_Short_Circuit=1;
  }
	if(ADC_GetITStatus(ADC1, ADC_IT_AWD) != RESET)
  {
		ADC_ClearITPendingBit(ADC1, ADC_IT_AWD);
		BAT_PWM_EN(0);
		B_BAT_COMP_EN=0xF0;
//	/* Enable AWD interrupt */
		ADC_ITConfig(ADC1, ADC_IT_AWD,DISABLE);
  }
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
