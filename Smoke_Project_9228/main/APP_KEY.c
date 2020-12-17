#include "main_2.h"
#include "APP_KEY.h"
#include "WM_Disp.h"

#define	d_KEY_TOUCH

u8	B_KEY_JC;
u8	R_KEY_timMax;
vu8	R_KEY_timi;

/*鎸夐敭婊ゆ尝澶勭悊*/
u8	Key_LB_value;	//婊ゆ尝鍚庣殑缁撴灉
static  u8	Key_LB_i;			//鎸夐敭婊ゆ尝璁℃暟鍣?
static  u8	Key_LB_data;	//閿�?
static  u8	Key_LB_data_Q;	//涔嬪墠鐨勯敭鍊?
void	KEY_Filter_processing(void)
{
	Key_LB_data=0;

	if(!KEY_1_RinBit)
		Key_LB_data |= 0x01;
	#ifdef	d_KEY_TOUCH
	if(B_OLED_BL)
	{
	#endif
	if(KEY_2_RinBit)
		Key_LB_data |= 0x02;
	if(KEY_3_RinBit)
		Key_LB_data |= 0x04;
	if(KEY_4_RinBit)
		Key_LB_data |= 0x08;
	#ifdef	d_KEY_TOUCH
	}
	#endif
	if(Key_LB_data_Q==Key_LB_data)
	{
		if(Key_LB_i<10)
			Key_LB_i++;
		else
		{
			Key_LB_value=Key_LB_data;
		}
	}
	else
	{
		Key_LB_i=0;
		Key_LB_data_Q=Key_LB_data;
	}
	Smoking_KEY_anxia_JC();
}


/****************************************************************************/

u8	R_key_anxia;				//按下
u8	R_key_Open;					//松开
u8	R_key_anxiaOpen;		//短按松开
u8	R_key_anzhuOpen;		//长按松开
u8	R_key_keep;					//长按按下
u8	R_key_super_keep;		//超长按按下
u8	R_key_1C;						//按键1次
u8	R_key_3C;						//按键3次
u8	R_key_5C;						//按键5次
u8	R_key_XC;
u8	R_key_XC_Data;
u8	R_key_anzhu;				//长按按住

u8	B_Key_release;			//是否返回按键键值，按键全部释放才清零

u8  key_value=0;//当前按键值寄存器

//KEY_bit	R_KEY_UP=KEY_ADD;
//KEY_bit	R_KEY_DOWN=KEY_SUB;


