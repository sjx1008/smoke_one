#include "WM_Disp.h"

//#define	d_Cursor_SUM				1
//#define	d_VT_set_SUM				4
//#define	d_TCR_set_SUM				3


////鑿滃崟鍚嶇О
//#define	Menu_Name_Font	GUI_FontSF_Proverbial_Gothic32


//static	Work_mode		R_Temp_MODE=d_Temp_mode;
//static	u8	R_TCR_project;


//static	const char	*const	VT_project_Name[]={
//"VT-NI SET",
//"VT-TI SET",
//"VT-SS SET",
//"TCR-M1 SET",
//"TCR-M2 SET",
//};
//static	const char	*const	TCR_project_Name[]={
//"TCR-M1 SET",
//"TCR-M2 SET",
//};
///////////////////////////////
//static	const char	*Menu_Name;

//static	u32	MENU_TC_LOGO[]={
//	d_TC_TEMP,
//	d_TC_WATT,
//	d_CCTSET,
//	d_RESLOCKoff,
//};

//static	const char	*const	Temp_MODE_Name_Buff1[]={
//	"TCR SET",
//	"POWER SET",
//	"CCT SET",
//	"LOCK/UNLOCK",
//};

//static	const char	*const	Temp_MODE_Name_Buff2[]={
//	"TCR SET",
//	"POWER SET",
//	"LOCK/UNLOCK",
//};
//static	s8	R_Cursor_M=0;

//static	uc8	Temp_MODE1_Page_SUM[][2]={{0,4}};
//static	uc8	Temp_MODE2_Page_SUM[][2]={{0,3}};

const char *const	*MODE_Name_Buff;
uc32	*MENU_LOGO_BUFF;
u8	MODE_Name_Page;
uc8	(*MODE_Name_Page_SUB)[2];
s8* R_MENU_Cursor_M;
s8 	R_MENU_Cursor_M_Q;
s8	R_Cursor_SUM;
s8	R_System_set_SUM;
//////////

//void	Set_TCR_project(u8 R,u8	d,void (*S)(void))
//{
//	TCR_Data_Return=S;
//	R_Temp_MODE=(Work_mode)R;
//	R_TCR_project=d;
//	Windows_Switch(VT_MODE_Set_interface);
//}





/* N：Pointer position on this page 指针在本页的位置   */
/* I：Pointer to the last 上次指针   */
/* B：The pointer 本次指针   */
static	void	Disp_DATA_Adjust_Name(u8	N,u8	I,u8	B)	//鍦ㄧN涓綅缃樉绀篒鍙疯彍鍗?
{
	GUI_MEMDEV_Handle hMem;
	GUI_BITMAPSTREAM_INFO	pInfo;
	u8	x,y;

	hMem = GUI_MEMDEV_CreateEx(0, 0, 216, 38,GUI_MEMDEV_NOTRANS);
	GUI_MEMDEV_Select(hMem);
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_AA_SetFactor(3);
	if(B==I)         										//如果上次指针跟这次指针一样
		GUI_SetColor(0xB5863C);
	else																//如果上次指针跟这次指针不一样
		GUI_SetColor(0x5F5C58);

	GUI_AA_FillRoundedRect(0,0,215,37,18);

	Flash_GUI_GetStreamedBitmapInfoEx(MENU_LOGO_BUFF[I],&pInfo);
	x=18-pInfo.XSize/2;
	y=18-pInfo.YSize/2;
	Draw_Bitmap_EX(GUI_DrawStreamedBitmapA565Ex,MENU_LOGO_BUFF[I],x,y);
	GUI_SetFont(&GUI_FontRaavi18);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringAt(MODE_Name_Buff[I],36,10);
	GUI_MEMDEV_Select(0);
	GUI_MEMDEV_WriteAt(hMem,12,60+N*55);//
	GUI_MEMDEV_Delete(hMem);
}

