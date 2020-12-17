/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
#include "main_2.h"
#include "Main interface.h"
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */
	#if 0
	LL_RCC_PLL_Disable();
	LL_RCC_HSE_Disable();

	/*内部HSI*/
  LL_RCC_HSI_SetCalibTrimming(16);

  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }

  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_16, 200, LL_RCC_PLLP_DIV_2);

  LL_RCC_PLLI2S_ConfigDomain_I2S(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLI2SM_DIV_16, 192, LL_RCC_PLLI2SR_DIV_2);

  LL_RCC_PLLI2S_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLI2SM_DIV_16, 192, LL_RCC_PLLI2SQ_DIV_4);
	/*内部HSI*/
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_PLLI2S_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLLI2S_IsReady() != 1)
  {

  }
	#endif
  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
	NVIC_SystemReset();
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */
	NVIC_SystemReset();
  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {

  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */
	NVIC_SystemReset();
  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */
	NVIC_SystemReset();
  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */
	NVIC_SystemReset();
  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */
	NVIC_SystemReset();
  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */
	NVIC_SystemReset();
  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */
	NVIC_SystemReset();
  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */
	static u8		B_Res_BAT_JC=0;
	static u8 	Tim10ms=1,Tim20ms=2,Tim100ms=3,Tim250ms=4;
	static u16	Tim1s=5;/*Tim500ms=0,Tim1s=0,Tim2s=0;*/

	Tim10ms++;
	Tim20ms++;
	Tim100ms++;
	Tim250ms++;
//	Tim500ms++;
	Tim1s++;
//	Tim2s++;
	B_Charg_Jianche=1;
	B_Out_JC=1;
	if(R_LCDRESET_Tim)
		R_LCDRESET_Tim--;
	if(B_InterfaceGOTO)
	{
		BAT_Management_Charge();
		OUT_YES_Control();
	}
	Vibrate_drive();
	if(R_KEY_timi)
	{
		R_KEY_timi--;
	}
	if(R_Read_Rtim)
	{
		R_Read_Rtim--;
	}
	KEY_Filter_processing();
	if(Tim10ms>=10)
	{
		Tim10ms=0;
		/////////////////////////////
		if(Get_BL_PWM_Data>R_BL_PWM_Data)
			Get_BL_PWM_Data--;
		else	if(Get_BL_PWM_Data<R_BL_PWM_Data)
			Get_BL_PWM_Data++;

		if(Get_LED1_PWM_Data>R_KEY_LED_PWM_Data)
			Get_LED1_PWM_Data--;
		else	if(Get_LED1_PWM_Data<R_KEY_LED_PWM_Data)
			Get_LED1_PWM_Data++;

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
		if(USBovertime)
		{
			USBovertime--;
		}
		if(R_LUX_ADC_Tim)
			R_LUX_ADC_Tim--;
		if(B_Out_Yes)
		{
			if(R_Smoke_Tim10ms<R_User_Smoke_Tim_max*10)
				R_Smoke_Tim10ms++;
		}
		if(Vape_Arc_Tim<11)
				Vape_Arc_Tim++;
		///////////////////////
	}

	if(Tim20ms>=20)
	{
		Tim20ms=0;
		/////////////////////////////
		LOGO_LED_Control();
		B_KEY_JC=1;
		B_load_JC=1;
		if(Arc_angle_Time)
			Arc_angle_Time--;
		///////////////////////
	}

	if(Tim100ms>=100)
	{
		Tim100ms=0;
		/////////////////////////////
		if(R_Auto_Locked_KEY)
			R_Auto_Locked_KEY--;
		if(R_Interface_maintain_Time)
			R_Interface_maintain_Time--;
		if(R_Bright_screen_Time)
			R_Bright_screen_Time--;
		if(R_USB_error_Tim)
			R_USB_error_Tim--;
		if(R_XY_Tim_yanshi)
			R_XY_Tim_yanshi--;
		if(KEY_LED_Tim)
			KEY_LED_Tim--;
		if(B_Out_Yes)
		{
			if(R_Smoke_Tim<R_User_Smoke_Tim_max)
				R_Smoke_Tim++;
		}
		if(R_SleepTim)
		{
			R_SleepTim--;
		}
		B_Read_RTC=1;
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
  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles DMA1 stream0 global interrupt.
*/
void DMA1_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream0_IRQn 0 */

  /* USER CODE END DMA1_Stream0_IRQn 0 */

  /* USER CODE BEGIN DMA1_Stream0_IRQn 1 */

  /* USER CODE END DMA1_Stream0_IRQn 1 */
}

/**
* @brief This function handles ADC1 global interrupt.
*/
void ADC_IRQHandler(void)
{
  /* USER CODE BEGIN ADC_IRQn 0 */
	if(LL_ADC_IsEnabledIT_AWD1(ADC1))
	{
		LL_ADC_ClearFlag_AWD1(ADC1);
		BAT_PWM_EN(0);
		B_BAT_COMP_EN=0xF0;
		LL_ADC_DisableIT_AWD1(ADC1);
	}
  /* USER CODE END ADC_IRQn 0 */
  /* USER CODE BEGIN ADC_IRQn 1 */

  /* USER CODE END ADC_IRQn 1 */
}


void EXTI15_10_IRQHandler(void)
{
	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);

	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);

	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_12);

	LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_15);
}

/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
extern	Skinning_mode	R_Skinning_modeOUT;		//窗口状态
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6) != RESET)
  {
    /* USER CODE BEGIN LL_EXTI_LINE_10 */
		while(R_OUT_PWM_data)
		{
			R_OUT_PWM_data--;
			OUT_PWM_Wdata(&R_OUT_PWM_data);
			Delay_Nus(1);
		}
		Set_OUT_BOOST_PWM_Data(0);
		Set_OUT_Buck_PWM_Data(0);

		R_OUT_PWM_data=0;
		OUT_En_DCDC_OFF();
		B_Smoking_mark=0;
		R_Skinning_modeOUT=Short_circuit;
		LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_6);
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);
    /* USER CODE END LL_EXTI_LINE_10 */
  }
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */
	if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_7) != RESET)
  {
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_7);
	}
  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
* @brief This function handles USB On The Go FS global interrupt.
*/
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
