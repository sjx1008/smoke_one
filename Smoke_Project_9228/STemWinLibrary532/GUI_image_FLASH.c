#include "GUI.h"
#include "GUI_image_FLASH.h"
#include "Flahs_Driver.h"
#include "TFT_Drive.h"
#include	"TFT_Init.h"
#include "TFT_Drive.h"
#include	<string.h>

__align(4)	u8	GetFLASH_Buff[2][d_GetFLASH_Buff_Size];


//从FLASH里面获取图片数据
static int	ImageGetDoubleData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off)
{
	static	u32	pD,pD_Q;
	static	u8	GetFLASH_I;
	static	u32	NumBytesReq_Q;
	pD=(u32)p;
	if(NumBytesReq>d_GetFLASH_Buff_Size)
		NumBytesReq=d_GetFLASH_Buff_Size;
	if(Off==0 || pD_Q!=pD+Off || NumBytesReq_Q<NumBytesReq)
	{
		GetFLASH_I=0;
		SPI_Flash_Read_BuffData_OK();
		SPI_Flash_Read_BuffData8(pD+Off,GetFLASH_Buff[GetFLASH_I],NumBytesReq);
	}
	pD_Q=pD+Off+NumBytesReq;
	SPI_Flash_Read_BuffData_OK();
	*ppData = GetFLASH_Buff[GetFLASH_I];
	GetFLASH_I=!GetFLASH_I;
	SPI_Flash_Read_BuffData8(pD_Q,GetFLASH_Buff[GetFLASH_I],NumBytesReq);
	NumBytesReq_Q=NumBytesReq;
	return NumBytesReq;
}
static int	ImageGetData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off)
{
	static	u32	pD;
	pD=(u32)p;
	if(NumBytesReq>d_GetFLASH_Buff_Size)
		NumBytesReq=d_GetFLASH_Buff_Size;

	SPI_Flash_Read_BuffData8(pD+Off,GetFLASH_Buff[0],NumBytesReq);
	SPI_Flash_Read_BuffData_OK();
	*ppData = GetFLASH_Buff[0];
	return NumBytesReq;
}
#if	1
//从FLASH里面获取PNG图片数据
static int	ImageGetPNGData(void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off)
{
	static	u32	pD;
	u8 *Buff;
	pD=(u32)p+Off;
	Buff=(U8 *)*ppData;
	SPI_Flash_Read_BuffData8(pD,Buff,NumBytesReq);
	SPI_Flash_Read_BuffData_OK();
	return NumBytesReq;
}
#endif
//Emwin	绘制BMP图片
void	Draw_BMP_EX(u32	FLASH_Addr,s16	X0,s16	Y0)
{
	GUI_BMP_DrawEx(ImageGetDoubleData,(void*)FLASH_Addr,X0,Y0);//在指定位置显示BMP图片
	SPI_Flash_Read_BuffData_OK();
}

//Emwin绘制缩放BMP图片
//mode:图片放置位置	0：X0,Y0为图片的左上角
//									1：X0,Y0为图片的右上角
//									2：X0,Y0为图片的左下角
//									3：X0,Y0为图片的右下角
//									4：X0,Y0为图片的中心
//member:  缩放比例的分子项
//denom:缩放比例的分母项
void	Draw_BMPScaled_EX(u32	FLASH_Addr,s16	X0,s16	Y0,s16	member,s16	denom,u8	mode)
{
	s16	XSize,YSize;
	if(mode!=0)
	{
		XSize = GUI_BMP_GetXSizeEx(ImageGetDoubleData,(void*)FLASH_Addr);	//获取图片的X轴大小
		YSize = GUI_BMP_GetYSizeEx(ImageGetDoubleData,(void*)FLASH_Addr);	//获取图片的Y轴大小
		if(mode==1)
		{
			X0-=XSize;
		}
		else if(mode==2)
		{
			Y0-=YSize;
		}
		else if(mode==3)
		{
			X0-=XSize;
			Y0-=YSize;
		}
		else if(mode==4)
		{
			X0-=XSize/2;
			Y0-=YSize/2;
		}
	}
	GUI_BMP_DrawScaledEx(ImageGetDoubleData,(void*)FLASH_Addr,X0,Y0,member,denom);//在指定位置显示BMP图片
	SPI_Flash_Read_BuffData_OK();
}

