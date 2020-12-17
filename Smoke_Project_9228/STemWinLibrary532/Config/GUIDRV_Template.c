/*********************************************************************
*          Portions COPYRIGHT 2016 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIDRV_Template.c
Purpose     : Template driver, could be used as starting point for new
              simple display drivers supporting only one color depth.
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include <stddef.h>

#include "LCD_Private.h"
#include "GUI_Private.h"
#include "LCD_ConfDefaults.h"

#include "TFT_Init.h"
#include "TFT_Drive.h"
//#include "malloc.h"

static u16	hMem0[240];
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
/*********************************************************************
*
*       Macros for MIRROR_, SWAP_ and LUT_
*/
#if (!defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
  #if   (!LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) y
  #elif (!LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define LOG2PHYS_X(x, y) y
    #define LOG2PHYS_Y(x, y) x
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
  #elif (!LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define LOG2PHYS_X(x, y) y
    #define LOG2PHYS_Y(x, y) LCD_XSIZE - 1 - (x)
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
    #define LOG2PHYS_Y(x, y) y
  #elif ( LCD_MIRROR_X && !LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
    #define LOG2PHYS_Y(x, y) x
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y && !LCD_SWAP_XY)
    #define LOG2PHYS_X(x, y) LCD_XSIZE - 1 - (x)
    #define LOG2PHYS_Y(x, y) LCD_YSIZE - 1 - (y)
  #elif ( LCD_MIRROR_X &&  LCD_MIRROR_Y &&  LCD_SWAP_XY)
    #define LOG2PHYS_X(x, y) LCD_YSIZE - 1 - (y)
    #define LOG2PHYS_Y(x, y) LCD_XSIZE - 1 - (x)
  #endif
#else
  #if   ( defined (LCD_LUT_COM) && !defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) x
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #elif (!defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) y
  #elif ( defined (LCD_LUT_COM) &&  defined(LCD_LUT_SEG))
    #define LOG2PHYS_X(x, y) LCD__aCol2Seg0[x]
    #define LOG2PHYS_Y(x, y) LCD__aLine2Com0[y]
  #endif
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  U32 VRAMAddr;
  int xSize, ySize;
  int vxSize, vySize;
  int vxSizePhys;
  int BitsPerPixel;
} DRIVER_CONTEXT_TEMPLATE;

/*********************************************************************
*
*       Static functions
*
**********************************************************************
*/

/*********************************************************************
*
*       _SetPixelIndex
*´òµã
* Purpose:
*   Sets the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
static void _SetPixelIndex(GUI_DEVICE * pDevice, int x, int y, int PixelIndex) {
    //
    // Convert logical into physical coordinates (Dep. on LCDConf.h)
    //
    #if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
      int xPhys, yPhys;

      xPhys = LOG2PHYS_X(x, y);
      yPhys = LOG2PHYS_Y(x, y);
    #else
      #define xPhys x
      #define yPhys y
    #endif
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);
    GUI_USE_PARA(PixelIndex);
    {
      //#define		d_TFT_X_Max	240
      // Write into hardware ... Adapt to your system
//			LCD_Write_Window(x,y);
//			LCD_WriteData_16bit(PixelIndex);


      LCD_WriteComm(0x2A);
			LCD_WriteData_8bit(xPhys>>8);
			LCD_WriteData_8bit(xPhys&0xFF);
			LCD_WriteComm(0x2B);
			LCD_WriteData_8bit((yPhys+TFT_Y_panyi)>>8);
			LCD_WriteData_8bit((yPhys+TFT_Y_panyi)&0xFF);
			LCD_WriteComm(0x2c);
//
			LCD_WriteData_16bit(PixelIndex);
      // TBD by customer...
      //
    }
    #if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
      #undef xPhys
      #undef yPhys
    #endif
}

/*********************************************************************
*
*       _GetPixelIndex
*¶Áµã
* Purpose:
*   Returns the index of the given pixel. The upper layers
*   calling this routine make sure that the coordinates are in range, so
*   that no check on the parameters needs to be performed.
*/
static unsigned int _GetPixelIndex(GUI_DEVICE * pDevice, int x, int y) {
  unsigned int PixelIndex;
    //
    // Convert logical into physical coordinates (Dep. on LCDConf.h)
    //
    #if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
      int xPhys, yPhys;

      xPhys = LOG2PHYS_X(x, y);
      yPhys = LOG2PHYS_Y(x, y);
    #else
      #define xPhys x
      #define yPhys y
    #endif
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);
    {
      //
      // Write into hardware ... Adapt to your system
			LCD_WriteComm(0x2A);
			LCD_WriteData_8bit(xPhys>>8);
			LCD_WriteData_8bit(xPhys&0xFF);
			LCD_WriteComm(0x2B);
			LCD_WriteData_8bit((yPhys+TFT_Y_panyi)>>8);
			LCD_WriteData_8bit((yPhys+TFT_Y_panyi)&0xFF);
			LCD_WriteComm(0x2E);
      PixelIndex = LCD_ReadColor_16bit();
      // TBD by customer...
      //
     // PixelIndex = 0;
    }
    #if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
      #undef xPhys
      #undef yPhys
    #endif
  return PixelIndex;
}

