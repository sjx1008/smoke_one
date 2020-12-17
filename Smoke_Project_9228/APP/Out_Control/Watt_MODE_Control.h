#ifndef __WATT_MODE_CONTROL_H__
#define __WATT_MODE_CONTROL_H__

#include "main.h"

//用户设定值
extern	u8	B_SMART_mode;
extern	u16	R_User_Watt_Set;				//设定瓦数				//100mW			00.0
extern	void	Watt_mode_int(void);


typedef enum
{
	SOFT_Strength=0,		//柔和输出
	NOR_Strength,			//正常强度
	HIGH_Strength,			//暴力输出
	NOP_Strength,			//
}Watt_Strength;
extern	Watt_Strength		R_Watt_Strength;

#endif
