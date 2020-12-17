#include "APP_Outputcontrol.h"
#include "main_2.h"
#include "WM_Disp.h"

//ó??§éè?¨?μ
u8	R_User_Smoke_Tim_max=100; 							//?ü?ì??ê±max		//100mS			00.0

//////////////////////////////////////////////////////////////

u8	B_Smoking_mark;						///?ü?ì±ê??
u8	B_Smoking_mark_Q=1;					///?ü?ì±ê??
u8	B_Power_down;							///?μ1|?ê±ê??

u8	R_Smoke_Tim; 		//吸烟计时			//100ms		00.0
u16	R_Smoke_Tim10ms; 		//吸烟计时			//10ms		00.00


u8	B_Out_Yes;					///正在输出标志
u8	B_Out_JC;						///输出电压检测
u8	B_load_JC;					///电阻检测
u8	B_load_OK;					///电阻检测
u8	B_yule=0;						///预热
u8	B_AUOT_MODE=1;				//麦克维尔的自动模式

u16	R_MODE_Out_ResMin;

////////最大允许输出功率 放大100倍
u16	R_PowerMAX;				//10mW	00.00
////////最大允许输出功率	放大100倍
u16	R_PowerMAXMAX;		//10mW	00.00
////////温控最大输出功率	放大100倍
u16	R_Temp_PowerMAX;	//10mW	00.00
u16	R_Temp_MAX;	//
/*******************************************/
u16	R_Out_W_Set;				///ê?3?Wêy		00.00
u16	R_Out_V_Set;				///ê?3?V		0.00
u16	R_Out_Temp_Set;			///ê?3????è	000

u16	R_Res_Actual;				//平均阻值		0.000
u16	R_Out_I_Actual;			//平均电流		0.00
u16	R_Out_V_Actual;			//平均电压		0.00
u16	R_Out_W_Actual;			//平均瓦数		0.00
u16	R_Out_TempC_Actual;	//平均温度		000
u16	R_Out_TempF_Actual;	//平均温度		000
u32	R_Out_I_SUM;				///
u32	R_Out_V_SUM;				///
u32	R_Out_W_SUM;				///
u8	R_Out_V_i;					///
u8	R_Out_V_i_max;					///

u32	R_Out_Temp_SUM;				///
u8	R_Out_Temp_i;				///
u32	R_Real_SUM;				///
u8	R_Real_i;				///

u16	R_T_Gradient_out;			//电阻温度系数_out
u8	R_Efficiency;					//转换效率

/*******************************************/

u16	R_real_Temp;				///实时温度		//000
u16	R_real_BAT;					///实时电池电压	0.00
u16	R_real_WOUT;				///实时输出瓦数	0.00
u16	R_real_VOUT;				///实时输出电压	0.00
u16	R_real_IOUT;				///实时输出电流	0.00
u16	R_real_Res;					///实时电阻			0.000

u8	R_Lbat_LB;					///低电量滤波

u8	R_Temp_compensate;			//温度补偿值
u8	R_Temp_compensate_MAX=15;	//温度补偿最大值

u8	R_XY_Tim_yanshi=0;

Skinning_mode	R_Skinning_modeOUT;		//窗口状态
/************************************************/
void	(*Output_control_program)(void);	//输出控制程序

void	PID_init(void);
void	PID_realize(u16 speed , u16 Aspeed);
void	Fault_handling(Skinning_mode	R);


///统计平均输出电压电流功率
void	F_Average_Vout(void)
{
	R_Out_V_i++;
	R_Out_V_SUM+=R_real_VOUT;
	R_Out_I_SUM+=R_real_IOUT;
	R_Out_W_SUM+=R_real_WOUT;
	if(R_Out_V_i>=R_Out_V_i_max)
	{
		/*统计平均电压*/
		R_Out_V_Actual=R_Out_V_SUM/R_Out_V_i_max;
		if(R_Out_V_Actual>d_User_Vout_max)
			R_Out_V_Actual=d_User_Vout_max;
//////////////////////////////////////////

		/*统计平均电流*/
		R_Out_I_Actual=R_Out_I_SUM/R_Out_V_i_max;
		if(R_Out_I_Actual>d_User_Iout_max_x100)
			R_Out_I_Actual=d_User_Iout_max_x100;
/////////////////////////////////
		/*统计平均瓦数*/
		R_Out_W_Actual=R_Out_W_SUM/R_Out_V_i_max/10;
		if(R_Out_W_Actual>d_User_Watt_max)
			R_Out_W_Actual=d_User_Watt_max;


		R_Out_W_SUM=0;
		R_Out_V_SUM=0;
		R_Out_I_SUM=0;
		R_Out_V_i=0;
		if(R_Out_V_i_max<200)
			R_Out_V_i_max=200;
	}
}

