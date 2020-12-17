
#include "WM_Disp.h"

static	u8	B_Disp_Atomize=0;
static	u8	B_Disp_LOCK_Resis=0;
static	u8	R_Cursor=0;
static	u16	R_LOCK_Resis_Data;

static	const	char	*const	Hint_chars[]={
	"",
	"Check Atomizer",
};

static	void	Resis_Data_update(u16	R)
{
	char	s[6];
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	RECT.x0=85;
	RECT.y0=198;
	RECT.x1=153;
	RECT.y1=217;
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

static	void	LOCK_Resis_LOGO_update(u8	B)
{
	GUI_RECT	RECT;
	if(B)
	{
		RECT.x0=54;
		RECT.y0=20;
		RECT.x1=66;
		RECT.y1=25;
		Map_draw_bmpToBitmap_ex(d_LickRes_BMP,&RECT,136,135);
	}
	else
	{
		GUI_SetColor(GUI_BLACK);
		GUI_FillRect(136,135,148,140);
	}
}
static	void	Disp_Hint_chars(const	char	*const	R)
{
//	GUI_RECT	Rect;
//	GUI_MEMDEV_Handle hMem;
//	hMem = GUI_MEMDEV_Create(0, 0, 135, 25);
//	GUI_MEMDEV_Select(hMem);
//	GUI_SetColor(GUI_BLACK);
//	GUI_FillRect(0,0,135,25);
//	GUI_SetColor(GUI_ORANGE);
//	GUI_SetFont(Hint_charsFONT[R_Language]);
//	Rect.x0=0;
//	Rect.y0=0;
//	Rect.x1=134;
//	Rect.y1=24;
//	GUI_DispStringInRect(R,&Rect,GUI_TA_VCENTER|GUI_TA_HCENTER);
//	GUI_MEMDEV_Select(0);
//	GUI_MEMDEV_WriteAt(hMem, 54, 181);//显示
//	GUI_MEMDEV_Delete(hMem);
}
static	void	Disp_Resis_Data(void)
{
	if(B_LOCK_Res)
	{
		if(R_LOCK_Resis_Data!=R_Res_Initial_jiyi/10)
		{
			R_LOCK_Resis_Data=R_Res_Initial_jiyi/10;
			Resis_Data_update(R_LOCK_Resis_Data);
		}
		if(!B_Disp_LOCK_Resis)
		{
			B_Disp_LOCK_Resis=1;
//			LOCK_Resis_LOGO_update(1);
		}
		if(B_Disp_Atomize)
		{
			B_Disp_Atomize=0;
			Disp_Hint_chars(Hint_chars[0]);
		}
	}
	else
	{
		if(R_LOCK_Resis_Data!=R_Res_Initial/10)
		{
			R_LOCK_Resis_Data=R_Res_Initial/10;
			Resis_Data_update(R_LOCK_Resis_Data);
		}
		if(B_Disp_LOCK_Resis)
		{
			B_Disp_LOCK_Resis=0;
//			LOCK_Resis_LOGO_update(0);
		}
		if(R_Res_Initial>d_Res_usable || R_Res_Initial<d_Res_min)
		{
			if(R_Cursor==0)
			{
				if(!B_Disp_Atomize)
				{
					B_Disp_Atomize=1;
					Disp_Hint_chars(Hint_chars[1]);
				}
			}
			else
			{
				if(B_Disp_Atomize)
				{
					B_Disp_Atomize=0;
					Disp_Hint_chars(Hint_chars[0]);
				}
			}
		}
		else
		{
			if(B_Disp_Atomize)
			{
				B_Disp_Atomize=0;
				Disp_Hint_chars(Hint_chars[0]);
			}
		}
	}
}


//
static	const	GUI_RECT	Button_LOCK_Resis[]={{20,272,100,298},{108,272,218,298}};
#define	Button_LOCK_Resis_COLOR_Release		0x57534E
static	const char	*const	Button_LOCK_Resis_Name_Buff[]={
	"LOCK",
	"UNLOCK",
};
static	void	DISP_Button_LOCK(u8	i,u8	B)
{
	GUI_COLOR	COLOR;
	GUI_COLOR	FontCOLOR;
	if(i==B)
	{
		COLOR=0xFFEF00;
		FontCOLOR=Button_LOCK_Resis_COLOR_Release;
	}
	else
	{
		COLOR=Button_LOCK_Resis_COLOR_Release;
		FontCOLOR=0xB5863C;
	}
	Print_Button_Disp(Button_LOCK_Resis_Name_Buff[i],(GUI_RECT*)&Button_LOCK_Resis[i],COLOR,FontCOLOR);
}
static	void	LOCK_Resis_Windows(void)
{
	if(Disp_windows_Q==VT_SET_menu_interface && B_windows_GOTO)
	{
		if(B_LOCK_Res)
			R_Cursor=0;
		else
			R_Cursor=1;
	}

	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("LOCK RESIS",36);
	draw_Bmp_ex(d_LickRes_BMP,82,115);

	if(B_LOCK_Res)
	{
		B_Disp_LOCK_Resis=1;
		Resis_Data_update(R_Res_Initial_jiyi/10);
		R_LOCK_Resis_Data=R_Res_Initial_jiyi/10;
	}
	else
	{
		B_Disp_LOCK_Resis=0;
		Resis_Data_update(R_Res_Initial/10);
		R_LOCK_Resis_Data=R_Res_Initial/10;
	}
	LOCK_Resis_LOGO_update(!R_Cursor);
	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(15,267,225,303,18);
	DISP_Button_LOCK(0,R_Cursor);
	DISP_Button_LOCK(1,R_Cursor);
	PanelTurnOnDisplay();
	PanelTurnOnDisplay();
}

static	void	LOCK_Resis_touch(void)
{
	u8	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_Cursor,KEY_ADD,KEY_SUB,1,0,1,1,100);
	if(R!=R_Cursor)
	{
		R_Cursor=R;
		DISP_Button_LOCK(0,R_Cursor);
		DISP_Button_LOCK(1,R_Cursor);
		LOCK_Resis_LOGO_update(!R_Cursor);
	}
	if(R_key_anxia_Mode==KEY_MODE)
	{
		if(R_Work_mode==d_CustomTemp_mode)
		{
			if(CC_Menu_I>1)
			{
				R_Atomizer=(Atomizer)(CC_Menu_I-2);
			}
			else
			{
				CC_Menu_I=4;
				R_Atomizer=(Atomizer)(CC_Menu_I-2);
			}
		}
		else
		{
			if(Temp_Menu_I<3)
			{
				R_Work_mode=d_Temp_mode;
				R_Atomizer=(Atomizer)Temp_Menu_I;
			}
			else
			{
				R_Work_mode=d_TCR_mode;
				R_TCR_term=(TCR_term)(Temp_Menu_I-3);
			}
		}
		if(R_Cursor==0)
		{
			if(R_Res_Initial<=d_Res_usable && R_Res_Initial>=d_Res_min)
			{
				B_LOCK_Res=1;
				R_Res_Initial_jiyi=R_Res_Initial;
				Windows_Switch(Main_interface);
			}
			else
			{
				Windows_Interrupt_Push(Warning_interface);
				Warning_Windows=Open_circuit_windows;
				Disp_windows_QQ=Main_interface;
			}
		}
		else
		{
			B_LOCK_Res=0;
			Windows_Switch(Main_interface);
		}
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//
void	LOCK_Resis_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		LOCK_Resis_Windows();
		B_Key_release=1;
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
			LOCK_Resis_touch();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	Disp_Resis_Data();
	R_Skinning_mode=Skinning_mode_null;
}


