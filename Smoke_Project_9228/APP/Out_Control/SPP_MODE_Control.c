#include	"main_2.h"
#include	"OUT_Public.h"
#include "SPP_MODE_Control.h"

////////////////功率输出控制程序

void	SPP_Output_control(void);
static	void 	SPP_yule(void);
void	SPP_mode_int(void)
{
	if(R_User_Watt_Set<=1000 && R_Res_average<=800)
		R_Out_W_Set=R_User_Watt_Set*1600/100;
	else
		R_Out_W_Set=R_User_Watt_Set*1400/100;
	if(R_Out_W_Set<R_PowerMAXMAX)
		R_PowerMAXMAX=R_Out_W_Set;
	R_PowerMAX=R_PowerMAXMAX;

	Output_control_program=SPP_Output_control;
	SPP_yule();
}

//预热
static	void SPP_yule(void)
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
		if(R_Res_average<50)
			Wout_adjust(1);
		else
			Wout_adjust(5);
		Delay_Nus(5);
	}
	R_Read_Rtim=R;
}

void	SPP_Output_control(void)
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
	if(R_Out_W_Set>d_User_Watt_max_x10)
		R_Out_W_Set=d_User_Watt_max_x10;
	Power_down_control();
	Count_Wout();
	Wout_adjust(1);
}



