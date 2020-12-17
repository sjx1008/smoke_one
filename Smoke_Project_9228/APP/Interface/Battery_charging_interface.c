#include "WM_Disp.h"


//static	u16	R_Batter_Interface_Tim_Q;
static	u8	BatterGrade_Q;
static	u8	BatterGrade2_Q;
static	u8	B_BAT_Paoma;
static	u8	B_BAT_Congman_Q;
static	u8	B_BAT_Congman2_Q;
static	u8	R_BattL_Proportion_Q;		//低节电池百分比
static	u8	R_BattH_Proportion_Q;		//高节电池百分比
//static	u8	B_Fast_Charg_Q;
//static	u16	R_Charging_current_average_Q;
u8	B_Get_Charg_BH_Q;
static	u16	Charging_Over_Time_Q[2];	//充电预计时间
//static	u8	B_USC_CL;



//显示充电平衡状态
static	void	Disp_Get_Charg_BH(void)
{
//	static	u8	Tim;
//	GUI_RECT	RECT;
//	if(Tim)
//	{
//		Tim--;
//	}
//	else
//	{
//		if(B_BAT_Congman && B_BAT_Congman2)
//			B_Get_Charg_BH=0;
//		if(B_Get_Charg_BH)
//		{
//			if(!B_Get_Charg_BH_Q)
//			{
//				Tim=100;
//				RECT.x0=45;
//				RECT.y0=49;
//				RECT.x1=59;
//				RECT.y1=66;
//				Map_draw_bmpToBitmap_ex(d_Blue_circle_Vape,&RECT,113,128);
//			}
//		}
//		else
//		{
//			if(B_Get_Charg_BH_Q)
//			{
//				Tim=100;
//				RECT.x0=113;
//				RECT.y0=128;
//				RECT.x1=127;
//				RECT.y1=145;
//				Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,RECT.x0,RECT.y0);
//			}
//		}
//		B_Get_Charg_BH_Q=B_Get_Charg_BH;
//	}
}

//显示充电时间
static	void	Disp_Batter_Time_Data(u16	R,u8	i)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	char	s[7];
	if(i==0)
	{
		RECT.x0=21;
		RECT.y0=199;
		RECT.x1=117;
		RECT.y1=218;
	}
	else
	{
		RECT.x0=122;
		RECT.y0=199;
		RECT.x1=218;
		RECT.y1=218;
	}
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(0xB5863C);
	GUI_SetFont(&GUI_FontArial27);
	sprintf(s,"%dMIN",R);
	s[6]=0;
	GUI_DispStringInRect(s,&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}
static	void	Disp_Batter_Interface_Tim(void)
{
	if(Charging_Over_Time_Q[0]!=Charging_Over_Time[0])
	{
		Charging_Over_Time_Q[0]=Charging_Over_Time[0];
		Disp_Batter_Time_Data(Charging_Over_Time_Q[0],0);

	}
	if(Charging_Over_Time_Q[1]!=Charging_Over_Time[1])
	{
		Charging_Over_Time_Q[1]=Charging_Over_Time[1];
		Disp_Batter_Time_Data(Charging_Over_Time_Q[1],1);
	}
}
////显示USB插入图标
//void	Disp_USB_CL(void)
//{
//	if(B_USC_CL!=B_USB_Computer)
//	{
//		B_USC_CL=B_USB_Computer;
//		R_Back_Color=d_Clean_Color;
//		if(B_USC_CL)
//			R_Front_Color=d_Bright_Color;
//		else
//			R_Front_Color=d_Clean_Color;
//		GUI_Write_Bitmap(32,1,USB_LOGO);
//	}
//}
//显示电量百分比
static	void	Disp_Proportion_Data(u16	R,u8	i)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	char	s[5];
	if(i==0)
	{
		RECT.x0=37;
		RECT.y0=158;
		RECT.x1=105;
		RECT.y1=177;
	}
	else
	{
		RECT.x0=133;
		RECT.y0=158;
		RECT.x1=201;
		RECT.y1=177;
	}
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_FontArial27);
	sprintf(s,"%d%%",R);
	s[4]=0;
	GUI_DispStringInRect(s,&RECT,GUI_TA_VCENTER|GUI_TA_HCENTER);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}

