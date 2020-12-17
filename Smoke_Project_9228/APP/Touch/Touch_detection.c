#include "stm32f0xx.h"
#include "Stdint_2.h"
#include "TP_I2C.h"
#include "APP_Delay.h"
#include "OLED_driver.h"
#include "Touch_detection.h"
#include "WM_Disp.h"

#define		d_TP_debugging	0		//打开TP调试功能


#define		TP_Range	4		//触摸容错范围
//
Touch_struct	Touch_events;
Touch_coordinate_struct		Touch_value;		//当前的按键坐标值

#define	d_absolute_max	3
u8	R_absolute_max;
u8	Sliding_direction_judgment(s16	Xs,s16	Ys,s16	Xz,s16	Yz,s16 max)
{
	s16	X_distance;
	s16	Y_distance;
	s16	X_absolute;
	s16	Y_absolute;
	X_distance=Xz-Xs;
	Y_distance=Yz-Ys;
	if(X_distance>0)
		X_absolute=X_distance;
	else
		X_absolute=-X_distance;
	if(Y_distance>0)
		Y_absolute=Y_distance;
	else
		Y_absolute=-Y_distance;
	if((Y_distance<-max)&&(Y_absolute*2>=X_absolute*3))
	{
		return	Gesture_Up_slip;
	}
	else if((Y_distance>max)&&(Y_absolute*2>=X_absolute*3))
	{
		return	Gesture_Down_slip;
	}
	else if((X_distance<-max)&&(X_absolute*2>=Y_absolute*3))
	{
		return	Gesture_Left_slip;
	}
	else if((X_distance>max)&&(X_absolute*2>=Y_absolute*3))
	{
		return	Gesture_Right_slip;
	}
	else
	{
		return	Gesture_NOP;
	}
}

u8	Touch_BUFF[4];
u8	Get_Touch_coordinates(void)
{
	static	u8	Tim,state=0;
	u8	Data;
	u8	B;
	u8	a;
	if(state==0)
	{
		if(!IIC_Read_OneByte8(FT_REG_NUM_FINGER,&B))
		{
//			IIC_Read_OneByte8(FT_REG_NUM_FINGER,&B);
			if(B&0x0F)
			{
				IIC_Read_Byte8_N(FT_TP1_REG,Touch_BUFF,4);
				
				if(B_Screen_orientation==d_Vertical_screen)
				{
					a=Touch_BUFF[1];

					Touch_BUFF[1]=Touch_BUFF[3];
					Touch_BUFF[3]=63-a;
				}
				return	1;
			}
		}
		Tim++;
		if(Tim>25)
		{
			Tim=0;
			IIC_Read_OneByte8(ID_G_FT6236ID,&Data);
			if(Data!=0x11)
			{
				state=1;
				I2C_REST_CLR;
			}
		}
	}
	else	if(state==1)
	{
		I2C_REST_SET;
		state=2;
	}
	else
	{
		Tim++;
		if(Tim>15)
		{
			Tim=0;
			state=0;
			TP_Init();
		}
	}
	return	0;
}

#define	d_huadong_Tim		10
#define	d_huadong_sum		2


static  Touch_coordinate_struct   Touch_value1_Start;
static  Touch_coordinate_struct   Touch_value1_End;
static  u8   key_longtime=0;//长按时间累积寄存器
static  u8   F_longkey=0;//长按
static 	u8	 f_onkey=0;

static	u8 	 B_changanjianche=1;
static	u8 	 B_huadongjianche=1;
static	u8 	 B_shanghuadong=0;
static	u8 	 B_xiahuadong=0;
static	u8 	 B_zuohuadong=0;
static	u8 	 B_youhuadong=0;
static	Gesture_enum	Release_event;	//释放后要发的消息

static  Touch_coordinate_struct   Touch_value_Q;
static  u8		key_huadongtime=0;//滑动时间累积寄存器
static	u8		R_huadong_sum;	
static	u8		huadong;

void	Touch_Release_chuli(void)
{
	f_onkey=0;
	F_longkey=0;
	key_longtime=0;
	B_changanjianche=1;
	B_huadongjianche=1;
	B_shanghuadong=0;
	B_xiahuadong=0;
	B_zuohuadong=0;
	B_youhuadong=0;
	R_huadong_sum=0;
	key_huadongtime=40;
	R_absolute_max=d_absolute_max;
	Touch_value.x=-1;
	Touch_value.y=-1;
}
void	huadong_fangxiang_panduan(u8	R)
{
	if(huadong==R)
	{
		key_huadongtime=d_huadong_Tim;
		if(R_huadong_sum<d_huadong_sum)
			R_huadong_sum++;
		Touch_value_Q.x=Touch_value.x;
		Touch_value_Q.y=Touch_value.y;
	}
	else if(huadong)
	{
		B_huadongjianche=0;
		R_huadong_sum=0;
	}
}

