#ifndef __STATISTICS_PORT_NUMBER_H__
#define __STATISTICS_PORT_NUMBER_H__


#define	d_Statistics_number_MAX				99999			//���ͳ�ƿ���
extern	u16	R_Statistics_number_Set;	//�������̿���
extern	u32	R_Statistics_number;			//ͳ�ƿ���
extern	u32	R_Vape_Time_number;			//ͳ��������ʱ��

//ͳ�����̿���������ʱ��
//��ڲ�����
extern	void	Statistics_numberANDlengthTim(u8	R_tim_s);
//������̿���������ʱ��
extern	void	Clear_numberANDlengthTim(void);
extern	u8	Judge_Vape_plan(void);
#endif


