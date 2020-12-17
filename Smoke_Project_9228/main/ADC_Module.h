#ifndef		_ADC_Module_
#define		_ADC_Module_

#include "main.h"


//ADC通道选择
#define	ADC_VoutGPIO				LL_ADC_CHANNEL_8
#define	ADC_IoutGPIO				LL_ADC_CHANNEL_1
#define	ADC_CPUTempGPIO			LL_ADC_CHANNEL_TEMPSENSOR
#define	ADC_PCBTempGPIO			LL_ADC_CHANNEL_9
#define	ADC_BATGPIO					LL_ADC_CHANNEL_3
#define	ADC_BAT1GPIO				LL_ADC_CHANNEL_2
#define	ADC_USBGPIO					LL_ADC_CHANNEL_7
#define	ADC_ChargIGPIO			LL_ADC_CHANNEL_4
#define	ADC_LUXGPIO					LL_ADC_CHANNEL_3


//计算放大100倍后的电池电压公式
#define	JS_BAT1(a)	(a*550/4096)
#define	JS_BATZ(a)	(a*990/4096)
//#define	JS_CPUTempC(a)	((332-3330*a/17609)+25)
#define	JS_outV(a)	(a*330/1024)
#define	JS_outI(a)	(a*1650/1024)
#define	JS_USBV(a)		(a*330/2048)
#define	JS_ChargI(a)	(a*330/4096)
#define	JS_VCC_Voltage(a)	(4096*120/a)


/*CPU温度计算参数*/
#define	TEMPSENSOR_TYP_AVGSLOPE		2500
#define	TEMPSENSOR_TYP_CALX_V		760
#define	TEMPSENSOR_CALX_TEMP		25
#define	VREFANALOG_VOLTAGE			3300
#define	ADC_RESOLUTION 				LL_ADC_RESOLUTION_12B


extern	u8 	B_BAT_Jianche;


extern u32	R_ReadLoad_outV;
extern u32	R_ReadLoad_outI;

extern void	ADC_DMA_int(void);
extern 	u16	ADC_TDx_Data(uint32_t ADC_Channel);
extern 	u16	ADC_TDx_Data_1C(uint32_t ADC_Channel);
extern 	u16	ReadBATz_Data(void);
extern 	s16 ReadTemp_Data(void);
extern	u16 Read_outV_Data(void);
extern	u16 Read_outI_Data(void);
extern	u16 ReadLoad_Data(void);
extern	u16 Read_outI_Data_1C(void);
//USB端电压计算
extern	u16 Read_USBV_Data(void);
extern	u16 Read_ChargIV_Data(void);
//VCC电压计算
extern	u16 Read_VCC_Data(void);
//光敏二极管ADC
extern	u16 Read_LUX_Data(void);

/////////////////////SDNT1005X104F4250FTF ////////////////////
#define d_T50  (uint16_t)((uint32_t)(3319*4095)/(3319+10000) )
#define d_T51  (uint16_t)((uint32_t)(3185*4095)/(3185+10000) )
#define d_T52  (uint16_t)((uint32_t)(3058*4095)/(3058+10000) )
#define d_T53  (uint16_t)((uint32_t)(2936*4095)/(2936+10000) )
#define d_T54  (uint16_t)((uint32_t)(2820*4095)/(2820+10000) )
#define d_T55  (uint16_t)((uint32_t)(2709*4095)/(2709+10000) )
#define d_T56  (uint16_t)((uint32_t)(2603*4095)/(2603+10000) )
#define d_T57  (uint16_t)((uint32_t)(2502*4095)/(2502+10000) )
#define d_T58  (uint16_t)((uint32_t)(2405*4095)/(2405+10000) )
#define d_T59  (uint16_t)((uint32_t)(2312*4095)/(2312+10000) )
#define d_T60  (uint16_t)((uint32_t)(2223*4095)/(2223+10000) )
#define d_T61  (uint16_t)((uint32_t)(2139*4095)/(2139+10000) )
#define d_T62  (uint16_t)((uint32_t)(2057*4095)/(2057+10000) )
#define d_T63  (uint16_t)((uint32_t)(1980*4095)/(1980+10000) )
#define d_T64  (uint16_t)((uint32_t)(1905*4095)/(1905+10000) )
#define d_T65  (uint16_t)((uint32_t)(1834*4095)/(1834+10000) )
#define d_T66  (uint16_t)((uint32_t)(1766*4095)/(1766+10000) )
#define d_T67  (uint16_t)((uint32_t)(1701*4095)/(1701+10000) )
#define d_T68  (uint16_t)((uint32_t)(1638*4095)/(1638+10000) )
#define d_T69  (uint16_t)((uint32_t)(1578*4095)/(1578+10000) )
#define d_T70  (uint16_t)((uint32_t)(1521*4095)/(1521+10000) )
#define d_T71  (uint16_t)((uint32_t)(1466*4095)/(1466+10000) )
#define d_T72  (uint16_t)((uint32_t)(1413*4095)/(1413+10000) )
#define d_T73  (uint16_t)((uint32_t)(1362*4095)/(1362+10000) )
#define d_T74  (uint16_t)((uint32_t)(1313*4095)/(1313+10000) )
#define d_T75  (uint16_t)((uint32_t)(1267*4095)/(1267+10000) )
#define d_T76  (uint16_t)((uint32_t)(1222*4095)/(1222+10000) )
#define d_T77  (uint16_t)((uint32_t)(1179*4095)/(1179+10000) )
#define d_T78  (uint16_t)((uint32_t)(1138*4095)/(1138+10000) )
#define d_T79  (uint16_t)((uint32_t)(1098*4095)/(1098+10000) )
#define d_T80  (uint16_t)((uint32_t)(1060*4095)/(1060+10000) )
#define d_T81  (uint16_t)((uint32_t)(1023*4095)/(1023+10000) )
#define d_T82  (uint16_t)((uint32_t)( 988*4095)/( 988+10000) )
#define d_T83  (uint16_t)((uint32_t)( 955*4095)/( 955+10000) )
#define d_T87  (uint16_t)((uint32_t)( 832*4095)/( 832+10000) )
#define d_T88  (uint16_t)((uint32_t)( 804*4095)/( 804+10000) )
#define d_T89  (uint16_t)((uint32_t)( 778*4095)/( 778+10000) )
#define d_T90  (uint16_t)((uint32_t)( 752*4095)/( 752+10000) )
#define d_T91  (uint16_t)((uint32_t)( 727*4095)/( 727+10000) )
#define d_T92  (uint16_t)((uint32_t)( 704*4095)/( 704+10000) )
#define d_T93  (uint16_t)((uint32_t)( 681*4095)/( 681+10000) )
#define d_T94  (uint16_t)((uint32_t)( 659*4095)/( 659+10000) )
#define d_T95  (uint16_t)((uint32_t)( 637*4095)/( 637+10000) )
#define d_T96  (uint16_t)((uint32_t)( 617*4095)/( 617+10000) )
#define d_T97  (uint16_t)((uint32_t)( 597*4095)/( 597+10000) )
#define d_T98  (uint16_t)((uint32_t)( 578*4095)/( 578+10000) )
#define d_T99  (uint16_t)((uint32_t)( 560*4095)/( 560+10000) )

#endif