static	void	Disp_Button(void)
{
	if(*R_MENU_Cursor_M==R_Cursor_SUM+R_System_set_SUM-1)
		Disp_EXIT_Key("EXIT",1);
	else
		Disp_EXIT_Key("EXIT",0);
}
static	void	Delete_Menu(u8	i)
{
	GUI_SetColor(GUI_BLACK);
	GUI_FillRect(12,60+i*55,227,97+i*55);
}
void	Disp_MENU_Name(s8	R,s8	R_Q)
{
	u8	i,page,a;
	u8	B=0;
	for(i=0;i<MODE_Name_Page;i++)       //On what page can I find the current pointer  找到当前指针在哪一页
	{
		if(R>=MODE_Name_Page_SUB[i][0] && R<=MODE_Name_Page_SUB[i][1])
		{
			if(R_Q>=MODE_Name_Page_SUB[i][0] && R_Q<=MODE_Name_Page_SUB[i][1])
				B=1;    //Do you need to turn pages    1: no 0: yes 是否需要翻页 1：不需要  0：需要
			break;
		}
	}
	page=i;
	//鍦ㄥ悓涓�椤?
	if(B)
	{
		if(R_Q<R_System_set_SUM)
			Disp_DATA_Adjust_Name(R_Q-MODE_Name_Page_SUB[page][0],R_Q,R);  //Eliminate previous  消掉之前的
		else
			Disp_Button();
		if(R<R_System_set_SUM)
			Disp_DATA_Adjust_Name(R-MODE_Name_Page_SUB[page][0],R,R);			//Highlight the present  高亮现在的
		else
			Disp_Button();
	}
	else //鍦ㄤ笉鍚岄〉
	{
		a=MODE_Name_Page_SUB[page][0];
		for(i=0;i<4;i++)
		{
			if(a<R_System_set_SUM && a<=MODE_Name_Page_SUB[page][1])
			{
				Disp_DATA_Adjust_Name(i,a,R);
			}
			else
			{
				Delete_Menu(i);																								//Over menu quantity. Cover with a black frame 超过菜单总数 用黑框盖住
			}
			a++;
		}
		Disp_Button();
	}
}

////设置菜单按键操作
//static	void	System_Set_Operation(void)
//{
////	u8	R;
//	*R_MENU_Cursor_M=KEY_R_ADD_SUB(&R_key_anxiaOpen,*R_MENU_Cursor_M,KEY_ADD,KEY_SUB,R_Cursor_SUM+R_System_set_SUM-1,0,1,1,100);
//	if(R_MENU_Cursor_M_Q!=*R_MENU_Cursor_M)
//	{
//		Disp_MENU_Name(*R_MENU_Cursor_M,R_MENU_Cursor_M_Q);
//		R_MENU_Cursor_M_Q=*R_MENU_Cursor_M;
//	}
//
//	if(R_key_anxia_Mode==KEY_MODE)
//	{
//		if(R_Temp_MODE==d_Temp_mode)
//		{
//			if(*R_MENU_Cursor_M==0)
//			{
//				R_Work_mode=d_Temp_mode;
//				R_Atomizer=(Atomizer)R_TCR_project;
//				R_TCR_SetProject=R_TCR_project;
//				Windows_Switch(TCR_Data_Set_interface);
//			}
//			else if(*R_MENU_Cursor_M==1)
//			{
//				R_Work_mode=d_Temp_mode;
//				R_Atomizer=(Atomizer)R_TCR_project;
//				R_TCR_SetProject=R_TCR_project;
//				Windows_Switch(PWR_Data_Set_interface);
//			}
//			else if(*R_MENU_Cursor_M==2)
//			{
//				R_Work_mode=d_CustomTemp_mode;
//				R_Atomizer=(Atomizer)R_TCR_project;
//				Windows_Switch(CCT_Custom_Data_Set_interface);
//			}
//			else if(*R_MENU_Cursor_M==3)
//			{
//				if(R_Work_mode!=d_Temp_mode && R_Work_mode!=d_CustomTemp_mode )
//					R_Work_mode=d_Temp_mode;
//				R_Atomizer=(Atomizer)R_TCR_project;
//				Windows_Switch(LOCK_Resis_interface);
//			}
//			else
//			{
//				Windows_Switch(TCR_Data_Return);
//			}
//		}
//		else
//		{
//			if(*R_MENU_Cursor_M==0)
//			{
//				R_Work_mode=d_TCR_mode;
//				R_TCR_term=(TCR_term)R_TCR_project;
//				R_TCR_SetProject=R_TCR_project+3;
//				Windows_Switch(TCR_Data_Set_interface);
//			}
//			else if(*R_MENU_Cursor_M==1)
//			{
//				R_Work_mode=d_TCR_mode;
//				R_TCR_term=(TCR_term)R_TCR_project;
//			  R_TCR_SetProject=R_TCR_project+3;
//				Windows_Switch(PWR_Data_Set_interface);
//			}
//			else if(*R_MENU_Cursor_M==2)
//			{
//				R_Work_mode=d_TCR_mode;
//				R_TCR_term=(TCR_term)R_TCR_project;
//				Windows_Switch(LOCK_Resis_interface);
//			}
//			else
//			{
//				Windows_Switch(TCR_Data_Return);
//			}
//		}
//	}
//	if(R_key_anxia==KEY_M)
//	{
//		Windows_Switch(Main_interface);
////		if(R_Temp_MODE==d_Temp_mode)
////		{
////			R_Work_mode=d_Temp_mode;
////			R_Atomizer=(Atomizer)R_TCR_project;
////		}
////		else
////		{
////			R_Work_mode=d_TCR_mode;
////			R_TCR_term=(TCR_term)R_TCR_project;
////		}
//	}
//}

