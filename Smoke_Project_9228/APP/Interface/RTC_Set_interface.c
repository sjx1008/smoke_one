
#include "WM_Disp.h"

Dial_typ	R_Dial=ON_Dial;		//ʱדާĦҭƌ`э

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

static	u8	R_Cursor=0;
static	u8	B_RTC_change;

static	const	GUI_RECT RTC_Cursor_Back[8]={
[0]={72,70,167,99},
[1]={34,125,69,150},
[2]={82,125,117,150},
[3]={125,125,190,150},
[4]={20,185,51,202},
[5]={58,172,103,203},
[6]={114,172,159,203},
[7]={170,172,215,203},
};

static	u8	Watch;
static	const	char	*const	WatchName[]={
	"NUMBER",
	"POINTER",
	"OFF"
};
static	void	print_Watch(void)
{
	#define	printi	0
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1);

	if(R_Cursor==printi)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1,14);
	}

	GUI_SetFont(&GUI_FontRaavi18);
	GUI_SetColor(0xFFFFFF);
	GUI_DispStringInRect(WatchName[Watch],(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}

static	void	print_Month(void)
{
	char	s[3];
	#define	printi	1
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==printi)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1,4);
	}
	GUI_SetFont(&GUI_FontArial32);
	GUI_SetColor(0xFFFFFF);
	sprintf(s,"%02d",SET_Date.Month);  //ݫ  SET_Date.Month  Ӕ࠭׈Ϊ2քٱʽдɫ s
	s[2]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}

static	void	print_Day(void)
{
	char	s[3];
	#define	printi	2
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==printi)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1,4);
	}
	GUI_SetFont(&GUI_FontArial32);
	GUI_SetColor(0xFFFFFF);
	sprintf(s,"%02d",SET_Date.Day);
	s[2]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}

static	void	print_Year(void)
{
	char	s[5];
	#define	printi	3
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==printi)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1,4);
	}
	GUI_SetFont(&GUI_FontArial32);
	GUI_SetColor(0xFFFFFF);
	sprintf(s,"%04d",2000+SET_Date.Year);
	s[4]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}

u8	AMPM_EN;
static	void	print_AMPM(void)
{
	#define	printi	4
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==printi)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1,4);
	}
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(0xFFFFFF);
	if(AMPM_EN)
	{
		if(SET_Time.Hours<12)
			GUI_DispStringInRect("AM",(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
		else
			GUI_DispStringInRect("PM",(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	}
	else
	{
			GUI_DispStringInRect("24",(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}

static	void	print_Hours(void)
{
	u8	R;
	char	s[3];
	#define	printi	5
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==printi)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1,4);
	}
	GUI_SetFont(&GUI_FontArial41);
	GUI_SetColor(0xFFFFFF);
	if(AMPM_EN)
	{
		R=SET_Time.Hours%12;
		if(R==0)
			R=12;
	}
	else
	{
		R=SET_Time.Hours;
	}
	sprintf(s,"%02d",R);
	s[2]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}

static	void	print_Minutes(void)
{
	char	s[3];
	#define	printi	6
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==printi)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1,4);
	}
	GUI_SetFont(&GUI_FontArial41);
	GUI_SetColor(0xFFFFFF);
	sprintf(s,"%02d",SET_Time.Minutes);
	s[2]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}

static	void	print_Seconds(void)
{
	char	s[3];
	#define	printi	7
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	if(R_Cursor==printi)
	{
		GUI_AA_SetFactor(4);
		GUI_SetColor(0xB5863C);
		GUI_AA_FillRoundedRect(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1,RTC_Cursor_Back[printi].y1,4);
	}
	GUI_SetFont(&GUI_FontArial41);
	GUI_SetColor(0xFFFFFF);
	sprintf(s,"%02d",SET_Time.Seconds);
	s[2]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}

/////////////
void	(*const Prain_display[])(void)={print_Watch,print_Month,print_Day,print_Year,print_AMPM,print_Hours,print_Minutes,print_Seconds};

