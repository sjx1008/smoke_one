
#include	"main_2.h"
#include	"OUT_Public.h"
#include "Tempe_MODE_Control.h"

////////////////功率输出控制程序
u8	CompensationTim;

//用户设定值
u16	R_User_Temp_Set_C=205;			//设定摄氏度			//1摄氏度	 	000
u16	R_User_Temp_Set_F=400;			//设定华氏度			//1华氏度		000

//u16	R_User_Temp_Watt_Max = 75;

static	u16   temp_auto_set = 0;

void	Temp_Output_control(void);

void	Temp_mode_int(void)
{
	if(R_Temp_metric==C_metric)
	{
		R_Out_Temp_Set=R_User_Temp_Set_C;
	}
	else
	{
		R_Out_Temp_Set=(R_User_Temp_Set_F-32)*5/9;
	}
	R_Temp_MAX=500;
	R_PowerMAX=Atomizer_Pointer[R_Atomizer]->WattsMAX*100;
	R_T_Gradient_out=Atomizer_Pointer[R_Atomizer]->Gradient;
	if(R_PowerMAX<R_PowerMAXMAX)
	{
		R_PowerMAXMAX=R_PowerMAX;
	}
	else
	{
		R_PowerMAX=R_PowerMAXMAX;
	}
	R_Temp_PowerMAX=R_PowerMAX;
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
	CompensationTim=0;
	Output_control_program=Temp_Output_control;
}


void	TCR_mode_int(void)
{
	if(R_Temp_metric==C_metric)
	{
		R_Out_Temp_Set=R_User_Temp_Set_C;
	}
	else
	{
		R_Out_Temp_Set=(R_User_Temp_Set_F-32)*5/9;
	}
	R_Temp_MAX=500;
	R_PowerMAX=TCR_Pointer[R_TCR_term]->WattsMAX*100;
	R_T_Gradient_out=TCR_Pointer[R_TCR_term]->Gradient;
	if(R_PowerMAX<R_PowerMAXMAX)
	{
		R_PowerMAXMAX=R_PowerMAX;
	}
	else
	{
		R_PowerMAX=R_PowerMAXMAX;
	}
	R_Temp_PowerMAX=R_PowerMAX;
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
	R_Out_W_Set=TCR_Pointer[R_TCR_term]->WattsMAX*temp_auto_set/300;
	R_Temp_compensate=0;
	PID_init();
	CompensationTim=0;
	Output_control_program=Temp_Output_control;
}

//温度补偿计算
void Tempe_Compensation_calculation(void)
{
	if(R_real_Res>R_Res_Initial)
	{
		R_real_Temp=((R_real_Res-R_Res_Initial)*100000)/(R_T_Gradient_out*R_Res_Initial);
		if(R_Smoke_Tim<100)
		{
			if(R_Out_TempC_Actual+3>R_Out_Temp_Set)
			{
				if(CompensationTim!=R_Smoke_Tim/10)
				{
					CompensationTim=R_Smoke_Tim/10;
					R_Temp_compensate++;
				}
			}
		}
		if(R_Out_TempC_Actual>100)
		{
			R_real_Temp-=R_Temp_compensate*R_Temp_compensate_MAX/10;
		}
		R_Efficiency=100;
	}
	else
	{
		R_Efficiency=90;
		R_real_Temp=20;
	}

	if(R_real_Temp>500)
	{
		R_real_Temp=500;
	}
}

////////////////温度输出控制程序
void	Temp_Output_control(void)
{
	if(R_Smoke_Tim<3 && R_real_IOUT<3000)
		B_Out_JC=1;
	if(B_load_OK)
	{
		B_load_OK=0;
		Tempe_Compensation_calculation();
		if(R_Smoke_Tim>50)
		{
			if(R_Temp_MAX==500)
			{
				if(R_Out_TempC_Actual+3<R_Out_Temp_Set)
				{
					if(R_Out_W_Set>R_PowerMAXMAX*2/3)
					{
						R_Out_Temp_Set=R_Out_TempC_Actual+3;
					}
				}
				R_Temp_MAX=R_Out_TempC_Actual+2;
			}
		}
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


