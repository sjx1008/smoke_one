/**
  ******************************************************************************
  * File Name          : SPI.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

#include "gpio.h"
#include "dma.h"

/* USER CODE BEGIN 0 */
#define		SPI_READ_Data8_Address		(&(SPI1->DR))
#define		SPI_WRITE_Data8_Address		(&(SPI1->DR))



#define SPI3_Flag_TXE_BSY_RXNE		(*(vu32*)0x40013008)
#define SPI3_TX_RX_Data						(*(vu8*)0x4001300C)
#define SPI3_TransferDirection		(*(vu32*)0x40013000)

#define	d_SPI_IsActiveFlag_TXE()			(SPI3_Flag_TXE_BSY_RXNE&0x00000002)
#define	d_SPI_IsActiveFlag_BSY()			(SPI3_Flag_TXE_BSY_RXNE&0x00000080)
#define	d_SPI_IsActiveFlag_RXNE()			(SPI3_Flag_TXE_BSY_RXNE&0x00000001)
#define	d_SPI_TransmitData8(Data)		(SPI3_TX_RX_Data=Data)
#define	d_SPI_ReceiveData8()					SPI3_TX_RX_Data
#define	d_SPI_SetTransferDirection(a)	(SPI3_TransferDirection=SPI3_TransferDirection&0xFFFF3BFF|a)


//////DMA 3
#define	d_DMA_STREAM_5_DataLength				(*(vu32*)0x4002645C)
#define	d_DMA_SetDataLength_5(a)	(d_DMA_STREAM_5_DataLength=a)
#define	d_DMA_STREAM_5_MemoryAddress		(*(vu32*)0x40026464)
#define	d_DMA_SetMemoryAddress_5(a)		(d_DMA_STREAM_5_MemoryAddress=a)
#define	d_DMA_STREAM_5_Flag							(*(vu32*)0x40026408)
#define	d_DMA_STREAM_5_ClearFlag()			(d_DMA_STREAM_5_Flag=0x0F400000)
#define	d_DMA_STREAM_5_EN								(*(vu32*)0x40026458)
#define	d_DMA_EnableStream_5()		(d_DMA_STREAM_5_EN|=0x01)
#define	d_DMA_DisableStream_5()	(d_DMA_STREAM_5_EN&=0xFFFFFFFE)
#define	d_DMA_STREAM_5_TC								(*(vu32*)0x40026400)
#define	d_DMA_IsActiveFlag_TC5()		(d_DMA_STREAM_5_TC&0x08000000)
#define	d_DMA_STREAM_MemoryIncMode_5		(*(vu32*)0x40026458)
#define	d_DMA_SetMemoryIncMode_5(a)	(d_DMA_STREAM_MemoryIncMode_5=d_DMA_STREAM_MemoryIncMode_5&0xFFFFFBFF|a)

//2
#define	d_DMA_STREAM_0_DataLength				(*(vu32*)0x40026444)
#define	d_DMA_SetDataLength_0(a)	(d_DMA_STREAM_0_DataLength=a)
#define	d_DMA_STREAM_0_MemoryAddress		(*(vu32*)0x4002644C)
#define	d_DMA_SetMemoryAddress_0( a)		(d_DMA_STREAM_0_MemoryAddress=a)
#define	d_DMA_STREAM_0_Flag							(*(vu32*)0x40026408)
#define	d_DMA_STREAM_0_ClearFlag()			(d_DMA_STREAM_0_Flag=0x003D0000)
#define	d_DMA_STREAM_0_EN								(*(vu32*)0x40026440)
#define	d_DMA_EnableStream_0()		(d_DMA_STREAM_0_EN|=0x01)
#define	d_DMA_DisableStream_0()	(d_DMA_STREAM_0_EN&=0xFFFFFFFE)
#define	d_DMA_STREAM_0_TC								(*(vu32*)0x40026400)
#define	d_DMA_IsActiveFlag_TC0()		(d_DMA_STREAM_0_TC&0x00200000)
#define	d_DMA_STREAM_MemoryIncMode_0		(*(vu32*)0x40026440)
#define	d_DMA_SetMemoryIncMode_0(a)	(d_DMA_STREAM_MemoryIncMode_0=d_DMA_STREAM_MemoryIncMode_0&0xFFFFFBFF|a)

u32	B_External_Flash_DMA_Wait=0;
/* USER CODE END 0 */


