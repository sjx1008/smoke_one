#include "stm32f0xx.h"
#include "Stdint_2.h"
#include "stdio.h"
#include "APP_Delay.h"
#include "OLED_driver.h"
#include "TP_I2C.h"

#define	d_DEVICE_ADDRESS		0x70

	typedef union 
	{
		u8 	Ru8[4];
		u16 Ru16[2];
		u32 Ru32;
	}union_32bit;
	
	
void	TP_I2C_GPIOInit(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(I2C_SCK_GPIO_CLK | I2C_SDA_GPIO_CLK | I2C_REST_GPIO_CLK | I2C_INT_GPIO_CLK, ENABLE);

  GPIO_InitStructure.GPIO_Pin = I2C_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(I2C_SCK_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =I2C_REST_PIN;
	GPIO_Init(I2C_REST_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =I2C_SDA_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = I2C_INT_PIN;
	GPIO_Init(I2C_INT_GPIO_PORT, &GPIO_InitStructure);
	
	I2C_SCK_SET;
	I2C_SDA_SET;
	I2C_INT_CLR;
	I2C_REST_SET;

}


void	Delay_NOP(u8 i)
{
	while(i)
	{
		i--;
	}
}

//����IIC��ʼ�ź�
void	IIC_Start(void)
{
	I2C_SDA_SET;
	Delay_NOP(2);
	I2C_SCK_SET;
	Delay_NOP(8);
	I2C_SDA_CLR;
	Delay_NOP(8);
	I2C_SCK_CLR;//ǯסI2C���ߣ�׼�����ͻ�������� 
	Delay_NOP(8);
}	 

//����IICֹͣ�ź�
void	IIC_Stop(void)
{
	I2C_SDA_CLR;//STOP:when CLK is high DATA change form low 
	Delay_NOP(8);
	I2C_SCK_SET; 
	Delay_NOP(8);
	I2C_SDA_SET;//����I2C���߽����ź�	
	Delay_NOP(8);
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8	IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	I2C_SCK_SET; 
	SET_SDA_IN();
	Delay_NOP(8);	//SDA����Ϊ����  
	while(GET_I2C_SDA)
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			return 1;
		}
	}
	I2C_SCK_CLR;//ʱ�����0 	
	SET_SDA_OUT();
	Delay_NOP(8);
	return 0;  
} 

//����ACKӦ��
void	IIC_Ack(u8 AK)
{
	if(AK)
		I2C_SDA_SET;
	else
		I2C_SDA_CLR;
	Delay_NOP(8);
	I2C_SCK_SET;
	Delay_NOP(8);
	I2C_SCK_CLR;
	Delay_NOP(8);
}

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//0����Ӧ��
//1����Ӧ��			  
u8	IIC_Send_Byte(u8 txd)
{                        
	u8 t; 
	for(t=0;t<8;t++)
	{  		
		if(txd&0x80)
			I2C_SDA_SET;
		else
			I2C_SDA_CLR;
		txd<<=1; 
		Delay_NOP(8);	  
		I2C_SCK_SET;
		Delay_NOP(8);
		I2C_SCK_CLR;	
	}	
	Delay_NOP(8);
	return	IIC_Wait_Ack();
} 

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8	IIC_Read_Byte(u8 ack)
{
	u8 i,receive=0;
	SET_SDA_IN();//SDA����Ϊ����
	for(i=0;i<8;i++ )
	{	
		I2C_SCK_SET;
		Delay_NOP(8);
		receive<<=1;
		if(GET_I2C_SDA)
			receive++;
		I2C_SCK_CLR;
		Delay_NOP(8);
	}	
	IIC_Ack(ack);//����nACK
	return receive;
}

//��WriteAddr��ʼ����дLen���ȸ�����
u8	IIC_WriteLen(u8	Addr_Len,u32 WriteAddr,u8 *DataToWrite,u8 Len)
{  	
	u8	i;
	u8	ACK=0;
	union_32bit	Addr;
	Addr.Ru32=WriteAddr;
	IIC_Start();
	ACK|=IIC_Send_Byte(d_DEVICE_ADDRESS);
	if(Addr_Len>2)
	{
		ACK|=IIC_Send_Byte(Addr.Ru8[3]);
		ACK|=IIC_Send_Byte(Addr.Ru8[2]);
	}
	if(Addr_Len>1)
		ACK|=IIC_Send_Byte(Addr.Ru8[1]);
	ACK|=IIC_Send_Byte(Addr.Ru8[0]);
	for(i=0;i<Len;i++)
	{
		ACK|=IIC_Send_Byte(DataToWrite[i]);
		if(ACK)
			break;
	}
	IIC_Stop();
	return	ACK;
}

