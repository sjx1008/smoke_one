#include "main.h"
#include "main_2.h"
#include "usbd_customhid.h"
#include "usb_device.h"
u8 	Send_Buffer[64];		//定义USB发送缓存
u8 	Report_buf[64];
u8	B_Accept_Data_OK=0;



APP_upgrade		R_APP_TypeDef;		//定义烧录程序数据结构
//LOGO_upgrade		R_LOGO_TypeDef;
//INT_60byte	R_INT_60byte;
INT_32bit		R_INT_32bit;
INT_16bit		R_INT_16bit;

//u8	R_return_USB;		//答复上位机信息
u16	USBovertime;		//USB超时

//u8	R_USB_Enable;		//USB使能工作状态

USB_state	R_USB_state;	//USB工作状态


#define USB_Serial_number    		"2016428191300000"

#define USB_Disp_height        	320  	//显示高
#define USB_Disp_width  				240 		//显示宽
#define USB_Disp_mode    				1			//取模方式		0：列行		1：行列
#define USB_Disp_material    		1			//材质			0：OLED		1:TFT
///////////////////////升级程序/////////////////////
/*****************************/
//求数据校验和
u8 checksum_usbdata(u8	*buf)
{
	u8	check=0;
	u8	i;
	u8	longss;
	longss=buf[2]+3;
	for (i=0;i<longss;i++)
	{
		check+=buf[i];
	}
	return check;
}
//求数据校验和
void FLASH_Data_checksum_usbdata(void)
{
	u8	i;
	Send_Buffer[4]=0;
	for (i=0;i<4;i++)
	{
		Send_Buffer[4]+=Report_buf[i];
	}
}
//数据解密
void	decrypt_data(void)
{
	u8	i;
	for(i=3;i<Report_buf[2]+3;i++)
	{
		if(Report_buf[i]!=0x00	&& Report_buf[i]!=0xff && Report_buf[i]!=0xA5 && Report_buf[i]!=0x5A)
			Report_buf[i]=Report_buf[i]^encryption_Key;
	}
}

//接收下载FLASH数据解密
void	FLASH_Data_decrypt_data(void)
{
	u8	i;
	for(i=3;i<63;i++)
	{
		if(Report_buf[i]!=0x00	&& Report_buf[i]!=0xff && Report_buf[i]!=0xA5 && Report_buf[i]!=0x5A)
		{
			Report_buf[i]=Report_buf[i]^encryption_Key;
		}
	}
}

//数据加密
void	encryption_data(void)
{
	u8	i,a;
	a=3;
	if(Send_Buffer[2] > 1)
	{
		for(i=0;i<Send_Buffer[2];i++)
		{
			if(Send_Buffer[a]!=0x00	&& Send_Buffer[a]!=0xff && Send_Buffer[a]!=0xA5 && Send_Buffer[a]!=0x5A)
			{
				Send_Buffer[a]^=encryption_Key;
			}
			a++;
		}
	}
	Send_Buffer[Send_Buffer[2]+3]=checksum_usbdata(Send_Buffer);
}

/***********************************/
//提取第0包信息
void pro_first_program(void)
{
	Send_Buffer[0]=Report_buf[0];
	Send_Buffer[1]=Report_buf[1];
	Send_Buffer[2]=1;
	if(checksum_usbdata(Report_buf)!=Report_buf[Report_buf[2]+3])
	{
		Send_Buffer[3]=RETURN_ERROR;  //
		goto	return_pro_first_program;
	}
	if(Report_buf[2]!=46 && Report_buf[1]!=0x00)
	{
		Send_Buffer[3]=RETURN_ERROR;
		goto	return_pro_first_program;
	}
	R_INT_32bit.chars[3]=Report_buf[7];
	R_INT_32bit.chars[2]=Report_buf[8];
	R_INT_32bit.chars[1]=Report_buf[9];
	R_INT_32bit.chars[0]=Report_buf[10];
	R_APP_TypeDef.Data_ALL_number=R_INT_32bit.ints;
	if(R_APP_TypeDef.Data_ALL_number>APP_DEFAULT_ADD_SIZE || R_APP_TypeDef.Data_ALL_number<0x5000)
	{
		Send_Buffer[3]=RETURN_ERROR;
		goto	return_pro_first_program;
	}
	R_INT_32bit.chars[3]=Report_buf[43];
	R_INT_32bit.chars[2]=Report_buf[44];
	R_INT_32bit.chars[1]=Report_buf[45];
	R_INT_32bit.chars[0]=Report_buf[46];
	if(R_INT_32bit.ints!=APP_DEFAULT_ADD)
	{
		Send_Buffer[3]=RETURN_ERROR;
		goto	return_pro_first_program;
	}
	Send_Buffer[2]=3;
	Send_Buffer[3]=0xAA;
	Send_Buffer[4]=0x5A;
	Send_Buffer[5]=0x01^encryption_Key;	//應該是升級第一包衹需要一個異或A5；
  Send_Buffer[Send_Buffer[2]+3]=checksum_usbdata(Send_Buffer);
	R_USB_state=S_USB_APP;
	USBovertime=4;
	return;
	return_pro_first_program:
	encryption_data();
	Send_Buffer[Send_Buffer[2]+3]=checksum_usbdata(Send_Buffer);
}


