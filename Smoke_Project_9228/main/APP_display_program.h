#ifndef __APP_display_program_H
#define __APP_display_program_H


#define	d_Bat_Volt_min		285
#define	d_Bat_Volt_max		415

#define	d_DIS_Watt_min		10
#define	d_DIS_Watt_max		800
#define	d_DIS_Watt_max_x10		8000

#define	d_DIS_Vout_min		0
#define	d_DIS_Vout_max		850

#define	d_DIS_Iout_max		26
#define	d_DIS_Iout_max_x100		2600

#define	d_DIS_TempC_min		100
#define	d_DIS_TempC_max		315

#define	d_DIS_TempF_min		200
#define	d_DIS_TempF_max		600


#define	d_Smoke_Tim_max		(R_DISP_DATA.Smoke_Tim_max*10)

extern u8	B_Display_Detect;					///��ʱˢ����Ļ��־
extern u8	B_Smoking_mark;						///���̱�־
extern u8	B_Smoking_mark_Q;					///���̱�־
extern u8	B_Power_down;							///������
extern u8	B_BAT_Twinkle;						///��ط���˸
extern u8	B_BAT_Charge;							///����־
extern u8	B_BAT_Congman;						///��������־
extern u8	B_BAT_Congman_Q;					///��������־
extern u8	B_BAT_Paoma;							///��������־
extern u8	B_Shuoji;									///������־
//extern u8	B_Shuoji_Q;								///������־
extern u8	B_Key_Shuo;								///������־
extern u8	B_PowerOFF;								///�ػ���־

//extern	u8	R_yaoshi_i;							///����Сͼ���ڵ�����
//extern	u8	R_yaoshi_i_Q;							///����Сͼ���ڵ�����
extern	u8	R_Window_keep_TimS;						///����ά������
extern	u8	R_Window_Tim_MAX;						///����ά������
extern	u8 *R_ii;
extern	uc8 *R_i2;

extern	u16	R_Win_tim;
///////���������
//extern	u8	B_Charging_1;


/*************ͯ������*******************/
extern	u8	R_now_password[];		//��ǰ����
extern	u8	R_input_password[];								//��������
extern	u8	R_input_password_x;									//��ǰ��������ĸ���
extern	u8	R_input_password_x_Q;								//��һ����������ĸ���
extern	u8	B_Password_error;								//������������־
/*************����LOGO*******************/
extern	u8	R_input_LOGO[];								//����LOGO
extern	u8	R_input_LOGO_x;									//��ǰ����LOGO�ĸ���
extern	u8	R_input_LOGO_x_Q;		//��һ������LOGO�ĸ���
extern	u8	B_Big_small;									//��һ������LOGO�ĸ���
/*************TCR����*******************/
extern	u8	R_TCR_Selected;								//ѡ�еĵ�����
/**************��ѹģʽ���������������ѹ*********************/
extern	u16	R_VoltageMAX;

extern	u8	B_Display_Power_OFF;
extern	u8	B_Display_Power_OFF_Q;

////////////////////��Ļ��������
extern	u8	R_Screen_FLIP;
extern	u8	R_Screen_Light;

/////�����л�����ʼ����
extern	u8	B_ON_DISP_BL;


//extern	u8	R_Operation_mode;

//////��ʾ״̬
typedef enum  Displays
{
	/*02*/
	Dis_The_Work	=0x02,			//��������
		/*03*/
	Dis_S_Smoke		=0x03,			//����
	/*04*/
	Dis_Power_OFF	=0x04,			//�ػ�
	/*05*/
	Dis_Shuoji		=0x05,			//����
	Dis_Jiesuo		=0x15,			//�����������
	Dis_Locked		=0x25,			//������������
	Dis_Old_password		=0x35,			//����ԭ������
	Dis_New_password		=0x45,			//�����µ�����
	/*07*/
	Dis_Charging	=0x07,			//���
	/*08*/
	Dis_Short_Circuit	=0x08,	//��·
	Dis_Open_Circuit	=0x18,	//��·
	Dis_Low_Battery		=0x28,	//�͵���
	Dis_Time_Out			=0x38,	//���̳�ʱ
	Dis_Temperature		=0x48,	//�¶ȱ���
	Dis_Empty_battery	=0x58,	//�յ���
	Dis_LOW_USB				=0x68,	//USB������
	Dis_SpeedBrake		=0x78,	//������ʾ
	Dis_limit_number	=0x88,	//���̿���������ʾ
	/*09*/
	Dis_Language	=0x09, 			//����ѡ��
	Dis_Software_version	=0x19,	//����汾
	Dis_Operation_mode	=0x29,	//������ʽ
	/*0A*/
	Dis_Atomizer_replace		=0x0A,		//��������ѯ��
	/*0B*/
	Dis_TCR_adjust		=0x0B,		//TCR����
	Dis_Custom_adjust	=0x1B,		//�Զ������ߵ���
	Dis_Screen_setting	=0x2B,		//��Ļ����
	Dis_menu						=0x3B,		//�˵�
	Dis_STATISTICS			=0x4B,		//����ͳ��
	/*0C*/
	Dis_Change_LOGO		=0x0C,		//���Ŀ���LOGO
	Dis_Firmware_data					=0x0D,		//�̼���Ϣ
	/*0E*/
	
	/*0F*/
	
	/*00*/	
	Dis_Status_NOP	=0x00
}Displays;
extern Displays		R_DisStatus,R_DisStatus_Q,R_DisStatus_S;

