
#ifndef __Char_Library_H
#define __Char_Library_H

#include "stm32f0xx.h"
#include "Stdint_2.h"

	#define		Font_7_ON
	#define		Font_10_ON
	#define		Font_12_ON
	#define		Font_19_ON


	#ifdef	Font_7_ON
		extern uc8 *const ASCII7[];
	#endif
	
	#ifdef	Font_10_ON
		extern uc8 *const ASCII10[];
	#endif
	
	#ifdef	Font_12_ON
		extern uc8 *const ASCII12[];
	#endif
	
	#ifdef	Font_19_ON
		extern uc8 *const ASCII19[];
	#endif
	

////////////////中文字库/////////////////////

	typedef union 
	{
		uc8		chars[2];
		uc16	ints;
	}zhong_un;
	/*定义中文字符结构体---------------------*/		
	typedef struct
	{
		zhong_un	*zhong;
		uc8			*data;	
	}Chinese_typ;

	#define	Zhong_16_ON
	
	#ifdef	Zhong_16_ON
		extern Chinese_typ *const ZHONG16[];
		#define		ZHONG16_length	40
	#endif

#endif

	
	