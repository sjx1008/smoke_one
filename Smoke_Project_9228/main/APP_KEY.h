#ifndef __APP_KEY_H
#define __APP_KEY_H

#include "main.h"

	#define KEY_1_PIN               LL_GPIO_PIN_12
	#define KEY_1_GPIO_PORT         GPIOC
		#define KEY_1_RinBit					LL_GPIO_IsInputPinSet(KEY_1_GPIO_PORT, KEY_1_PIN)
	#define KEY_2_PIN               LL_GPIO_PIN_15
	#define KEY_2_GPIO_PORT         GPIOA
		#define KEY_2_RinBit					LL_GPIO_IsInputPinSet(KEY_2_GPIO_PORT, KEY_2_PIN)
	#define KEY_3_PIN               LL_GPIO_PIN_10
	#define KEY_3_GPIO_PORT         GPIOC
		#define KEY_3_RinBit					LL_GPIO_IsInputPinSet(KEY_3_GPIO_PORT, KEY_3_PIN)
	#define KEY_4_PIN               LL_GPIO_PIN_11
	#define KEY_4_GPIO_PORT         GPIOC
		#define KEY_4_RinBit					LL_GPIO_IsInputPinSet(KEY_4_GPIO_PORT, KEY_4_PIN)

	#define USB_T_PIN               LL_GPIO_PIN_7
	#define USB_T_GPIO_PORT         GPIOA
	#define USB_T_AIN               LL_ADC_CHANNEL_7
		#define USB_T_RinBit					LL_GPIO_IsInputPinSet(USB_T_GPIO_PORT, USB_T_PIN)
////////////////////////////////////////////////////////////////

extern	u8	B_KEY_JC;		//按键检测标志位
extern	u8	R_KEY_timMax;
extern	vu8	R_KEY_timi;
extern	u8	Key_LB_value;	//濠娿倖灏濋崥搴ｆ畱缂佹挻鐏?

extern	u8	R_key_anxia;
extern	u8	R_key_Open;
extern	u8	R_key_anxiaOpen;	//短按松开
extern	u8	R_key_anzhuOpen;	//长按松开
extern	u8	R_key_keep;
extern	u8	R_key_super_keep;
extern	u8	R_key_1C;
extern	u8	R_key_3C;				//按键3次
extern	u8	R_key_5C;
extern	u8	R_key_XC;
extern	u8	R_key_XC_Data;
extern	u8	R_key_anzhu;
extern	u8   key_value;//当前按键值寄存器
extern	u8	B_Key_Clean_xC;
extern	u8	B_Key_release;

extern	u8	R_key_super_keep_Mode;
extern	u8	R_key_3C_Mode;
extern	u8	R_key_anzhuOpen_Mode;
extern	u8	R_key_XC_Data_Mode;
extern	u8	R_key_XC_Mode;
extern	u8	R_key_anxia_Mode;
extern	u8	R_key_anxiaOpen_Mode;
extern	u8	B_USB_RinBit;
extern	u8	B_USB_Low;

extern	u8	B_testing_IC;
extern	u16	R_testing_IC_Tim;

extern	u8	B_InterfaceGOTO;


//////////////////////////////////////////


//////////////////////////////////////////

/////按键脚
typedef enum  KEY_bit
{
	KEY_M=0x01,
	KEY_ADD=0x08,
	KEY_SUB=0x02,
	KEY_MODE=0x04,
	KEY_M_ADD=0x09,
	KEY_M_SUB=0x03,
	KEY_ADD_SUB=0x0A,
	KEY_M_MODE=0x05,
	KEY_MODE_ADD=0x0C,
	KEY_MODE_SUB=0x06,
	KEY_MODE_SUB_ADD=0x0E,
	KEY_NOP=0xFF,
}KEY_bit;

//extern	KEY_bit	R_KEY_UP;
//extern	KEY_bit	R_KEY_DOWN;

extern	void KEY_USB_GPIO_int(void);
extern	void Key_scan(void);
extern	void KEY_ALL_Task(void);
extern	void	KEY_TFT_RESET(void);
extern	u16	KEY_R_ADD_SUB(u8 *KEY,s16	R,u8 KADD,u8 KSUB,s16 max,s16 min,s8 bu,u8 xh,u8 tim);
extern	void	KEY_Filter_processing(void);

#endif



