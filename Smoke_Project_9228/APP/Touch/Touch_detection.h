#ifndef __TOUCH_DETECTION_H__
#define __TOUCH_DETECTION_H__
#include "stm32f0xx.h"
#include "Stdint_2.h"

typedef struct
{
	s16		x;		
	s16 	y;
}Touch_coordinate_struct;		//����
//
typedef enum
{
	Gesture_NOP=0,      			///�޶���
	Gesture_Press,   					///����
	Gesture_Short_Release,   	///�̰��ɿ�
	Gesture_Long_Press,   		///����
	Gesture_Long_Release,   	///�����ɿ�
	Gesture_Release,   				///�ɿ�
	Gesture_Hold_down,				///��ס
	Gesture_Up_slip,					///�ϻ�
	Gesture_Down_slip,				///�»�
	Gesture_Left_slip,				///��
	Gesture_Right_slip,				///�һ�
	Gesture_Stay_Screen,			///��ָ����Ļ��
	Gesture_Leave_Screen,			///��ָ�Ѿ��뿪��Ļ
}Gesture_enum;
//
typedef struct
{
	Gesture_enum							R_Gesture_mode;			
	Touch_coordinate_struct 	R_Gesture_coordinate_Start;
	Touch_coordinate_struct 	R_Gesture_coordinate_End;
}Touch_struct;

extern	u8	B_Touch_release;
extern	Touch_struct	Touch_events;
extern	Touch_coordinate_struct		Touch_value;		//��ǰ�İ�������ֵ

extern	void Touch_scan(void); 


//////////////////////////////////
extern	u8	R_Button_anxia;
extern	u8	R_Button_Open;
extern	u8	R_Button_anxiaOpen;	//�̰��ɿ�
extern	u8	R_Button_anzhuOpen;	//�����ɿ�
extern	u8	R_Button_keep;
extern	u8	R_Button_anzhu;
extern	u8	R_Button_shanghua;
extern	u8	R_Button_xiahua;
extern	u8	R_Button_zuohua;
extern	u8	R_Button_youhua;
extern	u8	R_Button_3C;
extern	u8	B_Receive_press;	//�ȴ����±�־
extern	void	Get_TP_Button_Key(void);
extern	void	Init_TP_Button_Key(uc8	Button[][4],u8	sum);
extern	void	TP_Button_Key_OFF(void);
extern	u16	TP_R_ADD_SUB(u8 *KEY,s16	R,u8 KADD,u8 KSUB,s16 max,s16 min,s8 bu,u8 xh,u8 tim);

#endif



