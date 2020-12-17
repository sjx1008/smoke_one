#include	"main.h"

u8	B_Display_Detect=0;					///定时刷新屏幕标志
u8	B_Smoking_mark=0;						///吸烟标志
u8	B_Smoking_mark_Q=1;						///吸烟标志
u8	B_Power_down=0;							///降功率
u8	B_BAT_Twinkle=0;						///电池符闪烁
u8	B_BAT_Charge=0;							///充电标志
u8	B_BAT_Congman=0;						///充电充满标志
u8	B_BAT_Congman_Q=0;					///充电充满标志
u8	B_BAT_Paoma;								///充电跑马标志
u8	B_Shuoji;										///锁机标志
//u8	B_Shuoji_Q;									///锁机标志
u8	B_PowerOFF;	
u8	B_Key_Shuo;	//按键锁
u8	B_Key_Shuo_Q;

Language	R_Language;									///语言选择

//u8	R_yaoshi_i;									///锁机小图标内的数字
//u8	R_yaoshi_i_Q;								///锁机小图标内的数字
u8	R_Window_keep_TimS;					///窗口维持秒数
u8	R_Window_Tim_MAX;						///窗口维持秒数
u8	*R_ii;
uc8 *R_i2;

u16	R_Win_tim;
///////充电界面参数
//u8	B_Charging_1;

Displays		R_DisStatus,R_DisStatus_Q,R_DisStatus_S;
Atomizer		R_Atomizer,R_Atomizer_Q,R_Atomizer_Set;
Work_mode		R_Work_mode,R_Work_mode_Q,R_Work_mode_Set;
DATA_Atomizer		R_DISP_DATA,R_DISP_DATA_Q;
Temp_metric		R_Temp_metric,R_Temp_metric_Q,R_Temp_metric_Set;
TCR_term		R_TCR_term,R_TCR_term_Q,R_TCR_term_Set;

//u8	R_Operation_mode=0;

/*************童锁密码*******************/
u8	R_now_password[3]={'0','0','0'};		//当前密码
u8	R_input_password[3];								//输入密码
u8	R_input_password_x;									//当前输入密码的个数
u8	R_input_password_x_Q;								//上一次输入密码的个数
u8	B_Password_error;									 	//密码输入错误标志
/*************更改LOGO*******************/
u8	R_input_LOGO[12];							//输入LOGO
u8	R_input_LOGO_x=6;								//当前输入LOGO的个数
u8	R_input_LOGO_x_Q;							//上一次输入LOGO的个数
u8	B_Big_small;									//上一次输入LOGO的个数
/*************TCR调节*******************/
u8	R_TCR_Selected;								//选中的调节项
/**************电压模式下允许的最大输出电压*********************/
u16	R_VoltageMAX;


/////界面切换的起始操作
u8	B_ON_DISP_BL;
void	Dis_Start_operation(void)
{
	New_DisStatus_S();
	R_DisStatus_Q=R_DisStatus;
	R_Window_keep_TimS=R_Window_Tim_MAX;
	//R_DISP_DATA_Q_DeInit();
	Clear_screen();
	if(!B_OLED_BL)
	{
		Disp_ON();
	}
}
/********************************************************************************/
/////开路界面///////////
void	Open_Interface(void)
{
	if(R_Language==English)
	{
		////GUI_Write_Chars(11,22,"No Atomizer",ZT14,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Bitmap(15,10,NoAtomizer_LOGO,d_Clean_Color,d_Bright_Color);

	}
	else
	{
		//请接入雾化器
		////GUI_Write_Zhongwen(0,23,Please_access_Atomizer_C,d_Clean_Color,d_Bright_Color);
	}
}
void	Display_Open_Circuit(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		Open_Interface();
		R_Win_tim=300;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
}
/********************************************************************************/
/////短路界面///////////
void	Short_Interface(void)
{
	if(R_Language==English)
	{
		////GUI_Write_Chars(24,22,"Low Res",ZT14,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//低阻值保护
		////GUI_Write_Zhongwen(9,23,Low_resistance_C,d_Clean_Color,d_Bright_Color);
	}
}
void	Display_Short_Circuit(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		Short_Interface();
		R_Win_tim=300;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
}
/********************************************************************************/
/////吸烟超时界面///////////
void	Timeout_Interface(void)
{
//	////GUI_Write_Round(13,15,12,d_Bright_Color);
//	////GUI_Write_block(12,7,13,17,d_Bright_Color);
//	////GUI_Write_block(11,15,18,16,d_Bright_Color);
	if(R_Language==English)
	{
		////GUI_Write_Bitmap(22,9,Over_LOGO,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Chars(20,22,"Over   s",ZT14,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//吸烟超时
		////GUI_Write_Zhongwen(2,23,Smoking_timeout_C,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Chars(87,23,"s",ZT14,d_Clean_Color,d_Bright_Color);
	}
	R_DISP_DATA_Q.Smoke_Tim_max=0x70;
}
void	Display_Timeout_Circuit(void)
{
	static	u8	C;
	Color_TypeDef R_Color;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		Timeout_Interface();
		R_Win_tim=500;
	}
	
	if(R_DISP_DATA_Q.Smoke_Tim_max!=R_DISP_DATA.Smoke_Tim_max)
	{
		R_DISP_DATA_Q.Smoke_Tim_max=R_DISP_DATA.Smoke_Tim_max;
		B_BAT_Twinkle=1;
		C=0;
	}
	if(B_BAT_Twinkle)
	{
		B_BAT_Twinkle=0;
		C=!C;
		if(C)
		{
			R_Color=d_Bright_Color;
		}
		else
		{
			R_Color=d_Clean_Color;
		}
		if(R_Language==English)
		{
			if(R_DISP_DATA.Smoke_Tim_max<10)
			{
				////GUI_Write_block(53,10,59,22,d_Clean_Color);
				////GUI_Write_data(60,22,1,R_DISP_DATA.Smoke_Tim_max,ZT14,d_Clean_Color,R_Color);
			}
			else
			{
				////GUI_Write_data(54,22,2,R_DISP_DATA.Smoke_Tim_max,ZT14,d_Clean_Color,R_Color);
			}
		}
		else
		{
			if(R_DISP_DATA.Smoke_Tim_max<10)
			{
				////GUI_Write_block(71,10,77,23,d_Clean_Color);
				////GUI_Write_data(78,23,1,R_DISP_DATA.Smoke_Tim_max,ZT14,d_Clean_Color,R_Color);
			}
			else
			{
				////GUI_Write_data(72,23,2,R_DISP_DATA.Smoke_Tim_max,ZT14,d_Clean_Color,R_Color);
			}
		}
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
}
/********************************************************************************/

////////////////PCB高温保护界面////////////////////
void	Temperature_protection_interface(void)
{
	if(R_Language==English)
	{
		//////GUI_Write_Chars(23,23,"Too Hot",ZT14,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Bitmap(22,10,TooHot_LOGO,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//过热保护
		////GUI_Write_Zhongwen(15,23,High_temp_C,d_Clean_Color,d_Bright_Color);
	}
}
void	Display_High_Temperature(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		Temperature_protection_interface();
		R_Win_tim=500;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
}
/********************************************************************************/
////////////////低电量界面////////////////////
void	Low_battery_interface(void)
{
	if(R_Language==English)
	{
		//////GUI_Write_Chars(10,23,"Low Battery",ZT14,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Bitmap(13,9,LowBatter_LOGO,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//电池电量低
		////GUI_Write_Zhongwen(9,23,Low_BAT_C,d_Clean_Color,d_Bright_Color);
	}
}
void	Display_Low_battery(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		Low_battery_interface();
		R_Win_tim=300;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
}
/********************************************************************************/
////////////////空电量界面////////////////////
void	Empty_battery_interface(void)
{
	Charging_BAT_windows();
	////GUI_Write_Bitmap(22,12,Empty_battery_LOGO,d_Clean_Color,d_Bright_Color);
}
void	Display_Empty_battery(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		if(USB_T_RinBit)
		{
			R_Window_Tim_MAX=10;
			Dis_Start_operation();
			
			//Empty_battery_interface();
		}
	}
	if(!USB_T_RinBit)
	{
		if(B_OLED_BL)
		{
			Disp_OFF();
		}
	}
	else
	{
		if(!B_OLED_BL)
		{
			Disp_ON();
			//Empty_battery_interface();
		}
	}
}
/********************************************************************************/
////////////////////更换雾化器设置询问
void	Atomizer_replace_interface(void)
{
	if(R_Language==English)
	{
		////GUI_Write_Chars(2,13,"New Atomizer?",ZT14,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Chars(10,31,"YES+ / NO-",ZT14,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//新雾化器？
		//是+/否-
		////GUI_Write_Zhongwen(13,15,New_atomizer_C,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Zhongwen(16,31,YESorNO_C,d_Clean_Color,d_Bright_Color);
	}
	
}
void	Display_Atomizer_replace(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		Atomizer_replace_interface();
	}
}
/********************************************************************************/
/////////////////////锁机界面//////////////////////////////////
///////////////////////////////////////////////////////////////////
				////锁机窗口
void	Shuoji_windows(void)
{
	////GUI_Write_block(23,13,70,30,d_Bright_Color);
	////GUI_Write_block(28,2,30,12,d_Bright_Color);
	////GUI_Write_block(63,2,65,12,d_Bright_Color);
	////GUI_Write_block(29,1,64,3,d_Bright_Color);
	
	////GUI_Write_block(45,18,48,20,d_Clean_Color);
	////GUI_Write_block(46,21,47,27,d_Clean_Color);
}
void	Display_Shuoji(void)
{	
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=5;
		Dis_Start_operation();
		Shuoji_windows();
	}
}
/********************************************************************************/
//////////////关机/////////
void	Power_OFF_windows(void)
{
	if(R_Language==English)
	{
		//////GUI_Write_Chars(23,14,"Locked",ZT14,d_Clean_Color,d_Bright_Color);
		//////GUI_Write_Chars(20,29,"Click 5X",ZT14,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Bitmap(27,3,Locked_LOGO,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//关机
		////GUI_Write_Zhongwen(11,15,Shuoding_C,d_Clean_Color,d_Bright_Color);
		////GUI_Write_Zhongwen(11,31,Shutdown_C,d_Clean_Color,d_Bright_Color);
	}
}

u8	B_Display_Power_OFF;
u8	B_Display_Power_OFF_Q;
void	Display_Power_OFF(void)
{	
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=3;
		if(B_Display_Power_OFF)
		{
			New_DisStatus_S();
			R_DisStatus_Q=R_DisStatus;
			R_Window_keep_TimS=R_Window_Tim_MAX;
			if(B_Display_Power_OFF_Q==B_Display_Power_OFF)
			{
				if(B_OLED_BL)
				{
					Disp_OFF();
				}
			}
		}
		else
		{			
			Dis_Start_operation();
			Power_OFF_windows();
		}
	}
	if(B_Display_Power_OFF_Q!=B_Display_Power_OFF)
	{
		Clear_screen();
		if(R_Language==English)
		{
			//GUI_Write_Chars(8,22,"System off",ZT14,d_Clean_Color,d_Bright_Color);
		}
		else
		{
			//GUI_Write_Zhongwen(16,23,System_off_C,d_Clean_Color,d_Bright_Color);
		}
		B_Display_Power_OFF_Q=B_Display_Power_OFF;
	}
}
/********************************************************************************/
///////////////语言选择
void	Software_version(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		//GUI_Write_Chars(15,23,d_Firmware_version,ZT14,d_Clean_Color,d_Bright_Color);
		R_Win_tim=150;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_Language;
	}
}

void	Language_windows(void)
{
	//GUI_Write_Bitmap(19,9,EN_LOGO,d_Clean_Color,d_Bright_Color);
	//GUI_Write_Bitmap(57,9,CH_LOGO,d_Clean_Color,d_Bright_Color);
}

void	Display_Language_asked(void)
{
	static	u8 Language_i_Q;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		Language_windows();
		Language_i_Q=0x70;
		R_ii = (u8*)&R_Language;
	}
	
	if(R_Language!=Language_i_Q)
	{
		if(Language_i_Q<2)
			//GUI_Write_block(Language_block[Language_i_Q][0],7,Language_block[Language_i_Q][1],24,d_Transparent_Color);
		//GUI_Write_block(Language_block[R_Language][0],7,Language_block[R_Language][1],24,d_Transparent_Color);
		Language_i_Q=R_Language;
	}
}
/********************************************************************************/
/////////////////////充电跑马//////////////////////////////////
///////////////////////////////////////////////////////////////////

				////电池窗口
void	Charging_BAT_windows(void)
{
	//GUI_Write_Rectangular(12,5,81,27,d_Bright_Color);
	//GUI_Write_Rectangular(13,6,80,26,d_Bright_Color);
	//GUI_Write_block(82,9,84,23,d_Bright_Color);
	R_DISP_DATA_Q.BAT_vip=0x70;
	R_DISP_DATA_Q.BAT_data=0x7000;
	B_BAT_Congman_Q=0;
}
	////充电界面跑马