static	void	BATT_Proportion_disp(void)
{
	if(R_BattL_Proportion_Q!=R_BattL_Proportion)
	{
		R_BattL_Proportion_Q=R_BattL_Proportion;
		Disp_Proportion_Data(R_BattL_Proportion_Q,0);
	}
	if(R_BattH_Proportion_Q!=R_BattH_Proportion)
	{
		R_BattH_Proportion_Q=R_BattH_Proportion;
		Disp_Proportion_Data(R_BattH_Proportion_Q,1);
	}
}
////显示充电电流
//static	void	Print_Batt_Current(u16	R)
//{
//	GUI_MEMDEV_Handle hMem;
//	hMem = GUI_MEMDEV_Create(0, 0, 34, 13);
//	GUI_MEMDEV_Select(hMem);
//	GUI_SetColor(GUI_BLACK);
//	GUI_FillRect(0,0,34,13);
//	GUI_SetColor(GUI_WHITE);
//	GUI_SetFont(&FontGill22);
//	GUI_GotoXY(0,-5);
//	GUI_DispDecShift(R,4,2);
//	GUI_MEMDEV_Select(0);
//	GUI_MEMDEV_WriteAt(hMem, 97, 65);//显示
//	GUI_MEMDEV_Delete(hMem);
//}

//显示快充闪电
void	Disp_Quick_LOGO(void)
{
//	GUI_RECT	RECT;
//	GUI_MEMDEV_Handle hMem;
//	if(B_Fast_Charg_Q!=B_Fast_Charg)
//	{
//		B_Fast_Charg_Q=B_Fast_Charg;
//		if(B_Fast_Charg==0)
//		{
//			//画一个闪电
//			hMem = GUI_MEMDEV_CreateEx(0,0,21,32,GUI_MEMDEV_NOTRANS);
//			GUI_MEMDEV_Select(hMem);
//			RECT.x0=93;
//			RECT.y0=73;
//			RECT.x1=113;
//			RECT.y1=104;
//			Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,0,0);
//			Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Quick_bright,0,0);
//			GUI_MEMDEV_Select(0);
//			GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//
//			GUI_MEMDEV_Select(hMem);
//			RECT.x0=127;
//			RECT.y0=73;
//			RECT.x1=147;
//			RECT.y1=104;
//			Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,0,0);
//			Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Quick_dark,0,0);
//			GUI_MEMDEV_Select(0);
//			GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//
//			GUI_MEMDEV_Delete(hMem);
//		}
//		else
//		{
//			//画两个闪电
//			hMem = GUI_MEMDEV_CreateEx(0,0,21,32,GUI_MEMDEV_NOTRANS);
//			GUI_MEMDEV_Select(hMem);
//			RECT.x0=93;
//			RECT.y0=73;
//			RECT.x1=113;
//			RECT.y1=104;
//			Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,0,0);
//			Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Quick_bright,0,0);
//			GUI_MEMDEV_Select(0);
//			GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//
//			GUI_MEMDEV_Select(hMem);
//			RECT.x0=127;
//			RECT.y0=73;
//			RECT.x1=147;
//			RECT.y1=104;
//			Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,0,0);
//			Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,d_Quick_bright,0,0);
//			GUI_MEMDEV_Select(0);
//			GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//
//			GUI_MEMDEV_Delete(hMem);
//		}
//	}
}

//显示电池格数
static	void	BATT_Vip_disp(u8	vip,u8	I)
{
	GUI_MEMDEV_Handle hMem;
	GUI_RECT	RECT;
	if(I==0)
	{
		RECT.x0=36;
		RECT.y0=107;
		RECT.x1=105;
		RECT.y1=129;
	}
	else
	{
		RECT.x0=132;
		RECT.y0=107;
		RECT.x1=201;
		RECT.y1=129;
	}
	hMem = GUI_MEMDEV_CreateEx(RECT.x0,RECT.y0,RECT.x1-RECT.x0+1,RECT.y1-RECT.y0+1,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(0x00E641);
	if(vip)
		GUI_FillRect(RECT.x0,RECT.y0,vip*(RECT.x1-RECT.x0)/5+RECT.x0,RECT.y1);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem, RECT.x0, RECT.y0);//显示
	GUI_MEMDEV_Delete(hMem);
}

