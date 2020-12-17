#include "WM_Disp.h"

static	u8	R_Cursor=0;

static	const	GUI_RECT	Button_Resis[]={{20,272,78,298},{170,272,220,298}};
#define	Button_Resis_COLOR_Release		0x57534E
static	const char	*const	Button_Resis_Name_Buff[]={
	"YES",
	"NO",
};
static	void	DISP_Button(u8	i,u8	B)
{
	GUI_COLOR	COLOR;
	GUI_COLOR	FontCOLOR;
	if(i==B)
	{
		COLOR=0xFFEF00;
		FontCOLOR=Button_Resis_COLOR_Release;
	}
	else
	{
		COLOR=Button_Resis_COLOR_Release;
		FontCOLOR=0xB5863C;
	}
	Print_Button_Disp(Button_Resis_Name_Buff[i],(GUI_RECT*)&Button_Resis[i],COLOR,FontCOLOR);
}
static	void	Resis_Data_update(u16	R)
{
	char	s[6];
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	RECT.x0=85;
	RECT.y0=232;
	RECT.x1=153;
	RECT.y1=251;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetFont(&GUI_FontArial27);
	GUI_SetColor(0xA6A6A6);
	sprintf(s,"%d.%02d&",R/100,R%100);
	s[5]=0;
	GUI_DispStringInRect(s,&RECT,GUI_TA_VCENTER| GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}
static	uc16	NewCoilRes[]={59,70,95,165,185,235,285,385,485,585,685,885,985,1185,1385,1485,1585,1785};
static	uc8	match_Watt[]={120,100,60,55,50,45,42,40,35,32,30,25,20,15,12,10,10,8};
//ؔ֯ƥƤ٦Êәط
u8	B_SMART_RES_Update=0;
u16	R_SMART_RES=0;
void	Auto_match_Watt_program(void)
{
	u8	i;
	if((R_SMART_RES<R_Res_average+15 || R_SMART_RES>R_Res_average+15)
		&&(R_SMART_RES<R_Res_average*9/10 || R_SMART_RES>R_Res_average*11/10))
	{
		i=18;
		while(i)
		{
			i--;
			if(R_Res_average>NewCoilRes[i])
			{
				R_User_Watt_Set=match_Watt[i]*10;
				B_SMART_RES_Update=1;
				break;
			}
		}
		R_SMART_RES=R_Res_average;
	}
}
void	Atomizer_inquiry_touch(void)
{
	if(R_key_anxia==KEY_ADD || R_key_anxia==KEY_SUB)
	{
		R_Cursor=!R_Cursor;
		DISP_Button(0,R_Cursor);
		DISP_Button(1,R_Cursor);
	}
	if(R_key_anxia_Mode==KEY_MODE)
	{
		if(R_Cursor==1)
		{
			B_Atomizer_inquiry=0;
			if(R_Res_Initial<R_Res_Initial_jiyi || R_Res_Initial>(4*R_Res_Initial_jiyi))
			{
				R_Res_Initial_jiyi=R_Res_Initial;
			}
			else
			{
				R_Res_Initial=R_Res_Initial_jiyi;
			}
		}
		else
		{
			B_Atomizer_inquiry=0;
			if(!B_LOCK_Res)
				R_Res_Initial_jiyi=R_Res_Initial;
		}
	}
	if(B_Atomizer_inquiry==0)
	 	Fanhui_Main_interface();
}

//
void	Atomizer_inquiry_windows(void)
{
	if(R_Cursor>1)
		R_Cursor=0;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	draw_Bmp_ex(d_ATOMIZEER_BMP,56,77);
	draw_Bmp_ex(d_NEW_ATOMIZEER_BMP,145,163);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontRaavi38B_19);
	GUI_DispStringHCenterAt("NEW ATOMIZER",120,36);
	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(15,267,225,303,18);
	Resis_Data_update(R_Res_Initial/10);
	DISP_Button(0,R_Cursor);
	DISP_Button(1,R_Cursor);
	PanelTurnOnDisplay();
}
//
u8	B_GOTO_Atomizer_inquiry=0;
void	Atomizer_inquiry_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		Atomizer_inquiry_windows();
		B_Key_release=1;
		R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_access:{//usbӥɫ
			Windows_Switch(Battery_charging_interface);
		};break;
		case	USB_anomaly:{//USBӬӣ
			Windows_Switch(USB_Warning_interface);
		};break;
		default:{
			Atomizer_inquiry_touch();
			if(!R_Bright_screen_Time)
			{
				if(B_BAT_Charge)
					Windows_Switch(Battery_charging_interface);
				else	if(B_USB_Low)
					Windows_Switch(USB_Warning_interface);
				else	if(R_Dial!=OFF_Dial)
					Windows_Switch(Screensaver_interface);
			}
			Batt_error_GOTO();
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}





