#include "stm32f0xx.h"
#include "Stdint_2.h"
#include <string.h>
#include "TP_I2C.h"
#include "TP_Firmware_update.h"
#include "Firmware_BUFF.h"

#define MAX_BUFFER_SIZE						256

#define QUERY_COMMAND_READY					0x00
#define QUERY_COMMAND_BUSY					0x01
#define QUERY_COMMAND_ERROR					0X02

#define COMMAND_RESPONSE_SUCCESS			0x0000
#define SIGNATURE_LENGTH						16

#define FLASH_HIGH_ADDR						0xD0
#define FLASH_LOW_ADDR						0x00

#define KAL_FALSE							0
#define KAL_TRUE							1
#define NULL								0

#define max_error_count 10

#define CTP_SLAVE_ADDR		(0x8C)

#define COMMAND_BUFFER_INDEX          0x20
#define QUERY_BUFFER_INDEX            0x80
#define COMMAND_RESPONSE_BUFFER_INDEX 0xA0
#define SYSTEM_COMMAND_RESPONSE_INDEX 0xC0
#define POINT_BUFFER_INDEX            0xE0
#define COMMAND_SUCCESS        				0x0000
#define COMMAND_ERROR         				0x0200
#define ERROR_QUERY_TIME_OUT    			0x0800

extern int Upgrade_FW_CFG(void);
extern int Clear_FW_CFG(void);
extern int Reset_IT7259(void);

u8 arucBuffer[1024];

u8 FW_CFG_UPGRADE_NEED = 0x03;

u8 ite_i2c_read(u8 reg,u8* data,u32 len) //ite_i2c_read
{
	int bRet = 0;
	int nErrCount = 0;
	do
	{
		bRet = IIC_Read_Byte8_N(reg, data, len);
	} while((bRet)&&(++nErrCount < max_error_count));

	return !bRet;
}

u8 ite_i2c_read16(u16 reg16,u8 *data,u32 len)  //ite_i2c_read16
{
	int bRet = 0;
	int nErrCount = 0;
	do
	{
		bRet = IIC_Read_Byte16_N(reg16, data, len);
	} while((bRet)&&(++nErrCount < max_error_count));

	return !bRet;
}

u8 ite_i2c_multi_write(u8 *data,u32 len) //ite_i2c_multi_write
{
	int bRet = 0;
	int nErrCount = 0;
	do
	{
		bRet = IIC_Write_Byte8_N(data[0], data+1, len-1);
	} while((bRet)&&(++nErrCount < max_error_count));

	return !bRet;
}


u8 ite_i2c_multi_write4(u8 data0,u8 data1,u8 data2,u8 data3,u8* readbuf,u32 len) 
//ite_i2c_multi_write4
{

	int bRet = 0;
	int nErrCount = 0;
	do
	{
		bRet = IIC_Read_Byte32_N(data0<<24|data1<<16|data2<<8|data3, readbuf,len);
	} while((bRet)&&(++nErrCount < max_error_count));

	return !bRet;
}

u8 tpd_it7259_is_busy(void)
{
	char bRet = 0;
	int nErrCount = 0;
	u8 buffer[8] = {0};
	do
	{
		buffer[0] = 0xFF;
		bRet = ite_i2c_read(QUERY_BUFFER_INDEX, buffer, 1);  
	}while ((buffer[0] & 0x01)&&(++nErrCount < 20));

	if(nErrCount>20)
	{
		return 1;
	}
	if(bRet)
	{
			;
	}
	return 0;
}

