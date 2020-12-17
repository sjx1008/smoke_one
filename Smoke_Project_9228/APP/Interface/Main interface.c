/* 梅工
2018/08/02
CCW和CCV都去掉下面的显示，并且放大中间的跳动
*/


#include "WM_Disp.h"
#include	<math.h>

#ifndef PI
#define PI                 3.14159265358979f
#endif

static uc16	minFFTBUFF[];
static	void	Disp_Main(void);
static	void	MP3_DisWave(void);
//static	void	__min_DisWave(void);
static	void	__max_DisWave(void);
static	void	DisWaveInit(u16 x, u16 y,u16 *uiFFT,u16	*minFFT,u16	max,u16 min,u8 Multiple,void (*P)(void));

uc16	MP3_FFT_BUFF[][10]={
{5,8,6,10,3,4,5,4,6,8},
{7,4,3,7,10,8,4,6,3,4},
{3,5,1,4,6,4,7,5,7,8},
{7,10,4,8,10,7,5,3,6,5},
{4,7,8,5,4,10,4,7,8,3},
{8,4,7,9,2,7,10,4,7,8},
};
static	u8	N=0;
static	u8	MP3_Tim=0;

#define WattTest
#define SmokingTime

#define	d_Main_BK_Color	0

////主题颜色定义
///*当前所处风格*/
////u8	R_UI_Theme=0;
///*主界面刘线条*/
//uc32	line_Vape_BUFF[]={d_Orange_line_Vape,d_Green_line_Vape,d_Blue_line_Vape,d_Yellow_line_Vape,d_Red_line_Vape};
///*功率吸烟跑马*/
//uc32	Vape_paoma_BUFF[]={d_Orange_circle_Vape,d_Green_circle_Vape,d_Blue_circle_Vape,d_Yellow_circle_Vape,d_Red_circle_Vape};
///*SPP吸烟跑马*/
//uc32	SPP_paoma_BUFF[]={d_SPP_Orange_Vape,d_SPP_Green_Vape,d_SPP_Blue_Vape,d_SPP_Yellow_Vape,d_SPP_Red_Vape};



static	sc16	Vape_Tim_angle_BUFF_VW[][4]=
{{250,270,-90,-72},
{215,251,-73,-36},
{180,215,-36,0},
{144,180,0,36},
{115,144,37,66},
};
static	sc16	Vape_Tim_angle_BUFF_VV[][4]=
{{250,270,-90,-72},
{215,251,-73,-36},
{180,215,-36,0},
{144,180,0,36},
{110,144,37,71},
};
static	sc16	Vape_Tim_angle_BUFF_BP[][4]=
{{250,270,-90,-72},
{215,251,-73,-36},
{180,215,-36,0},
{144,180,0,36},
{130,144,37,51},
};

static	sc16	(*p_Vape_Tim_angle_BUFF)[4];

//static	sc16	Vape_Tim_angle_VW[][6]={{270,260,239,208,166,115},{-90,-80,-59,-28,14,66}};
//static	sc16	Vape_Tim_angle_VV[][6]={{270,259,238,206,163,109},{-90,-79,-58,-26,17,71}};
//static	sc16	Vape_Tim_angle_BP[][6]={{270,261,242,214,176,130},{-90,-81,-62,-34,4,50}};

//static	sc16	Vape_Tim_angle_VW[][16]={
//{270,267,264,
//260,253,246,
//239,229,219,
//208,194,180,
//166,149,132,
//115},
//{-90,-87,-84,
//-80,-73,-66,
//-59,-49,-39,
//-28,-14,0,
//14,31,48,
//66}};
//static	sc16	Vape_Tim_angle_VV[][16]={
//{270,267,263,
//259,252,245,
//238,227,216,
//206,192,178,
//163,155,147,
//109},
//{-90,-87,-83,
//-79,-72,-65,
//-58,-47,-36,
//-26,-12,2,
//17,35,53,
//71}};
//static	sc16	Vape_Tim_angle_BP[][16]={
//{270,267,264,
//261,255,249,
//242,233,224,
//214,202,189,
//176,161,146,
//130},
//{-90,-87,-84,
//-81,-75,-69,
//-62,-53,-44,
//-34,-22,-9,
//4,19,34,
//50}};

static	sc16	Vape_Tim_angle_VW[][2]={
{270,115},
{-90,66}};
static	sc16	Vape_Tim_angle_VV[][2]={
{270,109},
{-90,71}};
static	sc16	Vape_Tim_angle_BP[][2]={
{270,130},
{-90,50}};

static	uc8	Vape_Tim_angle_I_BUFF[]={
	0,1,2,3,5,7,9,12,15,18,22,27,33,40,48,57
};
static	sc16	(*p_Vape_Tim_angle)[2];
//static	u8	R_Vape_TimStart;





///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

static	u8	BatterGrade_Q;
static	u8	BatterGrade2_Q;
static	u8	Smoking_tim_Q;
static	u16	Smoking_tim10ms_Q;
static	u16	Res_Q;
static	u16	Wout_Q;
//static	u16	Wset_Q;
static	u16	Vout_Q;
//static	u16	Vset_Q;
//static	u16	Vset_MAX;
//static	u16	Iout_Q;
static	u16	Dataout_Q;
static	u8	B_BAT_Congman_Q;
static	u8	B_BAT_Congman2_Q;
static	u8	B_Batt1_Back_YES=0;
static	u8	B_Batt2_Back_YES=0;
static	u8	B_BAT_Paoma;
static	u8	B_Custom_Disp;
static	u16	Vape_number_Q;
//static	u8	B_Fast_Charg_Q;
//static	u8	mainRTC_m;
//static	u8	mainRTC_h;
static	u8	Disp_RTC_Hour;
static	u8	Disp_RTC_Minute;

u8	B_ADDSUB_LOCK;

//吸烟计时窗口
//static	void	RTC_Time_parts(void)
//{
//	mainRTC_m=0xF0;
//	mainRTC_h=0xF0;
//}
//主界面RTC窗口
static	void	RTC_parts(void)
{
	GUI_SetColor(0xB5863C);
	GUI_FillRect(206,10,207,11);
	GUI_FillRect(206,16,207,17);
	Disp_RTC_Hour=0xF0;
	Disp_RTC_Minute=0xF0;
}
//AUTO模式窗口
static	void	AUTO_MODE_parts(void)
{
//	static	u8	B=0,Time=0;
//	GUI_RECT	RECT;
	if(B_AUOT_MODE)
	{
//		Time++;
//		if(Time>50)
//		{
//			Time=0;
//			B=!B;
//			if(B)
			{
				draw_Bmp_ex(d_Main_AUTO_BMP,106,7);
			}
//			else
//			{
//				RECT.x0=112;
//				RECT.y0=235;
//				RECT.x1=127;
//				RECT.y1=250;
//				Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,112,235);
//			}
//		}
	}
//	else
//	{
//		if(B)
//		{
//			B=0;
//			RECT.x0=112;
//			RECT.y0=235;
//			RECT.x1=127;
//			RECT.y1=250;
//			Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,112,235);
//		}
//	}
}
//吸烟计时窗口 //20180907
static	void	Vape_Time_parts(void)
{
//	Smoking_tim_Q=0;
	Smoking_tim10ms_Q=0xF000;

	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispCharAt('S',219,291);
}
//吸烟口数窗口	//20180907
static	void	Vape_number_parts(void)
{
	Vape_number_Q=0xF000;
}
//阻值窗口	//20180907
static	void	Res_parts(void)
{
	Res_Q=0xF000;
}
//20180907
static	void	LOCK_Res_update(u8	B)
{
	if(B_LOCK_Res && B)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Main_LOCK_R_PNG,50,274);
	}
	else
	{
		GUI_SetColor(GUI_WHITE);
		GUI_SetFont(&GUI_FontArial22);
		GUI_DispCharAt('&',50,271);
	}
}
//加减键锁窗口//20180907
static	void	Lock_parts(void)
{
	GUI_RECT	RECT;
	if(B_ADDSUB_LOCK)
	{
		draw_Bmp_ex(d_LockADDSUB_BMP,110,291);
	}
	else
	{
		RECT.x0=110;
		RECT.y0=33;
		RECT.x1=128;
		RECT.y1=49;
		Map_draw_bmpToBitmap_ex(d_MainBottomBelow,&RECT,110,291);
	}
}

//电流窗口更新//20180907
void	OutI_parts(void)
{
//	Iout_Q=0xF000;
}

//void	Angle_calculation(u16 *X,u16 *Y,u16	R,u16	A)
//{
//	float	aaa,bbb;
//
////	float PI=3.1415926;

////	aaa=360-R*arm_sin_f32(PI*A/180)+0.5f;
////	bbb=360-R*arm_cos_f32(PI*A/180)+0.5f;

//  aaa=360-R*sin(PI*A/180)+0.5f;
//	bbb=360-R*cos(PI*A/180)+0.5f;
//
//	*X=aaa;
//	*Y=bbb;
//}
//20180907
static	void	Batt_parts(void)
{
	BatterGrade_Q=0xF0;
	BatterGrade2_Q=0xF0;
	B_BAT_Congman_Q=0;
	B_BAT_Congman2_Q=0;
	B_BAT_Paoma=40;
	B_Batt1_Back_YES=1;
	B_Batt2_Back_YES=1;
//	B_Fast_Charg_Q=0xF0;

	GUI_SetColor(0xB5863C);
	GUI_SetPenSize(1);
	GUI_DrawRect(11,8,35,19);
	GUI_DrawRect(42,8,66,19);
	GUI_DrawVLine(36,11,16);
	GUI_DrawVLine(67,11,16);
}
//

//输出电压窗口//20180907
static	void	OutV_parts(void)
{
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispCharAt('V',219,271);
	Vout_Q=0xf000;
}
//输出瓦数窗口//20180907
static	void	OutW_parts(void)
{
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispCharAt('W',217,271);
	Wout_Q=0xf000;
}
//温度单位窗口
static	void	Temp_metric_parts(void)
{
	GUI_RECT	RECT;
	GUI_MEMDEV_Handle hMem;
	RECT.x0=109;
	RECT.y0=180;
	RECT.x1=127;
	RECT.y1=193;

	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(0xFFEF00);
	GUI_SetFont(&GUI_FontArial22);
	if(R_Temp_metric==F_metric)
	{
		GUI_DispCharAt('F',114,176);
	}
	else
	{
		GUI_DispCharAt('C',114,176);
	}
	GUI_SetPenSize(1);
	GUI_AA_SetFactor(3);
	GUI_AA_DrawArc(111,182,2,2,0,360);

	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,RECT.x0,RECT.y0);//
	GUI_MEMDEV_Delete(hMem);
}

/////////////////////////////////////
//设定值弧度显示
static	void	Disp_Arc_angle(u16	molecule,u16	Denominator);
//static	void	Disp_Data_Arc_int(void);

#define	Arc_angle_Start		470	//
#define	Arc_angle_End			110	//

//SPP
#define	Arc_angleSPP_Start		470	//241
#define	Arc_angleSPP_End			110	//-61

static s16	Arc_angle_Old;
static s16	Arc_angle_Now;
static s16	Arc_angle_Set;
static u8	B_Arc_angle_State;	//0:设定值 ，1:吸烟时间
u8	Arc_angle_Time;			//状态切换延时

u16	(*Get_Mole)(void);
u16	(*Get_Deno)(void);

//SPP两只眼睛呼吸
//static	u8	SPP_Eye_state;	//两只眼睛的状态	0：关闭呼吸	1：开启呼吸
//static	u16	SPP_Eye_Alpha;	//当前的混色值
//static	void	SPP_Eye_AlphaBreathing(void)
//{
//	GUI_RECT	RECT;
//	GUI_MEMDEV_Handle hMem;
//	RECT.x0=38;
//	RECT.y0=94;
//	RECT.x1=59;
//	RECT.y1=105;
//
//	hMem = GUI_MEMDEV_CreateEx(0, 0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
//	GUI_MEMDEV_Select(hMem);
//	Map_draw_bmpToBitmap_ex(SPP_paoma_BUFF[R_UI_Theme],&RECT,0,0);
//	GUI_EnableAlpha(1);
//	GUI_SetAlpha(SPP_Eye_Alpha);
////	GUI_SetUserAlpha(&AlphaState, SPP_Eye_Alpha);
//	Map_draw_bmpToBitmap_ex(d_SPP_Ash_Vape,&RECT,0,0);
//	GUI_SetAlpha(0);
////	GUI_RestoreUserAlpha(&AlphaState);
//	GUI_EnableAlpha(0);
//	GUI_MEMDEV_Select(0);
//	GUI_MEMDEV_WriteAt(hMem,82,128);//
//
//	RECT.x0=92;
//	RECT.y0=94;
//	RECT.x1=113;
//	RECT.y1=105;
//	GUI_MEMDEV_Select(hMem);
//	Map_draw_bmpToBitmap_ex(SPP_paoma_BUFF[R_UI_Theme],&RECT,0,0);
//	GUI_EnableAlpha(1);
//	GUI_SetAlpha(SPP_Eye_Alpha);
////	GUI_SetUserAlpha(&AlphaState, SPP_Eye_Alpha);
//	Map_draw_bmpToBitmap_ex(d_SPP_Ash_Vape,&RECT,0,0);
////	GUI_RestoreUserAlpha(&AlphaState);
//	GUI_SetAlpha(0);
//	GUI_EnableAlpha(0);
//	GUI_MEMDEV_Select(0);
//	GUI_MEMDEV_WriteAt(hMem,136,128);//
//	GUI_MEMDEV_Delete(hMem);
//}

