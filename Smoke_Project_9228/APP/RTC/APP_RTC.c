#include "APP_RTC.h"
#include "main_2.h"

//////当前RTC所使用的时钟源
RTC_Clock_type	RTC_Clock;

LL_RTC_TimeTypeDef RTC_Time;			//实际时间
LL_RTC_DateTypeDef RTC_Date;			//实际日期
LL_RTC_TimeTypeDef SET_Time;			//设置时间
LL_RTC_DateTypeDef SET_Date;			//设置日期

u8	B_Read_RTC;								//读当前时间标志
u8	RTC_error_LB=30;					//RTC外部时钟停震滤波

uc8	PingnianWeek[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
uc8	RunnianWeek[]={0,31,29,31,30,31,30,31,31,30,31,30,31};


/////计算星期几
WeekDay_TypeDef	Count_WeekDay(LL_RTC_DateTypeDef* R)
{
	s16	R_WeekDay;
	u8	R_Month;
	u16	R_Year;
	u8	c,y;

	R_Year=2000+R->Year;
	R_Month=R->Month;
	if(R_Month<3)
	{
		R_Month+=12;
		R_Year--;
	}
	c=R_Year/100;
	y=R_Year%100;
	R_WeekDay=(c/4)-2*c+(y+y/4)+(13*(R_Month+1)/5)+R->Day-1;
	while(R_WeekDay<0){R_WeekDay+=7;}
	R_WeekDay%=7;
	if(!R_WeekDay)
	{
		R_WeekDay=7;
	}
	return	((WeekDay_TypeDef)R_WeekDay);
}



////设置日期
void	Set_RTC_DateTime(LL_RTC_DateTypeDef* R1,LL_RTC_TimeTypeDef* R2)
{
//	RTC_DateTypeDef RTC_DateStructure;
	if(R1->Year>99 || R1->Month>12 || R1->Day>31)
		return;
	if(R2->Hours>23 || R2->Minutes>59 || R2->Seconds>59)
		return;
	if((R1->Year)%4)
	{
		if(R1->Day>PingnianWeek[R1->Month])
			return;
	}
	if(R2->Hours>12)
	{
		R2->TimeFormat=LL_RTC_TIME_FORMAT_PM;
	}
	else
	{
		R2->TimeFormat=LL_RTC_TIME_FORMAT_AM_OR_24;
	}
	R1->WeekDay=Count_WeekDay(R1);
	LL_RTC_DATE_Init(RTC,LL_RTC_FORMAT_BIN,R1);
	LL_RTC_TIME_Init(RTC,LL_RTC_FORMAT_BIN,R2);
	B_Read_RTC=1;
	RTC_error_LB=30;
}


void RTC_TimeRegulate(void)
{
	u8	max;
	if(RTC_Date.Year<d_Firmware_Year || RTC_Date.Year>99)
	{
		RTC_Date.Year=d_Firmware_Year;
		RTC_Date.Month=d_Firmware_Month;
		RTC_Date.Day=d_Firmware_Date;
	}
	else	if(RTC_Date.Year==d_Firmware_Year)
	{
		if(RTC_Date.Month<d_Firmware_Month || RTC_Date.Month>12)
		{
			RTC_Date.Month=d_Firmware_Month;
			RTC_Date.Day=d_Firmware_Date;
		}
		else
		{
			if(RTC_Date.Year%4)
			{
				max=PingnianWeek[RTC_Date.Month];
			}
			else
			{
				max=RunnianWeek[RTC_Date.Month];
			}
			if(RTC_Date.Month==d_Firmware_Month)
			{
				if(RTC_Date.Day<d_Firmware_Date || RTC_Date.Day>max)
				{
					RTC_Date.Day=d_Firmware_Date;
				}
			}
			else
			{
				if(RTC_Date.Day<1 || RTC_Date.Day>max)
				{
					RTC_Date.Day=1;
				}
			}
		}
	}
	else
	{
		if(RTC_Date.Month<1 || RTC_Date.Month>12)
		{
			RTC_Date.Month=1;
		}
		if(RTC_Date.Year%4)
		{
			max=PingnianWeek[RTC_Date.Month];
		}
		else
		{
			max=RunnianWeek[RTC_Date.Month];
		}
		if(RTC_Date.Day<1 || RTC_Date.Day>max)
		{
			RTC_Date.Day=1;
		}
	}

	if(RTC_Time.Hours>23)
		RTC_Time.Hours=0;
	if(RTC_Time.Minutes>59)
		RTC_Time.Minutes=0;
  /* Set Time hh:mm:ss */
  SET_Time.Hours   = RTC_Time.Hours;
  SET_Time.Minutes = RTC_Time.Minutes;
  SET_Time.Seconds = RTC_Time.Seconds;
	if(SET_Time.Seconds>59)
		SET_Time.Seconds=0;
  /* Set Date Week/Date/Month/Year */
  SET_Date.Day = RTC_Date.Day;
  SET_Date.Month = RTC_Date.Month;
  SET_Date.Year = RTC_Date.Year;
 ////设置日期
	Set_RTC_DateTime(&SET_Date,&SET_Time);
}

void RTC_GetTime(uint32_t RTC_Format, LL_RTC_TimeTypeDef* RTC_TimeStruct)
{
  /* Fill the structure fields with the read parameters */
  RTC_TimeStruct->Hours = LL_RTC_TIME_GetHour(RTC);
  RTC_TimeStruct->Minutes = LL_RTC_TIME_GetMinute(RTC);
  RTC_TimeStruct->Seconds = LL_RTC_TIME_GetSecond(RTC);
  RTC_TimeStruct->TimeFormat = LL_RTC_TIME_GetFormat(RTC);

  /* Check the input parameters format */
  if (RTC_Format == LL_RTC_FORMAT_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_TimeStruct->Hours = __LL_RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Hours);
    RTC_TimeStruct->Minutes = __LL_RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Minutes);
    RTC_TimeStruct->Seconds = __LL_RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Seconds);
  }
}

