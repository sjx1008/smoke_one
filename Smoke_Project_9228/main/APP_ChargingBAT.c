#include "main_2.h"
#include "APP_ChargingBAT.h"
#include "WM_Disp.h"

#define		d_USB_error_H		580
#define		d_USB_error_L		415

u8	B_Fast_Charg=0;
u8 	B_Charg_Jianche;
u8 	B_BAT_Jianche;
u8 	B_BAT_error=1;						//电池异常标志
u8	B_BAT_error_LB_i=0;
u8	R_USB_error_i;
u8	R_USB_error_Tim;

u8	B_Proportion_Init=0;

//u16		R_last30M;
u16		R_last5M[2];
//u8		R_CLEAR_Congman;

u8		B_Get_Charg_BH=0;				//充电平衡状态标识 0：未开启 1：开启

u8		B_BAT_Congman;					///第一节充电充满标志
u8		B_BAT_Congman2;					///第二节充电充满标志
u8		B_BAT_Charge;						///充电标志

u16		R_BATT_Actual;							//总电池电压
u16		R_BATT_Z_Actual;							//总电池电压
u16		R_BATT_L_Actual;						//低端电池电压
u16		R_BATT_H_Actual;						//高端电池电压
u16		R_Charging_current_average;		//平均充电电流
u16		R_USB_Charging_current_average;	//USB平均充电电流

u16		R_BAT_L_Real;		//实时值
u16		R_BAT_H_Real;		//实时值
u16		R_BAT_Real;			//实时值
u16		R_BAT_MAX_Real;			//实时值
u16		R_BATZ_Real;		//实时值
u16		R_Charging_current_Real;		//实时充电电流
u16		R_USB_Charging_current_Real;	//USB实时充电电流

u16		R_Charging_Tim;		//充电计时
u16		R_Batter_Interface_Tim;		//屏幕充电计时

u16		R_Charg_I_Set;	//设置充电电流

u16		R_VCC_Voltage;

uc16	R_BAT_VIP[]={d_Bat_Volt_min,350,375,390,405,d_Bat_Volt_max};

void	Batt_Proportion(void);
static	void	BATT_Charging_Count_down(void);
void	BatterGrade_Calculate(void);
//USB检测口设置为数字口
USB_GPIO_term		R_USB_GPIO=USB_IN;
void	USB_GPIO_Set(USB_GPIO_term	R)
{
	LL_GPIO_InitTypeDef   GPIO_InitStructure;
	if(R!=R_USB_GPIO)
	{
		R_USB_GPIO=R;
		GPIO_InitStructure.Pin = USB_T_PIN;
		GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
		GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		GPIO_InitStructure.Pull = LL_GPIO_PULL_NO;

		GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
		if(R_USB_GPIO==USB_IN)
		{
			GPIO_InitStructure.Mode = 	LL_GPIO_MODE_INPUT;
		}
		else
		{
			GPIO_InitStructure.Mode = 	LL_GPIO_MODE_ANALOG;
		}
		LL_GPIO_Init(USB_T_GPIO_PORT, &GPIO_InitStructure);
	}
}

