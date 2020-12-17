
#ifndef __APP_CUSTOM_H__
#define __APP_CUSTOM_H__

#include	"main.h"

#include "APP_FLASH.h"


/*定义数据属性---------------------*/
	typedef struct
	{
		u32		Custom_A5A5;
		u16 	CustomCCW_Data[10];
		u16 	CustomCCV_Data[10];
		u16 	CustomCCTSS_C_Data[10];
		u16 	CustomCCTNI_C_Data[10];
		u16 	CustomCCTTI_C_Data[10];
		u16 	CustomCCTSS_F_Data[10];
		u16 	CustomCCTNI_F_Data[10];
		u16 	CustomCCTTI_F_Data[10];
		u32		Custom_CRC;
	}Custom_struct;

typedef union
{
	u8	Custom_byte[168];
	u16	Custom_int[84];
	Custom_struct	Custom_array;
	u32	Custom_int32[42];
}Custom_union;



extern	u8	B_Custom_Hold;
extern	Custom_union R_Custom_BUFF;
extern	const 	FLASH_Structure		R_FLASH_Custom;
extern	void Read_Custom_flash(void);
extern	void Custom_WriteFLASH(void);

#endif


