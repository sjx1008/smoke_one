
#ifndef _FLASH_DATA_H_
#define _FLASH_DATA_H_

#include "main.h"

#define	FLASH_SectorsSize		4096	//外部FLASH扇区大小

/*电池校准存储空间0-4K*/
#define	Device1_Identifier			0x00000000	//唯一设备ID1
#define	Device2_Identifier			0x00000004	//唯一设备ID2
#define	Device3_Identifier			0x00000008	//唯一设备ID3
#define	d_Batt_JY_DATA_Address		0x0000000C	//电池校准值

/*升级信息存储空间4-8K*/
#define	d_IAP_Data_Address			0x00001000	//定义IAP掉电数据保存空间
	#define	Program_Rom_Length		0x00001000	//程序数据长度
	#define	Program_Rom_Checksum	0x00001004	//程序数据校验和
	#define	Program_Rom_Status		0x00001008	//程序升级状态

/*软件硬件版本信息8-12K*/
#define	Program_Rom_Version			0x00002000
	#define	Program_Finished_Product_Name	0x00002000	//产品名称
	#define	Program_Software_version			0x00002020	//软件版本
	#define	Program_Software_Date					0x00002040	//软件编译日期
	#define	Program_Software_Time					0x00002060	//软件编译时间
	#define	Program_Hardware_version			0x00002080	//硬件版本

/*掉电保存空间12-36K*/
#define	FLASH_Power_down_save_ADDR		0x00003000
	#define	FLASH_SaveData_address			0x00003000	   	/* 掉电保存区域 4096*/
	#define	FLASH_Custom_address				0x00004000		/* 自定义曲线保存区域 4096*/
	#define	FLASH_PUFF_address					0x00005000
	#define	FLASH_RTC_address						0x00006000
	#define	FLASH_Retain3_address				0x00007000
	#define	FLASH_Retain4_address				0x00008000

#define	FLASH_Data_address		0x00009000			//FLASH数据区域的起始地址
	#define	FLASH_Data_size				0x003F7000			//FLASH数据区域的长度
#define	FLASH_Backups_Base		0x00009000			//FLASH备份基础地址
	#define	FLASH_Backups_size		0x003F7000			//FLASH备份区域长度
#define	FLASH_BackupsData_address		0x00009000//0x00900000			//FLASH备份基础地址


/////////////////////////////////////////////////////////////



//////////////




