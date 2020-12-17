#include "main_2.h"
#include "usb_device.h"
#include "gpio.h"
u16	R_BattZ_JZ_Data=1000;
u16	R_Batt1_JZ_Data=1000;

#if 1
static	void	Disp_Firmware_Tim(void)
{
	char Schar[11];
	Schar[0]=DataStr[9];
	Schar[1]=DataStr[10];
	if(DataStr[0]=='F')
	{
		Schar[2]='0';
		Schar[3]='2';
	}
	else if(DataStr[0]=='S')
	{
		Schar[2]='0';
		Schar[3]='9';
	}
	else if(DataStr[0]=='O')
	{
		Schar[2]='1';
		Schar[3]='0';
	}
	else if(DataStr[0]=='N')
	{
		Schar[2]='1';
		Schar[3]='1';
	}
	else if(DataStr[0]=='D')
	{
		Schar[2]='1';
		Schar[3]='2';
	}
	else if(DataStr[0]=='J')
	{
		if(DataStr[1]=='a')
		{
			Schar[2]='0';
			Schar[3]='1';
		}
		else if(DataStr[2]=='n')
		{
			Schar[2]='0';
			Schar[3]='6';
		}
		else
		{
			Schar[2]='0';
			Schar[3]='7';
		}
	}
	else if(DataStr[0]=='M')
	{
		if(DataStr[2]=='r')
		{
			Schar[2]='0';
			Schar[3]='3';
		}
		else
		{
			Schar[2]='0';
			Schar[3]='5';
		}
	}
	else if(DataStr[0]=='A')
	{
		if(DataStr[1]=='p')
		{
			Schar[2]='0';
			Schar[3]='4';
		}
		else
		{
			Schar[2]='0';
			Schar[3]='8';
		}
	}
	Schar[4]=DataStr[4];
	if(Schar[4]==' ')
		Schar[4]='0';
	Schar[5]=DataStr[5];
	Schar[6]=TimeStr[0];
	Schar[7]=TimeStr[1];
	Schar[8]=TimeStr[3];
	Schar[9]=TimeStr[4];
	Schar[10]=0;

	GUI_SetTextMode(GUI_TEXTMODE_NORMAL);
	GUI_SetColor(GUI_WHITE);
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetFont(&FontGill18);
	GUI_DispStringAt((char*)USB_Hardware_version,50,25);
	GUI_DispStringAt(Schar,50,43);
	if(RTC_Clock==RTC_Clock_LSI)
		GUI_DispStringAt("NG",95,200);
}

static	u8	jiaozhun_panduan(void)
{
	vu8	i=0;
	vu16	P_P=0,P_N=0;
	vu16	P_P_Q=0,P_N_Q=0;
	u8	B;
	for(u8	i=0;i<5;i++)
	{
		B=0;
		if(SPI_Flash_Read_PageData32(Device1_Identifier)!=*(uint32_t*)UID_BASE)
		{B=1;continue;};
		if(SPI_Flash_Read_PageData32(Device2_Identifier)!=*(uint32_t*)(UID_BASE+4))
		{B=1;continue;};
		if(SPI_Flash_Read_PageData32(Device3_Identifier)!=*(uint32_t*)(UID_BASE+8))
		{B=1;continue;};
		if(B==0)
			break;
	}
	if(B)
		return 1;
	LL_GPIO_InitTypeDef   GPIO_InitStructure;
	////////////////////////////////////////////////////////////////////////////////////////
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	GPIO_InitStructure.Pin = LL_GPIO_PIN_11|LL_GPIO_PIN_12;
  GPIO_InitStructure.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = LL_GPIO_PULL_UP;
  LL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	R_Read_Rtim=50;
	while(R_Read_Rtim!=0 && (!(USB_T_GPIO_PORT->IDR & USB_T_PIN)))
	{
		if(GPIOA->IDR & LL_GPIO_PIN_12)
			P_P=1;
		else
			P_P=0;
		if(GPIOA->IDR & LL_GPIO_PIN_11)
			P_N=1;
		else
			P_N=0;
		if(P_P_Q!=P_P && P_N_Q!=P_N)
		{
			R_KEY_timi=14;
			R_Read_Rtim=24;
			P_P_Q=P_P;
			P_N_Q=P_N;
			i++;
		}
		if(i==2)
		{
			i=0;
			while(1)
			{
				if(GPIOA->IDR & LL_GPIO_PIN_12)
					P_P=1;
				else
					P_P=0;
				if(GPIOA->IDR & LL_GPIO_PIN_11)
					P_N=1;
				else
					P_N=0;
				if(P_P_Q!=P_P && P_N_Q!=P_N)
				{
					R_KEY_timi=14;
					R_Read_Rtim=24;
					P_P_Q=P_P;
					P_N_Q=P_N;
				}
				if(P_P_Q!=P_P)
				{
					P_P_Q=P_P;
					if(!R_KEY_timi || R_KEY_timi>=6)
					{
						return	0;
					}
					else
					{
						R_KEY_timi=14;
					}
				}
				if(P_N_Q!=P_N)
				{
					P_N_Q=P_N;
					if(!R_Read_Rtim || R_Read_Rtim>=6)
					{
						return	0;
					}
					else
					{
						R_Read_Rtim=24;
						i++;
						if(i>5)
							return 1;
					}
				}
				if(!R_Read_Rtim || !R_KEY_timi)
					return 0;
			}
		}
	}
	return 0;
}