//Emwin	绘制jpeg图片
void	Draw_JPG_EX(u32	FLASH_Addr,s16	X0,s16	Y0)
{
	GUI_JPEG_DrawEx(ImageGetDoubleData,(void*)FLASH_Addr,X0,Y0);//在指定位置显示JPEG图片
	SPI_Flash_Read_BuffData_OK();
}

//Emwin绘制缩放jpeg图片
//mode:图片放置位置	0：X0,Y0为图片的左上角
//									1：X0,Y0为图片的右上角
//									2：X0,Y0为图片的左下角
//									3：X0,Y0为图片的右下角
//									4：X0,Y0为图片的中心
//member:  缩放比例的分子项
//denom:缩放比例的分母项
void	Draw_JPGScaled_EX(u32	FLASH_Addr,s16	X0,s16	Y0,s16	member,s16	denom,u8	mode)
{
	GUI_JPEG_INFO	JPEG_INFO;
	if(mode!=0)
	{
		GUI_JPEG_GetInfoEx(ImageGetData,(void*)FLASH_Addr,&JPEG_INFO);
		if(mode==1)
		{
			X0-=JPEG_INFO.XSize;
		}
		else if(mode==2)
		{
			Y0-=JPEG_INFO.YSize;
		}
		else if(mode==3)
		{
			X0-=JPEG_INFO.XSize;
			Y0-=JPEG_INFO.YSize;
		}
		else if(mode==4)
		{
			X0-=JPEG_INFO.XSize/2;
			Y0-=JPEG_INFO.YSize/2;
		}
	}
	GUI_JPEG_DrawScaledEx(ImageGetDoubleData,(void*)FLASH_Addr,X0,Y0,member,denom);//在指定位置显示BMP图片
	SPI_Flash_Read_BuffData_OK();
}
#if 0
//Emwin	绘制PNG图片
void	Draw_PNG_EX(u32	FLASH_Addr,s16	X0,s16	Y0)
{
	GUI_PNG_DrawEx(ImageGetPNGData,(void*)FLASH_Addr,X0,Y0);//在指定位置显示JPEG图片
	SPI_Flash_Read_BuffData_OK();
}
#endif
//Emwin	绘制流位图图片
GUI_BITMAPSTREAM_INFO pInfo;
void	Draw_Bitmap_EX(int  (*PP)(GUI_GET_DATA_FUNC * pfGetData, const void * p, int x, int y),u32	FLASH_Addr,s16	X0,s16	Y0)
{
	(*PP)(ImageGetPNGData,(void*)FLASH_Addr,X0,Y0);
	SPI_Flash_Read_BuffData_OK();
}








//////////////////////////////
//////////////////////////////
//////////////////////////////
//从BMP里面切图 8位位图以上
///////////////////////
 typedef struct __attribute__((__packed__))  //BMP文件头14个字节
// typedef struct tagBITMAPFILEHEADER  //BMP文件头14个字节
{
	__IO	uint16_t bfType; //文件类型
	__IO	uint32_t bfSize; //图片的大小
	__IO	uint16_t bfReserved1; //保留
	__IO	uint16_t bfReserved2;
	__IO	uint32_t bfOffBits;//头信息到数据信息的偏移量
} BITMAPFILEHEADER;

