#ifndef __TEMPE_MODE_CONTROL_H__
#define __TEMPE_MODE_CONTROL_H__

#include "main.h"

//�û��趨ֵ
extern	u16	R_User_Temp_Set_C;			//�趨���϶�			//1���϶�	 	000
extern	u16	R_User_Temp_Set_F;			//�趨���϶�			//1���϶�		000

//extern	u16	R_User_Temp_Watt_Max;


extern	void	Temp_mode_int(void);
extern	void	TCR_mode_int(void);
//�¶Ȳ�������
extern	void Tempe_Compensation_calculation(void);
#endif



