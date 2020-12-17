
/* 梅工
2018/08/02
VV电压默认值改为3.6V
可调节0V
*/

#include	"main_2.h"
#include	"OUT_Public.h"
#include "Voltage_MODE_Control.h"

////////////////٦ÊˤԶ࠘׆ԌѲ
//ԃۧʨֵ֨
u16	R_User_Vout_Set=360;				//ʨ֨ˤԶ֧ѹ		//10mV     	0.00

void	Voltage_Output_control(void);
static	void Voltage_yule(void);
void	Voltage_mode_int(void)
{
	R_Out_W_Set=R_User_Vout_Set*R_User_Vout_Set*10/R_Res_average;
	if(R_Out_W_Set+1000<R_PowerMAXMAX)
		R_PowerMAXMAX=R_Out_W_Set+1000;
	R_PowerMAX=R_PowerMAXMAX;
	if(R_Out_W_Set>R_PowerMAXMAX)
	{
		R_Out_V_Set=sqrt_16(R_PowerMAXMAX*R_Res_average/10);
	}
	else
	{
		R_Out_V_Set=R_User_Vout_Set;
	}
	if(R_Out_V_Set>R_User_Vout_Set)
	{
		R_Out_V_Set=R_User_Vout_Set;
	}
	Output_control_program=Voltage_Output_control;
	Voltage_yule();
}
////////////////݆̣ˤԶ֧ѹ
void	Count_Vout(u16	R)
{
	R_Out_V_Set=sqrt_16(R_PowerMAX*R/10);
	if(R_Out_V_Set>R_User_Vout_Set)
	{
		R_Out_V_Set=R_User_Vout_Set;
	}
}

//ԤɈ
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
		if(B)
			Count_Vout(R_Res_average);
		Vout_adjust(10);
		Delay_Nus(5);
	}
	R_Read_Rtim=R;
}

////////////////֧ѹģʽˤԶ࠘׆ԌѲ
void	Voltage_Output_control(void)
{
	if(Power_down_control())
	{
		Count_Vout(R_Res_average);
	}
	Vout_adjust(1);
}