//统计平均电压电流
static 	u16	R_BAT_sum_i=0;
static	u32	R_BAT_sum_bat=0;
static	u32	R_BAT_sum_Z=0;
static	u32	R_BAT_sum_L_bat=0;
static	u32	R_BAT_sum_H_bat=0;
static	u32	R_Charging_current_sum=0;
static	u32	R_USB_Charging_current_sum=0;
void	F_BAT_Actual_Inti(void)
{
	R_BAT_sum_i=0;
	R_BAT_sum_bat=0;
	R_BAT_sum_L_bat=0;
	R_BAT_sum_H_bat=0;
	R_BAT_sum_Z=0;
	R_Charging_current_sum=0;
	R_USB_Charging_current_sum=0;
}
void	F_BAT_Actual(u8	B)
{
	u16	a;
	R_BAT_sum_i++;
	R_BAT_sum_bat+=R_BAT_Real;
	R_BAT_sum_L_bat+=R_BAT_L_Real;
	R_BAT_sum_H_bat+=R_BAT_H_Real;
	R_BAT_sum_Z+=R_BATZ_Real;
	if(B)
	{
		R_Charging_current_sum+=R_Charging_current_Real;
		R_USB_Charging_current_sum+=R_USB_Charging_current_Real;
		a=300;
	}
	else
	{
		R_Charging_current_sum=0;
		R_USB_Charging_current_sum=0;
		a=4;
	}
	if(R_BAT_sum_i>=a)
	{
		R_BATT_Z_Actual=R_BAT_sum_Z/R_BAT_sum_i;
		R_BATT_Actual=R_BAT_sum_bat/R_BAT_sum_i;
		R_BATT_L_Actual=R_BAT_sum_L_bat/R_BAT_sum_i;
		R_BATT_H_Actual=R_BAT_sum_H_bat/R_BAT_sum_i;
		R_Charging_current_average=R_Charging_current_sum/R_BAT_sum_i;
		R_USB_Charging_current_average=R_USB_Charging_current_sum/R_BAT_sum_i;
		if(R_USB_Charging_current_average>300)
			R_USB_Charging_current_average=300;
		if(R_USB_Charging_current_average>150)
			B_Fast_Charg=1;
		F_BAT_Actual_Inti();
	}
}
static u8 R_USB_L=0;
static u16 R_USB_L2=0;
static	u8	Over_CPU_Temp_I;
static	u8	R_Charg_I_Set_Q;
static	u16	R_BATZ_Real_Q=0;
static	u16	R_Charging_current_Q=0;
static	u8	B_NO_Charge=0;
static	Skinning_mode	R_Skinning_mode_Batt=Skinning_mode_null;

void	Decide_BAT_Congman(void)
{
	static	u8	Decide_L=0,Decide_H=0;
	if((!B_BAT_Congman2 && (R_BATT_L_Actual<415 || R_BATT_L_Actual+3<R_BATT_H_Actual)) || R_BATT_L_Actual<411)
	{
		if(Decide_L<5)
			Decide_L++;
		else
		{
			if(B_BAT_Congman && B_BAT_Congman2)
			{
				R_Charging_Tim=0;
				R_Batter_Interface_Tim=0;
			}
			B_BAT_Congman=0;
		}
	}
	else
	{
		Decide_L=0;
	}
	if((!B_BAT_Congman && (R_BATT_H_Actual<415 || R_BATT_H_Actual+3<R_BATT_L_Actual))||R_BATT_H_Actual<411)
	{
		if(Decide_H<5)
			Decide_H++;
		else
		{
			if(B_BAT_Congman && B_BAT_Congman2)
			{
				R_Charging_Tim=0;
				R_Batter_Interface_Tim=0;
			}
			B_BAT_Congman2=0;
		}
	}
	else
	{
		Decide_H=0;
	}
}