//////��������
typedef enum  Language
{
	English=0,			//Ӣ��
	Chinese,			//����
	Malaysia,
}Language;
extern Language		R_Language;

////////////����ģʽ
typedef enum  Work_mode
{
	d_Watt_mode=0,
	d_Bypass_mode,
	d_Temp_mode,
	d_Custom_mode,
	d_Voltage_mode,
	d_TCR_mode,
	d_NOP_mode,
}Work_mode;
extern Work_mode		R_Work_mode,R_Work_mode_Q,R_Work_mode_Set;


////////////��������
typedef enum  Atomizer
{
	Atomizer_0=0,	//Ss
	Atomizer_1,		//Ni
	Atomizer_2,		//Ti
	Atomizer_3,		//NiCr
	Atomizer_4,
	Atomizer_NC
}Atomizer;
extern Atomizer		R_Atomizer,R_Atomizer_Q,R_Atomizer_Set;

////////////��������
typedef enum  TCR_term
{
	TCR_0=0,	//M1
	TCR_1,		//M2
	TCR_2,		//M3
	TCR_NC
}TCR_term;
extern TCR_term		R_TCR_term,R_TCR_term_Q,R_TCR_term_Set;


////////////�¶ȵ�λ
typedef enum  Temp_metric
{
	C_metric=0,
	F_metric=1,
	Temp_metric_NC
}Temp_metric;
extern Temp_metric		R_Temp_metric,R_Temp_metric_Q,R_Temp_metric_Set;

/*������������---------------------*/		
	typedef struct
	{
		u16		BAT_data;			//��ص�ѹ�Ŵ�100��
		u8		BAT_vip;			//��صȼ�
		u16		Res_data;			//��ʼ��ֵ
		u16		Res_Actual;		//ʵ����ֵ
		u16		Vout_Set;			//�趨�����ѹ
		u16		Vout_Out;			//ʵ�������ѹ
		u16		Temp_Set_C;		//�趨���϶�
		u16		Temp_Out_C;		//������϶�
		u16		Temp_Set_F;		//�趨���϶�
		u16		Temp_Out_F;		//������϶�
		u16		Watt_Set;			//�趨����
		u16		Watt_Out;			//�������
		u16 	Smoke_data;		//���̿���
		u8		Smoke_Tim; 		//���̼�ʱ
		u8		Smoke_Tim_max; 		//���̼�ʱmax
	}DATA_Atomizer;
extern DATA_Atomizer		R_DISP_DATA,R_DISP_DATA_Q;
	
//////////////////////////////////////////////
extern	void	Open_Interface(void);
extern	void 	Display_Refresh(void);
extern	void	R_DISP_DATA_Q_DeInit(void);
extern	void	New_DisStatus(void);
extern	void	New_DisStatus_S(void);
extern	void	R_DISP_DATA_Q_DeInit(void);
extern	void	Charging_BAT_windows(void);
	
	
	
//////////////////////////////////
	
extern	void	Display_TCR_adjust(void);
extern	void	Display_Change_LOGO(void);
extern	void	Print_password(u8	*buf,u8	x,u8	B_yingchang);	
		
	//////////////////////////////��Ļ����
extern	void	Key_Screen(void);

extern	u8	B_FullBattClear;				//����������̿�����־  	 	0���ر�		1����
extern	u8	B_Display_STATISTICS;		//��������ʾͳ�����ݱ�־   0���ر�		1����
extern	u8	B_SpeedBrake;						//���̳��ٱ���				  	 	0���ر�		1����

#endif

