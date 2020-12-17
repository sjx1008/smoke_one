#include	"TFT_Init.h"
#include	"TFT_Init.h"
#include "TFT_Drive.h"
#include "APP_KEY.h"
#include	"APP_Delay.h"
#include	"gpio.h"
#include "APP_PWM_int.h"
#include "Flahs_Driver.h"
#include "WM_Disp.h"
#include "Brightness_AUTO.h"
#define	d_Bring_AutoMAX		10

u8	Bring_AUTO_Enable=0;
//初始化标志
static	u8	B_Bring_AUTO_Init=1;
//当前的档位
static	u8	R_LUX_VIP=9;
static	u8	R_LUX_VIP_Q=9;
static	u8	R_Bring_VIP=9;

//AD值区间
static	uc16	Bring_AUTO_ADC_BUFF[d_Bring_AutoMAX]={409,819,1228,1638,2048,2457,2867,3276,3686,4030};
//亮度档位值
static	uc8	Bring_AUTO_BUFF[d_Bring_AutoMAX]={10,20,30,40,50,60,70,80,90,100};

//读取ADCBUFF
#define	LUX_ADC_I_MAX	10
static	u16	LUX_ADC_DataBuff[LUX_ADC_I_MAX];
//读取ADC的第I个
static	u8	LUX_ADC_I=0;

//读取ADC间隔时间
u8	R_LUX_ADC_Tim=0;

//滤波处理
static	u8	R_LUXADD_LB=0;
static	u8	R_LUXSUB_LB=0;

//初始化延时时间
#define	d_Bring_Init_Tim	1		//10ms
//正常延时时间
#define	d_Bring_Tim	50				//100ms


//打开自动亮度调节
void	Bring_AUTO_EN(void)
{
	Bring_AUTO_Enable=1;
	Bring_AUTO_Init();
}
//自动调节亮度重新初始化
void	Bring_AUTO_Init(void)
{
	if(!Bring_AUTO_Enable)
		return;
	if(B_Bring_AUTO_Init==0)
	{
		B_Bring_AUTO_Init=1;
		R_LUX_ADC_Tim=d_Bring_Init_Tim;
		LUX_ADC_I=0;
	}
}

//求平均数
static	u16	Data_Average(u16* R,u8	max)
{
	u32	a=0;
	u8	i;
	for(i=0;i<max;i++)
	{
		a+=R[i];
	}
	return	(a/max);
}
//返回亮度等级
static	u8	Ret_Bring_VIP(u16	Dat)
{
	u8	i;
	for(i=0;i<d_Bring_AutoMAX-1;i++)
	{
		if(Dat<Bring_AUTO_ADC_BUFF[i])
			break;
	}
	return	i;
}

void	Bring_AUTO_Testing(void)
{
	if(!Bring_AUTO_Enable)
		return;
	if(B_OLED_BL&&!R_LUX_ADC_Tim && (!(key_value&KEY_M)))
	{
		u16	ADdata;
		u8	Vip;
		LUX_ADC_DataBuff[LUX_ADC_I]=Read_LUX_Data();
		if(B_Bring_AUTO_Init)//自动亮度调节初始化
		{
			R_LUX_ADC_Tim=d_Bring_Init_Tim;
			if(LUX_ADC_I==(LUX_ADC_I_MAX-1))
			{
				B_Bring_AUTO_Init=0;
				R_LUX_ADC_Tim=d_Bring_Tim;
				ADdata=Data_Average(LUX_ADC_DataBuff,LUX_ADC_I_MAX);
				R_LUX_VIP=Ret_Bring_VIP(ADdata);
				R_Bring_VIP=R_LUX_VIP;
				TFT_SET_BL_Brightness(Bring_AUTO_BUFF[R_Bring_VIP]);
			}
		}
		else//正常调节
		{
			R_LUX_ADC_Tim=d_Bring_Tim;
			ADdata=Data_Average(LUX_ADC_DataBuff,LUX_ADC_I_MAX);
			Vip=Ret_Bring_VIP(ADdata);
			if(Vip+1==R_LUX_VIP_Q && ADdata+40>Bring_AUTO_ADC_BUFF[Vip])
				Vip=R_LUX_VIP_Q;
			else if(Vip==R_LUX_VIP_Q+1 && ADdata<Bring_AUTO_ADC_BUFF[Vip-1]+40)
				Vip=R_LUX_VIP_Q;
			if(Vip>R_LUX_VIP)
			{
				if(Vip>R_LUX_VIP+1)
				{
					R_LUXADD_LB++;
				}
				if(R_LUXADD_LB<10)
				{
					R_LUXADD_LB++;
				}
				else
				{
					R_Bring_VIP+=Vip-R_LUX_VIP;
					if(R_Bring_VIP>=d_Bring_AutoMAX)
						R_Bring_VIP=d_Bring_AutoMAX-1;
					TFT_SET_BL_Brightness(Bring_AUTO_BUFF[R_Bring_VIP]);
					R_LUX_VIP=Vip;
				}
			}
			else	if(Vip<R_LUX_VIP)
			{
				if(Vip+1<R_LUX_VIP)
				{
					R_LUXADD_LB++;
				}
				if(R_LUXSUB_LB<10)
				{
					R_LUXSUB_LB++;
				}
				else
				{
					R_Bring_VIP+=Vip-R_LUX_VIP;
					if((s8)R_Bring_VIP<0)
						R_Bring_VIP=0;
					TFT_SET_BL_Brightness(Bring_AUTO_BUFF[R_Bring_VIP]);
					R_LUX_VIP=Vip;
				}
			}
			else
			{
				R_LUXADD_LB=0;
				R_LUXSUB_LB=0;
			}
		}
		LUX_ADC_I++;
		if(LUX_ADC_I>=LUX_ADC_I_MAX)
			LUX_ADC_I=0;
	}
}


//返回当前亮度值对应的等级
void	Set_Ret_Bring_VIP(void)
{
	u8	i;
	for(i=0;i<d_Bring_AutoMAX-1;i++)
	{
		if(R_Screen_brightness<=Bring_AUTO_BUFF[i])
			break;
	}
	R_Bring_VIP=i;
}


