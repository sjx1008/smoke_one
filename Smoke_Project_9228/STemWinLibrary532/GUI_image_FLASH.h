#ifndef		_GUI_IMAGE_FLASH_H_
#define		_GUI_IMAGE_FLASH_H_
#include "main.h"
#include "GUI.h"

#define	d_GetFLASH_Buff_Size	240*2
extern	u8	GetFLASH_Buff[2][d_GetFLASH_Buff_Size];

extern	void	Draw_BMP_EX(u32	FLASH_Addr,s16	X0,s16	Y0);
extern	void	Draw_BMPScaled_EX(u32	FLASH_Addr,s16	X0,s16	Y0,s16	member,s16	denom,u8	mode);
extern	void	Draw_JPG_EX(u32	FLASH_Addr,s16	X0,s16	Y0);
extern	void	Draw_JPGScaled_EX(u32	FLASH_Addr,s16	X0,s16	Y0,s16	member,s16	denom,u8	mode);
extern	void	Draw_PNG_EX(u32	FLASH_Addr,s16	X0,s16	Y0);
//Emwin	������λͼͼƬ
extern	void	Draw_Bitmap_EX(int  (*PP)(GUI_GET_DATA_FUNC * pfGetData, const void * p, int x, int y),u32	FLASH_Addr,s16	X0,s16	Y0);
extern	u8	Map_draw_bmp_ex(u32	pic_addr,GUI_RECT *pCutRectPos,int x0, int y0);
extern	u8	Map_draw_bmpToBitmap_ex(u32	pic_addr,GUI_RECT *pCutRectPos,int x0, int y0);

//��emwinֱ����ʾROM�����BMP��ʽͼƬ
//��emwinֱ����ʾFLASH�����BMP��ʽͼƬ
extern	u8 draw_Bmp_ex(uint32_t pic_addr,int x0, int y0);
extern	u8 draw_Bmp(const void * pFileData,int x0, int y0);
extern	u8 draw_BmpToBitmap_ex(uint32_t pic_addr,int x0, int y0);
extern	u8 draw_BmpToBitmap(const void * pFileData,int x0, int y0);

/*****************
���ο�ͼ
********************/
extern	void	MapNoRulebmpToBitmap_ex(u32	pic_addr,GUI_RECT *pCutRectPos,void (*P)(void), int x0, int y0,GUI_MEMDEV_Handle Mem);


/*****************
�ⲿFlash��GIF��ʾ
********************/
extern	void	Flash_GUI_GIF_GetInfoEx(u32	p,GUI_GIF_INFO * pInfo);
extern	void	Flash_GUI_GIF_DrawSubEx(u32	p,s16	x,s16 y,u32	i);
extern	void	Flash_GUI_GIF_GetImageInfoEx(u32	p,GUI_GIF_IMAGE_INFO * pInfo,u32	i);
/************************************/

//��ȡBMPͼƬ��X��С
int Flash_GUI_BMP_GetXSizeEx(u32	p);

//��ȡBMPͼƬ��Y��С
int Flash_GUI_BMP_GetYSizeEx(u32	p);
//��ȡ��λͼ�������Ϣ
void Flash_GUI_GetStreamedBitmapInfoEx(u32	p,GUI_BITMAPSTREAM_INFO * pInfo);

#endif









