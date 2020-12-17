#ifndef __APP_display_program_H
#define __APP_display_program_H


#define	d_Bat_Volt_min		285
#define	d_Bat_Volt_max		415

#define	d_DIS_Watt_min		10
#define	d_DIS_Watt_max		800
#define	d_DIS_Watt_max_x10		8000

#define	d_DIS_Vout_min		0
#define	d_DIS_Vout_max		850

#define	d_DIS_Iout_max		26
#define	d_DIS_Iout_max_x100		2600

#define	d_DIS_TempC_min		100
#define	d_DIS_TempC_max		315

#define	d_DIS_TempF_min		200
#define	d_DIS_TempF_max		600


#define	d_Smoke_Tim_max		(R_DISP_DATA.Smoke_Tim_max*10)

extern u8	B_Display_Detect;					///定时刷新屏幕标志
extern u8	B_Smoking_mark;						///吸烟标志
extern u8	B_Smoking_mark_Q;					///吸烟标志
extern u8	B_Power_down;							///降功率
extern u8	B_BAT_Twinkle;						///电池符闪烁
extern u8	B_BAT_Charge;							///充电标志
extern u8	B_BAT_Congman;						///充电充满标志
extern u8	B_BAT_Congman_Q;					///充电充满标志
extern u8	B_BAT_Paoma;							///充电跑马标志
extern u8	B_Shuoji;									///锁机标志
//extern u8	B_Shuoji_Q;								///锁机标志
extern u8	B_Key_Shuo;								///锁机标志
extern u8	B_PowerOFF;								///关机标志

//extern	u8	R_yaoshi_i;							///锁机小图标内的数字
//extern	u8	R_yaoshi_i_Q;							///锁机小图标内的数字
extern	u8	R_Window_keep_TimS;						///窗口维持秒数
extern	u8	R_Window_Tim_MAX;						///窗口维持秒数
extern	u8 *R_ii;
extern	uc8 *R_i2;

extern	u16	R_Win_tim;
///////充电界面参数
//extern	u8	B_Charging_1;


/*************童锁密码*******************/
extern	u8	R_now_password[];		//当前密码
extern	u8	R_input_password[];								//输入密码
extern	u8	R_input_password_x;									//当前输入密码的个数
extern	u8	R_input_password_x_Q;								//上一次输入密码的个数
extern	u8	B_Password_error;								//密码输入错误标志
/*************更改LOGO*******************/
extern	u8	R_input_LOGO[];								//输入LOGO
extern	u8	R_input_LOGO_x;									//当前输入LOGO的个数
extern	u8	R_input_LOGO_x_Q;		//上一次输入LOGO的个数
extern	u8	B_Big_small;									//上一次输入LOGO的个数
/*************TCR调节*******************/
extern	u8	R_TCR_Selected;								//选中的调节项
/**************电压模式下允许的最大输出电压*********************/
extern	u16	R_VoltageMAX;

extern	u8	B_Display_Power_OFF;
extern	u8	B_Display_Power_OFF_Q;

////////////////////屏幕参数设置
extern	u8	R_Screen_FLIP;
extern	u8	R_Screen_Light;

/////界面切换的起始操作
extern	u8	B_ON_DISP_BL;


//extern	u8	R_Operation_mode;

//////显示状态
typedef enum  Displays
{
	/*02*/
	Dis_The_Work	=0x02,			//工作界面
		/*03*/
	Dis_S_Smoke		=0x03,			//灭屏
	/*04*/
	Dis_Power_OFF	=0x04,			//关机
	/*05*/
	Dis_Shuoji		=0x05,			//锁机
	Dis_Jiesuo		=0x15,			//输入密码解锁
	Dis_Locked		=0x25,			//输入密码上锁
	Dis_Old_password		=0x35,			//输入原来密码
	Dis_New_password		=0x45,			//输入新的密码
	/*07*/
	Dis_Charging	=0x07,			//充电
	/*08*/
	Dis_Short_Circuit	=0x08,	//短路
	Dis_Open_Circuit	=0x18,	//断路
	Dis_Low_Battery		=0x28,	//低电量
	Dis_Time_Out			=0x38,	//吸烟超时
	Dis_Temperature		=0x48,	//温度保护
	Dis_Empty_battery	=0x58,	//空电量
	Dis_LOW_USB				=0x68,	//USB电量低
	Dis_SpeedBrake		=0x78,	//超速提示
	Dis_limit_number	=0x88,	//吸烟口数限制提示
	/*09*/
	Dis_Language	=0x09, 			//语言选择
	Dis_Software_version	=0x19,	//软件版本
	Dis_Operation_mode	=0x29,	//操作方式
	/*0A*/
	Dis_Atomizer_replace		=0x0A,		//雾化器更换询问
	/*0B*/
	Dis_TCR_adjust		=0x0B,		//TCR调节
	Dis_Custom_adjust	=0x1B,		//自定义曲线调节
	Dis_Screen_setting	=0x2B,		//屏幕调节
	Dis_menu						=0x3B,		//菜单
	Dis_STATISTICS			=0x4B,		//吸烟统计
	/*0C*/
	Dis_Change_LOGO		=0x0C,		//更改开机LOGO
	Dis_Firmware_data					=0x0D,		//固件信息
	/*0E*/
	
	/*0F*/
	
	/*00*/	
	Dis_Status_NOP	=0x00
}Displays;
extern Displays		R_DisStatus,R_DisStatus_Q,R_DisStatus_S;