u8 tpd_compare_fw_version(u8 f1, u8 f2, u8 f3, u8 f4)
{
	u8 buffer[8];
	char bRet = 0;
	//int nErrCount = 0;
	if(tpd_it7259_is_busy())
	{
		return 0;
	}
	
	buffer[0] = 0x20;
	buffer[1] = 0x09;
	buffer[2] = 0x00;
	buffer[3] = 0x88;
	buffer[4] = 0x00; 	/* 00-> firmware version, 06->config version */
	bRet = ite_i2c_multi_write(buffer, 5);

	if (!bRet)
	{
		
	}

	if(tpd_it7259_is_busy())
	{
		return 0;
	}
	buffer[0] = 0x20;
	buffer[1] = 0x0b;
	buffer[2] = 0x04; 	
	bRet = ite_i2c_multi_write(buffer, 3);
	if (!bRet)
	{
		return 0;
	}
	if(tpd_it7259_is_busy())
	{
		return 0;
	}

    bRet = ite_i2c_read(COMMAND_RESPONSE_BUFFER_INDEX, buffer, 4); 
		//printf("\r\n IC_FW_version:%d.%d.%d.%d\r\n",buffer[0],buffer[1],buffer[2],buffer[3]);
		//printf("\r\n BIN_FW_version:%d.%d.%d.%d\r\n",f1,f2,f3,f4);

  if ((buffer[0] == f1) && (buffer[1] == f2) && (buffer[2] == f3) && (buffer[3] == f4)) /* zgdezu: only compare first three number */
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

u8 tpd_compare_cfg_version(u8 c1, u8 c2, u8 c3, u8 c4)
{
	u8 buffer[8];
	char bRet = 0;
	buffer[0] = 0xFF;
	if(tpd_it7259_is_busy())
	{
		return 0;
	}

	buffer[0] = 0x20;
	buffer[1] = 0x1;
	buffer[2] = 0x06; /* 00-> firmware version, 06->config version */

	bRet =ite_i2c_multi_write(buffer, 3);
	if (!bRet)
	{
		return 0;
	}

	if(tpd_it7259_is_busy())
	{
		return 0;
	}

	bRet =ite_i2c_read(COMMAND_RESPONSE_BUFFER_INDEX, buffer, 8); 
	
	//printf("\r\n IC_CFG_version:%d.%d.%d.%d\r\n",buffer[1],buffer[2],buffer[3],buffer[4]);
	//printf("\r\n BIN_CFG_version:%d.%d.%d.%d\r\n",c1,c2,c3,c4);
	if (!bRet)
	{
		return 0;
	}
	
	if ((buffer[1] == c1) && (buffer[2] == c2) && (buffer[3] == c3) && (buffer[4] == c4)) /* zgdezu: config compare four number */
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

u8 i2cDirectReadFromIT7259(unsigned short addr, u8 *buf, int len )
{
    int ret;
    u8 tmp[16] = {0};
    tmp[0] = 0x90;
    tmp[1] = 0x00;
    tmp[2] = (addr &0xFF00) >> 8;
    tmp[3] = addr &0xFF;
	
    ite_i2c_multi_write4(tmp[0],tmp[1],tmp[2],tmp[3],buf,len);
	
    return ret;
}
u8 i2cDirectWriteToIT7259(unsigned short reg, u8 *buf, int len)
{
    int i = 0;
    int nRet = 0;
    int nErrCount = 0;
    u8 tmp[16] = {0};
    
    tmp[0] = 0x10;
    tmp[1] = 0x00;
    tmp[2] = (u8)((reg &0xFF00) >> 8);
    tmp[3] = (u8)(reg &0xFF);
    
    for( i = 0 ; i < len ; i++ )
    {
         tmp[i+4] = buf[i];
    }

    do
    {
  	nRet = ite_i2c_multi_write(tmp, len+4);
    } while((!nRet)&&(++nErrCount < max_error_count));

    return  nRet;
}

u8 gfnIT7259_SPIFCRReady()
{
    int nReadCount=0;
    u8 ucBuffer[2];

    do
    {
        i2cDirectReadFromIT7259(0xF400, ucBuffer, 2);
    } while (((ucBuffer[1]& 0x01)!=0x00) && ++nReadCount<20); //nReadCount 3000

    if (nReadCount >=20) //nReadCount 3000
    {
        return 0;
    }

    return 1;
}
unsigned int gfnIT7259_DirectReadFlash(unsigned short wFlashAddress, unsigned short readLength, u8* pData)
{
    int nSector = 0;
    u8 pucCommandBuffer[1024];
    int wTmp;
    int wAddress;
    unsigned int LenOffset;
    u8 bufTemp[4];
    int i;
		int wOffset ;

    nSector = wFlashAddress/0x0400;
    pucCommandBuffer[0] = nSector;

    //Select Sector
    wAddress = 0xF404;
    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,1);

    //Wait SPIFCR

    if (!gfnIT7259_SPIFCRReady())
    {
        return ERROR_QUERY_TIME_OUT;
    }

    //Read flash
		wOffset = wFlashAddress - (nSector*0x0400);
    wAddress = 0x3000 + wOffset;

    for (LenOffset = 0; LenOffset < readLength; LenOffset += 4) //for 8 byte limit
    {
        wTmp = i2cDirectReadFromIT7259(wAddress, bufTemp, 4);
		
        if (wTmp <= 0)
        {
            return COMMAND_ERROR;
        }

        for (i = 0; i < 4; i++)
        {
            pucCommandBuffer[LenOffset + i] = bufTemp[i] ;
        }

        wAddress = wAddress + 4;
    }

    //Wait SPIFCR
    if (!gfnIT7259_SPIFCRReady())
    {
        return ERROR_QUERY_TIME_OUT;
    }

    memcpy((u8*)pData, pucCommandBuffer, readLength * sizeof(u8));

    return COMMAND_SUCCESS;
}

static unsigned int gfnIT7259_GetFWSize()
{
    unsigned int unRet = 0;
    unsigned short wAddress;

    wAddress = 0;
    memset(arucBuffer,0x0,1024);
    gfnIT7259_DirectReadFlash(wAddress,0x0400,arucBuffer);

    unRet = arucBuffer[0x80+12] + (arucBuffer[0x80+13] << 8);

    return unRet;
}

int gfnIT7259_DirectEraseFlash(u8 ucEraseType, int wFlashAddress)
{
    int nSector = 0;
    u8 pucCommandBuffer[16];
    int wTmp;
    int wAddress;
    nSector = wFlashAddress/0x0400;
    pucCommandBuffer[0] = nSector;

    //Select Sector
    wAddress = 0xF404;
    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,1);
		if(wTmp)
		{
				;
		}
    //Wait SPIFCR

    if (!gfnIT7259_SPIFCRReady())
    {
        return ERROR_QUERY_TIME_OUT;
    }

    //Read flash
    wAddress = 0xF402;

    pucCommandBuffer[0] = ucEraseType;

    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,1);

    //Wait SPIFCR
    if (!gfnIT7259_SPIFCRReady())
    {
        return ERROR_QUERY_TIME_OUT;
    }

    return COMMAND_SUCCESS;
}