//static	void	SPP_Eye_breathing(void)
//{
//	static	u8	fanxiang=0;//1:递增	0:递减
//	if(R_Work_mode!=d_SPP_mode)
//		return;
//	if(SPP_Eye_state)
//	{
//		if(fanxiang)
//		{
//			SPP_Eye_Alpha+=10;
//			if(SPP_Eye_Alpha>255)
//			{
//				SPP_Eye_Alpha=255;
//				fanxiang=0;
//			}
//		}
//		else
//		{
//			SPP_Eye_Alpha-=10;
//			if(SPP_Eye_Alpha>255)
//			{
//				SPP_Eye_Alpha=0;
//				fanxiang=1;
//			}
//		}
//		SPP_Eye_AlphaBreathing();
//	}
//	else
//	{
//		if(SPP_Eye_Alpha<255)
//		{
//			fanxiang=1;
//			SPP_Eye_Alpha+=10;
//			if(SPP_Eye_Alpha>=255)
//				SPP_Eye_Alpha=255;
//			SPP_Eye_AlphaBreathing();
//		}
//	}
//
//}
//////////////吸烟动画
//吸烟音符跳动
static	uc32	Vape_MP3_VWS_BUFF[][2]={
	{d_Main_S_L_PNG1,d_Main_S_R_PNG1},{d_Main_S_L_PNG2,d_Main_S_R_PNG2},{d_Main_S_L_PNG3,d_Main_S_R_PNG3},
};
static	uc32	Vape_MP3_VWN_BUFF[][2]={
	{d_Main_N_L_PNG1,d_Main_N_R_PNG1},{d_Main_N_L_PNG2,d_Main_N_R_PNG2},{d_Main_N_L_PNG3,d_Main_N_R_PNG3},
};
static	uc32	Vape_MP3_VWH_BUFF[][2]={
	{d_Main_H_L_PNG1,d_Main_H_R_PNG1},{d_Main_H_L_PNG2,d_Main_H_R_PNG2},{d_Main_H_L_PNG3,d_Main_H_R_PNG3},
};
static	uc32 (*const Vape_MP3_VW_BUFF[])[2]={Vape_MP3_VWS_BUFF,Vape_MP3_VWN_BUFF,Vape_MP3_VWH_BUFF};

static	uc32	Vape_MP3_SP_BUFF[][2]={
	{d_Main_SP_L_PNG1,d_Main_SP_R_PNG1},{d_Main_SP_L_PNG2,d_Main_SP_R_PNG2},{d_Main_SP_L_PNG3,d_Main_SP_R_PNG3},
};

static	uc32	Vape_MP3_VT_BUFF[]={
	d_Main_VT_PNG1,d_Main_VT_PNG2,d_Main_VT_PNG3
};

static	void	Vape_MP3_Beat(void)
{
	static	u8	MP3_I=0;
	MP3_I++;
	if(MP3_I>2)
		MP3_I=0;
	if(R_Work_mode==d_Watt_mode)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_VW_BUFF[R_Watt_Strength][MP3_I][0],25,162);
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_VW_BUFF[R_Watt_Strength][MP3_I][1],169,162);
//			if(R_Watt_Strength==SOFT_Strength)
//			{
//			}
//			else if(R_Watt_Strength==NOR_Strength)
//			{
//			}
//			else
//			{
//			}
	}
	else if(R_Work_mode==d_SPP_mode)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_SP_BUFF[MP3_I][0],23,170);
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_SP_BUFF[MP3_I][1],181,170);
	}
	else if(R_Work_mode==d_Temp_mode || R_Work_mode==d_TCR_mode)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_VT_BUFF[MP3_I],26,165);
	}
	else if(R_Work_mode==d_Voltage_mode||R_Work_mode==d_Bypass_mode)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_VWH_BUFF[MP3_I][0],25,162);
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_VWH_BUFF[MP3_I][1],169,162);
	}
	else if(R_Work_mode==d_Custom_mode||R_Work_mode==d_CustomTemp_mode||R_Work_mode==d_CustomVolt_mode)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_VWH_BUFF[MP3_I][0],20,165);
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,Vape_MP3_VWH_BUFF[MP3_I][1],174,165);
	}
}

//static	const	GUI_RECT	Vape_Tim_angle_XY_1={87,203,151,217};
static	const	GUI_RECT	Vape_Tim_angle_XY_BUFF[][2]=
{
[0][0]={87,203,120,217},[0][1]={120,203,151,217},
[1][0]={33,168,88,211},[1][1]={152,168,206,211},
[2][0]={12,110,39,171},[2][1]={200,110,228,171},
[3][0]={12,46,39,108},[3][1]={201,46,228,108},
[4][0]={33,07,88,49},[4][1]={151,07,206,49},
};
//
//static	sc16	Vape_Tim_angle_1[]={-109,-71};

static	u8	Vape_Tim_angle_I=0;

//切吸烟动画图片
static	s16	R_Cutt_Vape_Arc_Start;
static	s16	R_Cutt_Vape_Arc_End;
static	s16	R_Cutt_Vape_Arc_Start2;
static	s16	R_Cutt_Vape_Arc_End2;
static	void	_Cutt_Vape_Arc(void)
{
	GUI_SetPenSize(13);
	GUI_DrawArc(120,149,104,104,R_Cutt_Vape_Arc_Start,R_Cutt_Vape_Arc_End);
}
//static	void	Cutt_Vape_Arc(u32	address,u8	i)
//{
//	R_Cutt_Vape_Arc_Start=p_Vape_Tim_angle_BUFF[i][0];
//	R_Cutt_Vape_Arc_End=p_Vape_Tim_angle_BUFF[i][1];
//	MapNoRulebmpToBitmap_ex(address,(GUI_RECT*)&Vape_Tim_angle_XY_BUFF[i][0],_Cutt_Vape_Arc,Vape_Tim_angle_XY_BUFF[i][0].x0,Vape_Tim_angle_XY_BUFF[i][0].y0+40,0);
//	R_Cutt_Vape_Arc_Start=p_Vape_Tim_angle_BUFF[i][2];
//	R_Cutt_Vape_Arc_End=p_Vape_Tim_angle_BUFF[i][3];
//	MapNoRulebmpToBitmap_ex(address,(GUI_RECT*)&Vape_Tim_angle_XY_BUFF[i][1],_Cutt_Vape_Arc,Vape_Tim_angle_XY_BUFF[i][1].x0,Vape_Tim_angle_XY_BUFF[i][1].y0+40,0);
//}
static	void	Clear_Vape_Arc(s16	A1,s16 A2)
{
	s8	i;
	for(i=4;i>=0;i--)
	{
		if(A1<=p_Vape_Tim_angle_BUFF[i][1])
		{
			R_Cutt_Vape_Arc_Start=p_Vape_Tim_angle_BUFF[i][0];
			R_Cutt_Vape_Arc_End=p_Vape_Tim_angle_BUFF[i][1];
			MapNoRulebmpToBitmap_ex(d_MainBottomDark,(GUI_RECT*)&Vape_Tim_angle_XY_BUFF[i][0],_Cutt_Vape_Arc,Vape_Tim_angle_XY_BUFF[i][0].x0,Vape_Tim_angle_XY_BUFF[i][0].y0+40,0);
		}
		if(A2>=p_Vape_Tim_angle_BUFF[i][2])
		{
			R_Cutt_Vape_Arc_Start=p_Vape_Tim_angle_BUFF[i][2];
			R_Cutt_Vape_Arc_End=p_Vape_Tim_angle_BUFF[i][3];
			MapNoRulebmpToBitmap_ex(d_MainBottomDark,(GUI_RECT*)&Vape_Tim_angle_XY_BUFF[i][1],_Cutt_Vape_Arc,Vape_Tim_angle_XY_BUFF[i][1].x0,Vape_Tim_angle_XY_BUFF[i][1].y0+40,0);
		}
	}
}
static	void	_SP_Vape_Arc(void)
{
	GUI_SetPenSize(54);
	GUI_DrawArc(120,154,50,50,Arc_angle_Set,Arc_angleSPP_Start);
}
static	void	SP_Cutt_Vape_Arc_4(u32	address1,u32	address2)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_CreateEx(23,122,195,38,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	draw_BmpToBitmap_ex(address1,23,122);
	GUI_RECT	RECT={0,0,194,37};
	MapNoRulebmpToBitmap_ex(address2,&RECT,_SP_Vape_Arc,23,122,hMem);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,23,122);//
	GUI_MEMDEV_Delete(hMem);
}