typedef struct __attribute__((__packed__)) //告诉编译器取消结构在编译过程中的优化对齐,按照实际占用字节数进行对齐
//typedef struct tagBITMAPINFOHEADER   //数据信息头为40个字节
{
  __IO	uint32_t biSize; //数据信息头size
	__IO	uint32_t biWidth;//图片宽度
	__IO	uint32_t biHeight;//图片高度
	__IO	uint16_t biPlanes;//颜色平面数总是1
	__IO	uint16_t biBitCount;//图片是几位的:1,4,8,16,24或32位
	__IO	uint32_t biCompression;//图片压缩类型
	__IO	uint32_t biSizeImage;//图片大小
	__IO	uint32_t biXPelsPerMeter;//水平分辨率
	__IO	uint32_t biYPelsPerMeter;//垂直分辨率
	__IO	uint32_t biClrUsed;//实际使用色彩表的索引数，0表示使用所有色彩板
	__IO	uint32_t biClrImportant;//颜色重要程度，0都很重要
} BITMAPINFOHEADER;


typedef struct __attribute__((__packed__)) //告诉编译器取消结构在编译过程中的优化对齐,按照实际占用字节数进行对齐
//typedef struct tagBITMAPINFOHEADER   //数据信息头为40个字节
{
	BITMAPFILEHEADER		bmpFileHead;
	BITMAPINFOHEADER		bmpInfoHead;
} BMPHEADINFORMATION;


