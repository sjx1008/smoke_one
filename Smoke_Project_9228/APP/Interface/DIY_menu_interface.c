#include "WM_Disp.h"


#define	d_Menu_SUM	4

static	u8	R_Cursor=0; ///当前的光标
static	u8	R_Cursor_Q=0; ///上一次的光标

//菜单名称
#define	Menu_Name				"DIY MENU"
#define	Menu_Name_Font	GUI_FontRaavi38B_19

//菜单LOGO
static	uc32	Menu_LOGO[]={
	d_Menu_VW_SET,d_Menu_VT_SET,d_Menu_CC_SET
};

static	uc8	CursorXY[][2]={
	{120,86},
	{120,160},
	{120,234},
};

//
static	void	Menu_coordinate_Init(void)
{
	R_Menu_SUM=d_Menu_SUM;
	P_Menu_LOGO=(u32*)Menu_LOGO;
	P_CursorXY=CursorXY;
	P_Cursor=&R_Cursor;
	P_Cursor_Q=&R_Cursor_Q;

	PanelTurnOffDisplay();
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	if(Disp_windows_Q==Main_menu_interface && B_windows_GOTO)
	{
//		*P_Cursor=0;
		if(R_Work_mode==d_Custom_mode || R_Work_mode==d_CustomTemp_mode || R_Work_mode==d_CustomVolt_mode)
			*P_Cursor=2;
		else if(R_Work_mode==d_Temp_mode || R_Work_mode==d_TCR_mode)
			*P_Cursor=1;
		else
			*P_Cursor=0;
	}
	Menu_Bottom_Windows(Menu_Name,47);

	Menu_Page_Init();
	PanelTurnOnDisplay();
}
//
static	void	Main_menu_operation(void)
{
	KEY_Main_menu_operation();
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
	else if(R_key_anxia_Mode==KEY_MODE)
	{
		switch(*P_Cursor)
		{
			case	0:
			{
				Return_windows=DIY_menu_interface;
				Windows_Switch(VW_SET_menu_interface);
			}break;
			case	1:
			{
				Windows_Switch(VT_SET_menu_interface);
			}break;
			case	2:
			{
				Windows_Switch(CC_SET_menu_interface);
			}break;
			case	3:
			{
				Windows_Switch(Main_menu_interface);
			}break;
		}
	}
}
//
void	DIY_menu_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
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
			Warning_Windows=USB_anomaly_windows;
		};break;
		default:{
			Main_menu_operation();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}

//////////////////////////////////////////////////////////////
//////VW SET
#define	d_VW_SET_Menu_SUM	4

static	u8	R_VW_SETCursor=0; ///当前的光标
static	u8	R_VW_SETCursor_Q=0; ///上一次的光标

//菜单LOGO
static	uc32	VW_SET_Menu_LOGO[]={
	d_Menu_VW_H,d_Menu_VW_N,d_Menu_VW_S
};

static	void	VW_SET_coordinate_Init(void)
{
	R_Menu_SUM=d_VW_SET_Menu_SUM;
	P_Menu_LOGO=(u32*)VW_SET_Menu_LOGO;
	P_CursorXY=CursorXY;
	P_Cursor=&R_VW_SETCursor;
	P_Cursor_Q=&R_VW_SETCursor_Q;

	PanelTurnOffDisplay();
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	if((Disp_windows_Q==DIY_menu_interface || Disp_windows_Q==Main_interface) && B_windows_GOTO)
	{
		if(Watt_Menu_I==0)
			*P_Cursor=2;
		else	if(Watt_Menu_I==1)
			*P_Cursor=1;
		else
			*P_Cursor=0;
	}
	Menu_Bottom_Windows("VW SET",60);

	Menu_Page_Init();
	PanelTurnOnDisplay();
}
//
static	void	VW_SET_menu_operation(void)
{
	KEY_Main_menu_operation();
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
	else if(R_key_anxia_Mode==KEY_MODE)
	{
		switch(*P_Cursor)
		{
			case	0:
			{
				Watt_Menu_I=2;
			}break;
			case	1:
			{
				Watt_Menu_I=1;
			}break;
			case	2:
			{
				Watt_Menu_I=0;
			}break;
			case	3:
			{
				Windows_Switch(Return_windows);
			}break;
		}
		if(*P_Cursor<3)
		{
			R_Work_mode=d_Watt_mode;
			R_Watt_Strength=(Watt_Strength)Watt_Menu_I;
			Windows_Switch(Main_interface);
		}
	}
}
/////
void	VW_SET_menu_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		VW_SET_coordinate_Init();
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
			Warning_Windows=USB_anomaly_windows;
		};break;
		default:{
			VW_SET_menu_operation();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}



//////////////////////////////////////////////////////////////
//////VT SET
#define	d_VT_SET_Menu_SUM	8

static	u8	R_VT_SETCursor=0; ///当前的光标
static	u8	R_VT_SETCursor_Q=0; ///上一次的光标

//菜单LOGO
static	uc32	VT_SET_Menu_LOGO[]={
	d_Menu_VT_SS,d_Menu_VT_NI,d_Menu_VT_TI,d_Menu_TCR_M1,d_Menu_TCR_M2,d_Menu_LOCK_R,d_Menu_SET
};
static	uc8	VT_CursorXY[][2]={
	{45,86},{120,86},{195,86},
	{45,160},{120,160},{195,160},
	{120,234},
};

