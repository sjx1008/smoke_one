#ifndef __APP_USB_H
#define __APP_USB_H
#include "main.h"

#define		encryption_Key	0xA5				//定义加密符号

#define USB_Product_name        "Luxe"   					// 产品名称
#define USB_Software_version  	"Luxe_Ver1.04"  		// 软件版本
#define USB_Hardware_version    "STW9228_V1.0"  	// Hardward vision

#define		d_IAP_Flash_Start_Address		0x08000000			//定义IAP程序空间的起始地址

#define 	APP_DEFAULT_ADD             0x08010000			//定义APP起始地址
#define 	APP_DEFAULT_ADD_SIZE        0x70000					//定义APP数据长度
#define 	APP_DEFAULT_ADD_Backups     0x08010000			//定义备份APP起始地址
#define 	APP_DEFAULT_Backups_SIZE		0x70000					//备份APP数据长度



//定义USB辅助命令
	typedef enum
	{
		R_Cmd_CURVE  		=	0x01,	// 读曲线数组
		W_Cmd_CURVE  		=	0x02,	// 写曲线数组
		R_Cmd_TCR    		=	0x03,  	// 读TCR参数
		W_Cmd_TCR    		=	0x04,  	// 写TCR参数
		R_Cmd_UI    		=	0x05,  	// 读警告图片
		W_Cmd_UI    		=	0x06,  	// 写警告图片
	}RW_Cmd_USB_TypeDef;




	typedef enum
	{
		M_Ni  				=	0x01,
		M_Ti  				=	0x02,
		M_Fe    			=	0x03,
		M_Ss    			=	0x04,
		M_NiCr    		=	0x05,
		M_M1    			=	0x81,
		M_M2    			=	0x82,
	}Material_TypeDef;


//定义USB运行状态
	typedef enum
	{
		S_USB_NOP=0,				//闲
		S_USB_APP=1,				//接收APP数据
		S_USB_APPEND=2,			//结束接收APP数据
		S_USB_LOGO=3,				//接收LOGO数据
		S_USB_LOGOEND=4,		//结束接收LOGO数据
		S_USB_FLASH=5,		//
		S_USB_TCR			  = 6,		//接收TCR数据中
		S_USB_CURVE			= 7,		//接收CURVE数据中
		S_USB_UI_R			= 8,		//上传UI数据中
		S_USB_UI_W			= 9		//接收UI数据中
	}USB_state;

//	//定义USB运行状态使能
//	typedef enum
//	{
//		S_USB_Disability=0,		//失能
//		S_USB_Enable_APP=1,				//使能接收APP
//		S_USB_Enable_LOGO=2,			//使能接收LOGO
//	}USB_Enable;


//定义USB指令
	typedef enum
	{
		Query_parameters=   0xA0,  // 询问电子烟参数
		SEND_PRO_BEGIN=   	0x30,  	// 发送编程形如开始
		SEND_DATA=        	0x00,   // 发送数据
		SEND_DATA_END=    	0x10,   // 发送数据结束
		SEND_LOGO_BEGIN=  	0x70,   // 下载开机LEGO 开始
		SEND_LOGO_DATA= 		0x80,   // 下载开机LEGO 数据
		SEND_LOGO_END=    	0x90,   // 下载开机LEGO 结束
		DATA_ICT		=    		0xB0,		// 读、写电子烟参数（UI、TCR、曲线数组等）
	}CmdTypeDef_USB;

//定义程序更新回复消息
	typedef enum
	{
		RETURN_RIGHT=   0xAA,   // 反馈正确
		RETURN_ERROR=   0x55,   // 反馈出错
		RETURN_NONSUPPORT 	= 	0x5F,	// 不支持
	}Cmdreply_USB;

	typedef union
	{
		u8 chars[60];
		u32 ints[15];
	}INT_60byte;

	typedef union
	{
		u8 chars[16];
		u32 ints[4];
	}INT_4byte;


	typedef union
	{
		u8 chars[4];
		u32 ints;
	}INT_32bit;

	typedef union
	{
		u8 chars[2];
		u16 ints;
	}INT_16bit;

	//定义2K缓存 共用体
	typedef union
	{
		u8	MAL_Buffer_8[2048];
		u16	MAL_Buffer_16[1024];
		u32	MAL_Buffer_32[512];
	}Cache_2K;


/*程序升级数据结构---------------------*/
	typedef struct
	{
		//u8		Hardware_version[16];		//硬件版本号
		u8		Software_version[16];		//软件版本号
		u8		Serial_number[16];			//序列号
		u32		base_address;						//写FLASH数据地址
		u32		Data_ALL_number;				//程序Byte总个数
		u32		Data_current_i;					//程序Byte当前个数
		//u8		Package_check;					//单个包校验
		//u8		Data_length;						//数据长度
		u32		ALL_checksum;						//所有数据检验和
		u32		DATA_checksum;					//所发数据检验和
		u16		Page_sequence;					//数据包序列
	}APP_upgrade;

/*图片下载数据结构---------------------*/
	typedef struct
	{
		u16	LOGO_wide;
		u16	LOGO_high;
		u16	Data_ALL_number;				//数据Byte总个数
		u16	Data_current_i;					//数据Byte当前个数
		u16	LOGO_i;
		u16	Page_sequence;					//数据包序列
	}LOGO_upgrade;

extern	Cache_2K	R_MAL_Buffer;				//定义2K缓存
extern	APP_upgrade		R_APP_TypeDef;		//定义烧录程序数据结构
//extern	LOGO_upgrade		R_LOGO_TypeDef;		//定义LOGO数据结构
extern	u8 	Send_Buffer[];		//定义USB发送缓存
extern	u8 	Report_buf[];
extern	u8	B_Accept_Data_OK;
//extern	u8	R_return_USB;		//答复上位机信息
extern	u16	USBovertime;		//超时计时
//extern	u8	R_USB_Enable;		//usb失能模式
extern	USB_state R_USB_state;	//USB工作状态
//////////////////////////////////////////
//求数据校验和
extern	u8 checksum_usbdata(u8	*buf);
//数据解密
extern	void	decrypt_data(void);
	//提取第0包信息
extern	void pro_first_program(void);
//提取程序数据
extern	void pro_program_data(void);
//最后一包数据
extern	void pro_program_end(void);
/********************************************/
//接收LOGO第0包数据
extern	void LOGO_pro_first_program(void);
//提取LOGO数据
extern	void LOGO_pro_program_data(void);
//最后一包数据
extern	void LOGO_pro_program_end(void);

extern	void	USB_state_program(void);
extern	void	USB_Query_parameters(void);
extern	void	USB_R_W_parameters(void);
//数据加密
extern	void	encryption_data(void);


extern	void	Handle_SEND_LOGO_BEGIN(void);
extern	void	Handle_SEND_LOGO_DATA(void);
extern	void	FLASH_Data_checksum_usbdata(void);
extern	void	Handle_SEND_LOGO_END(void);

/////////////////////USB上电处理////////////////

extern	u8	B_USB_PWER_JC;
extern	u8	B_USB_PWER;					//0：关闭USB   1：开启USB
extern	u8	B_USB_PWER_Q;		//0：关闭USB   1：开启USB
extern	u8	B_USB_chalu;			//0：USB拔出			1：USB插入
extern	u8	B_USB_Computer;

extern	void	USB_PWER_program(void);
extern	void	USB_ENABLE_transmission(void);
extern	void	USB_DISABLE_transmission(void);




#endif