void	BAT_Management_Charge(void)
{
	u8	Charg_I_Max;
	u16	R_USB_ADC_data;
	u16	R_CPU_Temp;
	u16	R_PCB_Temp;
	u8	B;
	//////////在充电时
	if(B_BAT_Charge)
	{
		if(B_Out_Yes || R_USB_state!=S_USB_NOP)
		{
			if(!B_NO_Charge)
			{
				BAT_PWM_EN(0);//关闭充电PWM
				BAT_BH_OFF();
				R_Charg_I_Set_Q=R_Charg_I_Set;
				R_Charging_current_average=0;
				R_USB_Charging_current_average=0;
				B_NO_Charge=1;
			}
		}
		else
		{
			B_NO_Charge=0;
			BAT_COMP_ONorOFF(1);
			R_BAT_Real=ReadBATz_Data();
			R_USB_ADC_data=Read_USBV_Data();
			R_Charging_current_Real=Read_ChargIV_Data();
			u16	a;
			a=R_USB_ADC_data;
			if(a==0)
				a=1;
			R_USB_Charging_current_Real=R_Charging_current_Real*R_BATZ_Real/a*100/92;
			R_VCC_Voltage=Read_VCC_Data();
			if(R_BATZ_Real>(R_BATZ_Real_Q+30) || !Charge_EN_RinBit || R_BATZ_Real>880)
			{
				BAT_PWM_EN(0);//关闭充电
			}
			if(R_Charging_current_Real>R_Charging_current_Q+80 || R_Charging_current_Real+80<R_Charging_current_Q)
			{
				BAT_PWM_EN(0);//关闭充电
			}
			if(R_Charging_current_Real>200 || R_USB_Charging_current_Real>350)
			{
				BAT_PWM_EN(0);//关闭充电
			}
			R_Charging_current_Q=R_Charging_current_Real;
			R_BATZ_Real_Q=R_BATZ_Real;
			if(R_BATZ_Real>900 || R_BAT_Real<70 || (!B_USB_RinBit && R_BAT_Real<200) || R_BAT_MAX_Real>470  || R_VCC_Voltage<310 || R_VCC_Voltage>350)
			{
				BAT_PWM_EN(0);//关闭充电
				BAT_BH_OFF();
				B_BAT_Charge=0;
				if(R_SleepTim<5)
					R_SleepTim=5;
				USB_GPIO_Set(USB_IN);
				Reverse_MOS_OFF();
				B_Proportion_Init=0;
				B_BAT_error=1;
				B_BAT_error_LB_i=0;
				return;
			}
			if(B_Charg_Jianche)
			{
				B_Charg_Jianche=0;
				if(R_Charg_I_Set_Q)
				{
					R_Charg_I_Set=R_Charg_I_Set_Q;
					R_Charg_I_Set_Q=0;
				}
				BATT_Charging_Count_down();
				if(R_Charging_Tim>=d_Charging_Tim_Max)
				{
					if(R_Charg_I_Set>10)
					{
						R_Charg_I_Set=10;
					}
				}
				BAT_PWM_EN(1);//打开充电PWM
				if(R_USB_ADC_data<350)
				{
					B_BAT_Charge=0;
					if(R_SleepTim<5)
						R_SleepTim=5;
					B_USB_RinBit=0;
					BAT_PWM_EN(0);//关闭充电
					BAT_BH_OFF();
					USB_GPIO_Set(USB_IN);
					R_USB_L=0;
					R_USB_L2=0;
					return;
				}
				else	if(R_USB_ADC_data<d_USB_error_L || R_USB_ADC_data>d_USB_error_H || (R_USB_ADC_data<440 && R_Charging_current_Real<5))
				{
					R_USB_L2++;
					if(R_USB_L2>1000)
					{
						R_USB_L2=0;
						B_USB_Low=1;
						R_USB_error_i++;
						R_USB_error_Tim=35;
						B_BAT_Charge=0;
						if(R_SleepTim<5)
							R_SleepTim=5;
						BAT_PWM_EN(0);//关闭充电
						BAT_BH_OFF();
						R_Skinning_mode_Batt=USB_anomaly;
						return;
					}
				}
				else
				{
					R_USB_L2=0;
				}
				if(R_BAT_Real<270)
					Charg_I_Max=40;
				else
					Charg_I_Max=160;

				if(R_Charging_current_Real>R_Charg_I_Set || R_USB_Charging_current_Real>250 || R_BAT_MAX_Real>=421 || (R_USB_ADC_data<440 && R_Charging_current_Real>3))
				{
					R_BAT_PWM_data--;
					if(R_Charging_current_Real>R_Charg_I_Set+4)
						R_BAT_PWM_data--;
					if(R_Charging_current_Real>R_Charg_I_Set+8)
						R_BAT_PWM_data--;
					BAT_PWM_Wdata(&R_BAT_PWM_data);
				}
				else if((R_Charging_current_Real+10<R_Charg_I_Set || R_Charging_current_Real<2) && R_USB_Charging_current_Real<240)
				{
					R_BAT_PWM_data++;
					BAT_PWM_Wdata(&R_BAT_PWM_data);
				}
				F_BAT_Actual(1);
				if(R_BATT_L_Actual>=417	&& (R_Charging_current_Real<=15 || (R_Charging_current_Real<38 && (BAT_BH1_GPIO_PORT->ODR & BAT_BH1_PIN))))
				{
					if(R_last5M[0]<300)
						R_last5M[0]++;
					else
						B_BAT_Congman=1;
				}
				else
				{
					R_last5M[0]=0;
				}
				if(R_BATT_H_Actual>=417	&& (R_Charging_current_Real<=15 || (R_Charging_current_Real<38 && (BAT_BH2_GPIO_PORT->ODR & BAT_BH2_PIN))))
				{
					if(R_last5M[1]<300)
						R_last5M[1]++;
					else
						B_BAT_Congman2=1;
				}
				else
				{
					R_last5M[1]=0;
				}
				if(B_BAT_Congman && B_BAT_Congman2)
				{
					R_Charging_current_average=0;
					R_USB_Charging_current_average=0;
				}
				if(B_BAT_Jianche)
				{
					B_BAT_Jianche=0;
					BatterGrade_Calculate();
					Decide_BAT_Congman();
					Batt_Proportion();

					R_CPU_Temp=ReadTemp_Data();
					R_PCB_Temp=ADC_TDx_Data(ADC_PCBTempGPIO);
					if(R_CPU_Temp>70 || R_PCB_Temp<d_T70)
					{
						if(R_Charg_I_Set>10)
							R_Charg_I_Set=10;
						BAT_BH_OFF();
					}
					else
					{
						B=0;
						if(R_BAT_MAX_Real>=d_Bat_Volt_max)
							B=1;
						else	if(R_BAT_MAX_Real<d_Bat_Volt_max-5 && (R_CPU_Temp<60 && R_PCB_Temp>d_T60))
							B=3;
						else	if(R_BAT_MAX_Real<d_Bat_Volt_max-1)
							B=2;
						if(R_BAT_MAX_Real>=417)
						{
							if((s16)(R_BAT_MAX_Real-R_BAT_Real)<3 || R_BAT_Real>=418)
							{	BAT_BH_OFF();}
							else if(R_BATT_L_Actual>R_BATT_H_Actual+2)								//打开BAT1放电，关闭BAT2放电
							{	BAT_BH1_ON();}
							else if(R_BATT_H_Actual>R_BATT_L_Actual+2)								//打开BAT2放电，关闭BAT1放电
							{	BAT_BH2_ON();}
						}
						else
						{
							if(R_BATT_L_Actual>(R_BATT_H_Actual+4))
							{	BAT_BH2_OFF();}
							else if(R_BATT_H_Actual>(R_BATT_L_Actual+4))
							{	BAT_BH1_OFF();}
							else	if((s16)(R_BAT_MAX_Real-R_BAT_Real)<4 || R_BAT_MAX_Real<417)
							{	BAT_BH_OFF();}
						}

						if(R_CPU_Temp>60 || R_PCB_Temp<d_T60)
						{
							Over_CPU_Temp_I++;
							if(Over_CPU_Temp_I>8)
							{
								Over_CPU_Temp_I=0;
								B=1;
							}
						}
						if(B==1)
						{
							if(R_Charg_I_Set>30)
								R_Charg_I_Set-=5;//电流--
							else if(R_Charg_I_Set>2)
								R_Charg_I_Set-=2;//电流--
						}
						else if(R_CPU_Temp<70)
						{
							if(B==2)
							{
								if(R_Charg_I_Set<=30)
									R_Charg_I_Set+=2;//电流++
								else
									R_Charg_I_Set+=5;//电流++
							}
							else if(B==3)
							{
								if(R_Charg_I_Set<=30)
									R_Charg_I_Set+=10;//电流++
								else
									R_Charg_I_Set+=20;//电流++
							}
						}
						if(R_Charg_I_Set>Charg_I_Max)
							R_Charg_I_Set=Charg_I_Max;
						else	if((s16)R_Charg_I_Set<2)
							R_Charg_I_Set=2;

					}
				}
			}
		}
	}
}

