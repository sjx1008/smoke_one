#ifndef __TFT_DRIVE_H__
#define __TFT_DRIVE_H__
#include "main.h"


#define		d_TFT_X_Max	240
#define		d_TFT_Y_Max	320

////������ʾ����
extern 	void LCD_Write_Window(u16 Xstart,u16 Ystart);
////������ʾ����
extern 	void LCD_Read_Window(u16 Xstart,u16 Ystart);
//��㺯��
extern 	void	GUI_Write_Dot(s16		Xs,s16	Ys,u16	Color);
//�������ɫ
extern 	u16	GUI_Read_Dot(s16		Xs,s16	Ys);
//�������ɫBUFF
extern 	void	GUI_Read_BUFF_Dot(u16* BUFF,s16		Xs,s16	Ys,s16	Xz,s16	Yz);
//д��ɫ��
extern 	void	GUI_Write_block(s16	Xs,s16	Ys,s16	Xz,s16	Yz,	u16		Color);
//д����
extern 	void	GUI_Write_Area(int x0, int y0, int x1, int y1, u16 *buf, uint8_t reverse);

#endif