static	void	VT_SET_coordinate_Init(void)
{
	R_Menu_SUM=d_VT_SET_Menu_SUM;
	P_Menu_LOGO=(u32*)VT_SET_Menu_LOGO;
	P_CursorXY=VT_CursorXY;
	P_Cursor=&R_VT_SETCursor;
	P_Cursor_Q=&R_VT_SETCursor_Q;

	PanelTurnOffDisplay();
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	if(Disp_windows_Q==DIY_menu_interface && B_windows_GOTO)
	{
		if(Temp_Menu_I==0)
			*P_Cursor=1;
		else	if(Temp_Menu_I==1)
			*P_Cursor=2;
		else	if(Temp_Menu_I==2)
			*P_Cursor=0;
		else	if(Temp_Menu_I==3)
			*P_Cursor=3;
		else
			*P_Cursor=4;
	}
	Menu_Bottom_Windows("VT SET",60);

	Menu_Page_Init();
	PanelTurnOnDisplay();
}
//
static	void	VT_SET_menu_operation(void)
{
	KEY_Main_menu_operation();
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
	else if(R_key_anxia_Mode==KEY_MODE)
	{
		switch(*P_Cursor)
		{
			case	0:
			{
				Temp_Menu_I=2;
				R_Atomizer=Ss;
			}break;
			case	1:
			{
				Temp_Menu_I=0;
				R_Atomizer=Ni;
			}break;
			case	2:
			{
				Temp_Menu_I=1;
				R_Atomizer=Ti;
			}break;
			case	3:
			{
				Temp_Menu_I=3;
				R_TCR_term=M1;
			}break;
			case	4:
			{
				Temp_Menu_I=4;
				R_TCR_term=M2;
			}break;
			case	5:
			{
				Windows_Switch(LOCK_Resis_interface);
			}break;
			case	6:
			{
				Return_windows=VT_SET_menu_interface;
				Windows_Switch(TCR_Data_Set_interface);
			}break;
			case	7:
			{
				Windows_Switch(DIY_menu_interface);
			}break;
		}
		if(*P_Cursor<5)
		{
			if(*P_Cursor<3)
				R_Work_mode=d_Temp_mode;
			else
				R_Work_mode=d_TCR_mode;
			Windows_Switch(Main_interface);
		}
	}
}
/////
void	VT_SET_menu_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		VT_SET_coordinate_Init();
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
			Warning_Windows=USB_anomaly_windows;
		};break;
		default:{
			VT_SET_menu_operation();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}



//////////////////////////////////////////////////////////////
//////CC SET
#define	d_CC_SET_Menu_SUM	6

static	u8	R_CC_SETCursor=0; ///当前的光标
static	u8	R_CC_SETCursor_Q=0; ///上一次的光标

//菜单LOGO
static	uc32	CC_SET_Menu_LOGO[]={
	d_Menu_CCW,d_Menu_CCV,d_Menu_CCT_SS,d_Menu_CCT_NI,d_Menu_CCT_TI
};
static	uc8	CC_CursorXY[][2]={
	{45,86},{120,86},{195,86},
	{45,160},				{195,160},
};

static	void	CC_SET_coordinate_Init(void)
{
	R_Menu_SUM=d_CC_SET_Menu_SUM;
	P_Menu_LOGO=(u32*)CC_SET_Menu_LOGO;
	P_CursorXY=CC_CursorXY;
	P_Cursor=&R_CC_SETCursor;
	P_Cursor_Q=&R_CC_SETCursor_Q;

	PanelTurnOffDisplay();
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	if(Disp_windows_Q==DIY_menu_interface && B_windows_GOTO)
	{
		if(CC_Menu_I==0)
			*P_Cursor=0;
		else	if(CC_Menu_I==1)
			*P_Cursor=1;
		else	if(CC_Menu_I==2)
			*P_Cursor=3;
		else	if(CC_Menu_I==3)
			*P_Cursor=4;
		else
			*P_Cursor=2;
	}
	Menu_Bottom_Windows("CC SET",60);

	Menu_Page_Init();
	PanelTurnOnDisplay();
}
//
static	void	CC_SET_menu_operation(void)
{
	KEY_Main_menu_operation();
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
	else if(R_key_anxia_Mode==KEY_MODE)
	{
		Return_windows=CC_SET_menu_interface;
		switch(*P_Cursor)
		{
			case	0:
			{
				CC_Menu_I=0;
				R_Work_mode=d_Custom_mode;
				Windows_Switch(Custom_Data_Set_interface);
			}break;
			case	1:
			{
				CC_Menu_I=1;
				R_Work_mode=d_CustomVolt_mode;
				Windows_Switch(CCV_Custom_Data_Set_interface);
			}break;
			case	2:
			{
				CC_Menu_I=4;
				R_Work_mode=d_CustomTemp_mode;
				R_Atomizer=Ss;
				Windows_Switch(CCT_Custom_Data_Set_interface);
			}break;
			case	3:
			{
				CC_Menu_I=2;
				R_Work_mode=d_CustomTemp_mode;
				R_Atomizer=Ni;
				Windows_Switch(CCT_Custom_Data_Set_interface);
			}break;
			case	4:
			{
				CC_Menu_I=3;
				R_Work_mode=d_CustomTemp_mode;
				R_Atomizer=Ti;
				Windows_Switch(CCT_Custom_Data_Set_interface);
			}break;
			case	5:
			{
				Windows_Switch(DIY_menu_interface);
			}break;
		}
	}
}
/////
void	CC_SET_menu_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		CC_SET_coordinate_Init();
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
			Warning_Windows=USB_anomaly_windows;
		};break;
		default:{
			CC_SET_menu_operation();
			Atomizer_inquiry_GOTO(1);
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}



















