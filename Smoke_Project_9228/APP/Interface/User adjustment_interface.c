#include "stm32f0xx.h"
#include "Stdint_2.h"
#include "WM_Disp.h"

static	u16	Res_Q;
static	void	Pint_Set_Watt(u16	R);
static	void	Pint_Set_Vout(u16	R);
static	void	Pint_Set_Temp(u16	R);

//显示瓦数
static	void	Pint_Set_Watt(u16	R)
{
	R_Back_Color=d_Clean_Color;
	R_Front_Color=d_Clean_Color;
	GUI_Write_block(5,6,43,24);
	R_Front_Color=d_Bright_Color;
	if(R<1000)
	{
		GUI_Write_data(5,24,2,R/10,ZT19,0);
		GUI_Write_data(33,24,1,R%10,ZT19,0);
		GUI_Write_block(29,22,31,24);
	}
	else
	{
		GUI_Write_data(8,24,3,R/10,ZT19,0);
	}
}
//显示电压
static	void	Pint_Set_Vout(u16	R)
{
	R_Back_Color=d_Clean_Color;
	R_Front_Color=d_Bright_Color;
	GUI_Write_data(5,24,1,R/100,ZT19,1);
	GUI_Write_data(21,24,2,R%100,ZT19,1);
}
//显示温度
static	void	Pint_Set_Temp(u16	R)
{
	R_Back_Color=d_Clean_Color;
	R_Front_Color=d_Bright_Color;
	GUI_Write_data(7,24,3,R,ZT19,0);
}

//显示瓦数强度
static	u8	R_Watt_Strength_X[]={18,22,18};
static	void	Prain_Watt_Strength(void)
{	
	u8	B;
	B=0;
	if(GUI_Read_Dot(16,50)==d_Bright_Color)
		B=1;
	Windows_Write_OFF();
	if(B)
		R_Front_Color=d_Bright_Color;
	else
		R_Front_Color=d_Clean_Color;
	GUI_Write_block(16,50,48,64);
	if(B)
	{
		R_Front_Color=d_Clean_Color;
		R_Back_Color=d_Bright_Color;
	}
	else
	{
		R_Front_Color=d_Bright_Color;
		R_Back_Color=d_Clean_Color;
	}
	GUI_Write_Chars(R_Watt_Strength_X[R_Watt_Strength],63,Watt_Strength_chars[R_Watt_Strength],ZT12);
	Windows_Write_ON();
}
//显示锁阻值的锁
static	uc8	Res_LOCK_LOGOH[]={5,4,0x70,0x88,0x88,0x88};
static	uc8	Res_LOCK_LOGOL[]={7,5,0xFE,0xC6,0xEE,0xEE,0xFE};
static	void	Prain_Res_LOCK(void)
{
	Windows_Write_OFF();
	R_Front_Color=d_Clean_Color;
	GUI_Write_block(44,70,53,73);
	R_Front_Color=d_Bright_Color;
	R_Back_Color=d_Clean_Color;
	if(B_LOCK_Res)
		GUI_Write_Bitmap(45,70,Res_LOCK_LOGOH);
	else
		GUI_Write_Bitmap(49,70,Res_LOCK_LOGOH);
	Windows_Write_ON();
}
//阻值更新
static	void	Res_update(void)
{
	u16	a;
	a=R_Res_Initial/10;
	if(a!=Res_Q)
	{
		Res_Q=a;
		R_Front_Color=d_Bright_Color;
		R_Back_Color=d_Clean_Color;
		GUI_Write_data(17,79,0,Res_Q/100,ZT12,0);
		GUI_Write_data(27,79,2,Res_Q%100,ZT12,1);
	}
}

