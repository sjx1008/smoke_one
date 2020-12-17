#include "stm32f0xx.h"
#include "Stdint_2.h"
#include "APP_Delay.h"
#include "LED091_Driver.h"
#include "OLED_driver.h"
#include "Char_Library.h"

Screen_orientation_TypeDef	B_Screen_orientation=d_Cross_screen;		//横竖屏
Color_TypeDef		R_Front_Color;		//前景色
Color_TypeDef		R_Back_Color;			//背景色

void	exchange_X_Y(s16	*X,s16	*Y)
{
	u16	t;
	if(B_Screen_orientation==d_Vertical_screen)
	{
		t=*X;
		*X=*Y;
		*Y=t;
	}
}
#ifdef	NO_DMA

static	void	OLED_Change_JS(s16	Sx,s16	Sy,s16	Zx,s16	Zy)
{
	s16	xs,xz,ys,yz;
	if(Sx>Zx)
	{
		xs=Zx;
		xz=Sx;
	}
	else
	{
		xs=Sx;
		xz=Zx;
	}
	
	if(Sy>Zy)
	{
		ys=Zy;
		yz=Sy;
	}
	else
	{
		ys=Sy;
		yz=Zy;
	}

	if(xs>R_DISP_windows->Xz || ys>R_DISP_windows->Yz || xz<R_DISP_windows->Xs || yz<R_DISP_windows->Ys)
	{
		return;
	}
	if(xs<R_DISP_windows->Xs)
	{
		xs=R_DISP_windows->Xs;
	}
	if(ys<R_DISP_windows->Ys)
	{
		ys=R_DISP_windows->Ys;
	}
	if(xz>R_DISP_windows->Xz)
	{
		xz=R_DISP_windows->Xz;
	}
	if(yz>R_DISP_windows->Yz)
	{
		yz=R_DISP_windows->Yz;
	}
	
	exchange_X_Y((s16*)&xs,(s16*)&ys);
	exchange_X_Y((s16*)&xz,(s16*)&yz);
	ys/=8;
	yz/=8;
	
	if(OLED_Change.i_s>=d_OLEDRAM_X)
	{
		OLED_Change.i_s=xs;
		OLED_Change.i_z=xz;
		OLED_Change.Page_s=ys;
		OLED_Change.Page_z=yz;
	}
	else
	{
		if(xs<OLED_Change.i_s)
		{
			OLED_Change.i_s=xs;
		}
		if(ys<OLED_Change.Page_s)
		{
			OLED_Change.Page_s=ys;
		}
		if(xz>OLED_Change.i_z)
		{
			OLED_Change.i_z=xz;
		}
		if(yz>OLED_Change.Page_z)
		{
			OLED_Change.Page_z=yz;
		}
	}
}
#endif

//有效窗口范围
DISP_windows	R_DISP_windowsMAX={
	.Xs=0,
	.Xz=d_OLED_X_Max-1,
	.Ys=0,
	.Yz=d_OLED_Y_Max-1,	
};
DISP_windows	R_DISP_windowsSET;
DISP_windows	*R_DISP_windows=&R_DISP_windowsMAX;


/*清除屏幕-------------------------------------------------------------*/
//入口参数：无
void	Clear_screen(void)
{
	u8 i,j;
	for(i=0;i<d_OLEDRAM_Y;i++)
	{
		for(j=0;j<d_OLEDRAM_X;j++)
		{
			R_Disp_RAM[i][j]=d_Clean_Color;
		}
	}
#ifdef	OLED_disp_ON
	OLED_Change.i_s=0;
	OLED_Change.i_z=d_OLED_X_Max-1;
	OLED_Change.Page_s=0;
	OLED_Change.Page_z=(d_OLED_Y_Max-1)/8;
	Windows_Write();
#endif
}

void	Fill_Color(vu8	*Ram,Color_TypeDef	Color,u8	D)
{
	if(Color==d_Clean_Color)
	{
		*Ram&=~D;
	}
	else	if(Color==d_Bright_Color)
	{
		*Ram|=D;
	}
	else	if(Color==d_Transparent_Color)
	{
		*Ram^=D;
	}
}