//BMP切图
u8	Map_draw_bmp_ex(u32	pic_addr,GUI_RECT *pCutRectPos,int x0, int y0)
{
	GUI_RECT	RECT;
	u16	rlinenum;
	uint32_t flash_addr;
	u16	i;
	int rlinelen = 0;
	int wBytes,hBytes;

	u8	GetFLASH_I=0;

	BMPHEADINFORMATION	bmp_head;
	BMPHEADINFORMATION	*bmp_head1,*bmp_head2;

	RECT=*pCutRectPos;
	bmp_head1=(BMPHEADINFORMATION*)GetFLASH_Buff[0];
	bmp_head2=(BMPHEADINFORMATION*)GetFLASH_Buff[1];
	SPI_Flash_Read_BuffData8(pic_addr,(u8*)&bmp_head,54);
	SPI_Flash_Read_BuffData_OK();
	if(RECT.x0>bmp_head.bmpInfoHead.biWidth || RECT.y0>bmp_head.bmpInfoHead.biHeight || bmp_head.bmpFileHead.bfOffBits>200)
		return 1;
	if(bmp_head.bmpFileHead.bfOffBits>54)
		SPI_Flash_Read_BuffData8(pic_addr+54,((u8*)bmp_head1)+54,bmp_head.bmpFileHead.bfOffBits-54);
	if(RECT.x1>bmp_head.bmpInfoHead.biWidth)
		RECT.x1=bmp_head.bmpInfoHead.biWidth;
	if(RECT.y1>bmp_head.bmpInfoHead.biHeight)
		RECT.y1=bmp_head.bmpInfoHead.biHeight;
	memcpy(bmp_head1,&bmp_head,54);
	bmp_head1->bmpInfoHead.biWidth=RECT.x1-RECT.x0+1;	//切图的宽度
	bmp_head1->bmpInfoHead.biHeight=1;	//切图的高度
	wBytes=(bmp_head.bmpInfoHead.biWidth*bmp_head.bmpInfoHead.biBitCount+31)/32*4;//获取母图一行的字节数
	bmp_head1->bmpInfoHead.biSizeImage=(bmp_head1->bmpInfoHead.biWidth*bmp_head.bmpInfoHead.biBitCount+31)/32*4; //获取切图的字节数，因为是一行
	rlinelen=bmp_head1->bmpInfoHead.biSizeImage;	//获取切图的一行数据字节数
	hBytes = RECT.x0 * bmp_head.bmpInfoHead.biBitCount/8;

	bmp_head1->bmpFileHead.bfSize=bmp_head1->bmpInfoHead.biSizeImage+bmp_head1->bmpFileHead.bfOffBits;
	SPI_Flash_Read_BuffData_OK();
	memcpy(bmp_head2,bmp_head1,bmp_head1->bmpFileHead.bfOffBits);

	rlinenum=RECT.y1 - RECT.y0+1;//行数
	RECT.y0=bmp_head.bmpInfoHead.biHeight-RECT.y0-1;
	pic_addr= hBytes + bmp_head.bmpFileHead.bfOffBits + pic_addr;

	flash_addr=wBytes*RECT.y0 + pic_addr;//计算每行首地址
	SPI_Flash_Read_BuffData8(flash_addr,&GetFLASH_Buff[0][bmp_head.bmpFileHead.bfOffBits],rlinelen);
	for(i=1;i<rlinenum;i++)
	{
		RECT.y0--;
		flash_addr=wBytes*RECT.y0 + pic_addr;//计算每行首地址
		GetFLASH_I=!GetFLASH_I;
		SPI_Flash_Read_BuffData_OK();
		SPI_Flash_Read_BuffData8(flash_addr,&GetFLASH_Buff[GetFLASH_I][bmp_head.bmpFileHead.bfOffBits],rlinelen);
		GUI_BMP_Draw(GetFLASH_Buff[!GetFLASH_I],x0,y0);
		y0++;
	}
	SPI_Flash_Read_BuffData_OK();
	GUI_BMP_Draw(GetFLASH_Buff[GetFLASH_I],x0,y0);
	return	0;
}
//BMP切图
u8	Map_draw_bmpToBitmap_ex(u32	pic_addr,GUI_RECT *pCutRectPos,int x0, int y0)
{
	GUI_RECT	RECT;
	u16	rlinenum;
	uint32_t flash_addr;
	u16	i;
	int rlinelen = 0;
	int wBytes,hBytes;
	u32	bfOffBits;
	u32	biWidth;
	u32	biHeight;
	u8	GetFLASH_I=0;
	u16	ys;
	GUI_BITMAP	p_BITMAP;

	RECT=*pCutRectPos;
	bfOffBits=SPI_Flash_Read_PageData32(pic_addr+10);
	biWidth=SPI_Flash_Read_PageData32(pic_addr+18);
	biHeight=SPI_Flash_Read_PageData32(pic_addr+22);

	if(RECT.x0>biWidth || RECT.y0>biHeight || bfOffBits!=0x46)
		return 1;
	if(RECT.x1>=biWidth)
		RECT.x1=biWidth-1;
	if(RECT.y1>=biHeight)
		RECT.y1=biHeight-1;

	p_BITMAP.XSize=RECT.x1-RECT.x0+1;//切图的宽度
	p_BITMAP.YSize=1;//切图的高度
	p_BITMAP.BytesPerLine=p_BITMAP.XSize*2;
	p_BITMAP.BitsPerPixel=16;
	p_BITMAP.pPal=NULL;
	p_BITMAP.pMethods=GUI_DRAW_BMPM565;

	wBytes=(biWidth*16+31)/32*4;//获取母图一行的字节数
	rlinelen=p_BITMAP.BytesPerLine;
	hBytes = RECT.x0 * 2;


	rlinenum=RECT.y1 - RECT.y0+1;//行数
	ys=biHeight-RECT.y0-1;
	pic_addr= hBytes + bfOffBits + pic_addr;

	flash_addr=wBytes*ys + pic_addr;//计算每行首地址
	SPI_Flash_Read_BuffData8(flash_addr,GetFLASH_Buff[0],rlinelen);
	for(i=1;i<rlinenum;i++)
	{
		ys--;
		flash_addr=wBytes*ys + pic_addr;//计算每行首地址
		p_BITMAP.pData=GetFLASH_Buff[GetFLASH_I];
		GetFLASH_I=!GetFLASH_I;
		SPI_Flash_Read_BuffData_OK();
		SPI_Flash_Read_BuffData8(flash_addr,GetFLASH_Buff[GetFLASH_I],rlinelen);
		GUI_DrawBitmap(&p_BITMAP,x0,y0++);
	}
	p_BITMAP.pData=GetFLASH_Buff[GetFLASH_I];
	SPI_Flash_Read_BuffData_OK();
	GUI_DrawBitmap(&p_BITMAP,x0,y0);
	return	0;
}
//非emwin直接显示FLASH里面的BMP格式图片到屏幕
u8 draw_Bmp_ex(uint32_t pic_addr,int x0, int y0)
{
	int i,j;
	uint32_t flash_addr = 0;

	u32	bfOffBits;
	u32	biWidth;
	u32	biHeight;
	u16	iLineByteCnt;
	u8	GetFLASH_I=0;

	bfOffBits=SPI_Flash_Read_PageData32(pic_addr+10);
	biWidth=SPI_Flash_Read_PageData32(pic_addr+18);
	biHeight=SPI_Flash_Read_PageData32(pic_addr+22);

	if(!biWidth || !biHeight)
		return	1;
	iLineByteCnt = (((biWidth <<4) + 31) >> 5) << 2; //四字节对齐的方式计算每行字节数

	pic_addr= pic_addr+bfOffBits+(biHeight-1)*iLineByteCnt;
	SPI_Flash_Read_BuffData8(pic_addr,GetFLASH_Buff[0],iLineByteCnt);
	LCD_WriteComm(0x2A);
	LCD_WriteData_8bit(x0>>8);
	LCD_WriteData_8bit(x0&0xFF);
	LCD_WriteData_8bit((x0+biWidth-1)>>8);
	LCD_WriteData_8bit((x0+biWidth-1)&0xFF);
	LCD_WriteComm(0x2B);
	LCD_WriteData_8bit((y0+TFT_Y_panyi)>>8);
	LCD_WriteData_8bit((y0+TFT_Y_panyi)&0xFF);
	LCD_WriteData_8bit((y0+biHeight+TFT_Y_panyi-1)>>8);
	LCD_WriteData_8bit((y0+biHeight+TFT_Y_panyi-1)&0xFF);
	LCD_WriteComm(0x2c);

	for(i=1;i<biHeight;i++)
	{
		flash_addr=pic_addr-iLineByteCnt*i;//计算每行首地址
		GetFLASH_I=!GetFLASH_I;
		SPI_Flash_Read_BuffData_OK();
		SPI_Flash_Read_BuffData8(flash_addr,GetFLASH_Buff[GetFLASH_I],iLineByteCnt);
		for(j=0;j<biWidth;j++)
			LCD_WriteData_16bit(((u16*)GetFLASH_Buff[!GetFLASH_I])[j]);
	}
	SPI_Flash_Read_BuffData_OK();
	for(j=0;j<biWidth;j++)
		LCD_WriteData_16bit(((u16*)GetFLASH_Buff[GetFLASH_I])[j]);
	LCD_WriteComm(0x2A);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0xEF);

	LCD_WriteComm(0x2B);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);//24
	LCD_WriteData_8bit((d_TFT_Y_Max+TFT_Y_panyi-1)>>8);
	LCD_WriteData_8bit((d_TFT_Y_Max+TFT_Y_panyi-1)&0xFF);
	return	0;
}

