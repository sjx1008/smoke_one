#ifndef __TFT_DRIVE_H__
#define __TFT_DRIVE_H__
#include "main.h"


#define		d_TFT_X_Max	240
#define		d_TFT_Y_Max	320

////设置显示窗口
extern 	void LCD_Write_Window(u16 Xstart,u16 Ystart);
////设置显示窗口
extern 	void LCD_Read_Window(u16 Xstart,u16 Ystart);
//打点函数
extern 	void	GUI_Write_Dot(s16		Xs,s16	Ys,u16	Color);
//读点的颜色
extern 	u16	GUI_Read_Dot(s16		Xs,s16	Ys);
//读点的颜色BUFF
extern 	void	GUI_Read_BUFF_Dot(u16* BUFF,s16		Xs,s16	Ys,s16	Xz,s16	Yz);
//写颜色块
extern 	void	GUI_Write_block(s16	Xs,s16	Ys,s16	Xz,s16	Yz,	u16		Color);
//写区域
extern 	void	GUI_Write_Area(int x0, int y0, int x1, int y1, u16 *buf, uint8_t reverse);

#endif
