#ifndef __OUT_PUBLIC_H__
#define __OUT_PUBLIC_H__

#include	"main.h"
#include "WM_Disp.h"

extern 	u8	R_Smoke_Tim; 		//���̼�ʱ			//100ms		00.0
extern 	u8	B_load_OK;					///������
extern 	u8	B_yule;						///Ԥ��

////////�������������� �Ŵ�100��
extern 	u16	R_PowerMAX;				//10mW	00.00
////////��������������	�Ŵ�100��
extern 	u16	R_PowerMAXMAX;		//10mW	00.00
////////�¿�����������	�Ŵ�100��
extern 	u16	R_Temp_PowerMAX;	//10mW	00.00

extern 	u16	R_Out_W_Set;				///���W��		00.00
extern 	u16	R_Out_V_Set;				///���V		0.00
extern 	u16	R_Out_Temp_Set;			///����¶�	000

extern 	u16	R_Res_Actual;				//ƽ����ֵ		0.000
extern 	u16	R_Out_I_Actual;			//ƽ������		0.00
extern 	u16	R_Out_V_Actual;			//ƽ����ѹ		0.00
extern 	u16	R_Out_W_Actual;			//ƽ������		0.00
extern 	u16	R_Out_TempC_Actual;	//ƽ���¶�		000
extern 	u16	R_Out_TempF_Actual;	//ƽ���¶�		000

extern 	u16	R_real_Temp;				///ʵʱ�¶�		//000
extern 	u16	R_real_BAT;					///ʵʱ��ص�ѹ	0.00
extern 	u16	R_real_WOUT;				///ʵʱ�������	0.00
extern 	u16	R_real_VOUT;				///ʵʱ�����ѹ	0.00
extern 	u16	R_real_IOUT;				///ʵʱ�������	0.00
extern 	u16	R_real_Res;					///ʵʱ����			0.000

extern 	u8	R_Lbat_LB;					///�͵����˲�

extern 	u16	R_T_Gradient_out;			//�����¶�ϵ��_out
extern 	u8	R_Efficiency;					//ת��Ч��

extern 	u8	R_Temp_compensate;			//�¶Ȳ���ֵ
extern 	u8	R_Temp_compensate_MAX;	//�¶Ȳ������ֵ

extern 	void	(*Output_control_program)(void);	//������Ƴ���
extern 	void	PID_init(void);
extern 	void	PID_realize(u16 speed , u16 Aspeed);
extern 	void	Fault_handling(Skinning_mode	R);

///ͳ��ƽ�������ѹ��������
extern 	void	F_Average_Vout(void);
///ͳ��ƽ���¶�
extern 	void	F_Average_Temp(void);
////////////////�����������
extern 	void	Count_Wout(void);
///////////��ѹ����
extern 	void	Vout_adjust(u8	bu);
///////////��������
extern 	void	Wout_adjust(u8	bu);
////////////////������
extern 	u8	Power_down_control(void);

#endif




