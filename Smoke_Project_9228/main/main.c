
#include "main.h"

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

void system_int(void)
{
	#if 1
    if(SET != FLASH_OB_GetRDP())
    {
        FLASH_Unlock();
        FLASH_OB_Unlock();
        FLASH_OB_RDPConfig(OB_RDP_Level_1);
        FLASH_OB_Launch();
        FLASH_OB_Lock();
        FLASH_Lock();
    }
#endif /* Flash read protection */
	SystemInit();								//时钟初始化
	SysTick_Configuration();		//滴答初始化
	TP_I2C_GPIOInit();
	LED_SPI_GPIO_int();					//OLED端口初始化
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);//开启CRC时钟
	TIM_Clk_int();
	KEY_USB_GPIO_int();
	OutputPWM_int();
	ADC_DMA_int();
	OutputControlGPIO_int();
	ChargingBATGPIO_int();
	BAT_PWM_int();
	COMP_Config();
	Rflash();
	Reset_TP();
	RESET_OLED();
	Delay_Nms(300);
	RTC_int();
	Init_IC();
	TP_Init();
	Batt_JZ_interface();
	Disp_windows=One_Power_interface;
	Disp_windows_Set=One_Power_interface;
	B_BAT_error=1;							//初始状态默认电池异常
	R_SleepTim=20;								//休眠时间寄存器赋值
}

void NVIC_SetVectorTable(void)
{
	uint8_t i;
	for(i = 0; i < 48; i++)
	{
		*((uint32_t*)(0x20000000 + (i << 2))) = *(__IO uint32_t*)(APP_DEFAULT_ADD + (i<<2));
	}
	/* Enable the SYSCFG peripheral clock*/
//RCC_APB2PeriphResetCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  /* Remap SRAM at 0x00000000 */
  SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);
}

int main(void)
{
	NVIC_SetVectorTable();
	system_int();
	Watchdog_ON();
	while(1)
	{
		feed_Watchdog();
		Read_RTC_BIN();
		BAT_Management();
		KEY_ALL_Task();
		Read_load();			//电阻检测
		OUTControl();			//输出控制
		Data_retention();
		USB_state_program();
		USB_PWER_program();
		Sleeping_Module();
	}
}