/* SPI3 init function */
void MX_SPI3_Init(void)
{
  LL_SPI_InitTypeDef SPI_InitStruct;
  LL_DMA_InitTypeDef				DMA_InitStructure;
  LL_GPIO_InitTypeDef GPIO_InitStruct;

  /**SPI3 GPIO Configuration
  PA15   ------> SPI3_NSS
  PC10   ------> SPI3_SCK
  PC11   ------> SPI3_MISO
  PC12   ------> SPI3_MOSI
  */

  GPIO_InitStruct.Pin = LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* SPI3_RX Init */
	LL_SPI_DeInit(SPI1);
	/* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_2EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 10;
  LL_SPI_Init(SPI1, &SPI_InitStruct);
  LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
	LL_SPI_EnableDMAReq_TX(SPI1);
	LL_SPI_EnableDMAReq_RX(SPI1);
	LL_SPI_Enable(SPI1);

  /* SPI3 DMA Init */
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_2);
	LL_DMA_DeInit(DMA2, LL_DMA_STREAM_3);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
	/* SPI3_RX Init */

  DMA_InitStructure.Channel=LL_DMA_CHANNEL_3;												//DMA通道
	DMA_InitStructure.Direction=LL_DMA_DIRECTION_PERIPH_TO_MEMORY;		//外设到内存
	DMA_InitStructure.FIFOMode=LL_DMA_FIFOMODE_DISABLE;
	DMA_InitStructure.FIFOThreshold=LL_DMA_FIFOTHRESHOLD_1_2;
	DMA_InitStructure.MemBurst=LL_DMA_MBURST_SINGLE;
	//DMA_InitStructure.MemoryOrM2MDstAddress=(u32)AD_Value;						//内存地址
	DMA_InitStructure.MemoryOrM2MDstDataSize=LL_DMA_MDATAALIGN_BYTE;	//8位
	DMA_InitStructure.MemoryOrM2MDstIncMode=LL_DMA_MEMORY_INCREMENT;			//内存地址自加1
	DMA_InitStructure.Mode=LL_DMA_MODE_NORMAL;
	//DMA_InitStructure.NbData=DMA_N;
	DMA_InitStructure.PeriphBurst=LL_DMA_PBURST_SINGLE;
	DMA_InitStructure.PeriphOrM2MSrcAddress=(u32)SPI_READ_Data8_Address;
	DMA_InitStructure.PeriphOrM2MSrcDataSize=LL_DMA_MDATAALIGN_BYTE;
	DMA_InitStructure.PeriphOrM2MSrcIncMode=LL_DMA_PERIPH_NOINCREMENT;
	DMA_InitStructure.Priority=LL_DMA_PRIORITY_VERYHIGH;
	LL_DMA_Init(DMA2, LL_DMA_STREAM_2, &DMA_InitStructure);

	/* SPI3_TX Init */
  DMA_InitStructure.Channel=LL_DMA_CHANNEL_3;												//DMA通道
	DMA_InitStructure.Direction=LL_DMA_DIRECTION_MEMORY_TO_PERIPH;		//
	DMA_InitStructure.FIFOMode=LL_DMA_FIFOMODE_DISABLE;
	DMA_InitStructure.FIFOThreshold=LL_DMA_FIFOTHRESHOLD_1_2;
	DMA_InitStructure.MemBurst=LL_DMA_MBURST_SINGLE;
	//DMA_InitStructure.MemoryOrM2MDstAddress=(u32)AD_Value;						//内存地址
	DMA_InitStructure.MemoryOrM2MDstDataSize=LL_DMA_MDATAALIGN_BYTE;	//8位
	DMA_InitStructure.MemoryOrM2MDstIncMode=LL_DMA_MEMORY_NOINCREMENT;			//内存地址自加1
	DMA_InitStructure.Mode=LL_DMA_MODE_NORMAL;
	//DMA_InitStructure.NbData=DMA_N;
	DMA_InitStructure.PeriphBurst=LL_DMA_PBURST_SINGLE;
	DMA_InitStructure.PeriphOrM2MSrcAddress=(u32)SPI_WRITE_Data8_Address;
	DMA_InitStructure.PeriphOrM2MSrcDataSize=LL_DMA_MDATAALIGN_BYTE;
	DMA_InitStructure.PeriphOrM2MSrcIncMode=LL_DMA_PERIPH_NOINCREMENT;
	DMA_InitStructure.Priority=LL_DMA_PRIORITY_LOW;
	LL_DMA_Init(DMA2, LL_DMA_STREAM_3, &DMA_InitStructure);

	//LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_5);
	//LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_0);
	//LL_SPI_Enable(SPI3);

	SPI3_Write_Data8(0xFF);
	/////////////
}

//void	SPI3_NSS_H(void)
//{
//	while(!d_SPI_IsActiveFlag_TXE());
//	while(d_SPI_IsActiveFlag_BSY());
//	SPI3_NSS_GPIO_H();
//}