/*********************************************************************
*
*       _XorPixel
*/
static void _XorPixel(GUI_DEVICE * pDevice, int x, int y) {
  LCD_PIXELINDEX PixelIndex;
  LCD_PIXELINDEX IndexMask;

  PixelIndex = _GetPixelIndex(pDevice, x, y);
  IndexMask  = pDevice->pColorConvAPI->pfGetIndexMask();
  _SetPixelIndex(pDevice, x, y, PixelIndex ^ IndexMask);
}

/*********************************************************************
*
*       _FillRect
*/
static void _FillRect(GUI_DEVICE * pDevice, int x0, int y0, int x1, int y1) {
	#if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
			int x0Phys, y0Phys, x1Phys, y1Phys;

            x0Phys = LOG2PHYS_X(x0, y0);
            y0Phys = LOG2PHYS_Y(x0, y0);
            x1Phys = LOG2PHYS_X(x1, y1);
            y1Phys = LOG2PHYS_Y(x1, y1);
        #else
            #define x0Phys x0
            #define y0Phys y0
            #define x1Phys x1
            #define y1Phys y1
        #endif

  LCD_PIXELINDEX PixelIndex;
  int x,i;
  PixelIndex = LCD__GetColorIndex();
  if (GUI_pContext->DrawMode & LCD_DRAWMODE_XOR) {
		x=x1Phys-x0Phys;
		for (; y0Phys <= y1Phys; y0Phys++) {
			GUI_Read_BUFF_Dot(hMem0,x0Phys,y0Phys,x1Phys,y0Phys);
			LCD_Write_Window(x0Phys,y0Phys);
      for (i = 0; i <= x; i++) {
				hMem0[i]^=pDevice->pColorConvAPI->pfGetIndexMask();
				LCD_WriteData_16bit(hMem0[i]);
      }
    }
//    for (; y0 <= y1; y0++) {
//      for (x = x0; x <= x1; x++) {
//        _XorPixel(pDevice, x, y0);
//      }
//    }
  } else {
//    for (; y0 <= y1; y0++) {
//      for (x = x0; x <= x1; x++) {
//        _SetPixelIndex(pDevice, x, y0, PixelIndex);
//      }
//    }
        GUI_USE_PARA(x0);
        GUI_USE_PARA(y0);
        GUI_USE_PARA(x1);
        GUI_USE_PARA(y1);
        PixelIndex = LCD__GetColorIndex();
        GUI_USE_PARA(PixelIndex);
        {
					for (; y0Phys <= y1Phys; y0Phys++) {
						LCD_Write_Window(x0Phys,y0Phys);
						for (x=x0Phys; x <= x1Phys; x++) {
							LCD_WriteData_16bit(PixelIndex);
						}
					}
        }
        #if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
            #undef x0Phys
            #undef y0Phys
            #undef x1Phys
            #undef y1Phys
        #endif
  }
}

/*********************************************************************
*
*       _DrawHLine
*/
static void _DrawHLine(GUI_DEVICE * pDevice, int x0, int y, int x1) {
  _FillRect(pDevice, x0, y, x1, y);
}

/*********************************************************************
*
*       _DrawVLine, not optimized
*/
static void _DrawVLine(GUI_DEVICE * pDevice, int x, int y0, int y1) {
  _FillRect(pDevice, x, y0, x, y1);
}