//将FLASH里面BMP图片转成Bitmap流显示 使用emwin方式  RGR565
u8 draw_BmpToBitmap_ex(uint32_t pic_addr,int x0, int y0)
{
	int i;
	uint32_t flash_addr = 0;

	u32	bfOffBits;
	u32	biWidth;
	u32	biHeight;
	u16	iLineByteCnt;
	u8	GetFLASH_I=0;
	GUI_BITMAP	p_BITMAP;
	bfOffBits=SPI_Flash_Read_PageData32(pic_addr+10);
	biWidth=SPI_Flash_Read_PageData32(pic_addr+18);
	biHeight=SPI_Flash_Read_PageData32(pic_addr+22);

	if(!biWidth || !biHeight)
		return	1;
	iLineByteCnt = (((biWidth <<4) + 31) >> 5) << 2; //四字节对齐的方式计算每行字节数
	pic_addr= pic_addr+bfOffBits+(biHeight-1)*iLineByteCnt;
	SPI_Flash_Read_BuffData8(pic_addr,GetFLASH_Buff[0],iLineByteCnt);
	p_BITMAP.XSize=biWidth;
	p_BITMAP.YSize=1;
	p_BITMAP.BytesPerLine=p_BITMAP.XSize*2;
	p_BITMAP.BitsPerPixel=16;
	p_BITMAP.pPal=NULL;
	p_BITMAP.pMethods=GUI_DRAW_BMPM565;

	for(i=1;i<biHeight;i++)
	{
		flash_addr=pic_addr-iLineByteCnt*i;//计算每行首地址
		p_BITMAP.pData=GetFLASH_Buff[GetFLASH_I];
		GetFLASH_I=!GetFLASH_I;
		SPI_Flash_Read_BuffData_OK();
		SPI_Flash_Read_BuffData8(flash_addr,GetFLASH_Buff[GetFLASH_I],iLineByteCnt);
		GUI_DrawBitmap(&p_BITMAP,x0,y0+i-1);
	}
	p_BITMAP.pData=GetFLASH_Buff[GetFLASH_I];
	SPI_Flash_Read_BuffData_OK();
	GUI_DrawBitmap(&p_BITMAP,x0,y0+i-1);
	return	0;
}

