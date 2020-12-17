#include "WM_Disp.h"

u8	GOTO_Screensaver_interface(u8	B)
{
//	if(R_Dial!=OFF_Dial)
//	{
//		if(R_key_super_keep==KEY_MODE_SUB_ADD)
//		{
//			if(B)
//				Windows_Interrupt_Push(Screensaver_interface);
//			else
//				Windows_Switch(Screensaver_interface);
//			return 1;
//		}
//	}
	return 0;
}

u8	ADDSUB_LOCK_GOTO(u8 B)
{
		static	u8	tim=0;
	if(tim)
		tim--;
	if(R_key_anxiaOpen==KEY_M || R_key_anxia==KEY_M)
		if(tim)
				tim=10;
	if(R_key_3C==KEY_M && !tim)
	{
		B_ADDSUB_LOCK=!B_ADDSUB_LOCK;
		return 1;
	}
	if(B)
	{
		if(B_ADDSUB_LOCK)
		{
			if(!B_Out_Yes)
			{
				if(R_key_anxia && !(R_key_anxia&KEY_M))
				{
					Warning_Windows=FIRE_TO_UNLOCK_windows;
					Windows_Interrupt_Push(Warning_interface);
					return 1;
				}
			}
		}
		else
		{
			if(B_Out_Yes)
			{
				if(!B_ADDSUB_LOCK)
				{
					B_ADDSUB_LOCK=1;
					tim=20;
					return 1;
				}
			}
		}
	}
	return 0;
}


u8 B_disp_prompt=0;
u8	B_Mode_selection_EN=0;
u8	Main_menu_GOTO(void)
{
	if(!R_Bright_screen_Time)
		B_Mode_selection_EN=1;
	if(!B_ADDSUB_LOCK)
	{
		if(R_key_3C_Mode==KEY_MODE || R_key_super_keep_Mode==KEY_MODE)
		{
			Windows_Switch(Main_menu_interface);
			return 1;
		}
		else
		{
			if(!B_Out_Yes)
			{
				if(!B_Mode_selection_EN)
				{
					if((R_key_XC_Mode == KEY_MODE && R_key_XC_Data_Mode!=3) || R_key_anzhuOpen_Mode==KEY_MODE)
					{
						if(Disp_windows!=Warning_interface)
						{
							Warning_Windows=MODE_TO_SET_windows;
							Windows_Interrupt_Push(Warning_interface);
							return 1;
						}
					}
				}
				else
				{
					if(R_key_anxia_Mode==KEY_MODE)
						B_Mode_selection_EN=0;
				}
			}
		}
	}
	return 0;
}
//void	Return_interface_GOTO(void (*R)(void))
//{
//	if(R_key_anxia==KEY_ADD_SUB)
//	{
//		Windows_Switch(R);
//	}
//	else if(R_key_super_keep==KEY_M)
//	{
//		Windows_Switch(Main_interface);
//		B_Smoking_mark_Q=1;
//	}
//}