int gfnIT7259_DMAModeWriteFlash(unsigned short wFlashAddress, unsigned short wSRAMAddress,unsigned int dataLength, uc8* pData, u8 bPollingWait)
{
    int nSector = 0;
    int wAddress;
    int wTmp;
    u8 pucCommandBuffer[32];
    u8 pucReadData[2];
    unsigned int LenOffset;
    u8 bufTemp[4];
    int i;
    unsigned int wStartAddress;

    //write  to address 0x0000 (SRAM only 6K)
    memset(bufTemp, 0xFF, 4);

    wAddress = wSRAMAddress;

    for (LenOffset=0; LenOffset < dataLength; LenOffset+=4) //for 8 byte limit
    {
        for (i = 0; i < 4; i++)
        {
            bufTemp[i] = pData[LenOffset + i];
        }
        wTmp = i2cDirectWriteToIT7259( wAddress, bufTemp, 4);
        wAddress = wAddress + 4;
    }

    //Select Sector
    memset(pucCommandBuffer, 0xFF, 32);

    nSector = wFlashAddress/0x0400;

    pucCommandBuffer[0] = (u8)(nSector & 0xFF);

    wAddress = 0xF404;

    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,1);//DirectWriteMemoryRegister
		//Wait SPIFCR
		if(wTmp)
		{
				;
		}
		
    if (!gfnIT7259_SPIFCRReady())
    {
        return ERROR_QUERY_TIME_OUT;
    }

    //Write Flash strat address

    memset(pucCommandBuffer, 0xFF, 32);

    wAddress = 0xF41A;
		wStartAddress = wFlashAddress - (nSector*0x0400);

    pucCommandBuffer[0] =  wStartAddress & 0x00FF;
    pucCommandBuffer[1] = (wStartAddress & 0xFF00) >> 8 ;

    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,2);//DirectWriteMemoryRegister

    //Write SARM strat address
    wAddress = 0xF41C;

    memset(pucCommandBuffer, 0xFF, 32);

    pucCommandBuffer[0] =  wSRAMAddress & 0xFF;
    pucCommandBuffer[1] = (wSRAMAddress & 0xFF00) >> 8 ;

    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,2);//DirectWriteMemoryRegister

    //write DMA transfer length
    wAddress = 0xF41E;

    pucCommandBuffer[0] =  dataLength & 0xFF;
    pucCommandBuffer[1] = (dataLength & 0xFF00) >> 8 ;


    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,2);//DirectWriteMemoryRegister

    //Write DMA_DIR and DMAEN
    wAddress = 0xF418;

    pucCommandBuffer[0] = 0x0B; //auto erase
    pucCommandBuffer[1] = 0x00;

    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,2);//DirectWriteMemoryRegister

    if (bPollingWait)
    {
        //polling bit 0, until value of bit 0 = 0
        wAddress = 0xF418;
        do
        {
            wTmp = i2cDirectReadFromIT7259(wAddress, pucReadData, 2);//gfnIT7259_DirectReadMemoryRegister
        } while ((pucReadData[0] & 0x01)!= 0x00);

        //Wait SPIFCR
        if (!gfnIT7259_SPIFCRReady())
        {
            return ERROR_QUERY_TIME_OUT;
        }
    }

    return COMMAND_SUCCESS;
}

