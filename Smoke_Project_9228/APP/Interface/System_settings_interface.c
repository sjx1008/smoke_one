
#include "WM_Disp.h"

//static	void	Min_UI_Set_interface(void);
static	void	Brightness_Set_interface(void);
static	void	PUFF_Set_interface(void);
static	void	BrightScreen_time_Set_interface(void);
//static	void	Default_Set_interface(void);
static	void	SMART_Set_interface(void);
static	void	KEY_LIGHT_Set_interface(void);
static	void	VIBRATE_Set_interface(void);

////////////////////////////

#define	d_Cursor_SUM				1
#define	d_System_set_SUM		10
static	const char	*const	SystemSet_Name_Buff[]={
	"DEFAULT",
	"TIME SET",
	"BRIGHTNESS",
	"PUFF COUNTER",
	"SMART ON/OFF",
	"AUTO ON/OFF",
	"SCREEN TIMEOUT",
	"KEY LIGHT",
	"VIBRATE",
	"VERSION",
};

static	u32	MENU_LOGO[]={
	d_Menu2_Default,
	d_Menu2_RTC,
	d_Menu2_ScreenLight,
	d_Menu2_PULL,
	d_Menu2_SMART,
	d_Menu2_AUTO,
	d_Menu2_ScreensaverTim,
	d_Menu2_KeyLed,
	d_Menu2_VIBRATE,
	d_Menu2_VERSION,

};
static	s8	R_Cursor_M=0;
static	uc8	SET1_Page_SUM[][2]={{0,3},{4,7},{8,10}};


//
static	void	Menu_coordinate_Init(void)
{
	if(Disp_windows_Q==Main_menu_interface && B_windows_GOTO)
	{
		R_Cursor_M=0;
	}
	MENU_LOGO_BUFF=MENU_LOGO;
	MODE_Name_Buff=SystemSet_Name_Buff;
	MODE_Name_Page=3;
	MODE_Name_Page_SUB=SET1_Page_SUM;
	R_MENU_Cursor_M=&R_Cursor_M;
	R_MENU_Cursor_M_Q=*R_MENU_Cursor_M;
	R_Cursor_SUM=d_Cursor_SUM;
	R_System_set_SUM=d_System_set_SUM;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("SYSTEM SET",38);
	Disp_MENU_Name(*R_MENU_Cursor_M,0xFF);
	PanelTurnOnDisplay();
}
//
void (*const System_Set_GOTO[])(void)={
Default_Set_interface,
RTC_Set_interface,
Brightness_Set_interface,
PUFF_Set_interface,
SMART_Set_interface,
AUTO_MODE_Set_interface,
BrightScreen_time_Set_interface,
KEY_LIGHT_Set_interface,
VIBRATE_Set_interface,
Firmware_Tim_interface,
Main_interface};
static	void	System_Set_Operation(void)
{
	*R_MENU_Cursor_M=KEY_R_ADD_SUB(&R_key_anxiaOpen,*R_MENU_Cursor_M,KEY_ADD,KEY_SUB,R_Cursor_SUM+R_System_set_SUM-1,0,1,1,100);
	if(R_MENU_Cursor_M_Q!=*R_MENU_Cursor_M)
	{
		Disp_MENU_Name(*R_MENU_Cursor_M,R_MENU_Cursor_M_Q);
		R_MENU_Cursor_M_Q=*R_MENU_Cursor_M;
	}
	if(R_key_anxia_Mode==KEY_MODE)
	{
		Windows_Switch(System_Set_GOTO[*R_MENU_Cursor_M]);
//		if(*R_MENU_Cursor_M == 9)
//		{
//		   kuaijie_banben_bz = 1;
//		}
//	  if(*R_MENU_Cursor_M == 10)
//		{
//		   kuaijie_fuwei_bz = 1;
//		}

	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//
void	System_Set_Menu_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);  //使能按下震动
		Menu_coordinate_Init();
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
			System_Set_Operation();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}

////主题颜色调节界面
//#define	d_Min_UICursor_SUM		1
//#define	d_Min_UI_set_SUM			5
//static	const char	*const	Min_UI_Name_Buff[]={
//	"ORANGE",
//	"GREEN",
//	"BLUE",
//	"YELLOW",
//	"RED",
//};

