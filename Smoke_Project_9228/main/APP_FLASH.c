#include "APP_FLASH.h"
#include "main_2.h"
#include "stm32f4xx_hal_def.h"

//extern FLASH_ProcessTypeDef pFlash;

//typedef union
//{
//	volatile	uc8		R_Flash8[4096];
//	volatile	uc16	R_Flash16[2048];
//	volatile	uc32	R_Flash32[1024];
//}FLASH_Power_typedef;


u16		R_Flash_i;


u8 	R_Flash_WB;					//写标志
u8	B_Force_Power_down_save=0;

//const FLASH_Power_typedef		FLASH_Power_down_save		__attribute__((at(FLASH_Power_down_save_ADDR)));		//掉电保存FLASH

#define		d_FLASH_Date_maxbyte	52
#define		d_FLASH_Date_maxword	13

u8	R_0xA5=0xA5;
u8	R_0xFF=0xFF;
u8	FLASH_Date_Qdata[d_FLASH_Date_maxbyte];
u8 *const FLASH_Date[]={
	&R_0xA5,
	(u8 *)&R_Work_mode,
	(u8 *)&R_Atomizer,
	(u8 *)&R_TCR_term,
	(u8 *)&R_Temp_metric,
	(u8 *)&R_Watt_Strength,
	(u8 *)&B_LOCK_Res,
	(u8 *)&R_Dial,
	(u8 *)&R_Watch_dial,
	(u8 *)&R_Screen_Tim,
	(u8 *)((u8 *)&R_Screen_Tim+1),
	(u8 *)&R_BrightScreen_TimeMAX,
	(u8 *)((u8 *)&R_BrightScreen_TimeMAX+1),
	(u8 *)&R_Res_Initial_jiyi,
	(u8 *)((u8 *)&R_Res_Initial_jiyi+1),
	(u8 *)&R_Screen_brightness,
	(u8 *)&R_User_Vout_Set,
	(u8 *)((u8 *)&R_User_Vout_Set+1),
	(u8 *)&R_User_Watt_Set,
	(u8 *)((u8 *)&R_User_Watt_Set+1),
	(u8 *)&R_User_Temp_Set_C,
	(u8 *)((u8 *)&R_User_Temp_Set_C+1),
	(u8 *)&R_User_Temp_Set_F,
	(u8 *)((u8 *)&R_User_Temp_Set_F+1),
	(u8 *)&Load_Ss316.Gradient,
	(u8 *)((u8 *)&Load_Ss316.Gradient+1),
	(u8 *)&Load_Ni200.Gradient,
	(u8 *)((u8 *)&Load_Ni200.Gradient+1),
	(u8 *)&Load_Ti.Gradient,
	(u8 *)((u8 *)&Load_Ti.Gradient+1),
	(u8 *)&Load_M1.Gradient,
	(u8 *)((u8 *)&Load_M1.Gradient+1),
	(u8 *)&Load_M2.Gradient,
	(u8 *)((u8 *)&Load_M2.Gradient+1),
	(u8 *)&R_SMART_RES,
	(u8 *)((u8 *)&R_SMART_RES+1),
	(u8 *)&B_AUOT_MODE,
	(u8 *)&B_SMART_mode,
	(u8 *)&R_Set_Vibrate,
	(u8 *)&R_Set_KEY_LED_Brig,
	(u8 *)&Load_Ni200.WattsMAX,
	(u8 *)&Load_Ti.WattsMAX,
	(u8 *)&Load_Ss316.WattsMAX,
	(u8 *)&Load_M1.WattsMAX,
	(u8 *)&Load_M2.WattsMAX,
	(u8 *)&Load_M3.WattsMAX,
	(u8 *)&Watt_Menu_I,
	(u8 *)&Temp_Menu_I,
	(u8 *)&CC_Menu_I,
	(u8 *)&AMPM_EN,
	(u8 *)&R_0xFF,
	(u8 *)&R_0xFF,
//	(u8 *)&R_0xFF,
//	(u8 *)&R_0xFF,

//	(u8 *)&RTC_Date.Year,
//	(u8 *)&RTC_Date.Month,
//	(u8 *)&RTC_Date.Day,
//	(u8 *)&RTC_Time.Hours,
//	(u8 *)&RTC_Time.Minutes,
};

