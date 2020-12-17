#ifndef __APP_Atomizer_H
#define __APP_Atomizer_H

#include	"main.h"

extern	u16	R_Res_Initial;						//初始阻值
extern	u16	R_Res_Initial_Q;					//上一致初始阻值
extern	u16	R_Res_Initial_jiyi;			//记忆阻值
extern	u16	R_Res_average;									//平均阻值
extern	u16	R_Res_Sleep;										//进入休眠前的平均电阻

extern	u8	B_LOCK_Res;								//阻值锁定标志
extern	u8	B_JC_Atomizer;							//启动电阻检测标志
extern 	u8	B_have_Atomizer;						//是否接入雾化器
extern	u8	B_Atomizer_inquiry;					//是否询问雾化器
extern	u8	B_Again_Read;								//新读取
extern 	vu16	R_Read_Rtim;

extern 	u8	B_Sleep_YES;

extern	u16 Read_L_1C(void);
extern	void Read_load(void);
extern	void	Enable_VoutADC_Use(void);
extern	void	Disable_VoutADC_Use(void);


////////////////////////////////////////
	//发热丝加热最大瓦数和变化率结构定义
	typedef struct	Load_Data
	{
		u8		WattsMAX;			//加热最大瓦数放大10倍
		u16		Gradient;			//温度变化率放大1000分之几放大100倍
	}Load_Data;

//NI200发热丝最大输出功率为50.0W，变化率不可调
extern	Load_Data		Load_Ni200;
//Ti发热丝最大输出功率为50.0W，变化率不可调
extern	Load_Data		Load_Ti;
//Ss发热丝最大输出功率为50.0W，变化率不可调
extern	Load_Data		Load_Ss316;
//TCR	M1
extern	Load_Data		Load_M1;
//TCR	M2
extern	Load_Data		Load_M2;
//TCR	M3
extern	Load_Data		Load_M3;

extern	Load_Data	*Atomizer_Pointer[];
extern	Load_Data	*TCR_Pointer[];

#endif


