#ifndef __CUSTOM_CURVE_ADJUSTMENT_INTERFACE_H__
#define __CUSTOM_CURVE_ADJUSTMENT_INTERFACE_H__

extern	u8	B_Set_OK;
extern	u16	*const CCT_C_BUFF[];
extern	u16	*const CCT_F_BUFF[];
extern	void (*Custom_Data_Return)(void);
extern	u8	R_Custom_SetProject;	//需要设置的项
extern	void	Print_Button_Disp(const char * s,GUI_RECT * pRect,GUI_COLOR	COLOR,	GUI_COLOR	FontCOLOR);
extern	void	Custom_Data_Set_interface(void);
extern	void	CCV_Custom_Data_Set_interface(void);
extern	void	CCT_Custom_Data_Set_interface(void);
#endif