//更改圆弧显示状态
//static	u8	Tim_Vape_Dat;
static	void	_Tim_Vape_Arc_L(void)
{
//	s16	a;
	GUI_SetPenSize(13);
//	a=R_Cutt_Vape_Arc_Start-Tim_Vape_Dat;
//	if(a<p_Vape_Tim_angle[0][5])
//		a=p_Vape_Tim_angle[0][5];
	GUI_DrawArc(120,149,105,105,R_Cutt_Vape_Arc_End,R_Cutt_Vape_Arc_Start);
}
static	void	_Tim_Vape_Arc_R(void)
{
//	s16	a;
	GUI_SetPenSize(13);
//	a=R_Cutt_Vape_Arc_Start2+Tim_Vape_Dat;
//	if(a>p_Vape_Tim_angle[1][5])
//		a=p_Vape_Tim_angle[1][5];
	GUI_DrawArc(120,149,105,105,R_Cutt_Vape_Arc_Start2,R_Cutt_Vape_Arc_End2);
}
u8	Vape_Arc_Tim=0;
static	void	Change_Arc_angle_State(void)
{
	static	u8	B;
	u8	i;
	u16	min,max;
	if(B_Arc_angle_State==0)
	{
		if(B_Out_Yes && R_Smoke_Tim>2)
		{
			Smoking_tim_Q=0;
			B_Arc_angle_State=1;
			R_Cutt_Vape_Arc_Start=270;
			R_Cutt_Vape_Arc_Start2=-90;
			B=1;
			Vape_Arc_Tim=11;
		}
	}
	if(B_Arc_angle_State==1)
	{
		if(B)
		{
			if(B_Out_Yes)
			{
				if(!R_Interface_maintain_Time)
				{
					R_Interface_maintain_Time=4;
					Vape_MP3_Beat();
				}
				if(Vape_Arc_Tim>=11)
				{
					Vape_Arc_Tim=0;
					if(Smoking_tim_Q<15)
						Smoking_tim_Q++;
					R_Cutt_Vape_Arc_End=Vape_Tim_angle_I_BUFF[Smoking_tim_Q]*(p_Vape_Tim_angle[0][1]-p_Vape_Tim_angle[0][0])/Vape_Tim_angle_I_BUFF[15]+p_Vape_Tim_angle[0][0];
					R_Cutt_Vape_Arc_End2=Vape_Tim_angle_I_BUFF[Smoking_tim_Q]*(p_Vape_Tim_angle[1][1]-p_Vape_Tim_angle[1][0])/Vape_Tim_angle_I_BUFF[15]+p_Vape_Tim_angle[1][0];
//					R_Cutt_Vape_Arc_End=p_Vape_Tim_angle[0][Smoking_tim_Q];
//					R_Cutt_Vape_Arc_End2=p_Vape_Tim_angle[1][Smoking_tim_Q];
//					for(i=1;i<6;i++)
//					{
//						max=86*i/5;
//						if(Smoking_tim_Q<=max)
//						{
//							min=86*(i-1)/5;
//							R_Cutt_Vape_Arc_End=((Smoking_tim_Q-min)*(p_Vape_Tim_angle[0][i]-p_Vape_Tim_angle[0][i-1])+p_Vape_Tim_angle[0][i-1]*(max-min))/(max-min);
//							R_Cutt_Vape_Arc_End2=((Smoking_tim_Q-min)*(p_Vape_Tim_angle[1][i]-p_Vape_Tim_angle[1][i-1])+p_Vape_Tim_angle[1][i-1]*(max-min))/(max-min);
//							break;
//						}
//					}
					if(R_Cutt_Vape_Arc_Start>R_Cutt_Vape_Arc_End)
					{
	//					if(R_Cutt_Vape_Arc_Start>=(R_Cutt_Vape_Arc_End+15))
	//						Tim_Vape_Dat=15;
	//					else if(R_Cutt_Vape_Arc_Start>=(R_Cutt_Vape_Arc_End+12))
	//						Tim_Vape_Dat=12;
	//					else if(R_Cutt_Vape_Arc_Start>=(R_Cutt_Vape_Arc_End+9))
	//						Tim_Vape_Dat=9;
	//					else if(R_Cutt_Vape_Arc_Start>=(R_Cutt_Vape_Arc_End+6))
	//						Tim_Vape_Dat=6;
	//					else
	//						Tim_Vape_Dat=3;
						min=4,max=0;
						for(i=0;i<5;i++)
						{
							if(R_Cutt_Vape_Arc_Start>=p_Vape_Tim_angle_BUFF[i][0] || R_Cutt_Vape_Arc_End>=p_Vape_Tim_angle_BUFF[i][0])
							{
								if(min>i)
									min=i;
							}
							if(R_Cutt_Vape_Arc_Start<=p_Vape_Tim_angle_BUFF[i][1] || R_Cutt_Vape_Arc_End<=p_Vape_Tim_angle_BUFF[i][1])
							{
								if(max<i)
									max=i;
							}
						}//
						for(i=min;i<=max;i++)
						{
							MapNoRulebmpToBitmap_ex(d_MainBottomLight,(GUI_RECT*)&Vape_Tim_angle_XY_BUFF[i][0],_Tim_Vape_Arc_L,Vape_Tim_angle_XY_BUFF[i][0].x0,Vape_Tim_angle_XY_BUFF[i][0].y0+40,0);
						}
						R_Cutt_Vape_Arc_Start=R_Cutt_Vape_Arc_End;
	//					R_Cutt_Vape_Arc_Start-=Tim_Vape_Dat;
					}
					if(R_Cutt_Vape_Arc_Start2<R_Cutt_Vape_Arc_End2)
					{
	//					if((R_Cutt_Vape_Arc_Start2+15)<=R_Cutt_Vape_Arc_End2)
	//						Tim_Vape_Dat=15;
	//					else if((R_Cutt_Vape_Arc_Start2+12)<=R_Cutt_Vape_Arc_End2)
	//						Tim_Vape_Dat=12;
	//					else if((R_Cutt_Vape_Arc_Start2+9)<=R_Cutt_Vape_Arc_End2)
	//						Tim_Vape_Dat=9;
	//					else if((R_Cutt_Vape_Arc_Start2+6)<=R_Cutt_Vape_Arc_End2)
	//						Tim_Vape_Dat=6;
	//					else
	//						Tim_Vape_Dat=3;
						min=4,max=0;
						for(i=0;i<5;i++)
						{
							if(R_Cutt_Vape_Arc_Start2>=p_Vape_Tim_angle_BUFF[i][2] || R_Cutt_Vape_Arc_End2>=p_Vape_Tim_angle_BUFF[i][2])
							{
								if(min>i)
									min=i;
							}
							if(R_Cutt_Vape_Arc_Start2<=p_Vape_Tim_angle_BUFF[i][3] || R_Cutt_Vape_Arc_End2<=p_Vape_Tim_angle_BUFF[i][3])
							{
								if(max<i)
									max=i;
							}
						}//
						for(i=min;i<=max;i++)
						{
							MapNoRulebmpToBitmap_ex(d_MainBottomLight,(GUI_RECT*)&Vape_Tim_angle_XY_BUFF[i][1],_Tim_Vape_Arc_R,Vape_Tim_angle_XY_BUFF[i][1].x0,Vape_Tim_angle_XY_BUFF[i][1].y0+40,0);
						}
						R_Cutt_Vape_Arc_Start2=R_Cutt_Vape_Arc_End2;
	//					R_Cutt_Vape_Arc_Start2+=Tim_Vape_Dat;
					}
				}
				if(R_Cutt_Vape_Arc_Start<=p_Vape_Tim_angle[0][1] && R_Cutt_Vape_Arc_Start2>=p_Vape_Tim_angle[1][1])
				{
					if(!Arc_angle_Time)
					{
//						Cutt_Vape_Arc(d_MainBottomDark,4);
//						Cutt_Vape_Arc(d_MainBottomDark,3);
//						Cutt_Vape_Arc(d_MainBottomDark,2);
//						Cutt_Vape_Arc(d_MainBottomDark,1);
//						Cutt_Vape_Arc(d_MainBottomDark,0);
						Clear_Vape_Arc(R_Cutt_Vape_Arc_Start,R_Cutt_Vape_Arc_Start2);
						Smoking_tim_Q=0;
						R_Cutt_Vape_Arc_Start=270;
						R_Cutt_Vape_Arc_Start2=-90;
						Vape_Arc_Tim=0;
					}
				}
				else
				{
					Arc_angle_Time=11;
				}
			}
			else
			{
				B=0;
				Arc_angle_Time=50;
			}
		}
		else
		{
			if(B_Out_Yes)
			{
//				Cutt_Vape_Arc(d_MainBottomDark,4);
//				Cutt_Vape_Arc(d_MainBottomDark,3);
//				Cutt_Vape_Arc(d_MainBottomDark,2);
//				Cutt_Vape_Arc(d_MainBottomDark,1);
//				Cutt_Vape_Arc(d_MainBottomDark,0);
				Clear_Vape_Arc(R_Cutt_Vape_Arc_Start,R_Cutt_Vape_Arc_Start2);
				B_Arc_angle_State=0;
			}
			else
			{
				if(!Arc_angle_Time)
				{
//					Cutt_Vape_Arc(d_MainBottomDark,4);
//					Cutt_Vape_Arc(d_MainBottomDark,3);
//					Cutt_Vape_Arc(d_MainBottomDark,2);
//					Cutt_Vape_Arc(d_MainBottomDark,1);
//					Cutt_Vape_Arc(d_MainBottomDark,0);
					Clear_Vape_Arc(R_Cutt_Vape_Arc_Start,R_Cutt_Vape_Arc_Start2);
					B_Arc_angle_State=0;
				}
			}
		}
	}
}
static	uc32	SP_Arc_angle_BUFF[][2]={
	{d_Main_SP_L1,d_Main_SP_R1},
	{d_Main_SP_L2,d_Main_SP_R2},
	{d_Main_SP_L3,d_Main_SP_R3},
	{d_Main_SP_L4,d_Main_SP_R4},
	{d_Main_SP_L5,d_Main_SP_R5},
	{d_Main_SP_L6,d_Main_SP_R6},
	{d_Main_SP_L7,d_Main_SP_R7},
	{d_Main_SP_L8,d_Main_SP_R8},
	{d_Main_SP_L9,d_Main_SP_R9},
	{d_Main_SP_L10,d_Main_SP_R10}
};
static	uc8	SP_Arc_angle_XY[][4]={
	{103,113,110,113},
	{96,113,117,113},
	{81,112,124,112},
	{67,110,136,110},
	{48,105,149,105},
	{32,99,165,99},
	{16,89,180,89},
	{4,73,194,73},
	{0,57,205,57},
	{1,38,198,38},
};
static	void	Disp_SP_Vape_Arc(u8	i)
{
	if(i<10)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,SP_Arc_angle_BUFF[i][0],SP_Arc_angle_XY[i][0]+11,SP_Arc_angle_XY[i][1]+122);
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,SP_Arc_angle_BUFF[i][1],SP_Arc_angle_XY[i][2]+11,SP_Arc_angle_XY[i][3]+122);
	}
	else
	{
		SP_Cutt_Vape_Arc_4(d_MainSP_PM3,d_MainSP_PM4);
	}
}
static	void	Clear_SP_Vape_Arc(u8	i)
{
	if(i>=10)
		SP_Cutt_Vape_Arc_4(d_MainSP_PM15,d_MainSP_PM5);
	if(i>=8)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_MainSP_PM13,11,160);
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_MainSP_PM18,209,160);
	}
	if(i>=6)
	{
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_MainSP_PM14,11,184);
		Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_MainSP_PM19,202,184);
	}
	if(i>=3)
	{
		draw_Bmp_ex(d_MainSP_PM16,30,213);
		draw_Bmp_ex(d_MainSP_PM17,153,213);
	}
	draw_Bmp_ex(d_MainSP_PM20,85,232);
}
static	void	SP_Arc_angle_State(void)
{
	static	u8	B;
	if(B_Arc_angle_State==0)
	{
		if(B_Out_Yes && R_Smoke_Tim>2)
		{
			B_Arc_angle_State=1;
			Arc_angle_Time=0;
			Vape_Tim_angle_I=0;
			B=1;
		}
	}
	if(B_Arc_angle_State==1)
	{
		if(B)
		{
			if(B_Out_Yes)
			{
				if(!R_Interface_maintain_Time)
				{
					R_Interface_maintain_Time=4;
					Vape_MP3_Beat();
				}
				if(!Arc_angle_Time)
				{
					if(Vape_Tim_angle_I<11)
					{
						//刷弧度
						Disp_SP_Vape_Arc(Vape_Tim_angle_I);
						Arc_angle_Time=8;
						Vape_Tim_angle_I++;
					}
					else
					{
						Clear_SP_Vape_Arc(Vape_Tim_angle_I);
						Arc_angle_Time=8;
						Vape_Tim_angle_I=0;
					}
				}
			}
			else
			{
				B=0;
				Arc_angle_Time=50;
			}
		}
		else
		{
			if(B_Out_Yes)
			{
			//清除
				Clear_SP_Vape_Arc(Vape_Tim_angle_I);
				B_Arc_angle_State=0;
			}
			else
			{
				if(!Arc_angle_Time)
				{
				//清除
					Clear_SP_Vape_Arc(Vape_Tim_angle_I);
					B_Arc_angle_State=0;
				}
			}
		}
	}
}
////显示设定值
//static	void	Disp_Data_Arc_int(void)
//{
//	Disp_Arc_angle((*Get_Mole)(),(*Get_Deno)());
//}
static	void	Disp_Data_Arc(void)
{
//	B_Arc_angle_State=0;
//	Arc_angle_Time=0;
//	if(!B_Arc_angle_State)
	{
		Disp_Arc_angle((*Get_Mole)(),(*Get_Deno)());
	}
}

//显示吸烟时间
//static	void	Disp_Time_Arc(u16	molecule,u16	Denominator)
//{
//	if(B_Arc_angle_State)
//	{
//		Disp_Arc_angle(molecule,Denominator);
//	}
//}

static	const	GUI_RECT	Arc_angleBUFF[]={
	[0]={72,80,120,115},
	[1]={120,80,168,115},
	[2]={155,102,188,149},
	[3]={155,149,188,197},
	[4]={120,185,167,217},
	[5]={70,185,120,217},
	[6]={51,149,85,198},
	[7]={51,101,85,149},
	[8]={72,80,120,115},
};
static	sc16	Arc_Buff[][2]={
{495,450},{450,405},{405,360},{360,315},
{315,270},{270,225},{225,180},{180,135},{135,90}
};

static	const	GUI_RECT	Arc_angleSPPBUFF[]={
	[0]={56,0,109,15},
	[1]={109,0,162,15},
	[2]={149,9,183,32},
	[3]={144,32,183,60},
	[4]={109,50,162,70},
	[5]={56,50,109,70},
	[6]={34,32,74,60},
	[7]={34,9,67,32},
	[8]={56,0,109,15},
};
static	sc16	Arc_SPPBuff[][2]={
{516,450},{450,384},{384,360},{360,333},
{333,270},{270,208},{208,180},{180,156},{156,90}
};

//绘制伸长剪切区域
static	void	Arc_Elongation(void)
{
	GUI_AA_SetFactor(3);
	GUI_SetPenSize(17);
	GUI_SetColor(GUI_BLACK);
	GUI_AA_DrawArc(120,149,59,59,0,360);
	GUI_SetPenSize(15);
	GUI_SetColor(0x5F5C58);
	GUI_AA_DrawArc(120,149,59,59,0,360);
	if(Arc_angle_Now<Arc_angle_Start)
	{
		GUI_SetColor(0xFFEF00);
		GUI_AA_DrawArc(120,149,59,59,Arc_angle_Now,Arc_angle_Start);
	}
}
//绘制缩短剪切区域
//static	void	Arc_Shorten(void)
//{
//	GUI_AA_SetFactor(3);
//	GUI_SetPenSize(18);
//	GUI_SetColor(GUI_BLACK);
//	GUI_AA_DrawArc(120,150,60,60,0,360);
//	GUI_SetPenSize(16);
//	GUI_SetColor(0x5F5C58);
//	GUI_AA_DrawArc(120,150,60,60,0,360);
//	GUI_SetColor(0xFFEF00);
//	GUI_AA_DrawArc(120,150,60,60,Arc_angle_Old,Arc_angle_Now);
//}