//static	u32	Min_UI_LOGO[]={
//	d_RED,
//	d_Green,
//	d_BLUE,
//	d_Yellow,
//	d_REDBREATHNG,
//};
//static	s8	R_Min_UICursor_M=0;
//static	uc8	Min_UI_Page_SUM[][2]={{0,3},{4,5}};
//static	void	Min_UI_Set_windows(void)
//{
//	if(Disp_windows_Q==System_Set_Menu_interface)
//	{
//		R_Min_UICursor_M=R_UI_Theme;
//	}
//
//	MENU_LOGO_BUFF=Min_UI_LOGO;
//	MODE_Name_Buff=Min_UI_Name_Buff;
//	MODE_Name_Page=2;
//	MODE_Name_Page_SUB=Min_UI_Page_SUM;
//	R_MENU_Cursor_M=&R_Min_UICursor_M;
//	R_MENU_Cursor_M_Q=*R_MENU_Cursor_M;
//	R_Cursor_SUM=d_Min_UICursor_SUM;
//	R_System_set_SUM=d_Min_UI_set_SUM;
//
//	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
//	PanelTurnOffDisplay();
//	draw_Bmp_ex(d_bgtop,0,0);
//	GUI_SetColor(GUI_WHITE);
//	GUI_SetFont(&GUI_FontSF_Proverbial_Gothic32);
//	GUI_DispStringHCenterAt("THEME COLOR",120,0);
//	GUI_RECT	RECT;
//	RECT.x0=0;
//	RECT.y0=33;
//	RECT.x1=239;
//	RECT.y1=319;
//	Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,0,33);
//	u8	a;
//	a=R_UI_Theme;
//	if(*R_MENU_Cursor_M<5)
//	{
//		R_UI_Theme=*R_MENU_Cursor_M;
//	}
//	Disp_MENU_Name(*R_MENU_Cursor_M,0xFF);
//	R_UI_Theme=a;
//	PanelTurnOnDisplay();
//}
//static	void	Min_UI_Set_touch(void)
//{
//	u8	a;
//	*R_MENU_Cursor_M=KEY_R_ADD_SUB(&R_key_anxiaOpen,*R_MENU_Cursor_M,KEY_ADD,KEY_SUB,R_Cursor_SUM+R_System_set_SUM-1,0,1,1,100);
//	if(R_MENU_Cursor_M_Q!=*R_MENU_Cursor_M)
//	{
//		a=R_UI_Theme;
//		if(*R_MENU_Cursor_M<5)
//		{
//			R_UI_Theme=*R_MENU_Cursor_M;
//		}
//		Disp_MENU_Name(*R_MENU_Cursor_M,R_MENU_Cursor_M_Q);
//		R_MENU_Cursor_M_Q=*R_MENU_Cursor_M;
//		R_UI_Theme=a;
//	}
//	if(R_key_anxia_Mode==KEY_MODE)
//	{
//		if(*R_MENU_Cursor_M<5)
//		{
//			R_UI_Theme=*R_MENU_Cursor_M;
//		}
//		Windows_Switch(System_Set_Menu_interface);
//	}
//	if(R_key_anxia==KEY_M)
//	{
//		Windows_Switch(Main_interface);
//	}
//}
//static	void	Min_UI_Set_interface(void)
//{
//	Key_Light_screen();
//	switch((u8)R_Skinning_mode)
//	{
//		case	Skinning_init:{//初始化
//			Vibrate_EN(1);
//			Min_UI_Set_windows();
//			B_Key_release=1;
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
//			Min_UI_Set_touch();
//			Atomizer_inquiry_GOTO(1);
//			GOTO_Screensaver_interface(1);
//			Screen_GOTO_charging();
//			Batt_error_GOTO();
//		}
//	}
//	R_Skinning_mode=Skinning_mode_null;
//}
//////////////////////////////////////////////////
//统计吸烟口数界面
static	u8	PUFF_Cursor=0;
static	const	GUI_RECT	Button_PUFF[]={{20,272,88,298},{130,272,220,298}};
#define	Button_PUFF_COLOR_Release		0x57534E
static	const char	*const	Button_PUFF_Name_Buff[]={
	"EXIT",
	"RESET",
};