void RTC_GetDate(uint32_t RTC_Format, LL_RTC_DateTypeDef* RTC_DateStruct)
{
  /* Fill the structure fields with the read parameters */
  RTC_DateStruct->Year = LL_RTC_DATE_GetYear(RTC);
  RTC_DateStruct->Month = LL_RTC_DATE_GetMonth(RTC);
  RTC_DateStruct->Day = LL_RTC_DATE_GetDay(RTC);
  RTC_DateStruct->WeekDay = LL_RTC_DATE_GetWeekDay(RTC);

  /* Check the input parameters format */
  if (RTC_Format == LL_RTC_FORMAT_BIN)
  {
    /* Convert the structure parameters to Binary format */
    RTC_DateStruct->Year = __LL_RTC_CONVERT_BCD2BIN(RTC_DateStruct->Year);
    RTC_DateStruct->Month = __LL_RTC_CONVERT_BCD2BIN(RTC_DateStruct->Month);
    RTC_DateStruct->Day = __LL_RTC_CONVERT_BCD2BIN(RTC_DateStruct->Day);
    RTC_DateStruct->WeekDay = __LL_RTC_CONVERT_BCD2BIN(RTC_DateStruct->WeekDay);
  }
}

/////实时时钟上电初始化
void RTC_int(void)
{
	LL_RTC_InitTypeDef RTC_InitStructure;
	u16	i;
	RTC_Clock=RTC_Clock_LSE;
	/* Enable the PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
	LL_PWR_EnableBkUpAccess();
	if(LL_RTC_BAK_GetRegister(RTC,LL_RTC_BKP_DR1) == 0x5A5A)
	{
		RTC_GetTime(LL_RTC_FORMAT_BIN, &RTC_Time);
		RTC_GetDate(LL_RTC_FORMAT_BIN, &RTC_Date);

		LL_RCC_ForceBackupDomainReset();
		LL_RCC_ReleaseBackupDomainReset();
	}
	/* Allow access to RTC */

	LL_RCC_LSE_Enable();//关闭外部低速外部时钟信号功能 后，PC13 PC14 PC15 才可以当普通IO用。
	/* Wait till LSI is ready */
  i=0;
	while(LL_RCC_LSE_IsReady() != 1)
  {
		i++;
		Delay_Nms(1);
		if(i>500)
		{
			if(LL_RTC_BAK_GetRegister(RTC,LL_RTC_BKP_DR1) != 0xA5A5)
			{
				LL_RTC_BAK_SetRegister(RTC,LL_RTC_BKP_DR1,0xA5A5);
				NVIC_SystemReset();
			}
			else
			{
				RTC_Clock=RTC_Clock_LSI;
				break;
			}
		}
  }
	if(RTC_Clock==RTC_Clock_LSI)
	{
		if(LL_RTC_BAK_GetRegister(RTC,LL_RTC_BKP_DR0) == d_RTC_key)
		{
			RTC_GetTime(LL_RTC_FORMAT_BIN, &RTC_Time);
			RTC_GetDate(LL_RTC_FORMAT_BIN, &RTC_Date);
		}
		LL_RCC_ForceBackupDomainReset();
		LL_RCC_ReleaseBackupDomainReset();
		LL_RTC_BAK_SetRegister(RTC,LL_RTC_BKP_DR1,0xA5A5);
		LL_RCC_LSE_Disable();
		LL_RCC_LSI_Enable();//使能LSI时钟
		i=0;
		while(LL_RCC_LSI_IsReady() != 1)
		{                                              //等待LSI就绪
			i++;
			Delay_Nms(1);
			if(i>500)
			{
				break;
			}
		}
		/* Select the RTC Clock Source */
		LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);

		/* Enable the RTC Clock */
		LL_RCC_EnableRTC();
		/* Wait for RTC APB registers synchronisation */
		LL_RTC_DisableWriteProtection(RTC);
		LL_RTC_WaitForSynchro(RTC);
		LL_RTC_EnableWriteProtection(RTC);

		/* Calendar Configuration */
		RTC_InitStructure.AsynchPrescaler = 99;
		RTC_InitStructure.SynchPrescaler	=  319; /* (32KHz / 100) - 1 = 399*/
		RTC_InitStructure.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
		LL_RTC_Init(RTC, &RTC_InitStructure);
	}
	else
	{
		/* Select the RTC Clock Source */
		LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
		  /* Enable the RTC Clock */
	  LL_RCC_EnableRTC();

	  /* Wait for RTC APB registers synchronisation */
	  LL_RTC_DisableWriteProtection(RTC);
		LL_RTC_WaitForSynchro(RTC);
		LL_RTC_EnableWriteProtection(RTC);

		 /* Configure the RTC data register and RTC prescaler */
		RTC_InitStructure.AsynchPrescaler = d_AsynchPrediv;
		RTC_InitStructure.SynchPrescaler = d_SynchPrediv ;
		RTC_InitStructure.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
		/* Check on RTC init */
		LL_RTC_Init(RTC, &RTC_InitStructure);
	}
	LL_RTC_TS_Disable(RTC);
	if (LL_RTC_BAK_GetRegister(RTC,LL_RTC_BKP_DR0) != d_RTC_key)
  {
    /* RTC configuration  */
   // RTC_Config();
    /* Configure the time&date register */
    RTC_TimeRegulate();
		/* Write BkUp DR0 */
		LL_RTC_BAK_SetRegister(RTC,LL_RTC_BKP_DR0,d_RTC_key);
	}
	B_Read_RTC=1;
	Read_RTC_BIN();
}

