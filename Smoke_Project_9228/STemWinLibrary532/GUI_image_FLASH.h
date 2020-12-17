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
//Emwin	绘制流位图图片
extern	void	Draw_Bitmap_EX(int  (*PP)(GUI_GET_DATA_FUNC * pfGetData, const void * p, int x, int y),u32	FLASH_Addr,s16	X0,s16	Y0);
extern	u8	Map_draw_bmp_ex(u32	pic_addr,GUI_RECT *pCutRectPos,int x0, int y0);
extern	u8	Map_draw_bmpToBitmap_ex(u32	pic_addr,GUI_RECT *pCutRectPos,int x0, int y0);

//非emwin直接显示ROM里面的BMP格式图片
//非emwin直接显示FLASH里面的BMP格式图片
extern	u8 draw_Bmp_ex(uint32_t pic_addr,int x0, int y0);
extern	u8 draw_Bmp(const void * pFileData,int x0, int y0);
extern	u8 draw_BmpToBitmap_ex(uint32_t pic_addr,int x0, int y0);
extern	u8 draw_BmpToBitmap(const void * pFileData,int x0, int y0);

/*****************
异形抠图
********************/
extern	void	MapNoRulebmpToBitmap_ex(u32	pic_addr,GUI_RECT *pCutRectPos,void (*P)(void), int x0, int y0,GUI_MEMDEV_Handle Mem);


/*****************
外部Flash的GIF显示
********************/
extern	void	Flash_GUI_GIF_GetInfoEx(u32	p,GUI_GIF_INFO * pInfo);
extern	void	Flash_GUI_GIF_DrawSubEx(u32	p,s16	x,s16 y,u32	i);
extern	void	Flash_GUI_GIF_GetImageInfoEx(u32	p,GUI_GIF_IMAGE_INFO * pInfo,u32	i);
/************************************/

//获取BMP图片的X大小
int Flash_GUI_BMP_GetXSizeEx(u32	p);

//获取BMP图片的Y大小
int Flash_GUI_BMP_GetYSizeEx(u32	p);
//获取流位图的相关信息
void Flash_GUI_GetStreamedBitmapInfoEx(u32	p,GUI_BITMAPSTREAM_INFO * pInfo);

#endif









