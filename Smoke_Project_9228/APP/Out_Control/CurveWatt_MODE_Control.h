#ifndef __CURVEWATT_MODE_CONTROL_H__
#define __CURVEWATT_MODE_CONTROL_H__

#include "main.h"

#define	d_Custom_I_MAX	9

//用户设定值
extern	u16	*R_Custom_Set;			//指向输出曲线
extern	u8	R_Custom_I_Set;			//正在输出的第I个点
extern	u8	R_Custom_tim; 			//两点之间的的时间段

extern	void	Custom_Output_control(void);

extern	void	Custom_mode_int(void);

extern	void	Custom_CCT_mode_int(void);
extern	void	Custom_CCT_Output_control(void);

#endif