//////读取当前时间到设定时间
void	RTCgotoSET(void)
{
	SET_Date=RTC_Date;
	SET_Time=RTC_Time;
//	SET_Date.RTC_Year=RTC_Date.RTC_Year;
//	SET_Date.RTC_Month=RTC_Date.RTC_Month;
//	SET_Date.RTC_Date=RTC_Date.RTC_Date;
//	SET_Time.RTC_Hours=RTC_Time.RTC_Hours;
//	SET_Time.RTC_Minutes=RTC_Time.RTC_Minutes;
//	SET_Time.RTC_Seconds=RTC_Time.RTC_Seconds;
}

void	Read_RTC_BIN(void)
{
	LL_RTC_InitTypeDef RTC_InitStructure;
	u16	i;
	static	u8	Tim_S=0;
	if(B_Read_RTC)
	{
		B_Read_RTC=0;
		RTC_GetTime(LL_RTC_FORMAT_BIN, &RTC_Time);
		RTC_GetDate(LL_RTC_FORMAT_BIN, &RTC_Date);
		if(RTC_Date.WeekDay==0	|| RTC_Date.WeekDay>7)
		{
			RTC_Date.WeekDay=Count_WeekDay(&RTC_Date);
		}
		if(RTC_Date.Month==0	|| RTC_Date.Month>12)
			RTC_Date.Month=1;
		if(RTC_Time.Seconds!=Tim_S)
		{
			RTC_error_LB=30;
			Tim_S=RTC_Time.Seconds;
		}
		else
		{
			if(RTC_error_LB)
				RTC_error_LB--;
			else	if(!B_Out_Yes)
			{
				if(RTC_Clock!=RTC_Clock_LSI)
				{
					RTC_Clock=RTC_Clock_LSI;
					RTC_error_LB=30;
					B_Force_Power_down_save=1;
					RTC_GetTime(LL_RTC_FORMAT_BIN, &RTC_Time);
					RTC_GetDate(LL_RTC_FORMAT_BIN, &RTC_Date);
					LL_RCC_ForceBackupDomainReset();
					LL_RCC_ReleaseBackupDomainReset();
					LL_RTC_BAK_SetRegister(RTC,LL_RTC_BKP_DR0,d_RTC_key);
					LL_RTC_BAK_SetRegister(RTC,LL_RTC_BKP_DR1, 0x5A5A);
					LL_RCC_LSI_Enable();//使能LSI时钟
					i=0;
					while(LL_RCC_LSI_IsReady() != 1)
					{                                              //等待LSI就绪
						i++;
						Delay_Nms(1);
						if(i>500)
						{
							break;
						}
					}
					/* Select the RTC Clock Source */
					LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);

					/* Enable the RTC Clock */
					LL_RCC_EnableRTC();
					/* Wait for RTC APB registers synchronisation */
					LL_RTC_DisableWriteProtection(RTC);
					LL_RTC_WaitForSynchro(RTC);
					LL_RTC_EnableWriteProtection(RTC);

					/* Calendar Configuration */
					RTC_InitStructure.AsynchPrescaler = 99;
					RTC_InitStructure.SynchPrescaler	=  319; /* (32KHz / 100) - 1 = 399*/
					RTC_InitStructure.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
					LL_RTC_Init(RTC, &RTC_InitStructure);
					RTC_TimeRegulate();
				}
			}
		}
	}
}