//SPP绘制伸长剪切区域
static	void	Arc_SPPElongation(void)
{
	GUI_SetPenSize(54);
	GUI_DrawArc(120,154,50,50,Arc_angle_Now,Arc_angle_Old);
}
//SPP绘制缩短剪切区域
static	void	Arc_SPPShorten(void)
{
	GUI_SetPenSize(54);
	GUI_DrawArc(120,154,50,50,Arc_angle_Old,Arc_angle_Now);
}
static	void	Watt_Progress(void(*P)(void),GUI_RECT *pCutRectPos)
{
	GUI_MEMDEV_Handle hMem;
	hMem = GUI_MEMDEV_Create(pCutRectPos->x0, pCutRectPos->y0, pCutRectPos->x1-pCutRectPos->x0+1, pCutRectPos->y1-pCutRectPos->y0+1);
	GUI_MEMDEV_Select(hMem);
	(*P)();
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,pCutRectPos->x0,pCutRectPos->y0);//
	GUI_MEMDEV_Delete(hMem);
}
//更改弧长
static	void	Disp_Arc_angle(u16	molecule,u16	Denominator)
{
	u8	min=8,max=0;
	s8	i;
	if(R_Work_mode!=d_SPP_mode)
	{
		Arc_angle_Set=Arc_angle_Start-molecule*(Arc_angle_Start-Arc_angle_End)/Denominator;
		Arc_angle_Now=Arc_angle_Set;
		for(i=0;i<9;i++)
		{
			if(Arc_angle_Now>=Arc_Buff[i][1] || Arc_angle_Old>=Arc_Buff[i][1])
			{
				if(min>i)
					min=i;
			}
			if(Arc_angle_Now<=Arc_Buff[i][0] || Arc_angle_Old<=Arc_Buff[i][0])
			{
				if(max<i)
					max=i;
			}
		}
		if(Arc_angle_Now>Arc_angle_Old)//缩短
		{
			for(i=max;i>=min;i--)
			{
				Watt_Progress(Arc_Elongation,(GUI_RECT*)&Arc_angleBUFF[i]);
			}
		}
		else if(Arc_angle_Now<Arc_angle_Old)//伸长
		{
			for(i=min;i<=max;i++)
			{
				Watt_Progress(Arc_Elongation,(GUI_RECT*)&Arc_angleBUFF[i]);
			}
		}
	}
	else
	{
		Arc_angle_Set=Arc_angleSPP_Start-molecule*(Arc_angleSPP_Start-Arc_angleSPP_End)/Denominator;
		Arc_angle_Now=Arc_angle_Set;
		for(i=0;i<9;i++)
		{
			if(Arc_angle_Now>=Arc_SPPBuff[i][1] || Arc_angle_Old>=Arc_SPPBuff[i][1])
			{
				if(min>i)
					min=i;
			}
			if(Arc_angle_Now<=Arc_SPPBuff[i][0] || Arc_angle_Old<=Arc_SPPBuff[i][0])
			{
				if(max<i)
					max=i;
			}
		}
//		u32	addr;
		GUI_RECT	RECT;
		if(Arc_angle_Now>Arc_angle_Old)//缩短
		{
			for(i=max;i>=min;i--)
			{
				if(Vape_Tim_angle_I==5)
				{
					if(i<3 || i==7)
					{
//						addr=d_MainSP_PM3;
						RECT.x0=Arc_angleSPPBUFF[i].x0-12;
						RECT.y0=Arc_angleSPPBUFF[i].y0;
						RECT.x1=Arc_angleSPPBUFF[i].x1-12;
						RECT.y1=Arc_angleSPPBUFF[i].y1;
						MapNoRulebmpToBitmap_ex(d_MainSP_PM3,&RECT,Arc_SPPShorten,Arc_angleSPPBUFF[i].x0+11,Arc_angleSPPBUFF[i].y0+122,0);
					}
					else
					{
						MapNoRulebmpToBitmap_ex(d_MainSP_PM11,(GUI_RECT*)&Arc_angleSPPBUFF[i],Arc_SPPShorten,Arc_angleSPPBUFF[i].x0+11,Arc_angleSPPBUFF[i].y0+122,0);
					}
				}
				else
				{
					MapNoRulebmpToBitmap_ex(d_MainSP_PM11,(GUI_RECT*)&Arc_angleSPPBUFF[i],Arc_SPPShorten,Arc_angleSPPBUFF[i].x0+11,Arc_angleSPPBUFF[i].y0+122,0);
				}
			}
		}
		else if(Arc_angle_Now<Arc_angle_Old)//伸长
		{
			for(i=min;i<=max;i++)
			{
				if(Vape_Tim_angle_I==5)
				{
					if(i<3 || i==7)
					{
//						addr=d_MainSP_PM3;
						RECT.x0=Arc_angleSPPBUFF[i].x0-12;
						RECT.y0=Arc_angleSPPBUFF[i].y0;
						RECT.x1=Arc_angleSPPBUFF[i].x1-12;
						RECT.y1=Arc_angleSPPBUFF[i].y1;
						MapNoRulebmpToBitmap_ex(d_MainSP_PM4,&RECT,Arc_SPPElongation,Arc_angleSPPBUFF[i].x0+11,Arc_angleSPPBUFF[i].y0+122,0);
					}
					else
					{
						MapNoRulebmpToBitmap_ex(d_MainSP_PM12,(GUI_RECT*)&Arc_angleSPPBUFF[i],Arc_SPPElongation,Arc_angleSPPBUFF[i].x0+11,Arc_angleSPPBUFF[i].y0+122,0);
					}
				}
				else
				{
					MapNoRulebmpToBitmap_ex(d_MainSP_PM12,(GUI_RECT*)&Arc_angleSPPBUFF[i],Arc_SPPElongation,Arc_angleSPPBUFF[i].x0+11,Arc_angleSPPBUFF[i].y0+122,0);
				}
			}
		}
	}
	Arc_angle_Old=Arc_angle_Now;
}
//弧长初始化
void	Arc_angle_Init(u16	(*molecule)(void),u16	(*Denominator)(void))
{
	if(R_Work_mode==d_SPP_mode)
		Arc_angle_Old=Arc_angleSPP_Start;
	else
		Arc_angle_Old=Arc_angle_Start;
	B_Arc_angle_State=0;	//0:设定值 ，1:吸烟时间
	Arc_angle_Time=0;			//状态切换延时
	Get_Mole=molecule;
	Get_Deno=Denominator;
	Disp_Arc_angle((*Get_Mole)(),(*Get_Deno)());
}

//
//功率模式窗口
static	u16	Get_Watt_MODE_Mole(void)
{
	return	R_User_Watt_Set;
}
static	u16	Get_Watt_MODE_Deno(void)
{
	return	d_User_Watt_max;
}
void	Watt_MODE_windows(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,39);
	draw_Bmp_ex(d_MainBottomDark,0,40);
	if(R_Watt_Strength==SOFT_Strength)
	{
		draw_Bmp_ex(d_Main_VWS_Name,76,38);
	}
	else	if(R_Watt_Strength==HIGH_Strength)
	{
		draw_Bmp_ex(d_Main_VWH_Name,76,38);
	}
	else
	{
		draw_Bmp_ex(d_Main_VWN_Name,76,38);
	}

	LOCK_Res_update(0);
	OutV_parts();
	GUI_SetColor(0xFFEF00);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispCharAt('W',110,175);
	if(B_SMART_mode)
	{
		draw_Bmp_ex(d_Main_SMART_BMP,127,7);
	}
	AUTO_MODE_parts();
	Arc_angle_Init(Get_Watt_MODE_Mole,Get_Watt_MODE_Deno);
	Vape_MP3_Beat();
	B_SMART_RES_Update=0;
	p_Vape_Tim_angle_BUFF=Vape_Tim_angle_BUFF_VW;
	p_Vape_Tim_angle=Vape_Tim_angle_VW;
}
//电压模式窗口
static	u16	Get_Volt_MODE_Mole(void)
{
	return	R_User_Vout_Set;
}
static	u16	Get_Volt_MODE_Deno(void)
{
	return	d_User_Vout_max;
}
void	Voltage_MODE_windows(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,39);
	draw_Bmp_ex(d_MainBottomDark,0,40);
	draw_Bmp_ex(d_Main_VV_Name,86,38);
	GUI_SetColor(0xFFEF00);
	GUI_SetFont(&GUI_FontArial22);
	GUI_DispCharAt('V',112,175);
	LOCK_Res_update(0);
	OutW_parts();
	AUTO_MODE_parts();
	Arc_angle_Init(Get_Volt_MODE_Mole,Get_Volt_MODE_Deno);
	Vape_MP3_Beat();
	p_Vape_Tim_angle_BUFF=Vape_Tim_angle_BUFF_VV;
	p_Vape_Tim_angle=Vape_Tim_angle_VV;
}
//Bypass模式窗口
static	u16	Get_Bypass_MODE_Mole(void)
{
	return	100;
}
static	u16	Get_Bypass_MODE_Deno(void)
{
	return	100;
}
void	Bypass_MODE_windows(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,39);
	draw_Bmp_ex(d_MainBottomDark,0,40);
	draw_Bmp_ex(d_Main_BYPASS_Name,52,38);
	LOCK_Res_update(0);
	OutV_parts();
	AUTO_MODE_parts();
	Arc_angle_Init(Get_Bypass_MODE_Mole,Get_Bypass_MODE_Deno);
	draw_Bmp_ex(d_Main_BYPASS_BMP,94,90);
	Vape_MP3_Beat();
	p_Vape_Tim_angle_BUFF=Vape_Tim_angle_BUFF_BP;
	p_Vape_Tim_angle=Vape_Tim_angle_BP;
}
//温控模式窗口
#define	d_dt_TempC	90
#define	d_dt_TempF	190
static	u16	Get_Temp_MODE_Mole(void)
{
	if(R_Temp_metric==C_metric)
		return	R_User_Temp_Set_C-d_dt_TempC;
	else
		return	R_User_Temp_Set_F-d_dt_TempF;
}
static	u16	Get_Temp_MODE_Deno(void)
{
	if(R_Temp_metric==C_metric)
		return	d_User_TempC_max-d_dt_TempC;
	else
		return	d_User_TempF_max-d_dt_TempF;
}
static	u32	Atomizer_Name[]={d_Main_VTNI_Name,d_Main_VTTI_Name,d_Main_VTSS_Name};
void	Temp_MODE_windows(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,39);
	draw_Bmp_ex(d_Main_VTBottom_BMP,0,40);
	draw_Bmp_ex(Atomizer_Name[R_Atomizer],86,38);
	Temp_metric_parts();
	LOCK_Res_update(1);
	OutW_parts();
	AUTO_MODE_parts();
	Arc_angle_Init(Get_Temp_MODE_Mole,Get_Temp_MODE_Deno);
	Vape_MP3_Beat();
	p_Vape_Tim_angle_BUFF=Vape_Tim_angle_BUFF_VV;
	p_Vape_Tim_angle=Vape_Tim_angle_VV;
}
//TCR模式窗口
//const char	*const	Atomizer_TCR[]={"M1","M2","M3"};
static	u32	TCR_Name[]={d_Main_TCRM1_Name,d_Main_TCRM2_Name};
void	TCR_MODE_windows(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,39);
	draw_Bmp_ex(d_Main_VTBottom_BMP,0,40);
	if(R_TCR_term==0)
		draw_Bmp_ex(TCR_Name[R_TCR_term],86,37);
	else
		draw_Bmp_ex(TCR_Name[R_TCR_term],86,38);
	Temp_metric_parts();
	LOCK_Res_update(1);
	OutW_parts();
	AUTO_MODE_parts();
	Arc_angle_Init(Get_Temp_MODE_Mole,Get_Temp_MODE_Deno);
	Vape_MP3_Beat();
	p_Vape_Tim_angle_BUFF=Vape_Tim_angle_BUFF_VV;
	p_Vape_Tim_angle=Vape_Tim_angle_VV;
}
//功率曲线窗口
/*
*********************************************************************************************************
*	函 数 名: DisWave
*	功能说明: 频谱显示
*	形    参: x  频谱x坐标
*             y  频谱y坐标
*	返 回 值: 无
*********************************************************************************************************
*/
//static uc32	TopVal_Colour[]={0x00AEFF,0xA3DA27,0xFFC321,0x00E7EF,0x181DFF};
static uc16	minFFTBUFF[]={1,1,1,1,1,1,1,1,1,1};
static uint16_t s_MP3Spec_TopVal[10] = {0};   	/* 频谱顶值表 */
static uint16_t s_MP3Spec_CurVal[10] = {0};	  /* 频谱当前值表 */
static uint8_t  s_MP3Spec_Time[10] = {0};	  	/* 顶值停留时间表 */
#define usMaxVal   10               	/* 高度固定为10个方块 */
static	void	(*P_DisWave)(void)=__max_DisWave;
static	u16	DisWave_X,DisWave_Y;
//static	void	__min_DisWave(void)
//{
//	uint16_t i,j;
//	GUI_MEMDEV_Handle hMem;
//	GUI_RECT	RECT;
//	hMem = GUI_MEMDEV_CreateEx(0,0, 98, 49,GUI_MEMDEV_NOTRANS);
//	GUI_MEMDEV_Select(hMem);
//	RECT.x0=DisWave_X-23;
//	RECT.y0=DisWave_Y-49;
//	RECT.x1=RECT.x0+97;
//	RECT.y1=RECT.y0+48;
//	Map_draw_bmpToBitmap_ex(d_Ash_circle_Vape,&RECT,0,0);
//	/* 6. 绘制得到的频谱 */
//	GUI_SetColor(TopVal_Colour[R_UI_Theme]);
//	GUI_SetPenSize(1);
//	for(i = 0; i < 10; i++)
//	{
//		/* 显示频谱 */
//		RECT.x0=65;
//		RECT.y0=113;
//		RECT.x1=72;
//		RECT.y1=116;
//		for(j=0;j<s_MP3Spec_CurVal[i];j++)
//		{
//			Map_draw_bmpToBitmap_ex(Vape_paoma_BUFF[R_UI_Theme],&RECT,i*10,45-5*j);
//			RECT.y0-=5;
//			RECT.y1-=5;
//		}
//		/* 显示顶值 */
//		if(s_MP3Spec_TopVal[i]!=s_MP3Spec_CurVal[i])
//		{
//			GUI_DrawHLine(50-s_MP3Spec_TopVal[i]*5,i*10,7+i*10);
//		}
//	}
//	GUI_MEMDEV_Select(0);
//	GUI_MEMDEV_WriteAt(hMem,DisWave_X,DisWave_Y);//
//	GUI_MEMDEV_Delete(hMem);
//}
static	void	__max_DisWave(void)
{
	uint16_t i,j;
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	hMem = GUI_MEMDEV_CreateEx(0,0, 125, 69,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	/* 6. 绘制得到的频谱 */
	GUI_SetColor(0xFFEF00);
	GUI_SetPenSize(1);
	for(i = 0; i < 10; i++)
	{
		/* 显示频谱 */
		RECT.x0=0+i*13;
		RECT.y0=63;
		RECT.x1=7+i*13;
		RECT.y1=68;
		for(j=0;j<s_MP3Spec_CurVal[i];j++)
		{
			GUI_FillRectEx(&RECT);
			RECT.y0-=7;
			RECT.y1-=7;
		}
		/* 显示顶值 */
		if(s_MP3Spec_TopVal[i]!=s_MP3Spec_CurVal[i])
		{
			GUI_DrawHLine(63-s_MP3Spec_TopVal[i]*7,i*13,8+i*13);
		}
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,DisWave_X,DisWave_Y);//
	GUI_MEMDEV_Delete(hMem);
}
static u8 DisWave(u16 *uiFFT,u16	*minFFT,u16	max,u16 min,u8 Multiple)
{
	static	u8	CurVal_Tim=0;
	uint16_t i;
	uint16_t temp;
	uint16_t tempL;
	u8	disp_i,disp_j;
	u8	B=0,B2=0;
	disp_i=0;
	disp_j=0;
	/* 显示32条频谱 */
	CurVal_Tim++;
	if(CurVal_Tim>5)
	{
		CurVal_Tim=0;
		B=1;
	}
	for(i = 0; i < 10; i++)
	{
		temp=(uiFFT[i]-min)*Multiple*10/(max-min)/100+1;
		tempL=(minFFT[i]-min)*Multiple*10/(max-min)/100+1;
		if(!tempL)	tempL=1;
		if(!temp)	temp=1;
		if(temp > usMaxVal)
		{
			temp = usMaxVal;
		}
		if(tempL > usMaxVal)
		{
			tempL = usMaxVal;
		}
		/* 2. 更新频谱数值 */
		if(s_MP3Spec_CurVal[i] < temp)
		{
			s_MP3Spec_CurVal[i] = temp;
			B2=1;
			disp_i++;
		}
		else
		{
			if(s_MP3Spec_CurVal[i] < tempL)
			{
				s_MP3Spec_CurVal[i]=tempL;
				B2=1;
				disp_i++;
			}
			else if(s_MP3Spec_CurVal[i] > tempL)
			{
				if(B)
				{
					s_MP3Spec_CurVal[i] --;
					B2=1;
				}
				disp_i++;
			}
		}

		/* 4. 重设频谱顶值 */
		if(s_MP3Spec_CurVal[i] > s_MP3Spec_TopVal[i])
		{
			s_MP3Spec_TopVal[i] = s_MP3Spec_CurVal[i];
			/* 重设峰值停顿时间 */
			s_MP3Spec_Time[i] = 15;
			disp_j++;
			B2=1;
		}

		/* 3. 更新频谱顶值 */
		if(s_MP3Spec_TopVal[i]>s_MP3Spec_CurVal[i])
		{
			disp_j++;
		}
		if(s_MP3Spec_Time[i])
		{
			s_MP3Spec_Time[i]--;
		}
		else
		{
			/* 峰值减小1 */
			s_MP3Spec_Time[i]=5;
			if(s_MP3Spec_TopVal[i]>s_MP3Spec_CurVal[i])
			{
				s_MP3Spec_TopVal[i]--;
				B2=1;
			}
		}
	}
	if(B2)
		(*P_DisWave)();
	B=0;
	for(i = 0; i < 10; i++)
	{
		if(s_MP3Spec_TopVal[i]!=s_MP3Spec_CurVal[i])
		{
			B=1;
			break;
		}
	}
	if(B || disp_i || disp_j)
		return	0;
	return	1;
}
static	void	DisWaveInit(u16 x, u16 y,u16 *uiFFT,u16	*minFFT,u16	max,u16 min,u8 Multiple,void (*P)(void))
{
	u8	i;
	for(i=0;i<10;i++)
	{
		s_MP3Spec_TopVal[i]=0;
		s_MP3Spec_CurVal[i]=0;
		s_MP3Spec_Time[i]=0;
	}
	P_DisWave=P;
	DisWave_X=x;
	DisWave_Y=y;
	DisWave(uiFFT,minFFT,max,min,Multiple);
}
//static	u16	Get_Custom_MODE_Mole(void)
//{
//	return	R_Custom_BUFF.Custom_array.CustomCCW_Data[0];
//}
//static	u16	Get_Custom_MODE_Deno(void)
//{
//	return	d_User_Watt_max/10;
//}
//const char	*const	Custom_LO[]={"C1","C2","C3"};
void	Custom_MODE_windows(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,45);
	draw_Bmp_ex(d_Main_CCBottom_BMP,0,46);
	draw_Bmp_ex(d_Main_CCW_Name,74,39);
	LOCK_Res_update(0);
	OutW_parts();
	AUTO_MODE_parts();
	B_Custom_Disp=0;
	DisWaveInit(58,114,R_Custom_BUFF.Custom_array.CustomCCW_Data,R_Custom_BUFF.Custom_array.CustomCCW_Data,d_User_Watt_max/10,d_User_Watt_min/10,100,__max_DisWave);
	Vape_MP3_Beat();
}
//CCV
//static	u16	Get_CCV_Custom_MODE_Mole(void)
//{
//	return	R_Custom_BUFF.Custom_array.CustomCCV_Data[0];
//}
//static	u16	Get_CCV_Custom_MODE_Deno(void)
//{
//	return	d_User_Vout_max;
//}
//const char	*const	Custom_LO[]={"C1","C2","C3"};
void	CCV_Custom_MODE_windows(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,45);
	draw_Bmp_ex(d_Main_CCBottom_BMP,0,46);
	draw_Bmp_ex(d_Main_CCV_Name,78,39);
	LOCK_Res_update(0);
	OutV_parts();
	AUTO_MODE_parts();
	B_Custom_Disp=0;
	DisWaveInit(58,114,R_Custom_BUFF.Custom_array.CustomCCV_Data,R_Custom_BUFF.Custom_array.CustomCCV_Data,d_User_Vout_max,d_User_Vout_min,100,__max_DisWave);
	Vape_MP3_Beat();
}
//CCT
u16	*CCT_BUFF;
u16	CCT_Custom_Max;
u16	CCT_Custom_Min;
//static	u16	Get_CCT_Custom_MODE_Mole(void)
//{
//	if(R_Temp_metric==C_metric)
//		return	CCT_BUFF[0]-d_dt_TempC;
//	else
//		return	CCT_BUFF[0]-d_dt_TempF;
//}
//static	u16	Get_CCT_Custom_MODE_Deno(void)
//{
//	if(R_Temp_metric==C_metric)
//		return	d_User_TempC_max-d_dt_TempC;
//	else
//		return	d_User_TempF_max-d_dt_TempF;
//}