void Touch_scan(void)  // uint8
{	
	static	u8	B_Anxia=1;
	if(B_Out_Yes || !R_Bright_screen_Time)
	{
		f_onkey=1;
		B_changanjianche=0;
		B_huadongjianche=0;
		B_Anxia=1;
		Release_event=Gesture_Leave_Screen;
		Touch_events.R_Gesture_mode=Release_event;
		return;
	}
	if(Get_Touch_coordinates())//无按键按下确认，等于0时表示无按键，清释放标识位
	{
		//R_Back_Color=d_Clean_Color;
		//R_Front_Color=d_Bright_Color;
		//GUI_Write_Dot(Touch_BUFF[1],Touch_BUFF[3]);
		B_Anxia=1;
		Touch_value.x=Touch_BUFF[1];
		Touch_value.y=Touch_BUFF[3];
		Touch_events.R_Gesture_mode=Gesture_Stay_Screen;
		if(!f_onkey)
		{
			f_onkey=1;		
			Touch_events.R_Gesture_mode=Gesture_Press;
			Release_event=Gesture_Short_Release;
			Touch_value1_Start.x=Touch_value.x-TP_Range;
			Touch_value1_Start.y=Touch_value.y-TP_Range;
			Touch_value1_End.x=Touch_value.x+TP_Range;
			Touch_value1_End.y=Touch_value.y+TP_Range;
			Touch_value_Q.x=Touch_value.x;
			Touch_value_Q.y=Touch_value.y;
			Touch_events.R_Gesture_coordinate_Start.x=Touch_value.x;
			Touch_events.R_Gesture_coordinate_Start.y=Touch_value.y;
		}
		else
		{
			//按键长按
			if(B_changanjianche)
			{
				if(Touch_value.x>Touch_value1_Start.x && Touch_value.x<Touch_value1_End.x && \
					Touch_value.y>Touch_value1_Start.y && Touch_value.y<Touch_value1_End.y)
				{
					if(!F_longkey)
					{
						if(++key_longtime>=30)
						{
							B_huadongjianche=0;	//关闭滑动检测
							F_longkey=1;
							//长按按键处理程序
							Touch_value1_Start.x-=6;
							Touch_value1_Start.y-=6;
							Touch_value1_End.x+=6;
							Touch_value1_End.y+=6;
							Touch_events.R_Gesture_mode=Gesture_Long_Press;
							Release_event=Gesture_Long_Release;
						}
					}
					else
					{
						Touch_events.R_Gesture_mode=Gesture_Hold_down;
					}
				}
				else
				{
					B_changanjianche=0;
					Release_event=Gesture_Release;
				}
			}
			if(B_huadongjianche)
			{
				huadong=Sliding_direction_judgment(Touch_value_Q.x,Touch_value_Q.y,Touch_value.x,Touch_value.y,R_absolute_max);
				if(B_shanghuadong)
				{
					huadong_fangxiang_panduan(Gesture_Up_slip);
				}
				else if(B_xiahuadong)
				{
					huadong_fangxiang_panduan(Gesture_Down_slip);
				}
				else if(B_zuohuadong)
				{
					huadong_fangxiang_panduan(Gesture_Left_slip);
				}
				else if(B_youhuadong)
				{
					huadong_fangxiang_panduan(Gesture_Right_slip);
				}
				else
				{
					if(huadong==Gesture_Up_slip)
						B_shanghuadong=1;
					else if(huadong==Gesture_Down_slip)
						B_xiahuadong=1;
					else if(huadong==Gesture_Left_slip)
						B_zuohuadong=1;
					else if(huadong==Gesture_Right_slip)
						B_youhuadong=1;
					if(huadong)
					{
						R_absolute_max=2;
						R_huadong_sum++;
						key_huadongtime=d_huadong_Tim;
						Touch_value_Q.x=Touch_value.x;
						Touch_value_Q.y=Touch_value.y;
					}
				}
				if(key_huadongtime)
				{
					key_huadongtime--;
				}
				else
				{
					B_huadongjianche=0;
					B_shanghuadong=0;
					B_xiahuadong=0;
					B_zuohuadong=0;
					B_youhuadong=0;
				}
			}
		}
	}
	else
	{
		Touch_events.R_Gesture_mode=Release_event;
		if(B_Anxia==1)
		{
			B_Anxia=0;
			if(B_huadongjianche)
			{
				if(R_huadong_sum>=d_huadong_sum)
				{
					Touch_events.R_Gesture_coordinate_End.x=Touch_value.x;
					Touch_events.R_Gesture_coordinate_End.y=Touch_value.y;
					if(B_shanghuadong)
					{
						Touch_events.R_Gesture_mode=Gesture_Up_slip;
					}
					else if(B_xiahuadong)
					{
						Touch_events.R_Gesture_mode=Gesture_Down_slip;
					}
					else if(B_zuohuadong)
					{
						Touch_events.R_Gesture_mode=Gesture_Left_slip;
					}
					else if(B_youhuadong)
					{
						Touch_events.R_Gesture_mode=Gesture_Right_slip;
					}
				}
			}
			Touch_Release_chuli();
		}
		Release_event=Gesture_Leave_Screen;
	}
}




///////////////////////////////////////////////////////

