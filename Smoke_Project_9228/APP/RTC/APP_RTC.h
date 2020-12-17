
#ifndef __APP_RTC_H
#define __APP_RTC_H
#include	"main.h"

	///////////�̼���������
	#define		d_Firmware_Year			18
	#define		d_Firmware_Month		9
	#define		d_Firmware_Date			20

	#define		d_Firmware_Hours		8
	#define		d_Firmware_Minutes	49



	#define		d_AsynchPrediv		0x7F
	#define		d_SynchPrediv			0xFF

	#define		d_RTC_key					0x1234

	//////��ǰRTC��ʹ�õ�ʱ��Դ
	typedef enum
	{
		RTC_Clock_LSI=0,			//�ڲ�ʱ��
		RTC_Clock_LSE,				//�ⲿʱ��
	}RTC_Clock_type;
	extern	RTC_Clock_type	RTC_Clock;


	extern	u8	B_Read_RTC;								//����ǰʱ���־

	extern	uc8	PingnianWeek[];
	extern	uc8	RunnianWeek[];

	extern	LL_RTC_TimeTypeDef RTC_Time;			//ʵ��ʱ��
	extern	LL_RTC_DateTypeDef RTC_Date;			//ʵ������
	extern	LL_RTC_TimeTypeDef SET_Time;			//����ʱ��
	extern	LL_RTC_DateTypeDef SET_Date;			//��������

/*���ڼ�---------------------*/
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


	/////�������ڼ�
	extern	WeekDay_TypeDef	Count_WeekDay(LL_RTC_DateTypeDef* R);
	extern	void 	RTC_Config(void);
	extern	void 	RTC_TimeRegulate(void);
	extern	void	Set_RTC_DateTime(LL_RTC_DateTypeDef* R1,LL_RTC_TimeTypeDef* R2);
	extern	void 	RTC_int(void);
	extern	void	RTCgotoSET(void);
	extern	void	Read_RTC_BIN(void);
#endif


