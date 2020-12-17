
#include "WM_Disp.h"

/////////////////////////////////////////////////////
///////////自定义曲线参数设置/////////////////////////////////
void (*Custom_Data_Return)(void);
u8	R_Custom_SetProject;	//需要设置的项
static	u16	*Set_Custom_Pointer;
static	u8	R_Custom_Set_Tim;


//设置自定义曲线
static	u8	Custom_Data_Y[d_Custom_I_MAX+1];
/////////////////////////////////////////

//左箭头
static	void	Disp_L_Arrow(u8	B)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(54,236,25,21,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRect(54,236,78,256);
	if(B)
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_X_L_Arrow,54,236);
	else
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_X_NO_L_Arrow,54,236);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,54,236);//显示
	GUI_MEMDEV_Delete(hMem);
}
//右箭头
static	void	Disp_R_Arrow(u8	B)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(162,236,25,21,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRect(162,236,186,256);
	if(B)
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_X_R_Arrow,162,236);
	else
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_X_NO_R_Arrow,162,236);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,162,236);//显示
	GUI_MEMDEV_Delete(hMem);
}



//计算顶部坐标位置
static	u8	GET_CustomWatt_Data_Y(u8	I)
{
	s8	a;
	a=(Set_Custom_Pointer[I]-d_User_Watt_min/10)*10/(d_User_Watt_max/10-d_User_Watt_min/10)+1;
	if(a<1)
		a=1;
	else if(a>10)
		a=10;
	return a;
}

static	void	Custom_curve_i_j_update(u8	i,u8	j,u8	B)
{
	u8	k;
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	GUI_RECT	RECT2;
	RECT.x0=41+16*i;
	RECT.y0=89;
	RECT.x1=51+16*j;
	RECT.y1=186;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	RECT2.x0=RECT.x0;
	RECT2.x1=RECT.x0+10;
	for(;i<=j;i++)
	{
		if(i==B)
			GUI_SetColor(GUI_WHITE);
		else
			GUI_SetColor(0xFFEF00);
		for(k=0;k<Custom_Data_Y[i];k++)
		{
			GUI_FillRect(RECT2.x0,179-k*10,RECT2.x1,186-k*10);
		}
		RECT2.x0+=16;
		RECT2.x1+=16;
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,RECT.x0,RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}

//
static	void	Custom_Tim_update(u8	R)
{
	GUI_RECT	RECT;
	GUI_MEMDEV_Handle hMem;
	R=R*5+5;
	RECT.x0=106;
	RECT.y0=201;
	RECT.x1=134;
	RECT.y1=216;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	GUI_GotoXY(107,198);//
	GUI_DispDecShift(R,3,1);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}
//
void	Custom_Data_update(u16	R)
{
	GUI_RECT	RECT;
	char	str[5];
	GUI_MEMDEV_Handle hMem;
	RECT.x0=102;
	RECT.y0=65;
	RECT.x1=136;
	RECT.y1=80;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	sprintf(str,"%d",R);
	str[4]=0;
	GUI_DispStringInRect(str,&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}

//
static	u8	cursor_key_value=0;
static	void	Custom_Set_Tim_Operation(void(*P)(u16))
{
	u16	R;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_Custom_Set_Tim,KEY_M,KEY_NOP,d_Custom_I_MAX,0,1,1,100);
	if(R!=R_Custom_Set_Tim)
	{
		Custom_Tim_update(R);
		Custom_curve_i_j_update(R_Custom_Set_Tim,R_Custom_Set_Tim,R);
		Custom_curve_i_j_update(R,R,R);
		(*P)(Set_Custom_Pointer[R]);
		R_Custom_Set_Tim=R;
	}
	if(cursor_key_value!=key_value)
	{
		if(key_value==KEY_M)
			Disp_R_Arrow(1);
		else
			Disp_R_Arrow(0);
		cursor_key_value=key_value;
	}
}
static	void	CCW_SET_Operation(void)
{
	u16	R;
	Custom_Set_Tim_Operation(Custom_Data_update);
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Set_Custom_Pointer[R_Custom_Set_Tim],KEY_ADD,KEY_SUB,d_User_Watt_max/10,d_User_Watt_min/10,1,0,20);
	if(R!=Set_Custom_Pointer[R_Custom_Set_Tim])
	{
		Set_Custom_Pointer[R_Custom_Set_Tim]=R;
		Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
		R=Custom_Data_Y[R_Custom_Set_Tim];
		Custom_Data_Y[R_Custom_Set_Tim]=GET_CustomWatt_Data_Y(R_Custom_Set_Tim);
		if(R!=Custom_Data_Y[R_Custom_Set_Tim])
			Custom_curve_i_j_update(R_Custom_Set_Tim,R_Custom_Set_Tim,R_Custom_Set_Tim);
	}
	if(B_Display_refresh)
	{
		B_Display_refresh=0;
		for(u8	i=0;i<=d_Custom_I_MAX;i++)
			Custom_Data_Y[i]=GET_CustomWatt_Data_Y(i);
		Custom_curve_i_j_update(0,d_Custom_I_MAX,R_Custom_Set_Tim);
		Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
	}
	if(!R_Bright_screen_Time)
		B_Custom_Hold=1;
}
//