//////////电池管理/////////
void	BAT_Management(void)
{
	u16	R_USB_ADC_data;
	BAT_Management_Charge();
	if(R_Skinning_mode_Batt!=Skinning_mode_null)
	{
		R_Skinning_mode=R_Skinning_mode_Batt;
		R_Skinning_mode_Batt=Skinning_mode_null;
	}
	if(B_BAT_error)
	{
		if(B_Charg_Jianche)
		{
			B_Charg_Jianche=0;
			R_BAT_Real=ReadBATz_Data();
			R_VCC_Voltage=Read_VCC_Data();
			if((R_BAT_Real>210 || (B_USB_RinBit && R_BAT_Real>80)) && R_BAT_MAX_Real<450 && R_VCC_Voltage>315 && R_VCC_Voltage<345)
			{
				if(B_BAT_error_LB_i<100)
					B_BAT_error_LB_i++;
				else
				{
					B_BAT_error_LB_i=0;
					B_BAT_error=0;
					Reverse_MOS_ON();
					B_Proportion_Init=0;
//					Batt_Proportion();
				}
			}
			else
			{
				B_BAT_error_LB_i=0;
			}
		}
	}
	if(!B_BAT_Charge || B_NO_Charge)
	{
		BAT_COMP_ONorOFF(0);
		if(B_BAT_Jianche)
		{
			B_BAT_Jianche=0;
			R_BAT_Real=ReadBATz_Data();
			F_BAT_Actual(0);
			if(R_BAT_Real>R_BATT_Actual+2 || R_BAT_Real+2<R_BATT_Actual)
			{
				R_BATT_Actual=R_BAT_Real;
				R_BATT_L_Actual=R_BAT_L_Real;
				R_BATT_H_Actual=R_BAT_H_Real;
			}
			BatterGrade_Calculate();
			R_VCC_Voltage=Read_VCC_Data();
			if(!B_BAT_error)
				Batt_Proportion();
//			if((R_BAT_Real>210 || (B_USB_RinBit && R_BAT_Real>80)) && R_BAT_MAX_Real<450 && R_VCC_Voltage>315 && R_VCC_Voltage<345)
//			{
//				B_BAT_error=0;
//				Reverse_MOS_ON();
//				Batt_Proportion();
//			}
			if(R_BAT_Real<70 || (!B_USB_RinBit && R_BAT_Real<200) || R_BAT_MAX_Real>470  || R_VCC_Voltage<310 || R_VCC_Voltage>350)
			{
				if(B_BAT_Charge)
				{
					BAT_PWM_EN(0);//关闭充电
					BAT_BH_OFF();
					B_BAT_Charge=0;
					if(R_SleepTim<5)
						R_SleepTim=5;
					USB_GPIO_Set(USB_IN);
				}
				B_Proportion_Init=0;
				Reverse_MOS_OFF();
				B_BAT_error=1;
				B_BAT_error_LB_i=0;
			}
			Decide_BAT_Congman();
			if(B_BAT_Charge || B_USB_Low)
			{
				static	u8	B_USB_Low_JC=0;
				if(B_USB_Low)
				{
					if(!B_USB_Low_JC)
					{
						B_USB_Low_JC=1;
						Set_BAT_Buck_PWM_Data(10);
						Set_BAT_BOOST_PWM_Data(d_BAT_PWM_Period-10);
					}
					else if(B_USB_Low_JC==1)
					{
						B_USB_Low_JC=2;
					}
					else if(B_USB_Low_JC==2)
					{
						B_USB_Low_JC=3;
						Set_BAT_Buck_PWM_Data(0);
						Set_BAT_BOOST_PWM_Data(0);
					}
					else if(B_USB_Low_JC==3)
					{
						B_USB_Low_JC=0;
					}
				}
				F_BAT_Actual_Inti();
				R_USB_ADC_data=Read_USBV_Data();
				if(R_USB_ADC_data<330)
				{
					B_BAT_Charge=0;
					if(R_SleepTim<5)
						R_SleepTim=5;
					B_USB_Low=0;
					USB_GPIO_Set(USB_IN);
					R_USB_L=0;
					B_USB_RinBit=0;

					B_USB_Low_JC=0;
					Set_BAT_Buck_PWM_Data(0);
					Set_BAT_BOOST_PWM_Data(0);
				}
				else	if(R_USB_ADC_data<d_USB_error_L || R_USB_ADC_data>d_USB_error_H)
				{
					if(!B_USB_Low)
					{
						R_USB_L++;
						if(R_USB_L>3)
						{
							R_USB_L=0;
							B_USB_Low=1;
							R_USB_error_i++;
							R_USB_error_Tim=35;
							B_BAT_Charge=0;
							if(R_SleepTim<5)
								R_SleepTim=5;
							R_Skinning_mode=USB_anomaly;
						}
					}
				}
				else
				{
					R_USB_L=0;
					if(!B_BAT_error && B_USB_Low && R_USB_error_i<3 && R_USB_ADC_data>450)
					{
						if(!R_USB_error_Tim)
						{
							B_USB_Low=0;
							B_BAT_Charge=1;
							B_Fast_Charg=0;
							R_Charging_Tim=0;
							R_Charg_I_Set=50;
							R_Charging_current_average=0;
							R_USB_Charging_current_average=0;
							R_Skinning_mode=USB_access;
							F_BAT_Actual_Inti();

							B_USB_Low_JC=0;
							Set_BAT_Buck_PWM_Data(0);
							Set_BAT_BOOST_PWM_Data(0);
						}
					}
				}
			}
		}
	}
}


