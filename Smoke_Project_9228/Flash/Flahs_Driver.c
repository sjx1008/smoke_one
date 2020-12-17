#include "Flahs_Driver.h"
#include "main_2.h"
#include "spi.h"

#define		SPI_Flash_NSS_L		SPI3_NSS_GPIO_L
#define		SPI_Flash_NSS_H		SPI3_NSS_GPIO_H

#define		SPI_Flash_Write_Data8					SPI3_Write_Data8
#define		SPI_Flash_Write_Data16				SPI3_Write_Data16
#define		SPI_Flash_Write_Data24				SPI3_Write_Data24
#define		SPI_Flash_Write_Data32				SPI3_Write_Data32
#define		SPI_Flash_Write_SmallData16		SPI3_Write_SmallData16
#define		SPI_Flash_Write_SmallData24		SPI3_Write_SmallData24
#define		SPI_Flash_Write_SmallData32		SPI3_Write_SmallData32

#define		SPI_Flash_Read_Data8					SPI3_Read_Data8
#define		SPI_Flash_Read_Data16					SPI3_Read_Data16
#define		SPI_Flash_Read_Data24					SPI3_Read_Data24
#define		SPI_Flash_Read_Data32					SPI3_Read_Data32
#define		SPI_Flash_Read_SmallData16		SPI3_Read_SmallData16
#define		SPI_Flash_Read_SmallData24		SPI3_Read_SmallData24
#define		SPI_Flash_Read_SmallData32		SPI3_Read_SmallData32

#define		SPI_Flash_Write_Buff			SPI3_DMA_Write_Data8_BUFF
#define		SPI_Flash_Write_Buff_OK		SPI3_DMA_Write_OK_Wait

#define		SPI_Flash_Read_Buff				SPI3_DMA_Read_Data8_BUFF
#define		SPI_Flash_Read_Buff_OK		SPI3_DMA_Read_OK_Wait

#define		SPI_Flash_ReadWrite_Buff				SPI3_DMA_ReadWrite_Data8_BUFF
#define		SPI_Flash_ReadWrite_Buff_OK			SPI3_DMA_ReadWrite_OK_Wait

u16 External_FlashID;


//��ȡFLASH ID��
uint32_t SPI_Flash_ReadID(void);
u8 SPI_Flash_ReadReg(void);
void SPI_Flash_WAKEUP(void);
void SPI_Flash_Write_Disable(void);
//FLASH��ʼ��
void Flash_Init(void)
{
	SPI_Flash_WAKEUP();
	External_FlashID=SPI_Flash_ReadID();
	SPI_Flash_Write_Disable();
}

//��ȡFLASH ID��
uint32_t SPI_Flash_ReadID(void)
{
	u32 ID;
	u8	i;
	for(i=0;i<3;i++)
	{
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_JedecDeviveID);
		SPI_Flash_Write_Data8(0);
		ID=SPI_Flash_Read_Data24();
		SPI_Flash_NSS_H();
		if(ID!=0 && ID!=0x00ffffff)
			break;
	}
	return ID;
}

//�ظ�д������ɱ�־Ϊ
void SPI_Flash_WaitForWriteEnd(void)
{
  while((SPI_Flash_ReadReg()&0x01)==0x01);
}