//非emwin直接显示ROM里面的BMP格式图片到屏幕上 RGB565
u8 draw_Bmp(const void * pFileData,int x0, int y0)
{
	int i,j;
	u16* flash_addr;
	BMPHEADINFORMATION	*bmp_head;
	u32	bfOffBits;
	u32	biWidth;
	u32	biHeight;
	u32	pic_addr;
	u16	iLineByteCnt;

	bmp_head=(BMPHEADINFORMATION*)pFileData;
	bfOffBits=bmp_head->bmpFileHead.bfOffBits;
	biWidth=bmp_head->bmpInfoHead.biWidth;
	biHeight=bmp_head->bmpInfoHead.biHeight;
	iLineByteCnt = (((biWidth <<4) + 31) >> 5) << 2; //四字节对齐的方式计算每行字节数
	pic_addr= (u32)pFileData+bfOffBits+(biHeight-1)*iLineByteCnt;
	LCD_WriteComm(0x2A);
	LCD_WriteData_8bit(x0>>8);
	LCD_WriteData_8bit(x0&0xFF);
	LCD_WriteData_8bit((x0+biWidth-1)>>8);
	LCD_WriteData_8bit((x0+biWidth-1)&0xFF);
	LCD_WriteComm(0x2B);
	LCD_WriteData_8bit((y0+TFT_Y_panyi)>>8);
	LCD_WriteData_8bit((y0+TFT_Y_panyi)&0xFF);
	LCD_WriteData_8bit((y0+biHeight+TFT_Y_panyi-1)>>8);
	LCD_WriteData_8bit((y0+biHeight+TFT_Y_panyi-1)&0xFF);
	LCD_WriteComm(0x2c);

	for(i=0;i<biHeight;i++)
	{
		flash_addr= (u16*)(pic_addr-iLineByteCnt*i);//计算每行首地址
		for(j=0;j<biWidth;j++)
			LCD_WriteData_16bit(flash_addr[j]);
	}
	LCD_WriteComm(0x2A);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0xEF);

	LCD_WriteComm(0x2B);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);//24
	LCD_WriteData_8bit((d_TFT_Y_Max+TFT_Y_panyi-1)>>8);
	LCD_WriteData_8bit((d_TFT_Y_Max+TFT_Y_panyi-1)&0xFF);
	return	0;

/////////////////////////////


}

