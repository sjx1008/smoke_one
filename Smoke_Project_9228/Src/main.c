
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "crc.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"
#include "main_2.h"
#include "WM_Disp.h"
/* USER CODE BEGIN Includes */
#include "GUI.h"
#include "GUI_Private.h"
#include "WM.h"
//#include "malloc.h"
#include "Program_Upgrade_Status.h"

/* USER CODE END Includes */
//#define	Flash_IC_Update


/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

#define	Watchdog_Max	20
u8	R_Watchdog_Tim=0;
u8	B_Watchdog_EN=0;
void	feed_Watchdog(void)
{
	R_Watchdog_Tim=0;
}

void	Watchdog_Reset(void)
{
	if(B_Watchdog_EN)
	{
		R_Watchdog_Tim++;
		if(R_Watchdog_Tim>Watchdog_Max)
			NVIC_SystemReset();
	}
}
void	Watchdog_ON(void)
{
	feed_Watchdog();
	B_Watchdog_EN=1;
}
void	Watchdog_OFF(void)
{
	B_Watchdog_EN=0;
}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void	VCC33_judge(void)
{
	u8	B=0;
	s16	VCC;
	u8	i=0;
	R_SleepTim=20;
	while(1)
	{
		if(B_Charg_Jianche)
		{
			B_Charg_Jianche=0;
			VCC=Read_VCC_Data();
			if(VCC>315 && VCC<345)
			{
				if(B)
					NVIC_SystemReset();
				else
				{
					R_SleepTim=20;
					i++;
					if(i>50)
						return;
				}
			}
			else	if(VCC<314 || VCC>346)
			{
				B=1;
				i=0;
			}
			if(!R_SleepTim)
			{
				Sleeping_Peripheral();
				R_SleepTim=20;
				MX_GPIO_Init(0);
				MX_ADC1_Init();
			}
		}
	}
}

/* USER CODE END 0 */

void NVIC_SetVectorTable(void)
{
//	uint8_t i;
//	for(i = 0; i < 101; i++)
//	{
//		*((uint32_t*)(0x20000000 + (i << 2))) = *(__IO uint32_t*)(APP_DEFAULT_ADD + (i<<2));
//	}
	memcpy((void*)0x20000000, (void*)APP_DEFAULT_ADD, 101);
	/* Enable the SYSCFG peripheral clock*/
//RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	__HAL_RCC_SYSCFG_RELEASE_RESET();
	__HAL_RCC_SYSCFG_CLK_ENABLE();
  /* Remap SRAM at 0x00000000 */
	LL_SYSCFG_SetRemapMemory(LL_SYSCFG_REMAP_SRAM);
}
#ifdef Flash_IC_Update
#include "usbd_customhid.h"
int main(void)
{
	NVIC_SetVectorTable();
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  TFT_LCD_RESET();
  MX_ADC1_Init();
  MX_SPI3_Init();
	MX_OUT_PWM_Init();
  MX_CHG_PWM_Init();
  MX_BL_PWM_Init();
  USB_ENABLE_transmission(); //??Batt_JZ_initerfaceo?????
  MX_CRC_Init();

  /* USER CODE BEGIN 2 */
	Flash_Init();
	TFT_ST7789S_Init();
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	Disp_windows=One_Power_interface;
	Disp_windows_Set=Disp_windows;
	while (1)
	{
		u8	Cmd;
		if(B_Accept_Data_OK)
		{
			Cmd=Report_buf[0]&0xf0;
			switch(Cmd)
			{
				case	Query_parameters:
				{
					USB_Query_parameters();
				}break;
				case	SEND_LOGO_BEGIN:		{
					Handle_SEND_LOGO_BEGIN();
					encryption_data();
				}break;
				case	SEND_LOGO_DATA:	{
					Handle_SEND_LOGO_DATA();
					FLASH_Data_checksum_usbdata();
				}break;
				case	SEND_LOGO_END:	{
					Handle_SEND_LOGO_END();
					FLASH_Data_checksum_usbdata();
				}break;
				default:
				{
					Send_Buffer[0]=Report_buf[0];
					Send_Buffer[1]=Report_buf[1];
					Send_Buffer[2]=1;
					Send_Buffer[3]=0x5F;
					encryption_data();
				}
			}
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,Send_Buffer,USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
			B_Accept_Data_OK=0;
		}
	}
	/* USER CODE END 3 */

}
#else
int main(void)
{
	NVIC_SetVectorTable();
  /* USER CODE BEGIN 1 */
#if 1
	#define FLASH_WRP_SECTORS   (OB_WRP_SECTOR_6 | OB_WRP_SECTOR_7) /* sectors 6 and 7 */
	FLASH_OBProgramInitTypeDef	pOBInit;
	HAL_FLASHEx_OBGetConfig(&pOBInit);
	if(OB_RDP_LEVEL_1 != pOBInit.RDPLevel)
	{
		HAL_FLASH_OB_Unlock();
		HAL_FLASH_Unlock();
		pOBInit.RDPLevel=OB_RDP_LEVEL_1;
		pOBInit.OptionType=OPTIONBYTE_RDP;
		HAL_FLASHEx_OBProgram(&pOBInit);
		/* Start the Option Bytes programming process */
		if (HAL_FLASH_OB_Launch() != HAL_OK)
		{
			/* User can add here some code to deal with this error */
			while (1)
			{
			}
		}
		HAL_FLASH_Lock();
		HAL_FLASH_OB_Lock();
	}
#endif /* Flash read protection */
  /* USER CODE END 1 */
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */

  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init(0);
	//TFT_LCD_RESET();
  MX_ADC1_Init();
	VCC33_judge();
  MX_SPI3_Init();
  MX_OUT_PWM_Init();
  MX_CHG_PWM_Init();
  MX_BL_PWM_Init();
	MX_LED_PWM_Init();
	MX_MOTOR_PWM_Init();
//  USB_ENABLE_transmission(); //放在Batt_JZ_initerface里面初始化了
  MX_CRC_Init();
  MX_RTC_Init();

  /* USER CODE BEGIN 2 */
	Flash_Init();
	Program_Upgrade_Status();
	Rflash();
	RTC_int();
	//TFT_ST7789S_Init();
	GUI_Init();
	initCharacterLib();
	WM_SelectWindow(WM_HBKWIN);
	Bring_AUTO_Init();
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	Disp_windows=One_Power_interface;
	Disp_windows_Set=Disp_windows;
	Batt_JZ_interface();
	Watchdog_ON();
	R_SleepTim=300;
	while (1)
	{
	/* USER CODE BEGIN 3 */
		feed_Watchdog();
		Bring_AUTO_Testing();
		Read_RTC_BIN();
		BAT_Management();
		KEY_ALL_Task();
		Read_load();
		OUTControl();
		Data_retention();
		USB_state_program();
		Sleeping_Module();
	}
	/* USER CODE END 3 */

}
#endif
/** System Clock Configuration
*/
void SystemClock_Config(void)
{
	__HAL_RCC_PWR_CLK_ENABLE();
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

   if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_2)
  {
  Error_Handler();
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	LL_FLASH_EnablePrefetch();
	LL_FLASH_EnableInstCache();
	LL_FLASH_EnableDataCache();
  LL_RCC_HSI_SetCalibTrimming(16);

  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 168, LL_RCC_PLLP_DIV_4);

  LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_8, 168, LL_RCC_PLLQ_DIV_7);

  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);

  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_Init1msTick(84000000);

  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);

  LL_SetSystemCoreClock(84000000);

  LL_RCC_SetTIMPrescaler(LL_RCC_TIM_PRESCALER_TWICE);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
