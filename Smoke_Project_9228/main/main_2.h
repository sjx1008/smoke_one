/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_2_H
#define __MAIN_2_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "arm_math.h"

#include "APP_Delay.h"
#include "WM_Disp.h"

#include "APP_Atomizer.h"
#include "APP_KEY.h"
#include "ADC_Module.h"
#include "APP_ChargingBAT.h"
#include "APP_OutputControl.h"
#include "APP_PWM_int.h"
#include "APP_Compare.h"
#include "Statistics Port number.h"

#include "APP_Sleeping.h"
#include "APP_FLASH.h"
#include "APP_Custom.h"
#include "APP_RTC.h"
#include "Vibrate.h"
#include "KEY_LED.h"
#include "Batt_JZ_interface.h"
#include "sqrt_16.h"
#include "TFT_Init.h"
#include "TFT_Drive.h"
#include "Flahs_Driver.h"
#include "GUI_image_FLASH.h"
#include "GUI_XBF_Font.h"
#include "Flahs_Data.h"
#include "Brightness_AUTo.h"
#include  "APP_USB.h"

///////////////��ʾ�̼��汾��////////////

extern	void	feed_Watchdog(void);
extern	void	Watchdog_ON(void);
extern	void	Watchdog_OFF(void);
extern	void	Watchdog_Reset(void);

extern	void SystemClock_Config(void);
//Flash	������
#define		d_Page_Flash									2048			//һҳFLASH��С

//#define		d_FLASH_LOGO_address					((uint32_t)0x08006800)		/* ��ʾ����LOGO�������� 2048*7*/
//#define		d_FLASH_transfer_address			((uint32_t)0x0800A000)		/* ��ת���� 2048*/


#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