static	void	DISP_Button_PUFF(u8	i,u8	B)
{
	GUI_COLOR	COLOR;
	GUI_COLOR	FontCOLOR;
	if(i==B)
	{
		COLOR=0xFFEF00;
		FontCOLOR=Button_PUFF_COLOR_Release;
	}
	else
	{
		COLOR=Button_PUFF_COLOR_Release;
		FontCOLOR=0xB5863C;
	}
	Print_Button_Disp(Button_PUFF_Name_Buff[i],(GUI_RECT*)&Button_PUFF[i],COLOR,FontCOLOR);
}


static	void	Print_PUFF_Data(void)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	RECT.x0=33;
	RECT.y0=87;
	RECT.x1=135;
	RECT.y1=115;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial41);
	GUI_DispDecAt(R_Statistics_number,RECT.x0,RECT.y0-6,5);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);

	RECT.x0=33;
	RECT.y0=155;
	RECT.x1=162;
	RECT.y1=184;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial41);
	GUI_GotoXY(RECT.x0,RECT.y0-6);
	GUI_DispFloatFix ((float)R_Vape_Time_number/600,7,2);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}
static	void	PUFF_Set_windows(void)
{
	if(Disp_windows_Q==System_Set_Menu_interface && B_windows_GOTO)
	{
		PUFF_Cursor=0;
	}

	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("PUFF COUNTER",22);
	draw_Bmp_ex(d_PULL_BMP,35,124);
	draw_Bmp_ex(d_PULLTim_BMP,35,193);
	GUI_SetFont(&GUI_FontRaavi18);
	GUI_SetColor(0xDDDDDD);
	GUI_DispStringAt("PUFF",63,124);
	GUI_DispStringAt("TIME",63,195);

	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispStringHCenterAt("M",173,163);
	Print_PUFF_Data();

	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(15,267,225,303,18);

	DISP_Button_PUFF(0,PUFF_Cursor);
	DISP_Button_PUFF(1,PUFF_Cursor);
	PanelTurnOnDisplay();
}
static	void	PUFF_Set_touch(void)
{
	u8 R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,PUFF_Cursor,KEY_ADD,KEY_SUB,1,0,1,1,100);
	if(PUFF_Cursor!=R)
	{
		PUFF_Cursor=R;
		DISP_Button_PUFF(0,PUFF_Cursor);
		DISP_Button_PUFF(1,PUFF_Cursor);
	}
	if(R_key_anxia_Mode==KEY_MODE)
	{
		if(PUFF_Cursor==0)
		{
			Windows_Switch(System_Set_Menu_interface);
		}
		else
		{
			R=1;
			if(R_Vape_Time_number==0 && R_Statistics_number==0)
				R=0;
			Clear_numberANDlengthTim();
			R_Smoke_Tim=0;
			R_Smoke_Tim10ms=0;
			if(R)
				Print_PUFF_Data();
		}
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
static	void	PUFF_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		PUFF_Set_windows();
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
			PUFF_Set_touch();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}



////////////////////////////////////////////////////
///////////////////亮屏时间设置///////////////////////
//
static	const	GUI_RECT	RECT_pfDraw={65,84,174,194};
static	void	__pfDraw(void * pData)
{
	void	(*P)(void);
	P=(void(*)(void))pData;
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_AA_SetFactor(4);
	GUI_SetPenSize(2);
	GUI_SetColor(0x5F5C58);
	GUI_AA_DrawArc(120,139,54,54,0,360);
	GUI_SetPenSize(10);
	GUI_AA_DrawArc(120,139,43,43,0,360);   //两个同心圆环 （空进度条）
	(*P)();
}

