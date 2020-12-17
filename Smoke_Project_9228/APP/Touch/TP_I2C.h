#ifndef __TP_I2C_H__
#define __TP_I2C_H__

#include "stm32f0xx.h"
#include "Stdint_2.h"

///////////////GPIO定义

	#define I2C_SCK_PIN               GPIO_Pin_7              
	#define I2C_SCK_GPIO_PORT         GPIOB                         
	#define I2C_SCK_GPIO_CLK          RCC_AHBPeriph_GPIOB	
		#define	I2C_SCK_SET			I2C_SCK_GPIO_PORT->BSRR = I2C_SCK_PIN
		#define	I2C_SCK_CLR			I2C_SCK_GPIO_PORT->BRR 	= I2C_SCK_PIN  


	#define	I2C_SDA_PIN       				GPIO_Pin_8           
	#define I2C_SDA_GPIO_PORT         GPIOB                        
	#define I2C_SDA_GPIO_CLK          RCC_AHBPeriph_GPIOB
		#define	I2C_SDA_SET			I2C_SDA_GPIO_PORT->BSRR = I2C_SDA_PIN
		#define	I2C_SDA_CLR			I2C_SDA_GPIO_PORT->BRR 	= I2C_SDA_PIN	
		#define    SET_SDA_IN()     I2C_SDA_SET
		#define    SET_SDA_OUT() 		;
		#define    GET_I2C_SDA    	(I2C_SDA_GPIO_PORT->IDR & I2C_SDA_PIN)
		
	#define I2C_REST_PIN     					GPIO_Pin_6         
	#define I2C_REST_GPIO_PORT				GPIOB                         
	#define I2C_REST_GPIO_CLK         RCC_AHBPeriph_GPIOB
		#define	I2C_REST_SET		I2C_REST_GPIO_PORT->BSRR	= I2C_REST_PIN
		#define	I2C_REST_CLR		I2C_REST_GPIO_PORT->BRR 	= I2C_REST_PIN	
		
	#define I2C_INT_PIN               GPIO_Pin_9        
	#define I2C_INT_GPIO_PORT					GPIOB                         
	#define I2C_INT_GPIO_CLK          RCC_AHBPeriph_GPIOB
		#define	I2C_INT_SET			I2C_INT_GPIO_PORT->BSRR	= I2C_INT_PIN
		#define	I2C_INT_CLR			I2C_INT_GPIO_PORT->BRR 	= I2C_INT_PIN	
		#define	GET_I2C_INT			(I2C_INT_GPIO_PORT->IDR & I2C_INT_PIN)
//////////////////////////////////////////////////////////////


//FT6236 ??????? 
#define FT_DEVIDE_MODE          0x00        //FT6236???????
#define FT_REG_NUM_FINGER       0x02        //???????

#define FT_TP1_REG              0X03        //??????????
#define FT_TP2_REG              0X09        //??????????
#define FT_TP3_REG              0X0F        //??????????
#define FT_TP4_REG              0X15        //??????????
#define FT_TP5_REG              0X1B        //??????????  
 
#define FT_ID_G_LIB_VERSION     0xA1        //??        
#define FT_ID_G_MODE            0xA4        //FT6236?????????
#define FT_ID_G_THGROUP         0x80        //??????????
#define FT_ID_G_PERIODACTIVE    0x88        //???????????  
#define Chip_Vendor_ID          0xA3        //??ID(0x36)
#define ID_G_FT6236ID           0xA8        //0x11
//////////////////////////////////////////////////////////

extern	void	Reset_TP(void);
extern	void	TP_I2C_GPIOInit(void);
extern	void	TP_Init(void);
extern	void	TP_Sleep(void);
extern	u8	ite_i2c_read_NULL(u8 reg,u8* data,u32 len);

//写一个Byte
extern	u8	IIC_Write_OneByte8(u8 WriteAddr,u8 Data);
extern	u8	IIC_Write_OneByte16(u16 WriteAddr,u8 Data);
extern	u8	IIC_Write_OneByte32(u32 WriteAddr,u8 Data);

//读一个Byte
extern	u8	IIC_Read_OneByte8(u8 WriteAddr,u8 *Data);
extern	u8	IIC_Read_OneByte16(u16 WriteAddr,u8 *Data);
extern	u8	IIC_Read_OneByte32(u32 WriteAddr,u8 *Data);

//写N个Byte
extern	u8	IIC_Write_Byte8_N(u8 WriteAddr,u8 *Data,u8 L);
extern	u8	IIC_Write_Byte16_N(u16 WriteAddr,u8 *Data,u8 L);
extern	u8	IIC_Write_Byte32_N(u32 WriteAddr,u8 *Data,u8 L);

//读N个Byte
extern	u8	IIC_Read_Byte8_N(u8 WriteAddr,u8 *Data,u8 L);
extern	u8	IIC_Read_Byte16_N(u16 WriteAddr,u8 *Data,u8 L);
extern	u8	IIC_Read_Byte32_N(u32 WriteAddr,u8 *Data,u8 L);

#endif




