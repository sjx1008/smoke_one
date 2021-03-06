#include "main.h"

//************主界面使用到的LOGO*****************************//
u8	BOOT_logo[12]={"aspire"};

uc8	W_LOGO[]={15,16,0xC3,0x0C,0xC3,0x0C,0xC3,0x0C,0xC3,0x0C,0x63,0x18,0x63,0x18,0x67,0x98,0x67,0x98,
0x3C,0xF0,0x3C,0xF0,0x3C,0xF0,0x3C,0xF0,0x38,0x70,0x18,0x60,0x18,0x60,0x18,0x60};
uc8	V_LOGO[]={15,16,0x60,0x18,0x60,0x18,0x60,0x18,0x70,0x38,0x30,0x30,0x30,0x30,0x38,0x70,0x18,0x60,
0x1C,0xE0,0x0C,0xC0,0x0F,0xC0,0x07,0x80,0x07,0x80,0x07,0x80,0x03,0x00,0x03,0x00};
uc8	B_LOGO[]={15,16,0x3F,0xE0,0x3F,0xF0,0x30,0x38,0x30,0x18,0x30,0x18,0x30,0x38,0x30,0x78,0x3F,0xE0,
0x3F,0xE0,0x30,0x70,0x30,0x38,0x30,0x18,0x30,0x18,0x30,0x38,0x3F,0xF0,0x3F,0xE0};
uc8	Ni_LOGO[]={15,16,0x60,0xC0,0x60,0xC0,0x70,0xC0,0x78,0xC0,0x68,0xC0,0x6C,0xCC,0x6C,0xCC,0x64,0xC0,
0x66,0xCC,0x66,0xCC,0x62,0xCC,0x63,0xCC,0x61,0xCC,0x61,0xCC,0x60,0xCC,0x60,0xCC};
uc8	Ti_LOGO[]={15,16,0x7F,0xE0,0x7F,0xE0,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x0C,0x06,0x0C,0x06,0x00,
0x06,0x0C,0x06,0x0C,0x06,0x0C,0x06,0x0C,0x06,0x0C,0x06,0x0C,0x06,0x0C,0x06,0x0C};	
uc8	Ss_LOGO[]={15,16,0x7C,0x00,0xFE,0x00,0xC6,0x00,0xC6,0x3C,0xC6,0x7E,0xC0,0x66,0xE0,0x66,0x78,0x60,
0x3C,0x70,0x0E,0x3C,0x06,0x0E,0xC6,0x06,0xC6,0x66,0xC6,0x66,0xFE,0x7E,0x7C,0x3C};
uc8	M1_LOGO[]={15,16,0xC1,0x80,0xC1,0x80,0xE3,0x80,0xE3,0x8C,0xE3,0x9C,0xF7,0xBC,0xF7,0xAC,0xF7,0x8C,
0xD5,0x8C,0xDD,0x8C,0xDD,0x8C,0xC9,0x8C,0xC9,0x8C,0xC9,0x8C,0xC1,0x8C,0xC1,0x8C};
uc8	M2_LOGO[]={15,16,0xC1,0x80,0xC1,0x80,0xE3,0x80,0xE3,0x9C,0xE3,0xBE,0xF7,0xA6,0xF7,0x86,0xF7,0x86,
0xD5,0x86,0xDD,0x8E,0xDD,0x9C,0xC9,0xB8,0xC9,0xB0,0xC9,0xB0,0xC1,0xBE,0xC1,0xBE};
uc8	M3_LOGO[]={15,16,0xC1,0x80,0xC1,0x80,0xE3,0x80,0xE3,0x9C,0xE3,0xBE,0xF7,0xA6,0xF7,0x86,0xF7,0x86,
0xD5,0x8C,0xDD,0x9C,0xDD,0x8E,0xC9,0x86,0xC9,0x86,0xC9,0xA6,0xC1,0xBE,0xC1,0x9C};
uc8	C1_LOGO[]={15,16,0x3E,0x00,0x7F,0x00,0xE3,0x80,0xC1,0x8C,0xC0,0x1C,0xC0,0x3C,0xC0,0x3C,0xC0,0x0C,
0xC0,0x0C,0xC0,0x0C,0xC0,0x0C,0xC0,0x0C,0xC1,0x8C,0xE3,0x8C,0x7F,0x0C,0x3E,0x0C};
uc8	C2_LOGO[]={15,16,0x3E,0x00,0x7F,0x00,0xE3,0x80,0xC1,0x9C,0xC0,0x3E,0xC0,0x26,0xC0,0x06,0xC0,0x06,
0xC0,0x06,0xC0,0x0E,0xC0,0x1C,0xC0,0x38,0xC1,0xB0,0xE3,0xB0,0x7F,0x3E,0x3E,0x3E};
uc8	C3_LOGO[]={15,16,0x3E,0x00,0x7F,0x00,0xE3,0x80,0xC1,0x9C,0xC0,0x3E,0xC0,0x26,0xC0,0x06,0xC0,0x06,
0xC0,0x0C,0xC0,0x18,0xC0,0x0C,0xC0,0x06,0xC1,0x86,0xE3,0xA6,0x7F,0x3E,0x3E,0x1C};

						///温度单位
