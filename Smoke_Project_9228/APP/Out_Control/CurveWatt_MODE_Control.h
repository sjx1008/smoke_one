#ifndef __CURVEWATT_MODE_CONTROL_H__
#define __CURVEWATT_MODE_CONTROL_H__

#include "main.h"

#define	d_Custom_I_MAX	9

//�û��趨ֵ
extern	u16	*R_Custom_Set;			//ָ���������
extern	u8	R_Custom_I_Set;			//��������ĵ�I����
extern	u8	R_Custom_tim; 			//����֮��ĵ�ʱ���

extern	void	Custom_Output_control(void);

extern	void	Custom_mode_int(void);

extern	void	Custom_CCT_mode_int(void);
extern	void	Custom_CCT_Output_control(void);

#endif