///统计平均温度
void	F_Average_Temp(void)
{
	R_Out_Temp_i++;
	R_Out_Temp_SUM+=R_real_Temp;
	if(R_Out_Temp_i>=10)
	{
		R_Out_TempC_Actual=R_Out_Temp_SUM/10;
		if(R_Out_TempC_Actual>500)
		{
			R_Out_TempC_Actual=500;
		}
		R_Out_TempF_Actual=R_Out_TempC_Actual*9/5+32;
		R_Out_Temp_SUM=0;
		R_Out_Temp_i=0;
	}
}

//求平均电阻
void	F_Average_Real(void)
{
	R_Real_i++;
	R_Real_SUM+=R_real_Res;
	if(R_Real_i>=20)
	{
		R_Res_Actual=R_Real_SUM/20;
		if(R_Res_Actual>9999)
			R_Res_Actual=9999;
		R_Real_i=0;
		R_Real_SUM=0;
	}
}

//判断是否过温
u8	Over_PCB_Temp(void)
{
	static	u8	B_Overheated=0;
	if(B_Overheated)
	{
		if(ADC_TDx_Data(ADC_PCBTempGPIO)<d_T60 || ReadTemp_Data()>60)
			return	1;
		else
			B_Overheated=0;
	}
	else
	{
		if(ADC_TDx_Data(ADC_PCBTempGPIO)<d_T70 || ReadTemp_Data()>70)
		{
			B_Overheated=1;
			return	1;
		}
	}
	return	0;
}

/////////////?á×è?μ
void	Out_Read_load(void)
{
	if(B_load_JC)
	{
		B_load_JC=0;
//		COMP_ONorOFF(DISABLE);
		R_real_Res=Read_L_1C();
//		COMP_ONorOFF(ENABLE);
		if(R_real_Res>=d_Res_max)
		{
			Fault_handling(Open_circuit);
		}
		else if(R_real_Res<R_MODE_Out_ResMin-2)
		{
			Fault_handling(Short_circuit);
		}
		else
		{
			B_load_OK=1;
			F_Average_Real();
			if(Over_PCB_Temp())
				Fault_handling(PCB_Overheated);
		}
	}
}

////////////////1ê??′|àí
void	Fault_handling(Skinning_mode	R)
{
	PWM_OFF();
	COMP_ONorOFF(DISABLE);
	B_Smoking_mark=0;
	R_Skinning_modeOUT=R;
}

void	Fault_handling2(Skinning_mode	R)
{
	B_Smoking_mark=0;
	R_Skinning_mode2=R;
}

////////////////?üD?ê?3?í?êy
void	Count_Wout(void)
{
	if(R_Out_W_Set>R_PowerMAX)
	{
		R_Out_W_Set=R_PowerMAX;
	}
}



///////////电压调节
void	Vout_adjust(u8	bu)
{
	if(R_real_BAT>d_Bat_OUT_Volt_min && R_real_VOUT+10<R_Out_V_Set && R_real_WOUT<d_User_Watt_max_x10+80 && R_real_IOUT<d_User_Iout_max_x100-30)
	{
		R_OUT_PWM_data+=bu;
		OUT_PWM_Wdata(&R_OUT_PWM_data);
	}
	else if(R_real_BAT<d_Bat_OUT_Volt_min-10 || R_real_VOUT>R_Out_V_Set+10 || R_real_WOUT>d_User_Watt_max_x10+80 || R_real_IOUT>d_User_Iout_max_x100)
	{
		R_OUT_PWM_data-=bu;
		OUT_PWM_Wdata(&R_OUT_PWM_data);
	}
}
///////////瓦数调节
void	Wout_adjust(u8	bu)
{
	static u8	i;
	static u8	j;
	if(R_real_BAT>d_Bat_OUT_Volt_min && R_real_WOUT+50<R_Out_W_Set && R_real_VOUT<d_User_Vout_max+10 && R_real_IOUT<d_User_Iout_max_x100-30)
	{
		j=0;
		i++;
		if(R_real_WOUT+100<R_Out_W_Set)
			i=20;
		if(i>=20)
		{
			i=0;
			R_OUT_PWM_data+=bu;
			OUT_PWM_Wdata(&R_OUT_PWM_data);
		}
	}
	else
	{
		if(R_real_BAT<d_Bat_OUT_Volt_min-10 || R_real_VOUT>d_User_Vout_max+10 || R_real_IOUT>d_User_Iout_max_x100)
		{	j=20;}
		if(R_real_WOUT>R_Out_W_Set+50)
		{
			i=0;
			j++;
			if(R_real_WOUT>R_Out_W_Set+100)
				j=20;
		}
		else
		{
			i=0;
			j=0;
		}
		if(j>=20)
		{
			j=0;
			R_OUT_PWM_data-=bu;
			OUT_PWM_Wdata(&R_OUT_PWM_data);
		}
	}
}