u8 gfnIT7259_SwitchCPUClock(u8 ucMode)
{
    u8 buffer[8];
		u16  reg16; 
    u8 ucRetCommandBuffer[1];
    int nErrCount = 0;

    do
    {

		buffer[0] = 0x70;
		buffer[1] = 0x23;
		buffer[2] = ucMode;
		ite_i2c_multi_write(buffer, 3);

		reg16 = 0x7023;
		ite_i2c_read16(reg16, ucRetCommandBuffer, 1);  
			////printf("\r\n ucRetCommandBuffer = %2x\r\n",ucRetCommandBuffer[0]);
        nErrCount++;
    } while (((ucRetCommandBuffer[0] & 0x0F) != ucMode) && nErrCount <= 20);

    if (nErrCount>20)
    {
        return 0;
    }

    return 1;
}

int gfnIT7259_DirectWriteFlash(int wFlashAddress, unsigned int wWriteLength, u8* pData)
{
    int nSector = 0;
    u8 pucCommandBuffer[1024];
    int wTmp;
    int wAddress;
		int wOffset ;
    nSector = wFlashAddress/0x0400;
    pucCommandBuffer[0] = nSector;

    //Select Sector
    wAddress = 0xF404;
    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,1);

    if (wTmp <= 0)
    {
        //return COMMAND_ERROR;
    }

    //Wait SPIFCR

    if (!gfnIT7259_SPIFCRReady())
    {
        return ERROR_QUERY_TIME_OUT;
    }

    //write flash
    wOffset = wFlashAddress - (nSector*0x0400);

    wAddress = 0x3000 + wOffset;

    memcpy(pucCommandBuffer, (u8*)pData, wWriteLength * sizeof(u8));

    wTmp = i2cDirectWriteToIT7259(wAddress,pucCommandBuffer,wWriteLength);


    //Wait SPIFCR

    if (!gfnIT7259_SPIFCRReady())
    {
        return ERROR_QUERY_TIME_OUT;
    }

    return COMMAND_SUCCESS;
}


