#include	"TFT_Init.h"
#include "Flahs_Driver.h"
#include "TFT_Drive.h"

////设置显示窗口
void LCD_Write_Window(u16 Xstart,u16 Ystart)
{
	LCD_WriteComm(0x2A);
	LCD_WriteData_8bit(Xstart>>8);
	LCD_WriteData_8bit(Xstart&0xFF);

	LCD_WriteComm(0x2B);
	LCD_WriteData_8bit((Ystart+TFT_Y_panyi)>>8);
	LCD_WriteData_8bit((Ystart+TFT_Y_panyi)&0xFF);

	LCD_WriteComm(0x2c);
}

////设置显示窗口
void LCD_Read_Window(u16 Xstart,u16 Ystart)
{
	LCD_WriteComm(0x2A);
	LCD_WriteData_8bit(Xstart>>8);
	LCD_WriteData_8bit(Xstart&0xFF);

	LCD_WriteComm(0x2B);
	LCD_WriteData_8bit((Ystart+TFT_Y_panyi)>>8);
	LCD_WriteData_8bit((Ystart+TFT_Y_panyi)&0xFF);

	LCD_WriteComm(0x2E);
}

//打点函数
void	GUI_Write_Dot(s16		Xs,s16	Ys,u16	Color)
{
	LCD_Write_Window(Xs,Ys);
	LCD_WriteData_16bit(Color);
}

//读点的颜色
u16	GUI_Read_Dot(s16		Xs,s16	Ys)
{
	u16	R;
	LCD_Read_Window(Xs,Ys);
	R=LCD_ReadColor_16bit();
	return	R;
}
//读点的颜色BUFF
void	GUI_Read_BUFF_Dot(u16* BUFF,s16		Xs,s16	Ys,s16	Xz,s16	Yz)
{
	u16	i=0;
	u16	x;
	for(;Ys<=Yz;Ys++)
	{
		LCD_Read_Window(Xs,Ys);
		for(x=Xs;x<=Xz;x++,i++)
		{
			BUFF[i]=LCD_ReadColor_16bit();
		}
	}
}
//写颜色块
void	GUI_Write_block(s16	Xs,s16	Ys,s16	Xz,s16	Yz,	u16		Color)
{
	u16	x;
	for(;Ys<=Yz;Ys++)
	{
		LCD_Read_Window(Xs,Ys);
		for(x=Xs;x<=Xz;x++)
		{
			LCD_WriteData_16bit(Color);
		}
	}
}

//写区域
void	GUI_Write_Area(int x0, int y0, int x1, int y1, u16 *buf, uint8_t reverse)
{
	u16	x;
	for(;y0<=y1;y0++)
	{
		LCD_Read_Window(x0,y0);
		for(x=x0;x<=x1;x++)
		{
			LCD_WriteData_16bit(*buf);
			buf++;
		}
	}
}