void Key_scan(void)  // uint8
{

//	static  u8   key_delay=0;//按键去抖动寄存器
//	static  u8   key_value0=0;//前一次按键值寄存器
	static  u8   key_value1=0;    //按键释放后的按键值寄存器
	static  u8   key_value2=0;    //按键释放后的按键值寄存器
	static  u8   key_longtime=0;//长按时间累积寄存器1
	static  u8   key_longtime1=0;//长按时间累积寄存器2
	static  u8   key_super_longtime=0;	//超长按时间累积寄存器
	static  u8   F_longkey=0;//长按
	static  u8   F_super_longkey=0;//超长按
	static 	u8	 f_onkey=0;
	static 	u8 	 Key_Hda;
	static	u8 	 KEY_data=0;
	static	u8	 B_anxiaOpen_EN=0;
	static	u8	 B_f_onkey=0;

	key_value=Key_LB_value;
//	if(key_value&KEY_MODE)
//		key_value=key_value&(~KEY_ADD_SUB);
	Vibrate_program();
	Key_smoke();
//	if(!KEY_1_RinBit)
//		key_value |= 0x01;
//	if(!KEY_2_RinBit)
//		key_value |= 0x02;
//	if(!KEY_3_RinBit)
//		key_value |= 0x04;

//	if(key_value==key_value0)//????,???????,??????,?????
	{
//		if(key_delay>0)//????
		{
			if(key_value>0)//???????,??0??????,??????
			{
				if(!f_onkey)
				{
					f_onkey=1;
					if(key_value!=key_value2)
					{
						KEY_data=0;
					}

					Key_Hda=0;
					if(key_value2==KEY_M && KEY_data==4)
					{
						KEY_data=0;
						R_key_5C=KEY_M;
					}
					if(!B_Key_release)
						R_key_anxia=key_value;

					key_value1=key_value;
					key_value2=key_value;
				}
				else
				{//按键长按
					if(key_longtime<15)//
					{
						key_longtime++;
						if(key_value1!=key_value)
						{
							R_key_anxia=key_value;
							key_longtime1=0;
							B_anxiaOpen_EN=1;
						}
						key_value1=key_value;
						key_value2=key_value;
					}
					if(key_value==key_value1 && key_value2==key_value)
					{
						if(!F_longkey)
						{
							if(++key_longtime1>=20)
							{
								key_longtime1=0;//

								F_longkey=1;
								//长按按键处理程序
								KEY_data=0;
								if(!B_Key_release)
								{
									R_key_keep=key_value;
								}
							}
						}
						else
						{
							if(!B_Key_release)
								R_key_anzhu=key_value1;
							if(!F_super_longkey)
							{
								if(++key_super_longtime>=15)
								{
									key_super_longtime=0;//
									F_super_longkey=1;
									//超长按按键处理程序
									if(!B_Key_release)
									{
										R_key_super_keep=key_value1;
									}
								}
							}
							key_value2=key_value;
						}
					}
					else	if((key_value&key_value1)==0)
					{
						if(F_longkey)
						{
							if(!B_Key_release)
								R_key_anzhuOpen=key_value1;
						}
						key_longtime=0;
						key_longtime1=0;//3????
						key_super_longtime=0;
						key_value1=key_value;
						key_value2=key_value;
					}
					else	if((key_value&key_value1) &&(key_value!=key_value1))
					{
						key_value2=key_value;
					}
				}
			}
			else//????
			{
				key_longtime=0;
				key_longtime1=0;
				key_super_longtime=0;
				if(F_longkey)
				{//长按按键释放
					KEY_data=0;
					F_super_longkey=0;
					if(!B_Key_release)
						R_key_anzhuOpen=key_value1;
					B_f_onkey=0;
				}
				else if(f_onkey)
				{//短按按键释放
					B_f_onkey=1;
					if(!B_Key_release)
					{
						if(key_value1>0)
						{
							if(KEY_data<5)
							{
								KEY_data++;
							}
						}
					}
					if(!B_Key_release && !B_anxiaOpen_EN)
						R_key_anxiaOpen=key_value1;
				}

				if(key_value2>0)
				{
					if(Key_Hda<18)
					{
						Key_Hda++;
					}
					else
					{

						if(!B_Key_release && B_f_onkey)
						{
							switch(KEY_data)
							{
								case	1:	R_key_1C=key_value2;break;
								case	3:	R_key_3C=key_value2;break;
								case	5:	R_key_5C=key_value2;break;
							}
							R_key_XC=key_value2;
							R_key_XC_Data=KEY_data;
						}
						KEY_data=0;
						key_value2=0;
					}
				}

				f_onkey=0;
				F_longkey=0;
				if(!B_Key_release)
					R_key_Open=key_value1;
				else
				{
					B_Key_release=0;
					KEY_data=0;
				}
				B_anxiaOpen_EN=0;
				key_value1=0;
			}
		}
//		else  //有按键
//		{
//			key_delay++;
//		}
	}
//	else
//	{
//		key_value0=key_value;
//		key_delay=0;
//	}

}
u8	R_key_super_keep_Mode;
u8	R_key_3C_Mode;
u8	R_key_anzhuOpen_Mode;
u8	R_key_XC_Data_Mode;
u8	R_key_XC_Mode;
u8	R_key_anxia_Mode;
u8	R_key_anxiaOpen_Mode;
void KeyMODE_scan(void)  // uint8
{
	static	u8	 key_valueMode=0;
	static  u8   key_value1=0;    //按键释放后的按键值寄存器
	static  u8   key_value2=0;    //按键释放后的按键值寄存器
	static  u8   key_longtime=0;//长按时间累积寄存器1
	static  u8   key_longtime1=0;//长按时间累积寄存器2
	static  u8   key_super_longtime=0;	//超长按时间累积寄存器
	static  u8   F_longkey=0;//长按
	static  u8   F_super_longkey=0;//超长按
	static 	u8	 f_onkey=0;
	static 	u8 	 Key_Hda;
	static	u8 	 KEY_data=0;
	static	u8	 B_anxiaOpen_EN=0;
	static	u8	 B_f_onkey=0;

	key_valueMode=Key_LB_value&(~KEY_ADD_SUB);
	if(key_valueMode>0)//???????,??0??????,??????
	{
		if(!f_onkey)
		{
			f_onkey=1;
			if(key_valueMode!=key_value2)
			{
				KEY_data=0;
			}

			Key_Hda=0;
			if(!B_Key_release)
				R_key_anxia_Mode=key_valueMode;

			key_value1=key_valueMode;
			key_value2=key_valueMode;
		}
		else
		{//按键长按
			if(key_longtime<15)//
			{
				key_longtime++;
				if(key_value1!=key_valueMode)
				{
					R_key_anxia_Mode=key_valueMode;
					key_longtime1=0;
					B_anxiaOpen_EN=1;
				}
				key_value1=key_valueMode;
				key_value2=key_valueMode;
			}
			if(key_valueMode==key_value1 && key_value2==key_valueMode)
			{
				if(!F_longkey)
				{

					if(++key_longtime1>=20)
					{
						key_longtime1=0;//

						F_longkey=1;
						//长按按键处理程序
						KEY_data=0;
//						if(!B_Key_release)
//							R_key_keep=key_valueMode;
					}
				}
				else
				{
//					if(!B_Key_release)
//						R_key_anzhu=key_value1;
					if(!F_super_longkey)
					{
						if(++key_super_longtime>=15)
						{
							key_super_longtime=0;//
							F_super_longkey=1;
							//超长按按键处理程序
							if(!B_Key_release)
								R_key_super_keep_Mode=key_value1;
						}
					}
					key_value2=key_valueMode;
				}
			}
			else	if((key_valueMode&key_value1)==0)
			{
				if(F_longkey)
				{
					if(!B_Key_release)
						R_key_anzhuOpen_Mode=key_value1;
				}
				key_longtime=0;
				key_longtime1=0;//3????
				key_super_longtime=0;
				key_value1=key_valueMode;
				key_value2=key_valueMode;
			}
			else	if((key_valueMode&key_value1) &&(key_valueMode!=key_value1))
			{
				key_value2=key_valueMode;
			}
		}
	}
	else//????
	{
		key_longtime=0;
		key_longtime1=0;
		key_super_longtime=0;
		if(F_longkey)
		{//长按按键释放
			KEY_data=0;
			F_super_longkey=0;
			if(!B_Key_release)
				R_key_anzhuOpen_Mode=key_value1;
			B_f_onkey=0;
		}
		else if(f_onkey)
		{//短按按键释放
			B_f_onkey=1;
			if(!B_Key_release)
			{
				if(key_value1>0)
				{
					if(KEY_data<5)
					{
						KEY_data++;
					}
				}
			}
			if(!B_Key_release && !B_anxiaOpen_EN)
				R_key_anxiaOpen_Mode=key_value1;
		}

		if(key_value2>0)
		{
			if(Key_Hda<18)
			{
				Key_Hda++;
			}
			else
			{

				if(!B_Key_release && B_f_onkey)
				{
					switch(KEY_data)
					{
//						case	1:	R_key_1C=key_value2;break;
						case	3:	R_key_3C_Mode=key_value2;break;
//						case	5:	R_key_5C=key_value2;break;
					}
					R_key_XC_Mode=key_value2;
					R_key_XC_Data_Mode=KEY_data;
				}
				KEY_data=0;
				key_value2=0;
			}
		}

		f_onkey=0;
		F_longkey=0;
		if(B_Key_release)
//			R_key_Open=key_value1;
		//else
		{
//			B_Key_release=0;
			KEY_data=0;
		}
		B_anxiaOpen_EN=0;
		key_value1=0;
	}
}
/*******************************************************************************/
u8	B_USB_RinBit;
//////////////////USB读键值//////////////////////
////        0:松开     1:插入
/////////////////////////////////////////////////
u8	B_USB_Low;
u8	B_testing_IC=0;		//判断是哪种充电IC
u16	R_testing_IC_Tim=0;
void USB_T_data(void)
{
	static u8 Key_Lda,Key_Hda;
	u16		USB_V;
	if(!B_BAT_Charge && !B_USB_Low)
	{
		if(USB_T_RinBit)
		{
			B_USB_RinBit=1;
			if(!B_BAT_error)
			{
				Key_Hda=25;
				Set_BAT_Buck_PWM_Data(8);
				Set_BAT_BOOST_PWM_Data(d_BAT_PWM_Period-8);
				if(Key_Lda<25)
				{
					Key_Lda++;
				}
				else
				{
					Key_Lda=0;
					if(R_SleepTim<5)
						R_SleepTim=5;
					//配置为模拟口
					USB_GPIO_Set(USB_AIN);
					USB_V=Read_USBV_Data();

					R_USB_error_i=0;
					R_last5M[0]=0;
					R_last5M[1]=0;
					R_Charging_Tim=0;
					R_Batter_Interface_Tim=0;
					R_Charg_I_Set=50;
					BATT_Charging_Count_down_Init();
					R_Charging_current_average=0;
					R_USB_Charging_current_average=0;
					F_BAT_Actual_Inti();

					if(USB_V<450 || USB_V>580)
					{
						B_USB_Low=1;
						R_USB_error_Tim=35;
						R_Skinning_mode=USB_anomaly;
						return;
					}
					Set_BAT_Buck_PWM_Data(0);
					Set_BAT_BOOST_PWM_Data(0);
					B_USB_Low=0;
					B_BAT_Charge=1;
					B_Fast_Charg=0;
					R_Skinning_mode=USB_access;
				}
			}
			else
			{
				Key_Lda=0;
				if(Key_Hda)
					Key_Hda--;
				else
				{
					Set_BAT_BOOST_PWM_Data(0);
					Set_BAT_Buck_PWM_Data(0);
				}
			}
		}
		else
		{
			Key_Lda=0;
			if(Key_Hda)
				Key_Hda--;
			else
			{
				Set_BAT_BOOST_PWM_Data(0);
				Set_BAT_Buck_PWM_Data(0);
			}
			B_USB_RinBit=0;
		}
	}
}
u8	B_InterfaceGOTO=0;
///按键处理
void KEY_ALL_Task(void)
{
	if(B_KEY_JC)
	{
		B_KEY_JC=0;
		KeyMODE_scan();
		Key_scan();
		USB_T_data();
		B_InterfaceGOTO=1;
		Interface_display();
		B_InterfaceGOTO=0;
	}
}

