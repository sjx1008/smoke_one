
#ifndef		_APP_OutputControl_
#define		_APP_OutputControl_
#include "main.h"
#include "WM_Disp.h"
#include "Watt_MODE_Control.h"
#include "Voltage_MODE_Control.h"
#include "Bypass_MODE_Control.h"
#include "Tempe_MODE_Control.h"
#include "CurveWatt_MODE_Control.h"
#include "CurveCCT_Mode_control.h"
#include "SPP_MODE_Control.h"
#include "CurveCCV_Mode_control.h"

/////�����һЩ��������
//	#define OUT_12V_EN_PIN              GPIO_Pin_0
//	#define OUT_12V_EN_GPIO_PORT        GPIOF
//	#define OUT_12V_EN_GPIO_CLK         RCC_AHBPeriph_GPIOF
//		#define	OUT_12V_EN_ON()			OUT_12V_EN_GPIO_PORT->BSRR = OUT_12V_EN_PIN
//		#define	OUT_12V_EN_OFF()		OUT_12V_EN_GPIO_PORT->BRR = OUT_12V_EN_PIN
//
//	#define OUT_En_DCDC_PIN          	GPIO_Pin_2
//	#define OUT_En_DCDC_GPIO_PORT     GPIOB                          /*  */
//	#define OUT_En_DCDC_GPIO_CLK     	RCC_AHBPeriph_GPIOB
//		#define	OUT_En_DCDC_ON()		OUT_En_DCDC_GPIO_PORT->BSRR = OUT_En_DCDC_PIN;
//		#define	OUT_En_DCDC_OFF()		OUT_En_DCDC_GPIO_PORT->BRR = OUT_En_DCDC_PIN;
//

/////////////////////////////////////////////////////////////

#define	d_Bat_OUT_Volt_min	280
#define	d_Bat_Volt_min		320
#define	d_Bat_Volt_max		420

#define	d_User_Watt_min			50
#define	d_User_Watt_max			2200
#define	d_User_Watt_min_x10	d_User_Watt_min*10
#define	d_User_Watt_max_x10	d_User_Watt_max*10

#define	d_User_Vout_min		0
#define	d_User_Vout_max		900

#define	d_User_Iout_max				47
#define	d_User_Iout_max_x10			d_User_Iout_max*10
#define	d_User_Iout_max_x100		d_User_Iout_max*100

#define	d_User_TempC_min		100
#define	d_User_TempC_max		315

#define	d_User_TempF_min		200
#define	d_User_TempF_max		600

#define	d_Res_min				50
#define	d_Res_usable			5000
#define	d_Res_max				9999


#define	d_OVER_Iout_max				56
#define	d_OVER_Iout_max_x10		d_OVER_Iout_max*10
#define	d_OVER_Iout_max_x100	d_OVER_Iout_max*100

	//�û��趨ֵ
extern	u8	B_AUOT_MODE;				//���ά�����Զ�ģʽ

extern	u8	R_User_Smoke_Tim_max; 	//���̼�ʱmax		//100mS			00.0

extern	u8	R_Smoke_Tim; 		//���̼�ʱ			//100ms		00.0
extern	u16	R_Smoke_Tim10ms; 		//���̼�ʱ			//10ms		00.00

extern	u8	B_Smoking_mark;						///���̱�־
extern	u8	B_Smoking_mark_Q;					///���̱�־

extern	u8	B_Out_Yes;					///���������־
extern	u8	B_Out_JC;						///�����ѹ���
extern	u8	B_load_JC;					///������
extern	u8	B_again;
extern	u8	R_again_Tim;


extern	u16	R_Out_W_Set;				///���W��		00.00
extern	u16	R_Out_V_Set;				///���V		0.00
extern	u16	R_Out_Temp_Set;			///����¶�	000
extern	u8	R_Custom_I_Set;			//��������ĵ�I����
extern	u8	R_Custom_tim; 			//����֮��ĵ�ʱ���

extern	u16	R_Res_Actual;				//ƽ����ֵ		0.00
extern	u16	R_Out_I_Actual;			//ƽ������		0.00
extern	u16	R_Out_V_Actual;			//ƽ����ѹ		0.00
extern	u16	R_Out_W_Actual;			//ƽ������		0.00
extern	u16	R_Out_TempC_Actual;	//ƽ���¶�		000
extern	u16	R_Out_TempF_Actual;	//ƽ���¶�

extern	u16	R_real_Temp;				///ʵʱ�¶�		//000
extern	u16	R_real_BAT;					///ʵʱ��ص�ѹ	0.00
extern	u16	R_real_WOUT;				///ʵʱ�������	0.00
extern	u16	R_real_VOUT;				///ʵʱ�����ѹ	0.00
extern	u16	R_real_IOUT;				///ʵʱ�������	0.00
extern	u16	R_real_Res;					///ʵʱ����			0.000

extern	u16	R_Temp_MAX;	//

extern	u8	R_XY_Tim_yanshi;

extern	void  OutputControlGPIO_int(void);
extern	void	OUT_YES_Control(void);
extern	void	OUTControl_Init(void);
extern	void	OUTControl(void);
////////////////���������ѹ
extern	void	Count_Vout(u16	R);
	////////////////���ϴ���
//extern	void	Fault_handling(Displays	R);
////////////////�¶�������Ƴ���
extern	void	Temp_Output_control(void);
#endif

