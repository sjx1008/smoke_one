#include "main.h"


u8	R_Screen_FLIP=1;
#ifdef	Gyroscope_ENABLE
u8	B_G3D_JC;
u8	XYZ_data_out[3];

void	Gyroscope_IIC_GPIO_int(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

  RCC_AHBPeriphClockCmd(G3D_SCK_GPIO_CLK | G3D_SDA_GPIO_CLK | G3D_END_GPIO_CLK , ENABLE);

  GPIO_InitStructure.GPIO_Pin = G3D_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(G3D_SCK_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin =G3D_SDA_PIN;
	GPIO_Init(G3D_SDA_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = G3D_END_PIN;
	GPIO_Init(G3D_END_GPIO_PORT, &GPIO_InitStructure);
	SCL_ADXL_SET;
	SDA_ADXL_SET;
	G3D_END_ON;
}

///////????2////////
void  delay_nop(u8 x)
{
	while(x)
	{
		x--;
	}
}

///////////////////////
void ADXL345_Start(void)
{
			SDA_ADXL_SET;                                                               //?????
			SCL_ADXL_SET;                                                               //?????
			delay_nop(20);                                                               //??
			SDA_ADXL_CLR;                                                               //?????
			delay_nop(20);                                                                     //??
			SCL_ADXL_CLR;                                                               //?????
}

void ADXL345_Stop(void)
{
			SDA_ADXL_CLR;                                                               //?????
			SCL_ADXL_SET;                                                               //?????
			delay_nop(20);                                                                      //??
			SDA_ADXL_SET;                                                               //?????
			delay_nop(20);                                                                    //??
}

void ADXL345_SendACK(unsigned char ack)
{
			if(ack==1)
					SDA_ADXL_SET;
			else
					SDA_ADXL_CLR;
			SCL_ADXL_SET;                                                               //?????
			delay_nop(20);                                                                  //??
			SCL_ADXL_CLR;                                                               //?????
			delay_nop(20);                                                                     //??
}

unsigned char ADXL345_RecvACK(void)
{
			unsigned char temp;
			SDA_ADXL_IN;
	    delay_nop(2); 
			SCL_ADXL_SET;                                                               //?????
		  delay_nop(10);                                                                     //??
			if(SDA_ADXL_READ)
					temp=1;
			else
					temp=0;

			SDA_ADXL_OUT;
			SCL_ADXL_CLR;                                                               //?????
		delay_nop(10);                                                                     //??
			return temp;
}

void  ADXL345_SendByte(unsigned char dat)
{
			unsigned int i;
			for (i=0; i<8; i++)                                                         //8????
			{
					if(dat&0x80)                                                            //????????
							SDA_ADXL_SET;
					else
							SDA_ADXL_CLR;
					dat <<= 1;                                                              //????????
					SCL_ADXL_SET;                                                           //?????
					delay_nop(10);                                                                 //??
					SCL_ADXL_CLR;                                                           //?????
					delay_nop(10);                                                                  //??
			}
			ADXL345_RecvACK();
}

unsigned char ADXL345_RecvByte(void)
{
			unsigned int i;
			unsigned char dat = 0;
			SDA_ADXL_SET;                                                               //??????,??????
			for (i=0; i<8; i++)                                                         //8????
			{
					dat <<= 1;
					SCL_ADXL_SET;                                                           //?????
					delay_nop(2); 
				  SDA_ADXL_IN;
					delay_nop(8);   
					if(SDA_ADXL_READ)
							dat |= 1;
					SCL_ADXL_CLR;
					delay_nop(10); 					//?????
			}
			SDA_ADXL_OUT;
			return dat;
}
void    WriteAccRegister(unsigned char REG_Address,unsigned char REG_data)
{
			 ADXL345_Start();                    //IIC??                                
			 ADXL345_SendByte(AccSlaveAddr);     //???????                               
			 ADXL345_SendByte(REG_Address);      //???????                               
			 ADXL345_SendByte(REG_data);         //????                         
			 ADXL345_Stop();                     //IIC??
}

void   ReadAccRegister(unsigned char REG_Address, unsigned char *p)
{    
			 unsigned char REG_data;
			 ADXL345_Start();                                                    //????
			 ADXL345_SendByte(AccSlaveAddr);                                     //??????+???
			 ADXL345_SendByte(REG_Address);                                      //????????,?0??
			 ADXL345_Start();                                                    //????
			 ADXL345_SendByte(AccSlaveAddr+1);                                   //??????+???
			 REG_data= ADXL345_RecvByte();                                       //???????
			 ADXL345_SendACK(1);
			 ADXL345_Stop();
			 *p= REG_data;  
}      

void    STK8312_Init_Setting(void)
{
//        unsigned char RegAddr, RegWriteValue;
		Gyroscope_IIC_GPIO_int();
        //---------------------
        //Software Reset
        //---------------------
            //RegAddr = 0x20;
            //RegWriteValue = 0x00;
            WriteAccRegister(0x20, 0x00);

        //---------------------
        //Set to standby mode
        //---------------------
        //0x07¡ªMODE/Features: 11000000
        //D7            D6          D5          	D4          	D3         		D2          	D1          	D0
        //IAH           IPP         Reserved        Reserved        Reserved        Reserved    	Reserved      	Mode
        //
            //RegAddr = 0x07;
           // RegWriteValue = 0xC0;	//Interrupt active high, push-pull, standby-mode
            WriteAccRegister(0x07, 0xC0);


        //---------------
        //Set Measure Range, Resolution
        //---------------
        //0x13: Dynamic Range Setup and Shake Threshold Register (Read/Write)
        //D7            D6          D5          D4      D3          D2          D1          D0
        //RNG[1]        RNG[0]      -           -       -           STH[2]      STH[1]      STH[0]
        // *** RNG[1:0]     MEASUREMENT RANGE   Resolution ***
        //     00           ¡À1.5 g                6
        //     01           ¡À6   g                8
        //     10           ¡À16  g                8
        //     11           RESERVED

           // RegAddr = 0x13;         
            //RegWriteValue = 0x42;	//6g, 8bit
            WriteAccRegister(0x13, 0x42);

			
        //---------------
        //Output Data Rate Settings :
        //---------------
        //0x08: Auto-Wake and Active Mode Portrait/Landscape Samples per Seconds Register (Read/Write)
        //D7        D6      D5      D4      D3      D2      D1      D0
        //FILT[2]   FILT[1] FILT[0] AWSR[1] AWSR[0] AMSR[2] AMSR[1] AMSR[0]

            //RegAddr = 0x08;
            //RegWriteValue = 0x03;	//ODR=50Hz
            WriteAccRegister(0x08, 0x03);


        //---------------
        //Set Mode as interrupt and measurement operation mode
        //---------------

        //0x06: Interrupt Setup Register (Read/Write)
        //D7        D6      D5      D4      D3      D2      D1      D0
        //SHINTX    SHINTY  SHINTZ  GINT    ASINT   TINT    PLINT   FBINT
          //  RegAddr       = 0x06;   //set Register Address
					//  RegWriteValue = 0x10;   //New Data Interrupt enabled
            WriteAccRegister(0x06, 0x10);
}


void    Set_Enable(u8 en)
{
//        unsigned char RegAddr, RegWriteValue;
        unsigned char readvalue = 0;
        int count = 10;   //time out setting 
	
        if(en)
        {
        //---------------
        //Set to Active mode
        //---------------
        //0x07: Mode Register (Read/Write)
        //D7        	D6      	D5      		D4      		D3      		D2          	D1      		D0
        //IAH           IPP         Reserved        Reserved        Reserved        Reserved    	Reserved      	Mode
        //
           // RegAddr       = 0x07;   //set Register Address      
					 // RegWriteValue = 0xC1;   //INT# active-high, push-pull, Active-Mode
            WriteAccRegister(0x07, 0xC1);  //
           Delay_Nms(1);
        //---------------
        //Engineering Setting
        //---------------

						WriteAccRegister(0x3D, 0x70);      
            WriteAccRegister(0x3D, 0x70);			
            WriteAccRegister(0x3F, 0x02);    
			
            Delay_Nms(1);// mSleep(1);
			
            while((readvalue>>7)!=1 && count!=0) 
            {
                Delay_Nms(4);// mSleep(5);
                ReadAccRegister(0x3F,&readvalue); // Read Engineering Register 0x3F					
                --count; 
            }
            ReadAccRegister(0x3E, &readvalue);
            if(readvalue != 0x00)
            WriteAccRegister( 0x24, readvalue);
				
//            Delay_Nms(50);// mSleep(300);	//Waiting for data ready
        }
        else
        {
							//---------------------
							//Set to standby mode
							//---------------------
							//0x07¡ªMODE/Features: 11000000
							//D7            D6          D5          	D4          	D3         		D2          	D1          	D0
							//IAH           IPP         Reserved        Reserved        Reserved        Reserved    	Reserved      	Mode
							//
							//RegAddr = 0x07;
							//RegWriteValue = 0xC0;	  //Interrupt active high, push-pull, standby-mode
							WriteAccRegister( 0x07, 0xC0);
					    WriteAccRegister( 0x07, 0xc0);
					    WriteAccRegister( 0x07, 0xc0);
        }
}
void  MCU_I2CDataOutRead(void)
{
	if(B_G3D_JC)
	{
		B_G3D_JC=0;
	   ADXL345_Start(); 
     ADXL345_SendByte(AccSlaveAddr); 
     ADXL345_SendByte(0x00); 
     ADXL345_Start(); 
     ADXL345_SendByte(AccSlaveAddr+1); 
		 XYZ_data_out[0] = ADXL345_RecvByte();
		 ADXL345_Stop(); 
		 
		if(XYZ_data_out[0]&0x80)   //Îª-
		{
			if(XYZ_data_out[0]<0xf3)
			{
				if(Flagzhenf_Change_Set!=d_Change)
				{
					Disp_180(d_Change);	
				}  
			}
		}
		else if(XYZ_data_out[0]>4)
		{  
			if(Flagzhenf_Change_Set!=d_Flag)
				{
					Disp_180(d_Flag);		
				} 
		}
	 }
}
#endif









