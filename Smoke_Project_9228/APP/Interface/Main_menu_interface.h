#ifndef __MAIN_MENU_INTERFACE_H__
#define __MAIN_MENU_INTERFACE_H__


//菜单LOGO
extern	u8	Watt_Menu_I;
extern	u8	Temp_Menu_I;
extern	u8	CC_Menu_I;

extern	uc32	Menu_Cursor_Colour[];
extern	void	Main_menu_interface(void);
extern	void	Menu_Bottom_Windows(char	*p,u8	x);
//显示返回按钮	B:(0：未选中	1：选中)
extern	void	Disp_EXIT_Key(char	*c,u8	B);

//////////////////////////////////////////
//图标菜单
extern	u8	R_Menu_SUM;
extern	u32	*P_Menu_LOGO;
extern	uc8	(*P_CursorXY)[2];
extern	u8	*P_Cursor;
extern	u8	*P_Cursor_Q;


//选中光标
extern	void	Selected_Cursor(u8 I,u8	B);
//初始化菜单页面
extern	void	Menu_Page_Init(void);
//
extern	void	KEY_Main_menu_operation(void);


#endif