void	Copy_information(u8	*Chars,u8	max,u8	start)
{
	u8	i;
	for(i=0;i<max;i++)
	{
		if(*Chars=='\0')
		{
			for(;i<max;i++)
			{
				Send_Buffer[start+i]='?';
				Chars++;
			}
		}
		else
		{
			Send_Buffer[start+i]=*Chars;
			Chars++;
		}
	}
}
void	Copy_information_20(u8	*Chars,u8	max,u8	start)
{
	u8	i;
	for(i=0;i<max;i++)
	{
		if(i == 12)
			start += 32;

		if(*Chars=='\0')
		{
			for(;i<max;i++)
			{
				Send_Buffer[start+i]='?';
				Chars++;
			}
		}
		else
		{
			Send_Buffer[start+i]=*Chars;
			Chars++;
		}
	}
}
/**********************询问电子烟参数******************************************/
void	USB_Query_parameters(void)
{
	u8	i;
	u32 Device_Serial0, Device_Serial1, Device_Serial2;
	Send_Buffer[0]=Report_buf[0];
	Send_Buffer[1]=Report_buf[1];

	R_INT_16bit.chars[0]=Report_buf[1];
	R_INT_16bit.chars[1]=Report_buf[0]&0x0f;
	if(checksum_usbdata(Report_buf)!=Report_buf[Report_buf[2]+3])
	{
		Send_Buffer[2]=1;
		Send_Buffer[3]=RETURN_ERROR;  //
	}
	else if(R_INT_16bit.ints==0x0001)
	{
		B_USB_inquiry=1;
		Send_Buffer[2]=60;
		Copy_information_20((uint8_t*)USB_Product_name,20,3);
		Copy_information((uint8_t*)USB_Software_version,16,15);
		Copy_information((uint8_t*)USB_Hardware_version,16,31);
		Device_Serial0 = *(uint32_t*)UID_BASE;
		Device_Serial1 = *(uint32_t*)(UID_BASE+4);
		Device_Serial2 = *(uint32_t*)(UID_BASE+8);

		Device_Serial0 += Device_Serial2;

		for( i = 0 ; i < 8 ; i++)
		{
			if( ((Device_Serial0 >> 28)) < 0xA )
			{
				Send_Buffer[47+i] = (Device_Serial0 >> 28) + '0';
			}
			else
			{
				Send_Buffer[47+i] = (Device_Serial0 >> 28) + 'A' - 10;
			}

			Device_Serial0 = Device_Serial0 << 4;
		}

		for( i = 0 ; i < 8 ; i++)
		{
			if( ((Device_Serial1 >> 28)) < 0xA )
			{
				Send_Buffer[55+i] = (Device_Serial1 >> 28) + '0';
			}
			else
			{
				Send_Buffer[55+i] = (Device_Serial1 >> 28) + 'A' - 10;
			}

			Device_Serial1 = Device_Serial1 << 4;
		}
	}
	else	if(R_INT_16bit.ints==0x0002)
	{
		Send_Buffer[2]=23;

		Send_Buffer[3]=USB_Disp_height>>8;
		Send_Buffer[4]=USB_Disp_height&0xff;
		Send_Buffer[5]=USB_Disp_width>>8;
		Send_Buffer[6]=USB_Disp_width&0xff;
		Send_Buffer[7]=USB_Disp_mode;
		Send_Buffer[8]=USB_Disp_material;

		Send_Buffer[9]=  0x07;//功能：UI、TCR、曲线
		Send_Buffer[10]= 0x00;//曲线个数高8位
		Send_Buffer[11]= 0x1f;//曲线个数低8位
		Send_Buffer[12]= 0x00;//TCR个数高8位
		Send_Buffer[13]= 0x1F;//TCR个数低8位

		Send_Buffer[14]= 0x00;//UI
		Send_Buffer[15]= 0x00;//UI
		Send_Buffer[16]= 0x00;//UI
		Send_Buffer[17]= 0x00;//UI
		Send_Buffer[18]= 0x00;//UI
		Send_Buffer[19]= 0x00;//UI
		Send_Buffer[20]= 0x00;//UI
		Send_Buffer[21]= 0x00;//UI

		Send_Buffer[22]=d_User_Watt_min/10>>8;
		Send_Buffer[23]=d_User_Watt_min/10&0xff;
		Send_Buffer[24]=d_User_Watt_max/10>>8;
		Send_Buffer[25]=d_User_Watt_max/10&0xff;
	}
	else
	{
		Send_Buffer[2]=1;
		Send_Buffer[3]=RETURN_NONSUPPORT;  //
	}
	encryption_data();
	Send_Buffer[Send_Buffer[2]+3]=checksum_usbdata(Send_Buffer);
}