void	DISP_BAT_paoma(u8	dat_vip)
{
	u8	i;
	Color_TypeDef		C;
	for(i=1;i<=5;i++)
	{
		if(i<=dat_vip)
			C=d_Bright_Color;
		else
			C=d_Clean_Color;
		//GUI_Write_block(2+i*13,8,13+i*13,24,C);
	}
}
uc16	R_BAT_VIP[]={285,350,370,385,400,0x0fff};
void	Display_BAT_Charging(void)
{	
	u8	i;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		Charging_BAT_windows();
	}
	if(R_DISP_DATA_Q.BAT_data != R_DISP_DATA.BAT_data)
	{
		for(i=0;i<6;i++)
		{
			if(R_DISP_DATA.BAT_data<R_BAT_VIP[i])
			{
				R_DISP_DATA.BAT_vip=i;
				break;
			}
		}
		R_DISP_DATA_Q.BAT_data = R_DISP_DATA.BAT_data;
	}
	if(B_BAT_Paoma)
	{
		B_BAT_Paoma=0;
		if(B_BAT_Congman)
		{
			if(!B_BAT_Congman_Q)
			{
				B_BAT_Congman_Q=1;
				DISP_BAT_paoma(5);
			}
		}
		else
		{
			B_BAT_Congman_Q=0;
			if(R_DISP_DATA_Q.BAT_vip>5)
			{
				R_DISP_DATA_Q.BAT_vip=R_DISP_DATA.BAT_vip;
				if(R_DISP_DATA.BAT_vip>=5)
				{
					R_DISP_DATA_Q.BAT_vip=4;
				}
			}
			DISP_BAT_paoma(R_DISP_DATA_Q.BAT_vip);
			R_DISP_DATA_Q.BAT_vip++;
		}
	}
}
/********************************************************************************/
/////////////////////主界面//////////////////////////////////
///////////////////////////////////////////////////////////////////
				////电池窗口
void	BAT_windows(void)
{
	//GUI_Write_Rectangular(71,24,94,31,d_Bright_Color);
	//GUI_Write_block(95,26,95,29,d_Bright_Color);
	R_DISP_DATA_Q.BAT_vip=0x70;
	R_DISP_DATA_Q.BAT_data=0x7000;
	B_BAT_Congman_Q=0;
}
			////电阻窗口
void	Resistance_windows(void)
{
	//GUI_Write_Bitmap(91,11,Omuunit_LOGO,d_Clean_Color,d_Bright_Color);
	//GUI_Write_Dot(77,21,d_Bright_Color);
	R_DISP_DATA_Q.Res_data=0x7000;
}
			////电压窗口
void	Volt_vout_windows(void)
{
	//GUI_Write_block(37,28,39,30,d_Bright_Color);
	R_DISP_DATA_Q.Vout_Set=0x7000;
	R_DISP_DATA_Q.Vout_Out=0x7000;
}
			////设定温度窗口 (C)
void	Temp_windows(void)
{
	if(R_Temp_metric==C_metric)
	{
		//GUI_Write_Bitmap(57,11,Cunit_LOGO,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//GUI_Write_Bitmap(57,11,Funit_LOGO,d_Clean_Color,d_Bright_Color);
	}
	R_DISP_DATA_Q.Temp_Set_C=0x7000;
	R_DISP_DATA_Q.Temp_Out_C=0x7000;
	R_DISP_DATA_Q.Temp_Set_F=0x7000;
	R_DISP_DATA_Q.Temp_Out_F=0x7000;
}
			////设定瓦数
void	Watt_windows(void)
{
	//GUI_Write_block(49,28,51,30,d_Bright_Color);
	R_DISP_DATA_Q.Watt_Set=0x7000;
	R_DISP_DATA_Q.Watt_Out=0x7000;
}
		////工作模式窗口
void	Work_mode_windows(void)
{
	//GUI_Write_Rectangular(0,11,18,31,d_Bright_Color);
	R_Work_mode_Q=d_NOP_mode;
	R_Atomizer_Q=Atomizer_NC;
	R_TCR_term_Q=TCR_NC;
}
		////LOGO窗口
void	Work_logo_windows(void)
{
	u8	i,L;
	L=0;
	//GUI_Write_block(1,0,79,8,d_Clean_Color);
	for(i=0;i<11;i++)
	{
		if(BOOT_logo[i]=='\0')
			break;
		L+=*ASCII9[BOOT_logo[i]-32];
		//*(*(A+(BOOT_logo[i]-32)));
	}
	//GUI_Write_Chars((83-L)/2,8,BOOT_logo,ZT9,d_Clean_Color,d_Bright_Color);
}
		////按键锁窗口
void	lock_windows(void)
{
	//GUI_Write_Rectangular(85,3,91,6,d_Bright_Color);
	B_Key_Shuo_Q=0x70;
}

//------------------------------------------------------------
		///////显示电池电量
void	BAT_Vip_disp(u8	vip)
{
	u8	i;
	i=72+vip*4;
	//GUI_Write_block(93,26,i+1,29,d_Clean_Color);
	if(vip)
	{
		//GUI_Write_block(73,26,i,29,d_Bright_Color);
	}
}
		///////显示电阻
void	Resistance_data_disp(u16	data)
{
	//GUI_Write_data(71,22,1,data/100,ZT14,d_Clean_Color,d_Bright_Color);
	//GUI_Write_data(79,22,2,data%100,ZT14,d_Clean_Color,d_Bright_Color);
}
		///////显示输出电压
void	Vout_Volt_disp(u16	data)
{
	//GUI_Write_data(24,31,1,data/100,ZT21,d_Clean_Color,d_Bright_Color);
	//GUI_Write_data(41,31,2,data%100,ZT21,d_Clean_Color,d_Bright_Color);
}
		///////显示设置温度
void	Temp_data_disp(u16	data)
{
	//GUI_Write_data(20,31,3,data,ZT21,d_Clean_Color,d_Bright_Color);
}
		///////显示设置瓦数
void	Watt_data_disp(u16	data)
{
	if(data<100)
	{
		//GUI_Write_block(25,11,34,31,d_Clean_Color);
		//GUI_Write_data(36,31,1,data/10,ZT21,d_Clean_Color,d_Bright_Color);
		//GUI_Write_data(53,31,1,data%10,ZT21,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//GUI_Write_data(24,31,2,data/10,ZT21,d_Clean_Color,d_Bright_Color);
		//GUI_Write_data(53,31,1,data%10,ZT21,d_Clean_Color,d_Bright_Color);
	}
}
		///////显示工作模式
void	Work_mode_disp(void)
{
	switch(R_Work_mode)
	{
		case	d_Watt_mode:		//GUI_Write_Bitmap(2,14,W_LOGO,d_Clean_Color,d_Bright_Color);break;
		case	d_Bypass_mode:	//GUI_Write_Bitmap(2,14,B_LOGO,d_Clean_Color,d_Bright_Color);break;
		case	d_Voltage_mode:	//GUI_Write_Bitmap(2,14,V_LOGO,d_Clean_Color,d_Bright_Color);break;
		case	d_Custom_mode:	{
			R_Dis_Custom_X_Q=0xee;
					switch(R_Custom_I)
					{
						case	0:	//GUI_Write_Bitmap(2,14,C1_LOGO,d_Clean_Color,d_Bright_Color);break;
						case	1:	//GUI_Write_Bitmap(2,14,C2_LOGO,d_Clean_Color,d_Bright_Color);break;
						case	2:	//GUI_Write_Bitmap(2,14,C3_LOGO,d_Clean_Color,d_Bright_Color);break;
					}
		}break;
		case	d_Temp_mode:		{
					switch(R_Atomizer)
					{
						case	Atomizer_0:	//GUI_Write_Bitmap(2,14,Ss_LOGO,d_Clean_Color,d_Bright_Color);break;
						case	Atomizer_1:	//GUI_Write_Bitmap(2,14,Ni_LOGO,d_Clean_Color,d_Bright_Color);break;
						case	Atomizer_2:	//GUI_Write_Bitmap(2,14,Ti_LOGO,d_Clean_Color,d_Bright_Color);break;
					}
		}break;
		case	d_TCR_mode:	{
					switch(R_TCR_term)
					{
						case	TCR_0:	//GUI_Write_Bitmap(2,14,M1_LOGO,d_Clean_Color,d_Bright_Color);break;
						case	TCR_1:	//GUI_Write_Bitmap(2,14,M2_LOGO,d_Clean_Color,d_Bright_Color);break;
						case	TCR_2:	//GUI_Write_Bitmap(2,14,M3_LOGO,d_Clean_Color,d_Bright_Color);break;
					}
		}break;	
	}
}
		///////显示按键锁状态
void	lock_disp(void)
{
	//GUI_Write_block(86,0,94,2,d_Clean_Color);
	if(B_Key_Shuo)
	{
		//GUI_Write_Bitmap(86,0,ShuoU_LOGO,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//GUI_Write_Bitmap(90,0,ShuoU_LOGO,d_Clean_Color,d_Bright_Color);
	}
}

//////////工作界面窗口更新
void	The_Work_interface(void)
{
	BAT_windows();
	Resistance_windows();
	Work_mode_windows();
	//Work_logo_windows();
	lock_windows();
	switch(R_Work_mode)
	{
		case	d_Watt_mode:			Watt_windows();break;
		case	d_Voltage_mode:
		case	d_Bypass_mode:		Volt_vout_windows();break;
		case	d_Temp_mode:
		case	d_TCR_mode:				Temp_windows();break;
	}
}

/////主界面电池更新
void	Display_BAT(void)
{
	u8	i;
	if(R_DISP_DATA_Q.BAT_data != R_DISP_DATA.BAT_data)
	{
		for(i=0;i<6;i++)
		{
			if(R_DISP_DATA.BAT_data<R_BAT_VIP[i])
			{
				R_DISP_DATA.BAT_vip=i;
				break;
			}
		}
		R_DISP_DATA_Q.BAT_data = R_DISP_DATA.BAT_data;
	}
	
	if(B_Out_Yes)
	{
		B_BAT_Congman_Q=0;
		if(R_DISP_DATA.BAT_vip!=R_DISP_DATA_Q.BAT_vip)
		{
			R_DISP_DATA_Q.BAT_vip=R_DISP_DATA.BAT_vip;
				BAT_Vip_disp(R_DISP_DATA.BAT_vip);
		}
	}
	else
	{
		if(B_BAT_Charge)
		{
			if(B_BAT_Paoma)
			{
				B_BAT_Paoma=0;
				if(B_BAT_Congman)
				{
					if(!B_BAT_Congman_Q)
					{
						B_BAT_Congman_Q=1;
						BAT_Vip_disp(5);
					}
				}
				else
				{
					B_BAT_Congman_Q=0;
					if(R_DISP_DATA_Q.BAT_vip>5)
					{
						R_DISP_DATA_Q.BAT_vip=R_DISP_DATA.BAT_vip;
						if(R_DISP_DATA.BAT_vip>=5)
						{
							R_DISP_DATA_Q.BAT_vip=4;
						}
					}
					BAT_Vip_disp(R_DISP_DATA_Q.BAT_vip);
					R_DISP_DATA_Q.BAT_vip++;
				}
			}
		}
		else
		{
			B_BAT_Congman_Q=0;
			if(R_DISP_DATA.BAT_vip!=R_DISP_DATA_Q.BAT_vip)
			{
				R_DISP_DATA_Q.BAT_vip=R_DISP_DATA.BAT_vip;
				BAT_Vip_disp(R_DISP_DATA.BAT_vip);
			}
		}
	}
}
//////主界面电阻值更新
void	Display_Resistance(void)
{
	u32	A,B;
	R_DISP_DATA.Res_data=R_Res_Initial/10;
	if(R_DISP_DATA_Q.Res_data!=R_DISP_DATA.Res_data)
	{
		R_DISP_DATA_Q.Res_data=R_DISP_DATA.Res_data;
		Resistance_data_disp(R_DISP_DATA.Res_data);
		
		/////////计算电压模式下允许的最大输出电压///////////
		A=R_DISP_DATA.Res_data*22;
		B=sqrt_16(d_DIS_Watt_max*R_DISP_DATA.Res_data*10);
		if(A>B)
		{
			A=B;
		}
		if(A>d_DIS_Vout_max)
			A=d_DIS_Vout_max;
		R_VoltageMAX=A;		
	}
}
/////主界面输出电压更新
void	Display_VOut(void)
{
	if(B_Out_Yes)
	{
		R_DISP_DATA_Q.Vout_Set=0x7fff;
		if(R_DISP_DATA_Q.Vout_Out!=R_DISP_DATA.Vout_Out)
		{
			R_DISP_DATA_Q.Vout_Out=R_DISP_DATA.Vout_Out;
			Vout_Volt_disp(R_DISP_DATA.Vout_Out);
		}
	}
	else
	{
		R_DISP_DATA_Q.Vout_Out=0x7fff;
		if(R_Work_mode==d_Voltage_mode)
		{
			if(R_DISP_DATA.Vout_Set>R_VoltageMAX)
				R_DISP_DATA.Vout_Set=R_VoltageMAX;
			if(R_DISP_DATA_Q.Vout_Set!=R_DISP_DATA.Vout_Set)
			{
				R_DISP_DATA_Q.Vout_Set=R_DISP_DATA.Vout_Set;
				Vout_Volt_disp(R_DISP_DATA.Vout_Set);
			}
		}
		else
		{
			if(R_DISP_DATA_Q.Vout_Set!=R_DISP_DATA.Vout_Out)
			{
				R_DISP_DATA_Q.Vout_Set=R_DISP_DATA.Vout_Out;
				Vout_Volt_disp(R_DISP_DATA.Vout_Out);
			}
		}
	}
}
/////主界面温度显示
void	Display_Temp(void)
{
	if(R_Temp_metric_Q!=R_Temp_metric)
	{
		R_Temp_metric_Q=R_Temp_metric;
		Temp_windows();
	}
	if(B_Out_Yes)
	{
		R_DISP_DATA_Q.Temp_Set_F=0x7fff;
		R_DISP_DATA_Q.Temp_Set_C=0x7fff;
		if(R_Temp_metric==C_metric)
		{
			if(R_DISP_DATA_Q.Temp_Out_C!=R_DISP_DATA.Temp_Out_C)
			{
				R_DISP_DATA_Q.Temp_Out_C=R_DISP_DATA.Temp_Out_C;
				Temp_data_disp(R_DISP_DATA.Temp_Out_C);
			}
			R_DISP_DATA_Q.Temp_Out_F=0x7fff;
		}
		else
		{
			if(R_DISP_DATA_Q.Temp_Out_F!=R_DISP_DATA.Temp_Out_F)
			{
				R_DISP_DATA_Q.Temp_Out_F=R_DISP_DATA.Temp_Out_F;
				Temp_data_disp(R_DISP_DATA.Temp_Out_F);
			}
			R_DISP_DATA_Q.Temp_Out_C=0x7fff;
		}
	}
	else
	{
		R_DISP_DATA_Q.Temp_Out_F=0x7fff;
		R_DISP_DATA_Q.Temp_Out_C=0x7fff;
		if(R_Temp_metric==C_metric)
		{
			if(R_DISP_DATA_Q.Temp_Set_C!=R_DISP_DATA.Temp_Set_C)
			{
				R_DISP_DATA_Q.Temp_Set_C=R_DISP_DATA.Temp_Set_C;
				R_DISP_DATA.Temp_Set_F=R_DISP_DATA.Temp_Set_C*9/5+32;
				if(R_DISP_DATA.Temp_Set_F<200)
				{
					R_DISP_DATA.Temp_Set_F=200;
				}
				else if(R_DISP_DATA.Temp_Set_F>600)
				{
					R_DISP_DATA.Temp_Set_F=600;
				}
				Temp_data_disp(R_DISP_DATA.Temp_Set_C);
			}
			R_DISP_DATA_Q.Temp_Set_F=0x7fff;
		}
		else
		{
			if(R_DISP_DATA_Q.Temp_Set_F!=R_DISP_DATA.Temp_Set_F)
			{
				R_DISP_DATA_Q.Temp_Set_F=R_DISP_DATA.Temp_Set_F;
				R_DISP_DATA.Temp_Set_C=(R_DISP_DATA.Temp_Set_F-32)*5/9;
				if(R_DISP_DATA.Temp_Set_C<100)
				{
					R_DISP_DATA.Temp_Set_C=100;
				}
				else if(R_DISP_DATA.Temp_Set_C>315)
				{
					R_DISP_DATA.Temp_Set_C=315;
				}
				Temp_data_disp(R_DISP_DATA.Temp_Set_F);
			}
			R_DISP_DATA_Q.Temp_Set_C=0x7fff;
		}
	}
}

