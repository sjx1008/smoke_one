#ifndef __APP_USB_H
#define __APP_USB_H
#include "main.h"

#define		encryption_Key	0xA5				//������ܷ���

#define USB_Product_name        "Luxe"   					// ��Ʒ����
#define USB_Software_version  	"Luxe_Ver1.04"  		// ����汾
#define USB_Hardware_version    "STW9228_V1.0"  	// Hardward vision

#define		d_IAP_Flash_Start_Address		0x08000000			//����IAP����ռ����ʼ��ַ

#define 	APP_DEFAULT_ADD             0x08010000			//����APP��ʼ��ַ
#define 	APP_DEFAULT_ADD_SIZE        0x70000					//����APP���ݳ���
#define 	APP_DEFAULT_ADD_Backups     0x08010000			//���屸��APP��ʼ��ַ
#define 	APP_DEFAULT_Backups_SIZE		0x70000					//����APP���ݳ���



//����USB��������
	typedef enum
	{
		R_Cmd_CURVE  		=	0x01,	// ����������
		W_Cmd_CURVE  		=	0x02,	// д��������
		R_Cmd_TCR    		=	0x03,  	// ��TCR����
		W_Cmd_TCR    		=	0x04,  	// дTCR����
		R_Cmd_UI    		=	0x05,  	// ������ͼƬ
		W_Cmd_UI    		=	0x06,  	// д����ͼƬ
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


//����USB����״̬
	typedef enum
	{
		S_USB_NOP=0,				//��
		S_USB_APP=1,				//����APP����
		S_USB_APPEND=2,			//��������APP����
		S_USB_LOGO=3,				//����LOGO����
		S_USB_LOGOEND=4,		//��������LOGO����
		S_USB_FLASH=5,		//
		S_USB_TCR			  = 6,		//����TCR������
		S_USB_CURVE			= 7,		//����CURVE������
		S_USB_UI_R			= 8,		//�ϴ�UI������
		S_USB_UI_W			= 9		//����UI������
	}USB_state;

//	//����USB����״̬ʹ��
//	typedef enum
//	{
//		S_USB_Disability=0,		//ʧ��
//		S_USB_Enable_APP=1,				//ʹ�ܽ���APP
//		S_USB_Enable_LOGO=2,			//ʹ�ܽ���LOGO
//	}USB_Enable;


//����USBָ��
	typedef enum
	{
		Query_parameters=   0xA0,  // ѯ�ʵ����̲���
		SEND_PRO_BEGIN=   	0x30,  	// ���ͱ�����翪ʼ
		SEND_DATA=        	0x00,   // ��������
		SEND_DATA_END=    	0x10,   // �������ݽ���
		SEND_LOGO_BEGIN=  	0x70,   // ���ؿ���LEGO ��ʼ
		SEND_LOGO_DATA= 		0x80,   // ���ؿ���LEGO ����
		SEND_LOGO_END=    	0x90,   // ���ؿ���LEGO ����
		DATA_ICT		=    		0xB0,		// ����д�����̲�����UI��TCR����������ȣ�
	}CmdTypeDef_USB;

//���������»ظ���Ϣ
	typedef enum
	{
		RETURN_RIGHT=   0xAA,   // ������ȷ
		RETURN_ERROR=   0x55,   // ��������
		RETURN_NONSUPPORT 	= 	0x5F,	// ��֧��
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

	//����2K���� ������
	typedef union
	{
		u8	MAL_Buffer_8[2048];
		u16	MAL_Buffer_16[1024];
		u32	MAL_Buffer_32[512];
	}Cache_2K;


/*�����������ݽṹ---------------------*/
	typedef struct
	{
		//u8		Hardware_version[16];		//Ӳ���汾��
		u8		Software_version[16];		//����汾��
		u8		Serial_number[16];			//���к�
		u32		base_address;						//дFLASH���ݵ�ַ
		u32		Data_ALL_number;				//����Byte�ܸ���
		u32		Data_current_i;					//����Byte��ǰ����
		//u8		Package_check;					//������У��
		//u8		Data_length;						//���ݳ���
		u32		ALL_checksum;						//�������ݼ����
		u32		DATA_checksum;					//�������ݼ����
		u16		Page_sequence;					//���ݰ�����
	}APP_upgrade;

/*ͼƬ�������ݽṹ---------------------*/
	typedef struct
	{
		u16	LOGO_wide;
		u16	LOGO_high;
		u16	Data_ALL_number;				//����Byte�ܸ���
		u16	Data_current_i;					//����Byte��ǰ����
		u16	LOGO_i;
		u16	Page_sequence;					//���ݰ�����
	}LOGO_upgrade;

extern	Cache_2K	R_MAL_Buffer;				//����2K����
extern	APP_upgrade		R_APP_TypeDef;		//������¼�������ݽṹ
//extern	LOGO_upgrade		R_LOGO_TypeDef;		//����LOGO���ݽṹ
extern	u8 	Send_Buffer[];		//����USB���ͻ���
extern	u8 	Report_buf[];
extern	u8	B_Accept_Data_OK;
//extern	u8	R_return_USB;		//����λ����Ϣ
extern	u16	USBovertime;		//��ʱ��ʱ
//extern	u8	R_USB_Enable;		//usbʧ��ģʽ
extern	USB_state R_USB_state;	//USB����״̬
//////////////////////////////////////////
//������У���
extern	u8 checksum_usbdata(u8	*buf);
//���ݽ���
extern	void	decrypt_data(void);
	//��ȡ��0����Ϣ
extern	void pro_first_program(void);
//��ȡ��������
extern	void pro_program_data(void);
//���һ������
extern	void pro_program_end(void);
/********************************************/
//����LOGO��0������
extern	void LOGO_pro_first_program(void);
//��ȡLOGO����
extern	void LOGO_pro_program_data(void);
//���һ������
extern	void LOGO_pro_program_end(void);

extern	void	USB_state_program(void);
extern	void	USB_Query_parameters(void);
extern	void	USB_R_W_parameters(void);
//���ݼ���
extern	void	encryption_data(void);


extern	void	Handle_SEND_LOGO_BEGIN(void);
extern	void	Handle_SEND_LOGO_DATA(void);
extern	void	FLASH_Data_checksum_usbdata(void);
extern	void	Handle_SEND_LOGO_END(void);

/////////////////////USB�ϵ紦��////////////////

extern	u8	B_USB_PWER_JC;
extern	u8	B_USB_PWER;					//0���ر�USB   1������USB
extern	u8	B_USB_PWER_Q;		//0���ر�USB   1������USB
extern	u8	B_USB_chalu;			//0��USB�γ�			1��USB����
extern	u8	B_USB_Computer;

extern	void	USB_PWER_program(void);
extern	void	USB_ENABLE_transmission(void);
extern	void	USB_DISABLE_transmission(void);




#endif


