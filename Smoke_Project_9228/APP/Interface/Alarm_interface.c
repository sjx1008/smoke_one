
#include "gpio.h"
#include "WM_Disp.h"
//static	u8	R_Interface_maintain_Time_Q;

void	Short_circuit_windows(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_ATOMIZEER_BMP,56,54);
	draw_Bmp_ex(d_Open_ATOMIZEER_BMP,137,136);

	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringHCenterAt("SHORT",120,221);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringHCenterAt("ATOMIZER",120,253);
	R_Interface_maintain_Time=30;
}
void	Low_ATOMIZER_windows(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_ATOMIZEER_BMP,56,54);
	draw_Bmp_ex(d_Open_ATOMIZEER_BMP,137,136);

	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringHCenterAt("LOW",120,221);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringHCenterAt("ATOMIZER",120,253);
	R_Interface_maintain_Time=30;
}
void	Open_circuit_windows(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_ATOMIZEER_BMP,56,54);
	draw_Bmp_ex(d_Open_ATOMIZEER_BMP,137,136);

	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringHCenterAt("CHECK",120,221);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringHCenterAt("ATOMIZER",120,253);
	R_Interface_maintain_Time=30;
}
void	HIGH_ATOMIZER_windows(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_ATOMIZEER_BMP,56,54);
	draw_Bmp_ex(d_Open_ATOMIZEER_BMP,137,136);

	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringHCenterAt("HIGH",120,221);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringHCenterAt("ATOMIZER",120,253);
	R_Interface_maintain_Time=30;
}

void	Low_Battery_windows(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_LowBatt1_BMP,85,55);
	draw_Bmp_ex(d_LowBatt2_BMP,117,153);

	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringHCenterAt("LOW",120,221);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringHCenterAt("BATTERY",120,253);
	R_Interface_maintain_Time=50;
}

void	Smoking_timeout_windows(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_ATOMIZEER_BMP,56,54);
	draw_Bmp_ex(d_OverTim_BMP,141,135);

	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringHCenterAt("OVER 10S",120,231);
//	GUI_SetColor(GUI_WHITE);
//	GUI_DispStringHCenterAt("10S",120,253);
	R_Interface_maintain_Time=50;
}

void	PCB_Overheated_windows(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_ATOMIZEER_BMP,56,54);
	draw_Bmp_ex(d_TooHot_BMP,137,136);

	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringHCenterAt("TOO HOT",120,221);
//	GUI_SetColor(GUI_WHITE);
//	GUI_DispStringHCenterAt("10S",120,253);
	R_Interface_maintain_Time=50;
}

void	USB_anomaly_windows(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_USB_error1_BMP,79,44);
	draw_Bmp_ex(d_USB_error2_BMP,121,129);

	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_SetColor(0xFFEF00);
	GUI_DispStringHCenterAt("USB INPUT",120,221);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringHCenterAt("PROTECTION",120,253);
	R_Interface_maintain_Time=50;
}

void	FIRE_TO_UNLOCK_windows(void)
{
	draw_Bmp_ex(d_UnlockADDSUB_BMP,0,0);

	R_Interface_maintain_Time=30;
}

//////////////////////////////////////////////////////////////


void	MODE_TO_SET_windows(void)
{
	draw_Bmp_ex(d_GOTO_Menu_BMP,0,0);
	R_Interface_maintain_Time=30;
}
void	(*Warning_Windows)(void)=Short_circuit_windows;
void	Warning_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(!B_ADDSUB_LOCK);
		GUI_SetTextMode(GUI_TEXTMODE_TRANS);
		PanelTurnOffDisplay();
		(*Warning_Windows)();
		//R_Interface_maintain_Time_Q=R_Interface_maintain_Time;
		PanelTurnOnDisplay();
		B_Key_release=0;
		B_GOTO_Atomizer_inquiry=1;
		R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_access:{//usb≤Â»Î
			Windows_Switch(Battery_charging_interface);
		};break;
		case	USB_anomaly:{//USB“Ï≥£
			Windows_Interrupt_Push(USB_Warning_interface);
		};break;
		default:{
			if(B_System_off==d_System_Normal)
			{
//				if(R_Interface_maintain_Time_Q-R_Interface_maintain_Time<3)
				{
					if(Disp_windows_Q==Main_interface)
					{
						if(ADDSUB_LOCK_GOTO(0))
						{
							Windows_Switch(Main_interface);
						}
						Main_menu_GOTO();
					}
				}
				if(Warning_Windows==FIRE_TO_UNLOCK_windows || Warning_Windows==MODE_TO_SET_windows)
        {
          if(key_value&KEY_M)
					{
              Windows_Switch(Main_interface);
					    B_SET_Key_release=1;
					}
        }
//				Screen_smoking_GOTO();
				System_off_GOTO();
				if(!B_Atomizer_inquiry)
				{
					B_GOTO_Atomizer_inquiry=0;
				}
				if(!B_GOTO_Atomizer_inquiry)
				{
					Atomizer_inquiry_GOTO(0);
				}
				GOTO_Screensaver_interface(0);
			}
			if(!R_Interface_maintain_Time)
			{
				Fanhui_Main_interface();
			}
			Batt_error_GOTO();
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}

void	USB_Warning_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(!B_ADDSUB_LOCK);
		GUI_SetTextMode(GUI_TEXTMODE_TRANS);
		PanelTurnOffDisplay();
		USB_anomaly_windows();
		PanelTurnOnDisplay();
		B_GOTO_Atomizer_inquiry=1;
		R_Bright_screen_TimeMAX=300;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_access:{//usb≤Â»Î
			Windows_Switch(Battery_charging_interface);
		};break;
		default:{
			if(B_System_off==d_System_Normal)
			{
				if(!B_Atomizer_inquiry)
				{
					B_GOTO_Atomizer_inquiry=0;
				}
				if(!B_GOTO_Atomizer_inquiry)
				{
					Atomizer_inquiry_GOTO(0);
				}
				GOTO_Screensaver_interface(0);
			}
			if((((R_key_anxia&KEY_M) || (R_key_anxia && !B_ADDSUB_LOCK)) && B_System_off!=d_System_Off) || (B_USB_Low==0&&R_Bright_screen_Time<2370) || !B_USB_RinBit)
			{
				Fanhui_Main_interface();
			}
			if(R_key_5C==KEY_M)
			{
				if(B_System_off==d_System_Off)
				{
					B_System_off=d_System_Normal;
					Windows_Switch(BOOT_LOGO_interface);
				}
				else if(B_System_off==d_System_Locked)
				{
					B_System_off=d_System_Normal;
					Windows_Switch(Main_interface);
				}
			}
			Batt_error_GOTO();
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}


/////////

void	Batt_error_interface(void)
{
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(0);
		BL_PanelTurnOffDisplay();
		R_Bright_screen_TimeMAX=20;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		default:{
			if(!B_BAT_error)
			{
				B_System_off=d_System_Normal;
				TFT_VCC_Reset();
				Delay_Nms(50);
				TFT_VCC_Set();
				TFT_LCD_RESET();
				TFT_ST7789S_Init();
				Windows_Switch(Main_interface);
			}
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}



