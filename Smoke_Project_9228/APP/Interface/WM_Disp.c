#include "main_2.h"
#include "WM_Disp.h"


void (*Disp_windows)(void)=One_Power_interface;				//当前窗口函数指针
void (*Disp_windows_Q)(void);			//上一次窗口函数指针
void (*Disp_windows_Set)(void)=One_Power_interface;		//设置窗口函数指针
void (*Disp_windows_QQ)(void);

u8	B_Skinning_init=1;
Skinning_mode	R_Skinning_mode;		//窗口状态
Skinning_mode	R_Skinning_mode2;		//窗口状态
u16	R_Interface_maintain_Time;		//界面维持时间	单位0.1S
u16	R_Bright_screen_Time;					//亮屏时间
u16	R_Bright_screen_TimeMAX;			//亮屏时间	单位0.1s

u16	R_BrightScreen_TimeMAX=150;			//平时界面亮屏时间

u8	B_Display_refresh=0;					//刷新标志
u8	B_windows_GOTO=0;			//界面第一次跳转标志

u8	B_System_off;

//切换界面
void	Windows_Switch(void (*R)(void))
{
	Disp_windows_Set=R;
}

void	Windows_Interrupt_Push(void (*R)(void))
{
	Disp_windows_QQ=Disp_windows;
	Disp_windows_Set=R;
}

//
u8	Key_Light_screen(void)
{
	if(R_Bright_screen_Time)
	{
		if(!B_OLED_BL)
		{
			BL_PanelTurnOnDisplay();
			R_key_anxia=0;		//按下
			R_key_Open=0;			//松开
			R_key_keep=0;			//长按按下
			R_key_super_keep=0;
			R_key_1C=0;				//按键1次
			R_key_3C=0;				//按键3次
			R_key_5C=0;				//按键5次
			R_key_XC=0;
			R_key_anzhu=0;		//长按按住
			R_key_anxiaOpen=0;	//短按松开
			R_key_anzhuOpen=0;	//长按松开
			R_key_super_keep_Mode=0;
			R_key_3C_Mode=0;
			R_key_anzhuOpen_Mode=0;
			R_key_XC_Data_Mode=0;
			R_key_XC_Mode=0;
			R_key_anxia_Mode=0;
			R_key_anxiaOpen_Mode=0;
			B_Key_release=1;
			return	1;
		}
	}
	return 0;
}

void	Interface_display(void)
{
	static	u16	tim;
	if((key_value) && B_OLED_BL && R_Screen_brightness==R_Screen_brightness_NOW)
	{
		if(tim<500)
		{
			tim++;
			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		}
	}
	else
	{
		tim=0;
	}
	if(R_key_anxia || R_key_Open)
	{
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		if(R_Auto_Locked_KEY)
			R_Auto_Locked_KEY=d_Auto_Locked_KEY_Tim;
	}
	if(!R_Bright_screen_Time)
	{
		if(B_OLED_BL)
		{
			BL_PanelTurnOffDisplay();
		}
	}
	else	if(B_OLED_BL)
	{
		if((s16)(R_Bright_screen_TimeMAX-R_Bright_screen_Time)>1200)
		{
			if(R_Screen_brightness_NOW!=0)
			{
				TFT_BL_Brightness(0);
			}
		}
		else
		{
			if(R_Screen_brightness!=R_Screen_brightness_NOW)
			{
				TFT_BL_Brightness(R_Screen_brightness);
				R_key_anxia &= KEY_M;
			}
		}
	}
	BL_OffDisplay_excessive();
	B_windows_GOTO=0;
	if(Disp_windows_Set!=Disp_windows)
	{
		Disp_windows_Q=Disp_windows;
		Disp_windows=Disp_windows_Set;
		B_Skinning_init=1;
		B_windows_GOTO=1;
	}
	(*Disp_windows)();
	R_key_anxia=0;		//按下
	R_key_Open=0;			//松开
	R_key_keep=0;			//长按按下
	R_key_super_keep=0;
	R_key_1C=0;				//按键1次
	R_key_3C=0;				//按键3次
	R_key_5C=0;				//按键5次
	R_key_XC=0;
	R_key_anzhu=0;		//长按按住
	R_key_anxiaOpen=0;	//短按松开
	R_key_anzhuOpen=0;	//长按松开
	R_key_super_keep_Mode=0;
	R_key_3C_Mode=0;
	R_key_anzhuOpen_Mode=0;
	R_key_XC_Data_Mode=0;
	R_key_XC_Mode=0;
	R_key_anxia_Mode=0;
	R_key_anxiaOpen_Mode=0;
	LED_drive();
}

///////////////////////////////////
Language		R_Language=English;
Work_mode		R_Work_mode=d_Watt_mode;
Temp_metric		R_Temp_metric=F_metric;
Atomizer		R_Atomizer=Ni;
TCR_term		R_TCR_term=M1;
Custom_typ		R_Custom=C1;

