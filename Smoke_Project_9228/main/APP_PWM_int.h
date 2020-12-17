#ifndef __APP_PWM_int_H
#define __APP_PWM_int_H
#include "main.h"

/*Êä³öPWMÉèÖÃµ×²ã BEGIN*******/

	#define OUT_En_DCDC_PIN          	LL_GPIO_PIN_10
	#define OUT_En_DCDC_GPIO_PORT     GPIOA
	#define	OUT_En_DCDC_ON()		LL_GPIO_SetOutputPin(OUT_En_DCDC_GPIO_PORT,OUT_En_DCDC_PIN)
	#define	OUT_En_DCDC_OFF()		LL_GPIO_ResetOutputPin(OUT_En_DCDC_GPIO_PORT,OUT_En_DCDC_PIN)



	#define	d_PWM_Boost_Buck_MODE

	/*ÉèÖÃÉýÑ¹PWMÖµ*/
	#define		Set_OUT_BOOST_PWM_Data(a)		TIM1->CCR2 = a
	/*ÉèÖÃ½µÑ¹PWMÖµ*/
	#define		Set_OUT_Buck_PWM_Data(a)		TIM1->CCR1 = a

#ifdef	d_PWM_Boost_Buck_MODE
/////Éý½µÑ¹PWM²ÎÊý
	#define	d_OUT_PWM_Period						100
	#define	d_OUT_PWM_SUM								(d_OUT_PWM_Period*2)
	#define	d_OUT_PWM_max								(d_OUT_PWM_Period+d_OUT_PWM_Period*65/100)
#else
	/////½µÑ¹PWM²ÎÊý
	#define	d_OUT_PWM_Period						200
	#define	d_OUT_PWM_SUM								d_OUT_PWM_Period
	#define	d_OUT_PWM_max								d_OUT_PWM_Period
#endif


extern	s16	R_OUT_PWM_data;				//PWM????¡À¨¨0~150

extern 	void	OUT_PWM_Wdata(s16* data);
extern	void	PWM_ON(void);
extern	void	PWM_OFF(void);

/*Êä³öPWMÉèÖÃµ×²ã END*******/

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*³äµçPWMÉèÖÃµ×²ã BEGIN*******/

	/*ÉèÖÃÉýÑ¹PWMÖµ*/
	#define		Set_BAT_BOOST_PWM_Data(a)		TIM4->CCR1 = a
	/*ÉèÖÃ½µÑ¹PWMÖµ*/
	#define		Set_BAT_Buck_PWM_Data(a)		TIM4->CCR2 = a


	#define	d_BAT_PWM_Period					120
	#define	d_BAT_PWM_SUM							(d_BAT_PWM_Period*2)
	#define	d_BAT_PWM_max							(d_BAT_PWM_Period+d_BAT_PWM_Period*65/100)

	extern 	s16	R_BAT_PWM_data;
	extern 	u8	B_BAT_PWM_EN;

	extern 	void	BAT_PWM_Wdata(s16* data);
	extern 	void	BAT_PWM_EN(u8	B);

/*³äµçPWMÉèÖÃµ×²ã END*******/

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/*±³¹âPWMÉèÖÃµ×²ã BEGIN*******/

	/*ÉèÖÃPWMÖµ*/
	#define		Set_BL_PWM_Data(a)		TIM3->CCR4 = a
	#define		Get_BL_PWM_Data			(TIM3->CCR4)

	#define	d_BL_PWM_min						5
	#define	d_BL_PWM_Period					100+d_BL_PWM_min
	extern 	u16	R_BL_PWM_Data;

	extern 	void	BL_PWM_Wdata(s16 data);
	extern 	void	BL_PWM_OFF(void);
/*±³¹âPWMÉèÖÃµ×²ã END*******/


/*LEDç¯PWM*/
	#define	d_LED_PWM_Period					d_BL_PWM_Period
	#define		Set_LED2_PWM_Data(a)		TIM3->CCR3 = a
	#define		Get_LED2_PWM_Data			(TIM3->CCR3)
	#define		Set_LED1_PWM_Data(a)		TIM10->CCR1 = a
	#define		Get_LED1_PWM_Data			(TIM10->CCR1)

	extern  u16	R_KEY_LED_PWM_Data;
	extern  void	KEY_LED_Wdata(s16 data);
	extern  void	KEY_LED_PWM_OFF(void);

	extern 	u16	R_LOGO_LED_PWM_Data;
	extern  void	LOGO_LED_Wdata(s16 data);
	extern  void	LOGO_LED_PWM_OFF(void);
/*******************************/

/*æŒ¯å­PWM*/
	#define	d_MOTOR_PWM_Period					20
	#define	d_MOTOR_PWM_max							18
	#define	d_MOTOR_PWM_min							9
	#define		Set_MOTOR_PWM_Data(a)		TIM2->CCR3 = a
	#define		Get_MOTOR_PWM_Data			(TIM2->CCR3)
	/*éœ‡åŠ¨é©¬è¾¾PWMè®¾ç½®åº•å±‚ BEGIN*******/
	extern 	u16	R_MOTOR_PWM_Data;
	extern  void	MOTOR_PWM_Wdata(s16 data);
	extern  void	MOTOR_PWM_OFF(void);
/*******************************/
#endif


