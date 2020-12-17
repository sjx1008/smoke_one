#include "main_2.h"
#include "adc.h"


//总电池电压计算
u16	ReadBATz_Data(void)
{
	u16	d1,d2;
	s16	d3;
	d1=ADC_TDx_Data(ADC_BAT1GPIO);
	d2=ADC_TDx_Data(ADC_BATGPIO);
	R_BAT_L_Real=JS_BAT1(d1)*R_Batt1_JZ_Data/1000;
	R_BATZ_Real=JS_BATZ(d2)*R_BattZ_JZ_Data/1000;
	d3=R_BATZ_Real-R_BAT_L_Real;
	if(d3<0)
		d3=0;
	R_BAT_H_Real=d3;
	if(R_BAT_L_Real>R_BAT_H_Real)
	{
		R_BAT_MAX_Real=R_BAT_L_Real;
		return R_BAT_H_Real;
	}
	else
	{
		R_BAT_MAX_Real=R_BAT_H_Real;
		return R_BAT_L_Real;
	}
}

//PCB温度计算
s16 ReadTemp_Data(void)
{
	u16	a;
	a=ADC_TDx_Data(LL_ADC_CHANNEL_TEMPSENSOR);
	//return JS_CPUTempC(ADC_TDx_Data(LL_ADC_CHANNEL_TEMPSENSOR));
	return	(((((int32_t)((((a) * (VREFANALOG_VOLTAGE))/ __LL_ADC_DIGITAL_SCALE(ADC_RESOLUTION))* 1000)-(int32_t)(((TEMPSENSOR_TYP_CALX_V))* 1000))) / (TEMPSENSOR_TYP_AVGSLOPE)) + (TEMPSENSOR_CALX_TEMP));
}

//输出电压计算
u16 Read_outV_Data(void)
{
	return JS_outV(ADC_TDx_Data(ADC_VoutGPIO));
}

//输出电流计算
u16 Read_outI_Data(void)
{
	return JS_outI(ADC_TDx_Data(ADC_IoutGPIO));
}
u16 Read_outI_Data_1C(void)
{
	return JS_outI(ADC_TDx_Data_1C(ADC_IoutGPIO));
}
//负载电阻计算
u32	R_ReadLoad_outV;
u32	R_ReadLoad_outI;
u16 ReadLoad_Data(void)
{
	u32	a;
	u32	b;
	u32	c;
	u32 data1;
	R_ReadLoad_outV=ADC_TDx_Data(ADC_VoutGPIO);
	R_ReadLoad_outI=ADC_TDx_Data(ADC_IoutGPIO);
	if(R_ReadLoad_outI==0)
	{
		data1=20000;
	}
	else
	{
		data1=R_ReadLoad_outV*200/R_ReadLoad_outI;
	}

	if(data1>6000)
		data1=20000;

	R_ReadLoad_outI=JS_outI(R_ReadLoad_outI);
	a=JS_outV(R_ReadLoad_outV);
	b=a-R_ReadLoad_outI*3/2000;
	c=a*10/11;
	if(c>b)
		R_ReadLoad_outV=c;
	else
		R_ReadLoad_outV=b;
	if((s32)R_ReadLoad_outV<0)
		R_ReadLoad_outV=0;

	return (u16)(data1);
}

u16 Read_PCB_ADC(void)
{
  return ADC_TDx_Data(ADC_PCBTempGPIO);
}

//USB端电压计算
u16 Read_USBV_Data(void)
{
	return JS_USBV(ADC_TDx_Data(ADC_USBGPIO));
}
//充电电流计算
u16 Read_ChargIV_Data(void)
{
	return JS_ChargI(ADC_TDx_Data(ADC_ChargIGPIO));
}

//VCC电压计算
u16 Read_VCC_Data(void)
{
	#if 1
	u16	R;
	R=ADC_TDx_Data(LL_ADC_CHANNEL_VREFINT);
	if(R<1228)
		return	400;
	else
		return JS_VCC_Voltage(R);
	#endif
	//return	330;
}

//光敏二极管ADC
u16 Read_LUX_Data(void)
{
	//return	ADC_TDx_Data(ADC_LUXGPIO);
	return 0;
}



