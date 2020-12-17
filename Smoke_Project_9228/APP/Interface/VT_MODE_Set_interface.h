
#ifndef __VT_MODE_SET_INTERFACE_H__
#define __VT_MODE_SET_INTERFACE_H__

extern	uc32	*MENU_LOGO_BUFF;
extern	const char *const	*MODE_Name_Buff;
extern	u8	MODE_Name_Page;
extern	uc8	(*MODE_Name_Page_SUB)[2];
extern	s8* R_MENU_Cursor_M;
extern	s8 	R_MENU_Cursor_M_Q;
extern	s8	R_Cursor_SUM;
extern	s8	R_System_set_SUM;
extern	void	Disp_MENU_Name(s8	R,s8	R_Q);

extern	const char	*const	TCR_project_Name[];
extern	void	VT_XX_SET_DISP(void);
extern	void	Set_TCR_project(u8 R,u8	d,void (*S)(void));
extern	void	VT_MODE_Set_interface(void);

#endif