u8 gfnIT7259_FirmwareDownload(unsigned int unFirmwareLength, uc8 arucFW[], unsigned int unConfigLength, uc8 arucConfig[])
{
    int dwAddress;
    u8 RetDATABuffer[10];
    u8 DATABuffer[10];
    int nSector = 0;
    unsigned int nFillSize = 0;
    int wTmp;
    unsigned int unTmp ;
    unsigned long dwFlashSize;
    unsigned int nEndFwSector ;
    unsigned int nStartCFGSector ;
    unsigned int nRemainderFwSize = 0;	
    int nConfigCount = 0;
    int wConfigAddress = 0;
		unsigned int i ;
		int wAddress;
	
    if ((unFirmwareLength == 0 /*|| pFirmware == NULL*/) && (unConfigLength == 0 /*|| pConfig == NULL*/))
    {
        return 0;
    }
    else
    {
    }
		
		//printf("\r\n gfnIT7259_SwitchCPUClock\r\n");
    //trun off CPU data clock    		
    if (!gfnIT7259_SwitchCPUClock(0x01))
    {
				//printf("\r\n gfnIT7259_SwitchCPUClock fail\r\n");
        return 0;
    }
		
    //Wait SPIFCR
    dwAddress = 0xF400;
    do
    {
        i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);
    } while ((RetDATABuffer[1] & 0x01)  != 0x00);
	
		//printf("\r\n Erase signature\r\n");
    //Erase signature

    dwAddress = 0xF404;
    DATABuffer[0] = 0x3F;
    i2cDirectWriteToIT7259(dwAddress,DATABuffer,1);

    dwAddress = 0xF402;
    DATABuffer[0] = 0xD7;
    i2cDirectWriteToIT7259(dwAddress,DATABuffer,1);

    //Wait SPIFCR
    dwAddress = 0xF400;
    do
    {
        i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);
    } while ((RetDATABuffer[1] & 0x01)  != 0x00);
	//return true;
		
		if(FW_CFG_UPGRADE_NEED&0x01)
		{
				//printf("\r\n Download FW\r\n");
				//Download FW
			
				i = 0;
				for (i  = 0 ; i < unFirmwareLength ; i+=0x0400) //0x0400
				{
						if ((unFirmwareLength - i) >= 0x0400)//0x0400
								nFillSize = 0x0400;//0x0400
						else
								nFillSize = unFirmwareLength - i ;

						wTmp = gfnIT7259_DMAModeWriteFlash(i,0x0000,nFillSize,arucFW+i,1);

						//ctp_delay_msec(1);//for test

						if (wTmp != COMMAND_SUCCESS)
						{
								//Write Firmware Flash error
								return 0;
						}
				}
			
				//3. Fw CRC Check
				//printf("\r\n FW CRC Check\r\n");
				//check FW CRC

				//write start address
				dwAddress = 0xF40A;
				DATABuffer[0] = 0x00;
				DATABuffer[1] = 0x00;
				i2cDirectWriteToIT7259(dwAddress,DATABuffer,2);

				//write end address
				dwAddress = 0xF40C;
				DATABuffer[0] = (unFirmwareLength-3) & 0x00ff ;
				DATABuffer[1] = ((unFirmwareLength-3) & 0xff00)>>8;
				i2cDirectWriteToIT7259(dwAddress,DATABuffer,2);

				//write CRCCR

				dwAddress = 0xF408;
				DATABuffer[0] = 0x01 ;
				i2cDirectWriteToIT7259(dwAddress,DATABuffer,1);

				//wait CRCCR

				dwAddress = 0xF408;
				do
				{
						i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);
				} while ((RetDATABuffer[0] & 0x01)  != 0x00);

				//read CRC

				dwAddress = 0xF40E;
				i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);

				//compare FW CRC

				if (RetDATABuffer[0]!= arucFW[unFirmwareLength - 2] || RetDATABuffer[1]!= arucFW[unFirmwareLength - 1])
				{
						//printf("\r\n CRC Check FW fail\r\n");
						return 0;//FW CRC check fail
				}
				//printf("\r\n CRC Check FW success\r\n");
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(FW_CFG_UPGRADE_NEED&0x02)
		{
				//printf("\r\n download config\r\n");
				//download config
				unTmp = gfnIT7259_GetFWSize();

				//	nConfigSize = unConfigLength;

				//3.7 get address for writing config (in flash)
				//check whether fw and config are in the same sector or not
				//set flash size
				dwFlashSize = 0x10000;
				nEndFwSector = (unTmp-1) / 1024;
				nStartCFGSector = 62 - (unConfigLength-1)/1024;

				nRemainderFwSize = 0;

				memset(arucBuffer,0,1024);
				if (nEndFwSector == nStartCFGSector)
				{
						nRemainderFwSize = unTmp - nEndFwSector*1024;
						wAddress = nEndFwSector*0x0400;
						gfnIT7259_DirectReadFlash(wAddress,nRemainderFwSize,arucBuffer);
				}

				//get config start address
				wTmp = dwFlashSize -1024 - unConfigLength;


				for (i = wTmp ; i<(dwFlashSize -1024) ; i+=0x0400)
				{
						int nSize = 0;
						nSector = i/0x0400;

						if ((nRemainderFwSize!=0) && (nSector == nStartCFGSector))
						{
								int wRemainderFWAddress = nStartCFGSector*0x0400;
								nFillSize = nRemainderFwSize;
								gfnIT7259_DMAModeWriteFlash(wRemainderFWAddress,0x0000,nFillSize,arucBuffer,1);
						}

						//write config
						nSize = (unConfigLength - (62-nSector)*1024);

						//int wConfigAddress = 0;
				if (nSize >=1024)
						{
								wConfigAddress = nSector * 0x0400;
								nFillSize = 1024;
						}
						else
						{
								wConfigAddress = i;
								nFillSize = nSize;
						}

						wTmp = gfnIT7259_DMAModeWriteFlash(wConfigAddress ,0x0000, nFillSize, arucConfig + nConfigCount , 1);

						if (wTmp != COMMAND_SUCCESS)
								return 0;

						nConfigCount += nFillSize;
				}

				//Config CRC Check
				//printf("\r\n Config CRC Check\r\n");
				//write start address

				dwAddress = 0xF40A;
				DATABuffer[0] = (0x10000 - unConfigLength -1024) & 0x00ff;
				DATABuffer[1] = ((0x10000- unConfigLength -1024) & 0xff00)>>8;

				i2cDirectWriteToIT7259(dwAddress,DATABuffer,2);

				//write end address

				dwAddress = 0xF40C;
				DATABuffer[0] = (0x10000 -1024 -3)& 0x00ff;
				DATABuffer[1] = ((0x10000-1024 -3) & 0xff00)>>8;

				i2cDirectWriteToIT7259(dwAddress,DATABuffer,2);

				//write CRCCR

				dwAddress = 0xF408;
				DATABuffer[0] = 0x01 ;
				i2cDirectWriteToIT7259(dwAddress,DATABuffer,1);

				//wait CRCCR

				dwAddress = 0xF408;
				do
				{
						i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);
				} while ((RetDATABuffer[0] & 0x01)  != 0x00);

				//read CRC
				dwAddress = 0xF40E;
				i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);

				//compare Config CRC

				if (RetDATABuffer[0]!= arucConfig[unConfigLength - 2] || RetDATABuffer[1]!= arucConfig[unConfigLength - 1])
				{
						//printf("\r\n Config CRC Check Error\r\n");
						return 0;//config CRC Check Error
				}
				//printf("\r\n Config CRC Check success\r\n");
		}
		
    DATABuffer[0] = 0x59;
    DATABuffer[1] = 0x72;
    gfnIT7259_DirectEraseFlash(0xD7,(dwFlashSize -1024));
    gfnIT7259_DirectWriteFlash((dwFlashSize -1024),2,DATABuffer);

    DATABuffer[0] = 0x00;
    DATABuffer[1] = 0x00;
    i2cDirectReadFromIT7259(dwAddress,DATABuffer,2);

    //trun on CPU data clock
    if (!gfnIT7259_SwitchCPUClock(0x04))
    {
				//printf("\r\n gfnIT7259_SwitchCPUClock fail 0x04\r\n");
        return 0;
    }

    return 1;
}

