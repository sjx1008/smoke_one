

#ifndef __RTC_SET_INTERFACE_H__
#define __RTC_SET_INTERFACE_H__

typedef enum
{
	ON_Dial,
	OFF_Dial
}Dial_typ;
extern	u8	AMPM_EN;
extern	Dial_typ	R_Dial;		//时钟界面表盘类型
extern	void	RTC_Set_interface(void);
#endif



