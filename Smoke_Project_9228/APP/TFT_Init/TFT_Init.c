#include	"TFT_Init.h"
#include	"TFT_Init.h"
#include "TFT_Drive.h"
#include "APP_KEY.h"
#include	"APP_Delay.h"
#include	"gpio.h"
#include "APP_PWM_int.h"
#include "Flahs_Driver.h"
#include "WM_Disp.h"

////全局变量申明
u8	R_Screen_brightness=100;	//设定屏幕亮度
u8	R_Screen_brightness_NOW;			//当前屏幕亮度
u8	R_Screen_brightness_i;			//背光亮度慢慢亮起
u8	B_OLED_BL=0;


#ifdef	d_TFT_MODE_SPI3Line
////发送8位命令
void	LCD_WriteComm(u8 dat)
{
	((*(vu32*)0x40020418)=0xB0000000);
	TFT_SCLK_H();

	if(dat&0x80)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x40)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x20)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x10)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x08)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x04)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x02)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x01)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	TFT_NSS_H();
}
///
////发送8位数据
void	LCD_WriteData_8bit(u8 dat)
{
	((*(vu32*)0x40020418)=0x30008000);
	TFT_SCLK_H();

	if(dat&0x80)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x40)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x20)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x10)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x08)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x04)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x02)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x01)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();

	TFT_NSS_H();
}
////
////发送16位数据
void	LCD_WriteData_16bit(u16 dat)
{
	((*(vu32*)0x40020418)=0x30008000);
	TFT_SCLK_H();

	if(dat&0x8000)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x4000)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x2000)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x1000)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x0800)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x0400)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x0200)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x0100)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();

	((*(vu32*)0x40020418)=0x30008000);
	TFT_SCLK_H();

	if(dat&0x80)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x40)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x20)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x10)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x08)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x04)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x02)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	if(dat&0x01)
		((*(vu32*)0x40020418)=0x20008000);
	else
		((*(vu32*)0x40020418)=0xA0000000);
	TFT_SCLK_H();
	TFT_NSS_H();
	((*(vu32*)0x40020400)|=0x40000000);
}
//////
////接收16位颜色数据
u16	LCD_ReadColor_16bit(void)
{
	u16	R=0;
	((*(vu32*)0x40020404)&=0x00007FFF);
	((*(vu32*)0x40020400)&=0x3FFFFFFF);
	((*(vu32*)0x40020418)=0x30008000);
	TFT_SCLK_H();

	TFT_SCLK_L();
	TFT_SCLK_H();
	TFT_SCLK_L();
	TFT_SCLK_H();
	TFT_SCLK_L();
	TFT_SCLK_H();
	TFT_SCLK_L();
	TFT_SCLK_H();
	TFT_SCLK_L();
	TFT_SCLK_H();
	TFT_SCLK_L();
	TFT_SCLK_H();
	TFT_SCLK_L();
	TFT_SCLK_H();


	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x8000;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x4000;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x2000;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x1000;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0800;
	TFT_SCLK_L();
	TFT_SCLK_H();

	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0400;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0200;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0100;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0080;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0040;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0020;

	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0010;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0008;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0004;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0002;
	TFT_SCLK_L();
	TFT_SCLK_H();
	if((*(vu32*)0x40020410)&TFT_SDA_PIN)
		R|=0x0001;
	TFT_SCLK_L();
	TFT_SCLK_H();

	TFT_NSS_H();
	((*(vu32*)0x40020400)|=0x40000000);
	((*(vu32*)0x40020404)|=0x00008000);
	return	R;
}
#endif
///////