//void	SPI3_NSS_L(void)
//{
//	while(!d_SPI_IsActiveFlag_TXE());
//	while(d_SPI_IsActiveFlag_BSY());
//	d_SPI_ReceiveData8(SPI3);
//	SPI3_NSS_GPIO_L();
//}
/* USER CODE BEGIN 1 */
//写一个8位数据
void SPI3_Write_Data8(u8	Data)
{
	while((SPI3_Flag_TXE_BSY_RXNE&0x00000082)!=0x00000002);
	d_SPI_TransmitData8(Data);
	while((SPI3_Flag_TXE_BSY_RXNE&0x00000083)!=0x00000003);
	d_SPI_ReceiveData8();
}
//写一个16位数据
void SPI3_Write_Data16(u16	Data)
{
	SPI3_Write_Data8((u8)(Data>>8));
	SPI3_Write_Data8((u8)Data);
}
//写一个24位数据
void SPI3_Write_Data24(u32	Data)
{
	SPI3_Write_Data8((u8)(Data>>16));
	SPI3_Write_Data8((u8)(Data>>8));
	SPI3_Write_Data8((u8)Data);
}
//写一个32位数据
void SPI3_Write_Data32(u32	Data)
{
	SPI3_Write_Data8((u8)(Data>>24));
	SPI3_Write_Data8((u8)(Data>>16));
	SPI3_Write_Data8((u8)(Data>>8));
	SPI3_Write_Data8((u8)Data);
}
//小端写一个16位数据
void SPI3_Write_SmallData16(u16	Data)
{
	SPI3_Write_Data8((u8)Data);
	SPI3_Write_Data8((u8)(Data>>8));
}
//小端写一个24位数据
void SPI3_Write_SmallData24(u32	Data)
{
	SPI3_Write_Data8((u8)Data);
	SPI3_Write_Data8((u8)(Data>>8));
	SPI3_Write_Data8((u8)(Data>>16));
}
//小端写一个32位数据
void SPI3_Write_SmallData32(u32	Data)
{
	SPI3_Write_Data8((u8)Data);
	SPI3_Write_Data8((u8)(Data>>8));
	SPI3_Write_Data8((u8)(Data>>16));
	SPI3_Write_Data8((u8)(Data>>24));
}

//读一个8位数据
u8 SPI3_Read_Data8(void)
{
	while((SPI3_Flag_TXE_BSY_RXNE&0x00000082)!=0x00000002);
	d_SPI_TransmitData8(0xFF);
	while((SPI3_Flag_TXE_BSY_RXNE&0x00000083)!=0x00000003);
	return	d_SPI_ReceiveData8();
}
//读一个16位数据
u16 SPI3_Read_Data16(void)
{
	u16	R;
	R=SPI3_Read_Data8()<<8;
	R|=SPI3_Read_Data8();
	return	R;
}
//读一个24位数据
u32 SPI3_Read_Data24(void)
{
	u32	R;
	R=SPI3_Read_Data8()<<16;
	R|=SPI3_Read_Data8()<<8;
	R|=SPI3_Read_Data8();
	return	R;
}
//读一个32位数据
u32 SPI3_Read_Data32(void)
{
	u32	R;
	R=SPI3_Read_Data8()<<24;
	R|=SPI3_Read_Data8()<<16;
	R|=SPI3_Read_Data8()<<8;
	R|=SPI3_Read_Data8();
	return	R;
}
//小端读一个16位数据
u16 SPI3_Read_SmallData16(void)
{
	u16	R;
	R=SPI3_Read_Data8();
	R|=SPI3_Read_Data8()<<8;
	return	R;
}
//小端读一个24位数据
u32 SPI3_Read_SmallData24(void)
{
	u32	R;
	R=SPI3_Read_Data8();
	R|=SPI3_Read_Data8()<<8;
	R|=SPI3_Read_Data8()<<16;
	return	R;
}
//小端读一个32位数据
u32 SPI3_Read_SmallData32(void)
{
	u32	R;
	R=SPI3_Read_Data8();
	R|=SPI3_Read_Data8()<<8;
	R|=SPI3_Read_Data8()<<16;
	R|=SPI3_Read_Data8()<<24;
	return	R;
}
/*DMA传输方式*/
uc8	NOP_0xFF=0xFF;
u8	NOPTX_0xFF=0xFF;
//SPI	DMA方式发送TX_Buff[] 数据
void	SPI3_DMA_Write_Data8_BUFF(u8* TX_Buff,u32	Length)
{
	while(!d_SPI_IsActiveFlag_TXE());
	while(d_SPI_IsActiveFlag_BSY());
	d_SPI_ReceiveData8();
//	LL_SPI_Disable(SPI1);
	d_DMA_SetDataLength_0(Length);
	d_DMA_SetMemoryAddress_0((u32)&NOPTX_0xFF);
	d_DMA_SetDataLength_5(Length);
	d_DMA_SetMemoryAddress_5((u32)TX_Buff);
	d_DMA_STREAM_0_ClearFlag();
	d_DMA_STREAM_5_ClearFlag();
	d_DMA_SetMemoryIncMode_5(LL_DMA_MEMORY_INCREMENT);
	d_DMA_SetMemoryIncMode_0(LL_DMA_MEMORY_NOINCREMENT);
	d_DMA_EnableStream_0();
	d_DMA_EnableStream_5();
//	LL_SPI_Enable(SPI1);
	B_External_Flash_DMA_Wait=Length;
}
void	SPI3_DMA_Write_OK_Wait(void)
{
	if(B_External_Flash_DMA_Wait)
	{
		B_External_Flash_DMA_Wait=0;
		while(!d_DMA_IsActiveFlag_TC0());
		while(!d_DMA_IsActiveFlag_TC5());
//		while(!d_SPI_IsActiveFlag_TXE());
//		while(d_SPI_IsActiveFlag_BSY());
		d_DMA_DisableStream_5();
		d_DMA_DisableStream_0();
		d_DMA_SetMemoryIncMode_5(LL_DMA_MEMORY_NOINCREMENT);
		d_DMA_SetMemoryIncMode_0(LL_DMA_MEMORY_INCREMENT);
	}
}