//////语言种类
typedef enum  Language
{
	English=0,			//英语
	Chinese,			//中文
	Malaysia,
}Language;
extern Language		R_Language;

////////////工作模式
typedef enum  Work_mode
{
	d_Watt_mode=0,
	d_Bypass_mode,
	d_Temp_mode,
	d_Custom_mode,
	d_Voltage_mode,
	d_TCR_mode,
	d_NOP_mode,
}Work_mode;
extern Work_mode		R_Work_mode,R_Work_mode_Q,R_Work_mode_Set;


////////////雾化器种类
typedef enum  Atomizer
{
	Atomizer_0=0,	//Ss
	Atomizer_1,		//Ni
	Atomizer_2,		//Ti
	Atomizer_3,		//NiCr
	Atomizer_4,
	Atomizer_NC
}Atomizer;
extern Atomizer		R_Atomizer,R_Atomizer_Q,R_Atomizer_Set;

////////////雾化器种类
typedef enum  TCR_term
{
	TCR_0=0,	//M1
	TCR_1,		//M2
	TCR_2,		//M3
	TCR_NC
}TCR_term;
extern TCR_term		R_TCR_term,R_TCR_term_Q,R_TCR_term_Set;


////////////温度单位
typedef enum  Temp_metric
{
	C_metric=0,
	F_metric=1,
	Temp_metric_NC
}Temp_metric;
extern Temp_metric		R_Temp_metric,R_Temp_metric_Q,R_Temp_metric_Set;

/*定义数据属性---------------------*/		
	typedef struct
	{
		u16		BAT_data;			//电池电压放大100倍
		u8		BAT_vip;			//电池等级
		u16		Res_data;			//初始阻值
		u16		Res_Actual;		//实际阻值
		u16		Vout_Set;			//设定输出电压
		u16		Vout_Out;			//实际输出电压
		u16		Temp_Set_C;		//设定摄氏度
		u16		Temp_Out_C;		//输出摄氏度
		u16		Temp_Set_F;		//设定华氏度
		u16		Temp_Out_F;		//输出华氏度
		u16		Watt_Set;			//设定瓦数
		u16		Watt_Out;			//输出瓦数
		u16 	Smoke_data;		//吸烟口数
		u8		Smoke_Tim; 		//吸烟计时
		u8		Smoke_Tim_max; 		//吸烟计时max
	}DATA_Atomizer;
extern DATA_Atomizer		R_DISP_DATA,R_DISP_DATA_Q;
	
//////////////////////////////////////////////
extern	void	Open_Interface(void);
extern	void 	Display_Refresh(void);
extern	void	R_DISP_DATA_Q_DeInit(void);
extern	void	New_DisStatus(void);
extern	void	New_DisStatus_S(void);
extern	void	R_DISP_DATA_Q_DeInit(void);
extern	void	Charging_BAT_windows(void);
	
	
	
//////////////////////////////////
	
extern	void	Display_TCR_adjust(void);
extern	void	Display_Change_LOGO(void);
extern	void	Print_password(u8	*buf,u8	x,u8	B_yingchang);	
		
	//////////////////////////////屏幕调节
extern	void	Key_Screen(void);

extern	u8	B_FullBattClear;				//满电清除吸烟口数标志  	 	0：关闭		1：打开
extern	u8	B_Display_STATISTICS;		//主界面显示统计数据标志   0：关闭		1：打开
extern	u8	B_SpeedBrake;						//吸烟超速保护				  	 	0：关闭		1：打开

#endif

