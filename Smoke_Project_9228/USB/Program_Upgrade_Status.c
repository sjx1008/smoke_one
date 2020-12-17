#include "main.h"
#include "main_2.h"
#include <stdio.h>
#include <string.h>

#define	d_update_OK			0xEDB77BDE
#define	d_GOTO_Main			0xA5A55A5A

void	Program_Upgrade_Status(void)
{
	u8	Schar[32];
	u8	B=0;
	u8	i;
	for(i=0;i<3;i++)
	{
		SPI_Flash_Read_BuffData8(Program_Finished_Product_Name,Schar,32);
		SPI_Flash_Read_BuffData_OK();
		if (strcmp(USB_Product_name,(char*)Schar))
		{	B=1;continue;}
		SPI_Flash_Read_BuffData8(Program_Software_version,Schar,32);
		SPI_Flash_Read_BuffData_OK();
		if (strcmp(USB_Software_version,(char*)Schar))
		{	B=1;continue;}
		SPI_Flash_Read_BuffData8(Program_Hardware_version,Schar,32);
		SPI_Flash_Read_BuffData_OK();
		if (strcmp(USB_Hardware_version,(char*)Schar))
		{	B=1;continue;}
		SPI_Flash_Read_BuffData8(Program_Software_Date,Schar,32);
		SPI_Flash_Read_BuffData_OK();
		if (strcmp(__DATE__,(char*)Schar))
		{	B=1;continue;}
		SPI_Flash_Read_BuffData8(Program_Software_Time,Schar,32);
		SPI_Flash_Read_BuffData_OK();
		if (strcmp(__TIME__,(char*)Schar))
		{	B=1;continue;}
		break;
	}

	if(SPI_Flash_Read_PageData32(Program_Rom_Status)==d_update_OK || B)
	{
		W25QXX_Erase_Sector(FLASH_SaveData_address);
		W25QXX_Erase_Sector(FLASH_Custom_address);
		W25QXX_Erase_Sector(Program_Rom_Version);
		W25QXX_Erase_Sector(FLASH_PUFF_address);

		SPI_Flash_Write_BuffData8(Program_Finished_Product_Name,(u8*)USB_Product_name,sizeof(USB_Product_name));
		SPI_Flash_Write_BuffData_OK();
		SPI_Flash_Write_BuffData8(Program_Software_version,(u8*)USB_Software_version,sizeof(USB_Software_version));
		SPI_Flash_Write_BuffData_OK();
		SPI_Flash_Write_BuffData8(Program_Hardware_version,(u8*)USB_Hardware_version,sizeof(USB_Hardware_version));
		SPI_Flash_Write_BuffData_OK();
		SPI_Flash_Write_BuffData8(Program_Software_Date,(u8*)__DATE__,sizeof(__DATE__));
		SPI_Flash_Write_BuffData_OK();
		SPI_Flash_Write_BuffData8(Program_Software_Time,(u8*)__TIME__,sizeof(__TIME__));
		SPI_Flash_Write_BuffData_OK();
		SPI_Flash_WritePageData32(Program_Rom_Status,d_GOTO_Main);
	}
}