////////////////?μ1|?ê
u8	Power_down_control(void)
{
	u8	B;
	static	u8	Power_i;
	B=0;
	if(R_real_BAT<=d_Bat_OUT_Volt_min)
	{
		Power_i=0;
		if(R_real_WOUT>1000 && R_PowerMAXMAX>1000)
		{
			if(R_real_WOUT<R_PowerMAX+200)
			{
				B=1;
				B_Power_down=1;
				R_PowerMAXMAX-=200;
				if(R_PowerMAXMAX<1000)
					R_PowerMAXMAX=1000;
				R_PowerMAX-=500;
				if(R_PowerMAX<1000)
					R_PowerMAX=1000;
			}
		}
		else
		{
			R_Lbat_LB++;
			if(R_Lbat_LB>=5)
			{
				Fault_handling(Low_Battery);
			}
		}
	}
	else
	{
		R_Lbat_LB=0;
		if(R_real_BAT>d_Bat_Volt_min)
		{
			Power_i++;
			if(Power_i>10)
			{
				Power_i=0;
				if(R_PowerMAX<R_PowerMAXMAX)
				{
					R_PowerMAX+=100;
					B=1;
				}
			}
		}
		else
		{
			Power_i=0;
		}
	}
	return B;
}

/////////ê?3?3?ê??ˉ
u8	B_again;
u8	R_again_Tim=100;
static	u8	MODE_OUT_int(u16	ResMin)
{
	u8	R_return;
	u8	B=0;
	u16	R_L;
	R_return=0;
	R_MODE_Out_ResMin=ResMin;
	if(!R_XY_Tim_yanshi)
	{
		if(BatterGrade && BatterGrade2)
			B=1;
	}
	else
	{
		if(R_BATT_Actual>(d_Bat_OUT_Volt_min-7))
			B=1;
	}
	if(B)
	{
		if(R_Res_average>=ResMin && R_Res_average<d_Res_max)
		{
			Enable_VoutADC_Use();
			if(!B_again && !R_again_Tim)
			{
				B_again=1;
				R_L=Read_L_1C();
				if((R_L*10/9)<R_Res_average && (R_L+10)<R_Res_average)
				{
					B_Sleep_YES=4;
					R_Read_Rtim=50;
					return 0;
				}
			}
		}
		if(R_Res_average<ResMin/2)
		{
			Fault_handling2(Short_circuit);
		}
		else if(R_Res_average<ResMin)
		{
			Fault_handling2(Low_Resistance);
		}
		else if(R_Res_average>=d_Res_max)
		{
			Fault_handling2(Open_circuit);
		}
		else if(R_Res_average>d_Res_usable)
		{
			Fault_handling2(High_Resistance);
		}
		else if(Over_PCB_Temp())
		{
			Fault_handling2(PCB_Overheated);
		}
		else
		{
			R_again_Tim=100;
//			if(R_Res_average>=(d_User_Watt_max_x10/(d_User_Iout_max*d_User_Iout_max/10)))
			{
				R_PowerMAXMAX=d_User_Watt_max_x10;
			}
//			else
//			{
//				R_PowerMAXMAX=(d_User_Iout_max*d_User_Iout_max/10)*R_Res_average;
//			}

			B_Power_down=0;							///降功率
			R_Smoke_Tim=0; 		//吸烟计时			//100ms		00.0
			R_Smoke_Tim10ms=0;
			B_Out_JC=0;						///输出电压检测
			B_load_JC=0;					///电阻检测
			B_load_OK=0;					///电阻检测
			B_yule=0;						///预热
			R_Res_Actual=R_Res_average;				//???ù×è?μ		0.000
			R_Out_I_Actual=0;			//平均电流		0.00
			R_Out_V_Actual=0;			//平均电压		0.00
			R_Out_W_Actual=0;			//平均瓦数		0.0
			R_Out_TempC_Actual=0;	//平均温度		000
			R_Out_TempF_Actual=0;	//平均温度		000
			R_Out_I_SUM=0;				///
			R_Out_V_SUM=0;				///
			R_Out_W_SUM=0;				///
			R_Out_V_i=0;					///
			R_Out_V_i_max=10;
			R_Out_Temp_SUM=0;				///
			R_Out_Temp_i=0;				///
			R_Real_SUM=0;				///
			R_Real_i=0;				///
			R_last5M[0]=0;
			R_last5M[1]=0;
			B_BAT_Congman=0;
			B_BAT_Congman2=0;
			R_Efficiency=100;
			R_Skinning_modeOUT=Skinning_mode_null;
			PWM_ON();
			COMP_ONorOFF(ENABLE);
			B_Out_Yes=1;
			R_return=1;
		}
	}
	else
	{
		Fault_handling2(Low_Battery);
	}
	return	R_return;
}
void	Out_int(void)
{
	switch	((u8)R_Work_mode)
	{
		case	d_Bypass_mode:		if(MODE_OUT_int(d_Res_min))Bypass_mode_int();break;
		case	d_Temp_mode:			if(MODE_OUT_int(d_Res_min))Temp_mode_int();;break;
		case	d_TCR_mode:				if(MODE_OUT_int(d_Res_min))TCR_mode_int();break;
		case	d_Custom_mode:		if(MODE_OUT_int(d_Res_min))Custom_mode_int();break;
		case	d_CustomTemp_mode:		if(MODE_OUT_int(d_Res_min))Custom_CCT_mode_int();break;
		case	d_CustomVolt_mode:		if(MODE_OUT_int(d_Res_min))Custom_CCV_mode_int();break;
		case	d_Voltage_mode:		if(MODE_OUT_int(d_Res_min))Voltage_mode_int();break;
		case	d_SPP_mode:				if(MODE_OUT_int(20))SPP_mode_int();break;
		default:			if(MODE_OUT_int(d_Res_min))Watt_mode_int();
	}
}