//键值
u8	R_Button_anxia;
u8	R_Button_Open;
u8	R_Button_anxiaOpen;	//短按松开
u8	R_Button_anzhuOpen;	//长按松开
u8	R_Button_keep;
u8	R_Button_anzhu;
u8	R_Button_shanghua;
u8	R_Button_xiahua;
u8	R_Button_zuohua;
u8	R_Button_youhua;
u8	R_Button_3C;
//
u8	B_Button_EN=0;			//按键扫描使能
u8	B_Receive_press=1;	//等待按下标志
u8 	Button_Hda=0;
u8 	Button_data=0;
u8	value=0xff;
uc8	(*Button_BUFF)[4];
u8	Button_SUM;

void	Get_TP_Button_Key(void)
{
	u8	i;
	static	u8	R;
	static	u8	B_anzhu;
	
	if(B_Button_EN)
	{
		R_Button_anxia=0xff;
		R_Button_Open=0xff;
		R_Button_anxiaOpen=0xff;
		R_Button_anzhuOpen=0xff;
		R_Button_keep=0xff;
		R_Button_anzhu=0xff;
		R_Button_shanghua=0xff;
		R_Button_xiahua=0xff;
		R_Button_zuohua=0xff;
		R_Button_youhua=0xff;
		R_Button_3C=0xff;
		if(B_Receive_press==1)
		{
			if(Touch_events.R_Gesture_mode==Gesture_Press)
			{
				for(i=0;i<Button_SUM;i++)
				{
					if(Touch_value.x>=Button_BUFF[i][0] && Touch_value.y>=Button_BUFF[i][1] &&\
					Touch_value.x<=Button_BUFF[i][2] && Touch_value.y<=Button_BUFF[i][3])
					{
						B_Receive_press=0;
						R=i;
						R_Button_anxia=R;
						Button_Hda=15;
						B_anzhu=1;
						break;
					}
				}
			}
			else  if(Touch_events.R_Gesture_mode==Gesture_Leave_Screen)
			{
				if(Button_Hda)
					Button_Hda--;
				else
				{
					if(Button_data==3)
						R_Button_3C=value;
					Button_data=0;
				}
			}
		}
		else
		{
			if(Button_Hda)
				Button_Hda--;
			else
				Button_data=0;
			if(B_anzhu==1)
			{
				if(Touch_events.R_Gesture_mode==Gesture_Hold_down)
				{
					B_anzhu=2;
					R_Button_keep=R;
					Button_data=0;	
				}
			}
			else	if(B_anzhu==2)
			{
				if(Touch_value.x>=Button_BUFF[R][0]&&Touch_value.y>=Button_BUFF[R][1] &&\
					Touch_value.x<=Button_BUFF[R][2] && Touch_value.y<=Button_BUFF[R][3])
				{
					R_Button_anzhu=R;
				}
				else
				{
					B_anzhu=0;
					if(Touch_value.x==-1)
						R_Button_anzhuOpen=R;
				}
			}
			if(Touch_events.R_Gesture_mode==Gesture_Short_Release)
			{
				R_Button_anxiaOpen=R;
				if(value!=R)
				{
					value=R;
					Button_data=1;
				}
				else if(Button_data<5)
				{
					Button_data++;
				}
				Button_Hda=15;
			}
			else if(Touch_events.R_Gesture_mode==Gesture_Leave_Screen)
			{
				R_Button_Open=R;
				B_Receive_press=1;
			}
			else	if(Touch_events.R_Gesture_mode==Gesture_Up_slip)
			{
				R_Button_shanghua=R;
				Button_data=0;	
			}
			else	if(Touch_events.R_Gesture_mode==Gesture_Down_slip)
			{
				R_Button_xiahua=R;
				Button_data=0;	
			}
			else	if(Touch_events.R_Gesture_mode==Gesture_Left_slip)
			{
				R_Button_zuohua=R;
				Button_data=0;	
			}
			else	if(Touch_events.R_Gesture_mode==Gesture_Right_slip)
			{
				R_Button_youhua=R;
				Button_data=0;	
			}
		}
	}
}

void	Init_TP_Button_Key(uc8	Button[][4],u8	sum)
{
	B_Button_EN=1;
	B_Receive_press=1;
	Button_Hda=0;
	Button_data=0;
	value=0xff;
	Button_BUFF=Button;
	Button_SUM=sum;
}
void	TP_Button_Key_OFF(void)
{
	B_Button_EN=0;
}

//TP调试功能
#if	d_TP_debugging
u8	R_TP_debug_X;
u8	R_TP_debug_Y;


#endif

//加减操作  //xh=0:加减不做循环  xh=1:加减到最大再次按下循环 xh=2：循环
u16	TP_R_ADD_SUB(u8 *KEY,s16	R,u8 KADD,u8 KSUB,s16 max,s16 min,s8 bu,u8 xh,u8 tim)
{
	static	u8	B;
	if((R==max || R==min)&&xh==1)
	{
		if(R_Button_anxia==KADD || R_Button_anxia==KSUB)
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
		
	if(R_Button_anzhu==KADD)
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
	else	if(R_Button_anzhu==KSUB)
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
	else if(R_Button_anzhu==0xff)
	{
		R_KEY_timMax=150;
	}
	if(R>max)
		R=max;
	else if(R<min)
		R=min;
	return R;
}

