#define		d_FLASH_PUFF_maxbyte	12
#define		d_FLASH_PUFF_maxword	3
u16		R_Flash_PUFF_i;
u8	FLASH_PUFF_Qdata[d_FLASH_PUFF_maxbyte];
u8 *const FLASH_PUFF_Date[]={
	&R_0xA5,
	(u8 *)&R_Statistics_number,
	(u8 *)((u8 *)&R_Statistics_number+1),
	(u8 *)((u8 *)&R_Statistics_number+2),
	(u8 *)((u8 *)&R_Statistics_number+3),
	(u8 *)&R_Vape_Time_number,
	(u8 *)((u8 *)&R_Vape_Time_number+1),
	(u8 *)((u8 *)&R_Vape_Time_number+2),
	(u8 *)((u8 *)&R_Vape_Time_number+3),
	(u8 *)&R_0xFF,
	(u8 *)&R_0xFF,
	(u8 *)&R_0xFF,
};


#define		d_FLASH_RTC_maxbyte	8
#define		d_FLASH_RTC_maxword	2
u16		R_Flash_RTC_i;
u8	FLASH_RTC_Qdata[d_FLASH_RTC_maxbyte];
u8 *const FLASH_RTC_Date[]={
	&R_0xA5,
	(u8 *)&RTC_Date.Year,
	(u8 *)&RTC_Date.Month,
	(u8 *)&RTC_Date.Day,
	(u8 *)&RTC_Time.Hours,
	(u8 *)&RTC_Time.Minutes,
	(u8 *)&R_0xFF,
	(u8 *)&R_0xFF,
};