/*********************************************************************
*
*       Draw Bitmap 1 BPP
*/
static void _DrawBitLine1BPP(GUI_DEVICE * pDevice, int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX IndexMask, Index0, Index1;
	u8	B=1;
	u16	i=0;
	#if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
      int xPhys, yPhys;

      xPhys = LOG2PHYS_X(x, y);
      yPhys = LOG2PHYS_Y(x, y);
    #else
      #define xPhys x
      #define yPhys y
    #endif
    GUI_USE_PARA(pDevice);
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);

  Index0 = *(pTrans + 0);
  Index1 = *(pTrans + 1);
  x += Diff;
  switch (GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
			LCD_Write_Window(xPhys,yPhys);
    do {
			LCD_WriteData_16bit((*p & (0x80 >> Diff)) ? Index1 : Index0);
      if (++Diff == 8) {
        Diff = 0;
        p++;
      }
    } while (--xsize);
    break;
  case LCD_DRAWMODE_TRANS:
    for(;i<xsize;i++){
      if (*p & (0x80 >> Diff))
			{
				if(B)
				{
					B=0;
					LCD_Write_Window(xPhys,yPhys);
				}
				LCD_WriteData_16bit(Index1);
			}
			else
				B=1;
      x++;
      if (++Diff == 8) {
        Diff = 0;
        p++;
      }
    }
    break;
  case LCD_DRAWMODE_XOR | LCD_DRAWMODE_TRANS:
  case LCD_DRAWMODE_XOR:
    IndexMask = pDevice->pColorConvAPI->pfGetIndexMask();
		GUI_Read_BUFF_Dot(hMem0,xPhys,yPhys,xPhys+xsize-1,yPhys);
		for(;i<xsize;i++)
		{
			if (*p & (0x80 >> Diff)) {
				if(B)
				{
					B=0;
					LCD_Write_Window(xPhys,yPhys);
				}
				LCD_WriteData_16bit(hMem0[i] ^ IndexMask);
      }
			else
				B=1;
      x++;
      if (++Diff == 8) {
        Diff = 0;
        p++;
      }
		}
    break;
  }
	#if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
      #undef xPhys
      #undef yPhys
    #endif
}

/*********************************************************************
*
*       Draw Bitmap 2 BPP
*/
static void  _DrawBitLine2BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels;
  int CurrentPixel, Shift, Index;
	u16	i=0;
	u8	B=1;
	#if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
      int xPhys, yPhys;
			u8	B=1;
      xPhys = LOG2PHYS_X(x, y);
      yPhys = LOG2PHYS_Y(x, y);
    #else
      #define xPhys x
      #define yPhys y
    #endif
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);

  Pixels = *p;
  CurrentPixel = Diff;
  x += Diff;
  switch (GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
		LCD_Write_Window(xPhys,yPhys);
    if (pTrans) {
      do {
        Shift = (3 - CurrentPixel) << 1;
        Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
				LCD_WriteData_16bit(*(pTrans + Index));
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
      } while (--xsize);
    } else {
      do {
        Shift = (3 - CurrentPixel) << 1;
				LCD_WriteData_16bit((Pixels & (0xC0 >> (6 - Shift))) >> Shift);
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
      } while (--xsize);
    }
    break;
  case LCD_DRAWMODE_TRANS:
    if (pTrans) {
      for(;i<xsize;i++)
			{
        Shift = (3 - CurrentPixel) << 1;
        Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        if (Index) {
					if(B)
					{
						B=0;
						LCD_Write_Window(xPhys,yPhys);
					}
					LCD_WriteData_16bit(*(pTrans + Index));
				}
				else
					B=1;

        x++;
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
      }
    } else {
       for(;i<xsize;i++){
        Shift = (3 - CurrentPixel) << 1;
        Index = (Pixels & (0xC0 >> (6 - Shift))) >> Shift;
        if (Index) {
					if(B)
					{
						B=0;
						LCD_Write_Window(xPhys,yPhys);
					}
					LCD_WriteData_16bit(Index);
        }
				else
					B=1;
        x++;
        if (++CurrentPixel == 4) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
      }
    }
    break;
  }
	 #if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
        #undef x0Phys
        #undef y0Phys
        #undef x1Phys
        #undef y1Phys
    #endif
}