//
static	void	RTC_Date_limit(void)
{
	if(SET_Date.Year%4)
	{
		if(SET_Date.Day>PingnianWeek[SET_Date.Month])
		{
			SET_Date.Day=PingnianWeek[SET_Date.Month];
			print_Day();
		}
	}
	else
	{
		if(SET_Date.Day>RunnianWeek[SET_Date.Month])
		{
			SET_Date.Day=RunnianWeek[SET_Date.Month];
			print_Day();
		}
	}
}
//
static	void	watch_set(void)
{
	u8	a;
	a=KEY_R_ADD_SUB(&R_key_anxiaOpen,Watch,KEY_ADD,KEY_SUB,2,0,1,1,30);
	if(Watch!=a)
	{
		Watch=a;
		if(Watch==0)
		{
			R_Dial=ON_Dial;
			R_Watch_dial=0;
		}
		else if(Watch==1)
		{
			R_Dial=ON_Dial;
			R_Watch_dial=1;
		}
		else
		{
			R_Dial=OFF_Dial;
		}
		print_Watch();
	}
}
static	void	RTC_Set_Year(void)
{
	u8	a;
	a=KEY_R_ADD_SUB(&R_key_anxiaOpen,SET_Date.Year,KEY_ADD,KEY_SUB,99,1,1,1,30);
	if(SET_Date.Year!=a)
	{
		SET_Date.Year=a;
		print_Year();
		RTC_Date_limit();
		B_RTC_change|=1;
	}
}
static	void	RTC_Set_Month(void)
{
	u8	a;
	a=KEY_R_ADD_SUB(&R_key_anxiaOpen,SET_Date.Month,KEY_ADD,KEY_SUB,12,1,1,1,30);
	if(SET_Date.Month!=a)
	{
		SET_Date.Month=a;
		print_Month();
		RTC_Date_limit();
		B_RTC_change|=1;
	}
}
static	void	RTC_Set_Date(void)
{
	u8	a;
	u8	max;
	if(SET_Date.Year%4)
	{
		max=PingnianWeek[SET_Date.Month];
	}
	else
	{
		max=RunnianWeek[SET_Date.Month];
	}
	a=KEY_R_ADD_SUB(&R_key_anxiaOpen,SET_Date.Day,KEY_ADD,KEY_SUB,max,1,1,1,30);
	if(SET_Date.Day!=a)
	{
		SET_Date.Day=a;
		print_Day();
		B_RTC_change|=1;
	}
}
static	void	RTC_Set_Hours(void)
{
	u8	a;
	a=KEY_R_ADD_SUB(&R_key_anxiaOpen,SET_Time.Hours,KEY_ADD,KEY_SUB,23,0,1,1,30);
	if(SET_Time.Hours!=a)
	{
		if(AMPM_EN)
		{
			if(SET_Time.Hours/12!=a/12)
			{
				SET_Time.Hours=a;
				print_AMPM();
			}
		}
		SET_Time.Hours=a;
		print_Hours();
		B_RTC_change|=2;
	}
}
static	void	RTC_Set_Minutes(void)
{
	u8	a;
	a=KEY_R_ADD_SUB(&R_key_anxiaOpen,SET_Time.Minutes,KEY_ADD,KEY_SUB,59,0,1,1,30);
	if(SET_Time.Minutes!=a)
	{
		SET_Time.Minutes=a;
		print_Minutes();
		B_RTC_change|=2;
	}
}
static	void	RTC_Set_Seconds(void)
{
	u8	a;
	a=KEY_R_ADD_SUB(&R_key_anxiaOpen,SET_Time.Seconds,KEY_ADD,KEY_SUB,59,0,1,1,30);
	if(SET_Time.Seconds!=a)
	{
		SET_Time.Seconds=a;
		print_Seconds();
		B_RTC_change|=2;
	}
}

static	void	RTC_AMPM_set(void)
{
	u8	a;
	a=KEY_R_ADD_SUB(&R_key_anxiaOpen,AMPM_EN,KEY_ADD,KEY_SUB,1,0,1,1,30);
	if(AMPM_EN!=a)
	{
		AMPM_EN=a;
		B_RTC_change|=2;
		print_AMPM();
		print_Hours();
	}
}
//سҟݽͷ
static	void	Disp_L_Arrow(u8	B)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(35,71,31,28,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRect(35,71,65,98);
	if(B)
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_D_L_Arrow,35,71);
	else
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_D_NO_L_Arrow,35,71);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, 35, 71);//显示
	GUI_MEMDEV_Delete(hMem);
}
//Ԓҟݽͷ
static	void	Disp_R_Arrow(u8	B)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(175,71,31,28,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetColor(0x57534E);
	GUI_FillRect(175,71,205,98);
	if(B)
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_D_R_Arrow,175,71);
	else
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Menu2_D_NO_R_Arrow,175,71);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, 175, 71);//显示
	GUI_MEMDEV_Delete(hMem);
}