void Rflash(void)
{
	u16	i;

	R_Flash_i=0;
	for(i=0;i<4096;i+=d_FLASH_Date_maxbyte)
	{
		if(SPI_Flash_Read_PageData8(FLASH_SaveData_address+i)==0xA5)
		{
			R_Flash_i=i;
			break;
		}
	}

	if(SPI_Flash_Read_PageData8(FLASH_SaveData_address)!=0xA5 && R_Flash_i==0)
	{
		W25QXX_Erase_Sector(FLASH_SaveData_address);
	}
	else
	{
		SPI_Flash_Read_BuffData8(FLASH_SaveData_address+R_Flash_i,FLASH_Date_Qdata,d_FLASH_Date_maxbyte);
		SPI_Flash_Read_BuffData_OK();
		for(i=0;i<d_FLASH_Date_maxbyte;i++)
			*FLASH_Date[i]=FLASH_Date_Qdata[i];

		if(R_Work_mode>=d_NOP_mode)
			R_Work_mode=d_Watt_mode;
		if(R_Atomizer>=Atomizer_NC)
			R_Atomizer=Ni;
		if(R_TCR_term>=TCR_NC)
			R_TCR_term=M1;
		if(R_Temp_metric>=Temp_metric_NC)
			R_Temp_metric=F_metric;
		if(R_Watt_Strength>HIGH_Strength)
			R_Watt_Strength=HIGH_Strength;
		if(R_Dial>1)
			R_Dial=(Dial_typ)0;
		if(R_Watch_dial>1)
			R_Watch_dial=0;
		if(R_Screen_Tim>d_Screen_Tim_Max || R_Screen_Tim<d_Screen_Tim_Min)
			R_Screen_Tim=900;
		R_BrightScreen_TimeMAX/=10;
		R_BrightScreen_TimeMAX*=10;
		if(R_BrightScreen_TimeMAX>d_BrightScreen_TimeMAX || R_BrightScreen_TimeMAX<d_BrightScreen_TimeMIN)
			R_BrightScreen_TimeMAX=150;
		if(R_Res_Initial_jiyi>d_Res_max || R_Res_Initial_jiyi<d_Res_min)
		{
			R_Res_Initial_jiyi=d_Res_max;
			B_LOCK_Res=0;
		}
		if(R_Screen_brightness>d_Screen_brightness_MAX || R_Screen_brightness==0)
			R_Screen_brightness=d_Screen_brightness_MAX;
		if(R_User_Temp_Set_C>d_User_TempC_max || R_User_Temp_Set_C<d_User_TempC_min)
			R_User_Temp_Set_C=d_User_TempC_max;
		R_User_Temp_Set_C=R_User_Temp_Set_C/5*5;
		if(R_User_Temp_Set_F>d_User_TempF_max || R_User_Temp_Set_F<d_User_TempF_min)
			R_User_Temp_Set_F=d_User_TempF_max;
		R_User_Temp_Set_F=R_User_Temp_Set_F/10*10;
		if(R_User_Watt_Set>d_User_Watt_max || R_User_Watt_Set<d_User_Watt_min)
			R_User_Watt_Set=d_User_Watt_min;
		if(R_User_Vout_Set>d_User_Vout_max || R_User_Vout_Set<d_User_Vout_min)
			R_User_Vout_Set=360;
		if(Load_Ss316.Gradient>250 || Load_Ss316.Gradient<50)
			Load_Ss316.Gradient=105;
		if(Load_Ni200.Gradient>800 || Load_Ni200.Gradient<400)
			Load_Ni200.Gradient=550;
		if(Load_Ti.Gradient>550 || Load_Ti.Gradient<150)
			Load_Ti.Gradient=320;
		if(Load_M1.Gradient>1000 || Load_M1.Gradient<20)
			Load_M1.Gradient=20;
		if(Load_M2.Gradient>1000 || Load_M2.Gradient<20)
			Load_M2.Gradient=20;
		if(R_SMART_RES>=9999)
			R_SMART_RES=0;
		if(B_AUOT_MODE>1)
			B_AUOT_MODE=0;
		if(Load_Ni200.WattsMAX>d_User_Watt_max/10 || Load_Ni200.WattsMAX<d_User_Watt_min/10)
			Load_Ni200.WattsMAX  =75;
		if(Load_Ti.WattsMAX>d_User_Watt_max/10 || Load_Ti.WattsMAX<d_User_Watt_min/10)
			Load_Ti.WattsMAX  =75;
		if(Load_Ss316.WattsMAX>d_User_Watt_max/10 || Load_Ss316.WattsMAX<d_User_Watt_min/10)
			Load_Ss316.WattsMAX  =75;
		if(Load_M1.WattsMAX>d_User_Watt_max/10 || Load_M1.WattsMAX<d_User_Watt_min/10)
			Load_M1.WattsMAX  =75;
		if(Load_M2.WattsMAX>d_User_Watt_max/10 || Load_M2.WattsMAX<d_User_Watt_min/10)
			Load_M2.WattsMAX  =75;

		if(Watt_Menu_I>2)
			Watt_Menu_I=1;
		if(Temp_Menu_I>4)
			Watt_Menu_I=2;
		if(CC_Menu_I>4)
			Watt_Menu_I=0;

		if(R_Set_Vibrate>10)
			R_Set_Vibrate=10;
		if(R_Set_KEY_LED_Brig>8)
			R_Set_KEY_LED_Brig=8;
	}
	for(i=0;i<d_FLASH_Date_maxbyte;i++)
	{
		FLASH_Date_Qdata[i]=*FLASH_Date[i];
	}

//////////////////////////////////
	R_Flash_PUFF_i=0;
	for(i=0;i<4096;i+=d_FLASH_PUFF_maxbyte)
	{
		if(SPI_Flash_Read_PageData8(FLASH_PUFF_address+i)==0xA5)
		{
			R_Flash_PUFF_i=i;
			break;
		}
	}

	if(SPI_Flash_Read_PageData8(FLASH_PUFF_address)!=0xA5 && R_Flash_PUFF_i==0)
	{
		W25QXX_Erase_Sector(FLASH_PUFF_address);
	}
	else
	{
		SPI_Flash_Read_BuffData8(FLASH_PUFF_address+R_Flash_PUFF_i,FLASH_PUFF_Qdata,d_FLASH_PUFF_maxbyte);
		SPI_Flash_Read_BuffData_OK();
		for(i=0;i<d_FLASH_PUFF_maxbyte;i++)
			*FLASH_PUFF_Date[i]=FLASH_PUFF_Qdata[i];



		if(R_Statistics_number>d_Statistics_number_MAX)
			R_Statistics_number=0;
		if(R_Vape_Time_number>5999994)
			R_Vape_Time_number=0;
	}
	for(i=0;i<d_FLASH_PUFF_maxbyte;i++)
	{
		FLASH_PUFF_Qdata[i]=*FLASH_PUFF_Date[i];
	}
	/////////////////////////////////////////////////////////////////////////
	R_Flash_RTC_i=0;
	for(i=0;i<4096;i+=d_FLASH_RTC_maxbyte)
	{
		if(SPI_Flash_Read_PageData8(FLASH_RTC_address+i)==0xA5)
		{
			R_Flash_RTC_i=i;
			break;
		}
	}

	if(SPI_Flash_Read_PageData8(FLASH_RTC_address)!=0xA5 && R_Flash_RTC_i==0)
	{
		W25QXX_Erase_Sector(FLASH_RTC_address);
	}
	else
	{
		SPI_Flash_Read_BuffData8(FLASH_RTC_address+R_Flash_RTC_i,FLASH_RTC_Qdata,d_FLASH_RTC_maxbyte);
		SPI_Flash_Read_BuffData_OK();
		for(i=0;i<d_FLASH_RTC_maxbyte;i++)
			*FLASH_RTC_Date[i]=FLASH_RTC_Qdata[i];
	}
	Read_Custom_flash();
}


