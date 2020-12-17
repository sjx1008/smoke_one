#include "WM_Disp.h"


//void	Locked_Click_interface(void)
//{
//	static	u8	Tim;
//	Key_Light_screen();
//	B_Key_release=0;
//	switch((u8)R_Skinning_mode)
//	{
//		case	Skinning_init:{//初始化
//			PanelTurnOffDisplay();
//			GUI_SetBkColor(GUI_BLACK);
//			GUI_Clear();
//			B_System_off=d_System_Locked;
//			{//绘制界面
//				GUI_SetColor(GUI_WHITE);
//				if(R_Language==English)
//				{
//					GUI_SetFont(&FontGill37);
//					GUI_DispStringHCenterAt("Locked",120,87);
//					GUI_SetFont(&FontGill27);
//					GUI_DispStringHCenterAt("Click 5X",120,123);
//				}
//				else
//				{
////					GUI_SetFont(&FontYaHei31);
//					GUI_DispStringHCenterAt("锁定",120,88);
////					GUI_SetFont(&FontYaHei28);
//					GUI_DispStringHCenterAt("5次解锁",120,122);
//				}
//			}
//			PanelTurnOnDisplay();
//			Tim=0;
//			R_Bright_screen_TimeMAX=50;
//			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
//		};break;
//		case	USB_access:{//usb插入
//			Windows_Interrupt_Push(Battery_charging_interface);
//		};break;
//		case	USB_anomaly:{//USB异常
//			Windows_Interrupt_Push(USB_Warning_interface);
//		};break;
//		default:{
//			if(R_key_5C==KEY_M)
//			{
//				B_System_off=d_System_Normal;
//				if(Atomizer_inquiry_GOTO(0))
//					Disp_windows_QQ=Main_interface;
//				else
//					Windows_Switch(Main_interface);
//			}
//			if(R_key_anzhu==KEY_M)
//			{
//				if(Tim>100)
//					Windows_Switch(System_off_interface);
//				else
//					Tim++;
//			}
//			else
//				Tim=0;
//			Screen_GOTO_charging();
//			Batt_error_GOTO();
//		};
//	}
//	R_Skinning_mode=Skinning_mode_null;
//}
//
static	void	System_off_windows(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_Vaporess_LOGO,65,56);
	draw_Bmp_ex(d_OMNI_LOGO,48,196);
	GUI_SetFont(&GUI_FontArial47);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringAt("4.2",126,191);
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(0xA9A9A9);
	GUI_DispStringHCenterAt(d_PCB_Software,120,250);
	GUI_DispStringHCenterAt(d_PCB_SoftwareTime,120,273);
	PanelTurnOnDisplay();
}
void	System_off_interface(void)
{
	static	u8	B;
	B_Key_release=0;
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(0);
		if(B_System_off!=d_System_Off)
		{
		B_System_off=d_System_Off;
		{//绘制界面
		System_off_windows();
		Vibrate_ON(d_System_OFF_Vibrate_Tim,7);
		}
		R_Interface_maintain_Time=31;
		B=1;
		}
		else
		{
		B=0;
		BL_PanelTurnOffDisplay();
		}
		R_Bright_screen_TimeMAX=31;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_anomaly:{//USB异常
				//Windows_Interrupt_Push(USB_Warning_interface);
		};break;
		default:{
			if(B)
			{
				if(!R_Interface_maintain_Time)
				{
					B=0;
					BL_PanelTurnOffDisplay();
				}
				else
				{
					R_Bright_screen_Time=R_Bright_screen_TimeMAX;
				}
			}
			else
			{
				if(B_BAT_Charge)
				{
					Windows_Interrupt_Push(Battery_charging_interface);
				}
				else
				{
					if(B_USB_Low)
						Windows_Interrupt_Push(USB_Warning_interface);
				}
			}
			if(R_key_5C==KEY_M)
			{
				B_System_off=d_System_Normal;
				Windows_Switch(BOOT_LOGO_interface);
			}
			Batt_error_GOTO();
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}
//

