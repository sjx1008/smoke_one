
#include	"main_2.h"
#include	"OUT_Public.h"
#include "Bypass_MODE_Control.h"
////////////////功率输出控制程序
//用户设定值

void	Bypass_Output_control(void);
static	void Voltage_yule(void);
void	Bypass_mode_int(void)
{
//	R_Out_V_Set=sqrt_16(R_PowerMAXMAX*R_Res_average/10);
//
//	if(R_Out_V_Set>400)
	{
		R_Out_V_Set=460;
	}
	Output_control_program=Bypass_Output_control;
	Voltage_yule();
}

//预热
static	void Voltage_yule(void)
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
		if(R_real_VOUT>=R_Out_V_Set*85/100  || R_real_BAT<=d_Bat_OUT_Volt_min+5 || R_real_WOUT>=d_User_Watt_max_x10*8/10 || R_real_IOUT>=(d_User_Iout_max_x100*8/10))
			break;
		B=Power_down_control();
		Vout_adjust(10);
		Delay_Nus(5);
	}
	R_Read_Rtim=R;
}

////////////////Bypass输出控制程序
void	Bypass_Output_control(void)
{
	if(R_Smoke_Tim10ms>=50)
	{
		R_Out_V_Set=420;
	}
	if(R_real_BAT<d_Bat_OUT_Volt_min)
	{
		if(R_Lbat_LB<10)
		{
			R_Lbat_LB++;
		}
		else
		{
			Fault_handling(Low_Battery);
		}
	}
	else
	{
		R_Lbat_LB=0;
	}
	Vout_adjust(1);
//		if(R_real_VOUT+2<R_Out_V_Set)
//		{
//			if(PWM_data<OUT_PWM_Period)
//			{
//				PWM_data++;
//				PWM_Wdata(&PWM_data);
//			}
//		}
}



