#ifndef __TEMPE_MODE_CONTROL_H__
#define __TEMPE_MODE_CONTROL_H__

#include "main.h"

//用户设定值
extern	u16	R_User_Temp_Set_C;			//设定摄氏度			//1摄氏度	 	000
extern	u16	R_User_Temp_Set_F;			//设定华氏度			//1华氏度		000

//extern	u16	R_User_Temp_Watt_Max;


extern	void	Temp_mode_int(void);
extern	void	TCR_mode_int(void);
//温度补偿计算
extern	void Tempe_Compensation_calculation(void);
#endif