void	OUT_YES_Control(void)
{
	if(B_Smoking_mark)
	{
		if(B_Out_Yes)
		{
			if(B_Out_JC)
			{
				B_Out_JC=0;
				R_XY_Tim_yanshi=20;
				R_real_BAT=ReadBATz_Data();
				ReadLoad_Data();
				R_real_VOUT=R_ReadLoad_outV;
				R_real_IOUT=R_ReadLoad_outI;
				R_real_WOUT=R_real_VOUT*R_real_IOUT/R_Efficiency;
				Out_Read_load();
				F_Average_Vout();
				(*Output_control_program)();
				if(R_real_IOUT>d_OVER_Iout_max_x100)
				{
					Fault_handling(Short_circuit);
				}
			}
			if(R_Smoke_Tim10ms>=R_User_Smoke_Tim_max*10)
			{
				Fault_handling(Smoking_timeout);
			}
			Statistics_numberANDlengthTim(R_Smoke_Tim);
		}
		if(!B_Smoking_KEY_anxia)
		{
			Fault_handling(Skinning_mode_null);
		}
	}
}

void	OUTControl_Init(void)
{
	if(B_Sleep_YES)
		return;
	if(B_Smoking_mark)
	{
		B_Smoking_mark_Q=1;
		if(!B_Out_Yes)
		{
			Out_int();
		}
	}
}
///////////输出总控制
void	OUTControl(void)
{
	if(R_USB_state==S_USB_NOP && R_SleepTim && !B_BAT_error)
	{
		OUTControl_Init();
		OUT_YES_Control();
	}
	else
	{
		B_Smoking_mark=0;
	}
	if(!B_Smoking_mark)
	{
		if(B_Out_Yes)
		{
			if(R_Skinning_modeOUT!=Skinning_mode_null)
			{
				R_Skinning_mode=R_Skinning_modeOUT;
				R_Skinning_modeOUT=Skinning_mode_null;
			}

			B_Out_Yes=0;
			B_again=0;
			PWM_OFF();
			COMP_ONorOFF(DISABLE);
//			R_Smoke_Tim=0;
			R_Out_I_Actual=0;			//平均电流		0.00
			R_Out_V_Actual=0;			//平均电压		0.00
			R_Out_W_Actual=0;			//平均瓦数		0.0
			R_Out_TempC_Actual=0;	//平均温度		000
			R_Out_TempF_Actual=0;	//平均温度		000
		}
	}
}



