#include "APP_Custom.h"
#include "main_2.h"
#include "crc.h"
u8		B_Custom_Hold=0;
u16		R_Custom_Flash_i;

Custom_union R_Custom_BUFF={
	.Custom_array.Custom_A5A5=0xA5A5A5A5,
	.Custom_array.CustomCCW_Data={120,110,100,90,80,70,60,50,40,30},
	.Custom_array.CustomCCV_Data={420,415,410,405,400,395,390,385,380,375},
	.Custom_array.CustomCCTSS_C_Data={200,210,220,230,240,250,260,270,280,290},
	.Custom_array.CustomCCTNI_C_Data={200,210,220,230,240,250,260,270,280,290},
	.Custom_array.CustomCCTTI_C_Data={200,210,220,230,240,250,260,270,280,290},
	.Custom_array.CustomCCTSS_F_Data={400,420,440,460,480,500,520,540,560,580},
	.Custom_array.CustomCCTNI_F_Data={400,420,440,460,480,500,520,540,560,580},
	.Custom_array.CustomCCTTI_F_Data={400,420,440,460,480,500,520,540,560,580},
};

//const 	FLASH_Structure		R_FLASH_Custom  		__attribute__((at(d_FLASH_Custom_address)));


#define		d_FLASH_Date_maxbyte	84
#define		d_FLASH_Date_maxword	42

void Read_Custom_flash(void)
{
	u16	i;
	R_Custom_Flash_i=0;
	for(i=0;i<1024;i+=d_FLASH_Date_maxword)
	{
		if(SPI_Flash_Read_PageData32(FLASH_Custom_address+i*4)==0xA5A5A5A5)
		{
			R_Custom_Flash_i=i;
			break;
		}
	}

	if(SPI_Flash_Read_PageData32(FLASH_Custom_address+R_Custom_Flash_i*4)!=0xA5A5A5A5 && R_Custom_Flash_i==0)
	{
		W25QXX_Erase_Sector(FLASH_Custom_address);
	}
	else
	{
		SPI_Flash_Read_BuffData32(FLASH_Custom_address+R_Custom_Flash_i*4,R_Custom_BUFF.Custom_int32,d_FLASH_Date_maxword);
		SPI_Flash_Read_BuffData_OK();
		for(i=0;i<10;i++)
		{
			if(R_Custom_BUFF.Custom_array.CustomCCW_Data[i]>d_User_Watt_max/10)
				R_Custom_BUFF.Custom_array.CustomCCW_Data[i]=d_User_Watt_max/10;
			else	if(R_Custom_BUFF.Custom_array.CustomCCW_Data[i]<d_User_Watt_min/10)
				R_Custom_BUFF.Custom_array.CustomCCW_Data[i]=d_User_Watt_min/10;

			if(R_Custom_BUFF.Custom_array.CustomCCV_Data[i]>d_User_Vout_max)
				R_Custom_BUFF.Custom_array.CustomCCV_Data[i]=d_User_Vout_max;
			else	if(R_Custom_BUFF.Custom_array.CustomCCV_Data[i]<d_User_Vout_min)
				R_Custom_BUFF.Custom_array.CustomCCV_Data[i]=d_User_Vout_min;

			if(R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data[i]>d_User_TempC_max)
				R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data[i]=d_User_TempC_max;
			else	if(R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data[i]<d_User_TempC_min)
				R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data[i]=d_User_TempC_min;
			R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data[i]/=5;
			R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data[i]*=5;

			if(R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data[i]>d_User_TempC_max)
				R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data[i]=d_User_TempC_max;
			else	if(R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data[i]<d_User_TempC_min)
				R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data[i]=d_User_TempC_min;
			R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data[i]/=5;
			R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data[i]*=5;

			if(R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data[i]>d_User_TempC_max)
				R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data[i]=d_User_TempC_max;
			else	if(R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data[i]<d_User_TempC_min)
				R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data[i]=d_User_TempC_min;
			R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data[i]/=5;
			R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data[i]*=5;

			if(R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data[i]>d_User_TempF_max)
				R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data[i]=d_User_TempF_max;
			else	if(R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data[i]<d_User_TempF_min)
				R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data[i]=d_User_TempF_min;
			R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data[i]/=10;
			R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data[i]*=10;

			if(R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data[i]>d_User_TempF_max)
				R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data[i]=d_User_TempF_max;
			else	if(R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data[i]<d_User_TempF_min)
				R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data[i]=d_User_TempF_min;
			R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data[i]/=10;
			R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data[i]*=10;

			if(R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data[i]>d_User_TempF_max)
				R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data[i]=d_User_TempF_max;
			else	if(R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data[i]<d_User_TempF_min)
				R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data[i]=d_User_TempF_min;
			R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data[i]/=10;
			R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data[i]*=10;
		}
	}
}


void Custom_WriteFLASH(void)
{
	u32 jiaoyan;
	if(!B_Custom_Hold)
		return;
	if(R_USB_state==S_USB_NOP)
		R_USB_state=S_USB_FLASH;
	else
		return;
	B_Custom_Hold=0;
	R_Custom_BUFF.Custom_array.Custom_A5A5=0xA5A5A5A5;
	LL_CRC_DeInit(CRC);
	jiaoyan=CRC_CalcBlockCRC(R_Custom_BUFF.Custom_int32,d_FLASH_Date_maxword-2);
	if(jiaoyan==R_Custom_BUFF.Custom_array.Custom_CRC)
	{
		R_USB_state=S_USB_NOP;
		return;
	}
	R_Custom_BUFF.Custom_array.Custom_CRC=jiaoyan;
	SPI_Flash_WritePageData32(FLASH_Custom_address+R_Custom_Flash_i*4,0);
	R_Custom_Flash_i+=d_FLASH_Date_maxword;
	if(R_Custom_Flash_i+d_FLASH_Date_maxword>=1024)
	{
		R_Custom_Flash_i=0;
		W25QXX_Erase_Sector(FLASH_Custom_address);
	}
	SPI_Flash_Write_BuffData32(FLASH_Custom_address+R_Custom_Flash_i*4,R_Custom_BUFF.Custom_int32,d_FLASH_Date_maxword);
	SPI_Flash_Write_BuffData_OK();
	R_USB_state=S_USB_NOP;
}


