/////主界面设定W更新
void	Display_Watt(void)
{
	if(B_Out_Yes)
	{
		R_DISP_DATA_Q.Watt_Set=0x7fff;
		if(R_DISP_DATA_Q.Watt_Out!=R_DISP_DATA.Watt_Out)
		{
			R_DISP_DATA_Q.Watt_Out=R_DISP_DATA.Watt_Out;
			Watt_data_disp(R_DISP_DATA.Watt_Out);
		}
	}
	else
	{
		R_DISP_DATA_Q.Watt_Out=0x7fff;
		if(R_DISP_DATA_Q.Watt_Set!=R_DISP_DATA.Watt_Set)
		{
			R_DISP_DATA_Q.Watt_Set=R_DISP_DATA.Watt_Set;
			Watt_data_disp(R_DISP_DATA.Watt_Set);
		}
	}
}

///主界面输出曲线更新
void	Display_CustomOut(void)
{
	u8	i;
	if(B_Out_Yes)
	{
		if(R_Dis_Custom_X!=R_Dis_Custom_X_Q)
		{
			if(R_Dis_Custom_X_Q>21)
			{
				//GUI_Write_block(23,11,69,31,d_Clean_Color);
			}
			//GUI_Write_block(25+R_Dis_Custom_X*2,29,26+R_Dis_Custom_X*2,29-(*(R_Custom_Wout+R_Custom_I*21+R_Dis_Custom_X))*18/d_DIS_Watt_max,d_Bright_Color);
			R_Dis_Custom_X_Q=R_Dis_Custom_X;
		}
	}
	else
	{
		if(R_Dis_Custom_X_Q!=0xff)
		{
			R_Dis_Custom_X_Q=0xff;
			//GUI_Write_block(23,11,69,31,d_Clean_Color);
			for(i=0;i<21;i++)
			{
				//GUI_Write_block(25+i*2,29,26+i*2,29-(*(R_Custom_Wout+R_Custom_I*21+i))*18/d_DIS_Watt_max,d_Bright_Color);
			}
		}
	}
}

/////工作模式更新
void	Display_Work(void)
{
	if(R_Work_mode!=R_Work_mode_Q || R_Atomizer!=R_Atomizer_Q || R_TCR_term!=R_TCR_term_Q || R_Custom_I!=R_Custom_I_Q)
	{
		R_Work_mode_Q=R_Work_mode;
		R_Atomizer_Q=R_Atomizer;
		R_TCR_term_Q=R_TCR_term;
		R_Custom_I_Q=R_Custom_I;
		Work_mode_disp();
		//GUI_Write_block(21,11,69,31,d_Clean_Color);
		switch(R_Work_mode)
		{
			case	d_Watt_mode:			Watt_windows();break;
			case	d_Voltage_mode:
			case	d_Bypass_mode:		Volt_vout_windows();break;
			case	d_Temp_mode:
			case	d_TCR_mode:				Temp_windows();break;
		}
	}
}
/////工作界面小锁更新
void	Display_lock(void)
{
	if(B_Key_Shuo!=B_Key_Shuo_Q)
	{
		B_Key_Shuo_Q=B_Key_Shuo;
		lock_disp();
	}
}

//状态栏显示吸烟口数
u8	B_Status_bar;
#define		d_B_Status_bar_LOGO		0
#define		d_B_Status_bar_number	1
u8	R_Status_bar_Delay;
u16	R_disp_PULL;
u16	R_disp_PULL_Q;
u16	R_disp_TIM;
u16	R_disp_TIM_Q;
u32	R_R_Statistics_lengthTim_Q;
void	Status_bar_number_windows(void)
{
	//GUI_Write_block(1,0,79,8,d_Clean_Color);
	//GUI_Write_Chars(1,8,"P:",ZT9,d_Clean_Color,d_Bright_Color);
	//GUI_Write_Chars(36,8,"TIM:",ZT9,d_Clean_Color,d_Bright_Color);
	R_Status_bar_Delay=250;
	R_disp_PULL_Q=0xffff;
	R_disp_TIM_Q=0xffff;
	R_R_Statistics_lengthTim_Q=0xFFFFFFFF;
	B_Status_bar=d_B_Status_bar_number;
}
void	Status_bar_number(void)
{
	u8	danwei[2];
	u8	B;
	if(B_Display_STATISTICS)
	{
		if(B_Out_Yes|| (R_key_anxia==KEY_M))
			R_Status_bar_Delay=250;
		if(R_Status_bar_Delay)
		{
			R_Status_bar_Delay--;
			if(B_Status_bar==d_B_Status_bar_LOGO)
			{
				Status_bar_number_windows();
			}
			if(R_Statistics_number>999)
				R_disp_PULL=999;
			else
				R_disp_PULL=R_Statistics_number;
			if(R_disp_PULL_Q!=R_disp_PULL)
			{
				R_disp_PULL_Q=R_disp_PULL;
				//GUI_Write_data(10,8,3,R_disp_PULL,ZT9,d_Clean_Color,d_Bright_Color);
			}
			if(R_R_Statistics_lengthTim_Q!=R_Statistics_lengthTim)
			{
				R_R_Statistics_lengthTim_Q=R_Statistics_lengthTim;
				danwei[1]=0;
				B=0;
				if(R_Statistics_lengthTim<1000)
				{
					danwei[0]='s';
					R_disp_TIM=R_Statistics_lengthTim;
				}
				else if(R_Statistics_lengthTim<6000)
				{
					danwei[0]='m';
					R_disp_TIM=R_Statistics_lengthTim*10/60;
					B=1;
				}
				else if(R_Statistics_lengthTim<60000)
				{
					danwei[0]='m';
					R_disp_TIM=R_Statistics_lengthTim/60;
				}
				else if(R_Statistics_lengthTim<360000)
				{
					danwei[0]='h';
					R_disp_TIM=R_Statistics_lengthTim*10/3600;
					B=1;
				}
				else if(R_Statistics_lengthTim<36000000)
				{
					danwei[0]='h';
					R_disp_TIM=R_Statistics_lengthTim/3600;
				}
				if(R_disp_TIM_Q!=R_disp_TIM)
				{
					R_disp_TIM_Q=R_disp_TIM;
					//GUI_Write_block(56,0,79,8,d_Clean_Color);
					//GUI_Write_Chars(75,8,danwei,ZT9,d_Clean_Color,d_Bright_Color);
					if(B)
					{
						//GUI_Write_Line(67,7,67,8,d_Bright_Color);
						//GUI_Write_data(55,8,2,R_disp_TIM/10,ZT9,d_Clean_Color,d_Bright_Color);
						//GUI_Write_data(69,8,0,R_disp_TIM%10,ZT9,d_Clean_Color,d_Bright_Color);
					}
					else
					{
						//GUI_Write_data(56,8,3,R_disp_TIM,ZT9,d_Clean_Color,d_Bright_Color);
					}
				}
			}
		}
		else
		{
			if(B_Status_bar==d_B_Status_bar_number)
			{
				Work_logo_windows();
				B_Status_bar=d_B_Status_bar_LOGO;
			}
		}
	}
}

void	Display_The_Work(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=15;
		Dis_Start_operation();
		The_Work_interface();
		if(B_Display_STATISTICS)
			Status_bar_number_windows();
		else
		{
			Work_logo_windows();
			B_Status_bar=d_B_Status_bar_LOGO;
		}
		B_Switch_BLON=1;
	}
	Status_bar_number();
	Display_BAT();
	Display_Resistance();
	Display_Work();
	Display_lock();
	switch(R_Work_mode)
	{
		case	d_Watt_mode:			Display_Watt();		break;
		case	d_Voltage_mode:
		case	d_Bypass_mode:		Display_VOut();		break;
		case	d_Custom_mode:		Display_CustomOut();		break;
		case	d_TCR_mode:
		case	d_Temp_mode:			Display_Temp();		break;
	}
}
/********************************************************************************/
////////童锁功能/////////////
			///打印0-9键盘
void	Print_0to9keyboard(void)
{
	u8	i;
	u8	Schars[2];
	//GUI_Write_block(0,16,95,31,d_Bright_Color);
	//GUI_Write_Line(24,14,69,14,d_Bright_Color);
	Schars[1]='\0';
	for(i=0;i<10;i++)
	{
		Schars[0]='0'+i;
		//GUI_Write_Chars(3+i*9,30,Schars,ZT14,d_Bright_Color,d_Clean_Color);
	}
	///
	//GUI_Write_block(1,17,9,31,d_Transparent_Color);
}
	///显示当前输入的密码			B_yingchang=1:隐藏密码
void	Print_password(u8	*buf,u8	x,u8	B_yingchang)
{
	u8	i;
	u8	Schars[2];
	Schars[1]='\0';
	for(i=0;i<3;i++)
	{
		if(i<x)
		{
			if(B_yingchang)
			{
				Schars[0]='#';
			}
			else
			{
				Schars[0]=buf[i];
			}
		}
		else
		{
			Schars[0]='*';
		}
		//GUI_Write_Chars(33+i*12,13,Schars,ZT14,d_Clean_Color,d_Bright_Color);
	}
}
		///解锁界面
void	Unlock_windows(void)
{
	Print_0to9keyboard();
}
void	Display_Unlock(void)
{
	static	u8	Unlock_i,Unlock_i_Q;
	static	u8	R_shan;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=15;
		Dis_Start_operation();
		Unlock_windows();
		R_input_password_x=0;
		R_input_password_x_Q=0x70;
		Unlock_i_Q=0;
		Unlock_i=0;
		R_ii=&Unlock_i;
		R_shan=0;
		B_Password_error=0;
	}
	if(B_Password_error)
	{
		if(B_BAT_Twinkle)
		{
			B_BAT_Twinkle=0;
			if(R_shan%2)
			{
				//GUI_Write_block(30,2,63,13,d_Clean_Color);
				//GUI_Write_Chars(35,12,"Error",ZT9,d_Clean_Color,d_Bright_Color);
			}
			else
			{
				//GUI_Write_block(30,2,63,13,d_Clean_Color);
			}
			R_shan++;
		}
		if(R_shan>5)
		{
			B_Password_error=0;
			//GUI_Write_block(30,2,63,13,d_Clean_Color);
		}
	}
	else
	{
		if(R_shan)
		{
			R_shan=0;
			//GUI_Write_block(30,2,63,13,d_Clean_Color);
		}
		if(R_input_password_x_Q!=R_input_password_x)
		{
			R_input_password_x_Q=R_input_password_x;
			Print_password(R_input_password,R_input_password_x,0);
		}
	}
	if(Unlock_i_Q!=Unlock_i)
	{
		//GUI_Write_block(1+Unlock_i_Q*9,17,9+Unlock_i_Q*9,31,d_Transparent_Color);
		//GUI_Write_block(1+Unlock_i*9,17,9+Unlock_i*9,31,d_Transparent_Color);
		Unlock_i_Q=Unlock_i;
	}
	if(R_Window_keep_TimS<2)
	{
		R_DisStatus=Dis_Shuoji;
	}
}
/********************************************************************************/
		///锁机输入密码界面
