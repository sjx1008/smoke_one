#ifndef __WATT_MODE_CONTROL_H__
#define __WATT_MODE_CONTROL_H__

#include "main.h"

//�û��趨ֵ
extern	u8	B_SMART_mode;
extern	u16	R_User_Watt_Set;				//�趨����				//100mW			00.0
extern	void	Watt_mode_int(void);


typedef enum
{
	SOFT_Strength=0,		//������
	NOR_Strength,			//����ǿ��
	HIGH_Strength,			//�������
	NOP_Strength,			//
}Watt_Strength;
extern	Watt_Strength		R_Watt_Strength;

#endif
