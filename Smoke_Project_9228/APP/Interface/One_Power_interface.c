#include	"gpio.h"
#include "WM_Disp.h"

static	GUI_GIF_INFO GifInfo;
static	u16	GIF_I=0;
static	u16	GIF_Tim;


static	void	Out_Boot(void)
{

}
//å¼€æœºåŠ¨ç”»
static	void	Boot_animation_Init(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	Flash_GUI_GIF_GetInfoEx(d_Boot_animation,&GifInfo);
	BL_PanelTurnOnDisplay();
	Disp_Sleep=Out_Boot;
	GIF_Tim=0;
	GIF_I=0;
}

static	void	Boot_animation(void)
{
	GUI_GIF_IMAGE_INFO	pInfo;
	if(GIF_Tim)
	{
		GIF_Tim--;
		R_Interface_maintain_Time=10;
	}
	if(!GIF_Tim)
	{
		if(GIF_I<GifInfo.NumImages)
		{
			Flash_GUI_GIF_DrawSubEx(d_Boot_animation,0,38,GIF_I);
			Flash_GUI_GIF_GetImageInfoEx(d_Boot_animation,&pInfo,GIF_I);
			GIF_I++;
			GIF_Tim=pInfo.Delay ? pInfo.Delay/2	:	5;
			R_Interface_maintain_Time=10;
		}
	}
}

void	BOOT_LOGO_interface(void)
{
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Boot_animation_Init();
		Vibrate_EN(0);
		Vibrate_ON(d_BOOT_Vibrate_Tim,7);
		R_Interface_maintain_Time=10;
		R_Bright_screen_TimeMAX=50;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		default:{
			if(!R_Interface_maintain_Time)
			{
				if(Atomizer_inquiry_GOTO(0))
				 	Disp_windows_QQ=Main_interface;
				else
				{
					R_Auto_Locked_KEY=d_Auto_Locked_KEY_Tim;
					Windows_Switch(Main_interface);
				}
			}
			else
			{
				R_Bright_screen_Time=R_Bright_screen_TimeMAX;
			}
			System_off_GOTO();
		}
	}
	Boot_animation();
	if(Disp_windows_Set!=Disp_windows)
	{
		Out_Boot();
		Disp_Sleep=Disp_Sleep_NOP;				//æ˜¾ç¤ºè¿›å…¥ä¼‘çœ æ—¶çš„é’©å­å‡½æ•°
	}
	R_Skinning_mode=Skinning_mode_null;
}
//
//ä¸Šç”µ
void	One_Power_interface(void)
{
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(0);
		R_Bright_screen_TimeMAX=20;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		default:{
			if(!B_BAT_error)
			{
				TFT_VCC_Set();
				TFT_LCD_RESET();
				TFT_ST7789S_Init();
				Windows_Switch(BOOT_LOGO_interface);
			}
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}