//����дʹ��
void SPI_Flash_Write_Enable(void)
{
  SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_WriteEnable);
	SPI_Flash_NSS_H();
}
//�ر�дʹ��
void SPI_Flash_Write_Disable(void)
{
  SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_WriteDisable);
	SPI_Flash_NSS_H();
}
//д״̬�Ĵ���
void SPI_Flash_WriteReg(u8	cmd)
{
  SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_ReadStatusReg1);
	SPI_Flash_Write_Data8(cmd);
	SPI_Flash_NSS_H();
}
//��״̬�Ĵ���
u8 SPI_Flash_ReadReg(void)
{
	u8 Data;
  SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_ReadStatusReg1);
	Data = SPI_Flash_Read_Data8();
	SPI_Flash_NSS_H();
	return Data;
}
//�������ģʽ
void SPI_Flash_PowerDown(void)
{
  SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_Power_Down);
	SPI_Flash_NSS_H();
	Delay_Nus(10);
}
//�˳�����ģʽ
void SPI_Flash_WAKEUP(void)
{
	SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_WakeUp);
	SPI_Flash_Write_Data8(W25X_DUMMY_BYTE);
	SPI_Flash_Write_Data8(W25X_DUMMY_BYTE);
	SPI_Flash_Write_Data8(W25X_DUMMY_BYTE);
	SPI_Flash_Read_Data8();
	SPI_Flash_NSS_H();
	Delay_Nus(30);
}
//��������
void W25QXX_Erase_Sector(u32  Dst_Addr)
{
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Enable();   //SET WEL
	SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_SectorErase);
	SPI_Flash_Write_Data24(Dst_Addr);
	SPI_Flash_NSS_H();
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Disable();
}
//��WriteAddr��д��pBuffer
void SPI_Flash_WritePageData8(u32  WriteAddr,u8  pBuffer)
{
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Enable();
	SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
	SPI_Flash_Write_Data24(WriteAddr);
	SPI_Flash_Write_Data8(pBuffer);
	SPI_Flash_NSS_H();
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Disable();
}
//��WriteAddr��д��pBuffer
void SPI_Flash_WritePageData16(u32  WriteAddr,u16  pBuffer)
{
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Enable();
	SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
	SPI_Flash_Write_Data24(WriteAddr);
	SPI_Flash_Write_SmallData16(pBuffer);
	SPI_Flash_NSS_H();
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Disable();
}
//��WriteAddr��д��pBuffer
void SPI_Flash_WritePageData32(u32  WriteAddr,u32  pBuffer)
{
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Enable();
	SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
	SPI_Flash_Write_Data24(WriteAddr);
	SPI_Flash_Write_SmallData32(pBuffer);
	SPI_Flash_NSS_H();
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Disable();
}
//��ReadAddr������
u8 SPI_Flash_Read_PageData8(u32  ReadAddr)
{
	u8	R;
	SPI_Flash_NSS_L();
  SPI_Flash_Write_Data8(W25X_CMD_ReadData);
  SPI_Flash_Write_Data24(ReadAddr);
	R=SPI_Flash_Read_Data8();
  SPI_Flash_NSS_H();
	return R;
}
//��ReadAddr������
u16 SPI_Flash_Read_PageData16(u32  ReadAddr)
{
	u16	R;
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Enable();
	SPI_Flash_NSS_L();
  SPI_Flash_Write_Data8(W25X_CMD_ReadData);
  SPI_Flash_Write_Data24(ReadAddr);
	R=SPI_Flash_Read_SmallData16();
  SPI_Flash_NSS_H();
	return R;
}
//��ReadAddr������
u32 SPI_Flash_Read_PageData32(u32  ReadAddr)
{
	u32	R;
	SPI_Flash_NSS_L();
  SPI_Flash_Write_Data8(W25X_CMD_ReadData);
  SPI_Flash_Write_Data24(ReadAddr);
	R=SPI_Flash_Read_SmallData32();
  SPI_Flash_NSS_H();
	return R;
}

//��FLASH,WriteAddr��ַ������дLength����TX_Buff
void	SPI_Flash_Write_BuffData8(u32	WriteAddr,u8* TX_Buff,u32	Length)
{
	u16	i=0,Surplus,m,a;
	a=256-(WriteAddr%256);
	SPI_Flash_WaitForWriteEnd();
	if(Length>a)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr);
		SPI_Flash_Write_Buff(TX_Buff,a);
		SPI_Flash_Write_Buff_OK();
		SPI_Flash_NSS_H();
		SPI_Flash_WaitForWriteEnd();
		Length-=a;
		TX_Buff+=a;
		WriteAddr+=a;
	}
	m=Length/FT25H04_SECTOR_SIZE;
	Surplus=Length%256;
	for(;i<m;i++)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr+i*256);
		SPI_Flash_Write_Buff(TX_Buff+i*256,256);
		SPI_Flash_Write_Buff_OK();
		SPI_Flash_NSS_H();
		SPI_Flash_WaitForWriteEnd();
	}
	if(Surplus)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr+i*256);
		SPI_Flash_Write_Buff(TX_Buff+i*256,Surplus);
	}
}

void	SPI_Flash_Write_BuffData16(u32	WriteAddr,u16* TX_Buff,u32	Length)
{
	u16	i=0,Surplus,m,a;
	u8* TTX_Buff;
	TTX_Buff=(u8*)TX_Buff;
	Length*=2;
	a=256-(WriteAddr%256);
	SPI_Flash_WaitForWriteEnd();
	if(Length>a)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr);
		SPI_Flash_Write_Buff(TTX_Buff,a);
		SPI_Flash_Write_Buff_OK();
		SPI_Flash_NSS_H();
		SPI_Flash_WaitForWriteEnd();
		Length-=a;
		TTX_Buff+=a;
		WriteAddr+=a;
	}
	m=Length/FT25H04_SECTOR_SIZE;
	Surplus=Length%256;
	for(;i<m;i++)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr+i*256);
		SPI_Flash_Write_Buff(TTX_Buff+i*256,256);
		SPI_Flash_Write_Buff_OK();
		SPI_Flash_NSS_H();
		SPI_Flash_WaitForWriteEnd();
	}
	if(Surplus)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr+i*256);
		SPI_Flash_Write_Buff(TTX_Buff+i*256,Surplus);
	}
}

