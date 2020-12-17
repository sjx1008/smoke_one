#include "main.h"
#include "main_2.h"

u8	R_Set_Vibrate=10;

static	uc8	Vibrate_Strength_BUFF[][2]={{0,100},{1,100},{2,100},{3,100},{4,100},{5,100},{6,100},{7,100},{8,100},{9,100},{10,100}};
//static	uc8	Vibrate_Strength_BUFF[][2]={{10,0},{10,8},{10,16},{10,24},{10,32},{10,40},{10,48},{10,56},{10,64},{10,72},{10,80}};

//static	uc8	Vibrate_Strength_BUFF[][2]={{10,0},{10,10},{10,20},{10,30},{10,40},{10,50},{10,60},{10,70},{10,80},{10,90},{10,100}};


u16	R_Vibrate_ON_Tim=0;//振子开启时间
u8	B_Vibrate_ENABLE=1;//使能按下震动


void	Vibrate_ON(u16	tim,u8	Strength)
{
	if(R_Vibrate_ON_Tim<tim)
	{
		R_Vibrate_ON_Tim=tim;
		if(R_Set_Vibrate==0)
			MOTOR_PWM_Wdata(0);
		else
			MOTOR_PWM_Wdata((Strength-1)*(d_MOTOR_PWM_max-d_MOTOR_PWM_min)/(d_Vibrate_Max-1)+d_MOTOR_PWM_min);
	}
}

void	Vibrate_drive(void)
{
	if(R_Vibrate_ON_Tim)
	{
		R_Vibrate_ON_Tim--;
	}
	else
	{
		MOTOR_PWM_OFF();
	}
	Get_MOTOR_PWM_Data=R_MOTOR_PWM_Data;
//	if(Get_MOTOR_PWM_Data<R_MOTOR_PWM_Data)
//			Get_MOTOR_PWM_Data++;
//	else if(Get_MOTOR_PWM_Data>R_MOTOR_PWM_Data)
//			Get_MOTOR_PWM_Data--;
}

static	u8	R_KEY_Data=0;
void	Vibrate_program(void)
{
//	u8	B;
//	if(R_KEY_Data!=key_value)
//	{
//		if(B_OLED_BL && B_Vibrate_ENABLE)
//		{
//			B=0;
//			if(((R_KEY_Data&KEY_ADD)==0) && (key_value&KEY_ADD))
//				B=1;
//			if(((R_KEY_Data&KEY_SUB)==0) && (key_value&KEY_SUB))
//				B=1;
//			if(((R_KEY_Data&KEY_MODE)==0) && (key_value&KEY_MODE))
//				B=1;
//			if(B)
//			{
//				Vibrate_ON(Vibrate_Strength_BUFF[R_Set_Vibrate][1],Vibrate_Strength_BUFF[R_Set_Vibrate][0]);
//			}
//		}
//		R_KEY_Data=key_value;
//	}

	u8	B=0;

	if(key_value&KEY_MODE_SUB_ADD)
	{
		B=1;
	}

	if(R_KEY_Data!=B)
	{
		R_KEY_Data=B;
		if(R_KEY_Data&&B_OLED_BL && B_Vibrate_ENABLE)
		{
			Vibrate_ON(Vibrate_Strength_BUFF[R_Set_Vibrate][1],Vibrate_Strength_BUFF[R_Set_Vibrate][0]);
		}
	}
}

void	Vibrate_EN(u8	B)
{
	B_Vibrate_ENABLE=B;
}