static	void	BrightScreen_time_Data_update(void)
{
	char	s[5],s2[2];
	u16	R;
	R=R_BrightScreen_TimeMAX/10;
	if(R<10)
	{
		GUI_SetFont(&GUI_FontArial60);
	}
	else if(R<100)
	{
		GUI_SetFont(&GUI_FontArial47);
	}
	else if(R<180)
	{
		GUI_SetFont(&GUI_FontArial41);
	}
	else if(R<600)
	{
		GUI_SetFont(&GUI_FontArial60);
	}
	else
	{
		GUI_SetFont(&GUI_FontArial47);
	}
	if(R<180)
	{
		sprintf(s,"%d",R);
		s2[0]='S';
		s2[1]=0;
	}
	else
	{
		sprintf(s,"%d",R/60);
		s2[0]='M';
		s2[1]=0;
	}
	GUI_SetColor(GUI_WHITE);
	s[4]=0;
	GUI_RECT	RECT={89,117,149,155};
	GUI_DispStringInRect(s,&RECT,GUI_TA_VCENTER| GUI_TA_HCENTER);
	GUI_SetColor(0xFFFF00);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispStringHCenterAt(s2,120,155);
	R=((d_BrightScreen_TimeMAX-R_BrightScreen_TimeMAX)*450+R_BrightScreen_TimeMAX*90)/d_BrightScreen_TimeMAX;
	GUI_AA_SetFactor(4);
	GUI_SetColor(0xFFEF00);
	GUI_SetPenSize(10);
	GUI_AA_DrawArc(120,139,43,43,R,450);
}
static	void	Screen_Tim_Data_update(void)
{
	char	s[5],s2[2];
	u16	R;
	R=R_Screen_Tim;
	if(R<10)
	{
		GUI_SetFont(&GUI_FontArial60);
	}
	else if(R<100)
	{
		GUI_SetFont(&GUI_FontArial47);
	}
	else if(R<180)
	{
		GUI_SetFont(&GUI_FontArial41);
	}
	else if(R<600)
	{
		GUI_SetFont(&GUI_FontArial60);
	}
	else
	{
		GUI_SetFont(&GUI_FontArial47);
	}
	if(R<180)
	{
		sprintf(s,"%d",R);
		s2[0]='S';
		s2[1]=0;
	}
	else
	{
		sprintf(s,"%d",R/60);
		s2[0]='M';
		s2[1]=0;
	}
	GUI_SetColor(GUI_WHITE);
	s[4]=0;
	GUI_RECT	RECT={89,117,149,155};
	GUI_DispStringInRect(s,&RECT,GUI_TA_VCENTER| GUI_TA_HCENTER);  //中心点对齐 写时间
	GUI_SetColor(0xFFFF00);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispStringHCenterAt(s2,120,155);
	R=((d_Screen_Tim_Max-R_Screen_Tim)*450+R_Screen_Tim*90)/d_Screen_Tim_Max;

	GUI_AA_SetFactor(4);
	GUI_SetColor(0xFFEF00);
	GUI_SetPenSize(10);
	GUI_AA_DrawArc(120,139,43,43,R,450);
}
//
static	void	BrightScreen_time_touch(void)
{
	u16	R;
	if(R_Dial==ON_Dial)
	{
		u8	bujin;
		if(R_Screen_Tim>180 || (R_Screen_Tim==180 && (R_key_anxiaOpen==KEY_ADD || R_key_anzhu==KEY_ADD)))
		{
			bujin=60;
		}
		else
		{
				bujin=1;
		}
		R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_Screen_Tim,KEY_ADD,KEY_SUB,d_Screen_Tim_Max,d_Screen_Tim_Min,bujin,1,30);
		if(R!=R_Screen_Tim)
		{
			R_Screen_Tim=R;
			GUI_MEMDEV_Draw((GUI_RECT*)&RECT_pfDraw,&__pfDraw,Screen_Tim_Data_update,0,0);//使用分段存储绘制
		}
	}
	else
	{
		R=10*KEY_R_ADD_SUB(&R_key_anxiaOpen,R_BrightScreen_TimeMAX/10,KEY_ADD,KEY_SUB,d_BrightScreen_TimeMAX/10,d_BrightScreen_TimeMIN/10,1,1,30);
		if(R!=R_BrightScreen_TimeMAX)
		{
			R_BrightScreen_TimeMAX=R;
			R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
			GUI_MEMDEV_Draw((GUI_RECT*)&RECT_pfDraw,&__pfDraw,BrightScreen_time_Data_update,0,0);//使用分段存储绘制
		}
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//

static	void	BrightScreen_time_Set_windows(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("SCREEN TIMEOUT",10);
	draw_Bmp_ex(d_Demarcation_line,2,230);

	Disp_EXIT_Key("OK",0);

	if(R_Dial==ON_Dial)
	{
		GUI_MEMDEV_Draw((GUI_RECT*)&RECT_pfDraw,&__pfDraw,Screen_Tim_Data_update,0,0);//使用分段存储绘制
	}
	else
	{
		GUI_MEMDEV_Draw((GUI_RECT*)&RECT_pfDraw,&__pfDraw,BrightScreen_time_Data_update,0,0);//使用分段存储绘制
	}
	PanelTurnOnDisplay();
}
//
static	void	BrightScreen_time_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		BrightScreen_time_Set_windows();
		B_Key_release=1;
		B_Set_OK=0;
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
			if(!B_Set_OK)
			{
				BrightScreen_time_touch();
				if(R_key_anxia_Mode==KEY_MODE)
				{
					B_Set_OK=1;
					R_Interface_maintain_Time=d_OK_stop_Tim;
					Disp_EXIT_Key("OK",1);
				}
				Atomizer_inquiry_GOTO(1);
				GOTO_Screensaver_interface(1);
				Screen_GOTO_charging();
			}
			else
			{
				if(!R_Interface_maintain_Time)
					Windows_Switch(System_Set_Menu_interface);
			}
			Batt_error_GOTO();
		}
	}
	if(Disp_windows_Set!=Screensaver_interface)
		(*Disp_Sleep)();
	R_Skinning_mode=Skinning_mode_null;
}
//


