#ifndef __BRIGHTNESS_AUTO_H__
#define __BRIGHTNESS_AUTO_H__
#include "main.h"

//读取ADC间隔时间
extern	u8	R_LUX_ADC_Tim;
extern	u8	Bring_AUTO_Enable;
//自动调节亮度重新初始化
extern	void	Bring_AUTO_Init(void);
extern	void	Bring_AUTO_Testing(void);
//打开自动亮度调节
extern	void	Bring_AUTO_EN(void);
//返回当前亮度值对应的等级
extern	void	Set_Ret_Bring_VIP(void);

#endif









