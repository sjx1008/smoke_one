
#ifndef __LOOG_H
#define __LOOG_H

/////////////////////////////////////////
//************主界面使用到的LOGO*****************************//
extern	u8	BOOT_logo[];

extern	uc8	W_LOGO[];
extern	uc8	V_LOGO[];
extern	uc8	B_LOGO[];
extern	uc8	Ni_LOGO[];
extern	uc8	Ti_LOGO[];	
extern	uc8	Ss_LOGO[];
extern	uc8	M1_LOGO[];
extern	uc8	M2_LOGO[];
extern	uc8	M3_LOGO[];
extern	uc8	C1_LOGO[];
extern	uc8	C2_LOGO[];
extern	uc8	C3_LOGO[];

						///温度单位
extern	uc8	Cunit_LOGO[];
extern	uc8	Funit_LOGO[];
					///欧姆
extern	uc8	Omuunit_LOGO[];
					///锁头
extern	uc8	ShuoU_LOGO[];

extern	uc8	*const WVB_D[];
extern	uc8	*const Temp_D[];
extern	uc8	*const TCR_D[];
//************吸烟超时*****************************//
extern	uc8	Over_LOGO[];
extern	uc8	Locked_LOGO[];
extern	uc8	LowBatter_LOGO[];
extern	uc8	NoAtomizer_LOGO[];
extern	uc8	TooHot_LOGO[];
//************电池反接提示*****************************//
extern	uc8	Empty_battery_LOGO[];
//************中英文选择界面*****************************//
extern	uc8	EN_LOGO[];
extern	uc8	CH_LOGO[];
extern	uc8	Language_block[][2];
//************输入密码锁机界面*****************************//
extern	uc8	Set_password_LOGO[];
//************TCR调节界面*****************************//
extern	uc8	*const TCR_name[];
extern	uc8	TCR_zuobiao[];
extern	uc8	TCR_nameBOX[][2];

//////////////////////////////////
////中文界面
extern	uc8	Please_access_Atomizer_C[];//////请接入雾化器
extern	uc8	Low_resistance_C[];/////低阻值保护
extern	uc8	Smoking_timeout_C[];/////吸烟超时
extern	uc8	High_temp_C[];//////过热保护
extern	uc8	Low_BAT_C[];//////电池电量低
extern	uc8	New_atomizer_C[];//////新雾化器？
extern	uc8	YESorNO_C[];///////是+/否-
extern	uc8	Shuoding_C[];
extern	uc8	Shutdown_C[];//////关机
extern	uc8	System_off_C[];


#endif



