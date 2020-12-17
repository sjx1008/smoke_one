#ifndef		_APP_Sleeping_
#define		_APP_Sleeping_
#include	"main.h"

extern 	u8	B_USB_inquiry;
extern 	u16	R_SleepTim;
extern	void (*Disp_Sleep)(void);				//显示进入休眠时的钩子函数
extern	void	Sleeping_Peripheral(void);
extern void	Sleeping_Module(void);
extern void	Disp_Sleep_NOP(void);
#endif


