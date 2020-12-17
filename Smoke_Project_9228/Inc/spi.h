/**
  ******************************************************************************
  * File Name          : SPI.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __spi_H
#define __spi_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_ll_spi.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define		SPI3_NSS_GPIO_H()		((*(vu32*)0x40020C18)=0x00000004)  	//PD2
#define		SPI3_NSS_GPIO_L()		((*(vu32*)0x40020C18)=0x00040000)		//PD2
/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void MX_SPI3_Init(void);

/* USER CODE BEGIN Prototypes */
extern void	SPI3_NSS_H(void);
extern void	SPI3_NSS_L(void);

extern void SPI3_Write_Data8(u8	Data);
//写一个16位数据
extern void SPI3_Write_Data16(u16	Data);
//写一个24位数据
extern void SPI3_Write_Data24(u32	Data);
//写一个32位数据
extern void SPI3_Write_Data32(u32	Data);
//小端写一个16位数据
extern void SPI3_Write_SmallData16(u16	Data);
//小端写一个24位数据
extern void SPI3_Write_SmallData24(u32	Data);
//小端写一个32位数据
extern void SPI3_Write_SmallData32(u32	Data);
//读一个8位数据
extern u8 SPI3_Read_Data8(void);
//读一个16位数据
extern u16 SPI3_Read_Data16(void);
//读一个24位数据
extern u32 SPI3_Read_Data24(void);
//读一个32位数据
extern u32 SPI3_Read_Data32(void);
//小端读一个16位数据
extern u16 SPI3_Read_SmallData16(void);
//小端读一个24位数据
extern u32 SPI3_Read_SmallData24(void);
//小端读一个32位数据
extern u32 SPI3_Read_SmallData32(void);

//SPI	DMA方式发送TX_Buff[] 数据
extern void	SPI3_DMA_Write_Data8_BUFF(u8* TX_Buff,u32	Length);
extern void	SPI3_DMA_Write_OK_Wait(void);

//SPI	DMA方式接收RX_Buff[] 数据
extern void	SPI3_DMA_Read_Data8_BUFF(u8* RX_Buff,u32	Length);
extern void	SPI3_DMA_Read_OK_Wait(void);
//SPI	DMA方式收发RX_Buff[]，TX_Buff[] 数据
extern void	SPI3_DMA_ReadWrite_Data8_BUFF(u8* RX_Buff,u8* TX_Buff,u32	Length);
extern void	SPI3_DMA_ReadWrite_OK_Wait(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ spi_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
