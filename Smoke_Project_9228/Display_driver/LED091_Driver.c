//****************************����ͷ�ļ�***************************/
#include "stm32f0xx.h"
#include "Stdint_2.h"
#include "APP_Delay.h"
#include "OLED_driver.h"
#include "LED091_Driver.h"



	//-------�������ݶ˿�--------//


	#define	LED_BL_OFF		_nop_()
	//LED_LCDBL_GPIO_PORT->BSRR = LED_LCDBL_PIN 
	#define	LED_BL_ON			_nop_()
	//LED_LCDBL_GPIO_PORT->BRR = LED_LCDBL_PIN


	#define LED_SPI_SCK_PIN               GPIO_Pin_13                     /* PB.03 */
	#define LED_SPI_SCK_GPIO_PORT         GPIOB                          /* GPIOB */
	#define LED_SPI_SCK_GPIO_CLK          RCC_AHBPeriph_GPIOB  
	#define LED_SPI_SCK_SOURCE            GPIO_PinSource13
	#define LED_SPI_SCK_AF                GPIO_AF_0
		#define	SPI_SCK_1		LED_SPI_SCK_GPIO_PORT->BSRR = LED_SPI_SCK_PIN
		#define	SPI_SCK_0		LED_SPI_SCK_GPIO_PORT->BRR = LED_SPI_SCK_PIN
//	#define LED_SPI_CS_PIN              GPIO_Pin_12                    /* PA.15 */
//	#define LED_SPI_CS_GPIO_PORT        GPIOB                         /* GPIOA */
//	#define LED_SPI_CS_GPIO_CLK         RCC_AHBPeriph_GPIOB
//	#define LED_SPI_CS_SOURCE           GPIO_PinSource12
//	#define LED_SPI_CS_AF               GPIO_AF_0

	#define LED_SPI_MOSI_PIN              GPIO_Pin_15                    /* PB.05 */
	#define LED_SPI_MOSI_GPIO_PORT        GPIOB                          /* GPIOB */
	#define LED_SPI_MOSI_GPIO_CLK         RCC_AHBPeriph_GPIOB  
	#define LED_SPI_MOSI_SOURCE           GPIO_PinSource15
	#define LED_SPI_MOSI_AF               GPIO_AF_0
		#define	SPI_MOSI_1		LED_SPI_MOSI_GPIO_PORT->BSRR = LED_SPI_MOSI_PIN
		#define	SPI_MOSI_0		LED_SPI_MOSI_GPIO_PORT->BRR = LED_SPI_MOSI_PIN
		
	#define LED_SPI                       SPI2
	#define LED_SPI_CLK                   RCC_APB1Periph_SPI2


	#define LED_SPI_RS_PIN               GPIO_Pin_12                     /* PB.03 */
	#define LED_SPI_RS_GPIO_PORT         GPIOB                          /* GPIOB */
	#define LED_SPI_RS_GPIO_CLK          RCC_AHBPeriph_GPIOB  
			#define	RS_1	LED_SPI_RS_GPIO_PORT->BSRR = LED_SPI_RS_PIN
			#define	RS_0	LED_SPI_RS_GPIO_PORT->BRR = LED_SPI_RS_PIN 
	
	#define LED_SPI_REST_PIN               GPIO_Pin_14                    /* PB.03 */
	#define LED_SPI_REST_GPIO_PORT         GPIOB                         /* GPIOB */
	#define LED_SPI_REST_GPIO_CLK          RCC_AHBPeriph_GPIOB 
			#define	REST_1	LED_SPI_REST_GPIO_PORT->BSRR = LED_SPI_REST_PIN
			#define	REST_0	LED_SPI_REST_GPIO_PORT->BRR = LED_SPI_REST_PIN 
	