uc8	Cunit_LOGO[]={13,21,0xE3,0xE0,0xA7,0xF0,0xEF,0xF8,0x0E,0x38,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,
0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,
0x1C,0x00,0x0E,0x38,0x0F,0xF8,0x07,0xF0,0x03,0xE0};
uc8	Funit_LOGO[]={13,21,0xEF,0xF8,0xAF,0xF8,0xEF,0xF8,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,
0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,
0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00,0x0E,0x00};
					///欧姆
uc8	Omuunit_LOGO[]={5,11,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x50,0x50,0x50,0xD8,};
					///锁头
uc8	ShuoU_LOGO[]={5,3,0x70,0x88,0x88};

uc8	*const WVB_D[]={W_LOGO,V_LOGO,B_LOGO};
uc8	*const Temp_D[]={Ni_LOGO,Ti_LOGO,Ss_LOGO};
uc8	*const TCR_D[]={M1_LOGO,M2_LOGO,M3_LOGO};

//************吸烟超时*****************************//
uc8	Over_LOGO[]={52,13,
0x38,0x00,0x00,0x00,0x21,0x81,0xC0,0x44,0x00,0x00,0x00,0x62,0x42,0x20,0x82,0x00,
0x00,0x00,0x24,0x24,0x10,0x82,0x00,0x00,0x00,0x24,0x24,0x00,0x82,0x00,0x00,0x00,
0x24,0x22,0x00,0x82,0x00,0x00,0x00,0x24,0x21,0x00,0x82,0x82,0x31,0x70,0x24,0x20,
0x80,0x82,0x44,0x49,0x80,0x24,0x20,0x40,0x82,0x44,0x85,0x00,0x24,0x20,0x20,0x82,
0x28,0xFD,0x00,0x24,0x20,0x10,0x82,0x28,0x81,0x00,0x24,0x24,0x10,0x44,0x10,0x45,
0x00,0x22,0x42,0x20,0x38,0x10,0x39,0x00,0x71,0x81,0xC0,/*"E:\lingxiangtao工作\2016\易佳特\8527(易佳特80W)\界面设计\4.bmp",0*/
/* (52 X 13 )*/};