//#define	d_Boot_animation						(0x00000000 + FLASH_Data_address) // 开机界面.gif
//#define	d_OMNI_LOGO									(0x000182DB + FLASH_Data_address) // OMNI_LOGO.bmp
//#define	d_Vaporess_LOGO							(0x000195A3 + FLASH_Data_address) // Vaporess_LOGO.bmp
//#define	d_EXIT_ON_Bottom						(0x0001EBB3 + FLASH_Data_address) // EXIT_ON-66-280.bmp
//#define	d_EXIT_Bottom								(0x00020BC7 + FLASH_Data_address) // EXIT-66-280.bmp
//#define	d_Demarcation_line					(0x00022BDB + FLASH_Data_address) // 菜单分界线-2-218.bmp
//#define	d_MenuNameBottom						(0x00024663 + FLASH_Data_address) // 菜单名称底图-0-0.bmp
//#define	d_Menu_BP										(0x0002938B + FLASH_Data_address) // BP.bmp
//#define	d_Menu_CC_SET								(0x0002ACC3 + FLASH_Data_address) // CC_SET.bmp
//#define	d_Menu_CCT_NI								(0x0002C58B + FLASH_Data_address) // CCT_NI.bmp
//#define	d_Menu_CCT_SS								(0x0002DF33 + FLASH_Data_address) // CCT_SS.bmp
//#define	d_Menu_CCT_TI								(0x0002F8DB + FLASH_Data_address) // CCT_TI.bmp
//#define	d_Menu_CCV									(0x00031283 + FLASH_Data_address) // CCV.bmp
//#define	d_Menu_CCW									(0x00032B4B + FLASH_Data_address) // CCW.bmp
//#define	d_Menu_DIY									(0x00034413 + FLASH_Data_address) // DIY.bmp
//#define	d_Menu_LOCK_R								(0x00035CDB + FLASH_Data_address) // LOCK_R.bmp
//#define	d_Menu_SET									(0x000375A3 + FLASH_Data_address) // SET.bmp
//#define	d_Menu_SET2									(0x00038E6B + FLASH_Data_address) // SET2.bmp
//#define	d_Menu_SP										(0x0003A733 + FLASH_Data_address) // SP.bmp
//#define	d_Menu_TCR_M1								(0x0003C58F + FLASH_Data_address) // TCR_M1.bmp
//#define	d_Menu_TCR_M2								(0x0003DE57 + FLASH_Data_address) // TCR_M2.bmp
//#define	d_Menu_VT_NI								(0x0003F71F + FLASH_Data_address) // VT_NI.bmp
//#define	d_Menu_VT_SET								(0x00040FE7 + FLASH_Data_address) // VT_SET.bmp
//#define	d_Menu_VT_SS								(0x000428AF + FLASH_Data_address) // VT_SS.bmp
//#define	d_Menu_VT_TI								(0x00044177 + FLASH_Data_address) // VT_TI.bmp
//#define	d_Menu_VV										(0x00045A3F + FLASH_Data_address) // VV.bmp
//#define	d_Menu_VW_H									(0x00047377 + FLASH_Data_address) // VW_H.bmp
//#define	d_Menu_VW_N									(0x00048BCF + FLASH_Data_address) // VW_N.bmp
//#define	d_Menu_VW_S									(0x0004A497 + FLASH_Data_address) // VW_S.bmp
//#define	d_Menu_VW_SET								(0x0004BCEF + FLASH_Data_address) // VW_SET.bmp
//#define	d_SelectMenuBottom					(0x0004D5B7 + FLASH_Data_address) // 图标选中框.dta
//#define	d_Menu2_AUTO								(0x000515F3 + FLASH_Data_address) // AUTO.dta
//#define	d_Menu2_RTC									(0x00051AB3 + FLASH_Data_address) // RTC设置.dta
//#define	d_Menu2_SMART								(0x00051F37 + FLASH_Data_address) // SMART.dta
//#define	d_Menu2_KeyLed							(0x000522D7 + FLASH_Data_address) // 按键灯.dta
//#define	d_Menu2_VERSION							(0x0005275B + FLASH_Data_address) // 版本信息.dta
//#define	d_Menu2_Default							(0x00052AFB + FLASH_Data_address) // 恢复出厂值.dta
//#define	d_Menu2_ScreensaverTim			(0x00052FF1 + FLASH_Data_address) // 屏保时长.dta
//#define	d_Menu2_ScreenLight					(0x00053391 + FLASH_Data_address) // 屏幕亮度.dta
//#define	d_Menu2_PULL								(0x00053851 + FLASH_Data_address) // 吸烟口数.dta
//#define	d_Menu2_VIBRATE							(0x00053C63 + FLASH_Data_address) // 震动.dta
//#define	d_Menu2_D_NO_R_Arrow				(0x00054123 + FLASH_Data_address) // 大未选中右箭头.dta
//#define	d_Menu2_D_NO_L_Arrow				(0x00054B5F + FLASH_Data_address) // 大未选中左箭头.dta
//#define	d_Menu2_D_R_Arrow						(0x00055547 + FLASH_Data_address) // 大选中右箭头.dta
//#define	d_Menu2_D_L_Arrow						(0x00055F83 + FLASH_Data_address) // 大选中左箭头.dta
//#define	d_Main_LOCK_R_PNG						(0x0005696B + FLASH_Data_address) // 电阻欧姆2.dta
//#define	d_Menu2_X_NO_R_Arrow				(0x00056BC4 + FLASH_Data_address) // 小未选中右箭头.dta
//#define	d_Menu2_X_NO_L_Arrow				(0x000571FB + FLASH_Data_address) // 小未选中左箭头.dta
//#define	d_Menu2_X_R_Arrow						(0x00057832 + FLASH_Data_address) // 小选中右箭头.dta
//#define	d_Menu2_X_L_Arrow						(0x00057E69 + FLASH_Data_address) // 小选中左箭头.dta
//#define	d_Menu2_VIBRATE2						(0x000584A0 + FLASH_Data_address) // 震动 - 副本.dta
//#define	d_AUTO_BMP									(0x00058EE2 + FLASH_Data_address) // AUTO_LOGO.bmp
//#define	d_SMART_BMP									(0x0005CC1E + FLASH_Data_address) // SMART_LOGO.bmp
//#define	d_KeyLedDark_BMP						(0x00060AFA + FLASH_Data_address) // 按键灯暗.bmp
//#define	d_KeyLedLight_BMP						(0x0006144A + FLASH_Data_address) // 按键灯亮.bmp
//#define	d_Default_BMP								(0x00061D9A + FLASH_Data_address) // 回复出厂值_LOGO.bmp
//#define	d_ScreenDark_BMP						(0x0006447A + FLASH_Data_address) // 屏亮度暗.bmp
//#define	d_ScreenLight_BMP						(0x00064D86 + FLASH_Data_address) // 屏亮度亮.bmp
//#define	d_LickRes_BMP								(0x00065692 + FLASH_Data_address) // 锁阻值_LOGO.bmp
//#define	d_PULL_BMP									(0x0006804A + FLASH_Data_address) // 吸烟口数LOGO.bmp
//#define	d_PULLTim_BMP								(0x0006833E + FLASH_Data_address) // 吸烟时长LOGO.bmp
//#define	d_NEW_ATOMIZEER_BMP					(0x0006874E + FLASH_Data_address) // NEW_ATOMIZEER-144-163.bmp
//#define	d_USB_error1_BMP						(0x000696B6 + FLASH_Data_address) // USB异常-79-44,.bmp
//#define	d_USB_error2_BMP						(0x0006E85E + FLASH_Data_address) // USB异常-121-129.bmp
//#define	d_OverTim_BMP								(0x0006F846 + FLASH_Data_address) // 超时-141-135.bmp
//#define	d_LowBatt1_BMP							(0x000707AE + FLASH_Data_address) // 低电量-85-55.bmp
//#define	d_LowBatt2_BMP							(0x00074372 + FLASH_Data_address) // 低电量-117-153.bmp
//#define	d_TooHot_BMP								(0x00075532 + FLASH_Data_address) // 过热-137-136.bmp
//#define	d_UnlockADDSUB_BMP					(0x000766F2 + FLASH_Data_address) // 解锁屏幕.bmp
//#define	d_GOTO_Menu_BMP							(0x0009BF3A + FLASH_Data_address) // 进入主菜单.bmp
//#define	d_ATOMIZEER_BMP							(0x000C1782 + FLASH_Data_address) // 连接雾化器-55-77.bmp
//#define	d_Open_ATOMIZEER_BMP				(0x000C8FAA + FLASH_Data_address) // 雾化器-137-136.bmp
//#define	d_Main_BYPASS_Name					(0x000CA16A + FLASH_Data_address) // BYPASS-52-39.bmp
//#define	d_Main_BYPASS_BMP						(0x000CD072 + FLASH_Data_address) // BYPASS-94-90.bmp
//#define	d_Main_CCT_Name							(0x000D0216 + FLASH_Data_address) // CCT-78-39.bmp
//#define	d_Main_CCV_Name							(0x000D1306 + FLASH_Data_address) // CCV-78-39.bmp
//#define	d_Main_CCW_Name							(0x000D23F6 + FLASH_Data_address) // CCW-74-39.bmp
//#define	d_Main_CCBottom_BMP					(0x000D373A + FLASH_Data_address) // CC底图-0-46.bmp
//#define	d_Main_AUTO_BMP							(0x000EC8C2 + FLASH_Data_address) // Main_AUTO.bmp
//#define	d_Main_SMART_BMP						(0x000ECA92 + FLASH_Data_address) // MainSMART.bmp
//#define	d_Main_TCRM1_Name						(0x000ECC62 + FLASH_Data_address) // TCRM1-86-38.bmp
//#define	d_Main_TCRM2_Name						(0x000EDC12 + FLASH_Data_address) // TCRM2-86-38.bmp
//#define	d_Main_VTNI_Name						(0x000EEBC2 + FLASH_Data_address) // VTNI-86-38.bmp
//#define	d_Main_VTSS_Name						(0x000EFB72 + FLASH_Data_address) // VTSS-86-39.bmp
//#define	d_Main_VTTI_Name						(0x000F0B22 + FLASH_Data_address) // VTTI-86-39.bmp
//#define	d_Main_VTBottom_BMP					(0x000F1A4A + FLASH_Data_address) // VT底图-0-40.bmp
//#define	d_Main_VV_Name							(0x0010B352 + FLASH_Data_address) // VV-86-38.bmp
//#define	d_Main_VWH_Name							(0x0010C27A + FLASH_Data_address) // VWH-76-38.bmp
//#define	d_Main_VWN_Name							(0x0010D812 + FLASH_Data_address) // VWN-76-37.bmp
//#define	d_Main_VWS_Name							(0x0010EE5A + FLASH_Data_address) // VWS-76-38.bmp
//#define	d_LockADDSUB_BMP						(0x001103F2 + FLASH_Data_address) // 按键锁-110-291.bmp
//#define	d_MainBottomDark						(0x001106E2 + FLASH_Data_address) // 主界面背景底图-0-40.bmp
//#define	d_MainBottomLight						(0x00129FEA + FLASH_Data_address) // 主界面背景底图2-0-40.bmp
//#define	d_MainBottomBelow						(0x001438F2 + FLASH_Data_address) // 主界面下栏-0-258.bmp
//#define	d_MainSP_PM3								(0x0014AD7A + FLASH_Data_address) // 23-122.bmp
//#define	d_MainSP_PM4								(0x0014E7F2 + FLASH_Data_address) // --23-122.bmp
//#define	d_MainSP_PM5								(0x0015226A + FLASH_Data_address) // -----23-122.bmp
//#define	d_MainSP_PM11								(0x00155CE2 + FLASH_Data_address) // 灰..11-122.bmp
//#define	d_MainSP_PM12								(0x00163092 + FLASH_Data_address) // 灰11-122.bmp
//#define	d_MainSP_PM13								(0x00170442 + FLASH_Data_address) // 灰11-155.dta
//#define	d_MainSP_PM14								(0x00170D7F + FLASH_Data_address) // 灰11-184.dta
//#define	d_MainSP_PM15								(0x001718B7 + FLASH_Data_address) // 灰23-122.bmp
//#define	d_MainSP_PM16								(0x0017532F + FLASH_Data_address) // 灰30-213.bmp
//#define	d_MainSP_PM17								(0x0017609B + FLASH_Data_address) // 灰153-213.bmp
//#define	d_MainSP_PM18								(0x00176E07 + FLASH_Data_address) // 灰200-155.dta
//#define	d_MainSP_PM19								(0x00177795 + FLASH_Data_address) // 灰202-184.dta
//#define	d_MainSP_PM20								(0x001782CD + FLASH_Data_address) // 灰第一85-232.bmp
//#define	d_Charg_Shell								(0x00178A31 + FLASH_Data_address) // 充电30-101.bmp
//#define	d_Main_H_R_PNG1							(0x0017A021 + FLASH_Data_address) // H1右 (1).dta
//#define	d_Main_H_L_PNG1							(0x0017C089 + FLASH_Data_address) // H1右 (2).dta
//#define	d_Main_H_R_PNG2							(0x0017E0F1 + FLASH_Data_address) // H1右 (3).dta
//#define	d_Main_H_L_PNG2							(0x00180159 + FLASH_Data_address) // H1右 (4).dta
//#define	d_Main_H_R_PNG3							(0x001821C1 + FLASH_Data_address) // H1右 (5).dta
//#define	d_Main_H_L_PNG3							(0x00184229 + FLASH_Data_address) // H1右 (6).dta
//#define	d_Main_N_L_PNG1							(0x00186291 + FLASH_Data_address) // N3左 (1).dta
//#define	d_Main_N_R_PNG1							(0x001882F9 + FLASH_Data_address) // N3左 (2).dta
//#define	d_Main_N_L_PNG2							(0x0018A361 + FLASH_Data_address) // N3左 (3).dta
//#define	d_Main_N_R_PNG2							(0x0018C3C9 + FLASH_Data_address) // N3左 (4).dta
//#define	d_Main_N_L_PNG3							(0x0018E431 + FLASH_Data_address) // N3左 (5).dta
//#define	d_Main_N_R_PNG3							(0x00190499 + FLASH_Data_address) // N3左 (6).dta
//#define	d_Main_S_L_PNG1							(0x00192501 + FLASH_Data_address) // S2右 (2).dta
//#define	d_Main_S_R_PNG1							(0x00194569 + FLASH_Data_address) // S2右 (3).dta
//#define	d_Main_S_L_PNG2							(0x001965D1 + FLASH_Data_address) // S2右 (4).dta
//#define	d_Main_S_R_PNG2							(0x00198639 + FLASH_Data_address) // S2右 (5).dta
//#define	d_Main_S_L_PNG3							(0x0019A6A1 + FLASH_Data_address) // S2右 (6).dta
//#define	d_Main_S_R_PNG3							(0x0019C709 + FLASH_Data_address) // S2右 (7).dta
//#define	d_Main_SP_L_PNG1						(0x0019E771 + FLASH_Data_address) // SP3左 (1).dta
//#define	d_Main_SP_L_PNG2						(0x0019F7FB + FLASH_Data_address) // SP3左 (2).dta
//#define	d_Main_SP_R_PNG1						(0x001A0885 + FLASH_Data_address) // SP3左 (3).dta
//#define	d_Main_SP_R_PNG2						(0x001A190F + FLASH_Data_address) // SP3左 (4).dta
//#define	d_Main_SP_L_PNG3						(0x001A2999 + FLASH_Data_address) // SP3左 (5).dta
//#define	d_Main_SP_R_PNG3						(0x001A3A23 + FLASH_Data_address) // SP3左 (6).dta
//#define	d_Main_VT_PNG1							(0x001A4AAD + FLASH_Data_address) // 温控模式1.dta
//#define	d_Main_VT_PNG2							(0x001AFD31 + FLASH_Data_address) // 温控模式2.dta
//#define	d_Main_VT_PNG3							(0x001BAFB5 + FLASH_Data_address) // 温控模式3.dta
//#define	d_Main_SP_L1								(0x001C6239 + FLASH_Data_address) // SP-L1.dta
//#define	d_Main_SP_L2								(0x001C62DF + FLASH_Data_address) // SP-L2.dta
//#define	d_Main_SP_L3								(0x001C6385 + FLASH_Data_address) // SP-L3.dta
//#define	d_Main_SP_L4								(0x001C6563 + FLASH_Data_address) // SP-L4.dta
//#define	d_Main_SP_L5								(0x001C6762 + FLASH_Data_address) // SP-L5.dta
//#define	d_Main_SP_L6								(0x001C6ACC + FLASH_Data_address) // SP-L6.dta
//#define	d_Main_SP_L7								(0x001C6E0F + FLASH_Data_address) // SP-L7.dta
//#define	d_Main_SP_L8								(0x001C726F + FLASH_Data_address) // SP-L8.dta
//#define	d_Main_SP_L9								(0x001C772F + FLASH_Data_address) // SP-L9.dta
//#define	d_Main_SP_L10								(0x001C7A87 + FLASH_Data_address) // SP-L10.dta
//#define	d_Main_SP_R1								(0x001C7ECF + FLASH_Data_address) // SP-R1.dta
//#define	d_Main_SP_R2								(0x001C7F75 + FLASH_Data_address) // SP-R2.dta
//#define	d_Main_SP_R3								(0x001C8039 + FLASH_Data_address) // SP-R3.dta
//#define	d_Main_SP_R4								(0x001C8217 + FLASH_Data_address) // SP-R4.dta
//#define	d_Main_SP_R5								(0x001C8416 + FLASH_Data_address) // SP-R5.dta
//#define	d_Main_SP_R6								(0x001C8759 + FLASH_Data_address) // SP-R6.dta
//#define	d_Main_SP_R7								(0x001C8A9C + FLASH_Data_address) // SP-R7.dta
//#define	d_Main_SP_R8								(0x001C8EFC + FLASH_Data_address) // SP-R8.dta
//#define	d_Main_SP_R9								(0x001C93F8 + FLASH_Data_address) // SP-R9.dta
//#define	d_Main_SP_R10								(0x001C9750 + FLASH_Data_address) // SP-R10.dta