/*FLASH_Data下载数据结构---------------------*/
	typedef struct
	{
		u32	FrameNumber;			//总帧数
		u32	BytesNumber;			//总Byte数
		u32	Cumulative;				//累加和
		u32	StatisticsCumulative;				//统计累加和
		u32	Current_Frame;		//下一帧
		u32	ReceivedBytes;		//已经接收到的字节数
		u8	Surplus;					//最后一包的字节数
	}USB_FLASH_Data_struct;
USB_FLASH_Data_struct	USB_FLASH_Data;
void	Handle_SEND_LOGO_BEGIN(void)
{
	Send_Buffer[0]=Report_buf[0];
	Send_Buffer[1]=Report_buf[1];
	Send_Buffer[2]=1;
	if(checksum_usbdata(Report_buf)!=Report_buf[Report_buf[2]+3])
	{
		Send_Buffer[3]=RETURN_ERROR;
		return;
	}
	if(Report_buf[2]==0x0e)
	{
		decrypt_data();
		R_INT_32bit.chars[3]=Report_buf[7];R_INT_32bit.chars[2]=Report_buf[8];R_INT_32bit.chars[1]=Report_buf[9];R_INT_32bit.chars[0]=Report_buf[10];
		USB_FLASH_Data.FrameNumber=R_INT_32bit.ints;
		R_INT_32bit.chars[3]=Report_buf[3];R_INT_32bit.chars[2]=Report_buf[4];R_INT_32bit.chars[1]=Report_buf[5];R_INT_32bit.chars[0]=Report_buf[6];
		USB_FLASH_Data.BytesNumber=R_INT_32bit.ints;
		R_INT_32bit.chars[3]=Report_buf[11];R_INT_32bit.chars[2]=Report_buf[12];R_INT_32bit.chars[1]=Report_buf[13];R_INT_32bit.chars[0]=Report_buf[14];
		USB_FLASH_Data.Cumulative=R_INT_32bit.ints;
		USB_FLASH_Data.Surplus=Report_buf[15];
		if(!USB_FLASH_Data.Surplus)USB_FLASH_Data.Surplus=60;
		if(USB_FLASH_Data.BytesNumber>0x00700000 || ((USB_FLASH_Data.FrameNumber-1)*60+USB_FLASH_Data.Surplus)!=USB_FLASH_Data.BytesNumber || USB_FLASH_Data.Surplus>60)
		{
			Send_Buffer[3]=RETURN_ERROR;
			return;
		}
		USB_FLASH_Data.StatisticsCumulative=0;
		USB_FLASH_Data.ReceivedBytes=0;
		USB_FLASH_Data.Current_Frame=1;
		W25QXX_Erase_Sector(FLASH_BackupsData_address);
		R_USB_state=S_USB_LOGO;
		Send_Buffer[3]=RETURN_RIGHT;  //
		USBovertime=500;
	}
	else
		Send_Buffer[3]=RETURN_ERROR;
}
u8	BUFF111111[60];
void	Handle_SEND_LOGO_DATA(void)
{
	u8	writelength,i;
	Send_Buffer[0]=Report_buf[0];
	Send_Buffer[1]=Report_buf[1];
	Send_Buffer[2]=Report_buf[2];
	if(R_USB_state!=S_USB_LOGO)
	{
		Send_Buffer[3]=RETURN_ERROR;
		return;
	}
	R_INT_32bit.chars[3]=0;R_INT_32bit.chars[2]=Report_buf[0]&0x0F;R_INT_32bit.chars[1]=Report_buf[1];R_INT_32bit.chars[0]=Report_buf[2];
	if(R_INT_32bit.ints!=USB_FLASH_Data.Current_Frame || USB_FLASH_Data.Current_Frame>USB_FLASH_Data.FrameNumber)
	{
		Send_Buffer[3]=RETURN_ERROR;
	}
	else
	{
		FLASH_Data_decrypt_data();
		if(USB_FLASH_Data.FrameNumber>USB_FLASH_Data.Current_Frame)
			writelength=60;
		else
			writelength=USB_FLASH_Data.Surplus;
		if(USB_FLASH_Data.ReceivedBytes/FLASH_SectorsSize != (USB_FLASH_Data.ReceivedBytes+writelength)/FLASH_SectorsSize)
			W25QXX_Erase_Sector(USB_FLASH_Data.ReceivedBytes+FLASH_BackupsData_address+writelength);
		SPI_Flash_Write_BuffData8(USB_FLASH_Data.ReceivedBytes+FLASH_BackupsData_address,Report_buf+3,writelength);
		SPI_Flash_Write_BuffData_OK();
		SPI_Flash_Read_BuffData8(USB_FLASH_Data.ReceivedBytes+FLASH_BackupsData_address,BUFF111111,writelength);
		SPI_Flash_Read_BuffData_OK();
		for(i=0;i<writelength;i++)
		{
			if(BUFF111111[i]!=Report_buf[3+i])
			{
				Send_Buffer[3]=RETURN_ERROR;
				return;
			}
		}
//		for(i=0;i<writelength;i++)
//		{
//			USB_FLASH_Data.StatisticsCumulative+=BUFF111111[i];
//		}
		USB_FLASH_Data.ReceivedBytes+=writelength;
		USB_FLASH_Data.Current_Frame++;
		Send_Buffer[3]=RETURN_RIGHT;
		USBovertime=500;
	}
}
void	Handle_SEND_LOGO_END(void)
{
	Send_Buffer[0]=Report_buf[0];
	Send_Buffer[1]=Report_buf[1];
	Send_Buffer[2]=Report_buf[2];
	if(R_USB_state!=S_USB_LOGO)
	{
		Send_Buffer[3]=RETURN_ERROR;
		return;
	}
	R_INT_32bit.chars[3]=0;R_INT_32bit.chars[2]=Report_buf[0]&0x0F;R_INT_32bit.chars[1]=Report_buf[1];R_INT_32bit.chars[0]=Report_buf[2];
	if((R_INT_32bit.ints!=USB_FLASH_Data.FrameNumber+1) || USB_FLASH_Data.ReceivedBytes!=USB_FLASH_Data.BytesNumber/* || USB_FLASH_Data.StatisticsCumulative!=USB_FLASH_Data.Cumulative*/)
		Send_Buffer[3]=RETURN_ERROR;
	else
	{
		Send_Buffer[3]=RETURN_RIGHT;
		R_USB_state=S_USB_LOGOEND;
		USBovertime=500;
	}
}
/*************************************************************/
/**********************设置或查询图片（警告提示）、TCR参数、自定义参数等******************************************/
#define	PACK_HEAD   (Report_buf[0] & 0xf0)       					          /* 包头[the head of the package] */
#define	PACK_NUM    (((uint16_t) (Report_buf[0]&0x0f)<<8) + Report_buf[1])  /* 包数 [the command of the package] */
#define	PACK_CMD  	(Report_buf[3])   										                  /* 包命令 [the command of the package] */
#define	PACK_LEN    (Report_buf[2]+3)       								                /* 包长度 [the length of the package]  */
#define	DATA_LEN    (Report_buf[2])      									                  /* 数据长度 [the length of the data]  */
#define	PACK_CHK    (Report_buf[PACK_LEN])

	vu8	R_Change_LOGO;		//更改第几个LOGO
	vu8	R_Page_LOGO;			//数据帧数计数
	vu16	R_Byte_LOGO_I;	//Byte计数
	vu8	R_Flash_LOGO;			//LOGO所处Flash地方
	vu8	R_Flash_LOGO_Q;			//LOGO所处Flash地方
