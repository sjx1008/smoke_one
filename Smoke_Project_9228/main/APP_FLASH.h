#ifndef		_APP_FLASH_
#define		_APP_FLASH_
#include	"main.h"

typedef union FLASH_Structure
{
	volatile	uc8		R_Flash8[2048];
	volatile	uc16	R_Flash16[1024];
	volatile	uc32	R_Flash32[512];
}FLASH_Structure;

extern 	u8 R_Flash_WB;
extern 	u8	B_Force_Power_down_save;

extern	uc16 R_Flash[];
extern void Data_retention(void);
extern void Rflash(void);
//extern HAL_StatusTypeDef	ROM_ProgramWord(uint32_t Address, uint32_t Data);

extern void	Default_Data(void);
#endif



