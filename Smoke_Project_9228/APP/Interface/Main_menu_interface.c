#include "WM_Disp.h"

//图标菜单
u8	R_Menu_SUM;
u32	*P_Menu_LOGO;
uc8	(*P_CursorXY)[2];
u8	*P_Cursor;
u8	*P_Cursor_Q;

#define	d_Menu_SUM	9

static	u8	R_Cursor=0; ///当前的光标
static	u8	R_Cursor_Q=0; ///上一次的光标

//菜单名称
#define	Menu_Name				"MODE MENU"
#define	Menu_Name_Font	GUI_FontRaavi38B_19
uc32	Menu_Cursor_Colour[]={0x008AFF,0x89D22C,0xF1A51C,0x05B9EE,0x2538DF};

//菜单LOGO
u8	Watt_Menu_I=1;
u8	Temp_Menu_I=2;
u8	CC_Menu_I=0;
static	uc32	Watt_Menu_LOGO[]={d_Menu_VW_S,d_Menu_VW_N,d_Menu_VW_H};
static	uc32	Temp_Menu_LOGO[]={d_Menu_VT_NI,d_Menu_VT_TI,d_Menu_VT_SS,d_Menu_TCR_M1,d_Menu_TCR_M2};
static	uc32	CC_Menu_LOGO[]={d_Menu_CCW,d_Menu_CCV,d_Menu_CCT_NI,d_Menu_CCT_TI,d_Menu_CCT_SS};

static	u32	Menu_LOGO[]={
	d_Menu_VW_N,d_Menu_SP,d_Menu_VT_SS,d_Menu_VV,d_Menu_CCW,d_Menu_BP,d_Menu_DIY,d_Menu_SET2
};

static	uc8	CursorXY[][2]={
	{45,92},{120,92},{195,92},
	{45,173},{120,173},{195,173},
	{45,254},					{195,254},
};

//选中光标
void	Selected_Cursor(u8 I,u8	B)
{
	GUI_MEMDEV_Handle hMem;
	u16	core_x,core_y;
	hMem = GUI_MEMDEV_CreateEx(P_CursorXY[I][0]-37,P_CursorXY[I][1]-37, 74, 74,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	core_x=Flash_GUI_BMP_GetXSizeEx(P_Menu_LOGO[I]);
	core_y=Flash_GUI_BMP_GetYSizeEx(P_Menu_LOGO[I]);
	draw_BmpToBitmap_ex(P_Menu_LOGO[I],P_CursorXY[I][0]-core_x/2,P_CursorXY[I][1]-core_y/2);
	if(B)
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_SelectMenuBottom,P_CursorXY[I][0]-37,P_CursorXY[I][1]-37);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, P_CursorXY[I][0]-37, P_CursorXY[I][1]-37);//
	GUI_MEMDEV_Delete(hMem);
}

//显示返回按钮	B:(0：未选中	1：选中)
void	Disp_EXIT_Key(char	*c,u8	B)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(66,280,109,37,GUI_MEMDEV_NOTRANS);  //创建内存
	GUI_MEMDEV_Select(hMem);  //选择一个内存设备作为绘图操作的目标。
	if(B)
	{
		draw_BmpToBitmap_ex(d_EXIT_ON_Bottom,66,280);  //高亮LOGO
		GUI_SetColor(GUI_WHITE);
	}
	else
	{
		draw_BmpToBitmap_ex(d_EXIT_Bottom,66,280);
		GUI_SetColor(GUI_BLACK);
	}
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispStringHCenterAt(c,120,295);  //显示字符串 c是指针
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,66,280);//
	GUI_MEMDEV_Delete(hMem);
}
//初始化菜单页面
void	Menu_Page_Init(void)
{
	u8	i;
	u16	x,y;
	*P_Cursor_Q=*P_Cursor;


	if(*P_Cursor==(R_Menu_SUM-1))
		Disp_EXIT_Key("EXIT",1);
	else
		Disp_EXIT_Key("EXIT",0);
	for(i=0;i<R_Menu_SUM-1;i++)
	{
		x=Flash_GUI_BMP_GetXSizeEx(P_Menu_LOGO[i]);
		y=Flash_GUI_BMP_GetYSizeEx(P_Menu_LOGO[i]);
		draw_Bmp_ex(P_Menu_LOGO[i],P_CursorXY[i][0]-x/2,P_CursorXY[i][1]-y/2);  //确定中点 往负半轴移动半张图的大小
		if(*P_Cursor==i)
		{
			Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_SelectMenuBottom,P_CursorXY[i][0]-37,P_CursorXY[i][1]-37);
		}
	}
}