//SPI	DMA方式接收RX_Buff[] 数据
void	SPI3_DMA_Read_Data8_BUFF(u8* RX_Buff,u32	Length)
{
	while(!d_SPI_IsActiveFlag_TXE());
	while(d_SPI_IsActiveFlag_BSY());
	d_SPI_ReceiveData8();
//	LL_SPI_Disable(SPI1);
	d_DMA_SetDataLength_0(Length);
	d_DMA_SetMemoryAddress_0((u32)RX_Buff);
	d_DMA_SetDataLength_5(Length);
	d_DMA_SetMemoryAddress_5((u32)&NOP_0xFF);
	d_DMA_STREAM_0_ClearFlag();
	d_DMA_STREAM_5_ClearFlag();
	d_DMA_EnableStream_0();
	d_DMA_EnableStream_5();
//	LL_SPI_Enable(SPI1);
	B_External_Flash_DMA_Wait=Length;
}
void	SPI3_DMA_Read_OK_Wait(void)
{
	if(B_External_Flash_DMA_Wait)
	{
		B_External_Flash_DMA_Wait=0;
		while(!d_DMA_IsActiveFlag_TC0());
		while(!d_DMA_IsActiveFlag_TC5());
//		while(!d_SPI_IsActiveFlag_TXE());
//		while(d_SPI_IsActiveFlag_BSY());
		d_DMA_DisableStream_5();
		d_DMA_DisableStream_0();
	}
}

//SPI	DMA方式收发RX_Buff[]，TX_Buff[] 数据
void	SPI3_DMA_ReadWrite_Data8_BUFF(u8* RX_Buff,u8* TX_Buff,u32	Length)
{
	while(!d_SPI_IsActiveFlag_TXE());
	while(d_SPI_IsActiveFlag_BSY());
	d_SPI_ReceiveData8();
//	LL_SPI_Disable(SPI1);
	d_DMA_SetDataLength_0(Length);
	d_DMA_SetMemoryAddress_0((u32)RX_Buff);
	d_DMA_SetDataLength_5(Length);
	d_DMA_SetMemoryAddress_5((u32)TX_Buff);
	d_DMA_STREAM_0_ClearFlag();
	d_DMA_STREAM_5_ClearFlag();
	d_DMA_SetMemoryIncMode_5(LL_DMA_MEMORY_INCREMENT);
	d_DMA_EnableStream_0();
	d_DMA_EnableStream_5();
//	LL_SPI_Enable(SPI1);
	B_External_Flash_DMA_Wait=Length;
}
void	SPI3_DMA_ReadWrite_OK_Wait(void)
{
	if(B_External_Flash_DMA_Wait)
	{
		B_External_Flash_DMA_Wait=0;
		while(!d_DMA_IsActiveFlag_TC0());
		while(!d_DMA_IsActiveFlag_TC5());
//		while(!d_SPI_IsActiveFlag_TXE());
//		while(d_SPI_IsActiveFlag_BSY());
		d_DMA_DisableStream_5();
		d_DMA_DisableStream_0();
		d_DMA_SetMemoryIncMode_5(LL_DMA_MEMORY_NOINCREMENT);
	}
}
/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
