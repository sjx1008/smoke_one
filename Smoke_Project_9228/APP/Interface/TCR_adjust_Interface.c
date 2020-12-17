#include "WM_Disp.h"

static	u8	R_Cursor=0;
u8	R_TCR_SetProject=0;	//需要设置的项
static	Load_Data	*Atomizer_TCR_Pointer;
static	Load_Data	*Atomizer_TCR_BUFF[]={&Load_Ss316,&Load_Ni200,&Load_Ti,&Load_M1,&Load_M2};
static	const char	*const	VT_project_Name[]={
"SS",
"NI",
"TI",
"M1",
"M2",
};

//
static	uc16	R_Atomizer_TCR[][2]={{50,250},{400,800},{150,550},{1,1000},{1,1000}};

/////////////////////////////////////////////////////////////////////////////
/////TCR参数设置界面////////////////////////////////////////////////////////////////////////
//左箭头
static	void	Disp_L_Arrow(u8	B)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(35,71+24,31,28,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRect(35,71+24,65,98+24);
	if(B)
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_D_L_Arrow,35,71+24);
	else
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_D_NO_L_Arrow,35,71+24);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, 35, 71+24);//显示
	GUI_MEMDEV_Delete(hMem);
}
//右箭头
static	void	Disp_R_Arrow(u8	B)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(175,71+24,31,28,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRect(175,71+24,205,98+24);
	if(B)
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_D_R_Arrow,175,71+24);
	else
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_D_NO_R_Arrow,175,71+24);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, 175, 71+24);//显示
	GUI_MEMDEV_Delete(hMem);
}

//雾化器种类更新
static	void	Disp_Atomizer(void)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT={87,94,153,123};
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRect(RECT.x0,RECT.y0,RECT.x1,RECT.y1);

	if(R_Cursor==0)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RECT.x0,RECT.y0,RECT.x1,RECT.y1,14);
	}

	GUI_SetFont(&GUI_FontRaavi64B_28);
	GUI_SetColor(0xFFFFFF);
	GUI_DispStringInRect(VT_project_Name[R_TCR_SetProject],&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,RECT.x0,RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}

////TCR参数更新
static	void	Disp_TCR_Data(void)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT={18,160,221,193};
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==1)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RECT.x0,RECT.y0,RECT.x1,RECT.y1,14);
		GUI_SetColor(GUI_BLACK);
	}
	else
	{
		GUI_SetColor(GUI_WHITE);
	}
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispStringAt("TCR:",29,166);
	GUI_GotoXY(166,166);
	GUI_DispDecMin(Atomizer_TCR_Pointer->Gradient);
	u16	x;
	x=(Atomizer_TCR_Pointer->Gradient-R_Atomizer_TCR[R_TCR_SetProject][0])*70/(R_Atomizer_TCR[R_TCR_SetProject][1]-R_Atomizer_TCR[R_TCR_SetProject][0]);
	if(R_Cursor==1)
	{
		GUI_SetColor(GUI_WHITE);
	}
	else
	{
		GUI_SetColor(0xFFEF00);
	}
	for(u8	i=0;i<10;i++)
	{
		if(x>=(i*7+6))
		{
			GUI_FillRect(76+i*9,169,82+i*9,184);
		}
		else if(x>=(i*7) && x<(i*7+6))
		{
			GUI_FillRect(76+i*9,169,76+i*2+x,184);
			GUI_SetColor(0x57534E);
			GUI_FillRect(77+i*2+x,169,82+i*9,184);
		}
		else
		{
			GUI_SetColor(0x57534E);
			GUI_FillRect(76+i*9,169,82+i*9,184);
		}
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,RECT.x0,RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}

////PWR参数更新
static	void	Disp_PWR_Data(void)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT={18,206,221,239};
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==2)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RECT.x0,RECT.y0,RECT.x1,RECT.y1,14);
		GUI_SetColor(GUI_BLACK);
	}
	else
	{
		GUI_SetColor(GUI_WHITE);
	}
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispStringAt("PWR:",23,212);
	GUI_GotoXY(166,212);
	GUI_DispDecMin(Atomizer_TCR_Pointer->WattsMAX);
	GUI_SetColor(0xFFEF00);
	GUI_DispChar('w');
	u16	x;
	x=(Atomizer_TCR_Pointer->WattsMAX-d_User_Watt_min/10)*700/(d_User_Watt_max-d_User_Watt_min);
	if(R_Cursor==2)
	{
		GUI_SetColor(GUI_WHITE);
	}
	else
	{
		GUI_SetColor(0xFFEF00);
	}
	for(u8	i=0;i<10;i++)
	{
		if(x>=(i*7+6))
		{
			GUI_FillRect(76+i*9,215,82+i*9,230);
		}
		else if(x>=(i*7) && x<(i*7+6))
		{
			GUI_FillRect(76+i*9,215,76+i*2+x,230);
			GUI_SetColor(0x57534E);
			GUI_FillRect(77+i*2+x,215,82+i*9,230);
		}
		else
		{
			GUI_SetColor(0x57534E);
			GUI_FillRect(76+i*9,215,82+i*9,230);
		}
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,RECT.x0,RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}



