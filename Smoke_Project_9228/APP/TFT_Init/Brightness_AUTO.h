#ifndef __BRIGHTNESS_AUTO_H__
#define __BRIGHTNESS_AUTO_H__
#include "main.h"

//��ȡADC���ʱ��
extern	u8	R_LUX_ADC_Tim;
extern	u8	Bring_AUTO_Enable;
//�Զ������������³�ʼ��
extern	void	Bring_AUTO_Init(void);
extern	void	Bring_AUTO_Testing(void);
//���Զ����ȵ���
extern	void	Bring_AUTO_EN(void);
//���ص�ǰ����ֵ��Ӧ�ĵȼ�
extern	void	Set_Ret_Bring_VIP(void);

#endif