//
u8	Atomizer_inquiry_GOTO(u8 B)
{
	if(B_Atomizer_inquiry)
	{
		if(R_Work_mode==d_Temp_mode || R_Work_mode==d_TCR_mode || R_Work_mode==d_CustomTemp_mode)
		{
			if(B_LOCK_Res)
			{
				B_Atomizer_inquiry=0;
			}
			else	if(!B_LOCK_Res)
			{
				Windows_Switch(Atomizer_inquiry_interface);
				if(B)
					Disp_windows_QQ=Disp_windows;
				B_GOTO_Atomizer_inquiry=1;
				return 1;
			}
		}
		else
		{
			if(R_Work_mode==d_Watt_mode)
			{
				if(B_SMART_mode)
					Auto_match_Watt_program();
			}
			B_Atomizer_inquiry=0;
		}
	}
	else
	{
		B_GOTO_Atomizer_inquiry=0;
	}
	return 0;
}
//
void	System_off_GOTO(void)
{
	if(R_key_5C==KEY_M)
	{
		Windows_Switch(System_off_interface);
	}
}
//
//void	Screen_smoking_GOTO(void)
//{
//	if(R_key_3C == KEY_M && !B_BAT_Charge)
//	{
//		Windows_Switch(Screen_smoking_interface);
//	}
//}
//
u8	Batt_error_GOTO(void)
{
	if(B_BAT_error)
	{
		Windows_Switch(Batt_error_interface);
		return 1;
	}
	return 0;
}
//
u8	B_Smoking_KEY_anxia=0;
static	u8	B11=0;
void	Smoking_KEY_anxia_JC(void)
{
//		if(B_Smoking_mark==1 && R_key_keep==KEY_M)
		B11=1;
	if(B11)
		B_Smoking_KEY_anxia=Key_LB_value&KEY_M;
	else
		B_Smoking_KEY_anxia=!(Key_LB_value ^ KEY_M);
}
void	Key_smoke(void)
{
	static	u8	tim=0,tim2=0,tim3=0;
	if((B_System_off==d_System_Normal)&& \
		(Disp_windows==Main_interface || (Disp_windows_QQ==Main_interface && \
	((Disp_windows==Battery_charging_interface && B_OLED_BL) || Disp_windows==Screensaver_interface || (Disp_windows==Warning_interface && (Warning_Windows==FIRE_TO_UNLOCK_windows || Warning_Windows==MODE_TO_SET_windows))))))
	{
		if(B_Smoking_KEY_anxia)
		{
			if(!B_Smoking_mark_Q && !tim)
			{
				B_Smoking_mark=1;
				OUTControl_Init();
			}
			if(tim3)
			{
				tim3--;
				if(!B_Sleep_YES)//等于0则一定会初始化
					tim=15;
			}
			else
			{
				tim=0;
			}
			if(tim2)
			{
				tim2--;
			}
			else
			{
				//if(Disp_windows==Main_interface)
				{
					switch((u8)R_Skinning_mode2)
					{
						case	Short_circuit:
						case	Open_circuit:
						case	Low_Resistance:
						case	High_Resistance:
						case	Low_Battery:
						case	PCB_Overheated:
						R_Skinning_mode=R_Skinning_mode2;
						break;
					}
					if(R_Skinning_mode2!=Skinning_mode_null)
						tim=0;
					R_Skinning_mode2=Skinning_mode_null;
				}
			}
		}
		else
		{
			R_Skinning_mode2=Skinning_mode_null;
			if(tim)
				tim--;
			tim2=10;
			tim3=15;
			if(!(Key_LB_value&KEY_M))
				B_Smoking_mark_Q=0;
			B_Smoking_mark=0;
			B11=0;
		}
	}
	else
	{
		B_Smoking_mark_Q=1;
		B_Smoking_mark=0;
		R_Skinning_mode2=Skinning_mode_null;
	}
}
//
void	Fanhui_Main_interface(void)
{
	if(!Atomizer_inquiry_GOTO(0))
	{
		if(Disp_windows_QQ==Disp_windows)
			Windows_Switch(Main_interface);
		else
			Windows_Switch(Disp_windows_QQ);
		if(Disp_windows_Set==Main_interface)
		{
//			Key_smoke();
			if(R_key_anxia==KEY_M || !key_value)
				B_SET_Key_release=1;
		}
	}
}
//
u8	Screen_GOTO_charging(void)
{
	if(!R_Bright_screen_Time)
	{
		if(B_BAT_Charge)
		{
			Windows_Interrupt_Push(Battery_charging_interface);
			return	1;
		}
		else	if(B_USB_Low)
		{
			Windows_Interrupt_Push(USB_Warning_interface);
			return	1;
		}
		else	if(R_Dial!=OFF_Dial)
		{
			Windows_Interrupt_Push(Screensaver_interface);
			return	1;
		}
	}
	return	0;
}
//

static	u8	Tim1=0;
static	u8	Tim2=0;
u8  kuaijie_banben_bz = 0;
u8	Firmware_Tim_GOTO(void)
{
//	static	u8	t=0;
if(!B_ADDSUB_LOCK)
{
	if(key_value!=KEY_M_MODE && key_value)
	{
		if(Tim1<30)
			Tim1++;
		Tim2=0;
	}
	else if(!key_value)
	{
		Tim1=0;
		Tim2=0;
	}
	else
	{
		if(Tim1<30)
		{
			Tim2++;
			if(Tim2>70)
			{
				Tim2=0;
				Tim1=30;
				kuaijie_banben_bz = 0;
				Windows_Switch(Firmware_Tim_interface);
			}
		}
	}


//		t++;
//		if(t>100)
//		{
//			t=0;
//			Windows_Switch(Firmware_Tim_interface);
//		return 1;
//		}
//	}
}
	return 0;
//	else
//	{
//		t=0;
//	}
}


u8  kuaijie_fuwei_bz = 0;
u8  fuwei_Tim_GOTO(void)
{
  if(!B_ADDSUB_LOCK)
  {
  	if(key_value==KEY_MODE_SUB_ADD && key_value)
  	{
      kuaijie_fuwei_bz = 0;
  		Windows_Switch(Default_Set_interface);
  	}
  }
  return 0;
}

