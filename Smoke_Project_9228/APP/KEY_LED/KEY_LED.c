/* 梅工
2018/08/02
亮度改为8级
时长改为30S
*/
#include "main.h"
#include "main_2.h"

#define	d_LED_Tim		290
u8	R_Set_KEY_LED_Brig=8;		//设置按键灯亮度等级
static	u8	R_KEY_LED_Brig=0;					//实际按键灯亮度等级
static	uc8	KEY_LED_Brig_BUFF[]={0,10,22,34,46,58,70,82,100};


//void	KEY_LED_drive(void)
//{
//	if(B_OLED_BL && R_Set_KEY_LED_Brig)
//	{
//		if((s16)(R_Bright_screen_TimeMAX-R_Bright_screen_Time)>150)
//		{
//			if(R_KEY_LED_Brig!=0)
//			{
////				R_KEY_LED_Brig=1;
////				KEY_LED_Wdata(KEY_LED_Brig_BUFF[1]);
//				R_KEY_LED_Brig=0;
//				KEY_LED_PWM_OFF();
//			}
//		}
//		else
//		{
//			if(R_Set_KEY_LED_Brig!=R_KEY_LED_Brig)
//			{
//				R_KEY_LED_Brig=R_Set_KEY_LED_Brig;
//				KEY_LED_Wdata(KEY_LED_Brig_BUFF[R_Set_KEY_LED_Brig]);
//			}
//		}
//	}
//	else
//	{
//		R_KEY_LED_Brig=0;
//		KEY_LED_PWM_OFF();
//	}
//}


#define		d_LOGO_LEDPwm_Max			100
#define		d_LOGO_LEDPwm_Dark		(d_LOGO_LEDPwm_Max/4)
static	u8	R_LOGO_LED_Brig=0;					//实际按键灯亮度等级
static	u8	B_LOGO_LED_Breathing=0;

//void	LOGO_LED_drive(void)
//{
//	if(B_BAT_Charge)
//	{
//		if(B_BAT_Congman && B_BAT_Congman2)
//		{
//			B_LOGO_LED_Breathing=0;
//			if(!B_OLED_BL || (s16)(R_Bright_screen_TimeMAX-R_Bright_screen_Time)>150)
//			{
//				LOGO_LED_PWM_OFF();
//			}
//			else
//			{
//				LOGO_LED_Wdata(d_LOGO_LEDPwm_Max);
//			}
//		}
//		else
//		{
//			B_LOGO_LED_Breathing=1;
//		}
//	}
//	else
//	{
//		B_LOGO_LED_Breathing=0;
////		if(B_OLED_BL)
////		{
////			if((s16)(R_Bright_screen_TimeMAX-R_Bright_screen_Time)>1200)
////			{
////				LOGO_LED_Wdata(d_LOGO_LEDPwm_Dark);
////			}
////			else
////			{
////				LOGO_LED_Wdata(d_LOGO_LEDPwm_Max);
////			}
////		}
////		else
////		{
////			LOGO_LED_PWM_OFF();
////		}
//		if(B_OLED_BL)
//		{
//			if((s16)(R_Bright_screen_TimeMAX-R_Bright_screen_Time)>150)
//			{
//				LOGO_LED_PWM_OFF();
//			}
//			else
//			{
//				LOGO_LED_Wdata(d_LOGO_LEDPwm_Max);
//			}
//		}
//		else
//		{
//			LOGO_LED_PWM_OFF();
//		}
//	}
//}
static	u8	LOGO_LED_PWM_Data=0;
//static	uc8	LOGO_PWM_BUFF[101]={
//0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,
//8,8,9,10,11,12,13,14,15,16,
//17,18,19,20,21,22,23,24,25,26,
//27,28,29,30,31,32,33,34,35,36,37,38,39,40,
//41,42,43,44,45,46,47,48,49,50,
//51,52,53,54,55,56,57,58,59,60,
//61,62,63,64,65,66,67,68,69,70,
//71,72,73,74,75,76,77,78,79,80,
//81,82,83,84,85,86,88,91,94,97,
//100
//};

/* ((SIN((x*45/100-90)*PI()/180))*100+100)/3*10 */
/* 1/4 的sin函数 */
static	uc8	LOGO_PWM_BUFF[101]={
 0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,3
,3,3,4,4,5,5,5,6,6,7,7,8,9,9,10,10
,11,12,13,13,14,15,16,16
,17,18,19,20,21,22,22,23
,24,25,26,27,28,30,31,32
,33,34,35,36,38,39,40,41
,43,44,45,46,48,49,50,52
,53,55,56,58,59,61,62,64
,65,67,68,70,72,73,75,76
,78,80,82,83,85,87,89,90
,92,94,96,98,99
};


