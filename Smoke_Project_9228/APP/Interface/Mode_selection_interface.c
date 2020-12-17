#include "WM_Disp.h"
//菜单列表显示区域
static	const	GUI_RECT NameRECTE[Disp_menu_struct_MAX]={
[0]={.x0=32,.y0=78,.x1=208,.y1=101},
[1]={.x0=32,.y0=103,.x1=208,.y1=139},
[2]={.x0=32,.y0=140,.x1=208,.y1=166},
[3]={.x0=32,.y0=167,.x1=208,.y1=188},
[4]={.x0=51,.y0=192,.x1=189,.y1=210},
};
static	const	GUI_RECT NameRECTZ[Disp_menu_struct_MAX]={
[0]={.x0=77,.y0=76,.x1=163,.y1=98},
[1]={.x0=59,.y0=105,.x1=179,.y1=135},
[2]={.x0=70,.y0=140,.x1=170,.y1=164},
[3]={.x0=75,.y0=167,.x1=166,.y1=188},
[4]={.x0=77,.y0=191,.x1=164,.y1=208},
};
//字体颜色
static	uc32	FONTColour[]={0x00A8A8A8,0x00FFFFFF,0x00C3C3C3C3,0x00A8A8A8,0x007D7D7D};
static	GUI_CONST_STORAGE GUI_FONT *const	menuFONTE[]={&FontGill22,&FontGill37,&FontGill27,&FontGill22,&FontGill18};
static	GUI_CONST_STORAGE GUI_FONT *const	menuFONTZ[]={&FontYaHei24,&FontYaHei31,&FontYaHei28,&FontYaHei24,&FontYaHei22};
Disp_menu_struct	R_Disp_menu_struct;

/////

void	menu2_struct_Init(char	*menuName,char	**P_Name,u8	Max,u8	*Cursor,u8	yuyan)
{
	u8	i;
	R_Disp_menu_struct.menuName=menuName;
	R_Disp_menu_struct.P_Name=P_Name;
	R_Disp_menu_struct.Max=Max;
	R_Disp_menu_struct.Cursor=Cursor;
	if(yuyan==English){
		R_Disp_menu_struct.menuFONT=menuFONTE;
		R_Disp_menu_struct.NameRECT=NameRECTE;}
	else{
		R_Disp_menu_struct.menuFONT=menuFONTZ;
		R_Disp_menu_struct.NameRECT=NameRECTZ;}
	for(i=0;i<Disp_menu_struct_MAX;i++)
		R_Disp_menu_struct.Sign[i]=0;
	if(R_Disp_menu_struct.Max==1)
	{
		R_Disp_menu_struct.Sign[1]=1;
	}
	else if(R_Disp_menu_struct.Max==2)
	{
		R_Disp_menu_struct.Sign[1]=1;
		R_Disp_menu_struct.Sign[2]=1;
	}
	else
	{
		for(i=0;i<Disp_menu_struct_MAX && i<R_Disp_menu_struct.Max;i++)
			R_Disp_menu_struct.Sign[i]=1;
	}
}

void	menu2_display_windows(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	draw_Bmp_ex(d_bottom_level_menu_interface,0,0);
	GUI_SetColor(GUI_WHITE);
	if(R_Language==English)
	{
		GUI_SetFont(&FontGill37);
		GUI_DispStringHCenterAt(R_Disp_menu_struct.menuName,120,19);
	}
	else
	{
		GUI_SetFont(&FontYaHei31);
		GUI_DispStringHCenterAt(R_Disp_menu_struct.menuName,120,26);
	}
	GUI_AA_SetFactor(3);
	GUI_AA_FillCircle(26,120,4);
	GUI_AA_FillCircle(215,120,4);
	Disp_menu2_Name();
	PanelTurnOnDisplay();
}

void	Disp_menu2_Name(void)
{
	GUI_MEMDEV_Handle hMem;
	u8	i;
	s8	a;
	s8	P;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	a=-2;
	for(i=0;i<Disp_menu_struct_MAX;i++)
	{
		a++;
		if(!R_Disp_menu_struct.Sign[i])
			continue;
		P=a+(s8)*R_Disp_menu_struct.Cursor;
		if(P<0)
			P+=R_Disp_menu_struct.Max;
		else if(P>=R_Disp_menu_struct.Max)
			P%=R_Disp_menu_struct.Max;
		hMem = GUI_MEMDEV_Create(R_Disp_menu_struct.NameRECT[i].x0,R_Disp_menu_struct.NameRECT[i].y0,R_Disp_menu_struct.NameRECT[i].x1-R_Disp_menu_struct.NameRECT[i].x0+1, R_Disp_menu_struct.NameRECT[i].y1-R_Disp_menu_struct.NameRECT[i].y0+1);
		GUI_MEMDEV_Select(hMem);
		GUI_SetColor(GUI_BLACK);
		GUI_FillRect(R_Disp_menu_struct.NameRECT[i].x0,R_Disp_menu_struct.NameRECT[i].y0,R_Disp_menu_struct.NameRECT[i].x1,R_Disp_menu_struct.NameRECT[i].y1);
		GUI_SetColor(FONTColour[i]);
		GUI_SetFont(R_Disp_menu_struct.menuFONT[i]);
		GUI_DispStringInRect(R_Disp_menu_struct.P_Name[P],(GUI_RECT*)&R_Disp_menu_struct.NameRECT[i],GUI_TA_VCENTER|GUI_TA_HCENTER);
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_WriteAt(hMem,R_Disp_menu_struct.NameRECT[i].x0,R_Disp_menu_struct.NameRECT[i].y0);//显示
		GUI_MEMDEV_Delete(hMem);
	}
}



