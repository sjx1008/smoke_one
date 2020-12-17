#ifndef		_APP_ChargingBAT_
#define		_APP_ChargingBAT_
#include "main.h"

	#define OUT_GNDE0_PIN             LL_GPIO_PIN_2
	#define OUT_GNDE0_GPIO_PORT       GPIOB
		#define	GNDE0_ON()			LL_GPIO_SetOutputPin(OUT_GNDE0_GPIO_PORT,OUT_GNDE0_PIN)
		#define	GNDE0_OFF()			LL_GPIO_ResetOutputPin(OUT_GNDE0_GPIO_PORT,OUT_GNDE0_PIN)

	#define BAT_BH1_PIN             	LL_GPIO_PIN_1
	#define BAT_BH1_GPIO_PORT        	GPIOH

	#define BAT_BH2_PIN			          LL_GPIO_PIN_13
	#define BAT_BH2_GPIO_PORT     		GPIOC

	#define	BAT_BH1_ON()		{LL_GPIO_ResetOutputPin(BAT_BH2_GPIO_PORT,BAT_BH2_PIN);LL_GPIO_SetOutputPin(BAT_BH1_GPIO_PORT,BAT_BH1_PIN);}
	#define	BAT_BH2_ON()		{LL_GPIO_ResetOutputPin(BAT_BH1_GPIO_PORT,BAT_BH1_PIN);LL_GPIO_SetOutputPin(BAT_BH2_GPIO_PORT,BAT_BH2_PIN);}
	#define	BAT_BH1_OFF()		{LL_GPIO_ResetOutputPin(BAT_BH1_GPIO_PORT,BAT_BH1_PIN);}
	#define	BAT_BH2_OFF()		{LL_GPIO_ResetOutputPin(BAT_BH2_GPIO_PORT,BAT_BH2_PIN);}
	#define	BAT_BH_OFF()		{LL_GPIO_ResetOutputPin(BAT_BH1_GPIO_PORT,BAT_BH1_PIN);LL_GPIO_ResetOutputPin(BAT_BH2_GPIO_PORT,BAT_BH2_PIN);}


	#define Charge_EN_PIN             LL_GPIO_PIN_0
	#define Charge_EN_GPIO_PORT       GPIOA
		#define Charge_EN_RinBit				LL_GPIO_IsInputPinSet(Charge_EN_GPIO_PORT, Charge_EN_PIN)

	#define Reverse_MOS_PIN          	//LL_GPIO_PIN_8
	#define Reverse_MOS_GPIO_PORT     //GPIOB                       /*  */
		#define	Reverse_MOS_ON()		//LL_GPIO_SetOutputPin(Reverse_MOS_GPIO_PORT,Reverse_MOS_PIN)
		#define	Reverse_MOS_OFF()		//LL_GPIO_ResetOutputPin(Reverse_MOS_GPIO_PORT,Reverse_MOS_PIN)

	#define	d_Charging_Tim_Max	64800

	extern	u8	B_Proportion_Init;
	extern	u8	B_Fast_Charg;
	extern	u8 	B_BAT_Jianche;
	extern	u8 	B_Charg_Jianche;
	extern	u8 	B_BAT_error;						//µç³ØÒì³£±êÖ¾
	extern	u8	R_USB_error_i;
	extern	u8	R_USB_error_Tim;
//	extern	u16	R_last30M;
	extern	u16	R_last5M[2];
	extern	u8	B_BAT_Congman;					///µÚÒ»½Ú³äµç³äÂú±êÖ¾
	extern	u8	B_BAT_Congman2;					///µÚ¶þ½Ú³äµç³äÂú±êÖ¾
	extern	u8	B_BAT_Charge;							///³äµç±êÖ¾
	extern	u16	R_BATT_Actual;							//×Üµç³ØµçÑ¹
	extern	u16		R_BATT_L_Actual;						//µÍ¶Ëµç³ØµçÑ¹
	extern	u16		R_BATT_H_Actual;						//¸ß¶Ëµç³ØµçÑ¹
	extern	u16		R_Charging_current_average;		//Æ½¾ù³äµçµçÁ÷
	extern	u16		R_USB_Charging_current_average;

	extern	u8		B_Get_Charg_BH;				//充电平衡状态标识 0：未开启 1：开启
	extern	u16		R_BAT_L_Real;		//实时值
	extern	u16		R_BAT_H_Real;		//实时值
	extern	u16		R_BATZ_Real;		//实时值
	extern	u16		R_BAT_MAX_Real;			//实时值
	extern	u16		R_Charg_I_Set;	//设置充电电流
	extern	u16		R_Charging_Tim;		//充电计时
	extern	u16		R_Batter_Interface_Tim;		//屏幕充电计时
	extern	uc16	R_BAT_VIP[];

	extern void ChargingBATGPIO_int(void);
	extern void BAT_Balance(void);
	extern void	BAT_Management_Charge(void);
	extern void BAT_Management(void);

	////////////////////////////Í³¼Æµç³ØµçÁ¿°Ù·Ö±È
	extern u8	R_BattL_Proportion;		//µÍ½Úµç³Ø°Ù·Ö±È
	extern u8	R_BattH_Proportion;		//¸ß½Úµç³Ø°Ù·Ö±È

	extern u16	Charging_Over_Time[2];
	extern void	BATT_Charging_Count_down_Init(void);

	typedef enum
	{
		USB_IN=0,	//Êý×Ö¿Ú
		USB_AIN,	//Ä£Äâ¿Ú
	}USB_GPIO_term;
	extern USB_GPIO_term		R_USB_GPIO;
	extern void	USB_GPIO_Set(USB_GPIO_term	R);
	extern void	F_BAT_Actual_Inti(void);

	extern	u8	BatterGrade;
	extern	u8	BatterGrade2;

#endif


