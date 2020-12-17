
#ifndef		_APP_OutputControl_
#define		_APP_OutputControl_
#include "main.h"
#include "WM_Disp.h"
#include "Watt_MODE_Control.h"
#include "Voltage_MODE_Control.h"
#include "Bypass_MODE_Control.h"
#include "Tempe_MODE_Control.h"
#include "CurveWatt_MODE_Control.h"
#include "CurveCCT_Mode_control.h"
#include "SPP_MODE_Control.h"
#include "CurveCCV_Mode_control.h"

/////输出的一些控制引脚
//	#define OUT_12V_EN_PIN              GPIO_Pin_0
//	#define OUT_12V_EN_GPIO_PORT        GPIOF
//	#define OUT_12V_EN_GPIO_CLK         RCC_AHBPeriph_GPIOF
//		#define	OUT_12V_EN_ON()			OUT_12V_EN_GPIO_PORT->BSRR = OUT_12V_EN_PIN
//		#define	OUT_12V_EN_OFF()		OUT_12V_EN_GPIO_PORT->BRR = OUT_12V_EN_PIN
//
//	#define OUT_En_DCDC_PIN          	GPIO_Pin_2
//	#define OUT_En_DCDC_GPIO_PORT     GPIOB                          /*  */
//	#define OUT_En_DCDC_GPIO_CLK     	RCC_AHBPeriph_GPIOB
//		#define	OUT_En_DCDC_ON()		OUT_En_DCDC_GPIO_PORT->BSRR = OUT_En_DCDC_PIN;
//		#define	OUT_En_DCDC_OFF()		OUT_En_DCDC_GPIO_PORT->BRR = OUT_En_DCDC_PIN;
//

/////////////////////////////////////////////////////////////

#define	d_Bat_OUT_Volt_min	280
#define	d_Bat_Volt_min		320
#define	d_Bat_Volt_max		420

#define	d_User_Watt_min			50
#define	d_User_Watt_max			2200
#define	d_User_Watt_min_x10	d_User_Watt_min*10
#define	d_User_Watt_max_x10	d_User_Watt_max*10

#define	d_User_Vout_min		0
#define	d_User_Vout_max		900

#define	d_User_Iout_max				47
#define	d_User_Iout_max_x10			d_User_Iout_max*10
#define	d_User_Iout_max_x100		d_User_Iout_max*100

#define	d_User_TempC_min		100
#define	d_User_TempC_max		315

#define	d_User_TempF_min		200
#define	d_User_TempF_max		600

#define	d_Res_min				50
#define	d_Res_usable			5000
#define	d_Res_max				9999


#define	d_OVER_Iout_max				56
#define	d_OVER_Iout_max_x10		d_OVER_Iout_max*10
#define	d_OVER_Iout_max_x100	d_OVER_Iout_max*100

	//用户设定值
extern	u8	B_AUOT_MODE;				//麦克维尔的自动模式

extern	u8	R_User_Smoke_Tim_max; 	//吸烟计时max		//100mS			00.0

extern	u8	R_Smoke_Tim; 		//吸烟计时			//100ms		00.0
extern	u16	R_Smoke_Tim10ms; 		//吸烟计时			//10ms		00.00

extern	u8	B_Smoking_mark;						///吸烟标志
extern	u8	B_Smoking_mark_Q;					///吸烟标志

extern	u8	B_Out_Yes;					///正在输出标志
extern	u8	B_Out_JC;						///输出电压检测
extern	u8	B_load_JC;					///电阻检测
extern	u8	B_again;
extern	u8	R_again_Tim;


extern	u16	R_Out_W_Set;				///输出W数		00.00
extern	u16	R_Out_V_Set;				///输出V		0.00
extern	u16	R_Out_Temp_Set;			///输出温度	000
extern	u8	R_Custom_I_Set;			//正在输出的第I个点
extern	u8	R_Custom_tim; 			//两点之间的的时间段

extern	u16	R_Res_Actual;				//平均阻值		0.00
extern	u16	R_Out_I_Actual;			//平均电流		0.00
extern	u16	R_Out_V_Actual;			//平均电压		0.00
extern	u16	R_Out_W_Actual;			//平均瓦数		0.00
extern	u16	R_Out_TempC_Actual;	//平均温度		000
extern	u16	R_Out_TempF_Actual;	//平均温度

extern	u16	R_real_Temp;				///实时温度		//000
extern	u16	R_real_BAT;					///实时电池电压	0.00
extern	u16	R_real_WOUT;				///实时输出瓦数	0.00
extern	u16	R_real_VOUT;				///实时输出电压	0.00
extern	u16	R_real_IOUT;				///实时输出电流	0.00
extern	u16	R_real_Res;					///实时电阻			0.000

extern	u16	R_Temp_MAX;	//

extern	u8	R_XY_Tim_yanshi;

extern	void  OutputControlGPIO_int(void);
extern	void	OUT_YES_Control(void);
extern	void	OUTControl_Init(void);
extern	void	OUTControl(void);
////////////////计算输出电压
extern	void	Count_Vout(u16	R);
	////////////////故障处理
//extern	void	Fault_handling(Displays	R);
////////////////温度输出控制程序
extern	void	Temp_Output_control(void);
#endif

