
#include	"APP_Delay.h"
#include "APP_PWM_int.h"

/*���PWM���õײ� BEGIN*******/

s16	R_OUT_PWM_data=0;				//PWMռ�ձ�0~150


void	OUT_PWM_Wdata(s16* data)
{
	s16	Buck_a,BOOST_b;
	if(*data>d_OUT_PWM_max)
	{
		*data=d_OUT_PWM_max;
	}
	else	if(*data<0)
	{
		*data=0;
	}

	if(*data>=d_OUT_PWM_Period)//��ѹ
	{
		Buck_a = d_OUT_PWM_Period;
		BOOST_b = *data-d_OUT_PWM_Period;
	}
	else
	{
		BOOST_b = 0;
		Buck_a = *data;
	}

	if(Buck_a>d_OUT_PWM_Period-2)
		Buck_a=d_OUT_PWM_Period-2;
	if(BOOST_b<3)
		BOOST_b=3;

	Set_OUT_Buck_PWM_Data(Buck_a);
	Set_OUT_BOOST_PWM_Data(BOOST_b);
}
void	PWM_ON(void)
{
	OUT_En_DCDC_ON();
}

void	PWM_OFF(void)
{
	while(R_OUT_PWM_data)
	{
		R_OUT_PWM_data--;
		OUT_PWM_Wdata(&R_OUT_PWM_data);
		Delay_Nus(1);
	}
	Set_OUT_Buck_PWM_Data(0);
	Set_OUT_BOOST_PWM_Data(0);
	R_OUT_PWM_data=0;
	OUT_En_DCDC_OFF();
}

/*���PWM���õײ� END*******/


/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


/*���PWM���õײ� BEGIN*******/

s16	R_BAT_PWM_data=0;
u8	B_BAT_PWM_EN=0;

void	BAT_PWM_Wdata(s16* data)
{
	if(!B_BAT_PWM_EN)
	{
		*data=0;
		Set_BAT_BOOST_PWM_Data(0);
		Set_BAT_Buck_PWM_Data(0);
		return;
	}
	if(*data>d_BAT_PWM_max)
	{
		*data=d_BAT_PWM_max;
	}
	else	if(*data<0)
	{
		*data=0;
	}
	if(*data>d_BAT_PWM_Period)
	{
		Set_BAT_Buck_PWM_Data(d_BAT_PWM_Period);
		Set_BAT_BOOST_PWM_Data(*data-d_BAT_PWM_Period);
	}
	else
	{
		Set_BAT_BOOST_PWM_Data(0);
		Set_BAT_Buck_PWM_Data(*data);
	}
}

void	BAT_PWM_EN(u8	B)
{
	if(B_BAT_PWM_EN!=B)
	{
		B_BAT_PWM_EN=B;
		R_BAT_PWM_data=0;
		Set_BAT_BOOST_PWM_Data(0);
		Set_BAT_Buck_PWM_Data(0);
	}
}

/*���PWM���õײ� END*******/


/*����PWM���õײ� BEGIN*******/
u16	R_BL_PWM_Data=0;
void	BL_PWM_Wdata(s16 data)
{
	R_BL_PWM_Data=data+d_BL_PWM_min;
}
void	BL_PWM_OFF(void)
{
	R_BL_PWM_Data=0;
}
/*����PWM���õײ� END*******/


/*�����PWM���õײ� BEGIN*******/
u16	R_MOTOR_PWM_Data=0;
void	MOTOR_PWM_Wdata(s16 data)
{
	R_MOTOR_PWM_Data=data;
}
void	MOTOR_PWM_OFF(void)
{
	R_MOTOR_PWM_Data=0;
}
/*�����PWM���õײ� END*******/

/*������PWM���õײ� BEGIN*******/
u16	R_KEY_LED_PWM_Data=0;
void	KEY_LED_Wdata(s16 data)
{
	R_KEY_LED_PWM_Data=data;
}
void	KEY_LED_PWM_OFF(void)
{
	R_KEY_LED_PWM_Data=0;
}
/*������PWM���õײ� END*******/

/*������PWM���õײ� BEGIN*******/
u16	R_LOGO_LED_PWM_Data=0;
void	LOGO_LED_Wdata(s16 data)
{
	R_LOGO_LED_PWM_Data=data;
}
void	LOGO_LED_PWM_OFF(void)
{
	R_LOGO_LED_PWM_Data=0;
}
/*������PWM���õײ� END*******/


