#include "WM_Disp.h"

uc8 DataStr[]=__DATE__;
uc8 TimeStr[]=__TIME__;

//static	const	GUI_RECT	Button_EXIT={71,276,168,305};

void	Firmware_Tim_Disp(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("VERSION",60);
	GUI_SetFont(&GUI_FontArial60);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringHCenterAt("LUXE",120,77);
	draw_Bmp_ex(d_OMNI_LOGO,54,146);
	GUI_SetFont(&GUI_FontArial47);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringAt("4.2",132,143);
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(0xA9A9A9);
	GUI_DispStringHCenterAt(d_PCB_Software,120,215);
	GUI_DispStringHCenterAt(d_PCB_SoftwareTime,120,238);
	PanelTurnOnDisplay();
}
void	Firmware_Tim_windows(void)
{
	Firmware_Tim_Disp();
//	Print_Button_Disp("EXIT",(GUI_RECT*)&Button_EXIT,Button_COLOR_Release,0xFFFFFF);
}

//void	Firmware_Tim_interface(void)
//{
//	Key_Light_screen();
//	switch((u8)R_Skinning_mode)
//	{
//		case	Skinning_init:{//初始化
//			Firmware_Tim_windows();
//			B_Key_release=1;
//			B_Set_OK=0;
//			R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
//			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
//		};break;
//		case	USB_access:{//usb插入
//			Windows_Interrupt_Push(Battery_charging_interface);
//		};break;
//		case	USB_anomaly:{//USB异常
//			Windows_Interrupt_Push(USB_Warning_interface);
//		};break;
//		default:{
//			if(!B_Set_OK)
//			{
//				if(R_key_anxia_Mode==KEY_MODE)
//				{
//					B_Set_OK=1;
//					R_Interface_maintain_Time=d_OK_stop_Tim;
//					Print_Button_Disp("EXIT",(GUI_RECT*)&Button_EXIT,Menu_Cursor_Colour[R_UI_Theme],0xFFFFFF);
//				}
//				if(R_key_anxia==KEY_M)
//				{
//					Windows_Switch(Main_interface);
//				}
//				Atomizer_inquiry_GOTO(1);
//				GOTO_Screensaver_interface(1);
//				Screen_GOTO_charging();
//			}
//			else
//			{
//				if(!R_Interface_maintain_Time)
//					Windows_Switch(System_Set_Menu_interface);
//			}
//			Batt_error_GOTO();
//		};
//	}
//	R_Skinning_mode=Skinning_mode_null;
//}



void	Firmware_Tim_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
	///就是这样
		Vibrate_EN(1);
		Firmware_Tim_windows();
		B_Key_release=1;
		R_Interface_maintain_Time=101;
		R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_access:{//usb插入
			Windows_Interrupt_Push(Battery_charging_interface);
		};break;
		case	USB_anomaly:{//USB异常
			Windows_Interrupt_Push(USB_Warning_interface);
		};break;
		default:{
			if(R_Interface_maintain_Time)
				R_Bright_screen_Time=R_Bright_screen_TimeMAX;
			if(!R_Interface_maintain_Time || R_key_anxiaOpen)
			{
//				if(kuaijie_banben_bz) ////这里这样就好了
//				{
//					kuaijie_banben_bz = 0;
					Windows_Switch(System_Set_Menu_interface);////把这个界面放在 就好了
//				}
//				else
//				{
//					Windows_Switch(Main_interface); ///统一返回主界
//				}
			}
			if(R_key_anxia == KEY_M)
			{
				//这样就OK了
				Windows_Switch(Main_interface);
			}
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}