void	Lock_windows(void)
{
	Print_0to9keyboard();
	//GUI_Write_Bitmap(92,21,Set_password_LOGO,d_Bright_Color,d_Clean_Color);
}
void	Display_Lock(void)
{
	static	u8 Lock_i,Lock_i_Q;
	static	u8	R_shan;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		Lock_windows();
		R_input_password_x=0;
		R_input_password_x_Q=0x70;
		Lock_i_Q=0;
		Lock_i=0;
		R_ii=&Lock_i;
		R_shan=0;
		B_Password_error=0;
	}
	if(B_Password_error)
	{
		if(B_BAT_Twinkle)
		{
			B_BAT_Twinkle=0;
			if(R_shan%2)
			{
				//GUI_Write_block(30,2,63,13,d_Clean_Color);
				//GUI_Write_Chars(35,12,"Error",ZT9,d_Clean_Color,d_Bright_Color);
			}
			else
			{
				//GUI_Write_block(30,2,63,13,d_Clean_Color);
			}
			R_shan++;
		}
		if(R_shan>5)
		{
			B_Password_error=0;
			//GUI_Write_block(30,2,63,13,d_Clean_Color);
		}
	}
	else
	{
		if(R_shan)
		{
			R_shan=0;
			//GUI_Write_block(30,2,63,13,d_Clean_Color);
		}
		if(R_input_password_x_Q!=R_input_password_x)
		{
			R_input_password_x_Q=R_input_password_x;
			Print_password(R_input_password,R_input_password_x,0);
		}
	}
	if(Lock_i_Q!=Lock_i)
	{
		//GUI_Write_block(1+Lock_i_Q*9,17,9+Lock_i_Q*9,31,d_Transparent_Color);
		//GUI_Write_block(1+Lock_i*9,17,9+Lock_i*9,31,d_Transparent_Color);
		if(Lock_i==10)
		{
			//GUI_Write_block(24,0,69,13,d_Clean_Color);
			//GUI_Write_Chars(32,11,"Reset",ZT9,d_Clean_Color,d_Bright_Color);
		}
		else	if(Lock_i_Q==10)
		{
			//GUI_Write_block(8,3,89,11,d_Clean_Color);
			R_input_password_x_Q=0x70;
		}
		Lock_i_Q=Lock_i;
	}
}
/********************************************************************************/
		///更改密码原来密码界面
void	Change_password_One_windows(void)
{
	Print_0to9keyboard();
	//GUI_Write_Chars(2,12,"Old:",ZT9,d_Clean_Color,d_Bright_Color);
}
void	Display_Change_password_One(void)
{
	static	u8 password_One_i,password_One_i_Q;
	static	u8	R_shan;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		Change_password_One_windows();
		R_input_password_x=0;
		R_input_password_x_Q=0x70;
		password_One_i_Q=0;
		password_One_i=0;
		R_ii=&password_One_i;
		R_shan=0;
		B_Password_error=0;
	}
	if(B_Password_error)
	{
		if(B_BAT_Twinkle)
		{
			B_BAT_Twinkle=0;
			if(R_shan%2)
			{
				//GUI_Write_block(30,2,63,13,d_Clean_Color);
				//GUI_Write_Chars(35,12,"Error",ZT9,d_Clean_Color,d_Bright_Color);
			}
			else
			{
				//GUI_Write_block(30,2,63,13,d_Clean_Color);
			}
			R_shan++;
		}
		if(R_shan>5)
		{
			B_Password_error=0;
			//GUI_Write_block(30,2,63,13,d_Clean_Color);
		}
	}
	else
	{
		if(R_shan)
		{
			R_shan=0;
			//GUI_Write_block(30,2,63,13,d_Clean_Color);
		}
		if(R_input_password_x_Q!=R_input_password_x)
		{
			R_input_password_x_Q=R_input_password_x;
			Print_password(R_input_password,R_input_password_x,0);
		}
	}
	if(password_One_i_Q!=password_One_i)
	{
		//GUI_Write_block(1+password_One_i_Q*9,17,9+password_One_i_Q*9,31,d_Transparent_Color);
		//GUI_Write_block(1+password_One_i*9,17,9+password_One_i*9,31,d_Transparent_Color);
		password_One_i_Q=password_One_i;
	}
}
/********************************************************************************/
		///输入新的密码
void	Change_password_Two_windows(void)
{
	Print_0to9keyboard();
	//GUI_Write_Chars(2,12,"New:",ZT9,d_Clean_Color,d_Bright_Color);
}
void	Display_Change_password_Two(void)
{
	static	u8 password_Two_i,password_Two_i_Q;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		Change_password_Two_windows();
		R_input_password_x=0;
		R_input_password_x_Q=0x70;
		password_Two_i_Q=0;
		password_Two_i=0;
		R_ii=&password_Two_i;
	}
	if(R_input_password_x_Q!=R_input_password_x)
	{
		R_input_password_x_Q=R_input_password_x;
		Print_password(R_input_password,R_input_password_x,0);
	}
	if(password_Two_i_Q!=password_Two_i)
	{
		//GUI_Write_block(1+password_Two_i_Q*9,17,9+password_Two_i_Q*9,31,d_Transparent_Color);
		//GUI_Write_block(1+password_Two_i*9,17,9+password_Two_i*9,31,d_Transparent_Color);
		password_Two_i_Q=password_Two_i;
	}
}
/********************************************************************************/
///更改logo界面
		//打印键盘
uc8	keyboard_kongge_LOGO[]={5,2,0x88,0xF8};
void	Print_AatoZzkeyboard(u8	Dchar)//打印字母键盘
{
	u8	i,j;
	u8	Schars[2];
	Schars[1]='\0';
	//GUI_Write_block(0,12,95,31,d_Bright_Color);
	//GUI_Write_block(87,1,95,11,d_Bright_Color);
	//GUI_Write_Bitmap(89,8,keyboard_kongge_LOGO,d_Bright_Color,d_Clean_Color);
	for(i=0;i<2;i++)
	{
		for(j=0;j<13;j++)
		{
			Schars[0]=Dchar;
			//GUI_Write_Chars(3+j*7+(6-(*ASCII9[Dchar-32]))/2,21+i*10,Schars,ZT9,d_Bright_Color,d_Clean_Color);
			Dchar++;
		}
	}
}

uc8	Digitalkeyboard_LOGO[]={89,18,
0x70,0x41,0xC3,0x81,0x0F,0x1C,0x7C,0x70,0xE0,0x82,0x8C,0x80,0x88,0xC2,0x24,0x43,
0x08,0x22,0x44,0x89,0x10,0x82,0x8D,0x00,0x88,0x42,0x20,0x45,0x10,0x20,0x04,0x89,
0x10,0x87,0xC1,0x00,0x88,0x40,0x21,0x85,0x1E,0x3C,0x08,0x71,0x10,0x82,0x82,0x00,
0x88,0x40,0x40,0x49,0x01,0x22,0x08,0x88,0xF0,0x87,0xC4,0x00,0x88,0x40,0x84,0x4F,
0x81,0x22,0x10,0x88,0x10,0x02,0x85,0x80,0x88,0x41,0x04,0x41,0x11,0x22,0x10,0x89,
0x10,0x82,0x89,0x80,0x70,0x43,0xE3,0x81,0x0E,0x1C,0x10,0x70,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x80,0x80,0x00,0x00,0x00,0x04,0x00,0x00,0x01,0x82,0x00,
0x20,0x42,0xA1,0x00,0x00,0x00,0x08,0x08,0x02,0x02,0x45,0x00,0x20,0x41,0xC1,0x00,
0x00,0x00,0x08,0x31,0xF1,0x80,0x48,0x80,0x20,0x40,0x87,0xCF,0x80,0x00,0x10,0xC0,
0x00,0x60,0x80,0x00,0x20,0x41,0xC1,0x00,0x00,0x00,0x20,0x31,0xF1,0x81,0x00,0x00,
0x20,0x42,0xA1,0x00,0x00,0x18,0x20,0x08,0x02,0x00,0x00,0x00,0x10,0x80,0x80,0x00,
0x1F,0x18,0x40,0x00,0x00,0x01,0x00,0x00,/*"C:\Users\Administrator\Desktop\5768221_1289012169875_1024x1024.bmp",0*/
/* (89 X 18 )*/
};

void	Print_Digitalkeyboard(void)//打印数字键盘
{
	//GUI_Write_block(0,12,95,31,d_Bright_Color);
	//GUI_Write_block(87,1,95,11,d_Bright_Color);
	//GUI_Write_Bitmap(89,8,keyboard_kongge_LOGO,d_Bright_Color,d_Clean_Color);
	//GUI_Write_Bitmap(3,13,Digitalkeyboard_LOGO,d_Bright_Color,d_Clean_Color);
}
		//键盘按键颜色去反
void	Color_keyboard(u8	key)
{
	if(key==26)
	{
		//GUI_Write_block(88,2,94,10,d_Transparent_Color);
	}
	else if(key<26)
	{
		//GUI_Write_block(2+(key%13)*7,(key/13)*10+13,8+(key%13)*7,(key/13)*10+21,d_Transparent_Color);
	}
}
		//显示输入字符
void	Print_logoChar(u8	x)
{
	u8	i;
	u8	L;//光标位置
	u8	Schars[2];
	Schars[1]='\0';
	L=0;
	for(i=0;i<x;i++)
	{
		L+=(*ASCII9[R_input_LOGO[i]-32]);
	}
	L=(83-L)/2;
	for(i=0;i<x;i++)
	{
		Schars[0]=R_input_LOGO[i];
		//GUI_Write_Chars(L,8,Schars,ZT9,d_Clean_Color,d_Bright_Color);
		L+=(*ASCII9[R_input_LOGO[i]-32]);
	}
	//GUI_Write_Line(L,8,L+5,8,d_Bright_Color);
	////GUI_Write_block(L,0,L+5,8,d_Bright_Color);
}
void	Display_Change_LOGO(void)
{
	static	u8 Change_LOGO_i,Change_LOGO_i_Q;
	static	u8 B_Big_small_Q;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();	
		if(R_input_LOGO_x==0)
		{
			R_input_LOGO_x_Q=0x70;
		}
		else
		{
			R_input_LOGO_x_Q=0x00;
		}
		R_ii=&Change_LOGO_i;
		B_Big_small_Q=0x70;
		B_Big_small=0x00;
		B_Switch_BLON=1;
	}
	if(B_Big_small_Q!=B_Big_small)
	{
		B_Big_small_Q=B_Big_small;
		Change_LOGO_i_Q=0x70;
		if(B_Big_small==0)
		{
			Print_AatoZzkeyboard('a');
		}
		else if(B_Big_small==1)
		{
			Print_AatoZzkeyboard('A');
		}
		else if(B_Big_small==2)
		{
			Print_Digitalkeyboard();
		}
	}
	if(R_input_LOGO_x_Q!=R_input_LOGO_x)
	{
		if(R_input_LOGO_x<R_input_LOGO_x_Q)
		{
			//GUI_Write_block(5,0,85,8,d_Clean_Color);
		}
		Print_logoChar(R_input_LOGO_x);
		R_input_LOGO_x_Q=R_input_LOGO_x;
	}
	if(Change_LOGO_i_Q!=Change_LOGO_i)
	{
		Color_keyboard(Change_LOGO_i_Q);
		Color_keyboard(Change_LOGO_i);
		Change_LOGO_i_Q=Change_LOGO_i;
	}
}

