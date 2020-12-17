#include "WM_Disp.h"

#define	d_Menu_SUM	4
static	u8	Cursor=0;
static	const char MenuNameE[]="Data";
static	const char MenuNameZ[]="参数";
static	const	char	*const	Menu_NAME_BUFFE[]={
	"WattPreheat",
	"TCR",
	"CPS",
	"Lock Resis",
};
static	const	char	*const	Menu_NAME_BUFFZ[]={
	"预热瓦数",
	"温控系数",
	"曲线参数",
	"锁定阻值",
};

static	void (*const menu_Set_goto[])(void)={
Watt_Preheat_interface,TCT_adjust_interface,Custom_curve_adjustment_interface,
LOCK_Resis_interface};

static	void	System_Set_Operation(void)
{
u8	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Cursor,KEY_ADD,KEY_SUB,d_Menu_SUM-1,0,1,1,200);
	if(R!=Cursor)
	{
		Cursor=R;
		Disp_menu2_Name();
	}
	
	if(R_key_anxiaOpen==KEY_M)
	{
		Windows_Switch(menu_Set_goto[Cursor]);
		Quick_setting_interface=Disp_windows;
	}
	Return_interface_GOTO(Main_menu_interface);
}

//
static	void	Menu_coordinate_Init(void)
{
	if(Disp_windows_Q==Main_menu_interface)
		Cursor=0;
	
	if(R_Language==English)
		menu2_struct_Init((char*)MenuNameE,(char	**)Menu_NAME_BUFFE,d_Menu_SUM,&Cursor,English);
	else
		menu2_struct_Init((char*)MenuNameZ,(char	**)Menu_NAME_BUFFZ,d_Menu_SUM,&Cursor,Chinese);
	menu2_display_windows();
}
//
//
//
void	Data_Adjust_Menu_interface(void)
{
	Key_Light_screen();
	switch((u8)R_Skinning_mode)
	{
		case	Skinning_init:{//��ʼ��
			Menu_coordinate_Init();
			B_Key_release=1;
			R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		};break;
		case	USB_access:{//usb����
			Windows_Interrupt_Push(Battery_charging_interface);
		};break;
		case	USB_anomaly:{//USB�쳣
			Windows_Interrupt_Push(USB_Warning_interface);
		};break;
		default:{
			System_Set_Operation();
			Atomizer_inquiry_GOTO(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}


