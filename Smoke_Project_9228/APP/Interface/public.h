
#ifndef __PUBLIC_H__
#define __PUBLIC_H__
#define	d_OK_stop_Tim	5
extern	u8 B_disp_prompt;
extern	u8	B_Mode_selection_EN;
extern  u8  kuaijie_fuwei_bz ;

extern	u8	ADDSUB_LOCK_GOTO(u8 B);
extern	u8	Main_menu_GOTO(void);
//extern	void	Return_interface_GOTO(void (*R)(void));
extern	u8	Atomizer_inquiry_GOTO(u8	B);
extern	u8	GOTO_Screensaver_interface(u8	B);

extern	u8	Batt_error_GOTO(void);
extern	void	Screen_smoking_GOTO(void);
//extern	u8	Locked_Click_GOTO(void);
extern	u8	B_Smoking_KEY_anxia;
extern	void	Smoking_KEY_anxia_JC(void);
extern	void	Key_smoke(void);
extern	void	Fanhui_Main_interface(void);

//extern	void	Automatic_rotating_screen(void);
extern	void	System_off_GOTO(void);
extern	u8	Screen_GOTO_charging(void);


extern  u8  kuaijie_banben_bz;
extern  u8	Firmware_Tim_GOTO(void);
extern  u8   fuwei_Tim_GOTO(void);

////////////////
//extern	u8	Satisfy_Gesture_Press(s16	xs,s16 ys,s16 xz,s16 yz);

#endif