//	#define LED_LCDBL_PIN               GPIO_Pin_9                    /* PB.03 */
//	#define LED_LCDBL_GPIO_PORT         GPIOA                         /* GPIOB */
//	#define LED_LCDBL_GPIO_CLK          RCC_AHBPeriph_GPIOA
		
	#define LED_SendData_8bit(dat)	{*(__IO uint8_t *) 0x4000380C  = dat;while(!((*(__IO uint16_t *) 0x40003808) & SPI_I2S_FLAG_TXE));while((*(__IO uint16_t *) 0x40003808) & SPI_I2S_FLAG_BSY);}
//////����16λ����
	#define LED_SendData_16bit(dat)		LED_SendData_8bit(dat>>8);LED_SendData_8bit(dat&0x00ff)
//-------END--------//

//-------������Ļ����--------//
Rotating_TypeDef				Flagzhenf_Change_Set=d_Flag;			//��ת180,0������1��180
//-------END--------//
		
//-------�������Է���--------//
Normal_Reverse_TypeDef	Normal_Reverse=d_Normal;						//���ԣ�//����
//-------END--------//

//-------�������Է���--------//	
uc8	R_OLED_Light_contrast[]={1,4,8,11,15,18,22,25,29,32,36,39,42,46,49,53,56,60,63,67,70};
#define		R_OLED_contrastMAX		(sizeof(R_OLED_Light_contrast)-1)
uc8	R_OLED_LightMAX=R_OLED_contrastMAX;
u8	R_OLED_Light=R_OLED_LightMAX;				//���ȵȼ�	
u8	R_OLED_Light_Actual;				//ʵ�����ȵȼ�	
//-------END--------//

u8	START_HIGH_BIT;

u8	B_OLED_BL=0;	//����

	#ifdef	NO_DMA
		Memory_Change		OLED_Change;		//���ڸ��·�Χ
	#endif