/*********************************************************************
*
*       Draw Bitmap 4 BPP
*/
static void  _DrawBitLine4BPP(int x, int y, U8 const GUI_UNI_PTR * p, int Diff, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixels;
  int CurrentPixel, Shift, Index;
	u16	i=0;
	u8	B=1;
	#if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
      int xPhys, yPhys;
			u8	B=1;
      xPhys = LOG2PHYS_X(x, y);
      yPhys = LOG2PHYS_Y(x, y);
    #else
      #define xPhys x
      #define yPhys y
    #endif
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);

  Pixels = *p;
  CurrentPixel = Diff;
  x += Diff;
  switch (GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
		LCD_Write_Window(xPhys,yPhys);
    if (pTrans) {
      do {
        Shift = (1 - CurrentPixel) << 2;
        Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
				LCD_WriteData_16bit(*(pTrans + Index));
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
      } while (--xsize);
    } else {
      do {
        Shift = (1 - CurrentPixel) << 2;
				LCD_WriteData_16bit((Pixels & (0xF0 >> (4 - Shift))) >> Shift);
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
      } while (--xsize);
    }
    break;
  case LCD_DRAWMODE_TRANS:
    if (pTrans) {
      for(;i<xsize;i++){
        Shift = (1 - CurrentPixel) << 2;
        Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        if (Index) {
					if(B)
					{
						B=0;
						LCD_Write_Window(xPhys,yPhys);
					}
					LCD_WriteData_16bit(*(pTrans + Index));
        }
        x++;
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
      }
    } else {
      for(;i<xsize;i++){
        Shift = (1 - CurrentPixel) << 2;
        Index = (Pixels & (0xF0 >> (4 - Shift))) >> Shift;
        if (Index) {
					if(B)
					{
						B=0;
						LCD_Write_Window(xPhys,yPhys);
					}
					LCD_WriteData_16bit(Index);
        }
				else
					B=1;
        x++;
        if (++CurrentPixel == 2) {
          CurrentPixel = 0;
          Pixels = *(++p);
        }
      }
    }
    break;
  }
	 #if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
        #undef x0Phys
        #undef y0Phys
        #undef x1Phys
        #undef y1Phys
    #endif
}

/*********************************************************************
*
*       Draw Bitmap 8 BPP
*/
static void  _DrawBitLine8BPP(int x, int y, U8 const GUI_UNI_PTR * p, int xsize, const LCD_PIXELINDEX * pTrans) {
  LCD_PIXELINDEX Pixel;
	u16	i=0;
	u8	B=1;
	#if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
      int xPhys, yPhys;
			u8	B=1;
      xPhys = LOG2PHYS_X(x, y);
      yPhys = LOG2PHYS_Y(x, y);
    #else
      #define xPhys x
      #define yPhys y
    #endif
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);

  switch (GUI_pContext->DrawMode & (LCD_DRAWMODE_TRANS | LCD_DRAWMODE_XOR)) {
  case 0:
		LCD_Write_Window(xPhys,yPhys);
    if (pTrans) {
      for (; xsize > 0; xsize--, x++, p++) {
				LCD_WriteData_16bit(*(pTrans + *p));
      }
    } else {
      for (; xsize > 0; xsize--, x++, p++) {
				LCD_WriteData_16bit(*p);
      }
    }
    break;
  case LCD_DRAWMODE_TRANS:
    if (pTrans) {
      for (; i < xsize; i++, x++, p++) {
        Pixel = *p;
        if (Pixel) {
					if(B)
					{
						B=0;
						LCD_Write_Window(xPhys,yPhys);
					}
					LCD_WriteData_16bit(*(pTrans + Pixel));
        }
				else
					B=1;
      }
    } else {
      for (; i < xsize; i++, x++, p++) {
        Pixel = *p;
        if (Pixel) {
					if(B)
					{
						B=0;
						LCD_Write_Window(xPhys,yPhys);
					}
					LCD_WriteData_16bit(Pixel);
        }
				else
					B=1;
      }
    }
    break;
  }
	 #if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
        #undef x0Phys
        #undef y0Phys
        #undef x1Phys
        #undef y1Phys
    #endif
}