////////////////////////////统计电池电量百分比
u8	R_BattL_Proportion;		//低节电池百分比
u8	R_BattH_Proportion;		//高节电池百分比
u8	a;
void	Batt_Proportion(void)
{
	u8	i;
	static	u8	wait=0;
	static	s8	LB[2]={5,5};
	u16	Charge_A;
	u16	BATT_V1,BATT_V2;
	if(B_Out_Yes)
	{
		wait=3;
		return;
	}
	if(wait)
	{
		wait--;
		return;
	}
	if(!B_BAT_Charge)
	{
		Charge_A=0;
		BATT_V1=R_BATT_L_Actual;
		BATT_V2=R_BATT_H_Actual;
	}
	else
	{
		Charge_A=R_Charging_current_average;
		if(Charge_A>200)
			Charge_A=200;
		BATT_V1=R_BATT_L_Actual-Charge_A/20;
		BATT_V2=R_BATT_H_Actual-Charge_A/20;
	}
	if(B_BAT_Congman)
	{
		R_BattL_Proportion=100;
		Charging_Over_Time[0]=0;
	}
	else
	{
		if(R_BattL_Proportion==100)
		{
			R_BattL_Proportion=99;
			Charging_Over_Time[0]=5;
		}
		if(BATT_V1<d_Bat_Volt_min)
		{
			a=0;
			LB[0]=0;
		}
		else	if(BATT_V1>=d_Bat_Volt_max)
			a=99;
		else
		{
			for(i=1;i<5;i++)
			{
				if(BATT_V1<R_BAT_VIP[i])
				{
					break;
				}
			}
			a=(BATT_V1-R_BAT_VIP[i-1])*20/(R_BAT_VIP[i]-R_BAT_VIP[i-1]);
			a+=(i-1)*20;
		}

		if(!B_Proportion_Init)
		{
			R_BattL_Proportion=a;
		}
		if(a+10<R_BattL_Proportion)
		{
			LB[0]=0;
		}
		else	if(a+5<R_BattL_Proportion)
		{
			LB[0]-=2;
		}
		else	if(a+3<R_BattL_Proportion)
		{
			LB[0]-=1;
		}
		else	if(a>R_BattL_Proportion+10)
		{
			LB[0]=10;
		}
		else	if(a>R_BattL_Proportion+5)
		{
			LB[0]+=2;
		}
		else	if(a>R_BattL_Proportion)
		{
			LB[0]+=1;
		}
		else	if(a)
		{
			LB[0]=5;
		}
		if(LB[0]<=0)
		{
			LB[0]=5;
			if(R_BattL_Proportion)
				R_BattL_Proportion--;
		}
		else if(LB[0]>=10)
		{
			LB[0]=5;
			if(R_BattL_Proportion<99)
				R_BattL_Proportion++;
		}
	}

	if(B_BAT_Congman2)
	{
		R_BattH_Proportion=100;
		Charging_Over_Time[1]=0;
	}
	else
	{
		if(R_BattH_Proportion==100)
		{
			R_BattH_Proportion=99;
			Charging_Over_Time[1]=5;
		}
		if(BATT_V2<d_Bat_Volt_min)
		{
			a=0;
			LB[1]=0;
		}
		else	if(BATT_V2>=d_Bat_Volt_max)
			a=99;
		else
		{
			for(i=1;i<5;i++)
			{
				if(BATT_V2<R_BAT_VIP[i])
				{
					break;
				}
			}
			a=(BATT_V2-R_BAT_VIP[i-1])*20/(R_BAT_VIP[i]-R_BAT_VIP[i-1]);
			a+=(i-1)*20;
		}
		if(!B_Proportion_Init)
		{
			R_BattH_Proportion=a;
		}
		if(a+10<R_BattH_Proportion)
		{
			LB[1]=0;
		}
		else	if(a+5<R_BattH_Proportion)
		{
			LB[1]-=2;
		}
		else	if(a+3<R_BattH_Proportion)
		{
			LB[1]-=1;
		}
		else	if(a>R_BattH_Proportion+10)
		{
			LB[1]=10;
		}
		else	if(a>R_BattH_Proportion+5)
		{
			LB[1]+=2;
		}
		else	if(a>R_BattH_Proportion)
		{
			LB[1]+=1;
		}
		else	if(a)
		{
			LB[1]=5;
		}
		if(LB[1]<=0)
		{
			LB[1]=5;
			if(R_BattH_Proportion)
				R_BattH_Proportion--;
		}
		else if(LB[1]>=10)
		{
			LB[1]=5;
			if(R_BattH_Proportion<99)
				R_BattH_Proportion++;
		}
	}
	B_Proportion_Init=1;
}