const char	*const	Atomizer_TC[]={"NI","TI","SS"};
void	CCT_Custom_MODE_windows(void)
{
	if(R_Temp_metric==C_metric)
	{
		CCT_BUFF=CCT_C_BUFF[R_Atomizer];
		CCT_Custom_Max=d_User_TempC_max;
		CCT_Custom_Min=d_User_TempC_min;
	}
	else
	{
		CCT_BUFF=CCT_F_BUFF[R_Atomizer];
		CCT_Custom_Max=d_User_TempF_max;
		CCT_Custom_Min=d_User_TempF_min;
	}
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,45);
	draw_Bmp_ex(d_Main_CCBottom_BMP,0,46);
	draw_Bmp_ex(d_Main_CCT_Name,78,39);
	LOCK_Res_update(1);
	OutW_parts();
	AUTO_MODE_parts();
	B_Custom_Disp=0;
	DisWaveInit(58,114,CCT_BUFF,CCT_BUFF,CCT_Custom_Max,CCT_Custom_Min,100,__max_DisWave);
	GUI_SetColor(0xB5863C);
	GUI_SetFont(&GUI_FontRaavi64B_28);
	GUI_DispStringHCenterAt(Atomizer_TC[R_Atomizer],120,193);
	Vape_MP3_Beat();
}
//SPP模式窗口
void	SPP_MODE_windows(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(0,0,239,121);
	GUI_FillRect(0,122,10,244);
	GUI_FillRect(230,122,239,244);
	GUI_FillRect(0,245,239,257);
	draw_Bmp_ex(d_MainSP_PM11,11,122);
	LOCK_Res_update(0);
	OutV_parts();
	AUTO_MODE_parts();
	Arc_angle_Init(Get_Watt_MODE_Mole,Get_Watt_MODE_Deno);
	Vape_MP3_Beat();
}

/////显示电池电量
static	void	BATT_Vip_disp(u8	vip,u8	I)
{
	GUI_COLOR	color;
	u8	d;
	u16	x0,x1;
	if(I==0)
		d=0;
	else
		d=31;
	x0=13+d;
	x1=20*vip/5+13+d;

	if(vip>1 || B_BAT_Charge)
	{
		color=0xB5863C;
	}
	else
	{
		color=0x2538DF;
	}
	GUI_SetColor(color);
	if(vip)
	{
		GUI_FillRect(x0,10,x1,17);
	}
	if(vip<5)
	{
		GUI_SetColor(GUI_BLACK);
		GUI_FillRect(x1+1,10,33+d,17);
	}
}