uc8	Locked_LOGO[]={42,26,
0x80,0x00,0x02,0x00,0x00,0x80,0x80,0x00,0x02,0x00,0x00,0x80,0x80,0x00,0x02,0x00,
0x00,0x80,0x80,0x00,0x02,0x00,0x00,0x80,0x80,0x70,0x72,0x23,0x06,0x80,0x80,0x88,
0x8A,0x44,0x89,0x80,0x81,0x05,0x02,0x88,0x50,0x80,0x81,0x05,0x03,0x0F,0xD0,0x80,
0x81,0x05,0x02,0x88,0x10,0x80,0x80,0x88,0x8A,0x44,0x48,0x80,0xFC,0x70,0x72,0x23,
0x87,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x39,0x20,0x10,0x0F,0xD0,0x40,
0x45,0x20,0x10,0x08,0x10,0x40,0x81,0x00,0x10,0x88,0x08,0x80,0x81,0x00,0x11,0x08,
0x08,0x80,0x81,0x23,0x92,0x0F,0x05,0x00,0x81,0x24,0x14,0x00,0x82,0x00,0x81,0x28,
0x18,0x00,0x45,0x00,0x81,0x28,0x14,0x00,0x48,0x80,0x81,0x28,0x12,0x00,0x48,0x80,
0x45,0x24,0x51,0x08,0x90,0x40,0x39,0x23,0x90,0x87,0x10,0x40,/*"E:\lingxiangtao工作\2016\易佳特\8527(易佳特80W)\界面设计\1.bmp",0*/
/* (42 X 26 )*/};

uc8	LowBatter_LOGO[]={71,13,
0x80,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x11,0x00,0x41,0x00,
0x00,0x00,0x80,0x00,0x00,0x10,0x80,0x41,0x00,0x00,0x00,0x80,0x00,0x00,0x10,0x80,
0x41,0x00,0x00,0x00,0x80,0x00,0x00,0x11,0x00,0x41,0x00,0x00,0x00,0x80,0xE2,0x48,
0x1E,0x1C,0xFB,0xE3,0x17,0x42,0x81,0x12,0x48,0x11,0x22,0x41,0x04,0x98,0x42,0x82,
0x0A,0x48,0x10,0x9E,0x41,0x08,0x50,0x24,0x82,0x0A,0xA8,0x10,0xA2,0x41,0x0F,0xD0,
0x24,0x82,0x0A,0xA8,0x10,0xA2,0x41,0x08,0x10,0x18,0x81,0x11,0x10,0x11,0x22,0x41,
0x04,0x50,0x08,0xFC,0xE1,0x10,0x0E,0x1D,0x38,0xE3,0x90,0x10,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x60,/*"E:\lingxiangtao工作\2016\易佳特\8527(易佳特80W)\界面设计\2.bmp",0*/
/* (71 X 13 )*/};

uc8	NoAtomizer_LOGO[]={69,12,
0x82,0x00,0x01,0x08,0x00,0x00,0x00,0x00,0x00,0x82,0x00,0x01,0x08,0x00,0x00,0x00,
0x00,0x00,0xC2,0x00,0x02,0x88,0x00,0x00,0x00,0x00,0x00,0xA2,0x00,0x02,0x88,0x00,
0x00,0x40,0x00,0x00,0xA2,0x00,0x02,0x88,0x00,0x00,0x00,0x00,0x00,0x92,0x38,0x04,
0x5F,0x9C,0x36,0x5F,0x98,0xB8,0x92,0x44,0x04,0x48,0x22,0x49,0x41,0x24,0xC0,0x8A,
0x82,0x04,0x48,0x41,0x49,0x42,0x42,0x80,0x8A,0x82,0x07,0xC8,0x41,0x49,0x42,0x7E,
0x80,0x86,0x82,0x08,0x28,0x41,0x49,0x44,0x40,0x80,0x82,0x44,0x08,0x28,0x22,0x49,
0x48,0x22,0x80,0x82,0x38,0x08,0x27,0x9C,0x49,0x5F,0x9C,0x80,/*"E:\lingxiangtao工作\2016\易佳特\8527(易佳特80W)\界面设计\3.bmp",0*/
/* (69 X 12 )*/};

