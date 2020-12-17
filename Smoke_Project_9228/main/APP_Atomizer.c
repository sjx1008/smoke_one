#include "main_2.h"
#include "APP_Atomizer.h"

u16	R_Res_Initial=d_Res_max;					//初始阻值
u16	R_Res_Initial_jiyi=d_Res_max;			//记忆阻值
u16	R_Res_average=d_Res_max;					//平均阻值
u16	R_Res_average_Q;
u16	R_Res_Initial_Q;
u16	R_Res_Sleep;											//进入休眠前的平均电阻

u8	B_LOCK_Res=0;									//阻值锁定标志
u8	B_have_Atomizer=0;						//是否接入雾化器
u8	B_Atomizer_inquiry=0;					//是否询问雾化器
u8	B_Again_Read=1;								//新读取
vu16	R_Read_Rtim=500;							//

u8	B_Sleep_YES;


#define	d_read_haveLMAX	6
uc8	R_read_haveL[7]={5,10,20,30,40,50,70};
u8	R_haveL_I=0;

//////?áò?′?×è?μ
u16 Read_L_1C(void)
{
	u16 LR;
	u8	PWM;
	u8	B;
	u8	i;
	PWM=R_OUT_PWM_data;
	PWM_ON();
	B=1;
	for(i=0;i<=d_read_haveLMAX;i++)
	{
		if(B)
		{
			B=0;
			if(Read_outI_Data_1C()>250)
				break;
		}
		for(;R_OUT_PWM_data<=R_read_haveL[i];R_OUT_PWM_data++)
		{
			OUT_PWM_Wdata(&R_OUT_PWM_data);
			Delay_Nus(4);
			B=1;
		}
	}
	if(PWM<R_read_haveL[i])
		Delay_Nus(60);
	LR=ReadLoad_Data();
	while(R_OUT_PWM_data>PWM)
	{
		R_OUT_PWM_data--;
		OUT_PWM_Wdata(&R_OUT_PWM_data);
		Delay_Nus(2);
	}
	if(!B_Out_Yes)
	{
		PWM_OFF();
	}
	return	LR;
}



#define Vout_GPIO_PIN       LL_GPIO_PIN_0
#define Vout_GPIO_PORT    	GPIOB

u8	B_VoutADC_Use=1;

void	Enable_VoutADC_Use(void)
{
	 LL_GPIO_InitTypeDef GPIO_InitStruct;
	B_VoutADC_Use=1;
	/*配置成ADC口*/
	GPIO_InitStruct.Pin = Vout_GPIO_PIN;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(Vout_GPIO_PORT, &GPIO_InitStruct);
}

void	Disable_VoutADC_Use(void)
{
	LL_GPIO_InitTypeDef    GPIO_InitStructure;
	B_VoutADC_Use=0;
	/*配置成普通IO口*/
	LL_GPIO_SetOutputPin(Vout_GPIO_PORT,Vout_GPIO_PIN);
	GPIO_InitStructure.Pin = Vout_GPIO_PIN;
  GPIO_InitStructure.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;
  GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStructure.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(Vout_GPIO_PORT, &GPIO_InitStructure);

}


