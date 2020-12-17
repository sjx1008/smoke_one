
#include	"main_2.h"
#include	"OUT_Public.h"
#include 	"CurveCCV_Mode_control.h"

static	u8	CCV_Tim;
/////
static	void CCV_yule(void);
void	Custom_CCV_Output_control(void);
void	Custom_CCV_mode_int(void)
{
	R_PowerMAX=R_PowerMAXMAX;
	R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCV_Data;
	R_Custom_I_Set=0;			//正在输出的第I个点
	R_Custom_tim=0; 			//两点之间的的时间段

	R_Out_W_Set=R_Custom_Set[0]*R_Custom_Set[0]*10/R_Res_average;
	if(R_Out_W_Set>R_PowerMAX)
	{
		R_Out_V_Set=sqrt_16(R_PowerMAX*R_Res_average/10);
	}
	else
	{
		R_Out_V_Set=R_Custom_Set[0];
	}
	CCV_Tim=0;
	Output_control_program=Custom_CCV_Output_control;
	CCV_yule();
}

static	void CCV_yule(void)
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
		if(B)
			Count_Vout(R_Res_average);
		Vout_adjust(10);
		Delay_Nus(5);
	}
	R_Read_Rtim=R;
}

//////////////
void	Custom_CCV_Output_control(void)
{
	u16		V_Set;
//	u16		Custom_A,Custom_B;
	if(R_Custom_I_Set<=d_Custom_I_MAX)
	{
		if(CCV_Tim!=R_Custom_tim)
		{
			CCV_Tim=R_Custom_tim;
			R_Out_V_Set=R_Custom_Set[R_Custom_I_Set];
//			Custom_A=R_Custom_Set[R_Custom_I_Set+1];
//			Custom_B=R_Custom_Set[R_Custom_I_Set];
//			if(Custom_A>Custom_B)
//				R_Out_V_Set=(Custom_A-Custom_B)*R_Custom_tim/50+Custom_B;
//			else
//				R_Out_V_Set=Custom_B-(Custom_B-Custom_A)*R_Custom_tim/50;
			R_Out_W_Set=R_Out_V_Set*R_Out_V_Set*10/R_Res_average;
			if(R_Out_W_Set>R_PowerMAX)
			{
				R_Out_V_Set=sqrt_16(R_PowerMAX*R_Res_average/10);
			}
		}
	}
	if(Power_down_control())
	{
		V_Set=sqrt_16(R_PowerMAX*R_Res_average/10);
		if(R_Out_V_Set>V_Set)
		{
			R_Out_V_Set=V_Set;
		}
	}
	Vout_adjust(1);
}