void	LOGO_LED_Control(void)
{
	static	u8	B_ADD=0;
	if(B_LOGO_LED_Breathing)
	{
		if(B_ADD)
		{
			if(LOGO_LED_PWM_Data<100)
				LOGO_LED_PWM_Data++;
			else
				B_ADD=0;
		}
		else
		{
			if(LOGO_LED_PWM_Data)
				LOGO_LED_PWM_Data--;
			else
				B_ADD=1;
		}
		Get_LED2_PWM_Data=LOGO_PWM_BUFF[LOGO_LED_PWM_Data]*R_LOGO_LED_PWM_Data/100;
	}
	else
	{
		if(Get_LED2_PWM_Data>R_LOGO_LED_PWM_Data)
		{
			Get_LED2_PWM_Data--;
			B_ADD=0;
		}
		else	if(Get_LED2_PWM_Data<R_LOGO_LED_PWM_Data)
		{
			Get_LED2_PWM_Data++;
			B_ADD=1;
		}
	}
}


u16	KEY_LED_Tim=0;					//按键灯亮的时间
static	u8	R_KEY_Data=0;		//按键状态
static	u8	B_BL_ON=0;			//背光状态

void	LED_drive(void)
{
	static	u8	LED_Tim_LB=0;
	if(B_OLED_BL!=B_BL_ON)
	{
		LED_Tim_LB++;
		if(LED_Tim_LB>1)
		{
			LED_Tim_LB=0;
			B_BL_ON=B_OLED_BL;
			if(B_BL_ON)
				KEY_LED_Tim=d_LED_Tim;
			else
				KEY_LED_Tim=0;
		}
	}
	else
	{
		LED_Tim_LB=0;
	}
	if(B_OLED_BL)
	{
		if(R_KEY_Data!=key_value)
		{
			R_KEY_Data=key_value;
			KEY_LED_Tim=d_LED_Tim;
		}
	}
	/////////////////////////////////
	if(KEY_LED_Tim &&	B_System_off!=d_System_Off)
	{
		if(R_Set_KEY_LED_Brig!=R_KEY_LED_Brig)
		{
			R_KEY_LED_Brig=R_Set_KEY_LED_Brig;
			KEY_LED_Wdata(KEY_LED_Brig_BUFF[R_Set_KEY_LED_Brig]);
		}
	}
	else
	{
		R_KEY_LED_Brig=0;
		KEY_LED_PWM_OFF();
	}
	if(R_Set_KEY_LED_Brig)
	{
		if(B_BAT_Charge)
		{
			if(B_BAT_Congman && B_BAT_Congman2)
			{
				B_LOGO_LED_Breathing=0;
				if(KEY_LED_Tim)
				{
					R_LOGO_LED_Brig=R_Set_KEY_LED_Brig;
					LOGO_LED_Wdata(KEY_LED_Brig_BUFF[R_Set_KEY_LED_Brig]);
				}
				else
				{
					R_LOGO_LED_Brig=0;
					LOGO_LED_PWM_OFF();
				}
			}
			else
			{
				if(!B_LOGO_LED_Breathing)
				{
					B_LOGO_LED_Breathing=1;
					LOGO_LED_PWM_Data=Get_LED1_PWM_Data*100/R_LOGO_LED_PWM_Data;
				}
				if(R_Set_KEY_LED_Brig!=R_LOGO_LED_Brig)
				{
					R_LOGO_LED_Brig=R_Set_KEY_LED_Brig;
					LOGO_LED_Wdata(KEY_LED_Brig_BUFF[R_Set_KEY_LED_Brig]);
					LOGO_LED_PWM_Data=Get_LED1_PWM_Data*100/R_LOGO_LED_PWM_Data;
				}
			}
		}
		else
		{
			B_LOGO_LED_Breathing=0;
			if(KEY_LED_Tim)
			{
				if(R_Set_KEY_LED_Brig!=R_LOGO_LED_Brig)
				{
					R_LOGO_LED_Brig=R_Set_KEY_LED_Brig;
					LOGO_LED_Wdata(KEY_LED_Brig_BUFF[R_Set_KEY_LED_Brig]);
				}
			}
			else
			{
				R_LOGO_LED_Brig=0;
				LOGO_LED_PWM_OFF();
			}
		}
	}
	else
	{
		R_LOGO_LED_Brig=0;
		LOGO_LED_PWM_OFF();
	}
}








