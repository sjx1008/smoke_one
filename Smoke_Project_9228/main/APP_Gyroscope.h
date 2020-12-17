#ifndef __APP_Gyroscope_H
#define __APP_Gyroscope_H
#include "stm32f0xx.h"
#include "Stdint_2.h"

//#define Gyroscope_ENABLE

///////////////GPIO¶¨Òå

	#define G3D_SCK_PIN               GPIO_Pin_11               
	#define G3D_SCK_GPIO_PORT         GPIOB                         
	#define G3D_SCK_GPIO_CLK          RCC_AHBPeriph_GPIOB	
		#define	SCL_ADXL_SET		G3D_SCK_GPIO_PORT->BSRR = G3D_SCK_PIN
		#define	SCL_ADXL_CLR		G3D_SCK_GPIO_PORT->BRR = G3D_SCK_PIN  


	#define	G3D_SDA_PIN               GPIO_Pin_10           
	#define G3D_SDA_GPIO_PORT         GPIOB                        
	#define G3D_SDA_GPIO_CLK          RCC_AHBPeriph_GPIOB
		#define	SDA_ADXL_SET		G3D_SDA_GPIO_PORT->BSRR = G3D_SDA_PIN
		#define	SDA_ADXL_CLR		G3D_SDA_GPIO_PORT->BRR = G3D_SDA_PIN	
		
	#define G3D_END_PIN               		GPIO_Pin_2         
	#define G3D_END_GPIO_PORT							GPIOB                         
	#define G3D_END_GPIO_CLK          		RCC_AHBPeriph_GPIOB
		#define	G3D_END_ON			G3D_END_GPIO_PORT->BSRR 	=	 G3D_END_PIN
		#define	G3D_END_OFF			G3D_END_GPIO_PORT->BRR = G3D_END_PIN	




#define    AccSlaveAddr   0x7a

#define    SDA_ADXL_IN      SDA_ADXL_SET
#define    SDA_ADXL_OUT     ;
#define    SDA_ADXL_READ    (G3D_SDA_GPIO_PORT->IDR & G3D_SDA_PIN)

#define    SCL_ADXL_IN      SCL_ADXL_SET
#define    SCL_ADXL_OUT     ;



extern	u8	B_G3D_JC;
extern	u8	R_Screen_FLIP;
extern  u8   XYZ_data_out[3];

////////////////////////////////////////////////////////////////////
extern    void   STK8312_Init_Setting(void);
extern    void   MCU_I2CDataOutRead(void);
extern    void   Set_Enable(u8 en);
extern    void   ReadAccRegister(unsigned char REG_Address, unsigned char *p);



#endif





