
#include	"main_2.h"
#include	"OUT_Public.h"
#include 	"CurveCCT_Mode_control.h"

static	u16   temp_auto_set = 0;

/////温控曲线模式
void	Custom_CCT_Output_control(void);
void	Custom_CCT_mode_int(void)
{
	if(R_Temp_metric==C_metric)
	{
		switch((u8)R_Atomizer)
		{
			case	0:	R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data;break;
			case	1:	R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data;break;
			default:	R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data;break;
		}
	}
	else
	{
		switch((u8)R_Atomizer)
		{
			case	0:	R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data;break;
			case	1:	R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data;break;
			default:	R_Custom_Set=R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data;break;
		}
	}
	R_T_Gradient_out=Atomizer_Pointer[R_Atomizer]->Gradient;

	R_Custom_I_Set=0;			//正在输出的第I个点
	R_Custom_tim=0; 			//两点之间的的时间段

	R_PowerMAX=Atomizer_Pointer[R_Atomizer]->WattsMAX*100;
	if(R_PowerMAX<R_PowerMAXMAX)
		R_PowerMAXMAX=R_PowerMAX;
	else
		R_PowerMAX=R_PowerMAXMAX;
	R_Temp_PowerMAX=R_PowerMAX;
	if(R_Temp_metric==C_metric)
	{
		R_Out_Temp_Set=R_Custom_Set[0];
	}
	else
	{
		R_Out_Temp_Set=(R_Custom_Set[0]-32)*5/9;
	}
	if(B_AUOT_MODE)
	{
		if(R_Out_Temp_Set < 220)
		{
		  temp_auto_set = 10000 - 50*(220-R_Out_Temp_Set);
		}
    else
		{
		  temp_auto_set = 10000;
		}
	}
	else
	{
	  temp_auto_set = 10000;
	}
	R_Out_W_Set=Atomizer_Pointer[R_Atomizer]->WattsMAX*temp_auto_set/300;
	R_Temp_compensate=0;
	PID_init();
	Output_control_program=Custom_CCT_Output_control;
}

////////////////温度输出控制程序
void	Custom_CCT_Output_control(void)
{
//	u16		Custom_A,Custom_B;
	if(R_Custom_I_Set<=d_Custom_I_MAX)
	{
//		Custom_A=R_Custom_Set[R_Custom_I_Set+1];
//		Custom_B=R_Custom_Set[R_Custom_I_Set];
//		if(Custom_A>Custom_B)
//			R_Out_Temp_Set=(Custom_A-Custom_B)*R_Custom_tim/50+Custom_B;
//		else
//			R_Out_Temp_Set=Custom_B-(Custom_B-Custom_A)*R_Custom_tim/50;
//
		R_Out_Temp_Set=R_Custom_Set[R_Custom_I_Set];
		if(R_Temp_metric!=C_metric)
		{
			R_Out_Temp_Set=(R_Out_Temp_Set-32)*5/9;
		}
	}
	if(B_load_OK)
	{
		B_load_OK=0;
		Tempe_Compensation_calculation();
		PID_realize(R_Out_Temp_Set,R_real_Temp);
		Count_Wout();
		F_Average_Temp();
	}

	if(Power_down_control())
	{
		Count_Wout();
	}
	Wout_adjust(1);
}