///显示雾化器阻值
void	ResData_update(u16	R)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	RECT.x0=8;
	RECT.y0=17;
	RECT.x1=45;
	RECT.y1=30;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);

	Map_draw_bmpToBitmap_ex(d_MainBottomBelow,&RECT,RECT.x0,RECT.y0);
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(GUI_WHITE);
	GUI_GotoXY(RECT.x0,RECT.y0-4);
	GUI_DispDecShift(R,4,2);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0+258);//
	GUI_MEMDEV_Delete(hMem);
}
//输出电压更新
void	Vout_Data_disp(u16	R)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	RECT.x0=178;
	RECT.y0=17;
	RECT.x1=214;
	RECT.y1=30;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	Map_draw_bmpToBitmap_ex(d_MainBottomBelow,&RECT,RECT.x0,RECT.y0);
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(GUI_WHITE);
	GUI_GotoXY(RECT.x0,RECT.y0-4);
	GUI_DispDecShift(R,4,2);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0+258);//
	GUI_MEMDEV_Delete(hMem);
}
//输出瓦数显示
void	Wout_Data_disp(u16	R,u16	R_Q)
{
	GUI_MEMDEV_Handle hMem;
	if(R>=1000 && R_Q>=1000 && (R/10==R_Q/10))
		return;
	GUI_RECT	RECT;
	RECT.x0=178;
	RECT.y0=17;
	RECT.x1=214;
	RECT.y1=30;
	hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	Map_draw_bmpToBitmap_ex(d_MainBottomBelow,&RECT,RECT.x0,RECT.y0);
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(GUI_WHITE);
	if(R<100)
	{
		GUI_GotoXY(RECT.x0+11,RECT.y0-4);
		GUI_DispDecShift(R,3,1);
	}
	else if(R<1000)
	{
		GUI_GotoXY(RECT.x0,RECT.y0-4);
		GUI_DispDecShift(R,4,1);
	}
	else
	{
		GUI_DispDecAt(R/10,RECT.x0+5,RECT.y0-4,3);
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0+258);//
	GUI_MEMDEV_Delete(hMem);
}
void	Batt_Back_shanshuo(u8	B)
{
	static	u8	Tim=30;
	static	u8	B1;
	Tim++;
	if(Tim>=30)
	{
		Tim=0;
		B1=!B1;
	}
	if(!BatterGrade && !B_Out_Yes && !B_BAT_Charge && !B)
	{
		if(!Tim)
		{
			B_Batt1_Back_YES=B1;
			if(B1)
			{
				//显示电池框
				GUI_SetColor(0xB5863C);
				GUI_SetPenSize(1);
				GUI_DrawRect(11,8,35,19);
				GUI_DrawVLine(36,11,16);
			}
			else
			{
				//不显示电池框
				GUI_SetColor(GUI_BLACK);
				GUI_FillRect(11,8,36,19);
			}
		}
	}
	else	if(!B_Batt1_Back_YES)
	{
		B_Batt1_Back_YES=1;
		//显示电池框
		GUI_SetColor(0xB5863C);
		GUI_SetPenSize(1);
		GUI_DrawRect(11,8,35,19);
		GUI_DrawVLine(36,11,16);
	}
	if(!BatterGrade2 && !B_Out_Yes && !B_BAT_Charge && !B)
	{
		if(!Tim)
		{
			B_Batt2_Back_YES=B1;
			if(B1)
			{
				//显示电池框
				GUI_SetColor(0xB5863C);
				GUI_SetPenSize(1);
				GUI_DrawRect(42,8,66,19);
				GUI_DrawVLine(67,11,16);
			}
			else
			{
				//不显示电池框
				GUI_SetColor(GUI_BLACK);
				GUI_FillRect(42,8,67,19);
			}
		}
	}
	else	if(!B_Batt2_Back_YES)
	{
		B_Batt2_Back_YES=1;
		//显示电池框
		GUI_SetColor(0xB5863C);
		GUI_SetPenSize(1);
		GUI_DrawRect(42,8,66,19);
		GUI_DrawVLine(67,11,16);
	}
}
//吸烟计时更新
void	Disp_Vape_Time(void)
{
	GUI_RECT	RECT;
	if(Smoking_tim10ms_Q!=R_Smoke_Tim10ms)
	{
		GUI_MEMDEV_Handle hMem;
		RECT.x0=177;
		RECT.y0=37;
		RECT.x1=214;
		RECT.y1=50;
		hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
		GUI_MEMDEV_Select(hMem);
		Map_draw_bmpToBitmap_ex(d_MainBottomBelow,&RECT,RECT.x0,RECT.y0);
		GUI_SetFont(&GUI_FontArial22);
		GUI_SetColor(GUI_WHITE);
		GUI_GotoXY(RECT.x0,RECT.y0-4);
		if(R_Smoke_Tim10ms<1000)
		{
			GUI_DispDecShift(R_Smoke_Tim10ms,4,2);
		}
		else
		{
			GUI_DispDecShift(R_Smoke_Tim10ms/10,4,1);
		}
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0+258);//
		GUI_MEMDEV_Delete(hMem);
		Smoking_tim10ms_Q=R_Smoke_Tim10ms;
	}
}
//吸烟口数更新
void	Disp_Vape_number(void)
{
	if(Vape_number_Q!=R_Statistics_number)
	{
		Vape_number_Q=R_Statistics_number;
		GUI_RECT	RECT;
		GUI_MEMDEV_Handle hMem;
		RECT.x0=8;
		RECT.y0=37;
		RECT.x1=62;
		RECT.y1=50;
		hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
		GUI_MEMDEV_Select(hMem);
		Map_draw_bmpToBitmap_ex(d_MainBottomBelow,&RECT,RECT.x0,RECT.y0);
		GUI_SetFont(&GUI_FontArial22);
		GUI_SetColor(GUI_WHITE);
		GUI_DispDecAt(R_Statistics_number,RECT.x0,RECT.y0-4,5);
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0+258);//
		GUI_MEMDEV_Delete(hMem);
	}
}
//主界面电池更新
void	Display_BAT(void)
{
	static	u8	Bat1,Bat2;
	static	u8	Tim;
	Batt_Back_shanshuo(Tim);
	if(B_Out_Yes)
	{
		B_BAT_Congman_Q=0;
		B_BAT_Congman2_Q=0;
		if(BatterGrade_Q!=Bat1)
		{
			BatterGrade_Q=Bat1;
			BATT_Vip_disp(Bat1,0);
		}
		if(BatterGrade2_Q!=Bat2)
		{
			BatterGrade2_Q=Bat2;
			BATT_Vip_disp(Bat2,1);
		}
		Tim=250;
	}
	else
	{
		if(Tim)
		{
			Tim--;
			if((s8)BatterGrade>(s8)BatterGrade_Q || (s8)BatterGrade2>(s8)BatterGrade2_Q)
			{
				Tim=0;
			}
		}
		else
		{
			Bat1=BatterGrade;
			Bat2=BatterGrade2;
		}
		if(B_BAT_Charge)
		{
			Tim=0;
			if(B_BAT_Paoma<30)
			{
				B_BAT_Paoma++;
			}
			else
			{
				B_BAT_Paoma=0;
				if(B_BAT_Congman)
				{
					if(!B_BAT_Congman_Q)
					{
						B_BAT_Congman_Q=1;
						BATT_Vip_disp(5,0);
					}
				}
				else
				{
					B_BAT_Congman_Q=0;
					if(BatterGrade_Q>5 || BatterGrade_Q+1<BatterGrade)
					{
						BatterGrade_Q=BatterGrade;
						if(BatterGrade>=5)
						{
							BatterGrade_Q=4;
						}
					}
					BATT_Vip_disp(BatterGrade_Q,0);
					BatterGrade_Q++;
				}
				if(B_BAT_Congman2)
				{
					if(!B_BAT_Congman2_Q)
					{
						B_BAT_Congman2_Q=1;
						BATT_Vip_disp(5,1);
					}
				}
				else
				{
					B_BAT_Congman2_Q=0;
					if(BatterGrade2_Q>5 || BatterGrade2_Q+1<BatterGrade2)
					{
						BatterGrade2_Q=BatterGrade2;
						if(BatterGrade2>=5)
						{
							BatterGrade2_Q=4;
						}
					}
					BATT_Vip_disp(BatterGrade2_Q,1);
					BatterGrade2_Q++;
				}
			}
		}
		else
		{
			B_BAT_Congman_Q=0;
			B_BAT_Congman2_Q=0;
			if(Tim)
			{
				if(Bat1!=BatterGrade_Q)
				{
					BatterGrade_Q=Bat1;
					BATT_Vip_disp(Bat1,0);
				}
				if(Bat2!=BatterGrade2_Q)
				{
					BatterGrade2_Q=Bat2;
					BATT_Vip_disp(Bat2,1);
				}
			}
			else
			{
				if(BatterGrade!=BatterGrade_Q)
				{
					BatterGrade_Q=BatterGrade;
					BATT_Vip_disp(BatterGrade,0);
				}
				if(BatterGrade2!=BatterGrade2_Q)
				{
					BatterGrade2_Q=BatterGrade2;
					BATT_Vip_disp(BatterGrade2,1);
				}
			}
		}
	}
//	if(B_BAT_Charge)
//	{
//		if(B_Fast_Charg_Q!=B_Fast_Charg)
//		{
//			B_Fast_Charg_Q=B_Fast_Charg;
//			RECT.x0=55;
//			RECT.y0=146;
//			RECT.x1=60;
//			RECT.y1=157;
//			if(B_Fast_Charg==0)
//			{
//				//画一个闪电
//				Map_draw_bmpToBitmap_ex(d_Orange_circle_Vape,&RECT,74,6);
//			}
//			else
//			{
//				//画两个闪电
//				Map_draw_bmpToBitmap_ex(d_Orange_circle_Vape,&RECT,74,6);
//				Map_draw_bmpToBitmap_ex(d_Orange_circle_Vape,&RECT,82,6);
//			}
//		}
//	}
//	else if(B_Fast_Charg_Q!=0xf0)
//	{
//		//清除闪电
//		RECT.x0=74;
//		RECT.y0=6;
//		RECT.x1=87;
//		RECT.y1=17;
//		Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,74,6);
//	}
}
//主界面电流更新
void	IoutData_update(void)
{
//	u8	B;
//	u16 a;
//	B=0;
//	if(B_Out_Yes)
//	{
//		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
//		a=R_Out_I_Actual/10;
//		if(a+3<Iout_Q || a>Iout_Q+3 || (Iout_Q==0 && a!=0))
//		{
//			Iout_Q=a;
//			B=1;
//		}
//	}
//	else
//	{
//		if(Iout_Q!=0)
//		{
//			Iout_Q=0;
//			B=1;
//		}
//	}
//	if(B)
//	{
//		GUI_MEMDEV_Handle hMem;
//		GUI_SetFont(&Font30);
//		hMem = GUI_MEMDEV_CreateEx(0, 0, 36, 15,GUI_MEMDEV_NOTRANS);
//		GUI_MEMDEV_Select(hMem);
//		GUI_SetColor(d_Main_BK_Color);
//		GUI_FillRect(0,0,35,14);
//		GUI_SetColor(GUI_WHITE);
//		GUI_GotoXY(-1, -8);
//		GUI_DispDecShift(Iout_Q,4,1);
//		GUI_MEMDEV_Select(0);
//		GUI_MEMDEV_WriteAt(hMem, 147, 136);//鏄剧ず
//		GUI_MEMDEV_Delete(hMem);
//	}
}



//主界面输出电压更新
void	Vout_update(void)
{
	u16	a,b;
	if(B_Out_Yes)
	{
		if(R_Smoke_Tim<3)
		{
			if(R_Work_mode==d_Watt_mode || R_Work_mode==d_SPP_mode)
			{
				a=sqrt_16(R_User_Watt_Set*R_Res_average);
				b=R_Res_average*d_User_Iout_max/10;
				if(b<a)
					a=b;
			}
			else	if(R_Work_mode==d_Bypass_mode)
			{
				a=d_Bypass_Vout;
			}
			else
			{
				a=R_Out_V_Actual;
			}
			if(a>d_User_Vout_max)
				a=d_User_Vout_max;
		}
		else
		{
			a=R_Out_V_Actual;
			if(R_Work_mode==d_Watt_mode)
			{
				if(a+9>Vout_Q && a<Vout_Q+9)
				{
					a=Vout_Q;
				}
			}
			else	if(R_Work_mode==d_Bypass_mode)
			{
				if(a+9>d_Bypass_Vout)
				{
					a=d_Bypass_Vout;
				}
			}
		}
		if(a!=Vout_Q)
		{
			Vout_Q=a;
			Vout_Data_disp(a);
		}
	}
	else
	{
		if(Vout_Q!=0)
		{
			Vout_Q=0;
			Vout_Data_disp(0);
		}
	}
}
//输出瓦数更新
void	Wout_update(void)
{
	u16	a;
	u16	R_User_Temp_Watt_Max;
	if(B_Out_Yes)
	{
		if(R_Out_W_Actual+20<Wout_Q || R_Out_W_Actual>Wout_Q+20 || (Wout_Q==0 && R_Out_W_Actual!=0))
		{
			a=R_Out_W_Actual;
			if(R_Work_mode==d_Temp_mode || R_Work_mode==d_CustomTemp_mode)
			{
				if(R_Atomizer==0)
					R_User_Temp_Watt_Max=Load_Ni200.WattsMAX;
				else if(R_Atomizer==1)
					R_User_Temp_Watt_Max=Load_Ti.WattsMAX;
				else
					R_User_Temp_Watt_Max=Load_Ss316.WattsMAX;
				if(a>R_User_Temp_Watt_Max*10)
					a=R_User_Temp_Watt_Max*10;
			}
			else if(R_Work_mode==d_TCR_mode)
			{
				if(R_TCR_term==0)
					R_User_Temp_Watt_Max=Load_M1.WattsMAX;
				else
					R_User_Temp_Watt_Max=Load_M2.WattsMAX;
				if(a>R_User_Temp_Watt_Max*10)
					a=R_User_Temp_Watt_Max*10;
			}
			Wout_Data_disp(a,Wout_Q);
			Wout_Q=a;
		}
	}
	else
	{
		if(R_Work_mode==d_Temp_mode || R_Work_mode==d_CustomTemp_mode)
		{
			if(R_Atomizer==0)
				R_User_Temp_Watt_Max=Load_Ni200.WattsMAX;
			else if(R_Atomizer==1)
				R_User_Temp_Watt_Max=Load_Ti.WattsMAX;
			else
				R_User_Temp_Watt_Max=Load_Ss316.WattsMAX;
			if(Wout_Q!=R_User_Temp_Watt_Max*10)
			{
				Wout_Data_disp(R_User_Temp_Watt_Max*10,Wout_Q);
				Wout_Q=R_User_Temp_Watt_Max*10;
			}
		}
		else if(R_Work_mode==d_TCR_mode)
		{
			if(R_TCR_term==0)
				R_User_Temp_Watt_Max=Load_M1.WattsMAX;
			else
				R_User_Temp_Watt_Max=Load_M2.WattsMAX;
			if(Wout_Q!=R_User_Temp_Watt_Max*10)
			{
				Wout_Data_disp(R_User_Temp_Watt_Max*10,Wout_Q);
				Wout_Q=R_User_Temp_Watt_Max*10;
			}
		}
		else
		{
			if(Wout_Q!=0)
			{
				Wout_Data_disp(0,Wout_Q);
				Wout_Q=0;
			}
		}
	}
}
//雾化器阻值更新
void	Atomizer_Res_update(void)
{
	u16	a;
//	u16 A,B;
//	if(B_Out_Yes)
//	{
//		a=R_Res_Actual/10;
//		if(a<R_Res_average/10)
//			a=R_Res_average/10;
//		if(a!=Res_Q)
//		{
//			Res_Q=a;
//			ResData_update(Res_Q);
//		}
//	}
//	else
	{
		if(R_Work_mode==d_Temp_mode || R_Work_mode==d_TCR_mode || R_Work_mode==d_CustomTemp_mode)
		{
			a=R_Res_Initial/10;
		}
		else
		{
			a=R_Res_average/10;
		}
		if(a!=Res_Q)
		{
			Res_Q=a;
//			if(R_Res_Initial>=d_Res_max || R_Res_Initial<d_Res_min)
//			{
//				Vset_MAX=d_User_Vout_max;
//				Wset_Q=0;
//				Vset_Q=0;
//			}
//			else
//			{
//				/////////计算电压模式下允许的最大输出电压///////////
//				A=R_Res_Initial*d_User_Iout_max/10;
//				B=sqrt_16(d_User_Watt_max*R_Res_Initial);
//				if(A>B)
//				{
//					A=B;
//				}
//				if(A>d_User_Vout_max)
//					A=d_User_Vout_max;
//				Vset_MAX=A;
//				if(R_User_Vout_Set>Vset_MAX)
//					R_User_Vout_Set=Vset_MAX;
//				Wset_Q=R_User_Vout_Set*R_User_Vout_Set/R_Res_Initial;
//				Vset_Q=sqrt_16(R_User_Watt_Set*R_Res_Initial);
//			}
			ResData_update(Res_Q);
		}
	}
}
//设定瓦数
void	Set_WattData_update(u16	R)
{
//	static	const	GUI_RECT	WattRECT[]={
//		{87,127,151,163},{81,130,157,159},{76,127,162,163}
//	};
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT={76,127,162,163};
	hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	if(R<100)
	{
		GUI_SetFont(&GUI_FontArial60);
		GUI_GotoXY(87,127-11);//
		GUI_DispDecShift(R,3,1);
	}
	else if(R<1000)
	{
		GUI_SetFont(&GUI_FontArial47);
		GUI_GotoXY(81,130-8);//
		GUI_DispDecShift(R,4,1);
	}
	else
	{
		GUI_SetFont(&GUI_FontArial60);
		GUI_DispDecAt(R/10,76,127-11,3);//
	}
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//
	GUI_MEMDEV_Delete(hMem);
}
//
void	Set_SPPWattData_update(u16	R)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT={54,59,208,112};
	hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial82);
	if(R<100)
	{
		GUI_GotoXY(72,46);//
		GUI_DispDecShift(R,3,1);
		GUI_GotoXY(166,95);
	}
	else if(R<1000)
	{
		GUI_GotoXY(54,46);//
		GUI_DispDecShift(R,4,1);
		GUI_GotoXY(190,95);
	}
	else
	{
		GUI_DispDecAt(R/10,58,46,3);//
		GUI_GotoXY(185,95);
	}
	GUI_SetFont(&GUI_FontArial22);
	GUI_SetColor(0xFFEF00);
	GUI_DispChar('W');
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//
	GUI_MEMDEV_Delete(hMem);
}
//设定瓦数更新
void	Set_Watt_update(void)
{
//	if(B_Out_Yes)
//	{
//		MP3_DisWave();
//	}
//	else
//	{
//		if(!B_Custom_Disp)
//		{
//			if(DisWave((u16*)MP3_FFT_BUFF[N],(u16*)MP3_FFT_BUFF[N],10,1,100))
//				B_Custom_Disp=1;
//		}
//	}

	#if 0
	u16	a;
	if(B_Out_Yes && R_Smoke_Tim>4)
	{
		a=R_Out_W_Actual;
		if(a+50>Dataout_Q && a<Dataout_Q+50)
		{
			a=Dataout_Q;
		}
		if(a+50>R_User_Watt_Set)
		{
			a=R_User_Watt_Set;
		}
		if(a!=Dataout_Q)
		{
			Set_WattData_update(a,Dataout_Q);
			Dataout_Q=a;
		}
	}
	else
	#endif
	{
		if(Dataout_Q!=R_User_Watt_Set)
		{
			Set_WattData_update(R_User_Watt_Set);
			Dataout_Q=R_User_Watt_Set;
		}
	}
}
//SPP设定瓦数更新
void	Set_SPPWatt_update(void)
{
	if(Dataout_Q!=R_User_Watt_Set)
	{
		Set_SPPWattData_update(R_User_Watt_Set);
		Dataout_Q=R_User_Watt_Set;
	}
}
//设定电压更新
static	void	Disp_Custom_Vout(u16	R);
void	Set_Volt_update(void)
{
	u16	a;
	u8 B;
	B=0;
	#if 0
	if(B_Out_Yes && R_Smoke_Tim>4)
	{
		a=R_Out_V_Actual;
		if(a+9>Dataout_Q && a<Dataout_Q+9)
		{
			a=Dataout_Q;
		}
		if(R_Work_mode==d_Voltage_mode)
		{
			if(a+15>R_User_Vout_Set)
				a=R_User_Vout_Set;
		}
		else
		{
			if(a+15>d_Bypass_Vout)
				a=d_Bypass_Vout;
		}
		if(Dataout_Q!=a)
			B=1;
	}
	else
	#endif
	{
		if(R_Work_mode==d_Voltage_mode)
		{
//			if(B_Out_Yes)
//			{
//				MP3_DisWave();
//			}
//			else
//			{
//				if(!B_Custom_Disp)
//				{
//					if(DisWave((u16*)MP3_FFT_BUFF[N],(u16*)MP3_FFT_BUFF[N],10,1,100))
//						B_Custom_Disp=1;
//				}
//			}
			if(Dataout_Q!=R_User_Vout_Set)
			{
				a=R_User_Vout_Set;
//				if(R_Res_Initial>=d_Res_min && R_Res_Initial<d_Res_max)
//					Wset_Q=R_User_Vout_Set*R_User_Vout_Set/R_Res_Initial;
				B=1;
			}
		}
		else
		{
			if(Dataout_Q!=d_Bypass_Vout)
			{
				a=d_Bypass_Vout;
				B=1;
			}
		}
	}
	if(B)
	{
		Disp_Custom_Vout(a);
		Dataout_Q=a;
	}
}
//
static	void	Disp_Set_Tempe(u16	R)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT={76,127,162,163};
	hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial60);
	GUI_DispDecAt(R,76,127-11,3);//
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//
	GUI_MEMDEV_Delete(hMem);
}
//设定温度更新
void	Set_Tempe_update(void)
{
	u8	B2;
	B2=0;
//	u16	b;
//	b=Dataout_Q;
//	if(B_Out_Yes)
//	{
//		MP3_DisWave();
//	}
//	else
//	{
//		if(!B_Custom_Disp)
//		{
//			if(DisWave((u16*)MP3_FFT_BUFF[N],(u16*)MP3_FFT_BUFF[N],10,1,100))
//				B_Custom_Disp=1;
//		}
//	}

	#if 0
	u16	a;
	static	u8	B=0;
	if(B_Out_Yes && R_Smoke_Tim>2)
	{
		if(!B)
		{
			B=1;
			B2=1;
			if(R_Temp_metric==C_metric)
				Dataout_Q=30;
			else
				Dataout_Q=86;
		}
		if(R_Temp_metric==C_metric)
		{
			if(R_Out_TempC_Actual>Dataout_Q && Dataout_Q<R_Out_Temp_Set)
			{
				Dataout_Q=R_Out_TempC_Actual;
				if(Dataout_Q+5>R_Out_Temp_Set)
					Dataout_Q=R_Out_Temp_Set;
				B2=1;
			}
		}
		else
		{
			a=R_Out_Temp_Set*9/5+32;
			if(a+10>R_User_Temp_Set_F)
				a=R_User_Temp_Set_F;
			if(R_Out_TempF_Actual>Dataout_Q && Dataout_Q<a)
			{
				Dataout_Q=R_Out_TempF_Actual;
				if(Dataout_Q+10>a)
					Dataout_Q=a;
				B2=1;
			}
		}
	}
	else
	#endif
	{
		//B=0;
		if(R_Temp_metric==C_metric)
		{
			if(Dataout_Q!=R_User_Temp_Set_C)
			{
				Dataout_Q=R_User_Temp_Set_C;
				B2=1;
			}
		}
		else
		{
			if(Dataout_Q!=R_User_Temp_Set_F)
			{
				Dataout_Q=R_User_Temp_Set_F;
				B2=1;
			}
		}
	}
	if(B2==1)
	{
		Disp_Set_Tempe(Dataout_Q);
	}
}