/**********************************************************************/
///TCR调节界面
void	TCR_adjust_windows(void)
{
	u8	i;
	for(i=0;i<6;i++)
	{
		//GUI_Write_Chars(TCR_zuobiao[i],9,TCR_name[i],ZT9,d_Clean_Color,d_Bright_Color);		
	}
	//GUI_Write_block(0,0,95,10,d_Transparent_Color);
	//GUI_Write_Chars(12,21,"PWR:",ZT9,d_Clean_Color,d_Bright_Color);		
	//GUI_Write_Chars(65,21,"W",ZT9,d_Clean_Color,d_Bright_Color);		
	//GUI_Write_Dot(53,20,d_Bright_Color);
	//GUI_Write_Chars(12,31,"TCR:",ZT9,d_Clean_Color,d_Bright_Color);		
	//GUI_Write_Chars(64,31,",",ZT9,d_Clean_Color,d_Bright_Color);		
	//GUI_Write_Dot(47,31,d_Bright_Color);
}
void	TCR_WattsMAX_data_disp(u16	data,u8	Selected)
{
	Color_TypeDef	R_Clean,R_Bright;
	if(Selected==0)
	{
		R_Clean=d_Bright_Color;
		R_Bright=d_Clean_Color;
	}
	else
	{
		R_Clean=d_Clean_Color;
		R_Bright=d_Bright_Color;
	}
	if(data<100)
	{
		//GUI_Write_block(41,12,45,20,R_Clean);
		//GUI_Write_data(47,20,1,data/10,ZT9,R_Clean,R_Bright);
		//GUI_Write_data(55,20,1,data%10,ZT9,R_Clean,R_Bright);
	}
	else
	{
		//GUI_Write_data(41,20,2,data/10,ZT9,R_Clean,R_Bright);
		//GUI_Write_data(55,20,1,data%10,ZT9,R_Clean,R_Bright);
	}
}
void	TCR_Gradient_data_disp(u16	data,u8	Selected)
{
	Color_TypeDef	R_Clean,R_Bright;
	if(Selected==1)
	{
		R_Clean=d_Bright_Color;
		R_Bright=d_Clean_Color;
	}
	else
	{
		R_Clean=d_Clean_Color;
		R_Bright=d_Bright_Color;
	}
	if(data==Load_Disability)
	{
		//GUI_Write_Chars(41,31,"-",ZT9,R_Clean,R_Bright);	
		//GUI_Write_Chars(49,31,"--",ZT9,R_Clean,R_Bright);		
	}
	else
	{
		//GUI_Write_data(41,31,1,data/100,ZT9,R_Clean,R_Bright);
		//GUI_Write_data(49,31,2,data%100,ZT9,R_Clean,R_Bright);
	}
}	
void	Display_TCR_adjust(void)
{
	static	u8	TCR_i,TCR_i_Q;
	static	u8	R_TCR_Selected_Q;								//选中的调节项
	static	u16	R_TCR_WattsMAX;									
	static	u16	R_TCR_Gradient;									
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		TCR_adjust_windows();
		TCR_i_Q=0x70;
		R_TCR_Selected_Q=0x70;
		R_TCR_WattsMAX=0x7000;									
		R_TCR_Gradient=0x7000;	
		if(R_Work_mode==d_Temp_mode)
		{
			if(R_Atomizer==Atomizer_0)
				TCR_i=2;
			else if(R_Atomizer==Atomizer_1)
				TCR_i=0;
			else if(R_Atomizer==Atomizer_2)
				TCR_i=1;
		}
		else if(R_Work_mode==d_TCR_mode)
		{
			TCR_i=R_TCR_term+3;
		}
		R_ii=&TCR_i;
	}
	if(TCR_i_Q!=TCR_i)
	{
		switch(TCR_i)
		{
			case	0:	Load_Set=&Load_Ni200;		break;
			case	1:	Load_Set=&Load_Ti;			break;
			case	2:	Load_Set=&Load_Ss316;		break;
			case	3:	Load_Set=&Load_M1;			break;
			case	4:	Load_Set=&Load_M2;			break;
			case	5:	Load_Set=&Load_M3;			break;
		}
		if(TCR_i_Q<6)
		{
			//GUI_Write_block(TCR_nameBOX[TCR_i_Q][0],0,TCR_nameBOX[TCR_i_Q][1],9,d_Transparent_Color);
		}
		//GUI_Write_block(TCR_nameBOX[TCR_i][0],0,TCR_nameBOX[TCR_i][1],9,d_Transparent_Color);
		TCR_i_Q=TCR_i;
	}
	if(R_TCR_Selected_Q!=R_TCR_Selected)
	{
		if(R_TCR_Selected_Q<2)
		{
			//GUI_Write_block(40,11+R_TCR_Selected_Q*11,60,21+R_TCR_Selected_Q*11,d_Transparent_Color);
		}
		//GUI_Write_block(40,11+R_TCR_Selected*11,60,21+R_TCR_Selected*11,d_Transparent_Color);
		R_TCR_Selected_Q=R_TCR_Selected;
	}
	if(R_TCR_WattsMAX!=Load_Set->WattsMAX)
	{
		TCR_WattsMAX_data_disp(Load_Set->WattsMAX,R_TCR_Selected);
		R_TCR_WattsMAX=Load_Set->WattsMAX;
	}
	if(R_TCR_Gradient!=Load_Set->Gradient)
	{
		TCR_Gradient_data_disp(Load_Set->Gradient,R_TCR_Selected);
		R_TCR_Gradient=Load_Set->Gradient;
	}
}



void	Custom_adjust_windows(void)
{
	//GUI_Write_block(0,0,95,31,d_Bright_Color);
	//GUI_Write_block(31,2,93,28,d_Clean_Color);
	//GUI_Write_Line(1,16,27,16,d_Clean_Color);
	//GUI_Write_Chars(22,14,"W",ZT9,d_Bright_Color,d_Clean_Color);
	//GUI_Write_Chars(22,28,"S",ZT9,d_Bright_Color,d_Clean_Color);
	//GUI_Write_Dot(13,27,d_Clean_Color);
	
}
////自定义曲线设置
void	Custom_Watt_Disp(u16	data)
{
	if(data>=1000)
	{
		//GUI_Write_data(2,14,3,data/10,ZT9,d_Bright_Color,d_Clean_Color);
	}
	else if(data>=100)
	{
		//GUI_Write_data(1,14,2,data/10,ZT9,d_Bright_Color,d_Clean_Color);
		//GUI_Write_data(15,14,1,data%10,ZT9,d_Bright_Color,d_Clean_Color);
	}
	else
	{
		//GUI_Write_block(1,5,5,14,d_Bright_Color);
		//GUI_Write_data(7,14,1,data/10,ZT9,d_Bright_Color,d_Clean_Color);
		//GUI_Write_data(15,14,1,data%10,ZT9,d_Bright_Color,d_Clean_Color);
	}
}
void	Custom_s_Disp(void)
{
	u8	i;
	//GUI_Write_Line(32,3,32,27,d_Clean_Color);
	for(i=1;i<21;i++)
	{
		//GUI_Write_block(30+i*3,3,32+i*3,27,d_Clean_Color);
		//GUI_Write_Line(29+i*3,27-(*(RAM_Custom_Wout+R_Custom_I*21+i-1))*24/d_DIS_Watt_max,32+i*3,27-(*(RAM_Custom_Wout+R_Custom_I*21+i))*24/d_DIS_Watt_max,d_Bright_Color);
	}
}
void	Display_Custom_adjust(void)
{
	static	u8	tim=0,tim_Q;
	static	u16	Watt;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		Custom_adjust_windows();
		tim_Q=0xff;
		Watt=0xffff;
		R_ii=&tim;
	}

	if(tim_Q!=tim)
	{
		R_Window_keep_TimS=R_Window_Tim_MAX;
		//Watt=0xffff;
		if(tim_Q!=0xff)
		{
			//GUI_Write_Line(32+tim_Q*3,29,32+tim_Q*3,30,d_Bright_Color);
		}
		//GUI_Write_Line(32+tim*3,29,32+tim*3,30,d_Clean_Color);
		//GUI_Write_data(1,28,2,tim*5/10,ZT9,d_Bright_Color,d_Clean_Color);
		//GUI_Write_data(15,28,1,tim*5%10,ZT9,d_Bright_Color,d_Clean_Color);
		tim_Q=tim;
	}
	if(Watt!=(*(RAM_Custom_Wout+R_Custom_I*21+tim)))
	{
		R_Window_keep_TimS=R_Window_Tim_MAX;
		if((Watt>=1000 && (*(RAM_Custom_Wout+R_Custom_I*21+tim))<1000) || (Watt<1000 && (*(RAM_Custom_Wout+R_Custom_I*21+tim))>=1000))
		{
			//GUI_Write_block(1,5,19,14,d_Bright_Color);
			if((*(RAM_Custom_Wout+R_Custom_I*21+tim))<1000)
			{
				//GUI_Write_Dot(13,13,d_Clean_Color);
			}
		}
		Custom_Watt_Disp((*(RAM_Custom_Wout+R_Custom_I*21+tim)));
		if(Watt*24/d_DIS_Watt_max!=(*(RAM_Custom_Wout+R_Custom_I*21+tim))*24/d_DIS_Watt_max)
		{
			if(Watt!=0xffff)
			{
				//GUI_Write_Line(29,27-Watt*24/d_DIS_Watt_max,30,27-Watt*24/d_DIS_Watt_max,d_Bright_Color);
			}
			//GUI_Write_Line(29,27-(*(RAM_Custom_Wout+R_Custom_I*21+tim))*24/d_DIS_Watt_max,30,27-(*(RAM_Custom_Wout+R_Custom_I*21+tim))*24/d_DIS_Watt_max,d_Clean_Color);
			Custom_s_Disp();
		}
		Watt=(*(RAM_Custom_Wout+R_Custom_I*21+tim));
	}
	
}


////////////////USB电量低界面////////////////////
uc8	LOW_USB_LOGO[]={48,28,
0x00,0xE4,0x00,0x00,0x00,0x00,0x01,0x14,0x00,0x00,0x20,0x00,0x02,0x04,0x00,0x00,
0x21,0x00,0x02,0x04,0x00,0x00,0x22,0x00,0x02,0x07,0xC3,0x07,0x24,0x00,0x02,0x04,
0x24,0x88,0xA8,0x00,0x02,0x04,0x28,0x50,0x30,0x00,0x02,0x04,0x2F,0xD0,0x28,0x00,
0x02,0x04,0x28,0x10,0x24,0x00,0x01,0x14,0x24,0x48,0xA2,0x00,0x00,0xE4,0x23,0x87,
0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x39,0x00,0x00,0x00,0x00,0x00,
0x45,0x00,0x00,0x00,0x00,0x00,0x81,0x00,0x00,0x00,0x00,0x00,0x81,0x00,0x00,0x00,
0x00,0x00,0x81,0xF1,0xC4,0xCF,0x8C,0x4C,0x81,0x0A,0x25,0x11,0x12,0x50,0x81,0x09,
0xE6,0x11,0x21,0x60,0x81,0x0A,0x24,0x0E,0x3F,0x40,0x81,0x0A,0x24,0x10,0x20,0x40,
0x45,0x0A,0x24,0x0F,0x11,0x40,0x39,0x09,0xD4,0x10,0x8E,0x40,0x00,0x00,0x00,0x10,
0x80,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,/*"C:\Users\Administrator\Desktop\123.bmp",0*/
/* (48 X 28 )*/};
uc8	LOW_USB_Z_LOGO[]={79,14,
0x10,0x40,0x01,0x00,0x02,0x00,0x01,0x00,0x3E,0x7C,0x10,0x40,0x01,0x00,0x01,0x00,
0x01,0x00,0x22,0x44,0x10,0xA0,0x7F,0xFC,0x7F,0xFC,0x3F,0xF8,0x22,0x44,0xFD,0x10,
0x05,0x40,0x04,0x00,0x21,0x08,0x3E,0x7C,0x12,0x08,0x09,0x20,0x08,0x20,0x21,0x08,
0x00,0x80,0x35,0xF6,0x31,0x18,0x10,0x10,0x3F,0xF8,0x3F,0xFC,0x38,0x00,0xC1,0x06,
0x3F,0xF8,0x21,0x08,0x01,0x60,0x54,0x88,0x1F,0xF0,0x04,0x48,0x21,0x08,0x06,0x30,
0x50,0x48,0x10,0x10,0x04,0x40,0x21,0x08,0x78,0x0E,0x92,0x48,0x1F,0xF0,0x04,0x40,
0x3F,0xF8,0x3E,0x7C,0x11,0x50,0x10,0x10,0x04,0x40,0x01,0x02,0x22,0x44,0x11,0x10,
0x1F,0xF0,0x08,0x44,0x01,0x02,0x22,0x44,0x10,0x20,0x00,0x00,0x08,0x44,0x01,0xFE,
0x3E,0x7C,0x17,0xFE,0x7F,0xFE,0x30,0x3C,0x00,0x00,0x22,0x44,/*"C:\Users\Administrator\Desktop\123.bmp",0*/
/* (79 X 14 )*/};
void	LOW_USB_interface(void)
{
	if(R_Language==English)
	{
		//GUI_Write_Bitmap(28,3,LOW_USB_LOGO,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//GUI_Write_Bitmap(9,10,LOW_USB_Z_LOGO,d_Clean_Color,d_Bright_Color);
	}
}
void	Display_LOW_USB(void)
{
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		LOW_USB_interface();
		R_Win_tim=500;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
}


//////////////灭屏/////////
void	Display_pintfOFF(void)
{	
	if(R_DisStatus_Q != R_DisStatus)
	{
		New_DisStatus_S();
		R_DisStatus_Q=R_DisStatus;
		R_Window_Tim_MAX=5;
		R_Window_keep_TimS=R_Window_Tim_MAX;
		if(B_OLED_BL)
		{
			Disp_OFF();
		}
	}
}

////////////////////屏幕参数设置/////////////////////////////////////////////////////
uc8	liangdu_LOGO[]={15,15,0x1F,0xF0,0x20,0x08,0x41,0x04,0x91,0x12,0x88,0x22,0x83,0x82,0x87,0xC2,0xB7,0xDA,
0x87,0xC2,0x83,0x82,0x88,0x22,0x91,0x12,0x41,0x04,0x20,0x08,0x1F,0xF0};
uc8	Screen_BOX[][4]={37,0,82,16,
										18,19,87,29};//英文界面下

uc8	zhuangping_LOGO[]={32,13,0x30,0x40,0x0F,0xFE,0x20,0x80,0x08,0x02,0xFF,0xF8,0x08,0x02,0x30,0x80,0x0F,0xFE,
0x50,0x80,0x09,0x04,0x57,0xF8,0x08,0x88,0xFD,0x00,0x0B,0xFF,0x11,0xF8,0x08,0x88,
0x14,0x10,0x0F,0xFF,0x78,0x20,0x08,0x88,0x91,0xC0,0x08,0x88,0x10,0xC0,0x11,0x08,
0x10,0x20,0x12,0x08};
uc8	zidong_LOGO[]={31,13,0x10,0x00,0x00,0x10,0x10,0x00,0x1F,0x10,0xFF,0x80,0x00,0x10,0x80,0x80,0x00,0xFE,
0x80,0x80,0x00,0x12,0xFF,0x80,0x3F,0x12,0x80,0x80,0x08,0x12,0x80,0x80,0x0A,0x12,
0xFF,0x80,0x12,0x12,0x80,0x80,0x11,0x22,0x80,0x80,0x2F,0x22,0xFF,0x80,0x30,0xC2,
0x80,0x80,0x00,0xCC};
uc8	xiangshang_LOGO[]={11,13,0x04,0x00,0x0E,0x00,0x1F,0x00,0x3F,0x80,0x7F,0xC0,0xFF,0xE0,0x1F,0x00,0x1F,0x00,
0x1F,0x00,0x1F,0x00,0x1F,0x00,0x1F,0x00,0x1F,0x00};
uc8	xiangxia_LOGO[]={11,13,0x1F,0x00,0x1F,0x00,0x1F,0x00,0x1F,0x00,0x1F,0x00,0x1F,0x00,0x1F,0x00,0xFF,0xE0,
0x7F,0xC0,0x3F,0x80,0x1F,0x00,0x0E,0x00,0x04,0x00};
uc8	Screen_BOX2[][4]={47,0,89,16,
										18,19,87,29};//英文界面下


