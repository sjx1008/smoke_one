#include "APP_Compare.h"

#define		d_COMP_EXTI_LINE		LL_EXTI_LINE_6
#define		d_COMP_GPIO					GPIOA
#define		d_COMP_GPIO_PIN			LL_GPIO_PIN_6


void COMP_ONorOFF(FunctionalState	cmd)
{
	if(cmd==ENABLE)
	{
		LL_EXTI_EnableIT_0_31(d_COMP_EXTI_LINE);
		if(LL_GPIO_IsInputPinSet(d_COMP_GPIO, d_COMP_GPIO_PIN))
			LL_EXTI_GenerateSWI_0_31(d_COMP_EXTI_LINE);
	}
	else
		LL_EXTI_DisableIT_0_31(d_COMP_EXTI_LINE);
}


//////////µç³Ø¿´ÃÅ¹·
u8	B_BAT_COMP_EN=0;

void BAT_COMP_ONorOFF(u8	cmd)
{
//	if(B_BAT_COMP_EN!=cmd)
//	{
//		B_BAT_COMP_EN=cmd;
//		if(B_BAT_COMP_EN==DISABLE)
//		{
//			LL_ADC_Disable(ADC1);
//			LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_0);
//			DMA2->LIFCR=DMA_LIFCR_CFEIF0|DMA_LIFCR_CDMEIF0|DMA_LIFCR_CTEIF0|DMA_LIFCR_CHTIF0|DMA_LIFCR_CTCIF0;
//			LL_ADC_DisableIT_AWD1(ADC1);
//		}
//		else
//		{
//			LL_ADC_EnableIT_AWD1(ADC1);
//		}
//	}
}