static	void	update_Cursor(u8	i)
{
	switch (i)
	{
		case	0:
			Disp_Atomizer();
			break;
		case	1:
			Disp_TCR_Data();
			break;
		default:
			Disp_PWR_Data();
			break;
	}
}




static	u8	cursor_key_value=0;
static	uc8	BUFF_Temp_Menu_I[]={1,2,0,3,4};

static	void	TCR_Data_touch(void)
{
	u8	bujin;
	u16	R;

	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}

	if(R_key_anxiaOpen_Mode==KEY_MODE)
	{
		u8	a;
		a=R_Cursor;
		R_Cursor++;
		if(R_Cursor>2)
			R_Cursor=0;
		update_Cursor(R_Cursor);
		update_Cursor(a);
	}
	if(R_Cursor==0)
	{
		R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_TCR_SetProject,KEY_ADD,KEY_SUB,4,0,1,1,100);
		if(R!=R_TCR_SetProject)
		{
			R_TCR_SetProject=R;
			Atomizer_TCR_Pointer=Atomizer_TCR_BUFF[R_TCR_SetProject];
			Disp_Atomizer();
			Disp_TCR_Data();
			Disp_PWR_Data();
			if(Return_windows==Main_interface)
			{
				if(R_TCR_SetProject>2)
					Temp_Menu_I=R_TCR_SetProject;
				else if(R_TCR_SetProject==0)
					Temp_Menu_I=2;
				else if(R_TCR_SetProject==1)
					Temp_Menu_I=0;
				else if(R_TCR_SetProject==2)
					Temp_Menu_I=1;
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
		}
	}
	else if(R_Cursor==1)
	{
		if(Atomizer_TCR_Pointer->Gradient%10==0 && (R_key_anzhu==KEY_ADD || R_key_anzhu==KEY_SUB))
			bujin=10;
		else
			bujin=1;
		R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Atomizer_TCR_Pointer->Gradient,KEY_ADD,KEY_SUB,R_Atomizer_TCR[R_TCR_SetProject][1],R_Atomizer_TCR[R_TCR_SetProject][0],bujin,1,10);
		if(R!=Atomizer_TCR_Pointer->Gradient || B_Display_refresh)
		{
			B_Display_refresh=0;
			Atomizer_TCR_Pointer->Gradient=R;
			Disp_TCR_Data();
		}
	}
	else
	{
		R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Atomizer_TCR_Pointer->WattsMAX,KEY_ADD,KEY_SUB,d_User_Watt_max/10,d_User_Watt_min/10,1,1,10);
		if(R!=Atomizer_TCR_Pointer->WattsMAX || B_Display_refresh)
		{
			B_Display_refresh=0;
			Atomizer_TCR_Pointer->WattsMAX=R;
			Disp_PWR_Data();
		}
	}
	if(R_Cursor==0)
	{
		if(cursor_key_value!=key_value)
		{
			if(key_value==KEY_ADD)
				Disp_R_Arrow(1);
			else
				Disp_R_Arrow(0);

			if(key_value==KEY_SUB)
				Disp_L_Arrow(1);
			else
				Disp_L_Arrow(0);
			cursor_key_value=key_value;
		}
	}
	else
	{
		if(cursor_key_value!=0)
		{
			cursor_key_value=0;
			Disp_L_Arrow(0);
			Disp_R_Arrow(0);
		}
	}
}
//
//

static	void	TCR_Data_Set_windows(void)
{
	if((Disp_windows_Q==VT_SET_menu_interface || Disp_windows_Q==Main_interface) && B_windows_GOTO)
	{
		R_Cursor=0;
		R_TCR_SetProject=BUFF_Temp_Menu_I[Temp_Menu_I];
	}

	Atomizer_TCR_Pointer=Atomizer_TCR_BUFF[R_TCR_SetProject];

	cursor_key_value=0;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("TCR SET",53);
	GUI_SetColor(0x808080);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispStringHCenterAt("LONG MODE",120,253);
	Disp_EXIT_Key("OK",0);
	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(22,90,217,127,18);

	Disp_Atomizer();
	Disp_TCR_Data();
	Disp_PWR_Data();

	Disp_L_Arrow(0);
	Disp_R_Arrow(0);
	PanelTurnOnDisplay();
}
//
void	TCR_Data_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		TCR_Data_Set_windows();
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
				TCR_Data_touch();
				if(R_key_super_keep_Mode==KEY_MODE)
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
					Windows_Switch(Return_windows);
			}
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}