#define	d_Menu_SUM	5

static	u8	Cursor=0;

static	const char MenuNameE[]="Modes";
static	const char MenuNameZ[]="模式";
static	const	char	*const	Menu_NAME_BUFFE[]={
	"WATT",
	"VOLTAGE",
	"BYPASS",
	"TC/TCR",
	"CPS",
};
static	const	char	*const	Menu_NAME_BUFFZ[]={
	"功率模式",
	"电压模式",
	"直接输出",
	"温控模式",
	"曲线模式",
};

static	void (*const menu_Set_goto[])(void)={
Main_interface,Main_interface,Main_interface,
TEMPE_Mode_selection_interface,Custom_Mode_selection_interface};
//
void	Mode_selection_Windows(void)
{
	if(Disp_windows_Q==Main_menu_interface)
	{
		if(R_Work_mode==d_Voltage_mode)
			Cursor=1;
		else if(R_Work_mode==d_Bypass_mode)
			Cursor=2;
		else if(R_Work_mode==d_Temp_mode || R_Work_mode==d_TCR_mode)
			Cursor=3;
		else if(R_Work_mode==d_Custom_mode)
			Cursor=4;
		else
			Cursor=0;
	}

	if(R_Language==English)
		menu2_struct_Init((char*)MenuNameE,(char	**)Menu_NAME_BUFFE,d_Menu_SUM,&Cursor,English);
	else
		menu2_struct_Init((char*)MenuNameZ,(char	**)Menu_NAME_BUFFZ,d_Menu_SUM,&Cursor,Chinese);
	menu2_display_windows();
}
static	void	Mode_selection_operation(void)
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
		if(Cursor==0)
		{
			R_Work_mode=d_Watt_mode;
		}
		else if(Cursor==1)
		{
			R_Work_mode=d_Voltage_mode;
		}
		else if(Cursor==2)
		{
			R_Work_mode=d_Bypass_mode;
		}
	}
	Return_interface_GOTO(Main_menu_interface);
}
//
void	Mode_selection_interface(void)
{
	Key_Light_screen();
	switch((u8)R_Skinning_mode)
	{
		case	Skinning_init:{//Եʼۯ
			Mode_selection_Windows();
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
			Mode_selection_operation();
			Atomizer_inquiry_GOTO(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}


//温控模式选择
//
static	u8	Cursor_Temp=0;
static	void	TEMPE_Mode_selection_Windows(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	draw_Bmp_ex(d_bottom_level_menu_interface,0,0);
	GUI_SetColor(GUI_WHITE);
	if(R_Language==English)
	{
		GUI_SetFont(&FontGill37);
		GUI_DispStringHCenterAt(MenuNameE,120,19);
	}
	else
	{
		GUI_SetFont(&FontYaHei31);
		GUI_DispStringHCenterAt(MenuNameZ,120,26);
	}
	draw_Bmp_ex(d_NiTiSs_NoSelected,33,84);
	Reverse_display_TEMPE_Name(Cursor_Temp,1);
	PanelTurnOnDisplay();
}
//
void	Reverse_display_TEMPE_Name(u8	i,u8	B)
{
	GUI_RECT	RECT;
	RECT.x0=1+60*(i%3);
	RECT.y0=1+54*(i/3);
	RECT.x1=RECT.x0+51;
	RECT.y1=RECT.y0+51;
	if(B)
		Map_draw_bmpToBitmap_ex(d_NiTiSs_Selected,&RECT,RECT.x0+33,RECT.y0+84);
	else
		Map_draw_bmpToBitmap_ex(d_NiTiSs_NoSelected,&RECT,RECT.x0+33,RECT.y0+84);
}
static	void	TEMPE_Mode_selection_operation(void)
{
	u8	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Cursor_Temp,KEY_ADD,KEY_SUB,5,0,1,1,100);
	if(R!=Cursor_Temp)
	{
		Reverse_display_TEMPE_Name(Cursor_Temp,0);
		Cursor_Temp=R;
		Reverse_display_TEMPE_Name(Cursor_Temp,1);
	}

	if(R_key_anxiaOpen==KEY_M)
	{
		if(Cursor_Temp<3)
		{
			R_Work_mode=d_Temp_mode;
			R_Atomizer=(Atomizer)Cursor_Temp;
		}
		else
		{
			R_Work_mode=d_TCR_mode;
			R_TCR_term=(TCR_term)(Cursor_Temp-3);
		}
		if(Atomizer_inquiry_GOTO(0))
			Disp_windows_QQ=Main_interface;
		else
			Windows_Switch(Main_interface);//Ȑۻս׷ާĦ
	}
	Return_interface_GOTO(Mode_selection_interface);
}
//
void	TEMPE_Mode_selection_interface(void)
{
	Key_Light_screen();
	switch((u8)R_Skinning_mode)
	{
		case	Skinning_init:{//Եʼۯ
			TEMPE_Mode_selection_Windows();
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
			Atomizer_inquiry_GOTO(1);
			TEMPE_Mode_selection_operation();
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}

	R_Skinning_mode=Skinning_mode_null;
}

//曲线模式选择
//
static	u8	Cursor_Custom=0;
static	void	Custom_Mode_selection_Windows(void)
{
	u8	i;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	draw_Bmp_ex(d_bottom_level_menu_interface,0,0);
	GUI_SetColor(GUI_WHITE);
	if(R_Language==English)
	{
		GUI_SetFont(&FontGill37);
		GUI_DispStringHCenterAt(MenuNameE,120,19);
	}
	else
	{
		GUI_SetFont(&FontYaHei31);
		GUI_DispStringHCenterAt(MenuNameZ,120,26);
	}
	GUI_SetFont(&FontGill27);
	GUI_DispStringHCenterAt("C1",52,160);
	GUI_DispStringHCenterAt("C2",119,160);
	GUI_DispStringHCenterAt("C3",185,160);
	for(i=0;i<3;i++)
	{
		if(i==Cursor_Custom)
			Reverse_display_Custom_Name(i,1);
		else
			Reverse_display_Custom_Name(i,0);
	}
	PanelTurnOnDisplay();
}
//
void	Reverse_display_Custom_Name(u8	i,u8	B)
{
	u32	Color,BkColor;
	u8	y1;
	u8	j;
	GUI_MEMDEV_Handle hMem;
	if(B){
		BkColor=GUI_WHITE;
		Color=GUI_DARKGRAY;}
	else{
		BkColor=GUI_DARKGRAY;
		Color=GUI_WHITE;}
	hMem = GUI_MEMDEV_Create(0, 0, 66, 66);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,65,65);
	GUI_AA_SetFactor(3);
	GUI_SetColor(BkColor);
	if(B)
	{
		GUI_AA_FillCircle(33,33,31);
		GUI_SetColor(Color);
	}
	else
	{
		GUI_FillCircle(33,33,30);
		GUI_SetColor(Color);
		GUI_SetPenSize(2);
		GUI_AA_DrawArc(33,33,30,30,0,360);
	}
	for(j=0;j<=d_Custom_I_MAX;j++)
	{
		y1=45-27*(R_Custom_BUFF.Custom_array.CustomCCW_Data[j]-d_User_Watt_min/10)/(d_User_Watt_max/10-d_User_Watt_min/10);
		GUI_FillRect(13+j*2,y1,14+j*2,45);
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, 20+67*i, 87);//显示
	GUI_MEMDEV_Delete(hMem);
}
static	void	Custom_Mode_selection_operation(void)
{
	u8	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Cursor_Custom,KEY_ADD,KEY_SUB,2,0,1,1,200);
	if(R!=Cursor_Custom)
	{
		Reverse_display_Custom_Name(Cursor_Custom,0);
		Cursor_Custom=R;
		Reverse_display_Custom_Name(Cursor_Custom,1);
	}

	if(R_key_anxiaOpen==KEY_M)
	{

		R_Work_mode=d_Custom_mode;
		R_Custom=(Custom_typ)Cursor_Custom;
		Windows_Switch(Main_interface);
	}
	Return_interface_GOTO(Mode_selection_interface);
}
//
void	Custom_Mode_selection_interface(void)
{
	Key_Light_screen();
	switch((u8)R_Skinning_mode)
	{
		case	Skinning_init:{//Եʼۯ
			Custom_Mode_selection_Windows();
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
			Atomizer_inquiry_GOTO(1);
			Custom_Mode_selection_operation();
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}

	R_Skinning_mode=Skinning_mode_null;
}

