#ifndef __MODE_SELECTION_INTERFACE_H__
#define __MODE_SELECTION_INTERFACE_H__
#include "WM_Disp.h"

/*�����μ��˵��ṹ��---------------------*/
#define	Disp_menu_struct_MAX	5
typedef struct
{
	u8	Max;			//�˵�����
	u8	Sign[Disp_menu_struct_MAX];	//���λ���Ƿ���Ч
	u8	*Cursor;	//��ǰ���λ��
	char	**P_Name;	//�˵�����BUFF
	char	*menuName;	//�˵�
	GUI_CONST_STORAGE GUI_FONT *const	*menuFONT;	//�˵��õ�������
	const	GUI_RECT *NameRECT;
}Disp_menu_struct;

extern	Disp_menu_struct	R_Disp_menu_struct;
extern	void	menu2_struct_Init(char	*menuName,char	**P_Name,u8	Max,u8	*Cursor,u8	yuyan);
extern	void	Disp_menu2_Name(void);
extern	void	menu2_display_windows(void);



extern	void	Mode_selection_interface(void);
extern	void	TEMPE_Mode_selection_interface(void);
extern	void	Custom_Mode_selection_interface(void);
extern	void	Reverse_display_TEMPE_Name(u8	i,u8	B);
extern	void	Reverse_display_Custom_Name(u8	i,u8	B);
//extern	void	Clear_TEMPE_Cursor(void);
//extern	u8	Get_TEMPE_Cursor(void);
//extern	void	TEMPE_Mode_selection_touch(void	(*program)(void),void	(*Fanhui_program)(void));
//extern	void	TEMPE_Mode_selection_Windows(void);
//extern	void	Custom_Mode_selection_Windows(void);
//extern	void	Custom_Mode_selection_touch(void	(*program)(void),void	(*Fanhui_program)(void));




#endif