//充电跑马
void	Display_BAT_Charging(void)
{
//	u8	i;
	Disp_Batter_Interface_Tim();
	BATT_Proportion_disp();
	Disp_Get_Charg_BH();
	Disp_Quick_LOGO();
	if(B_BAT_Charge)
	{
		if(B_BAT_Paoma<40)
		{
			B_BAT_Paoma++;
		}
		else
		{
			B_BAT_Paoma=0;
			if(B_BAT_Congman)
			{
				if(!B_BAT_Congman_Q)
				{
					B_BAT_Congman_Q=1;
					BATT_Vip_disp(5,0);
				}
			}
			else
			{
				B_BAT_Congman_Q=0;
				if(BatterGrade_Q>5 || BatterGrade_Q+1<BatterGrade)
				{
					BatterGrade_Q=BatterGrade;
					if(BatterGrade>=5)
					{
						BatterGrade_Q=4;
					}
				}
				BATT_Vip_disp(BatterGrade_Q,0);
				BatterGrade_Q++;
			}
			if(B_BAT_Congman2)
			{
				if(!B_BAT_Congman2_Q)
				{
					B_BAT_Congman2_Q=1;
					BATT_Vip_disp(5,1);
				}
			}
			else
			{
				B_BAT_Congman2_Q=0;
				if(BatterGrade2_Q>5 || BatterGrade2_Q+1<BatterGrade2)
				{
					BatterGrade2_Q=BatterGrade2;
					if(BatterGrade2>=5)
					{
						BatterGrade2_Q=4;
					}
				}
				BATT_Vip_disp(BatterGrade2_Q,1);
				BatterGrade2_Q++;
			}
		}
	}
	else
	{
		R_USB_Charging_current_average=0;
		if(BatterGrade_Q!=BatterGrade)
		{
			BatterGrade_Q=BatterGrade;
			BATT_Vip_disp(BatterGrade_Q,0);
		}
		if(BatterGrade2_Q!=BatterGrade2)
		{
			BatterGrade2_Q=BatterGrade2;
			BATT_Vip_disp(BatterGrade2_Q,1);
		}
	}
}
//充电界面窗口
//static	sc8		VAPORESSO[]={'V','A','P','O','R','E','S','S','O'};
//static	uc16	VAPORESSO_xEnd[]={36,55,78,94,118,137,152,169,185};
void	Battery_charging_windows(void)
{
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	PanelTurnOffDisplay();
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
//	GUI_SetColor(0xB5863C);
//	GUI_SetPenSize(1);
//	GUI_DrawRect(31,102,108,132);
//	GUI_DrawRect(32,103,107,131);
//	GUI_FillRect(109,109,111,125);
//
//	GUI_DrawRect(127,102,204,132);
//	GUI_DrawRect(128,103,203,131);
//	GUI_FillRect(205,109,207,125);
	draw_Bmp_ex(d_Charg_Shell,31,102);
	draw_Bmp_ex(d_Charg_Shell,127,102);
//	R_Batter_Interface_Tim_Q=0xFFFF;
	B_BAT_Paoma=40;
	BatterGrade_Q=0xF0;
	BatterGrade2_Q=0xF0;
	B_BAT_Congman_Q=0;
	B_BAT_Congman2_Q=0;
	R_BattL_Proportion_Q=0xF0;
	R_BattH_Proportion_Q=0xF0;
	Charging_Over_Time_Q[0]=0xF000;
	Charging_Over_Time_Q[1]=0xF000;
	B_Get_Charg_BH_Q=0;
//	B_Fast_Charg_Q=0xF0;
	Display_BAT_Charging();
	PanelTurnOnDisplay();
//	R_Charging_current_average_Q=0xf000;
//	B_USC_CL=0;
}
void	Battery_charging_interface(void)
{
	static	u8	B_chongman;
	u8	B=0;
	B=Key_Light_screen();
	if(B_Skinning_init)
	{
		B_Skinning_init=0;
		Vibrate_EN(!B_ADDSUB_LOCK&&!B_System_off);
		Battery_charging_windows();
		B_Key_release=1;
		B_Smoking_mark=0;
		B_GOTO_Atomizer_inquiry=1;
		R_Bright_screen_TimeMAX=2400;
		R_Bright_screen_Time=R_Bright_screen_TimeMAX;
		R_Interface_maintain_Time=5;
		B_chongman=0;
	}
	switch((u8)R_Skinning_mode)
	{
		case	USB_anomaly:{//USB异常
				Windows_Switch(USB_Warning_interface);
		};break;
		case	Short_circuit:{//短路
			Windows_Switch(Warning_interface);
			Warning_Windows=Short_circuit_windows;
		};break;
		case	Open_circuit:{//开路
			Windows_Switch(Warning_interface);
			Warning_Windows=Open_circuit_windows;
		};break;
		case	Low_Resistance:{//低阻值
			Windows_Switch(Warning_interface);
			Warning_Windows=Low_ATOMIZER_windows;
		};break;
		case	High_Resistance:{//高阻值
			Windows_Switch(Warning_interface);
			Warning_Windows=HIGH_ATOMIZER_windows;
		};break;
		case	Low_Battery:{//低电量
			Windows_Switch(Warning_interface);
			Warning_Windows=Low_Battery_windows;
		};break;
		case	Smoking_timeout:{//吸烟超时
			Windows_Switch(Warning_interface);
			Warning_Windows=Smoking_timeout_windows;
		};break;
		case	PCB_Overheated:{//PCB过热
			Windows_Switch(Warning_interface);
			Warning_Windows=PCB_Overheated_windows;
		};break;
		default:{
			if(!B_BAT_Charge)
			{
				R_Bright_screen_TimeMAX=2400;
				R_Bright_screen_Time=R_Bright_screen_TimeMAX;
				if(!R_Interface_maintain_Time)
				{
					if(B_System_off==d_System_Off)
						Windows_Switch(System_off_interface);
					else
						Fanhui_Main_interface();
				}
			}
			else
			{
				R_Interface_maintain_Time=5;
				if(!B_BAT_Congman || !B_BAT_Congman2)
				{
					R_Bright_screen_TimeMAX=2400;
					if(B_chongman)
						R_Bright_screen_Time=R_Bright_screen_TimeMAX;
					B_chongman=0;
				}
				else
				{
					if(!B_chongman)
					{
						B_chongman=1;
						R_Bright_screen_TimeMAX=100;
						R_Bright_screen_Time=R_Bright_screen_TimeMAX;
					}
				}
			}
			if(R_key_anxia || B_Out_Yes)
			{
				if(B_System_off!=d_System_Off)
				{
					Fanhui_Main_interface();
				}
			}
			if(R_key_5C==KEY_M)
			{
				if(B_System_off==d_System_Off)
				{
					B_System_off=d_System_Normal;
					Windows_Switch(BOOT_LOGO_interface);
				}
				else if(B_System_off==d_System_Locked)
				{
					B_System_off=d_System_Normal;
					Windows_Switch(Main_interface);
				}
			}
			if(!B_Atomizer_inquiry)
			{
				B_GOTO_Atomizer_inquiry=0;
			}
			if(!B_GOTO_Atomizer_inquiry)
			{
				if(B_System_off!=d_System_Off)
					Atomizer_inquiry_GOTO(0);
			}
			Batt_error_GOTO();
		};
	}
	if(B_OLED_BL)
	{
		if(B)
			Battery_charging_windows();
		Display_BAT_Charging();
	}
	R_Skinning_mode=Skinning_mode_null;
}