static	void	Print_Button(const char * s, GUI_RECT * pRect, int	r,	GUI_COLOR	COLOR,	GUI_COLOR	FontCOLOR)
{
	GUI_RECT	RECT;
	RECT.x0=pRect->x0+1;
	RECT.y0=pRect->y0;
	RECT.x1=pRect->x1;
	RECT.y1=pRect->y1;
	GUI_SetColor(COLOR);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(pRect->x0,pRect->y0,pRect->x1,pRect->y1,r);
	GUI_SetColor(FontCOLOR);
	GUI_SetFont(&GUI_FontRaavi22);
	GUI_DispStringInRect(s,&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
}

void	Print_Button_Disp(const char * s,GUI_RECT * pRect,GUI_COLOR	COLOR,	GUI_COLOR	FontCOLOR)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_Create(pRect->x0,pRect->y0,pRect->x1-pRect->x0+1,pRect->y1-pRect->y0+1);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRoundedRect(pRect->x0-2,pRect->y0-2,pRect->x1+2,pRect->y1+2,(pRect->y1-pRect->y0+5)/2);
	Print_Button(s,pRect,(pRect->y1-pRect->y0+1)/2,COLOR,FontCOLOR);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,pRect->x0,pRect->y0);//显示
	GUI_MEMDEV_Delete(hMem);
}

static	void	Custom_windows(char	*s,u8	L)
{
	Menu_Bottom_Windows(s,L);
	Disp_EXIT_Key("OK",0);
	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(45,232,195,260,14);
	GUI_SetColor(0xB5863C);
	GUI_AA_FillRoundedRect(91,234,149,258,12);
	GUI_RECT	RECT={91,234,149,258};
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontRaavi18);
	GUI_DispStringInRect("FIRE",&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
	Disp_L_Arrow(0);
	Disp_R_Arrow(0);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispCharAt('S',217,183);
	GUI_AA_SetFactor(3);
	GUI_SetColor(0x363116);
	GUI_POINT	Minutes_pin1[]={0,9,6,9,3,0};
	GUI_AA_FillPolygon(Minutes_pin1,3,27,80);
	Minutes_pin1[0].x=0;
	Minutes_pin1[0].y=0;
	Minutes_pin1[1].x=0;
	Minutes_pin1[1].y=6;
	Minutes_pin1[2].x=9;
	Minutes_pin1[2].y=3;
	GUI_AA_FillPolygon(Minutes_pin1,3,203,192);
	u8	i;
	for(i=0;i<14;i++)
	{
		GUI_DrawVLine(30,89+i*8,91+i*8);
	}
	for(i=0;i<21;i++)
	{
		GUI_DrawHLine(195,36+i*8,38+i*8);
	}
	Custom_curve_i_j_update(0,d_Custom_I_MAX,R_Custom_Set_Tim);
}
static	void	Custom_Data_Set_windows(void)
{
	u8	i;
	Set_Custom_Pointer=R_Custom_BUFF.Custom_array.CustomCCW_Data;
	for(i=0;i<=d_Custom_I_MAX;i++)
		Custom_Data_Y[i]=GET_CustomWatt_Data_Y(i);
	cursor_key_value=0;
	if(R_Custom_Set_Tim>d_Custom_I_MAX)
		R_Custom_Set_Tim=0;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Custom_windows("CCW SET",54);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispCharAt('W',21,58);
	Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
	Custom_Tim_update(R_Custom_Set_Tim);
	PanelTurnOnDisplay();
}
//CCW
u8	B_Set_OK;
void	Custom_Data_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		Custom_Data_Set_windows();
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
				CCW_SET_Operation();
				if(R_key_anxia_Mode==KEY_MODE)
				{
					B_Set_OK=1;
					B_Custom_Hold=1;
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
					Windows_Switch(Main_interface);
			}
			Batt_error_GOTO();
		}
	}
	if(Disp_windows_Set!=Disp_windows)
		B_Custom_Hold=1;
	R_Skinning_mode=Skinning_mode_null;
}


/****************************************************************************************/
//电压曲线调节
/*********************************/

