#include	"main_2.h"
#include	"OUT_Public.h"
#include "Watt_MODE_Control.h"
/*
2018/07/18
T18秒吸程序改进：
1）秒吸启动的第一个100MS的功率<=110W时,
   秒启动方式：秒吸100MS：设置功率+60%， 100MS：设置功率+40%
1）秒吸启动的第一个100MS的功率>110W时,
   秒启动方式：秒吸100MS：设置功率 + 30W， 100MS：设置功率 + 15W
*/
////////////////功率输出控制程序
//用户设定值
u8	B_SMART_mode=0;
u16	R_User_Watt_Set=50;				//设定瓦数				//100mW			00.0
Watt_Strength		R_Watt_Strength=NOR_Strength;		//输出强度设置

u16	R_Strength_Watt;

void	Watt_Output_control(void);
static	void 	Watt_yule(void);
void	Watt_mode_int(void)
{
	if(R_Watt_Strength==HIGH_Strength)
	{
		R_Out_W_Set=R_User_Watt_Set*1400/100;
	}
	else if(R_Watt_Strength==NOR_Strength)//第一个100毫秒
	{
		if(R_User_Watt_Set<=1000 && R_Res_average<=800)
		  R_Out_W_Set=R_User_Watt_Set*1600/100;
		else
			R_Out_W_Set=R_User_Watt_Set*1400/100;
	}
	else
	{
		R_Out_W_Set=R_User_Watt_Set*10;
	}
	if(R_Out_W_Set<R_PowerMAXMAX)
		R_PowerMAXMAX=R_Out_W_Set;
	R_PowerMAX=R_PowerMAXMAX;
	Output_control_program=Watt_Output_control;

	if(R_Watt_Strength==SOFT_Strength)
		R_Out_W_Set=R_User_Watt_Set*800/100;

	R_Strength_Watt=R_Out_W_Set;
	Watt_yule();
}

//预热
static	void Watt_yule(void)
{
	u8	B;
	u16	R;
	B=0;
	R=R_Read_Rtim;
	R_Read_Rtim=4;
	while(!B && R_Read_Rtim)
	{
		R_real_BAT=ReadBATz_Data();
		ReadLoad_Data();
		R_real_VOUT=R_ReadLoad_outV;
		R_real_IOUT=R_ReadLoad_outI;
		if(R_real_IOUT>d_OVER_Iout_max_x100)
		{
			Fault_handling(Short_circuit);
		}
		R_real_WOUT=R_real_VOUT*R_real_IOUT/100;
		if(R_real_WOUT>=R_Out_W_Set*85/100 || R_real_BAT<=d_Bat_OUT_Volt_min+5 || R_real_VOUT>=d_User_Vout_max-30 || R_real_IOUT>=(d_User_Iout_max_x100*8/10))
			break;
		B=Power_down_control();
		Count_Wout();
		Wout_adjust(10);
		Delay_Nus(5);
	}
	R_Read_Rtim=R;
}

void	Watt_Output_control(void)
{
	if(R_Watt_Strength==HIGH_Strength)
	{
		if(B_AUOT_MODE)
		{
			if(R_Smoke_Tim10ms>300)
			{
				R_Out_W_Set=R_User_Watt_Set*8;
			}
			else	if(R_Smoke_Tim10ms>130)
			{
				R_Out_W_Set=R_User_Watt_Set*(1960-2*R_Smoke_Tim10ms)/170;
			}
			else	if(R_Smoke_Tim10ms>60)
			{
				R_Out_W_Set=R_User_Watt_Set*10;
			}
			else	if(R_Smoke_Tim10ms>30)
			{
				R_Out_W_Set=R_User_Watt_Set*(540-4*R_Smoke_Tim10ms)/30;
			}
		}
		else
		{
			if(R_Smoke_Tim10ms>60)
			{
				R_Out_W_Set=R_User_Watt_Set*10;
			}
			else	if(R_Smoke_Tim10ms>30)
			{
				R_Out_W_Set=R_User_Watt_Set*(540-4*R_Smoke_Tim10ms)/30;
			}
		}
	}
	else if(R_Watt_Strength==NOR_Strength)
	{
		if(B_AUOT_MODE)
		{
			if(R_User_Watt_Set<=1000 && R_Res_average<=800)
		  {
				if(R_Smoke_Tim10ms>=300)
				{
					R_Out_W_Set=R_User_Watt_Set*8;
				}
				else	if(R_Smoke_Tim10ms>=130)
				{
					R_Out_W_Set=R_User_Watt_Set*(1960-2*R_Smoke_Tim10ms)/170;
				}
				else if(R_Smoke_Tim10ms>=20)
				{
					R_Out_W_Set=R_User_Watt_Set*10;
				}
				else if(R_Smoke_Tim10ms>=10)
				{
					R_Out_W_Set=R_User_Watt_Set*14;
				}
			}
			else
			{
				if(R_Smoke_Tim10ms>=300)
				{
					R_Out_W_Set=R_User_Watt_Set*8;
				}
				else	if(R_Smoke_Tim10ms>=130)
				{
					R_Out_W_Set=R_User_Watt_Set*(1960-2*R_Smoke_Tim10ms)/170;
				}
				else if(R_Smoke_Tim10ms>=30)
				{
					R_Out_W_Set=R_User_Watt_Set*10;
				}
			}
		}
		else
		{
			if(R_User_Watt_Set<=1000 && R_Res_average<=800)
		  {
				if(R_Smoke_Tim10ms>=20)
				{
					R_Out_W_Set=R_User_Watt_Set*10;
				}
				else if(R_Smoke_Tim10ms>=10)
				{
					R_Out_W_Set=R_User_Watt_Set*14;
				}
			}
			else
			{
				if(R_Smoke_Tim10ms>=30)
				{
					R_Out_W_Set=R_User_Watt_Set*10;
				}
			}
		}
	}
	else
	{
		if(B_AUOT_MODE)
		{
			if(R_Smoke_Tim10ms>300)
			{
				R_Out_W_Set=R_User_Watt_Set*8;
			}
			else	if(R_Smoke_Tim10ms>130)
			{
				R_Out_W_Set=R_User_Watt_Set*(1960-2*R_Smoke_Tim10ms)/170;
			}
			else	if(R_Smoke_Tim10ms>=30)
				R_Out_W_Set=R_User_Watt_Set*10;
		}
		else
		{
			if(R_Smoke_Tim10ms>=30)
				R_Out_W_Set=R_User_Watt_Set*10;
		}
	}
	if(R_Out_W_Set>d_User_Watt_max_x10)
		R_Out_W_Set=d_User_Watt_max_x10;
	Power_down_control();
	Count_Wout();
	Wout_adjust(1);
}