/*********************************************************************
*
*       Draw Bitmap 16 BPP, not optimized
*
* Purpose:
*   Drawing of 16bpp high color bitmaps.
*   Only required for 16bpp color depth of target. Should be removed otherwise.
*/
//static void _DrawBitLine16BPP(GUI_DEVICE * pDevice, int x, int y, U16 const GUI_UNI_PTR * p, int xsize) {
static void _DrawBitLine16BPP(int x, int y, U16 const GUI_UNI_PTR * p, int xsize) {
//  for (;xsize > 0; xsize--, x++, p++) {
//    _SetPixelIndex(pDevice, x, y, *p);
//  }

    #if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
        int x0Phys, y0Phys, x1Phys, y1Phys;

        x0Phys = LOG2PHYS_X(x, y);
        y0Phys = LOG2PHYS_Y(x, y);
    #else
        #define x0Phys x
        #define y0Phys y
    #endif
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);
    {
				LCD_Write_Window(x0Phys,y0Phys);
				for(;xsize > 0; xsize--)
				{
					LCD_WriteData_16bit(*p);
					p++;
				}
    }
    #if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
        #undef x0Phys
        #undef y0Phys
    #endif
}

/*********************************************************************
*
*       Draw Bitmap 32 BPP, not optimized
*
* Purpose:
*   Drawing of 32bpp true color bitmaps.
*   Only required for 32bpp color depth of target. Should be removed otherwise.
*/
static void _DrawBitLine32BPP(int x, int y, U32 const GUI_UNI_PTR * p, int xsize) {
	#if (LCD_MIRROR_X == 1) || (LCD_MIRROR_Y == 1) || (LCD_SWAP_XY == 1)
      int xPhys, yPhys;
      xPhys = LOG2PHYS_X(x, y);
      yPhys = LOG2PHYS_Y(x, y);
    #else
      #define xPhys x
      #define yPhys y
    #endif
    GUI_USE_PARA(x);
    GUI_USE_PARA(y);

	LCD_Write_Window(xPhys,yPhys);
				for(;xsize > 0; xsize--)
				{
					LCD_WriteData_16bit(*p);
					p++;
				}

	 #if (LCD_MIRROR_X == 0) && (LCD_MIRROR_Y == 0) && (LCD_SWAP_XY == 0)
        #undef x0Phys
        #undef y0Phys
        #undef x1Phys
        #undef y1Phys
    #endif
//  for (;xsize > 0; xsize--, x++, p++) {
//    _SetPixelIndex(pDevice, x, y, *p);
//  }
}

/*********************************************************************
*
*       _DrawBitmap
*/
static void _DrawBitmap(GUI_DEVICE * pDevice, int x0, int y0,
                       int xSize, int ySize,
                       int BitsPerPixel,
                       int BytesPerLine,
                       const U8 GUI_UNI_PTR * pData, int Diff,
                       const LCD_PIXELINDEX * pTrans) {
  int i;

  switch (BitsPerPixel) {
  case 1:
    for (i = 0; i < ySize; i++) {
      _DrawBitLine1BPP(pDevice, x0, i + y0, pData, Diff, xSize, pTrans);
      pData += BytesPerLine;
    }
    return;
  case 2:
    for (i = 0; i < ySize; i++) {
      _DrawBitLine2BPP(x0, i + y0, pData, Diff, xSize, pTrans);
      pData += BytesPerLine;
    }
    return;
  case 4:
    for (i = 0; i < ySize; i++) {
      _DrawBitLine4BPP(x0, i + y0, pData, Diff, xSize, pTrans);
      pData += BytesPerLine;
    }
    return;
  case 8:
    for (i = 0; i < ySize; i++) {
      _DrawBitLine8BPP(x0, i + y0, pData, xSize, pTrans);
      pData += BytesPerLine;
    }
    return;
  //
  // Only required for 16bpp color depth of target. Should be removed otherwise.
  //
  case 16:

    for (i = 0; i < ySize; i++) {
      _DrawBitLine16BPP(x0, i + y0, (const U16 *)pData, xSize);
      pData += BytesPerLine;
    }
    return;
  //
  // Only required for 32bpp color depth of target. Should be removed otherwise.
  //
  case 32:
    for (i = 0; i < ySize; i++) {
      _DrawBitLine32BPP( x0, i + y0, (const U32 *)pData, xSize);
      pData += BytesPerLine;
    }
    return;
  }
}