/*------------�����Դ�--------------*/
vu8  R_Disp_RAM[d_OLEDRAM_Y][d_OLEDRAM_X];  


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void	LED_SPI_GPIO_int(void)
{
		SPI_InitTypeDef    SPI_InitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
	
  /* Enable LED_SPI_SCK_GPIO_CLK, LED_SPI_CS_GPIO_CLK and LED_SPI_MOSI_GPIO_CLK clock */
  RCC_AHBPeriphClockCmd(LED_SPI_SCK_GPIO_CLK | LED_SPI_MOSI_GPIO_CLK, ENABLE);

  /* Configure LED_SPI SCK pin */
  GPIO_InitStructure.GPIO_Pin = LED_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
  
	  /* Configure LED_SPI MOSI pin */
  GPIO_InitStructure.GPIO_Pin = LED_SPI_MOSI_PIN;
  GPIO_Init(LED_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
	
	
  /* Connect PE.13 to SPI SCK */
  GPIO_PinAFConfig(LED_SPI_SCK_GPIO_PORT, LED_SPI_SCK_SOURCE, LED_SPI_SCK_AF);

	/* Connect PE.15 to SPI MOSI */
  GPIO_PinAFConfig(LED_SPI_MOSI_GPIO_PORT, LED_SPI_MOSI_SOURCE, LED_SPI_MOSI_AF);

	//GPIO_PinAFConfig(LED_SPI_CS_GPIO_PORT, LED_SPI_CS_SOURCE, LED_SPI_CS_AF);
	
	/////////////////////////////////////////////////////////////////////////////
  /* Enable SPI and SYSCFG clock  */
	SPI_I2S_DeInit(LED_SPI);
  RCC_APB1PeriphClockCmd(LED_SPI_CLK, ENABLE);
  /* SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;

  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 2;
  SPI_Init(LED_SPI, &SPI_InitStructure);
  
  /* Configure the RX FIFO Threshold to Quarter Full */
	//SPI_RxFIFOThresholdConfig(LED_SPI, SPI_RxFIFOThreshold_QF);
	SPI_BiDirectionalLineConfig(LED_SPI,SPI_Direction_Tx);
  
  /* SPI enable */
  SPI_Cmd(LED_SPI, ENABLE);
    
	////////////////////////////////////////////////////////////////////////////////////////		
		 /* Enable GPIOs clock*/
  RCC_AHBPeriphClockCmd(LED_SPI_RS_GPIO_CLK|LED_SPI_REST_GPIO_CLK, ENABLE);

  /* Configure RS in Output Push-Pull mode */
  GPIO_InitStructure.GPIO_Pin = LED_SPI_RS_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(LED_SPI_RS_GPIO_PORT, &GPIO_InitStructure);
  
  /* Configure REST in Output Push-Pull mode */
  GPIO_InitStructure.GPIO_Pin = LED_SPI_REST_PIN;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(LED_SPI_REST_GPIO_PORT, &GPIO_InitStructure);

  /* Set chip select pin high */
	
}

void _nop_(void)
{
	u8	i=5;
	while(i--);	
}
/**********************************************
//
////����8λ����
//
**********************************************/
void LED_WriteComm(u8 dat)
{
	RS_0;
	LED_SendData_8bit(dat);
//	_nop_();
}

/**********************************************
//
////����8λ����
//
**********************************************/
void LED_WriteData_8bit(u8 dat)
{
	RS_1;
	LED_SendData_8bit(dat);
//	_nop_();
}

/////д���Ⱥ���//////
void Write_DisContrast(u8 ADJUST)    //���ȵ���
{
	R_OLED_Light_Actual=ADJUST;
	LED_WriteComm(0x81);
	LED_WriteComm(R_OLED_Light_contrast[ADJUST]);
	//LED_WriteComm(0xDB);     // Set VCOMH Voltage 
  //LED_WriteComm(R_OLED_Light_VCOM[ADJUST]);
}

void	Disp_180_Command(Rotating_TypeDef	R)
{
	Flagzhenf_Change_Set=R;
	if(R==d_Change)
	{
		LED_WriteComm(0xA1);
		if(B_Screen_orientation==d_Cross_screen)
		{
			LED_WriteComm(0xC8);
			LED_WriteComm(0xD3);
			LED_WriteComm(0x20);
		}
		else if(B_Screen_orientation==d_Vertical_screen)
		{
			LED_WriteComm(0xC0);
			LED_WriteComm(0xD3);
			LED_WriteComm(0x60);
		}
		START_HIGH_BIT=0x12;
	}
	else	if(R==d_Flag)
	{
		LED_WriteComm(0xA0);
		if(B_Screen_orientation==d_Cross_screen)
		{
			LED_WriteComm(0xC0);
			LED_WriteComm(0xD3);
			LED_WriteComm(0x60);
		}
		else if(B_Screen_orientation==d_Vertical_screen)
		{
			LED_WriteComm(0xC8);
			LED_WriteComm(0xD3);
			LED_WriteComm(0x20);
		}
		START_HIGH_BIT=0x10;
	}
}
	
void	Set_Screen_orientation(Screen_orientation_TypeDef	Fa)
{
	B_Screen_orientation=Fa;
	if(B_Screen_orientation==d_Cross_screen)
	{
		R_DISP_windowsMAX.Xz=d_OLED_X_Max-1;
		R_DISP_windowsMAX.Yz=d_OLED_Y_Max-1;
		Disp_180_Command(Flagzhenf_Change_Set);
	}
	else if(B_Screen_orientation==d_Vertical_screen)
	{
		R_DISP_windowsMAX.Xz=d_OLED_Y_Max-1;
		R_DISP_windowsMAX.Yz=d_OLED_X_Max-1;
		Disp_180_Command(Flagzhenf_Change_Set);
	}
}

////��ʾ��ת180��
void 	Disp_180(Rotating_TypeDef	R)
{
	Disp_180_Command(R);
#ifdef	OLED_disp_ON
	OLED_Change.i_s=0;
	OLED_Change.i_z=d_OLEDRAM_X-1;
	OLED_Change.Page_s=0;
	OLED_Change.Page_z=d_OLEDRAM_Y-1;
	Windows_Write();
#endif
}

	
////������ʾָ��
void Disp_Normal_Reverse_Command(Normal_Reverse_TypeDef	R)
{
	Normal_Reverse=R;
	if(R==d_Normal)
	{
		LED_WriteComm(0xA6); /*normal / reverse*/
	}
	else if(R==d_Reverse)
	{
		LED_WriteComm(0xA7); /*normal / reverse*/
	}
}
////������ʾ����
void Disp_Normal_Reverse(Normal_Reverse_TypeDef	R)
{
	Disp_Normal_Reverse_Command(R);
#ifdef	OLED_disp_ON
	OLED_Change.i_s=0;
	OLED_Change.i_z=d_OLEDRAM_X-1;
	OLED_Change.Page_s=0;
	OLED_Change.Page_z=d_OLEDRAM_Y-1;
	Windows_Write();
#endif
}

/******************************************************
//
//��ʼ��IC����
//
******************************************************/
//
//
void	RESET_OLED(void)
{
	Delay_Nms(2);
  REST_1;
  Delay_Nms(2);
  REST_0;
  Delay_Nms(2);
  REST_1;
  Delay_Nms(10);
}
void Init_IC(void)
{
	LED_WriteComm(0xae); // Display OFF
	LED_WriteComm(0xa8); // Set Multiplex Ration
	LED_WriteComm(0x3f);
	LED_WriteComm(0xd5); // Set Frame Frequency
	LED_WriteComm(0x50); // 104Hz

	LED_WriteComm(0xdc); // Set Display Start Line
	LED_WriteComm(0x00);
	LED_WriteComm(0x20); // Set Page Addressing Mode

	LED_WriteComm(0xa4); // Set Entire Display OFF/ON
	LED_WriteComm(0xad); // Set External VPP
	LED_WriteComm(0x8a);
	LED_WriteComm(0xd9); // Set Phase Leghth
	LED_WriteComm(0x1f);
	LED_WriteComm(0xdb); // Set Vcomh voltage
	LED_WriteComm(0x20);

	Disp_180_Command(Flagzhenf_Change_Set);
	Disp_Normal_Reverse_Command(Normal_Reverse);
	Write_DisContrast(R_OLED_Light);
}


/////���ڸ���
#ifdef	NO_DMA

u8	B_Windows_Write_Enable=1;
void	Windows_Write(void)
{
	u8 i,j;
	if(B_Windows_Write_Enable)
	{
		if(OLED_Change.i_s<d_OLEDRAM_X)
		{
			for(j=OLED_Change.Page_s;j<=OLED_Change.Page_z;j++)
			{
				LED_WriteComm(START_PAGE+j);
				LED_WriteComm(START_HIGH_BIT+(OLED_Change.i_s)/16);
				LED_WriteComm(START_LOW_BIT+(OLED_Change.i_s)%16);
				for(i=OLED_Change.i_s;i<=OLED_Change.i_z;i++)
				{
					LED_WriteData_8bit(R_Disp_RAM[j][i]);
				}
			}
			OLED_Change.i_s=d_OLEDRAM_X;
		}  	
	}
}

//������ʾ�ر�
void	Windows_Write_OFF(void)
{
	B_Windows_Write_Enable=0;
}
//������ʾ��
void	Windows_Write_ON(void)
{
	B_Windows_Write_Enable=1;
	Windows_Write();
}
#endif

////��ʾ��
void Disp_ON(void)
{
	LED_BL_ON;
	LED_WriteComm(0xAF); /*display off*/
	B_OLED_BL=1;
}

////��ʾ�ر�
void Disp_OFF(void)
{
	LED_WriteComm(0xAE); /*display off*/
	LED_BL_OFF;
	B_OLED_BL=0;
}