typedef struct
{
	s16	SetSpeed;//定义设定值
	s16	ActualSpeed;//定义实际值
	s16	err; //定义偏差值
	s16 err_last;//定义上一个偏差值
	s16 err_last2;//定义上上一个偏差值
	u8	Kp,Ki,Kd;//定义比例、积分、微分系数
	float	voltage;//定义瓦数值
//	s16	integral;//定义积分值
	u8	L_Power_i;
	u8	H_Power_i;

	u8  B_Temp_state;
	u8  B_state_i;
}_PID;

_PID	pid;

void	PID_init(void)
{
	pid.SetSpeed=0;
	pid.ActualSpeed=0;
	pid.err=0;
	pid.err_last=0;
	pid.voltage=0;
//	pid.integral=0;
	pid.Kp=2;
	pid.Ki=3;
	pid.Kd=1;
	pid.L_Power_i=0;
	pid.H_Power_i=0;

	pid.B_Temp_state=0;
	pid.B_state_i=0;
}

void	PID_realize(u16 speed , u16 Aspeed)
{
	pid.SetSpeed=speed;
	pid.ActualSpeed=Aspeed;
	pid.err=pid.SetSpeed-pid.ActualSpeed;

	if(!B_yule)
	{
		if(pid.ActualSpeed>pid.SetSpeed || R_Smoke_Tim>2)
		{
			B_yule=1;
			pid.Ki=5;

			R_Out_W_Set=R_Out_W_Set*2/3;
		}
	}
	if(pid.ActualSpeed>350)
	{
		R_Out_W_Set=0;
		R_Temp_PowerMAX=0;
		pid.B_Temp_state=1;
	}
	else	if(pid.ActualSpeed>340)
	{
		R_Out_W_Set=R_Out_W_Set*2/3;
		R_Out_W_Set-=500;
		if(R_Temp_PowerMAX>500)
			R_Temp_PowerMAX-=500;
		else
			R_Temp_PowerMAX=0;
	}
	else if(pid.err<-15)
	{
		pid.H_Power_i=0;

		if(pid.L_Power_i<2)
		{
			pid.L_Power_i++;
		}
		else
		{
			pid.L_Power_i=0;
			R_Out_W_Set-=400;
			if(R_Temp_PowerMAX>500)
				R_Temp_PowerMAX-=500;
			else
				R_Temp_PowerMAX=0;
		}
	}
	else
	{
		pid.L_Power_i=0;
		if(pid.ActualSpeed<200)
		{
			pid.H_Power_i++;
			if(pid.H_Power_i>4)
			{
				pid.H_Power_i=0;
				if(R_Temp_PowerMAX<R_PowerMAXMAX && pid.B_Temp_state!=2)
				{
					R_Temp_PowerMAX+=250;
				}
			}
		}
		else
		{
			pid.H_Power_i=0;
		}
	}

	if(pid.err<2 && pid.err>-5)
	{
		pid.voltage=0;
	}
	else
	pid.voltage = pid.Kp*(pid.err-pid.err_last)+pid.Ki*pid.err+pid.Kd*(pid.err-2*pid.err_last+pid.err_last2);
	pid.err_last2=pid.err_last;
	pid.err_last=pid.err;
	if(pid.voltage>500)
	{
		pid.voltage=500;
	}
	else if(pid.voltage<-1000)
	{
		pid.voltage=-1000;
	}

	if(pid.err<(-6) || pid.ActualSpeed>320)
	{
			if(pid.voltage>0)
			{
				pid.voltage=0;
			}
			R_Out_W_Set-=100;
	}

	R_Out_W_Set+=(s16)pid.voltage;
	if((s16)R_Out_W_Set<0)
	{
		R_Out_W_Set=0;
	}
	else if(R_Out_W_Set>R_Temp_PowerMAX)
	{
		R_Out_W_Set=R_Temp_PowerMAX;
	}
	if(pid.B_Temp_state==1)
	{
		if(R_Out_W_Set<100)
		{
			if(pid.B_state_i++>20)
			{
				pid.B_Temp_state=2;
			}
		}
	}
}



