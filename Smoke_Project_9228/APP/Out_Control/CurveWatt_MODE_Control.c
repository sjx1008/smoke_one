
#include	"main_2.h"
#include	"OUT_Public.h"
#include "CurveWatt_MODE_Control.h"

////////////////功率输出控制程序
//用户设定值
u16	*R_Custom_Set;			//指向输出曲线
u8	R_Custom_I_Set;			//正在输出的第I个点
u8	R_Custom_tim; 			//两点之间的的时间段

void	Custom_Output_control(void);
static	void Custom_yule(void);
void	Custom_mode_int(void)
{
	R_PowerMAX=R_PowerMAXMAX;
	R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCW_Data;
	R_Custom_I_Set=0;			//正在输出的第I个点
	R_Custom_tim=0; 			//两点之间的的时间段
	Output_control_program=Custom_Output_control;
	Custom_yule();
}
//ԤɈ
static	void Custom_yule(void)
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
		if(R_real_WOUT>=R_Custom_Set[0]*85 || R_real_BAT<=d_Bat_OUT_Volt_min+5 || R_real_VOUT>=d_User_Vout_max-30 || R_real_IOUT>=(d_User_Iout_max_x100*8/10))
			break;
		B=Power_down_control();
		Count_Wout();
		Wout_adjust(10);
		Delay_Nus(5);
	}
	R_Read_Rtim=R;
}

////自定义模式输出
void	Custom_Output_control(void)
{
//	u16		Custom_A,Custom_B;
	if(Power_down_control())
	{
		Count_Wout();
	}
	if(R_Custom_I_Set<=d_Custom_I_MAX)
	{
		R_Out_W_Set=R_Custom_Set[R_Custom_I_Set]*100;
//		Custom_A=R_Custom_Set[R_Custom_I_Set+1];
//		Custom_B=R_Custom_Set[R_Custom_I_Set];
//		if(Custom_A>Custom_B)
//		{
//			R_Out_W_Set=(Custom_A-Custom_B)*R_Custom_tim*2+Custom_B*100;
//		}
//		else
//		{
//			R_Out_W_Set=Custom_B*100-(Custom_B-Custom_A)*R_Custom_tim*2;
//		}
		Count_Wout();
	}
	else
	{
		R_Out_W_Set=R_Custom_Set[d_Custom_I_MAX]*100;
		Count_Wout();
	}
	Wout_adjust(1);
}




///////温控曲线模式
//void	Custom_CCT_Output_control(void);
//void	Custom_CCT_mode_int(void)
//{
//	if(R_Temp_metric==C_metric)
//		R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCT_C_Data[R_Atomizer];
//	else
//		R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCT_F_Data[R_Atomizer];
//	R_T_Gradient_out=Atomizer_Pointer[R_Atomizer]->Gradient;
//
//	R_Custom_I_Set=0;			//正在输出的第I个点
//	R_Custom_tim=0; 			//两点之间的的时间段
//
//	R_PowerMAX=R_User_Temp_Watt_Max*10;
//	if(R_PowerMAX<R_PowerMAXMAX)
//		R_PowerMAXMAX=R_PowerMAX;
//	else
//		R_PowerMAX=R_PowerMAXMAX;
//	R_Temp_PowerMAX=R_PowerMAX;
//	R_Out_W_Set=R_PowerMAX/3;
//	R_Temp_compensate=0;
//	PID_init();
//	Output_control_program=Custom_CCT_Output_control;
//}

//////////////////温度输出控制程序
//void	Custom_CCT_Output_control(void)
//{
//	u16		Custom_A,Custom_B;
//	if(R_Custom_I_Set<9)
//	{
//		Custom_A=R_Custom_Set[R_Custom_I_Set+1];
//		Custom_B=R_Custom_Set[R_Custom_I_Set];
//		if(Custom_A>Custom_B)
//			R_Out_Temp_Set=(Custom_A-Custom_B)*R_Custom_tim/50+Custom_B;
//		else
//			R_Out_Temp_Set=Custom_B-(Custom_B-Custom_A)*R_Custom_tim/50;
//
//		if(R_Temp_metric!=C_metric)
//		{
//			R_Out_Temp_Set=(R_Out_Temp_Set-32)*5/9;
//		}
//	}
//	if(B_load_OK)
//	{
//		B_load_OK=0;
//		Tempe_Compensation_calculation();
//		PID_realize(R_Out_Temp_Set,R_real_Temp);
//		Count_Wout();
//		F_Average_Temp();
//	}

//	if(Power_down_control())
//	{
//		Count_Wout();
//	}
//	Wout_adjust();
//}