void	Screen_windows(void)
{
	if(R_Language==English)
	{
		//GUI_Write_Chars(2,14,"FLIP:",ZT14,d_Clean_Color,d_Bright_Color);
	}
	else
	{
		//GUI_Write_Bitmap(2,2,zhuangping_LOGO,d_Clean_Color,d_Bright_Color);
		//GUI_Write_block(39,4,40,5,d_Bright_Color);
		//GUI_Write_block(39,11,40,12,d_Bright_Color);
	}
	
	//GUI_Write_Bitmap(2,17,liangdu_LOGO,d_Clean_Color,d_Bright_Color);
	//GUI_Write_Line(22,23,22,25,d_Bright_Color);
	//GUI_Write_Line(83,23,83,25,d_Bright_Color);
	//GUI_Write_Line(23,22,82,22,d_Bright_Color);
	//GUI_Write_Line(23,26,82,26,d_Bright_Color);
}
u8	R_Screen_FLIP=0;
u8	R_Screen_Light=10;
void	Display_Screen_setting(void)
{
	static	u8	R_tiaojie_i=0,R_tiaojie_i_Q;
	static	u8	R_Screen_FLIP_Q,R_Screen_Light_Q;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		Screen_windows();
		R_tiaojie_i_Q=0x70;
		R_Screen_FLIP_Q=0x70;
		R_Screen_Light_Q=0x70;
		R_ii=&R_tiaojie_i;
	}
	if(R_tiaojie_i_Q!=R_tiaojie_i)
	{
		if(R_Language==English)
		{
			if(R_tiaojie_i_Q<2)
			{
				//GUI_Write_Rectangular(Screen_BOX[R_tiaojie_i_Q][0],Screen_BOX[R_tiaojie_i_Q][1],Screen_BOX[R_tiaojie_i_Q][2],Screen_BOX[R_tiaojie_i_Q][3],d_Clean_Color);
			}
			//GUI_Write_Rectangular(Screen_BOX[R_tiaojie_i][0],Screen_BOX[R_tiaojie_i][1],Screen_BOX[R_tiaojie_i][2],Screen_BOX[R_tiaojie_i][3],d_Bright_Color);
		}
		else
		{
			if(R_tiaojie_i_Q<2)
			{
				//GUI_Write_Rectangular(Screen_BOX2[R_tiaojie_i_Q][0],Screen_BOX2[R_tiaojie_i_Q][1],Screen_BOX2[R_tiaojie_i_Q][2],Screen_BOX2[R_tiaojie_i_Q][3],d_Clean_Color);
			}
			//GUI_Write_Rectangular(Screen_BOX2[R_tiaojie_i][0],Screen_BOX2[R_tiaojie_i][1],Screen_BOX2[R_tiaojie_i][2],Screen_BOX2[R_tiaojie_i][3],d_Bright_Color);
		}
		
		R_tiaojie_i_Q=R_tiaojie_i;
	}
	if(R_Screen_FLIP_Q!=R_Screen_FLIP)
	{
		R_Screen_FLIP_Q=R_Screen_FLIP;
		if(R_Language==English)
		{
			//GUI_Write_block(40,1,80,14,d_Clean_Color);
			if(R_Screen_FLIP==0)
			{
				//GUI_Write_Chars(44,14,"AUTO",ZT14,d_Clean_Color,d_Bright_Color);
			}
			else	if(R_Screen_FLIP==1)
			{
				//GUI_Write_Chars(53,14,"UP",ZT14,d_Clean_Color,d_Bright_Color);
			}
			else	if(R_Screen_FLIP==2)
			{
				//GUI_Write_Chars(45,14,"DOWN",ZT14,d_Clean_Color,d_Bright_Color);
			}
		}
		else
		{
			//GUI_Write_block(50,1,85,14,d_Clean_Color);
			if(R_Screen_FLIP==0)
			{
				//GUI_Write_Bitmap(53,2,zidong_LOGO,d_Clean_Color,d_Bright_Color);
			}
			else	if(R_Screen_FLIP==1)
			{
				//GUI_Write_Bitmap(62,2,xiangshang_LOGO,d_Clean_Color,d_Bright_Color);
			}
			else	if(R_Screen_FLIP==2)
			{
				//GUI_Write_Bitmap(62,2,xiangxia_LOGO,d_Clean_Color,d_Bright_Color);
			}
		}
		
	}
	if(R_Screen_Light_Q!=R_Screen_Light)
	{
		R_Screen_Light_Q=R_Screen_Light;
//		if(R_Screen_Light)
			//GUI_Write_block(23,23,22+R_Screen_Light*6,25,d_Bright_Color);
//		if(R_Screen_Light<10)
			//GUI_Write_block(23+R_Screen_Light*6,23,82,25,d_Clean_Color);
	}
}
////////////////////////////////////////////////////////////////////////////////

///////////////菜单图标/////////////////////////////////////////
uc8	KEY_LOCK_LOGO[]={16,17,0x00,0x00,0x01,0x80,0x02,0x40,0x02,0x40,0x07,0xE0,0x07,0xE0,0x07,0xE0,0x00,0x00,
0xFE,0x7F,0xAA,0x41,0xAA,0x77,0xD6,0x77,0x00,0x00,0xFE,0x7F,0xEE,0x7F,0x82,0x41,
0xEE,0x7F};
uc8	KEY_UNLOCK_LOGO[]={16,17,0x00,0x00,0x00,0x30,0x00,0x48,0x00,0x48,0x07,0xE0,0x07,0xE0,0x07,0xE0,0x00,0x00,
0xFE,0x7F,0xAA,0x41,0xAA,0x77,0xD6,0x77,0x00,0x00,0xFE,0x7F,0xEE,0x7F,0x82,0x41,
0xEE,0x7F};
uc8	PASSWORD_LOGO[]={16,17,0x07,0xE0,0x0F,0xF0,0x1C,0x38,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7F,0xFE,
0x7F,0xFE,0x7F,0xFE,0x7E,0x7E,0x7F,0x7E,0x7E,0x7E,0x7F,0x7E,0x7F,0xFE,0x7F,0xFE,
0x7F,0xFE};
uc8	SCREEN_LOGO[]={16,17,0x00,0x00,0x7F,0xFE,0x40,0x02,0x41,0x22,0x42,0x42,0x44,0x82,0x49,0x02,0x42,0x02,
0x40,0x02,0x40,0x02,0x7F,0xFE,0x7F,0xFE,0x03,0xC0,0x07,0xE0,0x0F,0xF0,0x0F,0xF0,
0x00,0x00};
uc8	LANGUAGE_LOGO[]={16,17,0x00,0x00,0x00,0x00,0x7E,0xC6,0x7E,0xC6,0x60,0xE6,0x60,0xE6,0x60,0xF6,0x60,0xF6,
0x7E,0xD6,0x7E,0xD6,0x60,0xDE,0x60,0xDE,0x60,0xCE,0x60,0xCE,0x7E,0xC6,0x7E,0xC6,
0x00,0x00};
uc8	UPDATE_LOGO[]={16,17,0x07,0xFE,0x0C,0x02,0x14,0x02,0x24,0x02,0x7C,0x02,0x40,0x02,0x40,0x02,0x4F,0xFA,
0x40,0x02,0x47,0xC2,0x40,0x02,0x47,0xE2,0x40,0x02,0x40,0x02,0x40,0x32,0x40,0x02,
0x7F,0xFE};
uc8	STATISTICS_LOGO[]={16,17,0x00,0x00,0x00,0xE0,0x00,0x60,0x00,0xA0,0x01,0x06,0x02,0x06,0x04,0x06,0x08,0x36,
0x10,0x36,0x21,0xB6,0x41,0xB6,0x0D,0xB6,0x6D,0xB6,0x6D,0xB6,0x00,0x00,0xFF,0xFF,
0x00,0x00};
uc8 *menu[]={KEY_LOCK_LOGO,PASSWORD_LOGO,SCREEN_LOGO,UPDATE_LOGO,STATISTICS_LOGO};

uc8	KEY_LOCK_EN[]="KEY LOCK";
uc8	KEY_UNLOCK_EN[]="KEY UNLOCK";
uc8	PASSWORD_EN[]="CHILD LOCK";
uc8	SCREEN_EN[]="SCREEN";
//uc8	LANGUAGE_EN[]="LANGUAGE";
uc8	UPDATE_EN[]="UPDATE LOGO";
uc8	STATISTICS_EN[]="COUNTER";
uc8 *menu_EN[]={KEY_LOCK_EN,PASSWORD_EN,SCREEN_EN,UPDATE_EN,STATISTICS_EN};

u8	KEY_lock_UP(void)
{
	if(B_Key_Shuo && menu[0]== KEY_LOCK_LOGO)
	{
		menu[0]=KEY_UNLOCK_LOGO;
		menu_EN[0]=KEY_UNLOCK_EN;
		return	1;
	}
	if(!B_Key_Shuo && menu[0]== KEY_UNLOCK_LOGO)
	{
		menu[0]=KEY_LOCK_LOGO;
		menu_EN[0]=KEY_LOCK_EN;
		return	1;
	}
	return 0;
}
void	menu_windows(void)
{
	u8	i;
	KEY_lock_UP();
	for(i=0;i<5;i++)
	{
		//GUI_Write_Bitmap(2+i*19,11,menu[i],d_Clean_Color,d_Bright_Color);
	}
	//GUI_Write_Line(0,30,95,30,d_Bright_Color);
}
void	Disp_menu(void)
{
	static	u8	R_menu_i=0,R_menu_Q;
	u8	i,L;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		menu_windows();
		R_menu_Q=0x70;
		R_ii=&R_menu_i;
	}
	if(R_menu_Q!=R_menu_i)
	{
		if(R_menu_Q<5)
		{
			//GUI_Write_block(1+19*R_menu_Q,10,18+19*R_menu_Q,28,d_Transparent_Color);
		}
		//GUI_Write_block(1+19*R_menu_i,10,18+19*R_menu_i,28,d_Transparent_Color);
		//GUI_Write_block(0,0,95,8,d_Clean_Color);
		
		L=0;
		for(i=0;i<20;i++)
		{
			if(menu_EN[R_menu_i][i]=='\0')
				break;
			L+=*ASCII9[menu_EN[R_menu_i][i]-32];
		}
		//GUI_Write_Chars((96-L)/2,8,menu_EN[R_menu_i],ZT9,d_Clean_Color,d_Bright_Color);
		
		//GUI_Write_Line(0,31,95,31,d_Clean_Color);
		//GUI_Write_Line(R_menu_i*96/5,31,R_menu_i*96/5+20,31,d_Bright_Color);
		R_menu_Q=R_menu_i;
	}
}


/////////////////////////////////////////////////////////////////////////

/////////选择操作方式  组合键方式还是菜单方式////////////////////
uc8	Operation_mode_LOGO[]={63,15,0x21,0xF0,0x09,0x00,0x02,0x00,0x00,0x48,0x21,0x10,0x09,0x00,0x01,0x00,0x00,0x44,
0x21,0xF0,0x09,0x00,0x01,0x00,0x00,0x44,0x20,0x00,0x11,0xFE,0xFF,0xFE,0x00,0x40,
0xF7,0xBC,0x12,0x80,0x04,0x00,0xFF,0xFE,0x24,0xA4,0x32,0x80,0x04,0x00,0x00,0x40,
0x27,0xBC,0x54,0x80,0x04,0x00,0x00,0x40,0x30,0x40,0x90,0xFC,0x07,0xF8,0x7E,0x40,
0x6F,0xFE,0x10,0x80,0x04,0x08,0x10,0x40,0xA0,0xE0,0x10,0x80,0x04,0x08,0x10,0x20,
0x21,0x50,0x10,0xFC,0x08,0x08,0x10,0x22,0x22,0x48,0x10,0x80,0x08,0x08,0x10,0x12,
0xA4,0x44,0x10,0x80,0x10,0x08,0x1F,0x0A,0x68,0x42,0x10,0x80,0x20,0x50,0xF0,0x06,
0x20,0x40,0x10,0x80,0xC0,0x20,0x40,0x02};
uc8	Combination_key_LOGO[]={47,14,0x11,0xF8,0x01,0x00,0x20,0x10,0x11,0x08,0x01,0x00,0x3B,0x7C,0x21,0x08,0x02,0x80,
0x41,0x14,0x21,0x08,0x04,0x40,0x41,0xFE,0x49,0xF8,0x08,0x20,0xFA,0x14,0xF9,0x08,
0x10,0x10,0xA2,0x7C,0x11,0x08,0x2F,0xE8,0x22,0x10,0x21,0x08,0xC0,0x06,0x27,0x7C,
0x41,0xF8,0x00,0x00,0xF9,0x10,0xF9,0x08,0x1F,0xF0,0x25,0xFE,0x41,0x08,0x10,0x10,
0x25,0x10,0x19,0x08,0x10,0x10,0x2A,0x10,0x61,0x08,0x10,0x10,0x35,0x00,0x87,0xFE,
0x1F,0xF0,0x28,0xFE};
uc8	Menu_LOGO[]={31,14,0x08,0x20,0x08,0x10,0xFF,0xFC,0x04,0x20,0x08,0x20,0x3F,0xF8,0x00,0x08,0x21,0x08,
0x00,0x78,0x21,0x08,0x3F,0x80,0x3F,0xF8,0x11,0x10,0x21,0x08,0x09,0x20,0x21,0x08,
0x01,0x00,0x3F,0xF8,0x7F,0xF8,0x01,0x00,0x05,0x40,0xFF,0xFE,0x09,0x20,0x01,0x00,
0x11,0x10,0x01,0x00,0x61,0x0C,0x01,0x00};
uc8	Operation_ZB[][4]={{0,16,50,31},{61,16,95,31}};
uc8	Operation_CB[][4]={{2,16,32,31},{56,16,94,31}};