//////////读电阻值
void Read_load(void)
{
	u16 LR;
	static 	u16	LR_S[6];
	static	u8	LR_i=0;
//	static	u8	XX_i=0;
	static	u8	XX_max=0;
	static	u16	Res_max;
	static	u16	Res_min;
	static	u32	Res_SUM;

	if(B_Out_Yes || B_BAT_error || (B_System_off!=d_System_Normal && (R_Res_average<d_Res_min || R_Res_average>=d_Res_max)))
	{
		B_Again_Read=1;
		LR_i=0;
		return;
	}

	if(!R_Read_Rtim)
	{
		R_Read_Rtim=500;
		if(B_VoutADC_Use)
		{
			LR=Read_L_1C();
		}
		else
		{
			Enable_VoutADC_Use();
			Delay_Nus(500);
			LR=Read_outV_Data();
			B_VoutADC_Use=0;
		}
		if(!B_have_Atomizer)
		{
			B_Sleep_YES=0;
			if(B_VoutADC_Use)
			{
				if(LR<d_Res_min)
				{
					R_Res_average=LR;
					R_Res_Initial=R_Res_average;
					B_Again_Read=1;
					B_Atomizer_inquiry=0;
					Enable_VoutADC_Use();
				}
				else if(LR>=d_Res_max)
				{
					R_Res_average=d_Res_max;
					R_Res_Initial=R_Res_average;
					B_Again_Read=1;
					B_Atomizer_inquiry=0;
					Disable_VoutADC_Use();
				}
				else
				{
					R_Read_Rtim=50;
					if(B_Again_Read)
					{
						LR_i=0;
						XX_max=0;
						B_Again_Read=0;
					}
					if(LR_i==0)
					{
//						XX_i=0;
						Res_SUM=0;
						Res_min=0xffff;
						Res_max=0;
					}

					LR_i++;
					if(LR>Res_max)
					{
						Res_max=LR;
					}
					if(LR<Res_min)
					{
						Res_min=LR;
					}
					Res_SUM+=LR;
					if(LR_i>1 && XX_max<30)
					{
						if(Res_min*105/100<Res_max)
						{
							XX_max+=LR_i;
							LR_i=0;
						}
					}
//					if(LR_i>7)
//					{
//						if((LR+LR*1/100)<(Res_SUM-Res_min-Res_max)/(LR_i-2))
//						{
//							XX_i++;
//						}
//					}
					if(LR_i>=12)
					{
						//XX_max++;
						//if(XX_max>4 || XX_i<3)
						//{
							R_Res_average=(Res_SUM-Res_min-Res_max)/10;
							if(B_LOCK_Res)
								R_Res_Initial=R_Res_Initial_jiyi;
							else
								R_Res_Initial=R_Res_average;
							if(R_Res_average<=d_Res_usable)
								B_Atomizer_inquiry=1;
							B_have_Atomizer=1;
							LR_i=0;
							Disable_VoutADC_Use();
						//}
//						else
//						{
//							LR_i=0;
//						}
					}
				}
			}
			else
			{
				if(LR>30)
					Disable_VoutADC_Use();
				else
					B_VoutADC_Use=1;
			}
		}
		else
		{
			if(B_VoutADC_Use)
			{
				if(B_Sleep_YES)
				{
					R_Read_Rtim=50;
				}
				if(LR>=d_Res_max)
				{
					B_Sleep_YES=0;
					R_Res_average=d_Res_max;
					R_Res_Initial=R_Res_average;
					B_have_Atomizer=0;
					B_Again_Read=1;
					B_Atomizer_inquiry=0;
					Disable_VoutADC_Use();
				}
				else if(LR<d_Res_min)
				{
					B_Sleep_YES=0;
					if(R_Res_average>=d_Res_min)
					{
						R_Res_Initial_Q=R_Res_Initial;
						R_Res_average_Q=R_Res_average;
					}
					R_Res_average=LR;
					R_Res_Initial=R_Res_average;
					Enable_VoutADC_Use();
				}
				else
				{
					if(R_Res_average<d_Res_min)
					{
						R_Res_Initial=R_Res_Initial_Q;
						R_Res_average=R_Res_average_Q;
					}

					if(B_Sleep_YES==1)
					{
						if(LR*11/10<R_Res_average)
						{
							B_Sleep_YES=3;
							LR_i=0;
						}
						else if(LR<(R_Res_Sleep+R_Res_Sleep*1/10))
						{
							B_Sleep_YES=0;
							Disable_VoutADC_Use();
						}
						else
						{
							B_Sleep_YES=2;
							LR_i=0;
						}
					}
					else if(B_Sleep_YES==4)
					{
						if(LR*11/10<R_Res_average)
						{
							B_Sleep_YES=3;
							LR_i=0;
						}
						else
						{
							B_Sleep_YES=0;
							Disable_VoutADC_Use();
						}
					}
					if(B_Sleep_YES)
					{
						LR_S[LR_i]=LR;
						LR_i++;
						if(LR_i>5)
						{
							Res_SUM=0;
							Res_min=0xffff;
							Res_max=0;
							for(LR_i=0;LR_i<6;LR_i++)
							{
								if(LR_S[LR_i]>Res_max)
								{
									Res_max=LR_S[LR_i];
								}
								if(LR_S[LR_i]<Res_min)
								{
									Res_min=LR_S[LR_i];
								}
								Res_SUM+=LR_S[LR_i];
							}
							LR_i=0;
							if(Res_min*105/100>Res_max)
							{
								Res_SUM=(Res_SUM-Res_min-Res_max)/4;
								if(B_Sleep_YES==2)
								{
									if((R_Res_Sleep*105/100)<Res_SUM && (R_Res_Sleep+10)<Res_SUM)
									{
										R_Res_average=Res_SUM;
										if(B_LOCK_Res)
											R_Res_Initial=R_Res_Initial_jiyi;
										else
											R_Res_Initial=R_Res_average;
										if(R_Res_average<=d_Res_usable)
											B_Atomizer_inquiry=1;
									}
								}
								else if(B_Sleep_YES==3)
								{
									if((Res_SUM*105/100)<R_Res_average && (Res_SUM+5)<R_Res_average)
									{
										R_Res_average=Res_SUM;
										if(!B_LOCK_Res && R_Res_average<R_Res_Initial)
											R_Res_Initial=R_Res_average;
									}
								}
							}
							Disable_VoutADC_Use();
							B_Sleep_YES=0;
						}
					}
					else
					{
						Disable_VoutADC_Use();
					}
				}
			}
			else
			{
				if(LR<30)
					Disable_VoutADC_Use();
				else
					B_VoutADC_Use=1;
			}
		}
	}
}


////////////////////////////////////////////////
//NI200发热丝最大输出功率为50.0W，变化率不可调
Load_Data		Load_Ni200={
	.WattsMAX=75,
	.Gradient=550
};

//Ti发热丝最大输出功率为50.0W，变化率不可调
Load_Data		Load_Ti={
	.WattsMAX=75,
	.Gradient=320
};

//Ss发热丝最大输出功率为50.0W，变化率不可调
Load_Data		Load_Ss316={
	.WattsMAX=115,
	.Gradient=105
};

Load_Data	*Atomizer_Pointer[]={&Load_Ni200,&Load_Ti,&Load_Ss316};

//TCR	M1
Load_Data		Load_M1={
	.WattsMAX=75,
	.Gradient=100
};

//TCR	M2
Load_Data		Load_M2={
	.WattsMAX=75,
	.Gradient=100
};

//TCR	M3
Load_Data		Load_M3={
	.WattsMAX=75,
	.Gradient=100
};

Load_Data	*TCR_Pointer[]={&Load_M1,&Load_M2,&Load_M3};

