
#include	"WM_Disp.h"
#include	"stdio.h"
#include	<math.h>
#ifndef PI
#define PI                 3.14159265358979f
#endif

static	void Screensaver_Windows_1(void);
static	void Screensaver_Windows_2(void);

u8	R_Watch_dial;  //0 数字  1 表盘
static	void 	(*Watch_dial_Init[2])(void)={Screensaver_Windows_1,Screensaver_Windows_2};

static	void	(*Screensaver_Dispaly)(void);


u16	R_Screen_Tim=180;		//屏保时间

static	LL_RTC_TimeTypeDef	Disp_Time;
static	LL_RTC_DateTypeDef	Disp_Date;

static	GUI_AUTODEV	AutoDev_1,AutoDev_2,AutoDev_3,AutoDev_4;

////////////////////////////////////////////////
static	void	Calculation_position(u16	X0,u16	Y0,s16 *X,s16 *Y,u16	R,double	A)
{
	*X=X0+R*arm_sin_f32(PI*A/180);
	*Y=Y0-R*arm_cos_f32(PI*A/180);
//  *X=X0+R*sin(PI*A/180);
//	*Y=Y0-R*cos(PI*A/180);
}



static	void	Screensaver_Windows(void)
{
	Disp_Date=RTC_Date;
	Disp_Time=RTC_Time;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
 	if(R_Watch_dial>1)
		R_Watch_dial=0;
	(*Watch_dial_Init[R_Watch_dial])();
	PanelTurnOnDisplay();
}

u16	R_Bright_screen_Time_Q;
u8	B_Atomizer_Screensaver;
void	Screensaver_interface(void)
{
	if(R_key_anxia & KEY_M || B_Out_Yes)
	{
		Fanhui_Main_interface();
		(*Disp_Sleep)();
		return;
	}
	Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(!B_ADDSUB_LOCK);
		R_Bright_screen_TimeMAX=R_Screen_Tim*10;
		if(B_Atomizer_Screensaver && Disp_windows_Q==Atomizer_inquiry_interface  && B_windows_GOTO)
		{
			if(R_Bright_screen_Time_Q>R_Bright_screen_TimeMAX)
				R_Bright_screen_Time_Q=R_Bright_screen_TimeMAX;
			else if(R_Bright_screen_Time_Q<30)
				R_Bright_screen_Time_Q=30;
			R_Bright_screen_Time=R_Bright_screen_Time_Q;
		}
		else
		{
			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		}
		B_Atomizer_Screensaver=0;
		Screensaver_Windows();
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_access:{//usb插入
			Windows_Switch(Battery_charging_interface);
		};break;
		case	USB_anomaly:{//USB异常
			Windows_Switch(USB_Warning_interface);
		};break;
		case	Short_circuit:{//短路
			Windows_Switch(Warning_interface);
			Warning_Windows=Short_circuit_windows;
		};break;
		case	Open_circuit:{//开路
			Windows_Switch(Warning_interface);
			Warning_Windows=Open_circuit_windows;
		};break;
		case	Low_Resistance:{//低阻值
			Windows_Switch(Warning_interface);
			Warning_Windows=Low_ATOMIZER_windows;
		};break;
		case	High_Resistance:{//高阻值
			Windows_Switch(Warning_interface);
			Warning_Windows=HIGH_ATOMIZER_windows;
		};break;
		case	Low_Battery:{//低电量
			Windows_Switch(Warning_interface);
			Warning_Windows=Low_Battery_windows;
		};break;
		case	Smoking_timeout:{//吸烟超时
			Windows_Switch(Warning_interface);
			Warning_Windows=Smoking_timeout_windows;
		};break;
		case	PCB_Overheated:{//PCB过热
			Windows_Switch(Warning_interface);
			Warning_Windows=PCB_Overheated_windows;
		};break;
		default:{
			if(R_BATT_Actual<d_Bat_Volt_min)
			{
				if(R_Bright_screen_TimeMAX-R_Bright_screen_Time>=200)
				{
					R_Bright_screen_TimeMAX=200;
					R_Bright_screen_Time=0;
				}
			}
			if(!R_Bright_screen_Time)
			{
				if(B_BAT_Charge)
				{
					Windows_Switch(Battery_charging_interface);
				}
			}

			if(R_key_anxia || B_Out_Yes)
			{
				Fanhui_Main_interface();
			}

			if(!B_Atomizer_inquiry)
			{
				B_GOTO_Atomizer_inquiry=0;
			}
			if(!B_GOTO_Atomizer_inquiry)
			{
				if(Atomizer_inquiry_GOTO(0))
				{
					B_Atomizer_Screensaver=1;
					R_Bright_screen_Time_Q=R_Bright_screen_Time;
				}
			}
			Batt_error_GOTO();
		};
	}
	(*Screensaver_Dispaly)();

	R_Skinning_mode=Skinning_mode_null;
}