void Data_retention(void)
{
	u8	i;
	if(!B_Out_Yes && !key_value)
	{
		if(!R_Flash_WB)
		{
			R_Flash_WB=50;
			R_0xA5=0xA5;
			R_0xFF=0xFF;
			for(i=0;i<d_FLASH_Date_maxbyte;i++)
			{
				if(*FLASH_Date[i]!=FLASH_Date_Qdata[i])
				{
					if(R_USB_state==S_USB_NOP)
						R_USB_state=S_USB_FLASH;
					else
						return;
					SPI_Flash_WritePageData8(FLASH_SaveData_address+R_Flash_i,0);

					R_Flash_i+=d_FLASH_Date_maxbyte;
					if(R_Flash_i+d_FLASH_Date_maxbyte>=4096)
					{
						R_Flash_i=0;
						W25QXX_Erase_Sector(FLASH_SaveData_address);
					}

					for(i=0;i<d_FLASH_Date_maxbyte;i++)
					{
						FLASH_Date_Qdata[i]=*FLASH_Date[i];
					}
					SPI_Flash_Write_BuffData8(FLASH_SaveData_address+R_Flash_i,FLASH_Date_Qdata,d_FLASH_Date_maxbyte);
					SPI_Flash_Write_BuffData_OK();
					R_USB_state=S_USB_NOP;
					break;
				}
			}
			///////////////////////////
			for(i=0;i<d_FLASH_PUFF_maxbyte;i++)
			{
				if(*FLASH_PUFF_Date[i]!=FLASH_PUFF_Qdata[i])
				{
					if(R_USB_state==S_USB_NOP)
						R_USB_state=S_USB_FLASH;
					else
						return;
					SPI_Flash_WritePageData8(FLASH_PUFF_address+R_Flash_PUFF_i,0);

					R_Flash_PUFF_i+=d_FLASH_PUFF_maxbyte;
					if(R_Flash_PUFF_i+d_FLASH_PUFF_maxbyte>=4096)
					{
						R_Flash_PUFF_i=0;
						W25QXX_Erase_Sector(FLASH_PUFF_address);
					}
					for(i=0;i<d_FLASH_PUFF_maxbyte;i++)
					{
						FLASH_PUFF_Qdata[i]=*FLASH_PUFF_Date[i];
					}
					SPI_Flash_Write_BuffData8(FLASH_PUFF_address+R_Flash_PUFF_i,FLASH_PUFF_Qdata,d_FLASH_PUFF_maxbyte);
					SPI_Flash_Write_BuffData_OK();
					R_USB_state=S_USB_NOP;
					break;
				}
			}
			////////////////////////////////////////////////////////////////////////
			for(i=0;i<d_FLASH_RTC_maxbyte;i++)
			{
				if(*FLASH_RTC_Date[i]!=FLASH_RTC_Qdata[i])
				{
					if(R_USB_state==S_USB_NOP)
						R_USB_state=S_USB_FLASH;
					else
						return;
					SPI_Flash_WritePageData8(FLASH_RTC_address+R_Flash_RTC_i,0);

					R_Flash_RTC_i+=d_FLASH_RTC_maxbyte;
					if(R_Flash_RTC_i+d_FLASH_RTC_maxbyte>=4096)
					{
						R_Flash_RTC_i=0;
						W25QXX_Erase_Sector(FLASH_RTC_address);
					}

					for(i=0;i<d_FLASH_RTC_maxbyte;i++)
					{
						FLASH_RTC_Qdata[i]=*FLASH_RTC_Date[i];
					}
					SPI_Flash_Write_BuffData8(FLASH_RTC_address+R_Flash_RTC_i,FLASH_RTC_Qdata,d_FLASH_RTC_maxbyte);
					SPI_Flash_Write_BuffData_OK();
					R_USB_state=S_USB_NOP;
					break;
				}
			}
			Custom_WriteFLASH();
		}
	}
	else
	{
		R_Flash_WB=50;
	}
}