void	Operation_windows(void)
{
	if(R_Language==English)
	{
		//GUI_Write_Chars(15,13,"OPERATION",ZT14,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Chars(6,30,"KEY",ZT14,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Chars(60,30,"MENU",ZT14,d_Clean_Color,d_Bright_Color);
		R_i2=(uc8 *)Operation_CB;
	}
	else
	{
		//GUI_Write_Bitmap(16,0,Operation_mode_LOGO,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Bitmap(2,17,Combination_key_LOGO,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Bitmap(63,17,Menu_LOGO,d_Clean_Color,d_Bright_Color);
		R_i2=(uc8 *)Operation_ZB;
	}
}

#if 0	//操作模式选择界面
void	Display_Operation(void)
{
	static	u8	R_mode_i=0,R_mode_Q;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		Operation_windows();
		R_mode_Q=0x70;
		R_ii=&R_mode_i;
	}
	if(R_mode_Q!=R_mode_i)
	{
		if(R_mode_Q<2)
			//GUI_Write_block(((uc8 (*)[4])R_i2)[R_mode_Q][0],((uc8 (*)[4])R_i2)[R_mode_Q][1],((uc8 (*)[4])R_i2)[R_mode_Q][2],((uc8 (*)[4])R_i2)[R_mode_Q][3],d_Transparent_Color);
		//GUI_Write_block(((uc8 (*)[4])R_i2)[R_mode_i][0],((uc8 (*)[4])R_i2)[R_mode_i][1],((uc8 (*)[4])R_i2)[R_mode_i][2],((uc8 (*)[4])R_i2)[R_mode_i][3],d_Transparent_Color);
		R_mode_Q=R_mode_i;
	}
}
#endif

uc8 DataStr[]=__DATE__;
uc8 TimeStr[]=__TIME__;
void	Display_Firmware_data(void)
{
	u8 Schar[11];
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		//GUI_Write_Chars(3,16,d_Firmware_version,ZT14,d_Clean_Color,d_Bright_Color);
		Schar[0]=DataStr[9];
		Schar[1]=DataStr[10];
		if(DataStr[0]=='F')
		{
			Schar[2]='0';
			Schar[3]='2';
		}
		else if(DataStr[0]=='S')
		{
			Schar[2]='0';
			Schar[3]='9';
		}
		else if(DataStr[0]=='O')
		{
			Schar[2]='1';
			Schar[3]='0';
		}
		else if(DataStr[0]=='N')
		{
			Schar[2]='1';
			Schar[3]='1';
		}
		else if(DataStr[0]=='D')
		{
			Schar[2]='1';
			Schar[3]='2';
		}
		else if(DataStr[0]=='J')
		{
			if(DataStr[1]=='a')
			{
				Schar[2]='0';
				Schar[3]='1';
			}
			else if(DataStr[2]=='n')
			{
				Schar[2]='0';
				Schar[3]='6';
			}
			else
			{
				Schar[2]='0';
				Schar[3]='7';
			}
		}
		else if(DataStr[0]=='M')
		{
			if(DataStr[2]=='r')
			{
				Schar[2]='0';
				Schar[3]='3';
			}
			else
			{
				Schar[2]='0';
				Schar[3]='5';
			}
		}
		else if(DataStr[0]=='A')
		{
			if(DataStr[1]=='p')
			{
				Schar[2]='0';
				Schar[3]='4';
			}
			else
			{
				Schar[2]='0';
				Schar[3]='8';
			}
		}
		Schar[4]=DataStr[4];
		Schar[5]=DataStr[5];
		Schar[6]=TimeStr[0];
		Schar[7]=TimeStr[1];
		Schar[8]=TimeStr[3];
		Schar[9]=TimeStr[4];
		Schar[10]=0;
		//GUI_Write_Chars(20,31,Schar,ZT14,d_Clean_Color,d_Bright_Color);
		R_Win_tim=1000;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
}
//统计界面显示
u8	B_FullBattClear=0;				//满电清除吸烟口数标志  	 	0：关闭		1：打开
u8	B_Display_STATISTICS=0;		//主界面显示统计数据标志   0：关闭		1：打开
u8	B_SpeedBrake=0;						//吸烟超速保护				  	 	0：关闭		1：打开
u8	R_STATISTICS_cursor=0;		//光标位置
u8	R_STATISTICS_cursor_Q=0;		//上一次光标位置
#define	d_STATISTICS_lowerPAGE	2		//下一页按键光标值
#define	d_STATISTICS_upperPAGE	3		//上一页按键光标值
#define	d_STATISTICS_cursorMAX	6		//光标最大值

uc8	Dustbin_LOGO[]={7,11,0x38,0xFE,0x00,0xFE,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0x7C};//垃圾箱LOGO
uc8	STATISTICS_lowerPAGE_LOGO[]={4,7,0x80,0xC0,0xE0,0xF0,0xE0,0xC0,0x80};					//下一页LOGO
uc8	STATISTICS_upperPAGE_LOGO[]={4,7,0x10,0x30,0x70,0xF0,0x70,0x30,0x10};					//上一页LOGO

uc8	R_STATISTICS_ON_char[]="ON";
uc8	R_STATISTICS_OFF_char[]="OFF";
void	Print_PUFF_Data(void)//打印吸烟口数数据
{
	//GUI_Write_block(28,0,56,8,d_Clean_Color);
	//GUI_Write_data(28,8,0,R_Statistics_number,ZT9,d_Clean_Color,d_Bright_Color);
}
void	Print_TIM_Data(void)//打印吸烟时长数据
{
	u32	a=10;
	u8	i=1;
	//GUI_Write_block(33,11,67,19,d_Clean_Color);
	//GUI_Write_data(33,19,0,R_Statistics_lengthTim,ZT9,d_Clean_Color,d_Bright_Color);
	while(R_Statistics_lengthTim/a)
	{
		a*=10;
		i++;
	}
	//GUI_Write_Chars(34+i*6,20,"s",ZT9,d_Clean_Color,d_Bright_Color);
}
void	Print_LIMIT_PUFF_Data(void)//打印限制口数数据
{
	Color_TypeDef	Background,Colour;
	u8	i=1;
	u16	a=10;
	if(R_STATISTICS_cursor==1)
	{
		Background=d_Bright_Color;
		Colour=d_Clean_Color;
	}
	else
	{
		Background=d_Clean_Color;
		Colour=d_Bright_Color;
	}
	//GUI_Write_block(73,22,89,30,Background);
	while(R_Set_number/a)
	{
		a*=10;
		i++;
	}
	//GUI_Write_data(82-i*3,30,0,R_Set_number,ZT9,Background,Colour);
}
void	Print_cursor(void)//显示光标位置
{
	static	uc8	STATISTICS_cursorXY[d_STATISTICS_cursorMAX+1][4]={{78,2,88,16},{71,21,91,31},{91,0,96,31},{0,0,4,31},{77,0,95,9},{46,11,64,20},{70,22,88,31}};
	
	//GUI_Write_block(STATISTICS_cursorXY[R_STATISTICS_cursor][0],\
											STATISTICS_cursorXY[R_STATISTICS_cursor][1],\
											STATISTICS_cursorXY[R_STATISTICS_cursor][2],\
											STATISTICS_cursorXY[R_STATISTICS_cursor][3],d_Transparent_Color);
	if((R_STATISTICS_cursor_Q<=d_STATISTICS_lowerPAGE && R_STATISTICS_cursor<=d_STATISTICS_lowerPAGE)\
		||(R_STATISTICS_cursor_Q<=d_STATISTICS_cursorMAX && R_STATISTICS_cursor>=d_STATISTICS_upperPAGE && R_STATISTICS_cursor_Q>=d_STATISTICS_upperPAGE))
	{
		//GUI_Write_block(STATISTICS_cursorXY[R_STATISTICS_cursor_Q][0],\
											STATISTICS_cursorXY[R_STATISTICS_cursor_Q][1],\
											STATISTICS_cursorXY[R_STATISTICS_cursor_Q][2],\
											STATISTICS_cursorXY[R_STATISTICS_cursor_Q][3],d_Transparent_Color);
	}
	R_STATISTICS_cursor_Q=R_STATISTICS_cursor;
}
void	Print_FullBattClear(void)//打印充满清除开关
{
	Color_TypeDef	Background,Colour;
	if(R_STATISTICS_cursor==4)
	{
		Background=d_Bright_Color;
		Colour=d_Clean_Color;
	}
	else
	{
		Background=d_Clean_Color;
		Colour=d_Bright_Color;
	}
	//GUI_Write_block(78,1,94,8,Background);
//	if(B_FullBattClear)
		//GUI_Write_Chars(81,9,R_STATISTICS_ON_char,ZT9,Background,Colour);
//	else
		//GUI_Write_Chars(78,9,R_STATISTICS_OFF_char,ZT9,Background,Colour);
}
void	Print_Display_STATISTICS(void)//打印显示使能开关
{
	Color_TypeDef	Background,Colour;
	if(R_STATISTICS_cursor==5)
	{
		Background=d_Bright_Color;
		Colour=d_Clean_Color;
	}
	else
	{
		Background=d_Clean_Color;
		Colour=d_Bright_Color;
	}
	//GUI_Write_block(47,12,63,19,Background);
//	if(B_Display_STATISTICS)
		//GUI_Write_Chars(50,20,R_STATISTICS_ON_char,ZT9,Background,Colour);
//	else
		//GUI_Write_Chars(47,20,R_STATISTICS_OFF_char,ZT9,Background,Colour);
}
void	Print_SpeedBrake(void)//打印超速保护开关
{
	Color_TypeDef	Background,Colour;
	if(R_STATISTICS_cursor==6)
	{
		Background=d_Bright_Color;
		Colour=d_Clean_Color;
	}
	else
	{
		Background=d_Clean_Color;
		Colour=d_Bright_Color;
	}
	//GUI_Write_block(71,23,87,30,Background);
//	if(B_SpeedBrake)
		//GUI_Write_Chars(73,31,R_STATISTICS_ON_char,ZT9,Background,Colour);
//	else
		//GUI_Write_Chars(71,31,R_STATISTICS_OFF_char,ZT9,Background,Colour);
}

void	STATISTICS_windows(void)
{
	Clear_screen();
	if(R_STATISTICS_cursor<=d_STATISTICS_lowerPAGE)
	{
		//GUI_Write_Chars(1,9,"PUFF:",ZT9,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Chars(1,20,"TIMER:",ZT9,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Chars(1,31,"LIMITED PUFF:",ZT9,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Bitmap(80,4,Dustbin_LOGO,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Bitmap(92,12,STATISTICS_lowerPAGE_LOGO,d_Clean_Color,d_Bright_Color);
		Print_cursor();
		Print_PUFF_Data();
		Print_TIM_Data();
		Print_LIMIT_PUFF_Data();
	}
	else
	{
		//GUI_Write_Chars(7,9,"FullBattClear:",ZT9,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Chars(7,20,"Display:",ZT9,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Chars(7,31,"SpeedBrake:",ZT9,d_Clean_Color,d_Bright_Color);
		//GUI_Write_Bitmap(0,12,STATISTICS_upperPAGE_LOGO,d_Clean_Color,d_Bright_Color);
		Print_cursor();
		Print_FullBattClear();
		Print_Display_STATISTICS();
		Print_SpeedBrake();
	}
}

void	Display_STATISTICS(void)
{
	u16	a;
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=30;
		Dis_Start_operation();
		R_STATISTICS_cursor_Q=0xFF;
		STATISTICS_windows();
	}
	
	if(R_STATISTICS_cursor<=d_STATISTICS_lowerPAGE)
	{
		a=KEY_R_ADD_SUB(R_STATISTICS_cursor,R_KEY_DOWN,R_KEY_UP,d_STATISTICS_lowerPAGE,0,1,1,100);
	}
	else
	{
		a=KEY_R_ADD_SUB(R_STATISTICS_cursor,R_KEY_DOWN,R_KEY_UP,d_STATISTICS_cursorMAX,d_STATISTICS_upperPAGE,1,1,100);
	}
	if(R_STATISTICS_cursor!=a)
	{
		R_STATISTICS_cursor=a;
		Print_cursor();
	}

	if(R_key_anxia==KEY_M)
	{
		if(R_STATISTICS_cursor==0)
		{
			if(R_Statistics_number!=0 || R_Statistics_lengthTim!=0)
			{
				Clear_numberANDlengthTim();
				Print_PUFF_Data();
				Print_TIM_Data();
			}
		}
		else	if(R_STATISTICS_cursor==2)
		{
			R_STATISTICS_cursor=4;
			STATISTICS_windows();
		}
		else	if(R_STATISTICS_cursor==3)
		{
			R_STATISTICS_cursor=0;
			STATISTICS_windows();
		}
		else	if(R_STATISTICS_cursor==4)
		{
			B_FullBattClear=!B_FullBattClear;
			Print_FullBattClear();
		}
		else	if(R_STATISTICS_cursor==5)
		{
			B_Display_STATISTICS=!B_Display_STATISTICS;
			Print_Display_STATISTICS();
		}
		else	if(R_STATISTICS_cursor==6)
		{
			B_SpeedBrake=!B_SpeedBrake;
			Print_SpeedBrake();
		}
	}
	if(R_STATISTICS_cursor==1)
	{
		if(R_key_anxia==KEY_ADD && R_Set_number>=d_Set_number_MAX)
		{
			a=0;
		}
		else if(R_key_anxia==KEY_SUB && R_Set_number==0)
		{
			a=d_Set_number_MAX;
		}
		else
		{
			a=KEY_R_ADD_SUB(R_Set_number,KEY_ADD,KEY_SUB,d_Set_number_MAX,0,1,0,10);
		}
		if(R_Set_number!=a)
		{
			R_Set_number=a;
			Print_LIMIT_PUFF_Data();
		}
	}
	if(R_key_keep==KEY_W_T)
	{
		R_DisStatus=Dis_The_Work;
	}
}