/*********************************************************************
*
*       _InitOnce
*
* Purpose:
*   Allocates a fixed block for the context of the driver
*
* Return value:
*   0 on success, 1 on error
*/
static int _InitOnce(GUI_DEVICE * pDevice) {
  DRIVER_CONTEXT_TEMPLATE * pContext;

  if (pDevice->u.pContext == NULL) {
    pDevice->u.pContext = GUI_ALLOC_GetFixedBlock(sizeof(DRIVER_CONTEXT_TEMPLATE));
    pContext = (DRIVER_CONTEXT_TEMPLATE *)pDevice->u.pContext;
    pContext->BitsPerPixel = LCD__GetBPP(pDevice->pColorConvAPI->pfGetIndexMask());
  }
  return pDevice->u.pContext ? 0 : 1;
}

/*********************************************************************
*
*       _GetDevProp
*/
static I32 _GetDevProp(GUI_DEVICE * pDevice, int Index) {
  DRIVER_CONTEXT_TEMPLATE * pContext;

  pContext = (DRIVER_CONTEXT_TEMPLATE *)pDevice->u.pContext;
  switch (Index) {
  case LCD_DEVCAP_XSIZE:
    return pContext->xSize;
  case LCD_DEVCAP_YSIZE:
    return pContext->ySize;
  case LCD_DEVCAP_VXSIZE:
    return pContext->vxSize;
  case LCD_DEVCAP_VYSIZE:
    return pContext->vySize;
  case LCD_DEVCAP_BITSPERPIXEL:
    return pContext->BitsPerPixel;
  case LCD_DEVCAP_NUMCOLORS:
    return 0;
  case LCD_DEVCAP_XMAG:
    return 1;
  case LCD_DEVCAP_YMAG:
    return 1;
  case LCD_DEVCAP_MIRROR_X:
    return 0;
  case LCD_DEVCAP_MIRROR_Y:
    return 0;
  case LCD_DEVCAP_SWAP_XY:
    return 0;
  }
  return -1;
}

/*********************************************************************
*
*       _GetDevData
*/
static void * _GetDevData(GUI_DEVICE * pDevice, int Index) {
  GUI_USE_PARA(pDevice);
  #if GUI_SUPPORT_MEMDEV
    switch (Index) {
    case LCD_DEVDATA_MEMDEV:
      return (void *)&GUI_MEMDEV_DEVICE_16; // TBD: Has to be adapted to the right memory device depending on the used color depth!
    }
  #else
    GUI_USE_PARA(Index);
  #endif
  return NULL;
}

/*********************************************************************
*
*       _GetRect
*/
static void _GetRect(GUI_DEVICE * pDevice, LCD_RECT * pRect) {
  DRIVER_CONTEXT_TEMPLATE * pContext;

  pContext = (DRIVER_CONTEXT_TEMPLATE *)pDevice->u.pContext;
  pRect->x0 = 0;
  pRect->y0 = 0;
  pRect->x1 = pContext->vxSize - 1;
  pRect->y1 = pContext->vySize - 1;
}

/*********************************************************************
*
*       _SetOrg
*/
static void _SetOrg(GUI_DEVICE * pDevice, int x, int y) {
  LCD_X_SETORG_INFO Data = {0};

  Data.xPos = x;
  Data.yPos = y;
  LCD_X_DisplayDriver(pDevice->LayerIndex, LCD_X_SETORG, (void *)&Data);
}

/*********************************************************************
*
*       Static code: Functions available by _GetDevFunc()
*
**********************************************************************
*/
/*********************************************************************
*
*       _SetVRAMAddr
*/
static void _SetVRAMAddr(GUI_DEVICE * pDevice, void * pVRAM) {
  DRIVER_CONTEXT_TEMPLATE * pContext;
  LCD_X_SETVRAMADDR_INFO Data = {0};

  _InitOnce(pDevice);
  if (pDevice->u.pContext) {
    pContext = (DRIVER_CONTEXT_TEMPLATE *)pDevice->u.pContext;
    pContext->VRAMAddr = (U32)pVRAM;
    Data.pVRAM = pVRAM;
    LCD_X_DisplayDriver(pDevice->LayerIndex, LCD_X_SETVRAMADDR, (void *)&Data);
  }
}

