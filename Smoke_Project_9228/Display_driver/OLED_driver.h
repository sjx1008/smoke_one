
#ifndef __OLED_DRIVER_H
#define __OLED_DRIVER_H
#include "stm32f0xx.h"
#include "Stdint_2.h"
#include "Char_Library.h"
//////��Ļ����///////////////	
	

/*������������---------------------*/	
	typedef enum
	{
	#ifdef	Font_6_ON
		ZT6 	= 0,
	#endif

	#ifdef	Font_7_ON
		ZT7,
	#endif
		
	#ifdef	Font_8_ON
		ZT8,
	#endif
		
	#ifdef	Font_9_ON
		ZT9,
	#endif

	#ifdef	Font_10_ON
		ZT10,
	#endif
		
	#ifdef	Font_12_ON
		ZT12,
	#endif
		
	#ifdef	Font_12B_ON
		ZT12B,
	#endif

	#ifdef	Font_13_ON
		ZT13,
	#endif
		
	#ifdef	Font_16_ON
		ZT16,
	#endif

	#ifdef	Font_19_ON
		ZT19,
	#endif

	#ifdef	Font_20_ON
		ZT20,
	#endif

	#ifdef	Font_21_ON
		ZT21,
	#endif
		
	#ifdef	Font_24_ON
		ZT24,
	#endif
	
	#ifdef	Font_27_ON
		ZT27,
	#endif
	
	#ifdef	Font_32_ON
		ZT32,
	#endif		
	}Font_TypeDef;
	
/*����������������---------------------*/	
	typedef enum
	{
		ZgT16 	= 16,	
	}Zhong_TypeDef;

	//////��Ļ�ƶ�����//////////
	typedef enum
	{
		d_Cross_screen 		= 0x00,
		d_Vertical_screen	= 0x01,
	}Screen_orientation_TypeDef;
	
	//////��ʾ��ɫ����//////////
	typedef enum
	{
		d_Clean_Color  			= 0x00,
		d_Bright_Color 			= 0xFF,
		d_Transparent_Color  	= 0xAA,
	}Color_TypeDef;
	

/*������ʾ����---------------------*/		
	typedef struct
	{
		u8	Xs;									//x���
		u8	Xz;									//x�յ�
		u8	Ys;									//y���
		u8	Yz;									//y�յ�
	}DISP_windows;
	
	
	/////////////////////����
	extern	Color_TypeDef		R_Front_Color;		//ǰ��ɫ
	extern	Color_TypeDef		R_Back_Color;			//����ɫ
	extern	Screen_orientation_TypeDef	B_Screen_orientation;

	//��Ч���ڷ�Χ
	extern	DISP_windows	R_DISP_windowsMAX;
	extern	DISP_windows	R_DISP_windowsSET;
	extern	DISP_windows	*R_DISP_windows;
	
	//�����Ļ
	extern	void	Clear_screen(void);
	//д��
	extern	void	GUI_Write_Dot(s16	Xs,s16	Ys);
	//����
	extern	Color_TypeDef	GUI_Read_Dot(s16		Xs,s16	Ys);
	//дʵ�ľ���
	extern	void	GUI_Write_block(s16	Xs,s16	Ys,s16	Xz,s16	Yz);
	//дֱ��
	extern	void	GUI_Write_Line(s16	Xs,s16	Ys,s16	Xz,s16	Yz);
	//д���ľ���
	extern	void	GUI_Write_Rectangular(s16	Xs,s16	Ys,s16	Xz,s16	Yz);
	//��ʾ����԰
	extern	void	GUI_Write_Round(s16	Xs,s16	Ys,u8	R);
	//��ʾʵ��԰
	extern	void	GUI_Write_Pie(s16	Xs,s16	Ys,u8	R);
	//��ʾͼƬ
	extern	void 	GUI_Write_Bitmap(s16 Xstart,s16 Ystart,uc8 *P);
	//��ʾָ���ߴ��ͼƬ
	extern	void 	GUI_Write_Bitmap_W_H(s16 Xstart,s16 Ystart,uc8 *P,u8	WIDE,u8	HIGH);
	//��ʾ�ַ���
	extern	void 	GUI_Write_Chars(s16 Xstart,s16 Yend,uc8 *Pchar,Font_TypeDef Font);
	//��ʾ�ַ�
	extern	void 	GUI_Write_Char(s16 Xstart,s16 Yend,uc8 Pchar,Font_TypeDef Font);
	//��ʾ�����ַ�
	extern	void 	GUI_Write_Zhongwen(s16 Xstart,s16 Yend,uc8 *Pchar,Zhong_TypeDef Font);
	//��ʾ10��������
	extern	void 	GUI_Write_data(s16 Xstart,s16 Yend,u8 Alignment,u32 data,Font_TypeDef	Font,u8 Zerofill);
	//��ʾԲ��
	extern	void	GUI_Write_Arc(s16	Xs,s16 Ys,u8	R,u16	Angle_S,u16	Angle_Z);
	//��ʾ����
	extern	void	GUI_Write_Sector(s16	Xs,s16 Ys,u8	R,u16	Angle_S,u16	Angle_Z);
	//��ʾԲ�ǿ��ľ���
	extern	void	GUI_Write_Rounded_rectangle(s16	X1,s16	Y1,s16	X2,s16	Y2,u8	R);
	//��ʾԲ��ʵ�ľ���
	extern	void	GUI_Write_Rounded_block(s16	X1,s16	Y1,s16	X2,s16	Y2,u8	R);
	//��ʾָ�����ֱ��
	extern	void	GUI_Write_Line_D(s16	Xs,s16	Ys,s16	Xz,s16	Yz,u8	D);
	//��ʾ������
	extern	void 	GUI_Write_Filled_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2);
	
	//���ø��´��ڷ�Χ
	extern	void	SET_Disp_Windows_ON(u8	Xs,u8	Ys,u8	Xz,u8	Yz);
	//�رո��´��ڷ�Χ���л���ȫ��
	extern	void	SET_Disp_Windows_OFF(void);
#endif 