static	u8	GET_CustomCCV_Data_Y(u8 I)
{
	s8	a;
	a=(Set_Custom_Pointer[I]-d_User_Vout_min)*10/(d_User_Vout_max-d_User_Vout_min)+1;
	if(a<1)
		a=1;
	else if(a>10)
		a=10;
	return a;
}
//
void	CCV_Custom_Data_update(u16	R)
{
	GUI_RECT	RECT;
	char	str[5];
	GUI_MEMDEV_Handle hMem;
	RECT.x0=100;
	RECT.y0=65;
	RECT.x1=138;
	RECT.y1=80;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	sprintf(str,"%d.%02d",R/100,R%100);
	str[4]=0;
	GUI_DispStringInRect(str,&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}
static	void	CCV_SET_Operation(void)
{
	u8	bujin;
	u16	R;
	Custom_Set_Tim_Operation(CCV_Custom_Data_update);
	if(Set_Custom_Pointer[R_Custom_Set_Tim]%10==0 && (R_key_anzhu==KEY_ADD || R_key_anzhu==KEY_SUB))
		bujin=10;
	else
		bujin=1;
	R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Set_Custom_Pointer[R_Custom_Set_Tim],KEY_ADD,KEY_SUB,d_User_Vout_max,d_User_Vout_min,bujin,0,20);
	if(R!=Set_Custom_Pointer[R_Custom_Set_Tim])
	{
		Set_Custom_Pointer[R_Custom_Set_Tim]=R;
		CCV_Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
		R=Custom_Data_Y[R_Custom_Set_Tim];
		Custom_Data_Y[R_Custom_Set_Tim]=GET_CustomCCV_Data_Y(R_Custom_Set_Tim);
		if(R!=Custom_Data_Y[R_Custom_Set_Tim])
			Custom_curve_i_j_update(R_Custom_Set_Tim,R_Custom_Set_Tim,R_Custom_Set_Tim);
	}
	if(B_Display_refresh)
	{
		B_Display_refresh=0;
		for(u8	i=0;i<=d_Custom_I_MAX;i++)
			Custom_Data_Y[i]=GET_CustomCCV_Data_Y(i);
		Custom_curve_i_j_update(0,d_Custom_I_MAX,R_Custom_Set_Tim);
		CCV_Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
	}
	if(!R_Bright_screen_Time)
		B_Custom_Hold=1;
}
static	void	CCV_Custom_Data_Set_windows(void)
{
	u8	i;
	Set_Custom_Pointer=R_Custom_BUFF.Custom_array.CustomCCV_Data;
	for(i=0;i<=d_Custom_I_MAX;i++)
		Custom_Data_Y[i]=GET_CustomCCV_Data_Y(i);
	cursor_key_value=0;
	if(R_Custom_Set_Tim>d_Custom_I_MAX)
		R_Custom_Set_Tim=0;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Custom_windows("CCV SET",54);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispCharAt('V',23,58);
	CCV_Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
	Custom_Tim_update(R_Custom_Set_Tim);
	PanelTurnOnDisplay();
}

//CCV
void	CCV_Custom_Data_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		CCV_Custom_Data_Set_windows();
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
				CCV_SET_Operation();
				if(R_key_anxia_Mode==KEY_MODE)
				{
					B_Set_OK=1;
					B_Custom_Hold=1;
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
					Windows_Switch(Main_interface);
			}
			Batt_error_GOTO();
		}
	}
	if(Disp_windows_Set!=Disp_windows)
		B_Custom_Hold=1;
	R_Skinning_mode=Skinning_mode_null;
}

/****************************************************************************************/
//温控曲线调节
/*********************************/
u16	*const CCT_C_BUFF[]={R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data,
												 R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data,
												 R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data};
u16	*const CCT_F_BUFF[]={R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data,
												 R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data,
												 R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data};

static	u8	GET_CustomCCT_Data_Y(u8 I)
{
	s8	a;
	if(R_Temp_metric==F_metric)
		a=(Set_Custom_Pointer[I]-d_User_TempF_min)*10/(d_User_TempF_max-d_User_TempF_min)+1;
	else
		a=(Set_Custom_Pointer[I]-d_User_TempC_min)*10/(d_User_TempC_max-d_User_TempC_min)+1;
	if(a<1)
		a=1;
	else if(a>10)
		a=10;
	return a;
}
//