void	USB_R_W_parameters(void)
{
	u8	i;
	u16	*R,*R1;
	u8	a;
	Send_Buffer[0]=Report_buf[0];
	Send_Buffer[1]=Report_buf[1];
	Send_Buffer[2]=1;
	Send_Buffer[3]=RETURN_ERROR;  //
	decrypt_data();//解密
	switch(PACK_CMD)
	{
		case R_Cmd_CURVE://曲线数组
		{
			Send_Buffer[2] = 28;
			Send_Buffer[4] = R_Cmd_CURVE;
			Send_Buffer[5] = Report_buf[4];//序号
			if(Report_buf[4]==1)
			{
				Send_Buffer[6]=R_Custom_BUFF.Custom_array.CustomCCW_Data[0];
				for(i=0;i<10;i++)
				{
						Send_Buffer[7+i]=R_Custom_BUFF.Custom_array.CustomCCW_Data[i];
				}
				for(i=10;i<20;i++)
				{
						Send_Buffer[7+i]=R_Custom_BUFF.Custom_array.CustomCCW_Data[9];
				}
				Send_Buffer[27]=d_User_Watt_max/10;
				Send_Buffer[28]=d_User_Watt_min/10;
				Send_Buffer[29]=(Send_Buffer[28]+Send_Buffer[27])/2;
				Send_Buffer[30]=0;
				Send_Buffer[3]=RETURN_RIGHT;  //
			}
			else if(Report_buf[4]>1 && Report_buf[4]<5)
			{
				if(R_Temp_metric==C_metric)
				{
					switch(Report_buf[4])
					{
						case 2:
							R=R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data;break;
						case 3:
							R=R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data;break;
						case 4:
							R=R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data;break;
					}
					a=5;
					Send_Buffer[27]=d_User_TempC_max/a;
					Send_Buffer[28]=d_User_TempC_min/a;
					Send_Buffer[30]=1;
				}
				else
				{
					switch(Report_buf[4])
					{
						case 2:
							R=R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data;break;
						case 3:
							R=R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data;break;
						case 4:
							R=R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data;break;
					}
					a=10;
					Send_Buffer[27]=d_User_TempF_max/a;
					Send_Buffer[28]=d_User_TempF_min/a;
					Send_Buffer[30]=2;
				}
				Send_Buffer[29]=(Send_Buffer[28]+Send_Buffer[27])/2;
				Send_Buffer[6]=R[0]/a;
				for(i=0;i<10;i++)
				{
						Send_Buffer[7+i]=R[i]/a;
				}
				for(i=10;i<20;i++)
				{
						Send_Buffer[7+i]=R[9]/a;
				}
				Send_Buffer[3]=RETURN_RIGHT;  //
			}
			else if(Report_buf[4]==5)
			{
				Send_Buffer[6]=R_Custom_BUFF.Custom_array.CustomCCV_Data[0]/5;
				for(i=0;i<10;i++)
				{
						Send_Buffer[7+i]=R_Custom_BUFF.Custom_array.CustomCCV_Data[i]/5;
				}
				for(i=10;i<20;i++)
				{
						Send_Buffer[7+i]=R_Custom_BUFF.Custom_array.CustomCCV_Data[9];
				}
				Send_Buffer[27]=d_User_Vout_max/5;
				Send_Buffer[28]=d_User_Vout_min/5;
				Send_Buffer[29]=(Send_Buffer[28]+Send_Buffer[27])/2;
				Send_Buffer[30]=3;
				Send_Buffer[3]=RETURN_RIGHT;  //
			}
			else
			{
				Send_Buffer[3]=RETURN_NONSUPPORT;  //
			}
		}break;

		case W_Cmd_CURVE:
		{
			Send_Buffer[2]=3;
			Send_Buffer[4] = W_Cmd_CURVE;//
			Send_Buffer[5] = Report_buf[4];//
			if(Report_buf[4]==1 && Report_buf[29]==0)
			{
				for(i=0;i<10;i++)
				{
					R_Custom_BUFF.Custom_array.CustomCCW_Data[i]=Report_buf[6+i];
					if(R_Custom_BUFF.Custom_array.CustomCCW_Data[i]<d_User_Watt_min/10)
						R_Custom_BUFF.Custom_array.CustomCCW_Data[i]=d_User_Watt_min/10;
					else if(R_Custom_BUFF.Custom_array.CustomCCW_Data[i]>d_User_Watt_max/10)
						R_Custom_BUFF.Custom_array.CustomCCW_Data[i]=d_User_Watt_max/10;
				}
				Send_Buffer[3] = RETURN_RIGHT;//
				B_Display_refresh=1;
				B_Custom_Hold=1;
			}
			else if(Report_buf[4]>1 && Report_buf[4]<5)
			{
				if(Report_buf[29]==1)
				{
					switch(Report_buf[4])
					{
						case 2:
							R=R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data;
							R1=R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data;
						break;
						case 3:
							R=R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data;
							R1=R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data;
						break;
						case 4:
							R=R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data;
							R1=R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data;
						break;
					}
					for(i=0;i<10;i++)
					{
						R[i]=Report_buf[6+i]*5;
						if(R[i]<d_User_TempC_min)
							R[i]=d_User_TempC_min;
						else if(R[i]>d_User_TempC_max)
							R[i]=d_User_TempC_max;
						R1[i]=(R[i]*9/5+32)/10*10;
						if(R1[i]<d_User_TempF_min)
							R1[i]=d_User_TempF_min;
						else	if(R1[i]>d_User_TempF_max)
							R1[i]=d_User_TempF_max;
					}
					B_Display_refresh=1;
					B_Custom_Hold=1;
					Send_Buffer[3] = RETURN_RIGHT;//
				}
				else if(Report_buf[29]==2)
				{
					switch(Report_buf[4])
					{
						case 2:
							R1=R_Custom_BUFF.Custom_array.CustomCCTSS_C_Data;
							R=R_Custom_BUFF.Custom_array.CustomCCTSS_F_Data;
						break;
						case 3:
							R1=R_Custom_BUFF.Custom_array.CustomCCTNI_C_Data;
							R=R_Custom_BUFF.Custom_array.CustomCCTNI_F_Data;
						break;
						case 4:
							R1=R_Custom_BUFF.Custom_array.CustomCCTTI_C_Data;
							R=R_Custom_BUFF.Custom_array.CustomCCTTI_F_Data;
						break;
					}
					for(i=0;i<10;i++)
					{
						R[i]=Report_buf[6+i]*10;
						if(R[i]<d_User_TempF_min)
							R[i]=d_User_TempF_min;
						else if(R[i]>d_User_TempF_max)
							R[i]=d_User_TempF_max;
						R1[i]=(R[i]-32)*5/9/5*5;
						if(R1[i]<d_User_TempC_min)
							R1[i]=d_User_TempC_min;
						else	if(R1[i]>d_User_TempC_max)
							R1[i]=d_User_TempC_max;
					}
					B_Display_refresh=1;
					B_Custom_Hold=1;
					Send_Buffer[3] = RETURN_RIGHT;//
				}
				else
				{
					Send_Buffer[3]=RETURN_ERROR;  //
				}
			}
			else if(Report_buf[4]==5 && Report_buf[29]==3)
			{
				for(i=0;i<10;i++)
				{
					R_Custom_BUFF.Custom_array.CustomCCV_Data[i]=Report_buf[6+i]*5;
					if(R_Custom_BUFF.Custom_array.CustomCCV_Data[i]<d_User_Vout_min)
						R_Custom_BUFF.Custom_array.CustomCCV_Data[i]=d_User_Vout_min;
					else if(R_Custom_BUFF.Custom_array.CustomCCV_Data[i]>d_User_Vout_max)
						R_Custom_BUFF.Custom_array.CustomCCV_Data[i]=d_User_Vout_max;
				}
				Send_Buffer[3] = RETURN_RIGHT;//
				B_Display_refresh=1;
				B_Custom_Hold=1;
			}
			else
			{
				Send_Buffer[3]=RETURN_NONSUPPORT;  //
			}
		}break;

		case R_Cmd_TCR://TCR参数
		{
			Send_Buffer[2]=21;
			Send_Buffer[3] = RETURN_RIGHT;//
			Send_Buffer[4] = R_Cmd_TCR;//
			Send_Buffer[5]	=	Report_buf[4];
			Send_Buffer[11]	= d_User_Watt_min>>8;
			Send_Buffer[12]	= d_User_Watt_min&0xFF;
			Send_Buffer[13]	= d_User_Watt_max>>8;
			Send_Buffer[14]	= d_User_Watt_max&0xFF;
			Send_Buffer[15]	= 0;
			Send_Buffer[16]	= 0;
			Send_Buffer[17]	= 0;
			Send_Buffer[18]	= 0;
			Send_Buffer[19]	= 0;
			if(Report_buf[4]==1)
			{
				Send_Buffer[6]	= 1;
				Send_Buffer[7]=Load_Ni200.Gradient>>8;
				Send_Buffer[8]=Load_Ni200.Gradient&0xFF;
				Send_Buffer[9]	= (Load_Ni200.WattsMAX*10)>>8;
				Send_Buffer[10]	= (Load_Ni200.WattsMAX*10)&0xFF;
				Send_Buffer[20]	= 400>>8;
				Send_Buffer[21]	= 400&0xFF;
				Send_Buffer[22]	= 800>>8;
				Send_Buffer[23]	= 800&0xFF;
			}
			else if(Report_buf[4]==2)
			{
				Send_Buffer[6]	= 2;
				Send_Buffer[7]=Load_Ti.Gradient>>8;
				Send_Buffer[8]=Load_Ti.Gradient&0xFF;
				Send_Buffer[9]	= (Load_Ti.WattsMAX*10)>>8;
				Send_Buffer[10]	= (Load_Ti.WattsMAX*10)&0xFF;
				Send_Buffer[20]	= 150>>8;
				Send_Buffer[21]	= 150&0xFF;
				Send_Buffer[22]	= 550>>8;
				Send_Buffer[23]	= 550&0xFF;
			}
			else if(Report_buf[4]==3)
			{
				Send_Buffer[6]	= 4;
				Send_Buffer[7]=Load_Ss316.Gradient>>8;
				Send_Buffer[8]=Load_Ss316.Gradient&0xFF;
				Send_Buffer[9]	= (Load_Ss316.WattsMAX*10)>>8;
				Send_Buffer[10]	= (Load_Ss316.WattsMAX*10)&0xFF;
				Send_Buffer[20]	= 50>>8;
				Send_Buffer[21]	= 50&0xFF;
				Send_Buffer[22]	= 250>>8;
				Send_Buffer[23]	= 250&0xFF;
			}
			else if(Report_buf[4]==4)
			{
				Send_Buffer[6]	= 0x81;
				Send_Buffer[7]=Load_M1.Gradient>>8;
				Send_Buffer[8]=Load_M1.Gradient&0xFF;
				Send_Buffer[9]	= (Load_M1.WattsMAX*10)>>8;
				Send_Buffer[10]	= (Load_M1.WattsMAX*10)&0xFF;
				Send_Buffer[20]	= 0;
				Send_Buffer[21]	= 1;
				Send_Buffer[22]	= 1000>>8;
				Send_Buffer[23]	= 1000&0xFF;
			}
			else if(Report_buf[4]==5)
			{
				Send_Buffer[6]	= 0x82;
				Send_Buffer[7]=Load_M2.Gradient>>8;
				Send_Buffer[8]=Load_M2.Gradient&0xFF;
				Send_Buffer[9]	= (Load_M2.WattsMAX*10)>>8;
				Send_Buffer[10]	= (Load_M2.WattsMAX*10)&0xFF;
				Send_Buffer[20]	= 0>>8;
				Send_Buffer[21]	= 1&0xFF;
				Send_Buffer[22]	= 1000>>8;
				Send_Buffer[23]	= 1000&0xFF;
			}
			else
			{
				Send_Buffer[2]=1;
				Send_Buffer[3]=RETURN_NONSUPPORT;  //
			}
		}break;
		case W_Cmd_TCR:
		{
			Send_Buffer[2]=3;
			Send_Buffer[3] = RETURN_RIGHT;//
			Send_Buffer[4] = W_Cmd_TCR;//
			Send_Buffer[5] = Report_buf[4];//
			if(Report_buf[5]==1)
			{
				Load_Ni200.Gradient=(Report_buf[6]<<8)|Report_buf[7];
				if(Load_Ni200.Gradient<400)
					Load_Ni200.Gradient=400;
				else if(Load_Ni200.Gradient>800)
					Load_Ni200.Gradient=800;
				Load_Ni200.WattsMAX=(((Report_buf[8]<<8)|Report_buf[9])+5)/10;
				if(Load_Ni200.WattsMAX<d_User_Watt_min/10)
					Load_Ni200.WattsMAX=d_User_Watt_min/10;
				else if(Load_Ni200.WattsMAX>d_User_Watt_max/10)
					Load_Ni200.WattsMAX=d_User_Watt_max/10;
				B_Display_refresh=1;
			}
			else if(Report_buf[5]==2)
			{
				Load_Ti.Gradient=(Report_buf[6]<<8)|Report_buf[7];
				if(Load_Ti.Gradient<150)
					Load_Ti.Gradient=150;
				else if(Load_Ti.Gradient>550)
					Load_Ti.Gradient=550;
				Load_Ti.WattsMAX=(((Report_buf[8]<<8)|Report_buf[9])+5)/10;
				if(Load_Ti.WattsMAX<d_User_Watt_min/10)
					Load_Ti.WattsMAX=d_User_Watt_min/10;
				else if(Load_Ti.WattsMAX>d_User_Watt_max/10)
					Load_Ti.WattsMAX=d_User_Watt_max/10;
				B_Display_refresh=1;
			}
			else if(Report_buf[5]==4)
			{
				Load_Ss316.Gradient=(Report_buf[6]<<8)|Report_buf[7];
				if(Load_Ss316.Gradient<50)
					Load_Ss316.Gradient=50;
				else if(Load_Ss316.Gradient>250)
					Load_Ss316.Gradient=250;
				Load_Ss316.WattsMAX=(((Report_buf[8]<<8)|Report_buf[9])+5)/10;
				if(Load_Ss316.WattsMAX<d_User_Watt_min/10)
					Load_Ss316.WattsMAX=d_User_Watt_min/10;
				else if(Load_Ss316.WattsMAX>d_User_Watt_max/10)
					Load_Ss316.WattsMAX=d_User_Watt_max/10;
				B_Display_refresh=1;
			}
			else if(Report_buf[5]==0x81)
			{
				Load_M1.Gradient=(Report_buf[6]<<8)|Report_buf[7];
				if(Load_M1.Gradient<1)
					Load_M1.Gradient=1;
				else if(Load_M1.Gradient>1000)
					Load_M1.Gradient=1000;
				Load_M1.WattsMAX=(((Report_buf[8]<<8)|Report_buf[9])+5)/10;
				if(Load_M1.WattsMAX<d_User_Watt_min/10)
					Load_M1.WattsMAX=d_User_Watt_min/10;
				else if(Load_M1.WattsMAX>d_User_Watt_max/10)
					Load_M1.WattsMAX=d_User_Watt_max/10;
				B_Display_refresh=1;
			}
			else if(Report_buf[5]==0x82)
			{
				Load_M2.Gradient=(Report_buf[6]<<8)|Report_buf[7];
				if(Load_M2.Gradient<1)
					Load_M2.Gradient=1;
				else if(Load_M2.Gradient>1000)
					Load_M2.Gradient=1000;
				Load_M2.WattsMAX=(((Report_buf[8]<<8)|Report_buf[9])+5)/10;
				if(Load_M2.WattsMAX<d_User_Watt_min/10)
					Load_M2.WattsMAX=d_User_Watt_min/10;
				else if(Load_M2.WattsMAX>d_User_Watt_max/10)
					Load_M2.WattsMAX=d_User_Watt_max/10;

				B_Display_refresh=1;
			}
			else
			{
				Send_Buffer[3]=RETURN_NONSUPPORT;  //
			}
		}break;

		case R_Cmd_UI://警告界面
		{
			Send_Buffer[2]=3;
			Send_Buffer[3] = RETURN_NONSUPPORT;//
		}break;

		case W_Cmd_UI:
		{
			Send_Buffer[2]=3;
			Send_Buffer[3] = RETURN_NONSUPPORT;//
		}break;
	}
	encryption_data();
}
/*************************************************************/
/*************************************************************/
/*************************************************************/
void	USB_state_program(void)
{
	u8	Cmd;
	if(B_Accept_Data_OK)
	{
		Cmd=Report_buf[0]&0xf0;
		switch(Cmd)
		{
			case	Query_parameters:			USB_Query_parameters();break;
			case	SEND_PRO_BEGIN:				pro_first_program();break;
			case	DATA_ICT:							USB_R_W_parameters();break;

//			case	SEND_LOGO_BEGIN:		{
//				Handle_SEND_LOGO_BEGIN();
//				encryption_data();
//			}break;
//			case	SEND_LOGO_DATA:	{
//				Handle_SEND_LOGO_DATA();
//				FLASH_Data_checksum_usbdata();
//			}break;
//			case	SEND_LOGO_END:	{
//				Handle_SEND_LOGO_END();
//				FLASH_Data_checksum_usbdata();
//			}break;
			default:
			{
				Send_Buffer[0]=Report_buf[0];
				Send_Buffer[1]=Report_buf[1];
				Send_Buffer[2]=1;
				Send_Buffer[3]=0x5F;
				encryption_data();
			}
		}
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,Send_Buffer,USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
		B_Accept_Data_OK=0;
	}

	if(!USBovertime && R_USB_state==S_USB_APP)
	{
		R_USB_state=S_USB_NOP;
		W25QXX_Erase_Sector(d_IAP_Data_Address);
		USB_DISABLE_transmission();
		NVIC_SystemReset();
	}
}


