
#ifndef _FLASH_DRIVER_H_
#define _FLASH_DRIVER_H_

#include "main.h"


#define W25X_CMD_WriteEnable 0x06 /*Write enable instruction */
#define W25X_CMD_WriteDisable 0x04 /*! Write to Memory Disable */
#define W25X_CMD_WriteStatusReg 0x01 /* Write Status Register instruction */
 
#define W25X_CMD_PageProgram 0x02 /* Write enable instruction */
#define W25X_CMD_QuadPageProgram 0x32 /* Write enable instruction */
 
#define W25X_CMD_BlockErase64 0xD8 /* Block 64k Erase instruction */
#define W25X_CMD_BlockErase32 0x52 /* Block 32k Erase instruction */
#define W25X_CMD_ChipErase 0xC7 /* Bulk Erase instruction */
#define W25X_CMD_SectorErase 0x20 /* Sector 4k Erase instruction */
#define W25X_CMD_EraseSuspend 0x75 /* Sector 4k Erase instruction */
#define W25X_CMD_EraseResume 0x7a /* Sector 4k Erase instruction */
 
#define W25X_CMD_ReadStatusReg1 0x05 /* Read Status Register instruction */
#define W25X_CMD_ReadStatusReg2 0x35 /* Read Status Register instruction */
 
#define W25X_CMD_High_Perform_Mode 0xa3
#define W25X_CMD_Conti_Read_Mode_Ret 0xff
 
#define W25X_WakeUp 					0xAB
#define W25X_JedecDeviveID 		0x9F /*Read identification */
#define W25X_ManufactDeviveID 0x90 /* Read identification */  
#define W25X_ReadUniqueID 		0x4B 
 
#define W25X_Power_Down 0xB9 /*Sector 4k Erase instruction */
 
#define W25X_CMD_ReadData 0x03 /* Read from Memory instruction */
#define W25X_CMD_FastRead 0x0b /* Read from Memory instruction */
#define W25X_CMD_FastReadDualOut 0x3b /*Read from Memory instruction */
#define W25X_CMD_FastReadDualIO 0xBB /* Read from Memory instruction */
#define W25X_CMD_FastReadQuadOut 0x6b /* Read from Memory instruction */
#define W25X_CMD_FastReadQuadIO 0xeb /* Read from Memory instruction */
#define W25X_CMD_OctalWordRead 0xe3 /* Read from Memory instruction */
 
#define W25X_DUMMY_BYTE 0xff
#define W25X_SPI_PAGESIZE 0x100



#define W25Q80_SECTOR_SIZE 4096
#define FT25H04_SECTOR_SIZE 256 //


//FLASH��ʼ��
extern	void Flash_Init(void);
	//�������ģʽ
extern	void SPI_Flash_PowerDown(void);
	//�˳�����ģʽ
extern	void SPI_Flash_WAKEUP(void);
	//��������
extern	void W25QXX_Erase_Sector(u32  Dst_Addr); 
	//��WriteAddr��д��pBuffer
extern	void SPI_Flash_WritePageData8(u32  WriteAddr,u8  pBuffer);
	//��WriteAddr��д��pBuffer
extern	void SPI_Flash_WritePageData16(u32  WriteAddr,u16  pBuffer);
	//��WriteAddr��д��pBuffer
extern	void SPI_Flash_WritePageData32(u32  WriteAddr,u32  pBuffer);
	//��ReadAddr������
extern	u8 SPI_Flash_Read_PageData8(u32  ReadAddr);
	//��ReadAddr������
extern	u16 SPI_Flash_Read_PageData16(u32  ReadAddr);
	//��ReadAddr������
extern	u32 SPI_Flash_Read_PageData32(u32  ReadAddr);

	//��FLASH,WriteAddr��ַ������дLength����TX_Buff
extern	void	SPI_Flash_Write_BuffData8(u32	WriteAddr,u8* TX_Buff,u32	Length);
extern	void	SPI_Flash_Write_BuffData16(u32	WriteAddr,u16* TX_Buff,u32	Length);
extern	void	SPI_Flash_Write_BuffData32(u32	WriteAddr,u32* TX_Buff,u32	Length);
extern	void	SPI_Flash_Write_BuffData_OK(void);

	//��FLASH,WriteAddr��ַ��������Length����RX_Buff
extern	void	SPI_Flash_Read_BuffData8(u32	ReadAddr,u8* RX_Buff,u32	Length);
extern	void	SPI_Flash_Read_BuffData16(u32	ReadAddr,u16* RX_Buff,u32	Length);
extern	void	SPI_Flash_Read_BuffData32(u32	ReadAddr,u32* RX_Buff,u32	Length);
extern	void	SPI_Flash_Read_BuffData_OK(void);


#endif