//
void	(*const _RTC_Set[])(void)={watch_set,RTC_Set_Month,RTC_Set_Date,RTC_Set_Year,RTC_AMPM_set,RTC_Set_Hours,RTC_Set_Minutes,RTC_Set_Seconds};

static	u8	cursor_key_value=0;
static	void	RTC_Set_touch(void)
{
	u8	b;
	if(R_key_anxiaOpen_Mode==KEY_MODE)
	{
		b=R_Cursor;
		R_Cursor++;
		if(R_Cursor>7)
			R_Cursor=0;
		(*Prain_display[b])();       		//Ј޸ȥһՎ ё֮ǰָ֫Ђք˽ߝטтˢʏ իһˢ֗ͼ
		(*Prain_display[R_Cursor])();		//ՙ޸ȥһՎ ёձǰָ֫Ђք˽ߝˢʏ Ңˢʏٟ
	}
	if(R_Cursor==0)
	{
		if(cursor_key_value!=key_value)  //سԒָ֫քٟܰǤȥԽ
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

	(*_RTC_Set[R_Cursor])();
	if(R_key_anxia==KEY_M)
	{
		Windows_Switch(Main_interface);
	}
}
//

static	void	RTC_Set_windows(void)
{
	if(Disp_windows_Q==System_Set_Menu_interface && B_windows_GOTO)
	{
		RTCgotoSET();
		B_RTC_change=0;
		R_Cursor=0;
	}
	if(R_Cursor>7)
		R_Cursor=0;

	if(R_Dial==ON_Dial)
	{
		if(R_Watch_dial==0)
			Watch=0;
		else
			Watch=1;
	}
	else
	{
		Watch=2;
	}
	cursor_key_value=0;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	Menu_Bottom_Windows("TIME SET",48);
	GUI_SetColor(0x808080);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispStringHCenterAt("LONG MODE",120,257);
	Disp_EXIT_Key("OK",0);
	GUI_SetColor(0x57534E);
	GUI_AA_SetFactor(3);
	GUI_AA_FillRoundedRect(22,66,217,103,18);

	GUI_SetColor(GUI_WHITE);
	GUI_FillRect(72,137,79,139);
	GUI_FillRect(107,180,110,183);
	GUI_FillRect(107,192,110,195);
	GUI_FillRect(163,180,166,183);
	GUI_FillRect(163,192,166,195);
	Disp_L_Arrow(0);
	Disp_R_Arrow(0);

	for(u8	i=0;i<8;i++)
	{
		(*Prain_display[i])();
	}
	PanelTurnOnDisplay();
}
//
void	RTC_Set_interface(void)
{
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(1);
		RTC_Set_windows();
		B_Key_release=1;
		B_Set_OK=0;
		R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_access:{//usbӥɫ
			Windows_Interrupt_Push(Battery_charging_interface);
		};break;
		case	USB_anomaly:{//USBӬӣ
			Windows_Interrupt_Push(USB_Warning_interface);
		};break;
		default:{
			if(!B_Set_OK)
			{
				RTC_Set_touch();
				if(R_key_super_keep_Mode==KEY_MODE)
				{
					u8	a;
					a=R_Cursor;
					R_Cursor=0xf0;
					(*Prain_display[a])();
					if(B_RTC_change)
					{
						B_Force_Power_down_save=1;
					}
					if(B_RTC_change==1)
						Set_RTC_DateTime(&SET_Date,&RTC_Time);			//ֻلҤɕǚ ޸֢oټтRTC
					else if(B_RTC_change==2)
						Set_RTC_DateTime(&RTC_Date,&SET_Time);			//ֻلҤʱݤ ޸֢oټтRTC
					else if(B_RTC_change==3)
						Set_RTC_DateTime(&SET_Date,&SET_Time);			//ɕǚʱݤּلҤ
					RTCgotoSET();	//ܘׁTCR ҜĢTCRдքʱ۲Զխ
					B_RTC_change=0;
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
		};
	}
	R_Skinning_mode=Skinning_mode_null;
}