u32 Get_IT7259ID(u8 *data_id)
{
		u16 id_num;

		id_num = 0x7032;
		ite_i2c_read16(id_num,data_id,1);//ite_i2c_read16
		id_num = 0x7033;
		ite_i2c_read16(id_num,data_id+1,1);//ite_i2c_read16

		//printf("\r\n data_id[0] = %2x,data_id[1] = %2x\r\n",data_id[0],data_id[1]);

		if((data_id[1] == 0x72)&&(data_id[0] == 0x59))
		{
				return 1;
		}
		else
		{
				return 0;
		}
}

int check_FW_CFG_NULL(void)
{
		char bRet = 0;
		int nErrCount = 0;
		u8 buffer[8] = {0};
		do
		{
			buffer[0] = 0xFF;
			bRet = ite_i2c_read_NULL(QUERY_BUFFER_INDEX, buffer, 1);  
		}while ((buffer[0] & 0x01)&&(++nErrCount < 20));

		if(bRet == 2)
		{
				return 2;
		}
		return 0;
}

int Upgrade_FW_CFG(void)
{
    unsigned int fw_size = 0;
    unsigned int config_size = 0;
		u8 DATA_ID[2] = {0};
		FW_CFG_UPGRADE_NEED = 0x03;
	
    fw_size =  sizeof(fw_buf);
    config_size = sizeof(config_buf);
		////printf("\r\n fw_size = %4d,config_size = %4d\r\n",fw_size,config_size);
	
		if(!Get_IT7259ID(DATA_ID))
		{
				//printf("\r\n Get_IT7259ID != IT7259,IC is not IT7259\r\n");
				return 0;
		}
		//printf("\r\n IC is IT%x%x\r\n",DATA_ID[1],DATA_ID[0]);
		
		if(2 !=check_FW_CFG_NULL())
		{
				if (0 == tpd_compare_fw_version(fw_buf[136], fw_buf[137], fw_buf[138], fw_buf[139]))
				{
					FW_CFG_UPGRADE_NEED &= (~0x01);
					//printf("\r\n BIN & IC FW_equal\r\n");
				}
				else
				{
						//printf("\r\n FW Need upgrade\r\n");
				}
				
				if (0 == tpd_compare_cfg_version(config_buf[config_size-8], config_buf[config_size-7], config_buf[config_size-6], config_buf[config_size-5]))
				{
					FW_CFG_UPGRADE_NEED &= (~0x02);
					//printf("\r\n BIN & IC CFG_equal\r\n");
					//return 0;
				}
				else
				{
						//printf("\r\n CFG Need upgrade\r\n");
				}
		}
		if(FW_CFG_UPGRADE_NEED & 0x03)
		{
				if (gfnIT7259_FirmwareDownload(fw_size, fw_buf, config_size, config_buf) == 0)
				{
						//printf("\r\n Upgrade_FW_CFG fail\r\n");
						return 0;
				}
				else
				{
						//printf("\r\n Upgrade_FW_CFG success\r\n");
						Reset_IT7259();
						return 1;
				}
		}
		else
		{
				//printf("\r\n No upgrade FW&CFG\r\n");
				return 0;
		}
}