/*********************************************************************
*
*       _SetVSize
*/
static void _SetVSize(GUI_DEVICE * pDevice, int xSize, int ySize) {
  DRIVER_CONTEXT_TEMPLATE * pContext;

  _InitOnce(pDevice);
  if (pDevice->u.pContext) {
    pContext = (DRIVER_CONTEXT_TEMPLATE *)pDevice->u.pContext;
    pContext->vxSize = xSize;
    pContext->vySize = ySize;
    pContext->vxSizePhys = xSize;
  }
}

/*********************************************************************
*
*       _SetSize
*/
static void _SetSize(GUI_DEVICE * pDevice, int xSize, int ySize) {
  DRIVER_CONTEXT_TEMPLATE * pContext;
  LCD_X_SETSIZE_INFO Data = {0};

  _InitOnce(pDevice);
  if (pDevice->u.pContext) {
    pContext = (DRIVER_CONTEXT_TEMPLATE *)pDevice->u.pContext;
    pContext->vxSizePhys = (pContext->vxSizePhys == 0) ? xSize : pContext->vxSizePhys;
    pContext->xSize = xSize;
    pContext->ySize = ySize;
    Data.xSize = xSize;
    Data.ySize = ySize;
    LCD_X_DisplayDriver(pDevice->LayerIndex, LCD_X_SETSIZE, (void *)&Data);
  }
}
/*********************************************************************
*
*       _Init
*/
static int  _Init(GUI_DEVICE * pDevice) {
  int r;

  r = _InitOnce(pDevice);
  r |= LCD_X_DisplayDriver(pDevice->LayerIndex, LCD_X_INITCONTROLLER, NULL);
  return r;
}

/*********************************************************************
*
*       _On
*/
static void _On (GUI_DEVICE * pDevice) {
  LCD_X_DisplayDriver(pDevice->LayerIndex, LCD_X_ON, NULL);
}

/*********************************************************************
*
*       _Off
*/
static void _Off (GUI_DEVICE * pDevice) {
  LCD_X_DisplayDriver(pDevice->LayerIndex, LCD_X_OFF, NULL);
}

/*********************************************************************
*
*       _SetLUTEntry
*/
static void _SetLUTEntry(GUI_DEVICE * pDevice, U8 Pos, LCD_COLOR Color) {
  LCD_X_SETLUTENTRY_INFO Data = {0};

  Data.Pos   = Pos;
  Data.Color = Color;
  LCD_X_DisplayDriver(pDevice->LayerIndex, LCD_X_SETLUTENTRY, (void *)&Data);
}

/*********************************************************************
*
*       _GetDevFunc
*/
static void (* _GetDevFunc(GUI_DEVICE ** ppDevice, int Index))(void) {
  GUI_USE_PARA(ppDevice);
  switch (Index) {
  case LCD_DEVFUNC_SET_VRAM_ADDR:
    return (void (*)(void))_SetVRAMAddr;
  case LCD_DEVFUNC_SET_VSIZE:
    return (void (*)(void))_SetVSize;
  case LCD_DEVFUNC_SET_SIZE:
    return (void (*)(void))_SetSize;
  case LCD_DEVFUNC_INIT:
    return (void (*)(void))_Init;
  case LCD_DEVFUNC_ON:
    return (void (*)(void))_On;
  case LCD_DEVFUNC_OFF:
    return (void (*)(void))_Off;
  case LCD_DEVFUNC_SETLUTENTRY:
    return (void (*)(void))_SetLUTEntry;
  }
  return NULL;
}

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_DEVICE_API structure
*/
const GUI_DEVICE_API GUIDRV_Template_API = {
  //
  // Data
  //
  DEVICE_CLASS_DRIVER,
  //
  // Drawing functions
  //
  _DrawBitmap,
  _DrawHLine,
  _DrawVLine,
  _FillRect,
  _GetPixelIndex,
  _SetPixelIndex,
  _XorPixel,
  //
  // Set origin
  //
  _SetOrg,
  //
  // Request information
  //
  _GetDevFunc,
  _GetDevProp,
  _GetDevData,
  _GetRect,
};

/*************************** End of file ****************************/



