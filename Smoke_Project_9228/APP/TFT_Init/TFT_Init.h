#ifndef __TFT_INIT_H__
#define __TFT_INIT_H__
#include "main.h"

///////
#define	d_TFT_MODE_MCU8						//定义接口方式为并口
//#define	d_TFT_MODE_SPI3Line			//定义接口方式为三线方式

#ifdef	d_TFT_MODE_SPI3Line

#define TFT_SCLK_PIN         		LL_GPIO_PIN_13
#define TFT_SCLK_GPIO_PORT			GPIOB
		#define	TFT_SCLK_L()				((*(vu32*)0x40020418)=0x20000000)
		#define	TFT_SCLK_H()				((*(vu32*)0x40020418)=0x2000)

#define TFT_SDA_PIN         		LL_GPIO_PIN_15
#define TFT_SDA_GPIO_PORT				GPIOB
		#define	TFT_SDA_L()					((*(vu32*)0x40020418)=0x80000000)
		#define	TFT_SDA_H()					((*(vu32*)0x40020418)=0x8000)

#define TFT_RESET_PIN         	LL_GPIO_PIN_14
#define TFT_RESET_GPIO_PORT			GPIOB
		#define	TFT_RESET_L()				((*(vu32*)0x40020418)=0x40000000)
		#define	TFT_RESET_H()				((*(vu32*)0x40020418)=0x4000)

#define TFT_NSS_PIN         		LL_GPIO_PIN_12
#define TFT_NSS_GPIO_PORT				GPIOB
		#define	TFT_NSS_L()					((*(vu32*)0x40020418)=0x10000000)
		#define	TFT_NSS_H()					((*(vu32*)0x40020418)=0x1000)

#endif

#ifdef	d_TFT_MODE_MCU8

#define TFT_RESET_PIN         	LL_GPIO_PIN_0
#define TFT_RESET_GPIO_PORT			GPIOH
		#define	TFT_RESET_L()				((*(vu32*)0x40021C18)=0x00010000)
		#define	TFT_RESET_H()				((*(vu32*)0x40021C18)=0x0001)

#define TFT_NSS_PIN         		LL_GPIO_PIN_14
#define TFT_NSS_GPIO_PORT				GPIOB
		#define	TFT_NSS_L()					((*(vu32*)0x40020418)=0x40000000)
		#define	TFT_NSS_H()					((*(vu32*)0x40020418)=0x4000)

#define TFT_DC_PIN       	  		LL_GPIO_PIN_12
#define TFT_DC_GPIO_PORT				GPIOB
		#define	TFT_DC_L()					((*(vu32*)0x40020418)=0x10000000)
		#define	TFT_DC_H()					((*(vu32*)0x40020418)=0x1000)

#define TFT_WR_PIN       	  		LL_GPIO_PIN_13
#define TFT_WR_GPIO_PORT				GPIOB
		#define	TFT_WR_L()					((*(vu32*)0x40020418)=0x20000000)
		#define	TFT_WR_H()					((*(vu32*)0x40020418)=0x2000)

#define TFT_RD_PIN       	  		LL_GPIO_PIN_15
#define TFT_RD_GPIO_PORT				GPIOB
		#define	TFT_RD_L()					((*(vu32*)0x40020418)=0x80000000)
		#define	TFT_RD_H()					((*(vu32*)0x40020418)=0x8000)

#define	SET_TFT_DATA_GPIO					(*(vu8*)0x40020814)
#define	GET_TFT_DATA_GPIO					(*(vu8*)0x40020810)
#define	SET_TFT_DATA_GPIO_OUT()		((*(vu16*)0x40020800)=0x5555)
#define	SET_TFT_DATA_GPIO_IN()		((*(vu16*)0x40020800)=0x0000)
#endif

#define	TFT_Y_panyi		0

////全局变量申明
extern 	u8	R_Screen_brightness;	//设定屏幕亮度
extern 	u8	R_Screen_brightness_NOW;			//当前屏幕亮度
		#define	d_Screen_brightness_MAX		100
///////
extern 	u8	B_OLED_BL;

////发送8位命令
extern 	void	LCD_WriteComm(u8 dat);
///
////发送8位数据
extern 	void	LCD_WriteData_8bit(u8 dat);
////
////发送16位数据
extern 	void	LCD_WriteData_16bit(u16 dat);
/////


////复位IC
extern 	u16	R_LCDRESET_Tim;		//复位高电平保持时间，在定时器里面递减，为0时才能开始写初始化

////发送8位命令
extern 	void	LCD_WriteComm(u8 dat);
	////发送8位数据
extern 	void	LCD_WriteData_8bit(u8 dat);
////发送16位数据
extern 	void	LCD_WriteData_16bit(u16 dat);
////接收16位颜色数据
extern 	u16	LCD_ReadColor_16bit(void);

extern 	void	TFT_LCD_RESET(void);
//屏幕初始化
extern 	void	TFT_ST7789S_Init(void);
//调节背光亮度
extern 	void	TFT_BL_Brightness(u8	PWM);
//设置屏幕亮度
extern 	void	TFT_SET_BL_Brightness(u8	R);

//面板打开显示
extern 	void PanelTurnOnDisplay (void);
//面板关闭显示
extern 	void PanelTurnOffDisplay (void);
//面板打开背光
extern 	void BL_PanelTurnOnDisplay (void);
//面板关闭背光
extern 	void BL_PanelTurnOffDisplay (void);
//灞忓箷鍏抽棴杩囧害锛岀瓑鑳屽厜鍏ㄩ儴鍏抽棴浜嗘墠鍏虫樉绀?
extern 	void	BL_OffDisplay_excessive(void);

#endif