static	u8	B_USB_EN=0;
void	USB_ENABLE_transmission(void)
{
	if(!B_USB_EN)
	{
		B_USB_EN=1;

		LL_GPIO_InitTypeDef   GPIO_InitStructure;
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
		GPIO_InitStructure.Pin = LL_GPIO_PIN_11 | LL_GPIO_PIN_12;
		GPIO_InitStructure.Mode = LL_GPIO_MODE_ANALOG;
		GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
		GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		GPIO_InitStructure.Pull = LL_GPIO_PULL_NO;
		LL_GPIO_Init(GPIOA, &GPIO_InitStructure);

		MX_USB_DEVICE_Init();
	}
}

void	USB_DISABLE_transmission(void)
{
	if(B_USB_EN)
	{
		B_USB_EN=0;

		LL_GPIO_InitTypeDef   GPIO_InitStructure;
		USBD_DeInit(&hUsbDeviceFS);
		__HAL_RCC_USB_OTG_FS_FORCE_RESET();
		__HAL_RCC_USB_OTG_FS_RELEASE_RESET();
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
		GPIO_InitStructure.Pin = LL_GPIO_PIN_11 | LL_GPIO_PIN_12;
		GPIO_InitStructure.Mode = LL_GPIO_MODE_INPUT;
		GPIO_InitStructure.Speed = LL_GPIO_SPEED_FREQ_LOW;
		GPIO_InitStructure.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
		GPIO_InitStructure.Pull = LL_GPIO_PULL_NO;
		LL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
}