//触摸操作
static	uc8	User_Press_box1[][4]={{1,95,31,125},{33,95,62,125},{2,41,61,73}};
static	uc8	TCR_Cursor_box1[][4]={{2,100,26,121},{37,100,61,121},{16,50,49,64}};
static	uc8	User_Press_box2[][4]={{1,95,31,125},{33,95,62,125},{2,26,61,56},{2,60,61,87}};
static	uc8	TCR_Cursor_box2[][4]={{2,100,26,121},{37,100,61,121},{16,35,49,49}};
typedef enum
{
	d_TP_KEY_SUB1,
	d_TP_KEY_ADD1,
	D_TP_KEY_STRENGTH,
	d_TP_KEY_NOP1=0xff,      			///无动作
}TP_KEY_enum1;
typedef enum
{
	d_TP_KEY_SUB2,
	d_TP_KEY_ADD2,
	D_TP_KEY_TCR,
	D_TP_KEY_LOCK,
	d_TP_KEY_NOP2=0xff,      			///无动作
}TP_KEY_enum2;
void	User_Data_touch(void)
{
	u16	R;
	u8	bujin;
	if(R_Work_mode==d_Watt_mode)
	{
		if(R_Button_anxia<3)
		{
			R_Front_Color=d_Transparent_Color;
			GUI_Write_block(TCR_Cursor_box1[R_Button_anxia][0],TCR_Cursor_box1[R_Button_anxia][1],TCR_Cursor_box1[R_Button_anxia][2],TCR_Cursor_box1[R_Button_anxia][3]);
		}
		if(R_Button_Open<3)
		{
			R_Front_Color=d_Transparent_Color;
			GUI_Write_block(TCR_Cursor_box1[R_Button_Open][0],TCR_Cursor_box1[R_Button_Open][1],TCR_Cursor_box1[R_Button_Open][2],TCR_Cursor_box1[R_Button_Open][3]);
		}
		if(R_Button_anxiaOpen==D_TP_KEY_STRENGTH)
		{
			R_Watt_Strength++;
			if(R_Watt_Strength>2)
				R_Watt_Strength=(Watt_Strength)0;
			Prain_Watt_Strength();
		}
		if(R_User_Watt_Set>1000 || (R_User_Watt_Set==1000 && (R_Button_anxiaOpen==d_TP_KEY_ADD1 || R_Button_anxiaOpen==d_TP_KEY_ADD1)))
		{
			bujin=10;
		}
		else
		{
			if(R_User_Watt_Set%10==0 && (R_Button_anzhu==d_TP_KEY_ADD1 || R_Button_anzhu==d_TP_KEY_SUB1))
				bujin=10;
			else
				bujin=1;
		}
		R=TP_R_ADD_SUB(&R_Button_anxiaOpen,R_User_Watt_Set,d_TP_KEY_ADD1,d_TP_KEY_SUB1,d_User_Watt_max,d_User_Watt_min,bujin,1,30);
		if(R!=R_User_Watt_Set)
		{
			R_User_Watt_Set=R;
			Windows_Write_OFF();
			Pint_Set_Watt(R_User_Watt_Set);
			Windows_Write_ON();
		}
	}
	else	if(R_Work_mode==d_Voltage_mode)
	{
		if(R_Button_anxia<2)
		{
			R_Front_Color=d_Transparent_Color;
			GUI_Write_block(TCR_Cursor_box1[R_Button_anxia][0],TCR_Cursor_box1[R_Button_anxia][1],TCR_Cursor_box1[R_Button_anxia][2],TCR_Cursor_box1[R_Button_anxia][3]);
		}
		if(R_Button_Open<2)
		{
			R_Front_Color=d_Transparent_Color;
			GUI_Write_block(TCR_Cursor_box1[R_Button_Open][0],TCR_Cursor_box1[R_Button_Open][1],TCR_Cursor_box1[R_Button_Open][2],TCR_Cursor_box1[R_Button_Open][3]);
		}
	
		if(R_User_Vout_Set%10==0 && (R_Button_anzhu==d_TP_KEY_ADD1 || R_Button_anzhu==d_TP_KEY_SUB1))
			bujin=10;
		else
			bujin=1;
		R=TP_R_ADD_SUB(&R_Button_anxiaOpen,R_User_Vout_Set,d_TP_KEY_ADD1,d_TP_KEY_SUB1,d_User_Vout_max,d_User_Vout_min,bujin,1,30);
		if(R!=R_User_Vout_Set)
		{
			R_User_Vout_Set=R;
			Pint_Set_Vout(R_User_Vout_Set);
		}
	}
	else
	{
		if(R_Button_anxia<3)
		{
			R_Front_Color=d_Transparent_Color;
			GUI_Write_block(TCR_Cursor_box2[R_Button_anxia][0],TCR_Cursor_box2[R_Button_anxia][1],TCR_Cursor_box2[R_Button_anxia][2],TCR_Cursor_box2[R_Button_anxia][3]);
		}
		if(R_Button_Open<3)
		{
			R_Front_Color=d_Transparent_Color;
			GUI_Write_block(TCR_Cursor_box2[R_Button_Open][0],TCR_Cursor_box2[R_Button_Open][1],TCR_Cursor_box2[R_Button_Open][2],TCR_Cursor_box2[R_Button_Open][3]);
		}
		if(R_Button_anxiaOpen==D_TP_KEY_TCR)
		{
			if(R_Work_mode==d_Temp_mode)
				R_TCR_SetProject=R_Atomizer;
			else
				R_TCR_SetProject=R_TCR_term+3;
			Left_slip_interface=Main_interface;				//左滑切换到的界面
			Right_slip_interface=User_Data_Set_interface;				//右滑切换到的界面
			Windows_Switch(TCR_Data_Set_interface);
		}
		else	if(R_Button_anxiaOpen==D_TP_KEY_LOCK)
		{
			if(B_LOCK_Res)
				B_LOCK_Res=0;
			else	if(R_Res_Initial>=d_Res_min && R_Res_Initial<d_Res_usable)
			{
				B_LOCK_Res=1;
				R_Res_Initial_jiyi=R_Res_Initial;
			}
			Prain_Res_LOCK();
		}		
		if(R_Temp_metric==C_metric)
		{
			R=TP_R_ADD_SUB(&R_Button_anxiaOpen,R_User_Temp_Set_C,d_TP_KEY_ADD2,d_TP_KEY_SUB2,d_User_TempC_max,d_User_TempC_min,1,1,30);
			if(R!=R_User_Temp_Set_C)
			{
				if(R==d_User_TempC_max	&& R_User_Temp_Set_C==d_User_TempC_min)
				{
					R_Temp_metric=F_metric;
					R_User_Temp_Set_F=d_User_TempF_max;
					R_Front_Color=d_Bright_Color;
					R_Back_Color=d_Clean_Color;
					GUI_Write_Bitmap(49,12,FMax_LOGO);
					Pint_Set_Temp(R_User_Temp_Set_F);
				}
				else	if(R==d_User_TempC_min	&& R_User_Temp_Set_C==d_User_TempC_max)
				{
					R_Temp_metric=F_metric;
					R_User_Temp_Set_F=d_User_TempF_min;
					R_Front_Color=d_Bright_Color;
					R_Back_Color=d_Clean_Color;
					GUI_Write_Bitmap(49,12,FMax_LOGO);
					Pint_Set_Temp(R_User_Temp_Set_F);
				}
				else
				{
					R_User_Temp_Set_C=R;
					R_User_Temp_Set_F=R_User_Temp_Set_C*9/5+32;
					if(R_User_Temp_Set_F<d_User_TempF_min)
						R_User_Temp_Set_F=d_User_TempF_min;
					else	if(R_User_Temp_Set_F>d_User_TempF_max)
						R_User_Temp_Set_F=d_User_TempF_max;
					Pint_Set_Temp(R_User_Temp_Set_C);
				}
			}
		}
		else
		{
			R=TP_R_ADD_SUB(&R_Button_anxiaOpen,R_User_Temp_Set_F,d_TP_KEY_ADD2,d_TP_KEY_SUB2,d_User_TempF_max,d_User_TempF_min,1,1,30);
			if(R!=R_User_Temp_Set_F)
			{
				if(R==d_User_TempF_max	&& R_User_Temp_Set_F==d_User_TempF_min)
				{
					R_Temp_metric=C_metric;
					R_User_Temp_Set_C=d_User_TempC_max;
					R_Front_Color=d_Bright_Color;
					R_Back_Color=d_Clean_Color;
					GUI_Write_Bitmap(49,12,CMax_LOGO);
					Pint_Set_Temp(R_User_Temp_Set_C);
				}
				else	if(R==d_User_TempF_min	&& R_User_Temp_Set_F==d_User_TempF_max)
				{
					R_Temp_metric=C_metric;
					R_User_Temp_Set_C=d_User_TempC_min;
					R_Front_Color=d_Bright_Color;
					R_Back_Color=d_Clean_Color;
					GUI_Write_Bitmap(49,12,CMax_LOGO);
					Pint_Set_Temp(R_User_Temp_Set_C);
				}
				else
				{
					R_User_Temp_Set_F=R;
					R_User_Temp_Set_C=(R_User_Temp_Set_F-32)*5/9;
					if(R_User_Temp_Set_C<d_User_TempC_min)
						R_User_Temp_Set_C=d_User_TempC_min;
					else	if(R_User_Temp_Set_C>d_User_TempC_max)
						R_User_Temp_Set_C=d_User_TempC_max;
					Pint_Set_Temp(R_User_Temp_Set_F);
				}
			}
		}
		Res_update();
	}
	if(Touch_events.R_Gesture_mode==Gesture_Left_slip || Touch_events.R_Gesture_mode==Gesture_Right_slip)
	{
		Windows_Switch(Main_interface);
	}
}