void	Batt_JZ_interface(void)
{
	u32	BattZ_Sum;
	u32	Batt1_Sum;
	u32	Batt1_max;
	u32	Batt1_min;
	u32	BattZ_max;
	u32	BattZ_min;
	u8	Batt_i;
	u8	B_JC;
	B_JC=jiaozhun_panduan();
	R_KEY_timi=0;
	R_Read_Rtim=500;
	USB_ENABLE_transmission();

	if(B_JC)
	{
		TFT_VCC_Reset();
		Delay_Nms(50);
		TFT_VCC_Set();
		TFT_LCD_RESET();
		TFT_ST7789S_Init();
		GUI_SetBkColor(GUI_BLACK);
		GUI_Clear();
		GUI_SetTextMode(GUI_TEXTMODE_NORMAL);
		GUI_SetColor(GUI_WHITE);
		GUI_SetFont(&FontGill18);
		GUI_DispStringAt("BATT ADJU",80,65);

		Disp_Firmware_Tim();
		BL_PanelTurnOnDisplay();
		Delay_Nms(1000);
		R_BattZ_JZ_Data=1000;
		R_Batt1_JZ_Data=1000;

		Batt1_Sum=0;
		BattZ_Sum=0;
		Batt1_max=0;
		Batt1_min=0xffff;
		BattZ_max=0;
		BattZ_min=0xffff;
		for(Batt_i=0;Batt_i<10;Batt_i++)
		{
			ReadBATz_Data();
			Delay_Nms(20);
			Batt1_Sum+=R_BAT_L_Real;
			BattZ_Sum+=R_BATZ_Real;
			if(R_BAT_L_Real>Batt1_max)
				Batt1_max=R_BAT_L_Real;
			if(R_BAT_L_Real<Batt1_min)
				Batt1_min=R_BAT_L_Real;
			if(R_BATZ_Real>BattZ_max)
				BattZ_max=R_BATZ_Real;
			if(R_BATZ_Real<BattZ_min)
				BattZ_min=R_BATZ_Real;
		}
		Batt1_Sum=(Batt1_Sum-Batt1_min-Batt1_max)/8;
		BattZ_Sum=(BattZ_Sum-BattZ_min-BattZ_max)/8;

		if(Batt1_Sum>405 && Batt1_Sum<435 && BattZ_Sum>810 && BattZ_Sum<870)
		{
			R_BattZ_JZ_Data=840*1000/BattZ_Sum;
			R_Batt1_JZ_Data=420*1000/Batt1_Sum;
			W25QXX_Erase_Sector(Device1_Identifier);
			SPI_Flash_WritePageData32(d_Batt_JY_DATA_Address,R_BattZ_JZ_Data<<16 | R_Batt1_JZ_Data);
			SPI_Flash_WritePageData32(Device1_Identifier,*(uint32_t*)UID_BASE);
			SPI_Flash_WritePageData32(Device2_Identifier,*(uint32_t*)(UID_BASE+4));
			SPI_Flash_WritePageData32(Device3_Identifier,*(uint32_t*)(UID_BASE+8));
			GUI_SetFont(&FontGill37);
			GUI_DispStringAt("OK",100,160);
		}
		else
		{
			GUI_SetFont(&FontGill37);
			GUI_DispStringAt("NG",100,160);
		}
		GUI_FillRect(111,113,113,116);
		GUI_FillRect(111,153,113,156);

		Batt_i=20;
		B_KEY_JC=1;
		GUI_SetFont(&FontCent45);
		while(1)
		{
			Delay_Nms(1);
			if(B_KEY_JC)
			{
				B_KEY_JC=0;
				Batt_i++;
				if(Batt_i>=20)
				{
					ReadBATz_Data();
					Batt_i=0;
					GUI_DispDecAt(R_BAT_H_Real/100,87,80,1);
					GUI_DispDecAt(R_BAT_H_Real%100,116,80,2);
					GUI_DispDecAt(R_BAT_L_Real/100,87,120,1);
					GUI_DispDecAt(R_BAT_L_Real%100,116,120,2);
				}
				Key_scan();
				if(R_key_3C==KEY_M)
				{
					BL_PanelTurnOffDisplay();
					return;
				}
			}
			USB_state_program();
		}
	}
	else
	{
		R_BattZ_JZ_Data=SPI_Flash_Read_PageData16(d_Batt_JY_DATA_Address+2);
		R_Batt1_JZ_Data=SPI_Flash_Read_PageData16(d_Batt_JY_DATA_Address);
		if(R_BattZ_JZ_Data>1034 || R_BattZ_JZ_Data<966)
			R_BattZ_JZ_Data=1000;
		if(R_Batt1_JZ_Data>1037 || R_Batt1_JZ_Data<965)
			R_Batt1_JZ_Data=1000;
		Key_scan();
		if(key_value==KEY_M)
		{
			TFT_VCC_Reset();
			Delay_Nms(50);
			TFT_VCC_Set();
			TFT_LCD_RESET();
			TFT_ST7789S_Init();
			GUI_SetBkColor(GUI_BLACK);
			GUI_Clear();
			Disp_Firmware_Tim();
			BL_PanelTurnOnDisplay();
			GUI_SetColor(GUI_WHITE);
			GUI_FillRect(111,113,113,116);
			GUI_FillRect(111,153,113,156);
			B_KEY_JC=1;
			Batt_i=20;
			R_SleepTim=50;
			GUI_SetFont(&FontCent45);
			while(R_SleepTim)
			{
				Delay_Nms(1);
				if(B_KEY_JC)
				{
					B_KEY_JC=0;
					Batt_i++;
					if(Batt_i>=20)
					{
						ReadBATz_Data();
						Batt_i=0;
						GUI_DispDecAt(R_BAT_H_Real/100,87,80,1);
						GUI_DispDecAt(R_BAT_H_Real%100,116,80,2);
						GUI_DispDecAt(R_BAT_L_Real/100,87,120,1);
						GUI_DispDecAt(R_BAT_L_Real%100,116,120,2);
					}
				}
			}
			BL_PanelTurnOffDisplay();
		}
	}
}
#endif