//将ROM里面BMP图片转成Bitmap流显示 使用emwin方式  RGR565
u8 draw_BmpToBitmap(const void * pFileData,int x0, int y0)
{
	int i;
	BMPHEADINFORMATION	*bmp_head;
	u32	bfOffBits;
	u32	biWidth;
	u32	biHeight;
	u32	pic_addr;
	u16	iLineByteCnt;
	GUI_BITMAP	p_BITMAP;

	bmp_head=(BMPHEADINFORMATION*)pFileData;
	bfOffBits=bmp_head->bmpFileHead.bfOffBits;
	biWidth=bmp_head->bmpInfoHead.biWidth;
	biHeight=bmp_head->bmpInfoHead.biHeight;
	iLineByteCnt = (((biWidth <<4) + 31) >> 5) << 2; //四字节对齐的方式计算每行字节数
	pic_addr= (u32)pFileData+bfOffBits+(biHeight-1)*iLineByteCnt;
	p_BITMAP.XSize=biWidth;
	p_BITMAP.YSize=1;
	p_BITMAP.BytesPerLine=p_BITMAP.XSize*2;
	p_BITMAP.BitsPerPixel=16;
	p_BITMAP.pPal=NULL;
	p_BITMAP.pMethods=GUI_DRAW_BMPM565;
	for(i=0;i<biHeight;i++)
	{
		p_BITMAP.pData= (u8*)(pic_addr-iLineByteCnt*i);//计算每行首地址
		GUI_DrawBitmap(&p_BITMAP,x0,y0+i);
	}
	return	0;
}


/*****************
异形抠图
********************/
void	MapNoRulebmpToBitmap_ex(u32	pic_addr,GUI_RECT *pCutRectPos,void (*P)(void), int x0, int y0,GUI_MEMDEV_Handle Mem)
{
	uint32_t flash_addr;
	int rlinelen = 0;
	int wBytes,hBytes;
	u32	bfOffBits;
	u32	biWidth;
	u32	biHeight;
	s16	ys;
	GUI_BITMAP	p_BITMAP;
	u32	addr;

	u8	GetFLASH_I=0;
	GUI_RECT	RECT;
	GUI_MEMDEV_Handle sMem;
	u8	B_kaishi;
	s16	xi,yi,x1,y1;
	u32	color;

	u8	B_Disp=0;
	s16	Disp_X,	Disp_Y;

	bfOffBits=SPI_Flash_Read_PageData32(pic_addr+10);
	biWidth=SPI_Flash_Read_PageData32(pic_addr+18);
	biHeight=SPI_Flash_Read_PageData32(pic_addr+22);

	if(bfOffBits!=0x46)
		return;

	p_BITMAP.YSize=1;//切图的高度
	p_BITMAP.BitsPerPixel=16;
	p_BITMAP.pPal=NULL;
	p_BITMAP.pMethods=GUI_DRAW_BMPM565;

	wBytes=(biWidth*16+31)/32*4;//获取母图一行的字节数

	x1=pCutRectPos->x1-pCutRectPos->x0+x0;
	y1=pCutRectPos->y1-pCutRectPos->y0+y0;
	sMem=GUI_MEMDEV_CreateFixed(x0,y0,x1-x0+1,y1-y0+1,
	GUI_MEMDEV_NOTRANS,
	GUI_MEMDEV_APILIST_1,
	GUI_COLOR_CONV_1);
	GUI_MEMDEV_Select(sMem);
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(x0,y0,x1,y1);
	GUI_SetColor(GUI_WHITE);
	(*P)();
	for(yi=y0;yi<=y1;yi++)
	{
		B_kaishi=0;
		RECT.y1=RECT.y0=yi-y0+pCutRectPos->y0;
		for(xi=x0;xi<=x1;xi++)
		{
			color=GUI_GetPixelIndex(xi,yi);
			if(B_kaishi==0)
			{
				if(color==1)
				{
					RECT.x0=xi-x0+pCutRectPos->x0;
					B_kaishi=1;
				}
			}
			else if(B_kaishi==1)
			{
				if(color!=1 || xi==x1)
				{
					RECT.x1=xi-x0+pCutRectPos->x0;
					B_kaishi=0;
					//开始抠图

					if(RECT.x0>biWidth || RECT.y0>biHeight)
						break;
					if(RECT.x1>=biWidth)
						RECT.x1=biWidth-1;
					if(RECT.y1>=biHeight)
						RECT.y1=biHeight-1;
					rlinelen=(RECT.x1-RECT.x0+1)*2;
					hBytes = RECT.x0 * 2;
					ys=biHeight-RECT.y0-1;
					addr= hBytes + bfOffBits + pic_addr;
					flash_addr=wBytes*ys + addr;//计算每行首地址
					GetFLASH_I=!GetFLASH_I;
					if(B_Disp)
					{
						SPI_Flash_Read_BuffData_OK();
						SPI_Flash_Read_BuffData8(flash_addr,GetFLASH_Buff[GetFLASH_I],rlinelen);
						GUI_MEMDEV_Select(Mem);
						GUI_DrawBitmap(&p_BITMAP,Disp_X,Disp_Y);
						GUI_MEMDEV_Select(sMem);
					}
					else
						SPI_Flash_Read_BuffData8(flash_addr,GetFLASH_Buff[GetFLASH_I],rlinelen);
					p_BITMAP.XSize=RECT.x1-RECT.x0+1;//切图的宽度
					p_BITMAP.BytesPerLine=p_BITMAP.XSize*2;
					B_Disp=1;
					Disp_X=RECT.x0-pCutRectPos->x0+x0;	Disp_Y=yi;
					p_BITMAP.pData=GetFLASH_Buff[GetFLASH_I];
				}
			}
		}
	}
	GUI_MEMDEV_Select(Mem);
	if(B_Disp)
	{
		SPI_Flash_Read_BuffData_OK();
		GUI_DrawBitmap(&p_BITMAP,Disp_X,Disp_Y);
	}
	GUI_MEMDEV_Delete(sMem);
}


