#ifndef __WM_DISP_H__
#define __WM_DISP_H__
#include "main.h"
#include "main_2.h"
#include "GUI.h"
#include "Flahs_Data.h"
//#include "APP_Delay.h"
//#include "OLED_driver.h"
//#include "LED091_Driver.h"
//#include "APP_ChargingBAT.h"
//#include "APP_OutputControl.h"
//#include "APP_Atomizer.h"
//#include "APP_Custom.h"
//#include "sqrt_16.h"
#include "Main interface.h"
#include "TCR_adjust_interface.h"
#include "One_Power_interface.h"
#include "Battery_charging_interface.h"
#include "Atomizer_inquiry_interface.h"
#include "Custom_curve_adjustment_interface.h"
#include "Alarm_interface.h"
#include "VT_MODE_Set_interface.h"
//#include "APP_RTC.h"
#include "System_off_interface.h"
//#include "APP_KEY.h"
#include "public.h"
//#include "APP_Gyroscope.h"
#include "Main_menu_interface.h"
#include "DIY_menu_interface.h"
//#include "Mode_selection_interface.h"
//#include "Data_Adjust_Menu_interface.h"
#include "Lock_Resis_Interface.h"
#include "System_settings_interface.h"
#include "Firmware_Tim_interface.h"
//#include "User adjustment_interface.h"
//#include "Watt_Preheat_Interface.h"
#include "RTC_Set_interface.h"
#include "Screensaver_interface.h"
//#include "Batt_JZ_interface.h"
/////xiugaiguo

//#include "usbd_custom_hid_core.h"
//#include  "usbd_usr.h"
//#include  "APP_USB.h"
//#include "Touch_detection.h"

typedef enum  Skinning_mode
{
	Skinning_init=0,      ///���ڳ�ʼ������
	Atomizer_access,			//��������
	Atomizer_pull_out,		//�����γ�
	USB_access,						//USB����
	USB_pull_out,					//USB�γ�
	Short_circuit,				//��·
	Open_circuit,					//��·
	High_Resistance,			//����ֵ
	Low_Resistance,				//����ֵ
	Low_Battery,					//�͵���
	Smoking_timeout,			//���̳�ʱ
	PCB_Overheated,				//PCB����
	USB_anomaly,					//USB�쳣
	Skinning_mode_null ,   //�޲���
}Skinning_mode;

extern	void (*Disp_windows)(void);				//��ǰ���еĴ��ں���ָ��
extern	void (*Disp_windows_Q)(void);			//��һ�δ��ں���ָ��
extern	void (*Disp_windows_Set)(void);		//���ô��ں���ָ��
extern	void (*Disp_windows_QQ)(void);
extern	u8	B_Skinning_init;
extern	u8	B_windows_GOTO;			//�����һ����ת��־
extern	u8	B_Display_refresh;
extern	Skinning_mode	R_Skinning_mode;
extern	Skinning_mode	R_Skinning_mode2;
extern	u16	R_Interface_maintain_Time;		//����ά��ʱ��
extern	u16	R_Bright_screen_Time;					//����ʱ��
extern	u16	R_Bright_screen_TimeMAX;					//����ʱ��
extern	u16	R_BrightScreen_TimeMAX;

#define	d_BrightScreen_TimeMAX	1200
#define	d_BrightScreen_TimeMIN	50

extern	void	Windows_Switch(void (*R)(void));
extern	void	Windows_Interrupt_Push(void (*R)(void));
extern	void	Interface_display(void);
extern	u8	Key_Light_screen(void);
//////////////////////

//////��������
typedef enum  Language
{
	English=0,			//Ӣ��
	Chinese,			//����
	Malaysia,
}Language;

////////////����ģʽ
typedef enum  Work_mode
{
	d_Watt_mode=0,
	d_Voltage_mode,
	d_Bypass_mode,
	d_Custom_mode,
	d_CustomTemp_mode,
	d_CustomVolt_mode,
	d_Temp_mode,
	d_TCR_mode,
	d_SPP_mode,
	d_NOP_mode,
}Work_mode;


////////////�¶ȵ�λ
typedef enum  Temp_metric
{
	C_metric=0,
	F_metric=1,
	Temp_metric_NC
}Temp_metric;


////////////��������
typedef enum  Atomizer
{
	Ni=0,	//Ss
	Ti,		//Ni
	Ss,		//Ti
	Atomizer_NC
}Atomizer;


////////////��������
typedef enum  TCR_term
{
	M1=0,	//M1
	M2,		//M2
	M3,		//M3
	TCR_NC
}TCR_term;


////////////�Զ�������
typedef enum  Custom_typ
{
	C1=0,	//C1
	C2,		//C2
	C3,		//C3
	Custom_NC
}Custom_typ;

extern 	Language			R_Language;
extern	Work_mode			R_Work_mode;
extern	Temp_metric		R_Temp_metric;
extern	Atomizer			R_Atomizer;
extern	TCR_term			R_TCR_term;
extern	Custom_typ		R_Custom;


typedef enum
{
	d_System_Normal=0,
	d_System_Locked,
	d_System_Off,
}System_enum;


extern	u8	B_System_off;

#endif