//用户瓦数设置界面
static	void	User_Watt_Set_windows(void)
{
	Clear_screen();
	Print_SUB_ADD_screen_low();
	R_Front_Color=d_Bright_Color;
	R_Back_Color=d_Clean_Color;
	if(R_Work_mode==d_Watt_mode)
	{
		GUI_Write_Bitmap(47,12,WattMax_LOGO);
		Pint_Set_Watt(R_User_Watt_Set);
		GUI_Write_Rectangular(14,48,51,66);
		Prain_Watt_Strength();
		Init_TP_Button_Key(User_Press_box1,3);
	}
	else	if(R_Work_mode==d_Voltage_mode)
	{
		GUI_Write_Bitmap(47,12,VattMax_LOGO);
		GUI_Write_block(17,22,19,24);
		Pint_Set_Vout(R_User_Vout_Set);
		Init_TP_Button_Key(User_Press_box1,2);
	}
	else
	{
		Res_Q=0xF000;
		GUI_Write_Line(45,12,46,12);
		GUI_Write_Line(45,15,46,15);
		GUI_Write_Line(44,13,44,14);
		GUI_Write_Line(47,13,47,14);
		if(R_Temp_metric==C_metric)
		{
			GUI_Write_Bitmap(49,12,CMax_LOGO);
			Pint_Set_Temp(R_User_Temp_Set_C);
		}
		else
		{
			GUI_Write_Bitmap(49,12,FMax_LOGO);
			Pint_Set_Temp(R_User_Temp_Set_F);
		}
		GUI_Write_Rectangular(14,33,51,51);
		GUI_Write_Chars(21,48,(uc8*)"TCR",ZT12);
		GUI_Write_Dot(25,78);
		GUI_Write_Bitmap(44,74,Res_LOCK_LOGOL);
		Res_update();
		Prain_Res_LOCK();
		Init_TP_Button_Key(User_Press_box2,4);
	}
}
//
void	User_Data_Set_interface(void)
{
	Key_Light_screen();
	switch((u8)R_Skinning_mode)
	{
		case	Skinning_init:{//初始化
			User_Watt_Set_windows();
			B_Receive_press=1;
			B_Key_release=1;
			R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		};break;
		case	USB_access:{//usb插入
			Windows_Interrupt_Push(Battery_charging_interface);
		};break;
		case	USB_anomaly:{//USB异常
//			Warning_Windows=USB_anomaly_windows;
			Windows_Interrupt_Push(USB_Warning_interface);
		};break;
		default:{
			User_Data_touch();
			if(R_key_anxia==KEY_M)
				Windows_Switch(Main_interface);
			Atomizer_inquiry_GOTO(1);
			Screen_GOTO_charging();
			Batt_error_GOTO();
		}
	}
	R_Skinning_mode=Skinning_mode_null;
}




