
#ifndef __VIBRATE_H__
#define __VIBRATE_H__


//按键按下振子开启时间 ms
#define	d_KEYanxia_Vibrate_Tim	50
//开机开启时间 ms
#define	d_BOOT_Vibrate_Tim	500
//关机开启时间 ms
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


