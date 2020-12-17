
#ifndef __KEY_LED_H__
#define __VIBRATE_H__

#define	d_KEY_LED_Max		3
extern	u8	R_Set_KEY_LED_Brig;		//设置按键灯亮度等级
extern	void	KEY_LED_drive(void);

extern	void	LOGO_LED_drive(void);
extern	void	LOGO_LED_Control(void);


extern	u16	KEY_LED_Tim;					//按键灯亮的时间
extern	void	LED_drive(void);
#endif