int Clear_FW_CFG(void)
{
		int dwAddress;
    u8 RetDATABuffer[10];
    u8 DATABuffer[10];

		//printf("\r\n gfnIT7259_SwitchCPUClock to 0x01\r\n");   		
    if (!gfnIT7259_SwitchCPUClock(0x01))
    {
				//printf("\r\n gfnIT7259_SwitchCPUClock fail\r\n");
				return 0;
    }
		//Wait SPIFCR
    dwAddress = 0xF400;
    do
    {
        i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);
    } while ((RetDATABuffer[1] & 0x01)  != 0x00);
		
		//printf("\r\n Erase signature\r\n");
    //Erase signature
    dwAddress = 0xF404;
    DATABuffer[0] = 0x3F;
    i2cDirectWriteToIT7259(dwAddress,DATABuffer,1);
		//Wait SPIFCR
    dwAddress = 0xF400;
    do
    {
        i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);
    } while ((RetDATABuffer[1] & 0x01)  != 0x00);
		
		
		dwAddress = 0xF404;
    DATABuffer[0] = 0x00;
    i2cDirectWriteToIT7259(dwAddress,DATABuffer,1);
		//Wait SPIFCR
    dwAddress = 0xF400;
    do
    {
        i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);
    } while ((RetDATABuffer[1] & 0x01)  != 0x00);
		
		dwAddress = 0xF402;
    DATABuffer[0] = 0x60;
    i2cDirectWriteToIT7259(dwAddress,DATABuffer,1);
		//Wait SPIFCR
    dwAddress = 0xF400;
    do
    {
        i2cDirectReadFromIT7259(dwAddress,RetDATABuffer,2);
    } while ((RetDATABuffer[1] & 0x01)  != 0x00);
		
    //trun off CPU data clock 
		//printf("\r\n gfnIT7259_SwitchCPUClock to 0x00\r\n"); 		
    if (!gfnIT7259_SwitchCPUClock(0x00))
    {
				//printf("\r\n gfnIT7259_SwitchCPUClock fail\r\n");
				return 0;
    }
		
		return 1;
}
int Reset_IT7259(void)
{
		u8 temp[2];
		int nRet;
		u8 nErrCount = 0;
		temp[0] = 0x20;
		temp[1] = 0x0c;
		do
    {
			nRet = ite_i2c_multi_write(temp, 2);
    } while((!nRet)&&(++nErrCount < max_error_count));
		return nRet;
}