////输出曲线更新
//void	Custom_i_j_update(u8	i,u8	j)
//{
//	u8	y1;
//	u8	y2;
//	GUI_SetColor(GUI_WHITE);
//	GUI_SetPenSize(2);
//	GUI_AA_SetFactor(3);
//	for(;i<j;i++)
//	{
//		y1=116-34*(R_Custom_BUFF.Custom_array.CustomCCW_Data[i]-d_User_Watt_min/10)/(d_User_Watt_max/10-d_User_Watt_min/10);
//		y2=116-34*(R_Custom_BUFF.Custom_array.CustomCCW_Data[i+1]-d_User_Watt_min/10)/(d_User_Watt_max/10-d_User_Watt_min/10);
//		GUI_AA_DrawLine(62+i*6,y1,67+i*6,y2);
//	}
//}
//
#define	d_MP3_FFT_BUFF_Max	6

//static	void	Disp_Custom_Watt(u16	R)
//{
//	GUI_MEMDEV_Handle hMem;
//	GUI_RECT	RECT;
//	RECT.x0=78-23;
//	RECT.y0=160-49;
//	RECT.x1=169-23;
//	RECT.y1=190-49;
//	hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
//	GUI_MEMDEV_Select(hMem);
//	Map_draw_bmpToBitmap_ex(d_Ash_circle_Vape,&RECT,RECT.x0,RECT.y0);
//	GUI_SetFont(&GUI_FontLCD_ATDate46);
//	GUI_SetColor(0xFAFAFA);
//	if(R<10)
//	{
//		GUI_DispDecAt(R,101-23,RECT.y0-6,1);
//		GUI_GotoXY(123-23,RECT.y0-5);
//	}
//	else if(R<20)
//	{
//		GUI_DispDecAt(R,86-23,RECT.y0-6,2);
//		GUI_GotoXY(127-23,RECT.y0-5);
//	}
//	else if(R<100)
//	{
//		GUI_DispDecAt(R,92-23,RECT.y0-6,2);
//		GUI_GotoXY(133-23,RECT.y0-5);
//	}
//	else if(R<200)
//	{
//		GUI_DispDecAt(R,76-23,RECT.y0-6,3);//
//		GUI_GotoXY(136-23,RECT.y0-5);
//	}
//	else
//	{
//		GUI_DispDecAt(R,82-23,RECT.y0-6,3);//
//		GUI_GotoXY(142-23,RECT.y0-5);
//	}
//
//	GUI_SetFont(&GUI_FontSF_Proverbial_Gothic45);
//	GUI_SetColor(0xFAFAFA);
//	GUI_DispChar('W');
//	GUI_MEMDEV_Select(0);
//	GUI_MEMDEV_WriteAt(hMem, RECT.x0+23, RECT.y0+49);//
//	GUI_MEMDEV_Delete(hMem);
//}
static	void	Disp_Custom_Vout(u16	R)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT={76,127,162,163};
	hMem = GUI_MEMDEV_CreateEx(RECT.x0, RECT.y0, RECT.x1-RECT.x0+1, RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial47);
	GUI_GotoXY(81,130-8);//
	GUI_DispDecShift(R,4,2);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//
	GUI_MEMDEV_Delete(hMem);
}

static	void	MP3_DisWave(void)
{
	B_Custom_Disp=0;
	DisWave((u16*)minFFTBUFF,(u16*)minFFTBUFF,10,1,100);
	MP3_Tim++;
	if(MP3_Tim>20)
	{
		MP3_Tim=0;
		N++;
		if(N>=d_MP3_FFT_BUFF_Max)
			N=0;
		DisWave((u16*)MP3_FFT_BUFF[N],(u16*)minFFTBUFF,10,1,100);
	}
}
static	void 	Set_Custom_Data_update(void)
{
	if(B_Out_Yes)
	{
//		if(Dataout_Q!=R_Custom_BUFF.Custom_array.CustomCCW_Data[R_Custom_I_Set])
//		{
//			Dataout_Q=R_Custom_BUFF.Custom_array.CustomCCW_Data[R_Custom_I_Set];
//			Disp_Custom_Watt(Dataout_Q);
//		}
		MP3_DisWave();
		if(!R_Interface_maintain_Time)
		{
			R_Interface_maintain_Time=4;
			Vape_MP3_Beat();
		}
	}
	else
	{
		if(!B_Custom_Disp || B_Display_refresh)
		{
			if(DisWave(R_Custom_BUFF.Custom_array.CustomCCW_Data,R_Custom_BUFF.Custom_array.CustomCCW_Data,d_User_Watt_max/10,d_User_Watt_min/10,100))
			{
				B_Custom_Disp=1;
				B_Display_refresh=0;
			}
		}
//		if(Dataout_Q!=R_Custom_BUFF.Custom_array.CustomCCW_Data[0])
//		{
//			Dataout_Q=R_Custom_BUFF.Custom_array.CustomCCW_Data[0];
//			Disp_Custom_Watt(Dataout_Q);
//		}
	}
}
//
static	void 	Set_CCV_Custom_Data_update(void)
{
	if(B_Out_Yes)
	{
//		if(Dataout_Q!=R_Custom_BUFF.Custom_array.CustomCCV_Data[R_Custom_I_Set])
//		{
//			Dataout_Q=R_Custom_BUFF.Custom_array.CustomCCV_Data[R_Custom_I_Set];
//			Disp_Custom_Vout(Dataout_Q);
//		}
		MP3_DisWave();
		if(!R_Interface_maintain_Time)
		{
			R_Interface_maintain_Time=4;
			Vape_MP3_Beat();
		}
	}
	else
	{
		if(!B_Custom_Disp || B_Display_refresh)
		{
			if(DisWave(R_Custom_BUFF.Custom_array.CustomCCV_Data,R_Custom_BUFF.Custom_array.CustomCCV_Data,d_User_Vout_max,d_User_Vout_min,100))
			{
				B_Custom_Disp=1;
				B_Display_refresh=0;
			}
		}
//		if(Dataout_Q!=R_Custom_BUFF.Custom_array.CustomCCV_Data[0])
//		{
//			Dataout_Q=R_Custom_BUFF.Custom_array.CustomCCV_Data[0];
//			Disp_Custom_Vout(Dataout_Q);
//		}
	}
}
//
static	void 	Set_CCT_Custom_Data_update(void)
{
	if(B_Out_Yes)
	{
//		if(Dataout_Q!=CCT_BUFF[R_Custom_I_Set])
//		{
//			Dataout_Q=CCT_BUFF[R_Custom_I_Set];
//			Disp_Set_Tempe(Dataout_Q);
//		}
		MP3_DisWave();
		if(!R_Interface_maintain_Time)
		{
			R_Interface_maintain_Time=4;
			Vape_MP3_Beat();
		}
	}
	else
	{
		if(!B_Custom_Disp || B_Display_refresh)
		{
			if(DisWave(CCT_BUFF,CCT_BUFF,CCT_Custom_Max,CCT_Custom_Min,100))
			{
				B_Custom_Disp=1;
				B_Display_refresh=0;
			}
		}
//		if(Dataout_Q!=CCT_BUFF[0])
//		{
//			Dataout_Q=CCT_BUFF[0];
//			Disp_Set_Tempe(Dataout_Q);
//		}
	}
}

///////////////////////////////////////////////////


