
#ifndef __VIBRATE_H__
#define __VIBRATE_H__


//�����������ӿ���ʱ�� ms
#define	d_KEYanxia_Vibrate_Tim	50
//��������ʱ�� ms
#define	d_BOOT_Vibrate_Tim	500
//�ػ�����ʱ�� ms
#define	d_System_OFF_Vibrate_Tim	500

#define	d_Vibrate_Max		10
extern	u8	R_Set_Vibrate;

extern	u8	B_Vibrate_ENABLE;
extern	void	Vibrate_ON(u16	tim,u8	Strength);
extern	void	Vibrate_GPIO_Init(void);
extern	void	Vibrate_drive(void);
extern	void	Vibrate_program(void);
extern	void	Vibrate_EN(u8	B);

#endif