uc8	TooHot_LOGO[]={52,12,
0xFE,0x00,0x00,0x04,0x10,0x01,0x00,0x10,0x00,0x00,0x04,0x10,0x01,0x00,0x10,0x00,
0x00,0x04,0x10,0x01,0x00,0x10,0x00,0x00,0x04,0x10,0x01,0x00,0x10,0x00,0x00,0x04,
0x10,0x01,0x00,0x10,0x70,0x70,0x07,0xF1,0xC7,0xF0,0x10,0x88,0x88,0x04,0x12,0x21,
0x00,0x11,0x05,0x04,0x04,0x14,0x11,0x00,0x11,0x05,0x04,0x04,0x14,0x11,0x00,0x11,
0x05,0x04,0x04,0x14,0x11,0x00,0x10,0x88,0x88,0x04,0x12,0x21,0x00,0x10,0x70,0x70,
0x04,0x11,0xC0,0xF0,/*"E:\lingxiangtao工作\2016\易佳特\8527(易佳特80W)\界面设计\5.bmp",0*/
/* (52 X 12 )*/};



//************电池反接提示*****************************//
uc8	Empty_battery_LOGO[]={0/*47,8,0x00,0x00,0x00,0x01,0xFF,0xE0,0x00,0x00,0x00,0x1F,0xFF,0xF8,0x3C,0x00,0x03,0xFF,
0xFF,0xFE,0xFF,0x03,0xFF,0xFF,0xFF,0xFE,0xFF,0x03,0xFF,0xFF,0xFF,0xFE,0x3C,0x00,
0x03,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x00,0x01,0xFF,0xE0*/};

//************中英文选择界面*****************************//
uc8	EN_LOGO[]={16,14,0xFE,0x63,0xFE,0x63,0xC0,0x73,0xC0,0x73,0xC0,0x7B,0xC0,0x7B,0xFC,0x7B,0xFC,0x6F,
0xC0,0x6F,0xC0,0x67,0xC0,0x67,0xC0,0x67,0xFE,0x63,0xFE,0x63};
uc8	CH_LOGO[]={16,14,0x7C,0x63,0xFE,0x63,0xC6,0x63,0xC6,0x63,0xC6,0x63,0xC0,0x7F,0xC0,0x7F,0xC0,0x63,
0xC0,0x63,0xC6,0x63,0xC6,0x63,0xC6,0x63,0xFE,0x63,0x7C,0x63};
uc8	Language_block[][2]={17,36,
												55,74};
//************输入密码锁机界面*****************************//
uc8	Set_password_LOGO[]={4,7,0x80,0xC0,0xE0,0xF0,0xE0,0xC0,0x80};
											
//************TCR调节界面*****************************//
uc8	TCR_Ni[]={"Ni"};
uc8	TCR_Ti[]={"Ti"};
uc8	TCR_Ss[]={"Ss"};
uc8	TCR_M1[]={"M\""};
uc8	TCR_M2[]={"M$"};
uc8	TCR_M3[]={"M&"};

uc8	*const TCR_name[]={TCR_Ni,TCR_Ti,TCR_Ss,TCR_M1,TCR_M2,TCR_M3};
uc8	TCR_zuobiao[]={9,22,34,50,63,78};
uc8	TCR_nameBOX[][2]={7,17,
											20,30,
											33,45,
											48,59,
											62,73,
											77,88};

//////////////////////////////////
////中文界面
uc8	Please_access_Atomizer_C[]={16,29,17,32,42,15,28,0xAA};//////请接入雾化器
uc8	Low_resistance_C[]={16,7,54,52,2,14,0xAA};//////低阻值保护
uc8	Smoking_timeout_C[]={16,43,47,3,33,0xAA};//////吸烟超时
uc8	High_temp_C[]={16,13,31,2,14,0xAA};//////过热保护
uc8	Low_BAT_C[]={16,8,4,8,23,7,0xAA};//////电池电量低
uc8	New_atomizer_C[]={16,45,42,15,28,63,0xAA};//////新雾化器？
uc8	YESorNO_C[]={16,35,64,66,10,65,0xAA};//////是+/否-
uc8	Shuoding_C[]={16,37,9,0xAA};//////锁定
uc8	Shutdown_C[]={16,1,56,6,18,37,0xAA};//////按5次解锁
uc8	System_off_C[]={16,44,39,12,16,0xAA};//////按5次解锁