//刷设置界面窗口
void	Menu_Bottom_Windows(char	*p,u8	x)
{
	draw_Bmp_ex(d_MenuNameBottom,0,0); //菜单底图
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,41,239,319);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&Menu_Name_Font);			//设置标题字体
	GUI_DispStringHCenterAt(p,120,12);
	GUI_SetColor(0xFFEF00);
	GUI_AA_SetFactor(3); 							//抗锯齿等级 1为无抗锯齿 6为最高抗锯齿
	GUI_AA_FillCircle(x,21,3);				//抗锯齿园
	GUI_AA_FillCircle(240-x,21,3);   	//大标题旁边两个蓝色小圆点
}
//
static	void	Menu_coordinate_Init(void)
{
	R_Menu_SUM=d_Menu_SUM;
	P_Menu_LOGO=Menu_LOGO;
	P_CursorXY=CursorXY;
	P_Cursor=&R_Cursor;
	P_Cursor_Q=&R_Cursor_Q;

	PanelTurnOffDisplay();
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);    //背景透明
	P_Menu_LOGO[0]=Watt_Menu_LOGO[Watt_Menu_I];
	P_Menu_LOGO[2]=Temp_Menu_LOGO[Temp_Menu_I];
	P_Menu_LOGO[4]=CC_Menu_LOGO[CC_Menu_I];
	if((Disp_windows_Q==Main_interface || Disp_windows_Q==Warning_interface) && B_windows_GOTO)
	{
		if(*P_Cursor>=d_Menu_SUM-1)
		{
			*P_Cursor=0;
		}
	}
	Menu_Bottom_Windows(Menu_Name,40);  //大标题

	Menu_Page_Init();
	PanelTurnOnDisplay();
}
//
void	KEY_Main_menu_operation(void)
{
	*P_Cursor=KEY_R_ADD_SUB(&R_key_anxiaOpen,*P_Cursor,KEY_ADD,KEY_SUB,R_Menu_SUM-1,0,1,1,200);
	if(*P_Cursor_Q!=*P_Cursor)
	{
		if(*P_Cursor==R_Menu_SUM-1)
		{
			Selected_Cursor(*P_Cursor_Q,0);
			Disp_EXIT_Key("EXIT",1);
		}
		else if(*P_Cursor_Q==R_Menu_SUM-1)
		{
			Disp_EXIT_Key("EXIT",0);
			Selected_Cursor(*P_Cursor,1);
		}
		else
		{
			Selected_Cursor(*P_Cursor_Q,0);
			Selected_Cursor(*P_Cursor,1);
		}
		*P_Cursor_Q=*P_Cursor;
	}
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
				R_Work_mode=d_Watt_mode;
				R_Watt_Strength=(Watt_Strength)Watt_Menu_I;
				Windows_Switch(Main_interface);
			}break;
			case	1:
			{
				R_Work_mode=d_SPP_mode;
				Windows_Switch(Main_interface);
			}break;
			case	2:
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
				Windows_Switch(Main_interface);
			}break;
			case	3:
			{
				R_Work_mode=d_Voltage_mode;
				Windows_Switch(Main_interface);
			}break;
			case	4:
			{
				if(CC_Menu_I==0)
					R_Work_mode=d_Custom_mode;
				else if(CC_Menu_I==1)
					R_Work_mode=d_CustomVolt_mode;
				else if(CC_Menu_I==2)
				{
					R_Work_mode=d_CustomTemp_mode;
					R_Atomizer=Ni;
				}
				else if(CC_Menu_I==3)
				{
					R_Work_mode=d_CustomTemp_mode;
					R_Atomizer=Ti;
				}
				else if(CC_Menu_I==4)
				{
					R_Work_mode=d_CustomTemp_mode;
					R_Atomizer=Ss;
				}
				Windows_Switch(Main_interface);
			}break;
			case	5:
			{
				R_Work_mode=d_Bypass_mode;
				Windows_Switch(Main_interface);
			}break;
			case	6:
			{
				Windows_Switch(DIY_menu_interface);
			}break;
			case	7:
			{
				Windows_Switch(System_Set_Menu_interface);
			}break;
			case	8:
			{
				Windows_Switch(Main_interface);
			}break;
		}
	}
}
//
void	Main_menu_interface(void)
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
