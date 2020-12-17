#ifndef __STATISTICS_PORT_NUMBER_H__
#define __STATISTICS_PORT_NUMBER_H__


#define	d_Statistics_number_MAX				99999			//最多统计口数
extern	u16	R_Statistics_number_Set;	//设置吸烟口数
extern	u32	R_Statistics_number;			//统计口数
extern	u32	R_Vape_Time_number;			//统计总吸烟时长

//统计吸烟口数和吸烟时长
//入口参数：
extern	void	Statistics_numberANDlengthTim(u8	R_tim_s);
//清除吸烟口数与吸烟时长
extern	void	Clear_numberANDlengthTim(void);
extern	u8	Judge_Vape_plan(void);
#endif