//表盘1
static	const	GUI_RECT RTC_Cursor_Back[8]={
[0]={105,274,148,289},
[1]={45,274,66,289},
[2]={75,274,96,289},
[3]={157,274,202,289},

[4]={106,43,133,58},
[5]={72,66,165,153},
[6]={72,158,165,245},
};
static	void	print_Year(void)
{
	char	s[5];
	#define	printi	0
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(0xFFFFFF);
	sprintf(s,"%04d",2000+Disp_Date.Year);
	s[4]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
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
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(0xFFFFFF);
	sprintf(s,"%02d",Disp_Date.Month);
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
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(0xFFFFFF);
	sprintf(s,"%02d",Disp_Date.Day);
	s[2]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}
const	char	*const	WeekDay_Name[]={
"MON","TUE","WED",
"THU","FRI","SAT",
"SUN"
};
static	void	print_Week(void)
{
	#define	printi	3
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(0xFFFFFF);
	GUI_DispStringInRect(WeekDay_Name[Disp_Date.WeekDay-1],(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}
static	void	print_AMPM(void)
{
	#define	printi	4
	if(AMPM_EN)
	{
		GUI_MEMDEV_Handle hMem;
		hMem = GUI_MEMDEV_CreateEx(RTC_Cursor_Back[printi].x0,RTC_Cursor_Back[printi].y0,RTC_Cursor_Back[printi].x1-RTC_Cursor_Back[printi].x0+1,RTC_Cursor_Back[printi].y1-RTC_Cursor_Back[printi].y0+1,GUI_MEMDEV_NOTRANS);
		GUI_MEMDEV_Select(hMem);
		GUI_SetBkColor(GUI_BLACK);
		GUI_Clear();
		GUI_SetFont(&GUI_FontArial22);
		GUI_SetColor(0xFFFFFF);
			if(RTC_Time.Hours<12)
				GUI_DispStringInRect("AM",(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
			else
				GUI_DispStringInRect("PM",(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
		GUI_MEMDEV_Delete(hMem);
	}
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
	GUI_SetFont(&GUI_FontAccidental_Presidency140);
	GUI_SetColor(0xFFFFFF);
	if(AMPM_EN)
	{
		R=Disp_Time.Hours%12;
		if(R==0)
			R=12;
	}
	else
	{
		R=Disp_Time.Hours;
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
	GUI_SetFont(&GUI_FontAccidental_Presidency140);
	GUI_SetColor(0xFFEF00);
	sprintf(s,"%02d",Disp_Time.Minutes);
	s[2]=0;
	GUI_DispStringInRect(s,(GUI_RECT*)&RTC_Cursor_Back[printi],GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RTC_Cursor_Back[printi].x0, RTC_Cursor_Back[printi].y0);//显示
	GUI_MEMDEV_Delete(hMem);
	#undef	printi
}
static	void	Watch_Dispaly_1_Display(void)
{
	u8	a;
	if(Disp_Date.Year!=RTC_Date.Year)
	{
		Disp_Date.Year=RTC_Date.Year;
		print_Year();
	}
	if(Disp_Date.Month!=RTC_Date.Month)
	{
		Disp_Date.Month=RTC_Date.Month;
		print_Month();
	}
	if(Disp_Date.WeekDay!=RTC_Date.WeekDay)
	{
		Disp_Date.WeekDay=RTC_Date.WeekDay;
		a=Disp_Date.WeekDay;
		if(Disp_Date.WeekDay>7 || Disp_Date.WeekDay==0)
			Disp_Date.WeekDay=1;
		print_Week();
		Disp_Date.WeekDay=a;
	}
	if(Disp_Date.Day!=RTC_Date.Day)
	{
		Disp_Date.Day=RTC_Date.Day;
		print_Day();
	}
	if(Disp_Time.Hours!=RTC_Time.Hours)
	{
		if(Disp_Time.Hours/12!=RTC_Time.Hours/12)
		{
			print_AMPM();
		}
		Disp_Time.Hours=RTC_Time.Hours;
		print_Hours();
	}
	if(Disp_Time.Minutes!=RTC_Time.Minutes)
	{
		Disp_Time.Minutes=RTC_Time.Minutes;
		print_Minutes();
	}
}
static	void	Screensaver_Windows_1return(void)
{
	__NOP();
}
static	void Screensaver_Windows_1(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_FillRect(69,281,72,282);
	GUI_FillRect(99,281,102,282);
	print_Year();
	print_Month();
	print_Day();
	if(Disp_Date.WeekDay>7 || Disp_Date.WeekDay==0)
		Disp_Date.WeekDay=1;
	print_Week();
	print_AMPM();
	print_Hours();
	print_Minutes();
	Screensaver_Dispaly=Watch_Dispaly_1_Display;
	Disp_Sleep=Screensaver_Windows_1return;
}


//表盘6
typedef struct {
	GUI_AUTODEV_INFO AutoDevInfo1,AutoDevInfo2,AutoDevInfo3;
	GUI_POINT	Minutes_pin[4];
	GUI_POINT	Minutes2_pin[4];
	GUI_POINT	Hours_pin[4];
	s16	X,Y;
//	s16	haloX,haloY;
	GUI_RECT	RECT;
	s16	Angle;
} AutoPARAM2;
static	AutoPARAM2	R_AutoPARAM_2;


static	const	GUI_POINT	Minutes_pin1[]={-1,-92,-1,14,1,14,1,-92};
static	const	GUI_POINT	Minutes_pin2[]={-2,-93,-2,-78,2,-78,2,-93};
static	const	GUI_POINT	Hours_pin1[]={-2,-66,-2,10,2,10,2,-66};

static	uc32	Seconds_Color_BUFF[]={
	0xBAAE07,0xB4A908,0xACA109,0xA89D09,0x9F950A,0x978E0B,
	0x8E860C,0x847C0D,0x7C750E,0x746D0F,0x6A6410,
	0x605B11,0x565212,0x4E4A13,0x444114,0x3B3815,
	0x323016,0x2C2A17,0x232218,0x1B1B18
};
static	void	_Pointer_Seconds_2_Display(void	*p)
{
	u8	i;
	AutoPARAM2	*pParam;
	pParam=(AutoPARAM2*)p;
	GUI_AA_SetFactor(4);
	if(pParam->AutoDevInfo1.DrawFixed)
	{
		GUI_SetColor(GUI_BLACK);
		GUI_FillRect(14,44,225,253);
		GUI_SetColor(0x191919);
		GUI_SetPenSize(18);
		GUI_AA_DrawArc(120,149,93,93,0,360);			//后面那个好暗的圆环
	}
	for(i=0;i<20;i++)
	{
		GUI_SetColor(Seconds_Color_BUFF[i]);
		GUI_AA_DrawArc(120,149,93,93,pParam->Angle+i*4-1,pParam->Angle+(i+1)*4);	//拖出来的尾巴
	}
	GUI_SetColor(0xF9E604);
	GUI_AA_EnableHiRes();
	GUI_AA_FillCircle(pParam->X,pParam->Y,11*4);
	GUI_AA_DisableHiRes();
	GUI_AA_FillCircle(pParam->X/4,pParam->Y/4,10);
	GUI_SetPenSize(18);
	if(pParam->AutoDevInfo1.DrawFixed)
	{
		GUI_SetColor(0xF9E604);
		GUI_AA_FillPolygon(pParam->Hours_pin,4,120,149);
		GUI_SetColor(GUI_BLACK);
		GUI_AA_FillPolygon(pParam->Minutes2_pin,4,120,149);
		GUI_SetColor(0xF9E604);
		GUI_AA_FillPolygon(pParam->Minutes_pin,4,120,149);
		GUI_AA_FillCircle(120,149,4);
		GUI_SetColor(GUI_BLACK);
		GUI_AA_FillCircle(120,149,2);
	}
}
static	void	_Pointer_Minutes_2_Display(void	*p)
{
	AutoPARAM2	*pParam;
	u8	i;
	pParam=(AutoPARAM2*)p;
	GUI_AA_SetFactor(4);
	if(pParam->AutoDevInfo2.DrawFixed)
	{
		GUI_SetColor(GUI_BLACK);
		GUI_FillRect(14,44,225,253);
		GUI_SetColor(0x191919);
		GUI_SetPenSize(18);
		GUI_AA_DrawArc(120,149,93,93,0,360);

		GUI_SetPenSize(18);
		for(i=0;i<20;i++)
		{
			GUI_SetColor(Seconds_Color_BUFF[i]);
			GUI_AA_DrawArc(120,149,93,93,pParam->Angle+i*4-1,pParam->Angle+(i+1)*4);
		}
		GUI_SetColor(0xF9E604);
		GUI_AA_EnableHiRes();
		GUI_AA_FillCircle(pParam->X,pParam->Y,11*4);
		GUI_AA_DisableHiRes();
		GUI_AA_FillCircle(pParam->X/4,pParam->Y/4,10);
		GUI_SetColor(0xF9E604);
		GUI_AA_FillPolygon(pParam->Hours_pin,4,120,149);
	}
	GUI_SetColor(GUI_BLACK);
	GUI_AA_FillPolygon(pParam->Minutes2_pin,4,120,149);
	GUI_SetColor(0xF9E604);
	GUI_AA_FillPolygon(pParam->Minutes_pin,4,120,149);
	GUI_AA_FillCircle(120,149,4);
	GUI_SetColor(GUI_BLACK);
	GUI_AA_FillCircle(120,149,2);
}
static	void	_Pointer_Hours_2_Display(void	*p)
{
	AutoPARAM2	*pParam;
	pParam=(AutoPARAM2*)p;
	GUI_AA_SetFactor(4);
	if(pParam->AutoDevInfo3.DrawFixed)
	{
		GUI_SetColor(GUI_BLACK);
		GUI_FillRect(14,44,225,253);
	}
	GUI_SetColor(0xF9E604);
	GUI_AA_FillPolygon(pParam->Hours_pin,4,120,149);
	if(pParam->AutoDevInfo3.DrawFixed)
	{
		GUI_SetColor(0xF9E604);
		GUI_AA_FillPolygon(pParam->Minutes_pin,4,120,149);
		GUI_AA_FillCircle(120,149,4);
		GUI_SetColor(GUI_BLACK);
		GUI_AA_FillCircle(120,149,2);
	}
}


static	void	Screensaver_2_Return(void)
{
	if(Disp_windows_Set!=Screensaver_interface)
	{
		GUI_MEMDEV_DeleteAuto(&AutoDev_1);
		GUI_MEMDEV_DeleteAuto(&AutoDev_2);
		GUI_MEMDEV_DeleteAuto(&AutoDev_3);
		GUI_MEMDEV_DeleteAuto(&AutoDev_4);
	}
}
static	const	GUI_RECT RTC_print_AMPM2_Back={106,23,133,38};
static	void	print_AMPM2(void)
{
	if(AMPM_EN)
	{
		GUI_MEMDEV_Handle hMem;
		hMem = GUI_MEMDEV_CreateEx(RTC_print_AMPM2_Back.x0,RTC_print_AMPM2_Back.y0,RTC_print_AMPM2_Back.x1-RTC_print_AMPM2_Back.x0+1,RTC_print_AMPM2_Back.y1-RTC_print_AMPM2_Back.y0+1,GUI_MEMDEV_NOTRANS);
		GUI_MEMDEV_Select(hMem);
		GUI_SetBkColor(GUI_BLACK);
		GUI_Clear();
		GUI_SetFont(&GUI_FontArial22);
		GUI_SetColor(0xFFFFFF);
			if(RTC_Time.Hours<12)
				GUI_DispStringInRect("AM",(GUI_RECT*)&RTC_print_AMPM2_Back,GUI_TA_VCENTER|GUI_TA_HCENTER);
			else
				GUI_DispStringInRect("PM",(GUI_RECT*)&RTC_print_AMPM2_Back,GUI_TA_VCENTER|GUI_TA_HCENTER);
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_WriteAt(hMem, RTC_print_AMPM2_Back.x0, RTC_print_AMPM2_Back.y0);//显示
		GUI_MEMDEV_Delete(hMem);
	}
}

static	void	Watch_Dispaly_2_Display(void)
{
	float	A;
	u16	a,b;
	if(Disp_Time.Seconds!=RTC_Time.Seconds)
	{
		a=(RTC_Time.Minutes*60+RTC_Time.Seconds)*360/3600;
		b=((RTC_Time.Hours%12)*60+RTC_Time.Minutes)*360/720;
		A=(360-a)*3.1415926/180;
		GUI_RotatePolygon(R_AutoPARAM_2.Minutes_pin,Minutes_pin1,4,A);
		GUI_RotatePolygon(R_AutoPARAM_2.Minutes2_pin,Minutes_pin2,4,A);
		GUI_RotatePolygon(R_AutoPARAM_2.Hours_pin,Hours_pin1,4,(360-b)*3.1415926/180);
		R_AutoPARAM_2.Angle=RTC_Time.Seconds*360/60;
		Calculation_position(120*4,149*4,&R_AutoPARAM_2.X,&R_AutoPARAM_2.Y,93*4,R_AutoPARAM_2.Angle);
		R_AutoPARAM_2.Angle=360-R_AutoPARAM_2.Angle+90;
		GUI_MEMDEV_DrawAuto(&AutoDev_1,&R_AutoPARAM_2.AutoDevInfo1,&_Pointer_Seconds_2_Display,&R_AutoPARAM_2);
		if(a!=(Disp_Time.Minutes*60+Disp_Time.Seconds)*360/3600)
			GUI_MEMDEV_DrawAuto(&AutoDev_2,&R_AutoPARAM_2.AutoDevInfo2,&_Pointer_Minutes_2_Display,&R_AutoPARAM_2);
		if(b!=((Disp_Time.Hours%12)*60+Disp_Time.Minutes)*360/720)
			GUI_MEMDEV_DrawAuto(&AutoDev_3,&R_AutoPARAM_2.AutoDevInfo3,&_Pointer_Hours_2_Display,&R_AutoPARAM_2);
		if(Disp_Time.Hours/12!=RTC_Time.Hours/12)
		{
			print_AMPM2();
		}
	}
	if(Disp_Date.Year!=RTC_Date.Year)
	{
		Disp_Date.Year=RTC_Date.Year;
		print_Year();
	}
	if(Disp_Date.Month!=RTC_Date.Month)
	{
		Disp_Date.Month=RTC_Date.Month;
		print_Month();
	}
	if(Disp_Date.WeekDay!=RTC_Date.WeekDay)
	{
		Disp_Date.WeekDay=RTC_Date.WeekDay;
		a=Disp_Date.WeekDay;
		if(Disp_Date.WeekDay>7 || Disp_Date.WeekDay==0)
			Disp_Date.WeekDay=1;
		print_Week();
		Disp_Date.WeekDay=a;
	}
	if(Disp_Date.Day!=RTC_Date.Day)
	{
		Disp_Date.Day=RTC_Date.Day;
		print_Day();
	}
	Disp_Date=RTC_Date;
	Disp_Time=RTC_Time;
	Screensaver_2_Return();
}

static	void Screensaver_Windows_2(void)
{
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_FillRect(69,281,72,282);
	GUI_FillRect(99,281,102,282);

	GUI_MEMDEV_CreateAuto(&AutoDev_1);
	GUI_MEMDEV_CreateAuto(&AutoDev_2);
	GUI_MEMDEV_CreateAuto(&AutoDev_3);

	AutoDev_1.FirstCall=1;
	AutoDev_2.FirstCall=0;
	AutoDev_3.FirstCall=0;

	AutoDev_2.rPrev.x0=120;
	AutoDev_2.rPrev.y0=148;
	AutoDev_2.rPrev.x1=120;
	AutoDev_2.rPrev.y1=148;
	AutoDev_2.rView.x0=AutoDev_2.rPrev.x0;
	AutoDev_2.rView.y0=AutoDev_2.rPrev.y0;
	AutoDev_2.rView.x1=AutoDev_2.rPrev.x1;
	AutoDev_2.rView.y1=AutoDev_2.rPrev.y1;

	AutoDev_3.rPrev.x0=120;
	AutoDev_3.rPrev.y0=148;
	AutoDev_3.rPrev.x1=120;
	AutoDev_3.rPrev.y1=148;
	AutoDev_3.rView.x0=AutoDev_3.rPrev.x0;
	AutoDev_3.rView.y0=AutoDev_3.rPrev.y0;
	AutoDev_3.rView.x1=AutoDev_3.rPrev.x1;
	AutoDev_3.rView.y1=AutoDev_3.rPrev.y1;


	Disp_Time.Seconds=0xFF;
	Disp_Time.Minutes=0xFF;
	Disp_Time.Hours=0xFF;
	Watch_Dispaly_2_Display();
	print_Year();
	print_Month();
	print_Day();
	if(Disp_Date.WeekDay>7 || Disp_Date.WeekDay==0)
		Disp_Date.WeekDay=1;
	print_Week();
	print_AMPM2();

	Screensaver_Dispaly=Watch_Dispaly_2_Display;
	Disp_Sleep=Screensaver_2_Return;
}

























