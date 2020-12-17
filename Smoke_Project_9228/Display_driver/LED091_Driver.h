#ifndef __LED091_DRIVER_H
#define __LED091_DRIVER_H
#include "stm32f0xx.h"
#include "Stdint_2.h"
#include "OLED_driver.h"

	#define	NO_DMA						//不用到DMA
	#ifdef	NO_DMA
		#define	OLED_disp_ON			//开启刷新完RAM就立即刷新屏幕
	#endif

	#define		d_OLED_X_Max	64
	#define		d_OLED_Y_Max	128

//////显存长度///////////////
	#define	d_OLEDRAM_X		d_OLED_X_Max
	#define	d_OLEDRAM_Y		(d_OLED_Y_Max/8)
	
	//////旋转方向定义//////////
	typedef enum
	{
		d_Flag  	= 0x00,		//正常
		d_Change 	= 0x01		//旋转180
	}Rotating_TypeDef;
	
	//////正反显示定义/////////
	typedef enum
	{
		d_Normal  	= 0x00,		//正显
		d_Reverse 	= 0x01		//反显
	}Normal_Reverse_TypeDef;	
	
	/*定义显存修改范围---------------------*/		
	#ifdef	NO_DMA
	typedef struct
	{
		s16	i_s;
		s16	i_z;
		s16	Page_s;
		s16	Page_z;
	}Memory_Change;
	extern	Memory_Change		OLED_Change;
	extern	void	Windows_Write(void);
	extern	void	Windows_Write_OFF(void);
	extern	void	Windows_Write_ON(void);
	#endif
	
	/*定义显存------------------------*/
	extern	vu8  R_Disp_RAM[d_OLEDRAM_Y][d_OLEDRAM_X];
	extern	uc8	R_OLED_LightMAX;
	extern	u8	R_OLED_Light;
	extern	u8	R_OLED_Light_Actual;				//实际亮度等级	
	extern	u8	B_OLED_BL;
///////////////////////////////////////////////////// 
	extern	Rotating_TypeDef				Flagzhenf_Change_Set;			//旋转180,0：正，1：180
	extern 	Normal_Reverse_TypeDef		Normal_Reverse;						//正显，//反显

	extern u8	START_HIGH_BIT;
	#define		 Slave_Address 	0x78		// 器件地址
	#define	 	OP_Command  		0x00		//
	#define	 	OP_Data 				0x40  	//
	#define		START_PAGE 			0xB0
	#define 	START_LOW_BIT 	0x00

	extern	void	LED_SPI_GPIO_int(void);
	extern	void 	Write_DisContrast(u8 ADJUST);    //亮度调节
	extern	void	Set_Screen_orientation(Screen_orientation_TypeDef	Fa);
	extern	void	RESET_OLED(void);
	extern	void 	Init_IC(void);
	extern	void	Disp_ON(void);
	extern	void	Disp_OFF(void);
	extern	void	Disp_180(Rotating_TypeDef	R);
	extern	void 	Disp_Normal_Reverse(Normal_Reverse_TypeDef	R);
	
#endif 