////////////////////////////////////////////////////
///////////////////屏幕亮度设置界面///////////////////////
//
static	void	Brightness_Data_update(void)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_Create(0,0,108,7);
	GUI_MEMDEV_Select(hMem);
	GUI_AA_SetFactor(3);
	GUI_SetColor(0x57534E);
	GUI_AA_FillRoundedRect(0,0,107,6,3);
	GUI_SetColor(0xFFEF00);
	GUI_AA_FillRoundedRect(0,0,101*(R_Screen_brightness-1)/(d_Screen_brightness_MAX-1)+6,6,3);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, 66, 132);//显示
	GUI_MEMDEV_Delete(hMem);
}
//
static	void	Brightness_Set_touch(void)
{
	u16	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_Screen_brightness,KEY_ADD,KEY_SUB,d_Screen_brightness_MAX,1,1,0,30);
	if(R!=R_Screen_brightness)
	{
		R_Screen_brightness=R;
		Brightness_Data_update();
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//

static	void	Brightness_Set_windows(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("BRIGHTNESS",38);
	draw_Bmp_ex(d_Demarcation_line,2,221);

	draw_Bmp_ex(d_ScreenDark_BMP,27,119);
	draw_Bmp_ex(d_ScreenLight_BMP,180,119);

	Disp_EXIT_Key("OK",0);

	Brightness_Data_update();
	PanelTurnOnDisplay();
}
//
static	void	Brightness_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		Brightness_Set_windows();
		B_Key_release=1;
		B_Set_OK=0;
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
			if(!B_Set_OK)
			{
				Brightness_Set_touch();
				if(R_key_anxia_Mode==KEY_MODE)
				{
					B_Set_OK=1;
					R_Interface_maintain_Time=d_OK_stop_Tim;
					Disp_EXIT_Key("OK",1);
				}
				Atomizer_inquiry_GOTO(1);
				GOTO_Screensaver_interface(1);
				Screen_GOTO_charging();
			}
			else
			{
				if(!R_Interface_maintain_Time)
					Windows_Switch(System_Set_Menu_interface);
			}
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}
//

////////////////////////////////////////////////////
///////////////////恢复出厂设置///////////////////////
//
static	u8	R_Default_Cursor=0;
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
void	Default_Set_touch(void)
{
	u16	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_Default_Cursor,KEY_ADD,KEY_SUB,1,0,1,1,100);
	if(R!=R_Default_Cursor)
	{
		R_Default_Cursor=R;
		DISP_Button(0,R_Default_Cursor);
		DISP_Button(1,R_Default_Cursor);
	}
	if(R_key_anxiaOpen_Mode==KEY_MODE)
	{
		if(!R_Default_Cursor)
		{
			//恢复默认值
			Default_Data();
			Windows_Switch(Main_interface);
		}
		else
		{
//		  if(kuaijie_fuwei_bz)
//			{
			  Windows_Switch(System_Set_Menu_interface);
//			}
//			else
//			{
//			  Windows_Switch(Main_interface);
//			}
		}
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//
static	void	Default_Set_windows(void)
{
	if((Disp_windows_Q==System_Set_Menu_interface || Disp_windows_Q==Main_interface) && B_windows_GOTO)
		R_Default_Cursor=1;

	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("SYSTEM SET",38);
	draw_Bmp_ex(d_Demarcation_line,2,230);
	draw_Bmp_ex(d_Default_BMP,83,103);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontRaavi49B_22);
	GUI_DispStringHCenterAt("DEFAULT",120,200);
	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(15,267,225,303,18);
	DISP_Button(0,R_Default_Cursor);
	DISP_Button(1,R_Default_Cursor);
	PanelTurnOnDisplay();
}
//
void	Default_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		Default_Set_windows();
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
			Default_Set_touch();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}