static	void	CCT_SET_Operation(void)
{
	u16	R;
	Custom_Set_Tim_Operation(Custom_Data_update);

	if(R_Temp_metric==F_metric)
		R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Set_Custom_Pointer[R_Custom_Set_Tim],KEY_ADD,KEY_SUB,d_User_TempF_max,d_User_TempF_min,10,1,50);
	else
		R=KEY_R_ADD_SUB(&R_key_anxiaOpen,Set_Custom_Pointer[R_Custom_Set_Tim],KEY_ADD,KEY_SUB,d_User_TempC_max,d_User_TempC_min,5,1,50);

	if(R!=Set_Custom_Pointer[R_Custom_Set_Tim])
	{
		Set_Custom_Pointer[R_Custom_Set_Tim]=R;
		Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
		R=Custom_Data_Y[R_Custom_Set_Tim];
		Custom_Data_Y[R_Custom_Set_Tim]=GET_CustomCCT_Data_Y(R_Custom_Set_Tim);
		if(R!=Custom_Data_Y[R_Custom_Set_Tim])
			Custom_curve_i_j_update(R_Custom_Set_Tim,R_Custom_Set_Tim,R_Custom_Set_Tim);

		if(R_Temp_metric==F_metric)
		{
			for(R=0;R<=d_Custom_I_MAX;R++)
			{
				CCT_C_BUFF[R_Atomizer][R]=(CCT_F_BUFF[R_Atomizer][R]-32)*5/9;
				CCT_C_BUFF[R_Atomizer][R]/=5;
				CCT_C_BUFF[R_Atomizer][R]*=5;
				if(CCT_C_BUFF[R_Atomizer][R]>d_User_TempC_max)
					CCT_C_BUFF[R_Atomizer][R]=d_User_TempC_max;
				else	if(CCT_C_BUFF[R_Atomizer][R]<d_User_TempC_min)
					CCT_C_BUFF[R_Atomizer][R]=d_User_TempC_min;
			}
		}
		else
		{
			for(R=0;R<=d_Custom_I_MAX;R++)
			{
				CCT_F_BUFF[R_Atomizer][R]=CCT_C_BUFF[R_Atomizer][R]*9/5+32;
				CCT_F_BUFF[R_Atomizer][R]/=5;
				CCT_F_BUFF[R_Atomizer][R]*=5;
				if(CCT_F_BUFF[R_Atomizer][R]>d_User_TempF_max)
					CCT_F_BUFF[R_Atomizer][R]=d_User_TempF_max;
				else	if(CCT_F_BUFF[R_Atomizer][R]<d_User_TempF_min)
					CCT_F_BUFF[R_Atomizer][R]=d_User_TempF_min;
			}
		}
	}
	if(B_Display_refresh)
	{
		B_Display_refresh=0;
		for(u8	i=0;i<=d_Custom_I_MAX;i++)
			Custom_Data_Y[i]=GET_CustomCCT_Data_Y(i);
		Custom_curve_i_j_update(0,d_Custom_I_MAX,R_Custom_Set_Tim);
		Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
	}
	if(!R_Bright_screen_Time)
		B_Custom_Hold=1;
}
static	const char	*const	CCT_Menu_Name_BUFFE[]={
	"CCT-NI SET",
	"CCT-TI SET",
	"CCT-SS SET",
};
static	void	CCT_Custom_Data_Set_windows(void)
{
	u8	i;
	if(CC_Menu_I<2)
		CC_Menu_I=2;
	if(R_Temp_metric==F_metric)
		Set_Custom_Pointer=CCT_F_BUFF[CC_Menu_I-2];
	else
		Set_Custom_Pointer=CCT_C_BUFF[CC_Menu_I-2];
	for(i=0;i<=d_Custom_I_MAX;i++)
		Custom_Data_Y[i]=GET_CustomCCT_Data_Y(i);

	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	if(R_Custom_Set_Tim>d_Custom_I_MAX)
		R_Custom_Set_Tim=0;

	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Custom_windows((char *)CCT_Menu_Name_BUFFE[CC_Menu_I-2],35);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	if(R_Temp_metric==F_metric)
	{
		GUI_DispCharAt('F',27,58);
	}
	else
	{
		GUI_DispCharAt('C',27,58);
	}
	GUI_SetPenSize(1);
	GUI_AA_SetFactor(3);
	GUI_AA_DrawArc(24,64,2,2,0,360);
	Custom_Data_update(Set_Custom_Pointer[R_Custom_Set_Tim]);
	Custom_Tim_update(R_Custom_Set_Tim);
	PanelTurnOnDisplay();
}

//CCT
void	CCT_Custom_Data_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		CCT_Custom_Data_Set_windows();
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
				CCT_SET_Operation();
				if(R_key_anxia_Mode==KEY_MODE)
				{
					B_Set_OK=1;
					B_Custom_Hold=1;
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
					Windows_Switch(Main_interface);
			}
			Batt_error_GOTO();
		}
	}
	if(Disp_windows_Set!=Disp_windows)
		B_Custom_Hold=1;
	R_Skinning_mode=Skinning_mode_null;
}