//充电倒计时


#define BATTMAH    2600

u8	Charging_Count;	//吸烟倒计时计数器
u32	BATT_Current_SUM;

u16	Charging_Over_Time[2];

//充电时间倒计时显示
u16	BATT_Charging_Count_down_JS(u8	CM,u8	Bat,u16	R)
{
	u16	a;
	if(CM)
		return	0;
	else
	{
		a=(BATTMAH-Bat*BATTMAH/100)*6/R;
		if(a<2)
			return	2;
		else	if(a>180)
			return	180;
		else
			return	a;
	}
}
static	u8	B_Count_down_Init=0;
void	BATT_Charging_Count_down_Init(void)
{
	u16	I;
	Charging_Count=20;
	BATT_Current_SUM=0;
	if(R_BATT_Actual<260)
		I=40;
	else
	{
		I=100000/R_BATT_Actual;
		if(I>150)
			I=150;
	}
	B_Count_down_Init=1;
	Charging_Over_Time[0]=BATT_Charging_Count_down_JS(B_BAT_Congman,R_BattL_Proportion,I);
	Charging_Over_Time[1]=BATT_Charging_Count_down_JS(B_BAT_Congman2,R_BattH_Proportion,I);
}

static	void	BATT_Charging_Count_down(void)
{
	u16	BATT_Current;
	u8	t1,t2;
	if(B_BAT_Jianche)
	{
		if(Charging_Count)
		{
			Charging_Count--;
			BATT_Current_SUM+=R_Charging_current_average;
		}
		else
		{
			Charging_Count=20;
			if(B_Count_down_Init)
			{
				B_Count_down_Init=0;
				BATT_Current=BATT_Current_SUM/Charging_Count*3/2;
				if(BATT_Current>150)
					BATT_Current=150;
			}
			else
				BATT_Current=BATT_Current_SUM/Charging_Count;
			BATT_Current_SUM=0;
			t1=BATT_Charging_Count_down_JS(B_BAT_Congman,R_BattL_Proportion,BATT_Current);
			t2=BATT_Charging_Count_down_JS(B_BAT_Congman2,R_BattH_Proportion,BATT_Current);
			if(t1>Charging_Over_Time[0]+10 || t1<Charging_Over_Time[0] || t1==0)
				Charging_Over_Time[0]=t1;
			if(t2>Charging_Over_Time[1]+10 || t2<Charging_Over_Time[1] || t2==0)
				Charging_Over_Time[1]=t2;
		}
	}
}