void	KEY_TFT_RESET(void)
{
	if(B_KEY_JC)
	{
		B_KEY_JC=0;
		B_InterfaceGOTO=0;
		Key_scan();
		KeyMODE_scan();
		Read_load();
		B_InterfaceGOTO=1;
	}
}
/***********************************************************************************************/




//加减操作  //xh=0:加减不做循环  xh=1:加减到最大再次按下循环 xh=2：循环
u16	KEY_R_ADD_SUB(u8 *KEY,s16	R,u8 KADD,u8 KSUB,s16 max,s16 min,s8 bu,u8 xh,u8 tim)
{
	static	u8	B;

	if((R==max || R==min)&&xh==1)
	{
		if(R_key_anxia==KADD || R_key_anxia==KSUB)
			B=1;
	}
	else
	{
		B=0;
	}


	if(*KEY==KADD)
	{
		if(R<max)
		{
			R+=bu;
			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		}
		else if(xh)
		{
			R=min;
		}
	}
	else	if(*KEY==KSUB)
	{
		if(R>min)
		{
			R-=bu;
			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		}
		else if(xh)
		{
			R=max;
		}
	}

	if(R_key_anzhu==KADD)
	{
		if(!R_KEY_timi)
		{
			if(R_KEY_timMax>tim)
			{
				R_KEY_timMax-=5;
			}
			R_KEY_timi=R_KEY_timMax;
			if(R<max)
			{
				R+=bu;
				R_Bright_screen_Time=R_Bright_screen_TimeMAX;
			}
			else if(xh==2 || B)
			{
				R=min;
			}
		}
	}
	else	if(R_key_anzhu==KSUB)
	{
		if(!R_KEY_timi)
		{
			if(R_KEY_timMax>tim)
			{
				R_KEY_timMax-=5;
			}
			R_KEY_timi=R_KEY_timMax;
			if(R>min)
			{
				R-=bu;
				R_Bright_screen_Time=R_Bright_screen_TimeMAX;
			}
			else if(xh==2 || B)
			{
				R=max;
			}
		}
	}
	else if(!R_key_anzhu)
	{
		R_KEY_timMax=150;
	}
	if(R>max)
		R=max;
	else if(R<min)
		R=min;
	return R;
}