//吸烟口数限制警告界面
void	Display_limit_number(void)
{
	static	uc8	R_Over_smok_CH[]={64,16,0x00,0x00,0x04,0x04,0x00,0x00,0x08,0x20,0x7B,0xF8,0x24,0x04,0x00,0x00,0x49,0x20,
0x4A,0x08,0x24,0x04,0x3F,0xF8,0x2A,0x20,0x52,0x08,0x3F,0xA4,0x20,0x08,0x08,0x3E,
0x53,0xF8,0x44,0x24,0x20,0x08,0xFF,0x44,0x62,0x08,0x04,0x24,0x20,0x08,0x2A,0x44,
0x52,0x08,0xFF,0xE4,0x20,0x08,0x49,0x44,0x4B,0xF8,0x04,0x24,0x20,0x08,0x88,0xA4,
0x4A,0x44,0x04,0x24,0x20,0x08,0x10,0x28,0x4A,0x48,0x3F,0xA4,0x20,0x08,0xFE,0x28,
0x6A,0x30,0x24,0xA4,0x20,0x08,0x22,0x10,0x52,0x20,0x24,0xA4,0x20,0x08,0x42,0x10,
0x42,0x10,0x26,0x84,0x20,0x08,0x64,0x28,0x42,0x88,0x25,0x04,0x3F,0xF8,0x18,0x28,
0x43,0x06,0x04,0x14,0x20,0x08,0x34,0x44,0x42,0x00,0x04,0x08,0x00,0x00,0xC2,0x82};
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		{
			if(R_Language==English)
			{
				//GUI_Write_Chars(3,15,"LIMITED PUFF:",ZT14,d_Clean_Color,d_Bright_Color);
				//GUI_Write_data(42,30,0,R_Set_number,ZT14,d_Clean_Color,d_Bright_Color);
			}
			else
			{
				//口数限制
				//GUI_Write_Bitmap(10,8,R_Over_smok_CH,d_Clean_Color,d_Bright_Color);
				//GUI_Write_data(78,22,0,R_Set_number,ZT14,d_Clean_Color,d_Bright_Color);
			}
		}
		R_Win_tim=300;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
}

//吸烟超速警告
void	Display_SpeedBrake(void)
{
	static	uc8	R_You_should_relax_CH[]={79,15,0x08,0x80,0x00,0x80,0x08,0x40,0x01,0x00,0x00,0x00,0x08,0x80,0x40,0x40,0x08,0x40,
0x02,0x00,0xFF,0xFE,0x08,0x80,0x2F,0xFE,0x08,0x40,0x1F,0xF0,0x02,0x00,0x11,0xFE,
0x20,0x80,0x10,0x40,0x10,0x10,0x02,0x00,0x11,0x02,0x01,0x10,0x17,0xFE,0x1F,0xF0,
0x02,0x00,0x32,0x04,0x01,0x10,0x30,0x40,0x10,0x10,0x02,0x00,0x34,0x20,0xE2,0x24,
0x30,0xE0,0x1F,0xF0,0x02,0x40,0x50,0x20,0x27,0xE4,0x50,0xE0,0x10,0x10,0x02,0x20,
0x91,0x28,0x20,0x48,0x91,0x50,0x1F,0xF0,0x02,0x10,0x11,0x24,0x20,0x88,0x11,0x50,
0x10,0x10,0x02,0x08,0x12,0x24,0x21,0x10,0x12,0x48,0x01,0x00,0x02,0x08,0x12,0x22,
0x2A,0x20,0x14,0x44,0x08,0x84,0x02,0x00,0x14,0x22,0x34,0x50,0x18,0x42,0x48,0x92,
0x02,0x00,0x10,0xA0,0x20,0x88,0x10,0x40,0x48,0x12,0x02,0x00,0x10,0x40,0x03,0x04,
0x10,0x40,0x87,0xF0,0x02,0x00};
	if(R_DisStatus_Q != R_DisStatus)
	{
		R_Window_Tim_MAX=10;
		Dis_Start_operation();
		{
			if(R_Language==English)
			{
				//GUI_Write_Chars(11,15,"You should",ZT14,d_Clean_Color,d_Bright_Color);
				//GUI_Write_Chars(11,29,"relax",ZT14,d_Clean_Color,d_Bright_Color);
			}
			else
			{
				//你该休息下
				//GUI_Write_Bitmap(10,9,R_You_should_relax_CH,d_Clean_Color,d_Bright_Color);
			}
		}
		R_Win_tim=500;
	}
	if(!R_Win_tim)
	{
		R_DisStatus=Dis_The_Work;
	}
	if(!B_SpeedBrake)
	{
		if(R_key_anxia)
			R_DisStatus=Dis_The_Work;
	}
	KEY_Warning_Disp();
}

//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void Display_Refresh(void)
{
	if(B_Display_Detect)
	{
		B_Display_Detect=0;
		
		if(!B_BAT_error)
		{
			if(R_key_anxia)
			{
				R_Window_keep_TimS=R_Window_Tim_MAX;
			}
			
			if(!R_Window_keep_TimS)
			{
				if(B_BAT_Charge)
				{
					R_DisStatus=Dis_Charging;
					if(B_OLED_BL && B_BAT_Congman)
					{
						Disp_OFF();
						B_Switch_BLON=1;
					}
					else	if(!B_OLED_BL && !B_BAT_Congman)
					{
						Disp_ON();
//						if(B_ON_DISP_BL)
//						{
//							B_ON_DISP_BL=0;
//							New_DisStatus();
//						}
					}
				}
				else if(B_OLED_BL)
				{
					Disp_OFF();
					B_Switch_BLON=1;
				}
			}
			else
			{
				if(!B_OLED_BL && (!B_Display_Power_OFF && R_DisStatus!=Dis_S_Smoke || B_BAT_Charge))
				{
					if(B_ON_DISP_BL)
					{
						B_ON_DISP_BL=0;
						New_DisStatus();
					}
					Disp_ON();
					R_key_anxia=0;
					R_key_Open=0;
					R_key_keep=0;
					R_key_1C=0;
					R_key_3C=0;
					R_key_5C=0;
					R_key_anzhu=0;
				}
			}
		}
		
		
		switch(R_DisStatus)
		{
			case	Dis_The_Work:								Display_The_Work();					KEY_Work_Disp();			break;
			case	Dis_Power_OFF:							Display_Power_OFF();				KEY_Power_OFF_Disp();	break;
			case	Dis_Shuoji:									Display_Shuoji();						KEY_Shuoji_Disp();		break;
			case	Dis_Jiesuo:									Display_Unlock();						KEY_Unlock_Disp();		break;
			case	Dis_Locked:									Display_Lock();							KEY_Lock_Disp();			break;
			case	Dis_Old_password:						Display_Change_password_One();		KEY_Old_password_Disp();	break;
			case	Dis_New_password:						Display_Change_password_Two();		KEY_New_password_Disp();	break;
			case	Dis_Charging:								Display_BAT_Charging();			KEY_BAT_Charging_Disp();	break;

			case	Dis_Change_LOGO:						Display_Change_LOGO();			KEY_Change_LOGO_Disp();		break;
			case	Dis_TCR_adjust:							Display_TCR_adjust();				KEY_TCR_adjust_Disp();		break;
			case	Dis_Custom_adjust:					Display_Custom_adjust();		KEY_Custom_adjust_Disp();	break;
			
			case	Dis_Short_Circuit:					Display_Short_Circuit();		KEY_Warning_Disp();		break;
			case	Dis_Open_Circuit:						Display_Open_Circuit();			KEY_Warning_Disp();		break;
			case	Dis_Low_Battery:						Display_Low_battery();			KEY_Warning_Disp();		break;
			case	Dis_Time_Out:								Display_Timeout_Circuit();	KEY_Warning_Disp();		break;
			case	Dis_Temperature:						Display_High_Temperature();	KEY_Warning_Disp();		break;
			case	Dis_Empty_battery:					Display_Empty_battery();		break;
			case	Dis_limit_number:						Display_limit_number();			KEY_Warning_Disp();		break;
			case	Dis_SpeedBrake:							Display_SpeedBrake();break;
			
			case	Dis_Language:								Display_Language_asked();		KEY_Language_Disp();		break;
			case	Dis_Atomizer_replace:				Display_Atomizer_replace();	KEY_Atomizer_replace_Disp();	break;
			case	Dis_LOW_USB:								Display_LOW_USB();					KEY_Warning_Disp();		break;
		
			case	Dis_S_Smoke:								Display_pintfOFF();					KEY_S_Smoke_Disp();		break;
		
			case	Dis_Screen_setting:					Display_Screen_setting();		KEY_Screen_setting();		break;
			case	Dis_menu:										Disp_menu();								KEY_menu();							break;
			case	Dis_Software_version:				Software_version();					break;
							
//			case	Dis_Operation_mode:					Display_Operation();				KEY_Operation();				break;
			case	Dis_Firmware_data:					Display_Firmware_data();			KEY_Firmware_Disp();		break;
			case	Dis_STATISTICS:							Display_STATISTICS();break;
		}	
		if(B_Shuoji)
		{
			if(!B_BAT_error && R_DisStatus!=Dis_Power_OFF && R_DisStatus!=Dis_Jiesuo && R_DisStatus!=Dis_Charging && R_DisStatus!=Dis_Empty_battery  && R_DisStatus!=Dis_LOW_USB)
			{
				R_DisStatus=Dis_Shuoji;
			}
		}
		else
		{
			if(R_DisStatus==R_DisStatus_Q)
			{
				if(B_Atomizer_inquiry==1 || B_Atomizer_inquiry==4)
				{
					if((R_DisStatus==Dis_The_Work || R_DisStatus==Dis_S_Smoke) &&(R_Work_mode==d_Temp_mode || R_Work_mode==d_TCR_mode))
					{
						R_DisStatus=Dis_Atomizer_replace;
						if(B_Atomizer_inquiry==1)
							B_Atomizer_inquiry=2;
						else
							B_Atomizer_inquiry=3;
					}
				}
				else 
				{
					if(B_Atomizer_inquiry==0)
					{
						if((R_DisStatus&0x0F)==0x0A)
						{
							R_DisStatus=Dis_The_Work;
						}
					}
				}
			}
		}
//		
		R_key_anxia=0;
		R_key_Open=0;
		R_key_keep=0;
		R_key_1C=0;
		R_key_3C=0;
		R_key_5C=0;
		R_key_anzhu=0;
	}
	
	Key_Screen();
}

void	New_DisStatus(void)
{
	if(R_DisStatus!=R_DisStatus_S)
	{
		R_DisStatus_Q=R_DisStatus_S;
	}
	else
	{
		R_DisStatus_Q=Dis_Status_NOP;
	}
}

void	New_DisStatus_S(void)
{
	if(R_DisStatus_Q==Dis_Status_NOP)
	{
		R_DisStatus_S=R_DisStatus;
	}
	else
	{
		R_DisStatus_S=R_DisStatus_Q;
	}
}



//////////////////////////////屏幕调节
void	Key_Screen(void)
{
	if(B_OLED_BL)
	{
		if(R_DisStatus==Dis_Charging)
		{
			if(Flagzhenf_Change_Set!=d_Change)
			{
				Flagzhenf_Change_Set=d_Change;
//				Disp_180();
			}
		}
		else
		{
			if(R_Screen_FLIP==0)
			{
				#ifdef	Gyroscope_ENABLE
					MCU_I2CDataOutRead();
				#endif
			}
			else	if(R_Screen_FLIP==1 && Flagzhenf_Change_Set!=d_Flag)
			{
				Flagzhenf_Change_Set=d_Flag;
//				Disp_180();
				R_KEY_UP=KEY_T;
				R_KEY_DOWN=KEY_W;
			}
			else	if(R_Screen_FLIP==2 && Flagzhenf_Change_Set!=d_Change)
			{
				Flagzhenf_Change_Set=d_Change;
//				Disp_180();
				R_KEY_UP=KEY_W;
				R_KEY_DOWN=KEY_T;
			}
			
			if(R_Screen_Light*20+1 != R_OLED_Light)
			{
				R_OLED_Light=R_Screen_Light*20+1;
				Write_DisContrast(R_OLED_Light);
				//Write_Command(0xdb); /*set vcomh*/
				//Write_Command(R_OLED_Light/5);//40
			}
		}
	}
}



