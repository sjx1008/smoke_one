
#ifndef __APP_RTC_H
#define __APP_RTC_H
#include	"main.h"

	///////////固件更新日期
	#define		d_Firmware_Year			18
	#define		d_Firmware_Month		9
	#define		d_Firmware_Date			20

	#define		d_Firmware_Hours		8
	#define		d_Firmware_Minutes	49



	#define		d_AsynchPrediv		0x7F
	#define		d_SynchPrediv			0xFF

	#define		d_RTC_key					0x1234

	//////当前RTC所使用的时钟源
	typedef enum
	{
		RTC_Clock_LSI=0,			//内部时钟
		RTC_Clock_LSE,				//外部时钟
	}RTC_Clock_type;
	extern	RTC_Clock_type	RTC_Clock;


	extern	u8	B_Read_RTC;								//读当前时间标志

	extern	uc8	PingnianWeek[];
	extern	uc8	RunnianWeek[];

	extern	LL_RTC_TimeTypeDef RTC_Time;			//实际时间
	extern	LL_RTC_DateTypeDef RTC_Date;			//实际日期
	extern	LL_RTC_TimeTypeDef SET_Time;			//设置时间
	extern	LL_RTC_DateTypeDef SET_Date;			//设置日期

/*星期几---------------------*/
	typedef enum
	{
		Monday 			= 1,
		Tuesday 		= 2,
		Wednesday  	= 3,
		Thursday	  = 4,
		Friday		  = 5,
		Saturday		= 6,
		Sunday		  = 7,
	}WeekDay_TypeDef;


	/////计算星期几
	extern	WeekDay_TypeDef	Count_WeekDay(LL_RTC_DateTypeDef* R);
	extern	void 	RTC_Config(void);
	extern	void 	RTC_TimeRegulate(void);
	extern	void	Set_RTC_DateTime(LL_RTC_DateTypeDef* R1,LL_RTC_TimeTypeDef* R2);
	extern	void 	RTC_int(void);
	extern	void	RTCgotoSET(void);
	extern	void	Read_RTC_BIN(void);
#endif