/*****************
外部Flash的GIF显示
********************/

void	Flash_GUI_GIF_GetInfoEx(u32	p,GUI_GIF_INFO * pInfo)
{
	GUI_GIF_GetInfoEx(ImageGetDoubleData,(void*) p,pInfo);
	SPI_Flash_Read_BuffData_OK();
}

void	Flash_GUI_GIF_DrawSubEx(u32	p,s16	x,s16 y,u32	i)
{
	GUI_GIF_DrawSubEx(ImageGetDoubleData,(void*) p,x,y,i);
	SPI_Flash_Read_BuffData_OK();
}
void	Flash_GUI_GIF_GetImageInfoEx(u32	p,GUI_GIF_IMAGE_INFO * pInfo,u32	i)
{
	GUI_GIF_GetImageInfoEx(ImageGetDoubleData,(void*) p,pInfo,i);
	SPI_Flash_Read_BuffData_OK();
}

/************************************/


//获取BMP图片的X大小
int Flash_GUI_BMP_GetXSizeEx(u32	p)
{
	u16	x;
	x=GUI_BMP_GetXSizeEx(ImageGetDoubleData, (void*) p);
	SPI_Flash_Read_BuffData_OK();
	return	x;
}

//获取BMP图片的Y大小
int Flash_GUI_BMP_GetYSizeEx(u32	p)
{
	u16	y;
	y=GUI_BMP_GetYSizeEx(ImageGetDoubleData, (void*) p);
	SPI_Flash_Read_BuffData_OK();
	return	y;
}

//获取流位图的相关信息
void Flash_GUI_GetStreamedBitmapInfoEx(u32	p,GUI_BITMAPSTREAM_INFO * pInfo)
{
	GUI_GetStreamedBitmapInfoEx(ImageGetPNGData,(void *) p,pInfo);
	SPI_Flash_Read_BuffData_OK();
}


