/*显存单点操作-------------------------------------------------------------*/
//入口参数：Xs，Ys，Color
//		Xs：点的X坐标
//		Xy：点的Y坐标
//		Color：点的颜色    0：熄灭		>0:点亮
static	void	Memory_Single_Dot(s16		Xs,s16	Ys,Color_TypeDef	Color)
{
	u8 i,j,D;
	if(Xs>=R_DISP_windows->Xs && Ys>=R_DISP_windows->Ys && Xs<=R_DISP_windows->Xz && Ys<=R_DISP_windows->Yz)
	{	
		#ifdef	NO_DMA
			OLED_Change_JS(Xs,Ys,Xs,Ys);
		#endif
		
		exchange_X_Y(&Xs,&Ys);
		i=Ys / 8;
		j=Ys % 8;
		
		D=0x01<<j;
		Fill_Color(&R_Disp_RAM[i][Xs],Color,D);
	}
}

/*显存显示实心矩形操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，Screen_property.Xz，Screen_property.Yz，
//					Screen_property.Color,
static	void	Memory_Single_block(s16	Xs,s16	Ys,s16	Xz,s16	Yz,Color_TypeDef	Color)
{
	s16	xss,xzz,yss,yzz;
	u8	i,j,Ds,Dz;
	#ifdef	NO_DMA
		OLED_Change_JS(Xs,Ys,Xz,Yz);
	#endif
	
	if(Xs>Xz)
	{
		xss=Xz;
		xzz=Xs;
	}
	else
	{
		xss=Xs;
		xzz=Xz;
	}
	
	if(Ys>Yz)
	{
		yss=Yz;
		yzz=Ys;
	}
	else
	{
		yss=Ys;
		yzz=Yz;
	}

	if(xss>R_DISP_windows->Xz || yss>R_DISP_windows->Yz || xzz<R_DISP_windows->Xs || yzz<R_DISP_windows->Ys)
	{
		return;
	}
	if(xss<R_DISP_windows->Xs)
	{
		xss=R_DISP_windows->Xs;
	}
	if(yss<R_DISP_windows->Ys)
	{
		yss=R_DISP_windows->Ys;
	}
	
	if(xzz>R_DISP_windows->Xz)
	{
		xzz=R_DISP_windows->Xz;
	}
	if(yzz>R_DISP_windows->Yz)
	{
		yzz=R_DISP_windows->Yz;
	}

	exchange_X_Y((s16*)&xss,(s16*)&yss);
	exchange_X_Y((s16*)&xzz,(s16*)&yzz);
	Ds=0xff<<(yss%8);
	if((yzz/8)==(yss/8))
	{
		Ds &= 0xff>>(7-yzz%8);
	}
	
	Dz=0xff>>(7-yzz%8);
	if((yzz/8)==(yss/8))
	{
		Dz &= 0xff<<(yss%8);
	}
	
	yss/=8;
	yzz/=8;
	
	for(i=xss;i<=xzz;i++)
	{
		Fill_Color(&R_Disp_RAM[yss][i],Color,Ds);
	}
	if(yss!=yzz)
	{
		for(i=xss;i<=xzz;i++)
		{
			Fill_Color(&R_Disp_RAM[yzz][i],Color,Dz);
		}
		for(j=yss+1;j<yzz;j++)
		{
			for(i=xss;i<=xzz;i++)
			{
				Fill_Color(&R_Disp_RAM[j][i],Color,0xff);
			}
		}
	}
}

void	GUI_Write_Dot(s16		Xs,s16	Ys)
{
	Memory_Single_Dot(Xs,Ys,R_Front_Color);
	#ifdef	OLED_disp_ON
	Windows_Write();
	#endif
}
//读点的颜色
Color_TypeDef	GUI_Read_Dot(s16		Xs,s16	Ys)
{
	u8 i,j,D;
	if(Xs>=R_DISP_windows->Xs && Ys>=R_DISP_windows->Ys && Xs<=R_DISP_windows->Xz && Ys<=R_DISP_windows->Yz)
	{	
		exchange_X_Y(&Xs,&Ys);
		i=Ys / 8;
		j=Ys % 8;
		
		D=0x01<<j;
		if(R_Disp_RAM[i][Xs] & D)
			return	d_Bright_Color;
	}
	return	d_Clean_Color;
}
/*显存显示实心矩形操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，Screen_property.Xz，Screen_property.Yz，
//					Screen_property.Color,
void	GUI_Write_block(s16	Xs,s16	Ys,s16	Xz,s16	Yz)
{
	Memory_Single_block(Xs,Ys,Xz,Yz,R_Front_Color);
	#ifdef	OLED_disp_ON
	Windows_Write();
	#endif
}

/*显存显示直线操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，Screen_property.Xz，Screen_property.Yz，
//					Screen_property.Color,
void	GUI_Write_Line(s16	Xs,s16	Ys,s16	Xz,s16	Yz)
{
	s16 t, distance;      
	s16 x = 0 , y = 0 , delta_x, delta_y ;
	s8 	incx, incy ;
	
	delta_x = Xz - Xs ;
	delta_y = Yz - Ys ;
	if( delta_x > 0 )
	{
		incx = 1;
	}
	else if( delta_x == 0 )
	{
		GUI_Write_block(Xs,Ys,Xz,Yz);
		return;
	}
	else
	{
		incx = -1;
	}
	if( delta_y > 0 )
	{
		incy = 1;
	}
	else if(delta_y == 0 )
	{
		GUI_Write_block(Xs,Ys,Xz,Yz);
		return;
	}
	else
	{
		incy = -1 ;
	}
	if(delta_x<0)
	{
		delta_x=-delta_x;
	}
	if(delta_y<0)
	{
		delta_y=-delta_y;
	}
	if( delta_x > delta_y )
	{
		distance = delta_x ;
	}
	else
	{
		distance = delta_y ; 
	}
	
/* Draw Line*/
	
	for( t = 0 ; t <= distance+1 ; t++ )
	{
		Memory_Single_Dot(Xs,Ys,R_Front_Color);
		x += delta_x ;
		y += delta_y ;
		if( x > distance )
		{
			x -= distance ;
			Xs += incx ;
		}
		if( y > distance )
		{
			y -= distance ;
			Ys += incy ;
		}
	}
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
}