//��WriteAddr��ʼ������Len���ȸ�����
u8	IIC_ReadLen(u8	Addr_Len,u32 WriteAddr,u8 *DataToWrite,u8 Len)
{  	
	u8	i;
	u8	ACK=0;
	union_32bit	Addr;
	Addr.Ru32=WriteAddr;
	IIC_Start();
	ACK|=IIC_Send_Byte(d_DEVICE_ADDRESS);
	if(Addr_Len>2)
	{
		ACK|=IIC_Send_Byte(Addr.Ru8[3]);
		ACK|=IIC_Send_Byte(Addr.Ru8[2]);
	}
	if(Addr_Len>1)
		ACK|=IIC_Send_Byte(Addr.Ru8[1]);
	ACK|=IIC_Send_Byte(Addr.Ru8[0]);
	IIC_Start();
	ACK|=IIC_Send_Byte(d_DEVICE_ADDRESS|0x01);
	if(!ACK)
	{
		for(i=0;i<Len-1;i++)
		{
			DataToWrite[i]=IIC_Read_Byte(0);
		}
		DataToWrite[i]=IIC_Read_Byte(1);
	}
	IIC_Stop();
	return	ACK;
}

//дһ��Byte
u8	IIC_Write_OneByte8(u8 WriteAddr,u8 Data)
{
	return	IIC_WriteLen(1,WriteAddr,&Data,1);
}
u8	IIC_Write_OneByte16(u16 WriteAddr,u8 Data)
{
	return	IIC_WriteLen(2,WriteAddr,&Data,1);
}
u8	IIC_Write_OneByte32(u32 WriteAddr,u8 Data)
{
	return	IIC_WriteLen(4,WriteAddr,&Data,1);
}

//��һ��Byte
u8	IIC_Read_OneByte8(u8 WriteAddr,u8 *Data)
{
	return	IIC_ReadLen(1,WriteAddr,Data,1);
}
u8	IIC_Read_OneByte16(u16 WriteAddr,u8 *Data)
{
	return	IIC_ReadLen(2,WriteAddr,Data,1);
}
u8	IIC_Read_OneByte32(u32 WriteAddr,u8 *Data)
{
	return	IIC_ReadLen(4,WriteAddr,Data,1);
}

//дN��Byte
u8	IIC_Write_Byte8_N(u8 WriteAddr,u8 *Data,u8 L)
{
	return	IIC_WriteLen(1,WriteAddr,Data,L);
}
u8	IIC_Write_Byte16_N(u16 WriteAddr,u8 *Data,u8 L)
{
	return	IIC_WriteLen(2,WriteAddr,Data,L);
}
u8	IIC_Write_Byte32_N(u32 WriteAddr,u8 *Data,u8 L)
{
	return	IIC_WriteLen(4,WriteAddr,Data,L);
}

//��N��Byte
u8	IIC_Read_Byte8_N(u8 WriteAddr,u8 *Data,u8 L)
{
	return	IIC_ReadLen(1,WriteAddr,Data,L);
}
u8	IIC_Read_Byte16_N(u16 WriteAddr,u8 *Data,u8 L)
{
	return	IIC_ReadLen(2,WriteAddr,Data,L);
}
u8	IIC_Read_Byte32_N(u32 WriteAddr,u8 *Data,u8 L)
{
	return	IIC_ReadLen(4,WriteAddr,Data,L);
}


void	Reset_TP(void)
{  	  
	I2C_REST_SET;
	Delay_Nms(10);
	I2C_REST_CLR;
	Delay_Nms(6);
	I2C_REST_SET;
	Delay_Nms(10);
}	

void	TP_Init(void)
{
	IIC_Write_OneByte8(FT_DEVIDE_MODE,0);
	IIC_Write_OneByte8(FT_ID_G_THGROUP,16);
	IIC_Write_OneByte8(FT_ID_G_PERIODACTIVE,12);
	IIC_Write_OneByte8(0xA4,0x01);
	IIC_Write_OneByte8(0x85,4);
}

void	TP_Sleep(void)
{
	IIC_Write_OneByte8(FT_DEVIDE_MODE,3);
}


