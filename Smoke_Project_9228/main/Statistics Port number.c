#include "main_2.h"
u16	R_Statistics_number_Set=0;	//设置吸烟口数
u32	R_Statistics_number=0;			//统计口数
u32	R_Vape_Time_number=0;			//统计总吸烟时长
//统计吸烟口数和吸烟时长
//入口参数：R_tim_s*100ms
void	Statistics_numberANDlengthTim(u8	R_tim_s)
{
	static	u8	B;
	static	u8	tim;
	u8	R;
	if(R_tim_s<5)
	{
		B=0;
		tim=0;
	}
	else
	{
		R=R_tim_s-tim;
		if(R)
		{
			R_Vape_Time_number+=R;
			if(R_Vape_Time_number>5999994)
				R_Vape_Time_number=5999994;
			tim=R_tim_s;
		}
		if(!B)
		{
			B=1;
			if(R_Statistics_number<d_Statistics_number_MAX)
				R_Statistics_number++;
		}
	}
}

//清除吸烟口数与吸烟时长
void	Clear_numberANDlengthTim(void)
{
	R_Vape_Time_number=0;
	R_Statistics_number=0;
}

//
u8	Judge_Vape_plan(void)
{
	if(R_Statistics_number_Set==0)
		return	0;
	if(R_Statistics_number>=R_Statistics_number_Set)
		return	1;

	return	0;
}