/*显存显示空心矩形操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，Screen_property.Xz，Screen_property.Yz，
//					Screen_property.Color,
void	GUI_Write_Rectangular(s16	Xs,s16	Ys,s16	Xz,s16	Yz)
{
	Memory_Single_block(Xs,Ys,Xz,Ys,R_Front_Color);
	Memory_Single_block(Xs,Yz,Xz,Yz,R_Front_Color);
	Memory_Single_block(Xs,Ys,Xs,Yz,R_Front_Color);
	Memory_Single_block(Xz,Ys,Xz,Yz,R_Front_Color);
	#ifdef	OLED_disp_ON
	Windows_Write();
	#endif
}

static	void	Memory_Single_Arc(s16	Xs,s16 Ys,u8	R,u16	Angle_S,u16	Angle_Z)
{
	s16 x=0,y=R,f=0;
	u16	i=0,j=0;
	while(x<=y)
	{
		i++;
		if(f<=0)
		{
			f+=2*x+1;
			x++;
		}
		else
		{
			f-=2*y+1;
			y--;
		}
	}
	Angle_S=Angle_S*i/45;
	Angle_Z=Angle_Z*i/45;
	x=0;
	y=R;
	f=0;
	while(x<=y)
	{
		j++;
		if(Angle_Z>Angle_S)
		{
			if(j>=Angle_S && j<=Angle_Z)
				Memory_Single_Dot(Xs+y,Ys-x,R_Front_Color);//1
			if(2*i-j>=Angle_S && 2*i-j<=Angle_Z)
				Memory_Single_Dot(Xs+x,Ys-y,R_Front_Color);//2
			if(2*i+j>=Angle_S && 2*i+j<=Angle_Z)
				Memory_Single_Dot(Xs-x,Ys-y,R_Front_Color);//3
			if(4*i-j>=Angle_S && 4*i-j<=Angle_Z)
				Memory_Single_Dot(Xs-y,Ys-x,R_Front_Color);//4
			if(4*i+j>=Angle_S && 4*i+j<=Angle_Z)
				Memory_Single_Dot(Xs-y,Ys+x,R_Front_Color);//5
			if(6*i-j>=Angle_S && 6*i-j<=Angle_Z)
				Memory_Single_Dot(Xs-x,Ys+y,R_Front_Color);//6
			if(6*i+j>=Angle_S && 6*i+j<=Angle_Z)
				Memory_Single_Dot(Xs+x,Ys+y,R_Front_Color);//7
			if(8*i-j>=Angle_S && 8*i-j<=Angle_Z)
				Memory_Single_Dot(Xs+y,Ys+x,R_Front_Color);//8
		}
		else
		{
			if(j>=Angle_S || j<=Angle_Z)
				Memory_Single_Dot(Xs+y,Ys-x,R_Front_Color);//1
			if(2*i-j>=Angle_S || 2*i-j<=Angle_Z)
				Memory_Single_Dot(Xs+x,Ys-y,R_Front_Color);//2
			if(2*i+j>=Angle_S || 2*i+j<=Angle_Z)
				Memory_Single_Dot(Xs-x,Ys-y,R_Front_Color);//3
			if(4*i-j>=Angle_S || 4*i-j<=Angle_Z)
				Memory_Single_Dot(Xs-y,Ys-x,R_Front_Color);//4
			if(4*i+j>=Angle_S || 4*i+j<=Angle_Z)
				Memory_Single_Dot(Xs-y,Ys+x,R_Front_Color);//5
			if(6*i-j>=Angle_S || 6*i-j<=Angle_Z)
				Memory_Single_Dot(Xs-x,Ys+y,R_Front_Color);//6
			if(6*i+j>=Angle_S || 6*i+j<=Angle_Z)
				Memory_Single_Dot(Xs+x,Ys+y,R_Front_Color);//7
			if(8*i-j>=Angle_S || 8*i-j<=Angle_Z)
				Memory_Single_Dot(Xs+y,Ys+x,R_Front_Color);//8
		}
		if(f<=0)
		{
			f+=2*x+1;
			x++;
		}
		else
		{
			f-=2*y+1;
			y--;
		}
	}
}
static	void	Memory_Single_Sector(s16	Xs,s16 Ys,u8	R,u16	Angle_S,u16	Angle_Z)
{
	u8	i;
	for(i=0;i<=R;i++)
	{
		Memory_Single_Arc(Xs,Ys,i,Angle_S,Angle_Z);
	}
}
/*显示空心园操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，R
//					Screen_property.Color,	
void	GUI_Write_Round(s16	Xs,s16 Ys,u8	R)
{
	Memory_Single_Arc(Xs,Ys,R,0,360);
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
}

/*显存显示圆弧操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，R
//					Screen_property.Color,	
void	GUI_Write_Arc(s16	Xs,s16 Ys,u8	R,u16	Angle_S,u16	Angle_Z)
{
	Memory_Single_Arc(Xs,Ys,R,Angle_S,Angle_Z);
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
}

/*显存显示扇形操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，R
//					Screen_property.Color,	
void	GUI_Write_Sector(s16	Xs,s16 Ys,u8	R,u16	Angle_S,u16	Angle_Z)
{
	Memory_Single_Sector(Xs,Ys,R,Angle_S,Angle_Z);
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
}

/*显存显示圆角矩形操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，R
//					Screen_property.Color,	
void	GUI_Write_Rounded_rectangle(s16	X1,s16	Y1,s16	X2,s16	Y2,u8	R)
{
	s16	Xs,Xz,Ys,Yz;
//	u16	H,L;
	u8	rr;
	if(X1>X2)
	{
		Xs=X2;
		Xz=X1;
	}
	else
	{
		Xs=X1;
		Xz=X2;
	}
	if(Y1>Y2)
	{
		Ys=Y2;
		Yz=Y1;
	}
	else
	{
		Ys=Y1;
		Yz=Y2;
	}
//	L=Xz-Xs;
//	H=Yz-Ys;
	if(R)
		rr=R-1;
	Memory_Single_block(Xs+R,Ys,Xz-rr,Ys,R_Front_Color);
	Memory_Single_block(Xs+R,Yz,Xz-R,Yz,R_Front_Color);
	Memory_Single_block(Xs,Ys+R,Xs,Yz-R,R_Front_Color);
	Memory_Single_block(Xz,Ys+R,Xz,Yz-R,R_Front_Color);
	Memory_Single_Arc(Xs+rr,Ys+rr,rr,90,180);
	Memory_Single_Arc(Xz-rr,Ys+rr,rr,0,90);
	Memory_Single_Arc(Xs+rr,Yz-rr,rr,180,270);
	Memory_Single_Arc(Xz-rr,Yz-rr,rr,270,360);
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
}

/*显存显示实心圆角矩形操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，R
//					Screen_property.Color,	
void	GUI_Write_Rounded_block(s16	X1,s16	Y1,s16	X2,s16	Y2,u8	R)
{
	s16	Xs,Xz,Ys,Yz;
//	u16	H,L;
	u8	rr;
	if(X1>X2)
	{
		Xs=X2;
		Xz=X1;
	}
	else
	{
		Xs=X1;
		Xz=X2;
	}
	if(Y1>Y2)
	{
		Ys=Y2;
		Yz=Y1;
	}
	else
	{
		Ys=Y1;
		Yz=Y2;
	}
//	L=Xz-Xs;
//	H=Yz-Ys;
	if(R)
		rr=R-1;
	Memory_Single_block(Xs+R,Ys+R,Xz-R,Yz-R,R_Front_Color);
	Memory_Single_block(Xs+R,Ys,Xz-R,Ys+rr,R_Front_Color);
	Memory_Single_block(Xs+R,Yz-rr,Xz-R,Yz,R_Front_Color);
	Memory_Single_block(Xs,Ys+R,Xs+rr,Yz-R,R_Front_Color);
	Memory_Single_block(Xz-rr,Ys+R,Xz,Yz-R,R_Front_Color);
	Memory_Single_Sector(Xs+rr,Ys+rr,rr,90,180);
	Memory_Single_Sector(Xz-rr,Ys+rr,rr,0,90);
	Memory_Single_Sector(Xs+rr,Yz-rr,rr,180,270);
	Memory_Single_Sector(Xz-rr,Yz-rr,rr,270,360);
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
}

/*显存显示实心园操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，R
//					Screen_property.Color,	

void	GUI_Write_Pie(s16	Xs,s16	Ys,u8	R)
{
	s16 i,j,a,b,c;
	s16 xss,yss,xzz,yzz;
	u32 R2;

	xss=Xs-R;
	xzz=Xs+R;
	yss=Ys-R;
	yzz=Ys+R;
	R2=R*R;
	if(xss<R_DISP_windows->Xs)
	{
		xss=R_DISP_windows->Xs;
	}
	else if(xss>R_DISP_windows->Xz)
	{
		return;
	}
	if(xzz<R_DISP_windows->Xs)
	{
		return;
	}
	else if(xzz>R_DISP_windows->Xz)
	{
		xzz=R_DISP_windows->Xz;
	}
	
	if(yss<R_DISP_windows->Ys)
	{
		yss=R_DISP_windows->Ys;
	}
	else if(yss>R_DISP_windows->Yz)
	{
		return;
	}
	if(yzz<R_DISP_windows->Ys)
	{
		return;
	}
	else if(yzz>R_DISP_windows->Yz)
	{
		yzz=R_DISP_windows->Yz;
	}
	
	for(j=yss;j<=yzz;j++)
	{
		c=0x0fff;
		for(i=xss;i<=xzz;i++)
		{
			
			a=i>Xs ? i-Xs:Xs-i;
			b=j>Ys ? j-Ys:Ys-j;
			if(R2>=(a*a+b*b))
			{
				if(c==0x0fff)
				{
					c=i;
				}					
			}	
			else
			{
				if(c!=0x0fff)
				{
					break;
				}
			}
		}
		if(c!=0x0fff)
		{
			Memory_Single_block(c,j,i-1,j,R_Front_Color);
		}
	}
#ifdef	OLED_disp_ON
	Windows_Write();
#endif	
}

////////画长为w，高为h	的位图
void GUI_Write_Bitmap_W_H(s16 Xstart,s16 Ystart,uc8 *P,u8	WIDE,u8	HIGH)
{
	s16	i,j,a,b;
	u16 c;
	u16 k;
	u8	R;
	
	if(Xstart>R_DISP_windows->Xz || Ystart>R_DISP_windows->Yz || (Xstart+WIDE-1)<R_DISP_windows->Xs	||	(Ystart+HIGH-1)<R_DISP_windows->Ys)
	{
		return;
	}
	
	c=WIDE/8;
	if(WIDE%8)
	{
		c++;
	}
	
	if((Xstart+WIDE-1)>R_DISP_windows->Xz)
		a=R_DISP_windows->Xz;
	else
		a=Xstart+WIDE-1;
	if((Ystart+HIGH-1)>R_DISP_windows->Yz)
		b=R_DISP_windows->Yz;
	else
		b=Ystart+HIGH-1;
	
	k=0;
	for(i=Ystart;i<=b;i++)
	{
		k=c*(i-Ystart);
		for(j=Xstart;j<=a;j++)
		{
			if(!((j-Xstart)%8))
			{
				R=*(P+k);
				k++;
			}
			if(j>=0 && i>=0)
			{
				if(R & 0x80)
				{	
					Memory_Single_Dot(j,i,R_Front_Color);
				}
				else if(R_Back_Color!=d_Transparent_Color)
				{
					Memory_Single_Dot(j,i,R_Back_Color);
				}
			}
			R<<=1;
		}
	}
	#ifdef	OLED_disp_ON
	Windows_Write();
	#endif
}

////////画位图
void GUI_Write_Bitmap(s16 Xstart,s16 Ystart,uc8 *P)
{
	GUI_Write_Bitmap_W_H(Xstart,Ystart,P+2,P[0],P[1]);
}

///////显示字符串
void GUI_Write_Chars(s16 Xstart,s16 Yend,uc8 *Pchar,Font_TypeDef Font)
{
	s16	i,j,a,b,Ystart;
	u8	ZT_L,c,k,D,l;
	uc8	*const	*A;
	u8	high;
	
	switch(Font)
	{
	#ifdef	Font_6_ON
		case	ZT6:	A=ASCII6;high=6;break;
	#endif
		
	#ifdef	Font_7_ON
		case	ZT7:	A=ASCII7;high=7;break;
	#endif
		
	#ifdef	Font_8_ON
		case	ZT8:	A=ASCII8;high=8;break;
	#endif
		
	#ifdef	Font_9_ON
		case	ZT9:	A=ASCII9;high=9;break;
	#endif
	
	#ifdef	Font_10_ON
		case	ZT10:	A=ASCII10;high=10;break;
	#endif
		
	#ifdef	Font_12_ON
		case	ZT12:	A=ASCII12;high=12;break;
	#endif
		
	#ifdef	Font_12B_ON
		case	ZT12B:	A=ASCII12B;high=12;break;
	#endif

	#ifdef	Font_13_ON
		case	ZT13:	A=ASCII13;high=13;break;
	#endif
		
	#ifdef	Font_16_ON
		case	ZT16:	A=ASCII16;high=16;break;
	#endif

	#ifdef	Font_19_ON
		case	ZT19:	A=ASCII19;high=19;break;
	#endif

	#ifdef	Font_20_ON
		case	ZT20:	A=ASCII20;high=20;break;
	#endif

	#ifdef	Font_21_ON
		case	ZT21:	A=ASCII21;high=21;break;
	#endif
		
	#ifdef	Font_24_ON
		case	ZT24:	A=ASCII24;high=24;break;
	#endif
	
	#ifdef	Font_27_ON
		case	ZT27:	A=ASCII27;high=27;break;
	#endif
	
	#ifdef	Font_32_ON
		case	ZT32:	A=ASCII32;high=32;break;
	#endif	
		default	: return;
	}
	
	Ystart=Yend-high+1;
	if(Xstart>R_DISP_windows->Xz || Ystart>R_DISP_windows->Yz ||	Yend<R_DISP_windows->Ys)
	{
		return;
	}
	
	if(Yend>R_DISP_windows->Yz)
		b=R_DISP_windows->Yz;
	else
		b=Yend;
	k=0;
	while(*(Pchar+k))
	{	
		ZT_L=*(*(A+(*(Pchar+k)-32)));
		
		c=ZT_L/8;
		if(ZT_L%8)
		{
			c++;
		}
	
		if((Xstart+ZT_L-1)>R_DISP_windows->Xz)
			a=R_DISP_windows->Xz;
		else
			a=Xstart+ZT_L-1;
	
		l=0;

		for(i=Ystart;i<=b;i++)
		{
			for(j=Xstart;j<=a;j++)
			{
				if(!((j-Xstart)%8))
				{
					l++;
					D=*(*(A+(*(Pchar+k)-32))+l);
				}
				if(j<R_DISP_windows->Xs || i<R_DISP_windows->Ys)
				{
					D<<=1;
					continue;
				}
				if(D & 0x80)
				{	
					Memory_Single_Dot(j,i,R_Front_Color);
				}
				else	if(R_Back_Color!=d_Transparent_Color)
				{
					Memory_Single_Dot(j,i,R_Back_Color);
				}
				D<<=1;
			}
			l=c*(i-Ystart+1);
		}	
		Xstart+=ZT_L;
		if(Xstart>R_DISP_windows->Xz)
		{
			//return;
			goto	Memory_Single_Chars_0;
		}
		k++;
	}
	Memory_Single_Chars_0:
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
	return;
}

///////显示英文字符
void GUI_Write_Char(s16 Xstart,s16 Yend,uc8 Pchar,Font_TypeDef Font)
{
	u8	S[2];
	S[0]=Pchar;
	S[1]=0;
	GUI_Write_Chars(Xstart,Yend,S,Font);
}


///////显示中文字符串
void	GUI_Write_Zhongwen(s16 Xstart,s16 Yend,uc8 *Pchar,Zhong_TypeDef Font)
{
	s16	i,j,a,b,Ystart;
	u8	ZT_L,c,k,D,l;
	u16	Zhong_I;
	u16	Length;
	u8	high;
	
	Chinese_typ	*const	*A;
	
	switch(Font)
	{
	#ifdef	Zhong_16_ON
		case	ZgT16:	A=ZHONG16;Length=ZHONG16_length;high=16;break;
	#endif
		default	: return;
	}
	
	Ystart=Yend-high+1;
	if(Xstart>R_DISP_windows->Xz || Ystart>R_DISP_windows->Yz ||	Yend<R_DISP_windows->Ys)
	{
		return;
	}
	
	if(Yend>R_DISP_windows->Yz)
		b=R_DISP_windows->Yz;
	else
		b=Yend;
	k=0;
	
	while(Pchar[k]!=0)
	{	
		for(Zhong_I=0;Zhong_I<Length;Zhong_I++)
		{
			if((A[Zhong_I]->zhong->ints)==(Pchar[k] | Pchar[k+1]<<8))
				break;
		}
		if(Zhong_I<Length)
		{
			ZT_L=A[Zhong_I]->data[0];
			c=ZT_L/8;
			if(ZT_L%8)
			{
				c++;
			}

			if((Xstart+ZT_L-1)>R_DISP_windows->Xz)
				a=R_DISP_windows->Xz;
			else
				a=Xstart+ZT_L-1;

			l=1;
			for(i=Ystart;i<=b;i++)
			{
				for(j=Xstart;j<=a;j++)
				{
					if(!((j-Xstart)%8))
					{
						D=A[Zhong_I]->data[l];
						l++;
					}
					if(j<R_DISP_windows->Xs || i<R_DISP_windows->Ys)
					{
						D<<=1;
						continue;
					}
					if(D & 0x80)
					{	
						Memory_Single_Dot(j,i,R_Front_Color);
					}
					else	if(R_Back_Color!=d_Transparent_Color)
					{
						Memory_Single_Dot(j,i,R_Back_Color);
					}
					D<<=1;
				}
				l=c*(i-Ystart+1)+1;
			}	
			Xstart+=ZT_L;
			if(Xstart>R_DISP_windows->Xz)
			{
				//return;
				goto	Memory_Single_Chars_0;
			}
		}
		k+=2;
	}
	Memory_Single_Chars_0:
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
	return;
}

///////显示数值 x,y,位数，数据，字体，前面是否补0
void GUI_Write_data(s16 Xstart,s16 Yend,u8 Alignment,u32 data,Font_TypeDef	Font,u8	Zerofill)
{
	u8 	a,j;
	u32 i;
	u8 	s[11];
	i=1;
	a=0;
	
	do
	{
		i*=10;
		s[a]='0'+(data%i)/(i/10);
		a++;
	}while(data/i);

	if(a<Alignment)
	{
		for(i=a;i<Alignment;i++)
		{
			if(Zerofill)
				s[i]='0';
			else
				s[i]=' ';
		}
		a=Alignment;
	}
	
	for(i=0;i<(a>>1);i++)
	{
		j=s[i];
		s[i]=s[a-1-i];
		s[a-1-i]=j;
	}	
	s[a]='\0';
	
	GUI_Write_Chars(Xstart,Yend,s,Font);
}


/*显存宽度为2或3直线操作-------------------------------------------------------------*/
//入口参数：Screen_property.Xs，Screen_property.Ys，Screen_property.Xz，Screen_property.Yz，
//					Screen_property.Color,
void	GUI_Write_Line_D(s16	Xs,s16	Ys,s16	Xz,s16	Yz,u8	D)
{
	s16 t, distance;      
	s16 x = 0 , y = 0 , delta_x, delta_y ;
	s8 	incx, incy ;
	
	s8	r=0;
	
	if(D==1)
		r=1;
	else
	{
		r=D/2;
	}
	
	delta_x = Xz - Xs ;
	delta_y = Yz - Ys ;
	if( delta_x > 0 )
	{
		incx = 1;
	}
	else if( delta_x == 0 )
	{
		incx=0;
	}
	else
	{
		incx = -1;
	}
	if( delta_y > 0 )
	{
		incy = 1;
	}
	else if(delta_y == 0 )
	{
		incy=0;
	}
	else
	{
		incy = -1 ;
	}
	if(delta_x<0)
	{
		delta_x=-delta_x;
	}
	if(delta_y<0)
	{
		delta_y=-delta_y;
	}
	if( delta_x > delta_y )
	{
		distance = delta_x ;
	}
	else
	{
		distance = delta_y ; 
	}
	
/* Draw Line*/
	
	for( t = 0 ; t <= distance+1 ; t++ )
	{
		if(D==0)
			Memory_Single_Dot(Xs,Ys,R_Front_Color);
		else	if(D==1)
			Memory_Single_block(Xs,Ys,Xs+r,Ys+r,R_Front_Color);
		else
			Memory_Single_Sector(Xs,Ys,r,0,360);
		x += delta_x ;
		y += delta_y ;
		if( x > distance )
		{
			x -= distance ;
			Xs += incx ;
		}
		if( y > distance )
		{
			y -= distance ;
			Ys += incy ;
		}
	}
	#ifdef	OLED_disp_ON
		Windows_Write();
	#endif
}

//画实心三角形
#define swap(a, b) { int16_t t = a; a = b; b = t; }
void GUI_Write_Filled_triangle(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2)
{
  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
		GUI_Write_block(a,y0,b,y0);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
		GUI_Write_block(a,y,b,y);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
		GUI_Write_block(a,y,b,y);
  }
}

//打开窗口范围
void	SET_Disp_Windows_ON(u8	Xs,u8	Ys,u8	Xz,u8	Yz)
{
	R_DISP_windowsSET.Xs=Xs;
	R_DISP_windowsSET.Xz=Xz;
	R_DISP_windowsSET.Ys=Ys;
	R_DISP_windowsSET.Yz=Yz;
	R_DISP_windows=&R_DISP_windowsSET;
}
//关闭窗口范围
void	SET_Disp_Windows_OFF(void)
{
	R_DISP_windows=&R_DISP_windowsMAX;
}