#define	d_Boot_animation						(0x00000000 + FLASH_Data_address) // 开机界面.gif
#define	d_OMNI_LOGO									(0x000182DB + FLASH_Data_address) // OMNI_LOGO.bmp
#define	d_Vaporess_LOGO							(0x000195A3 + FLASH_Data_address) // Vaporess_LOGO.bmp
#define	d_EXIT_ON_Bottom						(0x0001EBB3 + FLASH_Data_address) // EXIT_ON-66-280.bmp
#define	d_EXIT_Bottom								(0x00020BC7 + FLASH_Data_address) // EXIT-66-280.bmp
#define	d_Demarcation_line					(0x00022BDB + FLASH_Data_address) // 菜单分界线-2-218.bmp
#define	d_MenuNameBottom						(0x00024663 + FLASH_Data_address) // 菜单名称底图-0-0.bmp
#define	d_Menu_BP										(0x0002938B + FLASH_Data_address) // BP.bmp
#define	d_Menu_CC_SET								(0x0002ACC3 + FLASH_Data_address) // CC_SET.bmp
#define	d_Menu_CCT_NI								(0x0002C58B + FLASH_Data_address) // CCT_NI.bmp
#define	d_Menu_CCT_SS								(0x0002DF33 + FLASH_Data_address) // CCT_SS.bmp
#define	d_Menu_CCT_TI								(0x0002F8DB + FLASH_Data_address) // CCT_TI.bmp
#define	d_Menu_CCV									(0x00031283 + FLASH_Data_address) // CCV.bmp
#define	d_Menu_CCW									(0x00032B4B + FLASH_Data_address) // CCW.bmp
#define	d_Menu_DIY									(0x00034413 + FLASH_Data_address) // DIY.bmp
#define	d_Menu_LOCK_R								(0x00035CDB + FLASH_Data_address) // LOCK_R.bmp
#define	d_Menu_SET									(0x000375A3 + FLASH_Data_address) // SET.bmp
#define	d_Menu_SET2									(0x00038E6B + FLASH_Data_address) // SET2.bmp
#define	d_Menu_SP										(0x0003A733 + FLASH_Data_address) // SP.bmp
#define	d_Menu_TCR_M1								(0x0003C58F + FLASH_Data_address) // TCR_M1.bmp
#define	d_Menu_TCR_M2								(0x0003DE57 + FLASH_Data_address) // TCR_M2.bmp
#define	d_Menu_VT_NI								(0x0003F71F + FLASH_Data_address) // VT_NI.bmp
#define	d_Menu_VT_SET								(0x00040FE7 + FLASH_Data_address) // VT_SET.bmp
#define	d_Menu_VT_SS								(0x000428AF + FLASH_Data_address) // VT_SS.bmp
#define	d_Menu_VT_TI								(0x00044177 + FLASH_Data_address) // VT_TI.bmp
#define	d_Menu_VV										(0x00045A3F + FLASH_Data_address) // VV.bmp
#define	d_Menu_VW_H									(0x00047377 + FLASH_Data_address) // VW_H.bmp
#define	d_Menu_VW_N									(0x00048BCF + FLASH_Data_address) // VW_N.bmp
#define	d_Menu_VW_S									(0x0004A497 + FLASH_Data_address) // VW_S.bmp
#define	d_Menu_VW_SET								(0x0004BCEF + FLASH_Data_address) // VW_SET.bmp
#define	d_SelectMenuBottom					(0x0004D5B7 + FLASH_Data_address) // 图标选中框.dta
#define	d_Menu2_AUTO								(0x000515F3 + FLASH_Data_address) // AUTO.dta
#define	d_Menu2_RTC									(0x00051AB3 + FLASH_Data_address) // RTC设置.dta
#define	d_Menu2_SMART								(0x00051F37 + FLASH_Data_address) // SMART.dta
#define	d_Menu2_KeyLed							(0x000522D7 + FLASH_Data_address) // 按键灯.dta
#define	d_Menu2_VERSION							(0x0005275B + FLASH_Data_address) // 版本信息.dta
#define	d_Menu2_Default							(0x00052AFB + FLASH_Data_address) // 恢复出厂值.dta
#define	d_Menu2_ScreensaverTim			(0x00052FF1 + FLASH_Data_address) // 屏保时长.dta
#define	d_Menu2_ScreenLight					(0x00053391 + FLASH_Data_address) // 屏幕亮度.dta
#define	d_Menu2_PULL								(0x00053851 + FLASH_Data_address) // 吸烟口数.dta
#define	d_Menu2_VIBRATE							(0x00053C63 + FLASH_Data_address) // 震动.dta
#define	d_Menu2_D_NO_R_Arrow				(0x00054123 + FLASH_Data_address) // 大未选中右箭头.dta
#define	d_Menu2_D_NO_L_Arrow				(0x00054B5F + FLASH_Data_address) // 大未选中左箭头.dta
#define	d_Menu2_D_R_Arrow						(0x00055547 + FLASH_Data_address) // 大选中右箭头.dta
#define	d_Menu2_D_L_Arrow						(0x00055F83 + FLASH_Data_address) // 大选中左箭头.dta
#define	d_Main_LOCK_R_PNG						(0x0005696B + FLASH_Data_address) // 电阻欧姆2.dta
#define	d_Menu2_X_NO_R_Arrow				(0x00056BC4 + FLASH_Data_address) // 小未选中右箭头.dta
#define	d_Menu2_X_NO_L_Arrow				(0x000571FB + FLASH_Data_address) // 小未选中左箭头.dta
#define	d_Menu2_X_R_Arrow						(0x00057832 + FLASH_Data_address) // 小选中右箭头.dta
#define	d_Menu2_X_L_Arrow						(0x00057E69 + FLASH_Data_address) // 小选中左箭头.dta
#define	d_Menu2_VIBRATE2						(0x000584A0 + FLASH_Data_address) // 震动 - 副本.dta
#define	d_AUTO_BMP									(0x00058EE2 + FLASH_Data_address) // AUTO_LOGO.bmp
#define	d_SMART_BMP									(0x0005CC1E + FLASH_Data_address) // SMART_LOGO.bmp
#define	d_KeyLedDark_BMP						(0x00060AFA + FLASH_Data_address) // 按键灯暗.bmp
#define	d_KeyLedLight_BMP						(0x0006144A + FLASH_Data_address) // 按键灯亮.bmp
#define	d_Default_BMP								(0x00061D9A + FLASH_Data_address) // 回复出厂值_LOGO.bmp
#define	d_ScreenDark_BMP						(0x0006447A + FLASH_Data_address) // 屏亮度暗.bmp
#define	d_ScreenLight_BMP						(0x00064D86 + FLASH_Data_address) // 屏亮度亮.bmp
#define	d_LickRes_BMP								(0x00065692 + FLASH_Data_address) // 锁阻值_LOGO.bmp
#define	d_PULL_BMP									(0x0006804A + FLASH_Data_address) // 吸烟口数LOGO.bmp
#define	d_PULLTim_BMP								(0x0006833E + FLASH_Data_address) // 吸烟时长LOGO.bmp
#define	d_NEW_ATOMIZEER_BMP					(0x0006874E + FLASH_Data_address) // NEW_ATOMIZEER-144-163.bmp
#define	d_USB_error1_BMP						(0x000696B6 + FLASH_Data_address) // USB异常-79-44,.bmp
#define	d_USB_error2_BMP						(0x0006E85E + FLASH_Data_address) // USB异常-121-129.bmp
#define	d_OverTim_BMP								(0x0006F846 + FLASH_Data_address) // 超时-141-135.bmp
#define	d_LowBatt1_BMP							(0x000707AE + FLASH_Data_address) // 低电量-85-55.bmp
#define	d_LowBatt2_BMP							(0x00074372 + FLASH_Data_address) // 低电量-117-153.bmp
#define	d_TooHot_BMP								(0x00075532 + FLASH_Data_address) // 过热-137-136.bmp
#define	d_UnlockADDSUB_BMP					(0x000766F2 + FLASH_Data_address) // 解锁屏幕.bmp
#define	d_GOTO_Menu_BMP							(0x0009BF3A + FLASH_Data_address) // 进入主菜单.bmp
#define	d_ATOMIZEER_BMP							(0x000C1782 + FLASH_Data_address) // 连接雾化器-55-77.bmp
#define	d_Open_ATOMIZEER_BMP				(0x000C8FAA + FLASH_Data_address) // 雾化器-137-136.bmp
#define	d_Main_BYPASS_Name					(0x000CA16A + FLASH_Data_address) // BYPASS-52-39.bmp
#define	d_Main_BYPASS_BMP						(0x000CD072 + FLASH_Data_address) // BYPASS-94-90.bmp
#define	d_Main_CCT_Name							(0x000D0216 + FLASH_Data_address) // CCT-78-39.bmp
#define	d_Main_CCV_Name							(0x000D1306 + FLASH_Data_address) // CCV-78-39.bmp
#define	d_Main_CCW_Name							(0x000D23F6 + FLASH_Data_address) // CCW-74-39.bmp
#define	d_Main_CCBottom_BMP					(0x000D373A + FLASH_Data_address) // CC底图-0-46.bmp
#define	d_Main_AUTO_BMP							(0x000EC8C2 + FLASH_Data_address) // Main_AUTO.bmp
#define	d_Main_SMART_BMP						(0x000ECA92 + FLASH_Data_address) // MainSMART.bmp
#define	d_Main_TCRM1_Name						(0x000ECC62 + FLASH_Data_address) // TCRM1-86-38.bmp
#define	d_Main_TCRM2_Name						(0x000EDC12 + FLASH_Data_address) // TCRM2-86-38.bmp
#define	d_Main_VTNI_Name						(0x000EEBC2 + FLASH_Data_address) // VTNI-86-38.bmp
#define	d_Main_VTSS_Name						(0x000EFB72 + FLASH_Data_address) // VTSS-86-39.bmp
#define	d_Main_VTTI_Name						(0x000F0B22 + FLASH_Data_address) // VTTI-86-39.bmp
#define	d_Main_VTBottom_BMP					(0x000F1A4A + FLASH_Data_address) // VT底图-0-40.bmp
#define	d_Main_VV_Name							(0x0010B352 + FLASH_Data_address) // VV-86-38.bmp
#define	d_Main_VWH_Name							(0x0010C27A + FLASH_Data_address) // VWH-76-38.bmp
#define	d_Main_VWN_Name							(0x0010D812 + FLASH_Data_address) // VWN-76-37.bmp
#define	d_Main_VWS_Name							(0x0010EE5A + FLASH_Data_address) // VWS-76-38.bmp
#define	d_LockADDSUB_BMP						(0x001103F2 + FLASH_Data_address) // 按键锁-110-291.bmp
#define	d_MainBottomDark						(0x001106E2 + FLASH_Data_address) // 主界面背景底图-0-40.bmp
#define	d_MainBottomLight						(0x00129FEA + FLASH_Data_address) // 主界面背景底图2-0-40.bmp
#define	d_MainBottomBelow						(0x001438F2 + FLASH_Data_address) // 主界面下栏-0-258.bmp
#define	d_MainSP_PM3								(0x0014AD7A + FLASH_Data_address) // 23-122.bmp
#define	d_MainSP_PM4								(0x0014E7F2 + FLASH_Data_address) // --23-122.bmp
#define	d_MainSP_PM5								(0x0015226A + FLASH_Data_address) // -----23-122.bmp
#define	d_MainSP_PM11								(0x00155CE2 + FLASH_Data_address) // 灰..11-122.bmp
#define	d_MainSP_PM12								(0x00163092 + FLASH_Data_address) // 灰11-122.bmp
#define	d_MainSP_PM13								(0x00170442 + FLASH_Data_address) // 灰11-155.dta
#define	d_MainSP_PM14								(0x001709F2 + FLASH_Data_address) // 灰11-184.dta
#define	d_MainSP_PM15								(0x0017152A + FLASH_Data_address) // 灰23-122.bmp
#define	d_MainSP_PM16								(0x00174FA2 + FLASH_Data_address) // 灰30-213.bmp
#define	d_MainSP_PM17								(0x00175D0E + FLASH_Data_address) // 灰153-213.bmp
#define	d_MainSP_PM18								(0x00176A7A + FLASH_Data_address) // 灰200-155.dta
#define	d_MainSP_PM19								(0x00177072 + FLASH_Data_address) // 灰202-184.dta
#define	d_MainSP_PM20								(0x00177BAA + FLASH_Data_address) // 灰第一85-232.bmp
#define	d_Charg_Shell								(0x0017830E + FLASH_Data_address) // 充电30-101.bmp
#define	d_Main_H_R_PNG1							(0x001798FE + FLASH_Data_address) // H1右 (1).dta
#define	d_Main_H_L_PNG1							(0x0017B966 + FLASH_Data_address) // H1右 (2).dta
#define	d_Main_H_R_PNG2							(0x0017D9CE + FLASH_Data_address) // H1右 (3).dta
#define	d_Main_H_L_PNG2							(0x0017FA36 + FLASH_Data_address) // H1右 (4).dta
#define	d_Main_H_R_PNG3							(0x00181A9E + FLASH_Data_address) // H1右 (5).dta
#define	d_Main_H_L_PNG3							(0x00183B06 + FLASH_Data_address) // H1右 (6).dta
#define	d_Main_N_L_PNG1							(0x00185B6E + FLASH_Data_address) // N3左 (1).dta
#define	d_Main_N_R_PNG1							(0x00187BD6 + FLASH_Data_address) // N3左 (2).dta
#define	d_Main_N_L_PNG2							(0x00189C3E + FLASH_Data_address) // N3左 (3).dta
#define	d_Main_N_R_PNG2							(0x0018BCA6 + FLASH_Data_address) // N3左 (4).dta
#define	d_Main_N_L_PNG3							(0x0018DD0E + FLASH_Data_address) // N3左 (5).dta
#define	d_Main_N_R_PNG3							(0x0018FD76 + FLASH_Data_address) // N3左 (6).dta
#define	d_Main_S_L_PNG1							(0x00191DDE + FLASH_Data_address) // S2右 (2).dta
#define	d_Main_S_R_PNG1							(0x00193E46 + FLASH_Data_address) // S2右 (3).dta
#define	d_Main_S_L_PNG2							(0x00195EAE + FLASH_Data_address) // S2右 (4).dta
#define	d_Main_S_R_PNG2							(0x00197F16 + FLASH_Data_address) // S2右 (5).dta
#define	d_Main_S_L_PNG3							(0x00199F7E + FLASH_Data_address) // S2右 (6).dta
#define	d_Main_S_R_PNG3							(0x0019BFE6 + FLASH_Data_address) // S2右 (7).dta
#define	d_Main_SP_L_PNG1						(0x0019E04E + FLASH_Data_address) // SP3左 (1).dta
#define	d_Main_SP_L_PNG2						(0x0019F0D8 + FLASH_Data_address) // SP3左 (2).dta
#define	d_Main_SP_R_PNG1						(0x001A0162 + FLASH_Data_address) // SP3左 (3).dta
#define	d_Main_SP_R_PNG2						(0x001A11EC + FLASH_Data_address) // SP3左 (4).dta
#define	d_Main_SP_L_PNG3						(0x001A2276 + FLASH_Data_address) // SP3左 (5).dta
#define	d_Main_SP_R_PNG3						(0x001A3300 + FLASH_Data_address) // SP3左 (6).dta
#define	d_Main_VT_PNG1							(0x001A438A + FLASH_Data_address) // 温控模式1.dta
#define	d_Main_VT_PNG2							(0x001AF60E + FLASH_Data_address) // 温控模式2.dta
#define	d_Main_VT_PNG3							(0x001BA892 + FLASH_Data_address) // 温控模式3.dta
#define	d_Main_SP_L1								(0x001C5B16 + FLASH_Data_address) // SP-L1.dta
#define	d_Main_SP_L2								(0x001C5BBC + FLASH_Data_address) // SP-L2.dta
#define	d_Main_SP_L3								(0x001C5C62 + FLASH_Data_address) // SP-L3.dta
#define	d_Main_SP_L4								(0x001C5E40 + FLASH_Data_address) // SP-L4.dta
#define	d_Main_SP_L5								(0x001C603F + FLASH_Data_address) // SP-L5.dta
#define	d_Main_SP_L6								(0x001C63A9 + FLASH_Data_address) // SP-L6.dta
#define	d_Main_SP_L7								(0x001C66EC + FLASH_Data_address) // SP-L7.dta
#define	d_Main_SP_L8								(0x001C6B4C + FLASH_Data_address) // SP-L8.dta
#define	d_Main_SP_L9								(0x001C700C + FLASH_Data_address) // SP-L9.dta
#define	d_Main_SP_L10								(0x001C7364 + FLASH_Data_address) // SP-L10.dta
#define	d_Main_SP_R1								(0x001C77AC + FLASH_Data_address) // SP-R1.dta
#define	d_Main_SP_R2								(0x001C7852 + FLASH_Data_address) // SP-R2.dta
#define	d_Main_SP_R3								(0x001C7916 + FLASH_Data_address) // SP-R3.dta
#define	d_Main_SP_R4								(0x001C7AF4 + FLASH_Data_address) // SP-R4.dta
#define	d_Main_SP_R5								(0x001C7CF3 + FLASH_Data_address) // SP-R5.dta
#define	d_Main_SP_R6								(0x001C8036 + FLASH_Data_address) // SP-R6.dta
#define	d_Main_SP_R7								(0x001C8379 + FLASH_Data_address) // SP-R7.dta
#define	d_Main_SP_R8								(0x001C87D9 + FLASH_Data_address) // SP-R8.dta
#define	d_Main_SP_R9								(0x001C8CD5 + FLASH_Data_address) // SP-R9.dta
#define	d_Main_SP_R10								(0x001C902D + FLASH_Data_address) // SP-R10.dta





















//////////////





#endif