//static	void	VT_MODE_Set_windows(void)
//{
//	if(R_Temp_MODE==d_Temp_mode)
//	{
//		if(R_TCR_project>=Atomizer_NC)
//			R_TCR_project=Ss;
//		Menu_Name=VT_project_Name[R_TCR_project];
//		R_System_set_SUM=d_VT_set_SUM;
//		R_Cursor_SUM=d_Cursor_SUM;
//		MODE_Name_Buff=Temp_MODE_Name_Buff1;
//		MENU_TC_LOGO[2]=d_CCTSET;
//		if(B_LOCK_Res)
//			MENU_TC_LOGO[3]=d_RESLOCKon;
//		else
//			MENU_TC_LOGO[3]=d_RESLOCKoff;
//		MODE_Name_Page_SUB=Temp_MODE1_Page_SUM;
//	}
//	else
//	{
//		if(R_TCR_project>=TCR_NC)
//			R_TCR_project=M1;
//		Menu_Name=TCR_project_Name[R_TCR_project];
//		R_System_set_SUM=d_TCR_set_SUM;
//		R_Cursor_SUM=d_Cursor_SUM;
//		MODE_Name_Buff=Temp_MODE_Name_Buff2;
//		if(B_LOCK_Res)
//			MENU_TC_LOGO[2]=d_RESLOCKon;
//		else
//			MENU_TC_LOGO[2]=d_RESLOCKoff;
//		MODE_Name_Page_SUB=Temp_MODE2_Page_SUM;
//	}
//	MENU_LOGO_BUFF=MENU_TC_LOGO;
//	R_Cursor_M=0;
//	R_MENU_Cursor_M=&R_Cursor_M;
//	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
//	PanelTurnOffDisplay();
//	draw_Bmp_ex(d_bgtop,0,0);
//	GUI_SetColor(GUI_WHITE);
//	GUI_SetFont(&Menu_Name_Font);
//	GUI_DispStringHCenterAt(Menu_Name,120,0);
//	GUI_RECT	RECT;
//	RECT.x0=0;
//	RECT.y0=33;
//	RECT.x1=239;
//	RECT.y1=319;
//	Map_draw_bmpToBitmap_ex(d_Bottom_map,&RECT,0,33);
//	MODE_Name_Page=1;
//	R_MENU_Cursor_M_Q=*R_MENU_Cursor_M;
//	Disp_MENU_Name(*R_MENU_Cursor_M,0xFF);
//	PanelTurnOnDisplay();
//}

////
//void	VT_MODE_Set_interface(void)
//{
//	Key_Light_screen();
//	switch((u8)R_Skinning_mode)
//	{
//		case	Skinning_init:{//初始化
//			Vibrate_EN(1);
//			VT_MODE_Set_windows();
//			B_Key_release=1;
//			R_Bright_screen_TimeMAX=R_BrightScreen_TimeMAX;
//			R_Bright_screen_Time=R_Bright_screen_TimeMAX;
//		};break;
//		case	USB_access:{//usb插入
//			Windows_Interrupt_Push(Battery_charging_interface);
//		};break;
//		case	USB_anomaly:{//USB异常
//			Windows_Interrupt_Push(USB_Warning_interface);
//		};break;
//		default:{
//			System_Set_Operation();
//			Atomizer_inquiry_GOTO(1);
//			GOTO_Screensaver_interface(1);
//			Screen_GOTO_charging();
//			Batt_error_GOTO();
//		};
//	}
//	R_Skinning_mode=Skinning_mode_null;
//}







