#include "WM_Disp.h"

void (*Quick_setting_interface)(void);

static	const	char	*const	Watt_Strength_chars[]={
	"Soft",
	"Nor",
	"Hard",
};
static	const	char	*const	Watt_Strength_zhong[]={
	"柔和",
	"正常",
	"暴力",
};
static	void	Watt_Preheat_Selected(u8	i,u8	B)
{
	u32	Color,BkColor;
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	if(B){
		BkColor=GUI_WHITE;
		Color=GUI_BLACK;}
	else{
		BkColor=GUI_BLACK;
		Color=GUI_WHITE;}
	hMem = GUI_MEMDEV_Create(0, 0, 64, 64);
	GUI_MEMDEV_Select(hMem);
//	GUI_MEMDEV_Clear(hMem);
	GUI_AA_SetFactor(3);//6
	GUI_SetColor(BkColor);
	if(B)
	{
		GUI_AA_FillCircle(32,32,31);
		GUI_SetColor(Color);
	}
	else
	{
		GUI_FillRect(0,0,64,64);
		GUI_SetColor(Color);
	}
	RECT.x0=0;
	RECT.y0=0;
	RECT.x1=63;
	RECT.y1=63;
	if(R_Language==English)
	{
		GUI_SetFont(&FontGill30);
		GUI_DispStringInRect(Watt_Strength_chars[i],&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
	}
	else
	{
		GUI_SetFont(&FontYaHei28);
		GUI_DispStringInRect(Watt_Strength_zhong[i],&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, 21+68*i, 99);//显示
	GUI_MEMDEV_Delete(hMem);
}


static	void	Menu_touch(void)
{
		u8	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_Watt_Strength,KEY_ADD,KEY_SUB,2,0,1,1,200);
	if(R!=R_Watt_Strength)
	{
		Watt_Preheat_Selected(R_Watt_Strength,0);
		R_Watt_Strength=(Watt_Strength)R;
		Watt_Preheat_Selected(R_Watt_Strength,1);
	}

	if(R_key_anxiaOpen==KEY_M)
	{
		Windows_Switch(Quick_setting_interface);
	}
	Return_interface_GOTO(Quick_setting_interface);
}
//
static	void	Watt_Preheat_windows(void)
{
	u8	i;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	draw_Bmp_ex(d_bottom_level_menu_interface,0,0);
	GUI_SetColor(GUI_WHITE);
	if(R_Language==English)
	{
		GUI_SetFont(&FontGill30);
		GUI_DispStringHCenterAt("WattPreheat",120,28);
	}
	else
	{
		GUI_SetFont(&FontYaHei31);
		GUI_DispStringHCenterAt("预热瓦数",120,26);
	}
	for(i=0;i<3;i++)
	{
		if(i==R_Watt_Strength)
			Watt_Preheat_Selected(i,1);
		else
			Watt_Preheat_Selected(i,0);
	}
	PanelTurnOnDisplay();
}
//
void	Watt_Preheat_interface(void)
{
	Key_Light_screen();
	switch((u8)R_Skinning_mode)
	{
		case	Skinning_init:{//Եʼۯ
			Watt_Preheat_windows();
			B_Key_release=1;
			R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		};break;
		case	USB_access:{//usbӥɫ
			Windows_Interrupt_Push(Battery_charging_interface);
		};break;
		case	USB_anomaly:{//USBӬӣ
			Windows_Interrupt_Push(USB_Warning_interface);
		};break;
		default:{
			Menu_touch();
			Atomizer_inquiry_GOTO(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}