#ifdef	d_TFT_MODE_MCU8
////发送8位命令
void	LCD_WriteComm(u8 dat)
{
	(*(vu32*)0x40020418)=0x70008000;
	SET_TFT_DATA_GPIO=dat;
	TFT_WR_H();
	TFT_NSS_H();
}
///
////发送8位数据
void	LCD_WriteData_8bit(u8 dat)
{
	(*(vu32*)0x40020418)=0x60009000;
	SET_TFT_DATA_GPIO=dat;
	TFT_WR_H();
	TFT_NSS_H();
}
////
////发送16位数据
void	LCD_WriteData_16bit(u16 dat)
{
	(*(vu32*)0x40020418)=0x60009000;
	SET_TFT_DATA_GPIO=*((u8*)&dat+1);
	TFT_WR_H();
	__nop();
	TFT_WR_L();
	SET_TFT_DATA_GPIO=dat;
	TFT_WR_H();
	TFT_NSS_H();
}
//////
////接收16位颜色数据
void Delay_Nns(u32	t)
{
	while(t--);
}

u16	LCD_ReadColor_16bit(void)
{
	u16	R=0;
	(*(vu32*)0x40020418)=0xC0003000;
	SET_TFT_DATA_GPIO_IN();
	SET_TFT_DATA_GPIO=0xff;
	Delay_Nns(6);
	TFT_RD_H();
	Delay_Nns(4);
	TFT_RD_L();
	Delay_Nns(10);
	R |= (GET_TFT_DATA_GPIO & 0xf8) << 8 ;
	TFT_RD_H();
	Delay_Nns(3);
	TFT_RD_L();
	Delay_Nns(10);
	R |=(GET_TFT_DATA_GPIO>>2)<<5;
	TFT_RD_H();
	Delay_Nns(3);
	TFT_RD_L();
	Delay_Nns(10);
	R |=GET_TFT_DATA_GPIO>>3;
	TFT_RD_H();
	TFT_NSS_H();
	SET_TFT_DATA_GPIO_OUT();
	return	R;
}
#endif
u8	B_PanelTurnOnDisplay;
///////

void	TFT_REset_program(void)
{
	u8	a;
	a=B_InterfaceGOTO;
	while(R_LCDRESET_Tim)
	{
		KEY_TFT_RESET();
	}
	B_InterfaceGOTO=a;
}
	//屏幕初始化
void	TFT_ST7789S_Init(void)
{
	TFT_REset_program();
	//************* Start Initial Sequence **********//
	LCD_WriteComm(0x11);
	R_LCDRESET_Tim=120;
	TFT_REset_program();
  LCD_WriteComm(0x36);
  LCD_WriteData_8bit(0xC0);
  LCD_WriteComm(0x3a);
  LCD_WriteData_8bit(0x55);


  LCD_WriteComm(0xb2);
  LCD_WriteData_8bit(0x05);
  LCD_WriteData_8bit(0x05);
  LCD_WriteData_8bit(0x00);
  LCD_WriteData_8bit(0x33);
  LCD_WriteData_8bit(0x33);

  LCD_WriteComm(0xb7);
  LCD_WriteData_8bit(0x75); //VGH=13V, VGL=-10.4V
//----------------------------------------------------------------------------------------------------//
  LCD_WriteComm(0xbb);			//VCOM电压设置
  LCD_WriteData_8bit(0x22);


  LCD_WriteComm(0xc0);
  LCD_WriteData_8bit(0x2c);

  LCD_WriteComm(0xc2);
  LCD_WriteData_8bit(0x01);

  LCD_WriteComm(0xc3);
  LCD_WriteData_8bit(0x13);

  LCD_WriteComm(0xc4);
  LCD_WriteData_8bit(0x20);

//	LCD_WriteComm(0xc5);
//  LCD_WriteData_8bit(0x30);

  LCD_WriteComm(0xc6);
  LCD_WriteData_8bit(0x12);

  LCD_WriteComm(0xd0);
  LCD_WriteData_8bit(0xa4);
  LCD_WriteData_8bit(0xa1);

	LCD_WriteComm(0xd6);
  LCD_WriteData_8bit(0xa1);

//----------------------------------------------------------------------------------------------------//
  LCD_WriteComm(0xe0); //gamma setting
  LCD_WriteData_8bit(0xd0);
  LCD_WriteData_8bit(0x05);
  LCD_WriteData_8bit(0x0a);
  LCD_WriteData_8bit(0x09);
  LCD_WriteData_8bit(0x08);
  LCD_WriteData_8bit(0x05);
  LCD_WriteData_8bit(0x2e);
  LCD_WriteData_8bit(0x44);
  LCD_WriteData_8bit(0x45);
  LCD_WriteData_8bit(0x0f);
  LCD_WriteData_8bit(0x17);
  LCD_WriteData_8bit(0x16);
  LCD_WriteData_8bit(0x2b);
  LCD_WriteData_8bit(0x33);


  LCD_WriteComm(0xe1);
  LCD_WriteData_8bit(0xd0);
  LCD_WriteData_8bit(0x05);
  LCD_WriteData_8bit(0x0a);
  LCD_WriteData_8bit(0x09);
  LCD_WriteData_8bit(0x08);
  LCD_WriteData_8bit(0x05);
  LCD_WriteData_8bit(0x2e);
  LCD_WriteData_8bit(0x43);
  LCD_WriteData_8bit(0x45);
  LCD_WriteData_8bit(0x0f);
  LCD_WriteData_8bit(0x16);
  LCD_WriteData_8bit(0x16);
  LCD_WriteData_8bit(0x2b);
  LCD_WriteData_8bit(0x33);

	LCD_WriteComm(0x21);//Display On
//	LCD_WriteComm(0x12);//Display On

	LCD_WriteComm(0x2A);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0xEF);

	LCD_WriteComm(0x2B);
	LCD_WriteData_8bit(0);
	LCD_WriteData_8bit(0);//24
	LCD_WriteData_8bit((d_TFT_Y_Max+TFT_Y_panyi-1)>>8);
	LCD_WriteData_8bit((d_TFT_Y_Max+TFT_Y_panyi-1)&0xFF);
	B_PanelTurnOnDisplay=0;
	LCD_WriteComm(0x28);
}

