#ifndef __MAIN_INTERFACE__
#define __MAIN_INTERFACE__
#include "main.h"

#define	d_Auto_Locked_KEY_Tim		100
extern	u8	R_Auto_Locked_KEY;

//extern	u8	R_UI_Theme;

extern	u8	Arc_angle_Time;			//状态切换延时

extern	u8	B_ADDSUB_LOCK;

////////////////////////////////////
extern	const char *const	Atomizer_TC[];
//extern	const char *const	Atomizer_TCR[];
//extern	const char *const	Custom_LO[];
extern	const char	Watt_Strength_LOGO_address[];

extern	u8	B_SET_Key_release;

extern	u8	Return_Smoking_tim;	//退出吸烟计时界面时间

extern	void	Main_interface(void);
extern	void	Screen_smoking_interface(void);

extern	void	Display_BAT(void);
//extern	void	Angle_calculation(u16 *X,u16 *Y,u16	R,u16	A);
extern	void (*Return_windows)(void);
extern	u8	Vape_Arc_Tim;
#endif