//

////////////////////////////////////////////////////
///////////////////SMART设置///////////////////////
//
static	u8	R_SMART_Cursor=0;
static	const	GUI_RECT	Button_SMART[]={{20,272,77,298},{155,272,218,298}};
#define	Button_Resis_COLOR_Release		0x57534E
static	const char	*const	Button_SMART_Name_Buff[]={
	"ON",
	"OFF",
};
static	void	DISP_SMART_Button(u8	i,u8	B)
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
	Print_Button_Disp(Button_SMART_Name_Buff[i],(GUI_RECT*)&Button_SMART[i],COLOR,FontCOLOR);
}



void	SMART_Set_touch(void)
{
	u16	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_SMART_Cursor,KEY_ADD,KEY_SUB,1,0,1,1,100);
	if(R!=R_SMART_Cursor)
	{
		R_SMART_Cursor=R;
		DISP_SMART_Button(0,R_SMART_Cursor);
		DISP_SMART_Button(1,R_SMART_Cursor);
	}
	if(R_key_anxiaOpen_Mode==KEY_MODE)
	{
		if(!R_SMART_Cursor)
			B_SMART_mode=1;
		else
			B_SMART_mode=0;
		Windows_Switch(System_Set_Menu_interface);
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//
static	void	SMART_Set_windows(void)
{
	if(Disp_windows_Q==System_Set_Menu_interface && B_windows_GOTO)
	{
		if(B_SMART_mode)
			R_SMART_Cursor=0;
		else
			R_SMART_Cursor=1;
	}


	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("SYSTEM SET",38);
	draw_Bmp_ex(d_Demarcation_line,2,230);
	draw_Bmp_ex(d_SMART_BMP,75,86);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontRaavi49B_22);
	GUI_DispStringHCenterAt("SMART",120,200);
	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(15,267,225,303,18);
	DISP_SMART_Button(0,R_SMART_Cursor);
	DISP_SMART_Button(1,R_SMART_Cursor);

	PanelTurnOnDisplay();
}
//
static	void	SMART_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		SMART_Set_windows();
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
			SMART_Set_touch();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}
//
//////////////////////////////////////
//AUTO模式设置
static	u8	AUTO_MODE_Cursor=0;
void	AUTO_MODE_Set_touch(void)
{
	u16	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,AUTO_MODE_Cursor,KEY_ADD,KEY_SUB,1,0,1,1,100);
	if(R!=AUTO_MODE_Cursor)
	{
		AUTO_MODE_Cursor=R;
		DISP_SMART_Button(0,AUTO_MODE_Cursor);
		DISP_SMART_Button(1,AUTO_MODE_Cursor);
	}
	if(R_key_anxiaOpen_Mode==KEY_MODE)
	{
		if(!AUTO_MODE_Cursor)
			B_AUOT_MODE=1;
		else
			B_AUOT_MODE=0;
		Windows_Switch(System_Set_Menu_interface);
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//
static	void	AUTO_MODE_Set_windows(void)
{
	if(Disp_windows_Q==System_Set_Menu_interface && B_windows_GOTO)
	{
		if(B_AUOT_MODE)
			AUTO_MODE_Cursor=0;
		else
			AUTO_MODE_Cursor=1;
	}

	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("APH",80);
	draw_Bmp_ex(d_Demarcation_line,2,230);
	draw_Bmp_ex(d_AUTO_BMP,73,89);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontRaavi49B_22);
	GUI_DispStringHCenterAt("AUTO",120,200);
	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(15,267,225,303,18);
	DISP_SMART_Button(0,AUTO_MODE_Cursor);
	DISP_SMART_Button(1,AUTO_MODE_Cursor);
	PanelTurnOnDisplay();
}

void	AUTO_MODE_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		AUTO_MODE_Set_windows();
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
			AUTO_MODE_Set_touch();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}