/////


////复位IC
u16	R_LCDRESET_Tim;		//复位高电平保持时间，在定时器里面递减，为0时才能开始写初始化
void	TFT_LCD_RESET(void)
{

	TFT_RESET_H();
	Delay_Nms(2);
	TFT_RESET_L();
	Delay_Nms(10);
	TFT_RESET_H();
	R_LCDRESET_Tim=120;
}

//调节背光亮度
void	TFT_BL_Brightness(u8	PWM)
{
	R_Screen_brightness_NOW=PWM;
	BL_PWM_Wdata(PWM*100/d_Screen_brightness_MAX);
}
//设置屏幕亮度
void	TFT_SET_BL_Brightness(u8	R)
{
	R_Screen_brightness=R;
	Set_Ret_Bring_VIP();
	TFT_BL_Brightness(R_Screen_brightness);
}

//面板打开显示
void PanelTurnOnDisplay (void)
{
	if(B_PanelTurnOnDisplay)
		return;
	LCD_WriteComm(0x29);//Display On
	B_PanelTurnOnDisplay=1;
}
//面板关闭显示
void PanelTurnOffDisplay (void)
{
	if(!B_PanelTurnOnDisplay)
		return;
	LCD_WriteComm(0x28);//Display Off
	B_PanelTurnOnDisplay=0;
}

//面板打开背光
void BL_PanelTurnOnDisplay (void)
{
	B_OLED_BL=1;
	TFT_BL_Brightness(R_Screen_brightness);
	if(B_PanelTurnOnDisplay)
		return;
	LCD_WriteComm(0x29);//Display On
	B_PanelTurnOnDisplay=1;
}
//面板关闭背光
void BL_PanelTurnOffDisplay (void)
{
	BL_PWM_OFF();
	B_OLED_BL=0;
}
//屏幕关闭过度，等背光全部关闭了才关显示
void	BL_OffDisplay_excessive(void)
{
	if(!B_PanelTurnOnDisplay)
		return;
	if(!B_OLED_BL && Get_BL_PWM_Data==0)
	{
		B_PanelTurnOnDisplay=0;
		LCD_WriteComm(0x28);//Display Off
	}
}