void	Default_Data(void)
{
	u8	i;
	R_Work_mode=d_Watt_mode;
	R_Atomizer=Ss;
	R_TCR_term=M1;
	R_Temp_metric=F_metric;
	R_Watt_Strength=NOR_Strength;
	B_LOCK_Res=0;
	R_Dial=(Dial_typ)0;
	R_Watch_dial=0;
	R_Screen_Tim=180;
	R_BrightScreen_TimeMAX=150;
	R_Screen_brightness=d_Screen_brightness_MAX;
	R_User_Vout_Set=360;
	R_User_Watt_Set=50;
	R_User_Temp_Set_C=205;
	R_User_Temp_Set_F=400;
	Load_M1.Gradient=100;
	Load_M2.Gradient=100;
	Load_Ni200.Gradient=550;
	Load_Ti.Gradient=320;
	Load_Ss316.Gradient=105;

	Load_Ni200.WattsMAX  =75;
  Load_Ti.WattsMAX     =75;
  Load_Ss316.WattsMAX  =115;
  Load_M1.WattsMAX     =75;
  Load_M2.WattsMAX     =75;
  Load_M3.WattsMAX     =75;
//	R_User_Temp_Watt_Max=75;
	B_AUOT_MODE=1;
	R_SMART_RES=0;
	B_SMART_mode=0;
//	R_Date_order=0;
	R_Set_Vibrate=10;
	R_Set_KEY_LED_Brig=8;
	R_Statistics_number=0;
	R_Vape_Time_number=0;
	for(i=0;i<10;i++)
	{
		R_Custom_BUFF.Custom_array.CustomCCW_Data[i]=120-i*10;
		R_Custom_BUFF.Custom_array.CustomCCV_Data[i]=420-i*5;
		R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data[i]=200+i*10;
		R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data[i]=200+i*10;
		R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data[i]=200+i*10;
		R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data[i]=400+i*20;
		R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data[i]=400+i*20;
		R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data[i]=400+i*20;
	}
	AMPM_EN=0;
	B_Custom_Hold=1;
	R_Smoke_Tim=0;
	R_Smoke_Tim10ms=0;

	Watt_Menu_I=1;
	Temp_Menu_I=2;
	CC_Menu_I=0;
}