//工作窗口更新
void	Watt_MODE_windows(void);
void	Voltage_MODE_windows(void);
void	Bypass_MODE_windows(void);
void	Temp_MODE_windows(void);
void	TCR_MODE_windows(void);
void	Custom_MODE_windows(void);
void	Main_windows(void)
{
//	u8	i;
	B_Mode_selection_EN=1;
	Dataout_Q=0xF000;
	Vape_Tim_angle_I=0;
	R_Interface_maintain_Time=0;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	draw_Bmp_ex(d_MainBottomBelow,0,258);
	if(R_Work_mode==d_Watt_mode)
		Watt_MODE_windows();
	else if(R_Work_mode==d_Voltage_mode)
		Voltage_MODE_windows();
	else if(R_Work_mode==d_Bypass_mode)
		Bypass_MODE_windows();
	else if(R_Work_mode==d_Temp_mode)
		Temp_MODE_windows();
	else if(R_Work_mode==d_TCR_mode)
		TCR_MODE_windows();
	else if(R_Work_mode==d_Custom_mode)
		Custom_MODE_windows();
	else if(R_Work_mode==d_CustomVolt_mode)
		CCV_Custom_MODE_windows();
	else if(R_Work_mode==d_CustomTemp_mode)
		CCT_Custom_MODE_windows();
	else if(R_Work_mode==d_SPP_mode)
		SPP_MODE_windows();

	Res_parts();
	OutI_parts();
	Lock_parts();
	Vape_Time_parts();
	Vape_number_parts();
	Batt_parts();
	RTC_parts();
	Disp_Main();
	PanelTurnOnDisplay();
}
///
void (*Return_windows)(void);
static	void	Main_operation(void)
{
	u16	a;
	u8	bujin;
	if(ADDSUB_LOCK_GOTO(1))
	{
		Lock_parts();
	}
	else if(!B_ADDSUB_LOCK)
	{
		Main_menu_GOTO();
//		if(R_key_anxia==KEY_ADD_SUB)
//		{
//			R_UI_Theme++;
//			if(R_UI_Theme>4)
//				R_UI_Theme=0;
//			Main_windows();
//		}
//		else
		{
			if(R_Work_mode==d_Watt_mode || R_Work_mode==d_SPP_mode)
			{
				if(R_User_Watt_Set>1000 || (R_User_Watt_Set==1000 && R_key_anxiaOpen==KEY_ADD))
				{
					bujin=10;
				}
				else
				{
					if(R_User_Watt_Set%10==0 && (R_key_anzhu==KEY_ADD || R_key_anzhu==KEY_SUB))
						bujin=10;
					else
						bujin=1;
				}
				a=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_User_Watt_Set,KEY_ADD,KEY_SUB,d_User_Watt_max,d_User_Watt_min,bujin,0,30);
				if(a!=R_User_Watt_Set)
				{
					R_User_Watt_Set=a;
					Disp_Data_Arc();
				}
			}
			else if(R_Work_mode==d_Voltage_mode)
			{
				if(R_User_Vout_Set%10==0 && (R_key_anzhu==KEY_ADD || R_key_anzhu==KEY_SUB))
					bujin=10;
				else
					bujin=1;
				a=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_User_Vout_Set,KEY_ADD,KEY_SUB,d_User_Vout_max,d_User_Vout_min,bujin,0,20);
				if(a!=R_User_Vout_Set)
				{
					R_User_Vout_Set=a;
					Disp_Data_Arc();
				}
			}
			else if(R_Work_mode==d_Temp_mode || R_Work_mode==d_TCR_mode)
			{
				if(R_Temp_metric==C_metric)
				{
					a=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_User_Temp_Set_C,KEY_ADD,KEY_SUB,d_User_TempC_max,d_User_TempC_min,5,1,20);
					if(a!=R_User_Temp_Set_C)
					{
						if(a==d_User_TempC_max	&& R_User_Temp_Set_C==d_User_TempC_min)
						{
							R_Temp_metric=F_metric;
							R_User_Temp_Set_F=d_User_TempF_max;
							Temp_metric_parts();
						}
						else	if(a==d_User_TempC_min	&& R_User_Temp_Set_C==d_User_TempC_max)
						{
							R_Temp_metric=F_metric;
							R_User_Temp_Set_F=d_User_TempF_min;
							Temp_metric_parts();
						}
						else
						{
							R_User_Temp_Set_C=a;
							R_User_Temp_Set_F=R_User_Temp_Set_C*9/5+32;
							if(R_User_Temp_Set_F<d_User_TempF_min)
								R_User_Temp_Set_F=d_User_TempF_min;
							else	if(R_User_Temp_Set_F>d_User_TempF_max)
								R_User_Temp_Set_F=d_User_TempF_max;
						}
						Disp_Data_Arc();
					}
				}
				else
				{
					a=KEY_R_ADD_SUB(&R_key_anxiaOpen,R_User_Temp_Set_F,KEY_ADD,KEY_SUB,d_User_TempF_max,d_User_TempF_min,10,1,20);
					if(a!=R_User_Temp_Set_F)
					{
						if(a==d_User_TempF_max	&& R_User_Temp_Set_F==d_User_TempF_min)
						{
							R_Temp_metric=C_metric;
							R_User_Temp_Set_C=d_User_TempC_max;
							Temp_metric_parts();
						}
						else	if(a==d_User_TempF_min	&& R_User_Temp_Set_F==d_User_TempF_max)
						{
							R_Temp_metric=C_metric;
							R_User_Temp_Set_C=d_User_TempC_min;
							Temp_metric_parts();
						}
						else
						{
							R_User_Temp_Set_F=a;
							R_User_Temp_Set_C=(R_User_Temp_Set_F-32)*5/9;
							if(R_User_Temp_Set_C<d_User_TempC_min)
								R_User_Temp_Set_C=d_User_TempC_min;
							else	if(R_User_Temp_Set_C>d_User_TempC_max)
								R_User_Temp_Set_C=d_User_TempC_max;
						}
						Disp_Data_Arc();
					}
				}
			}
			if(R_key_keep==KEY_ADD_SUB)
			{
				Return_windows=Main_interface;
				if(R_Work_mode==d_Watt_mode)
				{
					Windows_Switch(VW_SET_menu_interface);
				}
				else if(R_Work_mode==d_Custom_mode)
				{
					Windows_Switch(Custom_Data_Set_interface);
				}
				else if(R_Work_mode==d_CustomVolt_mode)
				{
					Windows_Switch(CCV_Custom_Data_Set_interface);
				}
				else if(R_Work_mode==d_CustomTemp_mode)
				{
					Windows_Switch(CCT_Custom_Data_Set_interface);
				}
				if(R_Work_mode==d_Temp_mode || R_Work_mode==d_TCR_mode)
				{
					Windows_Switch(TCR_Data_Set_interface);
				}
			}
		}
	}
	if(R_Work_mode==d_Watt_mode || R_Work_mode==d_SPP_mode)
	{
		if(B_SMART_RES_Update)
		{
			B_SMART_RES_Update=0;
			Disp_Data_Arc();
		}
	}
}
//显示RTC时钟
static	void	Disp_RTC(void)
{
	GUI_MEMDEV_Handle hMem;
	if(Disp_RTC_Hour!=RTC_Time.Hours)
	{
		Disp_RTC_Hour=RTC_Time.Hours;
		hMem = GUI_MEMDEV_CreateEx(182,7,22,14,GUI_MEMDEV_NOTRANS);
		GUI_MEMDEV_Select(hMem);
		GUI_SetBkColor(GUI_BLACK);
		GUI_Clear();
		GUI_SetColor(0xB5863C);
		GUI_SetFont(&GUI_FontArial22);
		GUI_DispDecAt(Disp_RTC_Hour,182,3,2);
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_WriteAt(hMem,182,7);//
		GUI_MEMDEV_Delete(hMem);
	}
	if(Disp_RTC_Minute!=RTC_Time.Minutes)
	{
		Disp_RTC_Minute=RTC_Time.Minutes;
		hMem = GUI_MEMDEV_CreateEx(210,7,22,14,GUI_MEMDEV_NOTRANS);
		GUI_MEMDEV_Select(hMem);
		GUI_SetBkColor(GUI_BLACK);
		GUI_Clear();
		GUI_SetColor(0xB5863C);
		GUI_SetFont(&GUI_FontArial22);
		GUI_DispDecAt(Disp_RTC_Minute,210,3,2);
		GUI_MEMDEV_Select(0);
		GUI_MEMDEV_WriteAt(hMem,210,7);//
		GUI_MEMDEV_Delete(hMem);
	}
}
//
static	void	Disp_Main(void)
{
	Display_BAT();
	Atomizer_Res_update();
	Disp_Vape_number();
	Disp_Vape_Time();
	Disp_RTC();
	switch((u8)R_Work_mode)
	{
		case	d_Watt_mode:
			Set_Watt_update();
			Vout_update();
			Change_Arc_angle_State();
		/*AUTO_MODE_parts();*/break;
		case	d_Voltage_mode:
			Set_Volt_update();
			Wout_update();
			Change_Arc_angle_State();
		/*AUTO_MODE_parts();*/break;
		case	d_Bypass_mode:
			//Set_Volt_update();
			Vout_update();
			Change_Arc_angle_State();
		/*AUTO_MODE_parts();*/break;
		case	d_Custom_mode:
			Set_Custom_Data_update();
			Wout_update();
		/*AUTO_MODE_parts();*/break;
		case	d_CustomVolt_mode:
			Set_CCV_Custom_Data_update();
			Vout_update();
		/*AUTO_MODE_parts();*/break;
		case	d_CustomTemp_mode:
			Set_CCT_Custom_Data_update();
			Wout_update();
		/*AUTO_MODE_parts();*/break;
		case	d_Temp_mode:
			Set_Tempe_update();
			Wout_update();
			Change_Arc_angle_State();
		/*AUTO_MODE_parts();*/break;
		case	d_TCR_mode:
			Set_Tempe_update();
			Wout_update();
			Change_Arc_angle_State();
		/*AUTO_MODE_parts();*/break;
		case	d_SPP_mode:
			Set_SPPWatt_update();
			Vout_update();
			SP_Arc_angle_State();break;
	}
}

u8	R_Auto_Locked_KEY=d_Auto_Locked_KEY_Tim;
//自动锁触摸处理
void	Auto_Locked(void)
{
	if(R_Bright_screen_TimeMAX-R_Bright_screen_Time<3)
	{
		R_Auto_Locked_KEY=d_Auto_Locked_KEY_Tim;
	}
	if(!R_Auto_Locked_KEY)
	{
		if(!B_ADDSUB_LOCK)
		{
			B_ADDSUB_LOCK=1;
			Lock_parts();
		}
	}
}

u8	B_SET_Key_release;
void	Main_interface(void)
{
	u8	BL=0;
	if(!B_OLED_BL && key_value==KEY_M)
		BL=1;
	Key_Light_screen();
	if(B_OLED_BL && BL==1)
	{
		BL=2;
		B_Key_release=0;
	}
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		B_System_off=d_System_Normal;
		if(!R_Auto_Locked_KEY)
			B_ADDSUB_LOCK=1;
		Main_windows();
		R_Auto_Locked_KEY=d_Auto_Locked_KEY_Tim;

		if(!B_SET_Key_release && BL!=2)
			B_Key_release=1;
		B_SET_Key_release=0;
		R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_access:{//usb插入
			Windows_Interrupt_Push(Battery_charging_interface);
		};break;
		case	Short_circuit:{//短路
			Windows_Interrupt_Push(Warning_interface);
			Warning_Windows=Short_circuit_windows;
		};break;
		case	Open_circuit:{//开路
			Windows_Interrupt_Push(Warning_interface);
			Warning_Windows=Open_circuit_windows;
		};break;
		case	Low_Resistance:{//低阻值
			Windows_Interrupt_Push(Warning_interface);
			Warning_Windows=Low_ATOMIZER_windows;
		};break;
		case	High_Resistance:{//高阻值
			Windows_Interrupt_Push(Warning_interface);
			Warning_Windows=HIGH_ATOMIZER_windows;
		};break;
		case	Low_Battery:{//低电量
			Windows_Interrupt_Push(Warning_interface);
			Warning_Windows=Low_Battery_windows;
		};break;
		case	Smoking_timeout:{//吸烟超时
			Windows_Interrupt_Push(Warning_interface);
			Warning_Windows=Smoking_timeout_windows;
		};break;
		case	PCB_Overheated:{//PCB过热
			Windows_Interrupt_Push(Warning_interface);
			Warning_Windows=PCB_Overheated_windows;
		};break;
		case	USB_anomaly:{//USB异常
			Windows_Interrupt_Push(USB_Warning_interface);
		};break;
		default:{
			Vibrate_EN(!B_ADDSUB_LOCK);
			Main_operation();
			System_off_GOTO();
//			Key_smoke();
//			Screen_smoking_GOTO();
			Atomizer_inquiry_GOTO(1);
//			Firmware_Tim_GOTO();
//			fuwei_Tim_GOTO();
			GOTO_Screensaver_interface(1);
			Screen_GOTO_charging();
			Auto_Locked();
			Batt_error_GOTO();
		};
	}
	Disp_Main();
	R_Skinning_mode=Skinning_mode_null;
}


//void	Screen_smoking_interface(void)
//{
//	switch((u8)R_Skinning_mode)
//	{
//		case	Skinning_init:{//初始化
//			B_System_off=d_System_Normal;
//			if(B_OLED_BL)
//			{
//				PanelTurnOffDisplay();
//				BL_PanelTurnOffDisplay();
//			}
//			B_Key_release=0;
//			R_Bright_screen_TimeMAX=20;
//			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
//		};break;
//		case	USB_anomaly:{//USB异常
//			Disp_windows_QQ=Main_interface;
//			Windows_Switch(USB_Warning_interface);
//		};break;
//		default:{
////			Key_smoke();
//			if(B_Out_Yes)
//			{
//				R_Bright_screen_Time=R_Bright_screen_TimeMAX;
//			}
//			if(R_key_3C == KEY_M)
//			{
//				BL_PanelTurnOnDisplay();
//				Windows_Switch(Main_interface);
//			}
//			System_off_GOTO();
//			if(Atomizer_inquiry_GOTO(0))
//			{
//				Disp_windows_QQ=Main_interface;
//			}
//			if(B_BAT_Charge)
//			{
//				Disp_windows_QQ=Main_interface;
//				Windows_Switch(Battery_charging_interface);
//			}
//			Batt_error_GOTO();
//		};
//	}
//	R_Skinning_mode=Skinning_mode_null;
//}



/////////////