//计算电池格数
u8	BatterGrade;
u8	BatterGrade2;
void	BatterGrade_Calculate(void)
{
	u8	i;
	static	u16	Batter_Vatt_Q=0,Batter_Vatt2_Q=0;
	static	u16	BatterGrade_Q=0,BatterGrade2_Q=0;
	if(Batter_Vatt_Q!=R_BATT_L_Actual)
	{
		Batter_Vatt_Q=R_BATT_L_Actual;
		for(i=0;i<5;i++)
		{
			if(Batter_Vatt_Q<R_BAT_VIP[i])
			{
				break;
			}
		}
		BatterGrade=i;
		if(BatterGrade+1==BatterGrade_Q && R_BATT_L_Actual+3>R_BAT_VIP[i])
			BatterGrade=BatterGrade_Q;
		else if(BatterGrade==BatterGrade_Q+1 && R_BATT_L_Actual<R_BAT_VIP[i-1]+3)
			BatterGrade=BatterGrade_Q;
		BatterGrade_Q=BatterGrade;
	}
	if(Batter_Vatt2_Q!=R_BATT_H_Actual)
	{
		Batter_Vatt2_Q=R_BATT_H_Actual;
		for(i=0;i<5;i++)
		{
			if(Batter_Vatt2_Q<R_BAT_VIP[i])
			{
				break;
			}
		}
		BatterGrade2=i;
		if(BatterGrade2+1==BatterGrade2_Q && R_BATT_H_Actual+3>R_BAT_VIP[i])
			BatterGrade2=BatterGrade2_Q;
		else if(BatterGrade2==BatterGrade2_Q+1 && R_BATT_H_Actual<R_BAT_VIP[i-1]+3)
			BatterGrade2=BatterGrade2_Q;
		BatterGrade2_Q=BatterGrade2;
	}
}

