#ifndef __OUT_PUBLIC_H__
#define __OUT_PUBLIC_H__

#include	"main.h"
#include "WM_Disp.h"

extern 	u8	R_Smoke_Tim; 		//吸烟计时			//100ms		00.0
extern 	u8	B_load_OK;					///电阻检测
extern 	u8	B_yule;						///预热

////////最大允许输出功率 放大100倍
extern 	u16	R_PowerMAX;				//10mW	00.00
////////最大允许输出功率	放大100倍
extern 	u16	R_PowerMAXMAX;		//10mW	00.00
////////温控最大输出功率	放大100倍
extern 	u16	R_Temp_PowerMAX;	//10mW	00.00

extern 	u16	R_Out_W_Set;				///输出W数		00.00
extern 	u16	R_Out_V_Set;				///输出V		0.00
extern 	u16	R_Out_Temp_Set;			///输出温度	000

extern 	u16	R_Res_Actual;				//平均阻值		0.000
extern 	u16	R_Out_I_Actual;			//平均电流		0.00
extern 	u16	R_Out_V_Actual;			//平均电压		0.00
extern 	u16	R_Out_W_Actual;			//平均瓦数		0.00
extern 	u16	R_Out_TempC_Actual;	//平均温度		000
extern 	u16	R_Out_TempF_Actual;	//平均温度		000

extern 	u16	R_real_Temp;				///实时温度		//000
extern 	u16	R_real_BAT;					///实时电池电压	0.00
extern 	u16	R_real_WOUT;				///实时输出瓦数	0.00
extern 	u16	R_real_VOUT;				///实时输出电压	0.00
extern 	u16	R_real_IOUT;				///实时输出电流	0.00
extern 	u16	R_real_Res;					///实时电阻			0.000

extern 	u8	R_Lbat_LB;					///低电量滤波

extern 	u16	R_T_Gradient_out;			//电阻温度系数_out
extern 	u8	R_Efficiency;					//转换效率

extern 	u8	R_Temp_compensate;			//温度补偿值
extern 	u8	R_Temp_compensate_MAX;	//温度补偿最大值

extern 	void	(*Output_control_program)(void);	//输出控制程序
extern 	void	PID_init(void);
extern 	void	PID_realize(u16 speed , u16 Aspeed);
extern 	void	Fault_handling(Skinning_mode	R);

///统计平均输出电压电流功率
extern 	void	F_Average_Vout(void);
///统计平均温度
extern 	void	F_Average_Temp(void);
////////////////更新输出瓦数
extern 	void	Count_Wout(void);
///////////电压调节
extern 	void	Vout_adjust(u8	bu);
///////////瓦数调节
extern 	void	Wout_adjust(u8	bu);
////////////////降功率
extern 	u8	Power_down_control(void);

#endif