void	SPI_Flash_Write_BuffData32(u32	WriteAddr,u32* TX_Buff,u32	Length)
{
	u16	i=0,Surplus,m,a;
	u8* TTX_Buff;
	TTX_Buff=(u8*)TX_Buff;
	Length*=4;
	a=256-(WriteAddr%256);
	SPI_Flash_WaitForWriteEnd();
	if(Length>a)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr);
		SPI_Flash_Write_Buff(TTX_Buff,a);
		SPI_Flash_Write_Buff_OK();
		SPI_Flash_NSS_H();
		SPI_Flash_WaitForWriteEnd();
		Length-=a;
		TTX_Buff+=a;
		WriteAddr+=a;
	}
	m=Length/FT25H04_SECTOR_SIZE;
	Surplus=Length%256;
	for(;i<m;i++)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr+i*256);
		SPI_Flash_Write_Buff(TTX_Buff+i*256,256);
		SPI_Flash_Write_Buff_OK();
		SPI_Flash_NSS_H();
		SPI_Flash_WaitForWriteEnd();
	}
	if(Surplus)
	{
		SPI_Flash_Write_Enable();
		SPI_Flash_NSS_L();
		SPI_Flash_Write_Data8(W25X_CMD_PageProgram);//�ֽ�д��
		SPI_Flash_Write_Data24(WriteAddr+i*256);
		SPI_Flash_Write_Buff(TTX_Buff+i*256,Surplus);
	}
}

void	SPI_Flash_Write_BuffData_OK(void)
{
	SPI_Flash_Write_Buff_OK();
	SPI_Flash_NSS_H();
	SPI_Flash_WaitForWriteEnd();
	SPI_Flash_Write_Disable();
}

//��FLASH,WriteAddr��ַ��������Length����RX_Buff
void	SPI_Flash_Read_BuffData8(u32	ReadAddr,u8* RX_Buff,u32	Length)
{
	u16	aa;
	u16	b;
	aa=Length/65535;
	b=Length%65535;
	SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_ReadData);//�ֽ�д��
	SPI_Flash_Write_Data24(ReadAddr);
	for(;aa;aa--)
	{
		SPI_Flash_Read_Buff(RX_Buff,65535);
		RX_Buff+=65535;
		SPI_Flash_Read_Buff_OK();
	}
	if(b)
		SPI_Flash_Read_Buff(RX_Buff,b);
}

void	SPI_Flash_Read_BuffData16(u32	ReadAddr,u16* RX_Buff,u32	Length)
{
	u16	aa;
	u16	b;
	u8* RRX_Buff;
	RRX_Buff=(u8*)RX_Buff;
	Length*=2;
	aa=Length/65535;
	b=Length%65535;
	SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_ReadData);//�ֽ�д��
	SPI_Flash_Write_Data24(ReadAddr);
	for(;aa;aa--)
	{
		SPI_Flash_Read_Buff(RRX_Buff,65535);
		RRX_Buff+=65535;
		SPI_Flash_Read_Buff_OK();
	}
	if(b)
		SPI_Flash_Read_Buff(RRX_Buff,b);
}

void	SPI_Flash_Read_BuffData32(u32	ReadAddr,u32* RX_Buff,u32	Length)
{
	u16	aa;
	u16	b;
	u8* RRX_Buff;
	RRX_Buff=(u8*)RX_Buff;
	Length*=4;
	aa=Length/65535;
	b=Length%65535;
	SPI_Flash_NSS_L();
	SPI_Flash_Write_Data8(W25X_CMD_ReadData);//�ֽ�д��
	SPI_Flash_Write_Data24(ReadAddr);
	for(;aa;aa--)
	{
		SPI_Flash_Read_Buff(RRX_Buff,65535);
		RRX_Buff+=65535;
		SPI_Flash_Read_Buff_OK();
	}
	if(b)
		SPI_Flash_Read_Buff(RRX_Buff,b);
}

void	SPI_Flash_Read_BuffData_OK(void)
{
	SPI_Flash_Read_Buff_OK();
	SPI_Flash_NSS_H();
}
//////////////