///////////////////////////////////////
//  按键灯亮度调节设置
static	void	KEY_LIGHT_Data_update(void)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_Create(0,0,108,7);
	GUI_MEMDEV_Select(hMem);
	GUI_AA_SetFactor(3);
	GUI_SetColor(0x57534E);
	GUI_AA_FillRoundedRect(0,0,107,6,3);
	if(R_Set_KEY_LED_Brig)
	{
		GUI_SetColor(0xFFEF00);
		GUI_AA_FillRoundedRect(0,0,107*R_Set_KEY_LED_Brig/8,6,3);
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, 66, 137);//显示
	GUI_MEMDEV_Delete(hMem);
}
//
static	void	KEY_LIGHT_Set_touch(void)
{
	u16	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_Set_KEY_LED_Brig,KEY_ADD,KEY_SUB,8,0,1,0,100);
	if(R!=R_Set_KEY_LED_Brig)
	{
		R_Set_KEY_LED_Brig=R;
		KEY_LIGHT_Data_update();
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//

static	void	KEY_LIGHT_Set_windows(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("KEY LIGHT",43);
	draw_Bmp_ex(d_Demarcation_line,2,221);

	draw_Bmp_ex(d_KeyLedDark_BMP,27,124);
	draw_Bmp_ex(d_KeyLedLight_BMP,180,124);

	Disp_EXIT_Key("OK",0);
	KEY_LIGHT_Data_update();
	PanelTurnOnDisplay();
}
//
static	void	KEY_LIGHT_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		KEY_LIGHT_Set_windows();
		B_Key_release=1;
		B_Set_OK=0;
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
			if(!B_Set_OK)
			{
				KEY_LIGHT_Set_touch();
				if(R_key_anxia_Mode==KEY_MODE)
				{
					B_Set_OK=1;
					R_Interface_maintain_Time=d_OK_stop_Tim;
					Disp_EXIT_Key("OK",1);
				}
				Atomizer_inquiry_GOTO(1);
				GOTO_Screensaver_interface(1);
				Screen_GOTO_charging();
			}
			else
			{
				if(!R_Interface_maintain_Time)
					Windows_Switch(System_Set_Menu_interface);
			}
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}
//
///////////////////////////////////////
//  震动强度调节设置
static	void	VIBRATE_Data_update(void)
{
	u16	R;

	R=((10-R_Set_Vibrate)*450+R_Set_Vibrate*90)/10;
	GUI_AA_SetFactor(4);
	GUI_SetColor(0xFFEF00);
	GUI_SetPenSize(10);
	GUI_AA_DrawArc(120,139,43,43,R,450);
	Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_VIBRATE2,105,124);
}
//
static	void	VIBRATE_Set_touch(void)
{
	u16	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_Set_Vibrate,KEY_ADD,KEY_SUB,10,0,1,0,100);
	if(R!=R_Set_Vibrate)
	{
		R_Set_Vibrate=R;
		Vibrate_ON(100,R_Set_Vibrate);
		GUI_MEMDEV_Draw((GUI_RECT*)&RECT_pfDraw,&__pfDraw,VIBRATE_Data_update,0,0);//使用分段存储绘制
	}
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//

static	void	VIBRATE_Set_windows(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("VIBRATE",45);
	draw_Bmp_ex(d_Demarcation_line,2,230);

	Disp_EXIT_Key("OK",0);

	GUI_MEMDEV_Draw((GUI_RECT*)&RECT_pfDraw,&__pfDraw,VIBRATE_Data_update,0,0);//使用分段存储绘制
	PanelTurnOnDisplay();
}
//
static	void	VIBRATE_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		VIBRATE_Set_windows();
		B_Key_release=1;
		B_Set_OK=0;
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
			if(!B_Set_OK)
			{
				VIBRATE_Set_touch();
				if(R_key_anxia_Mode==KEY_MODE)
				{
					B_Set_OK=1;
					R_Interface_maintain_Time=d_OK_stop_Tim;
					Disp_EXIT_Key("OK",1);
				}
				Atomizer_inquiry_GOTO(1);
				GOTO_Screensaver_interface(1);
				Screen_GOTO_charging();
			}
			else
			{
				if(!R_Interface_maintain_Time)
					Windows_Switch(System_Set_Menu_interface);
			}
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}
//






