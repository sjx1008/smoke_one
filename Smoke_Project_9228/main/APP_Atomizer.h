#ifndef __APP_Atomizer_H
#define __APP_Atomizer_H

#include	"main.h"

extern	u16	R_Res_Initial;						//��ʼ��ֵ
extern	u16	R_Res_Initial_Q;					//��һ�³�ʼ��ֵ
extern	u16	R_Res_Initial_jiyi;			//������ֵ
extern	u16	R_Res_average;									//ƽ����ֵ
extern	u16	R_Res_Sleep;										//��������ǰ��ƽ������

extern	u8	B_LOCK_Res;								//��ֵ������־
extern	u8	B_JC_Atomizer;							//�����������־
extern 	u8	B_have_Atomizer;						//�Ƿ��������
extern	u8	B_Atomizer_inquiry;					//�Ƿ�ѯ������
extern	u8	B_Again_Read;								//�¶�ȡ
extern 	vu16	R_Read_Rtim;

extern 	u8	B_Sleep_YES;

extern	u16 Read_L_1C(void);
extern	void Read_load(void);
extern	void	Enable_VoutADC_Use(void);
extern	void	Disable_VoutADC_Use(void);


////////////////////////////////////////
	//����˿������������ͱ仯�ʽṹ����
	typedef struct	Load_Data
	{
		u8		WattsMAX;			//������������Ŵ�10��
		u16		Gradient;			//�¶ȱ仯�ʷŴ�1000��֮���Ŵ�100��
	}Load_Data;

//NI200����˿����������Ϊ50.0W���仯�ʲ��ɵ�
extern	Load_Data		Load_Ni200;
//Ti����˿����������Ϊ50.0W���仯�ʲ��ɵ�
extern	Load_Data		Load_Ti;
//Ss����˿����������Ϊ50.0W���仯�ʲ��ɵ�
extern	Load_Data		Load_Ss316;
//TCR	M1
extern	Load_Data		Load_M1;
//TCR	M2
extern	Load_Data		Load_M2;
//TCR	M3
extern	Load_Data		Load_M3;

extern	Load_Data	*Atomizer_Pointer[];
extern	Load_Data	*TCR_Pointer[];

#endif


