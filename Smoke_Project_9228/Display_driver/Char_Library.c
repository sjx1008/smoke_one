#include	"main.h"
uc8 Zero[]={0};

#ifdef	Font_7_ON
		//--------------------------高7*宽?----------------------//
	uc8 A7q32[]={5,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*" ",0*/
//	uc8 A7q33[]={0};/*"!",0*/
//	uc8 A7q34[]={0x00};/*""",1*/
//	uc8 A7q35[]={0x00};/*"#",2*/
//	uc8 A7q36[]={3,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"$",3*/
//	uc8 A7q37[]={6,0x90,0x20,0x20,0x40,0x40,0x80,0x90};/*"%",4*/
//	uc8 A7q38[]={2,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"&",5*/
//	uc8 A7q39[]={0x00};/*"'",6*/
//	uc8 A7q40[]={3,0x40,0x80,0x80,0x80,0x80,0x80,0x40};/*"(",7*/
//	uc8 A7q41[]={3,0x80,0x40,0x40,0x40,0x40,0x40,0x80};/*")",8*/
//	uc8 A7q42[]={0x00};/*"*",9*/
//	uc8 A7q43[]={0x00};/*"+",10*/
//	uc8 A7q44[]={0x00};/*",",11*/
	uc8 A7q45[]={5,0x00,0x00,0x00,0xF0,0x00,0x00,0x00};/*"-",12*/
	uc8 A7q46[]={2,0x00,0x00,0x00,0x00,0x00,0x00,0x80};/*".",13*/
//	uc8 A7q47[]={6,0x10,0x10,0x20,0x20,0x40,0x40,0x80};/*"/",14*/
	uc8 A7q48[]={5,0x60,0x90,0x90,0x90,0x90,0x90,0x60};/*"0",0*/
	uc8 A7q49[]={5,0x20,0x60,0x20,0x20,0x20,0x20,0x70};/*"1",1*/
	uc8 A7q50[]={5,0x60,0x90,0x10,0x20,0x40,0x80,0xF0};/*"2",2*/
	uc8 A7q51[]={5,0x60,0x90,0x10,0x60,0x10,0x90,0x60};/*"3",3*/
	uc8 A7q52[]={5,0x20,0x60,0xA0,0xA0,0xF0,0x20,0x20};/*"4",4*/
	uc8 A7q53[]={5,0xF0,0x80,0xE0,0x10,0x10,0x90,0x60};/*"5",5*/
	uc8 A7q54[]={5,0x60,0x90,0x80,0xE0,0x90,0x90,0x60};/*"6",6*/
	uc8 A7q55[]={5,0xF0,0x90,0x10,0x20,0x20,0x40,0x40};/*"7",7*/
	uc8 A7q56[]={5,0x60,0x90,0x90,0x60,0x90,0x90,0x60};/*"8",8*/
	uc8 A7q57[]={5,0x60,0x90,0x90,0x70,0x10,0x90,0x60};/*"9",9*/
//	uc8 A7q58[]={0x00};/*":",15*/
//	uc8 A7q59[]={0x00};/*";",16*/
//	uc8 A7q60[]={0x00};/*"<",17*/
//	uc8 A7q61[]={0x00};/*"=",18*/
//	uc8 A7q62[]={0x00};/*">",19*/
//	uc8 A7q63[]={0};/*"?",20*/
//	uc8 A7q64[]={0x00};/*"@",21*/
	uc8 A7q65[]={6,0x20,0x50,0x50,0x88,0xF8,0x88,0x88};/*"A",0*/
	uc8 A7q66[]={5,0xE0,0x90,0x90,0xE0,0x90,0x90,0xE0};/*"B",1*/
//	uc8 A7q67[]={6,0x70,0x88,0x80,0x80,0x80,0x88,0x70};/*"C",2*/
	uc8 A7q68[]={5,0xE0,0x90,0x90,0x90,0x90,0x90,0xE0};/*"D",3*/
	uc8 A7q69[]={5,0xF0,0x80,0x80,0xF0,0x80,0x80,0xF0};/*"E",4*/
//	uc8 A7q70[]={6,0xF8,0x80,0x80,0xF0,0x80,0x80,0x80};/*"F",5*/
//	uc8 A7q71[]={6,0x70,0x88,0x80,0x80,0xB8,0x88,0x70};/*"G",6*/
//	uc8 A7q72[]={6,0x88,0x88,0x88,0xF8,0x88,0x88,0x88};/*"H",7*/
	uc8 A7q73[]={4,0xE0,0x40,0x40,0x40,0x40,0x40,0xE0};/*"I",8*/
	uc8 A7q74[]={4,0x20,0x20,0x20,0x20,0x20,0xA0,0x40};/*"J",9*/
//	uc8 A7q75[]={6,0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88};/*"K",10*/
//	uc8 A7q76[]={5,0x80,0x80,0x80,0x80,0x80,0x80,0xF0};/*"L",11*/
	uc8 A7q77[]={6,0x88,0xD8,0xD8,0xA8,0xA8,0xA8,0xA8};/*"M",12*/
//	uc8 A7q78[]={6,0x88,0xC8,0xE8,0xA8,0xB8,0x98,0x88};/*"N",13*/
	uc8 A7q79[]={5,0x60,0x90,0x90,0x90,0x90,0x90,0x60};/*"O",14*/
//	uc8 A7q80[]={6,0xF0,0x88,0x88,0x88,0xF0,0x80,0x80};/*"P",15*/
//	uc8 A7q81[]={6,0x70,0x88,0x88,0x88,0xA8,0x90,0x68};/*"Q",16*/
	uc8 A7q82[]={6,0xF0,0x88,0x88,0xF0,0x88,0x88,0x88};/*"R",17*/
	uc8 A7q83[]={5,0x60,0x90,0x80,0x60,0x10,0x90,0x60};/*"S",0*/
	uc8 A7q84[]={6,0xF8,0x20,0x20,0x20,0x20,0x20,0x20};/*"T",19*/
	uc8 A7q85[]={5,0x90,0x90,0x90,0x90,0x90,0x90,0x60};/*"U",20*/
	uc8 A7q86[]={6,0x88,0x88,0x88,0x50,0x50,0x20,0x20};/*"V",21*/
	uc8 A7q87[]={6,0xA8,0xA8,0xA8,0xA8,0x50,0x50,0x50};/*"W",22*/
//	uc8 A7q88[]={6,0x88,0x88,0x50,0x20,0x50,0x88,0x88};/*"X",23*/
	uc8 A7q89[]={6,0x88,0x88,0x50,0x50,0x20,0x20,0x20};/*"Y",24*/
//	uc8 A7q90[]={6,0xF8,0x08,0x10,0x20,0x40,0x80,0xF8};/*"Z",25*/
	//uc8 A7q91[]={0x00};/*"[",22*/
	//uc8 A7q92[]={0x00};/*"\",23*/
	//uc8 A7q93[]={0x00};/*"]",24*/
	//uc8 A7q94[]={0x00};/*"^",25*/
	uc8 A7q95[]={4,0x00,0x00,0x00,0x00,0x00,0x00,0xE0};/*"_",26*/
	//uc8 A7q96[]={0x00};/*"`",27*/
	//uc8 A7q97[]={0x00};/*"a",0*/
	//uc8 A7q98[]={0x00};/*"b",1*/
	//uc8 A7q99[]={0x00};/*"c",2*/
	//uc8 A7q100[]={0x00};/*"d",3*/
	//uc8 A7q101[]={0x00};/*"e",4*/
	//uc8 A7q102[]={0x00};/*"f",5*/
	//uc8 A7q103[]={0x00};/*"g",6*/
	//uc8 A7q104[]={0x00};/*"h",7*/
	//uc8 A7q105[]={0x00};/*"i",8*/
	//uc8 A7q106[]={0x00};/*"j",9*/
	//uc8 A7q107[]={0x00};/*"k",10*/
	//uc8 A7q108[]={0x00};/*"l",11*/
	//uc8 A7q109[]={0x00};/*"m",12*/
	//uc8 A7q110[]={0x00};/*"n",13*/
	//uc8 A7q111[]={0x00};/*"o",14*/
	//uc8 A7q112[]={0x00};/*"p",15*/
	//uc8 A7q113[]={0x00};/*"q",16*/
	//uc8 A7q114[]={0x00};/*"r",17*/
	//uc8 A7q115[]={0x00};/*"s",18*/
	//uc8 A7q116[]={0x00};/*"t",19*/
	//uc8 A7q117[]={0x00};/*"u",20*/
	//uc8 A7q118[]={0x00};/*"v",21*/
	//uc8 A7q119[]={0x00};/*"w",22*/
	//uc8 A7q120[]={0x00};/*"x",23*/
	//uc8 A7q121[]={0x00};/*"y",24*/
	//uc8 A7q122[]={0x00};/*"z",25*/
	//uc8 A7q123[]={0x00};/*"{",28*/
	//uc8 A7q124[]={0};/*"|",29*/
	//uc8 A7q125[]={0};/*"}",30*/
	//uc8 A7q126[]={0};/*"~",31*/

	uc8 *const	ASCII7[]={A7q32,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,A7q45,A7q46,Zero,A7q48,A7q49,
		A7q50,A7q51,A7q52,A7q53,A7q54,A7q55,A7q56,A7q57,Zero,Zero,Zero,Zero,Zero,Zero,Zero,A7q65,A7q66,Zero,A7q68,A7q69,
		Zero,Zero,Zero,A7q73,A7q74,Zero,Zero,A7q77,Zero,A7q79,Zero,Zero,A7q82,A7q83,A7q84,A7q85,A7q86,A7q87,Zero,A7q89,
		Zero,Zero,Zero,Zero,Zero,A7q95/*,A7q96,A7q97,A7q98,A7q99,A7q100,A7q101,A7q102,A7q103,A7q104,A7q105,A7q106,A7q107,A7q108,A7q109,
		A7q110,A7q111,A7q112,A7q113,A7q114,A7q115,A7q116,A7q117,A7q118,A7q119,A7q120,A7q121,A7q122,A7q123,A7q124,A7q125,A7q126*/};
#endif
		
		
#ifdef	Font_10_ON
		//--------------------------高10*宽?----------------------//
	uc8 A10q32[]={6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*" ",0*/
//	uc8 A10q33[]={0};/*"!",0*/
//	uc8 A10q34[]={0x00};/*""",1*/
//	uc8 A10q35[]={0x00};/*"#",2*/
//	uc8 A10q36[]={3,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"$",3*/
	uc8 A10q37[]={8,0x00,0x00,0xC2,0xC4,0x08,0x10,0x20,0x46,0x86,0x00};/*"%",4*/
//	uc8 A10q38[]={2,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"&",5*/
//	uc8 A10q39[]={0x00};/*"'",6*/
//	uc8 A10q40[]={3,0x40,0x80,0x80,0x80,0x80,0x80,0x40};/*"(",7*/
//	uc8 A10q41[]={3,0x80,0x40,0x40,0x40,0x40,0x40,0x80};/*")",8*/
//	uc8 A10q42[]={0x00};/*"*",9*/
//	uc8 A10q43[]={0x00};/*"+",10*/
//	uc8 A10q44[]={0x00};/*",",11*/
//	uc8 A10q45[]={0x00};/*"-",12*/
//	uc8 A10q46[]={3,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0};/*".",13*/
//	uc8 A10q47[]={6,0x10,0x10,0x20,0x20,0x40,0x40,0x80};/*"/",14*/
	uc8 A10q48[]={6,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00};/*"0",0*/
	uc8 A10q49[]={6,0x10,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00};/*"1",1*/
	uc8 A10q50[]={6,0x70,0x88,0x88,0x08,0x10,0x20,0x40,0x80,0xF8,0x00};/*"2",2*/
	uc8 A10q51[]={6,0x70,0x88,0x88,0x08,0x30,0x08,0x88,0x88,0x70,0x00};/*"3",3*/
	uc8 A10q52[]={6,0x10,0x30,0x30,0x50,0x90,0x90,0xF8,0x10,0x10,0x00};/*"4",4*/
	uc8 A10q53[]={6,0xF8,0x80,0x80,0xF0,0x08,0x08,0x88,0x88,0x70,0x00};/*"5",5*/
	uc8 A10q54[]={6,0x70,0x88,0x80,0x80,0xF0,0x88,0x88,0x88,0x70,0x00};/*"6",6*/
	uc8 A10q55[]={6,0xF8,0x88,0x08,0x10,0x10,0x10,0x20,0x20,0x20,0x00};/*"7",7*/
	uc8 A10q56[]={6,0x70,0x88,0x88,0x88,0x70,0x88,0x88,0x88,0x70,0x00};/*"8",8*/
	uc8 A10q57[]={6,0x70,0x88,0x88,0x88,0x78,0x08,0x08,0x88,0x70,0x00};/*"9",9*/
//	uc8 A10q58[]={0x00};/*":",15*/
//	uc8 A10q59[]={0x00};/*";",16*/
//	uc8 A10q60[]={0x00};/*"<",17*/
//	uc8 A10q61[]={0x00};/*"=",18*/
//	uc8 A10q62[]={0x00};/*">",19*/
//	uc8 A10q63[]={0};/*"?",20*/
//	uc8 A10q64[]={0x00};/*"@",21*/
	uc8 A10q65[]={6,0x00,0x20,0x50,0x50,0x50,0x88,0xF8,0x88,0x88,0x00};/*"A",0*/
	uc8 A10q66[]={6,0x00,0xF0,0x88,0x88,0xF0,0x88,0x88,0x88,0xF0,0x00};/*"B",1*/
	uc8 A10q67[]={6,0x00,0x70,0x88,0x80,0x80,0x80,0x88,0x88,0x70,0x00};/*"C",2*/
	uc8 A10q68[]={6,0x00,0xE0,0x90,0x88,0x88,0x88,0x88,0x90,0xE0,0x00};/*"D",3*/
	uc8 A10q69[]={6,0x00,0xF8,0x80,0x80,0xF0,0x80,0x80,0x80,0xF8,0x00};/*"E",4*/
	uc8 A10q70[]={6,0x00,0xF8,0x80,0x80,0xF0,0x80,0x80,0x80,0x80,0x00};/*"F",5*/
	uc8 A10q71[]={6,0x00,0x70,0x88,0x80,0x80,0x98,0x88,0x98,0x68,0x00};/*"G",6*/
	uc8 A10q72[]={6,0x00,0x88,0x88,0x88,0xF8,0x88,0x88,0x88,0x88,0x00};/*"H",7*/
	uc8 A10q73[]={4,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0xE0,0x00};/*"I",8*/
	uc8 A10q74[]={5,0x00,0x10,0x10,0x10,0x10,0x10,0x90,0x90,0x60,0x00};/*"J",9*/
	uc8 A10q75[]={5,0x00,0x90,0xA0,0xA0,0xC0,0xA0,0xA0,0x90,0x90,0x00};/*"K",10*/
	uc8 A10q76[]={6,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xF8,0x00};/*"L",11*/
	uc8 A10q77[]={6,0x00,0x88,0xD8,0xD8,0xD8,0xA8,0xA8,0xA8,0xA8,0x00};/*"M",12*/
	uc8 A10q78[]={6,0x00,0x88,0xC8,0xC8,0xA8,0xA8,0x98,0x98,0x88,0x00};/*"N",13*/
	uc8 A10q79[]={6,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00};/*"O",14*/
	uc8 A10q80[]={6,0x00,0xF0,0x88,0x88,0x88,0xF0,0x80,0x80,0x80,0x00};/*"P",15*/
	uc8 A10q81[]={6,0x00,0x70,0x88,0x88,0x88,0x88,0xA8,0x90,0x68,0x00};/*"Q",16*/
	uc8 A10q82[]={6,0x00,0xF0,0x88,0x88,0x88,0xF0,0x88,0x88,0x88,0x00};/*"R",17*/
	uc8 A10q83[]={6,0x00,0x70,0x88,0x80,0x60,0x10,0x08,0x88,0x70,0x00};/*"S",0*/
	uc8 A10q84[]={6,0x00,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00};/*"T",19*/
	uc8 A10q85[]={6,0x00,0x88,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00};/*"U",20*/
	uc8 A10q86[]={6,0x00,0x88,0x88,0x88,0x50,0x50,0x50,0x20,0x20,0x00};/*"V",21*/
	uc8 A10q87[]={6,0x00,0xA8,0xA8,0xA8,0xA8,0xA8,0x50,0x50,0x50,0x00};/*"W",22*/
	uc8 A10q88[]={6,0x00,0x88,0x50,0x50,0x20,0x50,0x50,0x88,0x88,0x00};/*"X",23*/
	uc8 A10q89[]={6,0x00,0x88,0x88,0x50,0x50,0x20,0x20,0x20,0x20,0x00};/*"Y",24*/
	uc8 A10q90[]={6,0x00,0xF8,0x08,0x10,0x20,0x20,0x40,0x80,0xF8,0x00};/*"Z",25*/
	//uc8 A10q91[]={0x00};/*"[",22*/
	//uc8 A10q92[]={0x00};/*"\",23*/
	//uc8 A10q93[]={0x00};/*"]",24*/
	//uc8 A10q94[]={0x00};/*"^",25*/
	//uc8 A10q95[]={0x00};/*"_",26*/
	//uc8 A10q96[]={0x00};/*"`",27*/
	uc8 A10q97[]={6,0x00,0x00,0x00,0x60,0x90,0x70,0x90,0x90,0x68,0x00};/*"a",0*/
	uc8 A10q98[]={6,0x00,0x80,0x80,0x80,0xF0,0x88,0x88,0x88,0xF0,0x00};/*"b",1*/
	uc8 A10q99[]={6,0x00,0x00,0x00,0x70,0x88,0x80,0x80,0x88,0x70,0x00};/*"c",2*/
	uc8 A10q100[]={6,0x00,0x08,0x08,0x08,0x78,0x88,0x88,0x88,0x78,0x00};/*"d",3*/
	uc8 A10q101[]={6,0x00,0x00,0x00,0x70,0x88,0xF8,0x80,0x88,0x70,0x00};/*"e",4*/
	uc8 A10q102[]={5,0x00,0x30,0x40,0x40,0xF0,0x40,0x40,0x40,0x40,0x00};/*"f",5*/
	uc8 A10q103[]={6,0x00,0x00,0x00,0x68,0x90,0x60,0x80,0x70,0x88,0x70};/*"g",6*/
	uc8 A10q104[]={6,0x00,0x80,0x80,0x80,0xF0,0x88,0x88,0x88,0x88,0x00};/*"h",7*/
	uc8 A10q105[]={2,0x00,0x00,0x80,0x00,0x80,0x80,0x80,0x80,0x80,0x00};/*"i",8*/
	uc8 A10q106[]={3,0x00,0x00,0x40,0x00,0x40,0x40,0x40,0x40,0x40,0x80};/*"j",9*/
	uc8 A10q107[]={6,0x00,0x80,0x80,0x88,0xB0,0xC0,0xA0,0x90,0x88,0x00};/*"k",10*/
	uc8 A10q108[]={4,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0xA0,0x40,0x00};/*"l",11*/
	uc8 A10q109[]={6,0x00,0x00,0x00,0xD0,0xA8,0xA8,0xA8,0xA8,0xA8,0x00};/*"m",12*/
	uc8 A10q110[]={6,0x00,0x00,0x00,0xF0,0x88,0x88,0x88,0x88,0x88,0x00};/*"n",13*/
	uc8 A10q111[]={6,0x00,0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x70,0x00};/*"o",14*/
	uc8 A10q112[]={6,0x00,0x00,0x00,0xF0,0x88,0x88,0xF0,0x80,0x80,0x80};/*"p",15*/
	uc8 A10q113[]={6,0x00,0x00,0x00,0x78,0x88,0x88,0x78,0x08,0x08,0x08};/*"q",16*/
	uc8 A10q114[]={5,0x00,0x00,0x00,0xB0,0xC0,0x80,0x80,0x80,0x80,0x00};/*"r",17*/
	uc8 A10q115[]={6,0x00,0x00,0x00,0x70,0x88,0x60,0x10,0x88,0x70,0x00};/*"s",18*/
	uc8 A10q116[]={5,0x00,0x00,0x40,0x40,0xF0,0x40,0x40,0x50,0x20,0x00};/*"t",19*/
	uc8 A10q117[]={6,0x00,0x00,0x00,0x88,0x88,0x88,0x88,0x88,0x78,0x00};/*"u",20*/
	uc8 A10q118[]={6,0x00,0x00,0x00,0x88,0x88,0x50,0x50,0x20,0x20,0x00};/*"v",21*/
	uc8 A10q119[]={6,0x00,0x00,0x00,0xA8,0xA8,0xA8,0x50,0x50,0x50,0x00};/*"w",22*/
	uc8 A10q120[]={6,0x00,0x00,0x00,0x88,0x50,0x20,0x20,0x50,0x88,0x00};/*"x",23*/
	uc8 A10q121[]={6,0x00,0x00,0x00,0x88,0x88,0x50,0x50,0x20,0x20,0xC0};/*"y",24*/
	uc8 A10q122[]={6,0x00,0x00,0x00,0xF8,0x08,0x10,0x20,0x40,0xF8,0x00};/*"z",25*/
	//uc8 A10q123[]={0x00};/*"{",28*/
	//uc8 A10q124[]={0};/*"|",29*/
	//uc8 A10q125[]={0};/*"}",30*/
	//uc8 A10q126[]={0};/*"~",31*/

	uc8 *const	ASCII10[]={A10q32,Zero,Zero,Zero,Zero,A10q37,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,A10q48,A10q49,
		A10q50,A10q51,A10q52,A10q53,A10q54,A10q55,A10q56,A10q57,Zero,Zero,Zero,Zero,Zero,Zero,Zero,A10q65,A10q66,A10q67,A10q68,A10q69,
		A10q70,A10q71,A10q72,A10q73,A10q74,A10q75,A10q76,A10q77,A10q78,A10q79,A10q80,A10q81,A10q82,A10q83,A10q84,A10q85,A10q86,A10q87,A10q88,A10q89,
		A10q90,Zero,Zero,Zero,Zero,Zero,Zero,A10q97,A10q98,A10q99,A10q100,A10q101,A10q102,A10q103,A10q104,A10q105,A10q106,A10q107,A10q108,A10q109,
		A10q110,A10q111,A10q112,A10q113,A10q114,A10q115,A10q116,A10q117,A10q118,A10q119,A10q120,A10q121,A10q122/*,A10q123,A10q124,A10q125,A10q126*/};
#endif	
#ifdef	Font_12_ON
		//-------------- MS Gothic------------高12*宽?----------------------//
	uc8 Bq32[]={8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*" ",0*/
//	uc8 Bq33[]={0};/*"!",0*/
//	uc8 Bq34[]={0x00};/*""",1*/
//	uc8 Bq35[]={0x00};/*"#",2*/
//	uc8 Bq36[]={0x00};/*"$",3*/
//	uc8 Bq37[]={0x00};/*"%",4*/
//	uc8 Bq38[]={0x00};/*"&",5*/
//	uc8 Bq39[]={0x00};/*"'",6*/
//	uc8 Bq40[]={0x00};/*"(",7*/
//	uc8 Bq41[]={0x00};/*")",8*/
//	uc8 Bq42[]={0x00};/*"*",9*/
//	uc8 Bq43[]={0x00};/*"+",10*/
//	uc8 Bq44[]={0x00};/*",",11*/
//	uc8 Bq45[]={0x00};/*"-",12*/
//	uc8 Bq46[]={0x00};/*".",13*/
//	uc8 Bq47[]={0x00};/*"/",14*/
	uc8 Bq48[]={8,0x7C,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x7C,0x00};/*"0",0*/
	uc8 Bq49[]={8,0x08,0x18,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00};/*"1",1*/
	uc8 Bq50[]={8,0x38,0x44,0x82,0x02,0x02,0x04,0x08,0x10,0x20,0x40,0xFE,0x00};/*"2",2*/
	uc8 Bq51[]={8,0x7C,0x82,0x82,0x02,0x02,0x3C,0x02,0x02,0x82,0x82,0x7C,0x00};/*"3",3*/
	uc8 Bq52[]={8,0x04,0x0C,0x14,0x24,0x44,0x84,0x84,0x84,0xFE,0x04,0x04,0x00};/*"4",4*/
	uc8 Bq53[]={8,0xFE,0x80,0x80,0x80,0xFC,0x02,0x02,0x02,0x02,0x82,0x7C,0x00};/*"5",5*/
	uc8 Bq54[]={8,0x7C,0x82,0x80,0x80,0xBC,0xC2,0x82,0x82,0x82,0x82,0x7C,0x00};/*"6",6*/
	uc8 Bq55[]={8,0xFE,0x82,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x10,0x00};/*"7",7*/
	uc8 Bq56[]={8,0x7C,0x82,0x82,0x82,0x82,0x7C,0x82,0x82,0x82,0x82,0x7C,0x00};/*"8",8*/
	uc8 Bq57[]={8,0x7C,0x82,0x82,0x82,0x82,0x86,0x7A,0x02,0x02,0x82,0x7C,0x00};/*"9",9*/
	uc8 Bq58[]={3,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00};/*":",15*/
//	uc8 Bq59[]={0x00};/*";",16*/
//	uc8 Bq60[]={0x00};/*"<",17*/
//	uc8 Bq61[]={0x00};/*"=",18*/
//	uc8 Bq62[]={0x00};/*">",19*/
//	uc8 Bq63[]={0};/*"?",20*/
//	uc8 Bq64[]={0x00};/*"@",21*/
	uc8 Bq65[]={8,0x10,0x10,0x28,0x28,0x44,0x7C,0x82,0x82,0x82,0x82,0x82,0x00};/*"A",0*/
	uc8 Bq66[]={8,0xF8,0x84,0x82,0x82,0x84,0xF8,0x84,0x82,0x82,0x84,0xF8,0x00};/*"B",1*/
	uc8 Bq67[]={8,0x3C,0x42,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x42,0x3C,0x00};/*"C",2*/
	uc8 Bq68[]={8,0xF8,0x84,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x84,0xF8,0x00};/*"D",3*/
	uc8 Bq69[]={8,0xFE,0x80,0x80,0x80,0x80,0xFE,0x80,0x80,0x80,0x80,0xFE,0x00};/*"E",4*/
	uc8 Bq70[]={8,0xFE,0x80,0x80,0x80,0xFE,0x80,0x80,0x80,0x80,0x80,0x80,0x00};/*"F",5*/
	uc8 Bq71[]={9,0x3C,0x00,0x42,0x00,0x81,0x00,0x81,0x00,0x80,0x00,0x80,0x00,0x87,0x00,0x81,0x00,
0x81,0x00,0x43,0x00,0x3D,0x00,0x00,0x00};/*"G",6*/
	uc8 Bq72[]={8,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0x00};/*"H",7*/
	uc8 Bq73[]={6,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00};/*"I",8*/
	uc8 Bq74[]={7,0xFC,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x90,0x60,0x00};/*"J",9*/
	uc8 Bq75[]={8,0x82,0x84,0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88,0x84,0x82,0x00};/*"K",10*/
	uc8 Bq76[]={7,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFC,0x00};/*"L",11*/
	uc8 Bq77[]={8,0x82,0xC6,0xC6,0xC6,0xAA,0xAA,0xAA,0x92,0x92,0x92,0x92,0x00};/*"M",12*/
	uc8 Bq78[]={8,0x82,0x82,0xC2,0xC2,0xA2,0x92,0x8A,0x86,0x86,0x82,0x82,0x00};/*"N",13*/
	uc8 Bq79[]={8,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00};/*"O",14*/
	uc8 Bq80[]={8,0xF8,0x84,0x82,0x82,0x82,0x84,0xF8,0x80,0x80,0x80,0x80,0x00};/*"P",15*/
	uc8 Bq81[]={8,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x92,0x8A,0x44,0x3A,0x00};/*"Q",16*/
	uc8 Bq82[]={8,0xF8,0x84,0x82,0x82,0x84,0xF8,0x84,0x82,0x82,0x82,0x82,0x00};/*"R",17*/
	uc8 Bq83[]={8,0x78,0x84,0x80,0x80,0x40,0x30,0x08,0x04,0x04,0x84,0x78,0x00};/*"S",0*/
	uc8 Bq84[]={8,0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00};/*"T",19*/
	uc8 Bq85[]={8,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00};/*"U",20*/
	uc8 Bq86[]={10,0x80,0x80,0x80,0x80,0x80,0x80,0x41,0x00,0x41,0x00,0x22,0x00,0x22,0x00,0x14,0x00,
0x14,0x00,0x08,0x00,0x08,0x00,0x00,0x00};/*"V",21*/
	uc8 Bq87[]={8,0x92,0x92,0x92,0x92,0xAA,0xAA,0xAA,0x44,0x44,0x44,0x44,0x00};/*"W",22*/
	uc8 Bq88[]={8,0x82,0x82,0x44,0x44,0x28,0x10,0x28,0x44,0x44,0x82,0x82,0x00};/*"X",23*/
	uc8 Bq89[]={8,0x82,0x82,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x00};/*"Y",24*/
	uc8 Bq90[]={8,0xFE,0x02,0x04,0x04,0x08,0x10,0x20,0x40,0x40,0x80,0xFE,0x00};/*"Z",25*/
//	uc8 Bq91[]={0x00};/*"[",22*/
//	uc8 Bq92[]={0x00};/*"\",23*/
//	uc8 Bq93[]={0x00};/*"]",24*/
//	uc8 Bq94[]={0x00};/*"^",25*/
//	uc8 Bq95[]={0x00};/*"_",26*/
//	uc8 Bq96[]={0x00};/*"`",27*/
//	uc8 Bq97[]={0};/*"a",0*/
//	uc8 Bq98[]={0};/*"b",1*/
//	uc8 Bq99[]={0};/*"c",2*/
//	uc8 Bq100[]={0};/*"d",3*/
//	uc8 Bq101[]={0};/*"e",4*/
//	uc8 Bq102[]={0};/*"f",5*/
//	uc8 Bq103[]={0};/*"g",6*/
//	uc8 Bq104[]={0};/*"h",7*/
//	uc8 Bq105[]={0};/*"i",8*/
//	uc8 Bq106[]={0};/*"j",9*/
//	uc8 Bq107[]={0};/*"k",10*/
//	uc8 Bq108[]={0};/*"l",11*/
//	uc8 Bq109[]={0};/*"m",12*/
//	uc8 Bq110[]={0};/*"n",13*/
//	uc8 Bq111[]={0};/*"o",14*/
//	uc8 Bq112[]={0};/*"p",15*/
//	uc8 Bq113[]={0};/*"q",16*/
//	uc8 Bq114[]={0};/*"r",17*/
//	uc8 Bq115[]={0};/*"s",18*/
//	uc8 Bq116[]={0};/*"t",19*/
//	uc8 Bq117[]={0};/*"u",20*/
//	uc8 Bq118[]={0};/*"v",21*/
//	uc8 Bq119[]={0};/*"w",22*/
//	uc8 Bq120[]={0};/*"x",23*/
//	uc8 Bq121[]={0};/*"y",24*/
//	uc8 Bq122[]={0};/*"z",25*/
//	uc8 Bq123[]={0};/*"{",28*/
//	uc8 Bq124[]={0};/*"|",29*/
//	uc8 Bq125[]={0};/*"}",30*/
//	uc8 Bq126[]={0};/*"~",31*/
	
	uc8 *const ASCII12[]={Bq32,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Bq48,Bq49,
		Bq50,Bq51,Bq52,Bq53,Bq54,Bq55,Bq56,Bq57,Bq58,Zero,Zero,Zero,Zero,Zero,Zero,Bq65,Bq66,Bq67,Bq68,Bq69,
		Bq70,Bq71,Bq72,Bq73,Bq74,Bq75,Bq76,Bq77,Bq78,Bq79,Bq80,Bq81,Bq82,Bq83,Bq84,Bq85,Bq86,Bq87,Bq88,Bq89,
		Bq90/*,Bq91,Bq92,Bq93,Bq94,Bq95,Bq96,Bq97,Bq98,Bq99,Bq100,Bq101,Bq102,Bq103,Bq104,Bq105,Bq106,Bq107,Bq108,Bq109,
		Bq110,Bq111,Bq112,Bq113,Bq114,Bq115,Bq116,Bq117,Bq118,Bq119,Bq120,Bq121,Bq122,Bq123,Bq124,Bq125,Bq126*/};
#endif

#ifdef	Font_19_ON
		//--------------------------高19*宽?----------------------//
	uc8 A19q32[]={12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00};/*" ",0*/
//	uc8 A19q33[]={0};/*"!",0*/
//	uc8 A19q34[]={0x00};/*""",1*/
//	uc8 A19q35[]={0x00};/*"#",2*/
//	uc8 A19q36[]={3,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"$",3*/
//	uc8 A19q37[]={6,0x90,0x20,0x20,0x40,0x40,0x80,0x90};/*"%",4*/
//	uc8 A19q38[]={2,0x00,0x00,0x00,0x00,0x00,0x00,0x00};/*"&",5*/
//	uc8 A19q39[]={0x00};/*"'",6*/
//	uc8 A19q40[]={3,0x40,0x80,0x80,0x80,0x80,0x80,0x40};/*"(",7*/
//	uc8 A19q41[]={3,0x80,0x40,0x40,0x40,0x40,0x40,0x80};/*")",8*/
//	uc8 A19q42[]={0x00};/*"*",9*/
//	uc8 A19q43[]={0x00};/*"+",10*/
//	uc8 A19q44[]={0x00};/*",",11*/
//	uc8 A19q45[]={0x00};/*"-",12*/
//	uc8 A19q46[]={2,0x00,0x00,0x00,0x00,0x00,0x00,0x80};/*".",13*/
//	uc8 A19q47[]={6,0x10,0x10,0x20,0x20,0x40,0x40,0x80};/*"/",14*/
	uc8 A19q48[]={12,0x3F,0x80,0x7F,0xC0,0xFF,0xE0,0xF1,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,
0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF1,0xE0,
0xFF,0xE0,0x7F,0xC0,0x3F,0x80};/*"0",0*/
	uc8 A19q49[]={12,0x01,0x00,0x03,0x00,0x07,0x00,0x0F,0x00,0x1F,0x00,0x07,0x00,0x07,0x00,0x07,0x00,
0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,0x07,0x00,
0x07,0x00,0x07,0x00,0x07,0x00};/*"1",1*/
	uc8 A19q50[]={12,0x3F,0x80,0x7F,0xC0,0xFF,0xE0,0xF1,0xE0,0xE0,0xE0,0x00,0xE0,0x00,0xE0,0x01,0xE0,
0x03,0xC0,0x07,0x80,0x0F,0x00,0x1E,0x00,0x3C,0x00,0x78,0x00,0xF0,0x00,0xE0,0x00,
0xFF,0xE0,0xFF,0xE0,0xFF,0xE0};/*"2",2*/
	uc8 A19q51[]={12,0x3F,0x80,0x7F,0xC0,0xFF,0xE0,0xF1,0xE0,0xE0,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,
0x01,0xC0,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0xE0,0xE0,0xF1,0xE0,
0xFF,0xE0,0x7F,0xC0,0x3F,0x80};/*"3",3*/
	uc8 A19q52[]={12,0x00,0x80,0x01,0x80,0x03,0x80,0x07,0x80,0x0F,0x80,0x1F,0x80,0x3F,0x80,0x7B,0x80,
0xF3,0x80,0xE3,0x80,0xE3,0x80,0xE3,0x80,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0x03,0x80,
0x03,0x80,0x03,0x80,0x03,0x80};/*"4",4*/
	uc8 A19q53[]={12,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xFF,0x80,
0xFF,0xC0,0xFF,0xE0,0x01,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0xE1,0xE0,
0xFF,0xE0,0xFF,0xC0,0x7F,0x80};/*"5",5*/
	uc8 A19q54[]={12,0x3F,0x80,0x7F,0xC0,0xFF,0xE0,0xF1,0xE0,0xE0,0xE0,0xE0,0x00,0xE0,0x00,0xE0,0x00,
0xFF,0x80,0xFF,0xC0,0xFF,0xE0,0xF1,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF1,0xE0,
0xFF,0xE0,0x7F,0xC0,0x3F,0x80};/*"6",6*/
	uc8 A19q55[]={12,0xFF,0xE0,0xFF,0xE0,0xFF,0xE0,0x00,0xE0,0x00,0xE0,0x01,0xC0,0x01,0xC0,0x01,0xC0,
0x01,0xC0,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x03,0x80,0x07,0x00,0x07,0x00,
0x07,0x00,0x07,0x00,0x07,0x00};/*"7",7*/
	uc8 A19q56[]={12,0x3F,0x80,0x7F,0xC0,0xFF,0xE0,0xF1,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF1,0xE0,
0x7F,0xC0,0x3F,0x80,0x7F,0xC0,0xF1,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF1,0xE0,
0xFF,0xE0,0x7F,0xC0,0x3F,0x80};/*"8",8*/
	uc8 A19q57[]={12,0x3F,0x80,0x7F,0xC0,0xFF,0xE0,0xF1,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF1,0xE0,
0xFF,0xE0,0x7F,0xE0,0x3F,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0x00,0xE0,0xE1,0xE0,
0xFF,0xE0,0xFF,0xC0,0x7F,0x80};/*"9",9*/
//	uc8 A19q58[]={0x00};/*":",15*/
//	uc8 A19q59[]={0x00};/*";",16*/
//	uc8 A19q60[]={0x00};/*"<",17*/
//	uc8 A19q61[]={0x00};/*"=",18*/
//	uc8 A19q62[]={0x00};/*">",19*/
//	uc8 A19q63[]={0};/*"?",20*/
//	uc8 A19q64[]={0x00};/*"@",21*/
//	uc8 A19q65[]={6,0x70,0x88,0x88,0xF8,0x88,0x88,0x88};/*"A",0*/
//	uc8 A19q66[]={6,0xF0,0x88,0x88,0xF0,0x88,0x88,0xF0};/*"B",1*/
//	uc8 A19q67[]={6,0x70,0x88,0x80,0x80,0x80,0x88,0x70};/*"C",2*/
//	uc8 A19q68[]={6,0xF0,0x88,0x88,0x88,0x88,0x88,0xF0};/*"D",3*/
//	uc8 A19q69[]={6,0xF8,0x80,0x80,0xF0,0x80,0x80,0xF8};/*"E",4*/
//	uc8 A19q70[]={6,0xF8,0x80,0x80,0xF0,0x80,0x80,0x80};/*"F",5*/
//	uc8 A19q71[]={6,0x70,0x88,0x80,0x80,0xB8,0x88,0x70};/*"G",6*/
//	uc8 A19q72[]={6,0x88,0x88,0x88,0xF8,0x88,0x88,0x88};/*"H",7*/
//	uc8 A19q73[]={4,0x40,0x40,0x40,0x40,0x40,0x40,0x40};/*"I",8*/
//	uc8 A19q74[]={5,0x20,0x20,0x20,0x20,0x20,0x20,0xC0};/*"J",9*/
//	uc8 A19q75[]={6,0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88};/*"K",10*/
//	uc8 A19q76[]={5,0x80,0x80,0x80,0x80,0x80,0x80,0xF0};/*"L",11*/
//	uc8 A19q77[]={6,0x88,0xD8,0xF8,0xA8,0x88,0x88,0x88};/*"M",12*/
//	uc8 A19q78[]={6,0x88,0xC8,0xE8,0xA8,0xB8,0x98,0x88};/*"N",13*/
//	uc8 A19q79[]={6,0x70,0x88,0x88,0x88,0x88,0x88,0x70};/*"O",14*/
//	uc8 A19q80[]={6,0xF0,0x88,0x88,0x88,0xF0,0x80,0x80};/*"P",15*/
//	uc8 A19q81[]={6,0x70,0x88,0x88,0x88,0xA8,0x90,0x68};/*"Q",16*/
//	uc8 A19q82[]={6,0xF0,0x88,0x88,0xF0,0xA0,0x90,0x88};/*"R",17*/
//	uc8 A19q83[]={6,0x70,0x88,0x80,0x70,0x08,0x88,0x70};/*"S",0*/
//	uc8 A19q84[]={6,0xF8,0x20,0x20,0x20,0x20,0x20,0x20};/*"T",19*/
//	uc8 A19q85[]={6,0x88,0x88,0x88,0x88,0x88,0x88,0x70};/*"U",20*/
//	uc8 A19q86[]={6,0x88,0x88,0x88,0xD8,0x50,0x70,0x20};/*"V",21*/
//	uc8 A19q87[]={6,0x88,0xA8,0xA8,0xA8,0xF8,0x50,0x50};/*"W",22*/
//	uc8 A19q88[]={6,0x88,0x88,0x50,0x20,0x50,0x88,0x88};/*"X",23*/
//	uc8 A19q89[]={6,0x88,0x88,0x50,0x50,0x20,0x20,0x20};/*"Y",24*/
//	uc8 A19q90[]={6,0xF8,0x08,0x10,0x20,0x40,0x80,0xF8};/*"Z",25*/
	//uc8 A19q91[]={0x00};/*"[",22*/
	//uc8 A19q92[]={0x00};/*"\",23*/
	//uc8 A19q93[]={0x00};/*"]",24*/
	//uc8 A19q94[]={0x00};/*"^",25*/
	//uc8 A19q95[]={0x00};/*"_",26*/
	//uc8 A19q96[]={0x00};/*"`",27*/
	//uc8 A19q97[]={0x00};/*"a",0*/
	//uc8 A19q98[]={0x00};/*"b",1*/
	//uc8 A19q99[]={0x00};/*"c",2*/
	//uc8 A19q100[]={0x00};/*"d",3*/
	//uc8 A19q101[]={0x00};/*"e",4*/
	//uc8 A19q102[]={0x00};/*"f",5*/
	//uc8 A19q103[]={0x00};/*"g",6*/
	//uc8 A19q104[]={0x00};/*"h",7*/
	//uc8 A19q105[]={0x00};/*"i",8*/
	//uc8 A19q106[]={0x00};/*"j",9*/
	//uc8 A19q107[]={0x00};/*"k",10*/
	//uc8 A19q108[]={0x00};/*"l",11*/
	//uc8 A19q109[]={0x00};/*"m",12*/
	//uc8 A19q110[]={0x00};/*"n",13*/
	//uc8 A19q111[]={0x00};/*"o",14*/
	//uc8 A19q112[]={0x00};/*"p",15*/
	//uc8 A19q113[]={0x00};/*"q",16*/
	//uc8 A19q114[]={0x00};/*"r",17*/
	//uc8 A19q115[]={0x00};/*"s",18*/
	//uc8 A19q116[]={0x00};/*"t",19*/
	//uc8 A19q117[]={0x00};/*"u",20*/
	//uc8 A19q118[]={0x00};/*"v",21*/
	//uc8 A19q119[]={0x00};/*"w",22*/
	//uc8 A19q120[]={0x00};/*"x",23*/
	//uc8 A19q121[]={0x00};/*"y",24*/
	//uc8 A19q122[]={0x00};/*"z",25*/
	//uc8 A19q123[]={0x00};/*"{",28*/
	//uc8 A19q124[]={0};/*"|",29*/
	//uc8 A19q125[]={0};/*"}",30*/
	//uc8 A19q126[]={0};/*"~",31*/

	uc8 *const	ASCII19[]={A19q32,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,Zero,A19q48,A19q49,
		A19q50,A19q51,A19q52,A19q53,A19q54,A19q55,A19q56,A19q57/*,Zero,Zero,Zero,Zero,Zero,Zero,Zero,A19q65,A19q66,A19q67,A19q68,A19q69,
		A19q70,A19q71,A19q72,A19q73,A19q74,A19q75,A19q76,A19q77,A19q78,A19q79,A19q80,A19q81,A19q82,A19q83,A19q84,A19q85,A19q86,A19q87,A19q88,A19q89,
		A19q90,A19q91,A19q92,A19q93,A19q94,A19q95,A19q96,A19q97,A19q98,A19q99,A19q100,A19q101,A19q102,A19q103,A19q104,A19q105,A19q106,A19q107,A19q108,A19q109,
		A19q110,A19q111,A19q112,A19q113,A19q114,A19q115,A19q116,A19q117,A19q118,A19q119,A19q120,A19q121,A19q122,A19q123,A19q124,A19q125,A19q126*/};
#endif
		
#ifdef	Zhong_16_ON
/////////中文字库
zhong_un	ZH_0={
	.chars="雾",
};
uc8 Z15q0[]={16,0x3F,0xF8,0x01,0x00,0x7F,0xFE,0x41,0x02,0x9D,0x74,0x01,0x00,0x1D,0x70,0x04,0x00,
0x0F,0xE0,0x14,0x40,0x03,0x80,0x1C,0x70,0xE2,0x0E,0x0F,0xE0,0x04,0x20,0x18,0x60};//按//
Chinese_typ	Chinese0={
	.zhong=&ZH_0,
	.data=Z15q0
};
//////
zhong_un	ZH_1={
	.chars="化",
};
uc8 Z15q1[]={16,0x08,0x80,0x08,0x80,0x08,0x84,0x10,0x88,0x10,0x90,0x30,0xA0,0x30,0xC0,0x50,0x80,
0x91,0x80,0x12,0x80,0x14,0x80,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x7E,0x10,0x00};
Chinese_typ	Chinese1={
	.zhong=&ZH_1,
	.data=Z15q1
};
//////
zhong_un	ZH_2={
	.chars="器",
};
uc8 Z15q2[]={16,0x00,0x00,0x3E,0x7C,0x22,0x44,0x22,0x44,0x3E,0x7C,0x01,0x20,0x01,0x10,0xFF,0xFE,
0x02,0x80,0x0C,0x60,0x30,0x18,0xC0,0x06,0x3E,0x7C,0x22,0x44,0x22,0x44,0x3E,0x7C};
Chinese_typ	Chinese2={
	.zhong=&ZH_2,
	.data=Z15q2
};
//////
zhong_un	ZH_3={
	.chars="开",
};
uc8 Z15q3[]={16,0x00,0x00,0x7F,0xFC,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0xFF,0xFE,
0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x10,0x20,0x10,0x20,0x20,0x20,0x40,0x20};
Chinese_typ	Chinese3={
	.zhong=&ZH_3,
	.data=Z15q3
};
//////
zhong_un	ZH_4={
	.chars="低",
};
uc8 Z15q4[]={16,0x08,0x08,0x08,0x3C,0x0B,0xE0,0x12,0x20,0x12,0x20,0x32,0x20,0x32,0x20,0x53,0xFE,
0x92,0x20,0x12,0x10,0x12,0x10,0x12,0x12,0x12,0x0A,0x12,0x8A,0x13,0x26,0x12,0x12};
Chinese_typ	Chinese4={
	.zhong=&ZH_4,
	.data=Z15q4
};
//////
zhong_un	ZH_5={
	.chars="阻",
};
uc8 Z15q5[]={16,0x00,0x00,0x7D,0xF8,0x45,0x08,0x49,0x08,0x49,0x08,0x51,0xF8,0x49,0x08,0x49,0x08,
0x45,0x08,0x45,0xF8,0x45,0x08,0x69,0x08,0x51,0x08,0x41,0x08,0x47,0xFE,0x40,0x00};
Chinese_typ	Chinese5={
	.zhong=&ZH_5,
	.data=Z15q5
};
//////
zhong_un	ZH_6={
	.chars="值",
};
uc8 Z15q6[]={16,0x08,0x40,0x08,0x40,0x0F,0xFC,0x10,0x40,0x10,0x40,0x33,0xF8,0x32,0x08,0x53,0xF8,
0x92,0x08,0x13,0xF8,0x12,0x08,0x13,0xF8,0x12,0x08,0x12,0x08,0x1F,0xFE,0x10,0x00};
Chinese_typ	Chinese6={
	.zhong=&ZH_6,
	.data=Z15q6
};
//////
zhong_un	ZH_7={
	.chars="过",
};
uc8 Z15q7[]={16,0x00,0x10,0x20,0x10,0x10,0x10,0x17,0xFE,0x00,0x10,0x00,0x10,0xF2,0x10,0x11,0x10,
0x11,0x10,0x10,0x10,0x10,0x10,0x10,0x50,0x10,0x20,0x28,0x00,0x47,0xFE,0x00,0x00};
Chinese_typ	Chinese7={
	.zhong=&ZH_7,
	.data=Z15q7
};
//////
zhong_un	ZH_8={
	.chars="热",
};
uc8 Z15q8[]={16,0x10,0x40,0x10,0x40,0x10,0x40,0xFD,0xF8,0x10,0x48,0x10,0x48,0x1C,0xC8,0x30,0x48,
0xD0,0xAA,0x10,0xAA,0x51,0x06,0x22,0x02,0x00,0x00,0x48,0x88,0x44,0x44,0x84,0x44};
Chinese_typ	Chinese8={
	.zhong=&ZH_8,
	.data=Z15q8
};
//////
zhong_un	ZH_9={
	.chars="检",
};
uc8 Z15q9[]={16,0x10,0x40,0x10,0x40,0x10,0xA0,0x10,0xA0,0xFD,0x10,0x12,0x08,0x35,0xF6,0x38,0x00,
0x54,0x88,0x50,0x48,0x92,0x48,0x11,0x50,0x11,0x10,0x10,0x20,0x17,0xFE,0x10,0x00};
Chinese_typ	Chinese9={
	.zhong=&ZH_9,
	.data=Z15q9
};
//////
zhong_un	ZH_10={
	.chars="查",
};
uc8 Z15q10[]={16,0x01,0x00,0x01,0x00,0x7F,0xFC,0x05,0x40,0x09,0x20,0x31,0x18,0xC1,0x06,0x1F,0xF0,
0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x00,0x00,0xFF,0xFE,0x00,0x00};
Chinese_typ	Chinese10={
	.zhong=&ZH_10,
	.data=Z15q10
};
//////
zhong_un	ZH_11={
	.chars="充",
};
uc8 Z15q11[]={16,0x02,0x00,0x01,0x00,0xFF,0xFE,0x04,0x00,0x04,0x00,0x08,0x20,0x10,0x10,0x3F,0xF8,
0x04,0x48,0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x44,0x08,0x44,0x10,0x44,0x60,0x3C};
Chinese_typ	Chinese11={
	.zhong=&ZH_11,
	.data=Z15q11
};
//////
zhong_un	ZH_12={
	.chars="电",
};
uc8 Z15q12[]={16,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,
0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x0A,0x01,0x02,0x01,0x02,0x00,0xFE};
Chinese_typ	Chinese12={
	.zhong=&ZH_12,
	.data=Z15q12
};
//////
zhong_un	ZH_13={
	.chars="量",
};
uc8 Z15q13[]={16,0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0xFF,0xFE,0x00,0x00,0x1F,0xF0,
0x11,0x10,0x1F,0xF0,0x11,0x10,0x1F,0xF0,0x01,0x00,0x1F,0xF0,0x01,0x00,0x7F,0xFC};
Chinese_typ	Chinese13={
	.zhong=&ZH_13,
	.data=Z15q13
};
//////
zhong_un	ZH_14={
	.chars="新",
};
uc8 Z15q14[]={16,0x10,0x00,0x08,0x04,0x7F,0x78,0x00,0x40,0x22,0x40,0x14,0x40,0xFF,0x7E,0x08,0x48,
0x08,0x48,0x7F,0x48,0x08,0x48,0x2A,0x48,0x49,0x48,0x88,0x88,0x28,0x88,0x11,0x08};
Chinese_typ	Chinese14={
	.zhong=&ZH_14,
	.data=Z15q14
};
//////
zhong_un	ZH_15={
	.chars="吸",
};
uc8 Z15q15[]={16,0x00,0x00,0x07,0xF8,0x79,0x08,0x49,0x10,0x49,0x10,0x49,0x20,0x49,0x3C,0x49,0x04,
0x49,0x04,0x4A,0x88,0x7A,0x88,0x4A,0x50,0x04,0x20,0x04,0x50,0x08,0x88,0x03,0x06};
Chinese_typ	Chinese15={
	.zhong=&ZH_15,
	.data=Z15q15
};
//////
zhong_un	ZH_16={
	.chars="烟",
};
uc8 Z15q16[]={16,0x10,0x00,0x13,0xFE,0x12,0x02,0x16,0x22,0x5A,0x22,0x52,0x22,0x53,0xFE,0x92,0x22,
0x12,0x22,0x12,0x52,0x12,0x4A,0x2A,0x8A,0x27,0x02,0x42,0x02,0x43,0xFE,0x82,0x02};
Chinese_typ	Chinese16={
	.zhong=&ZH_16,
	.data=Z15q16
};
//////
zhong_un	ZH_17={
	.chars="超",
};
uc8 Z15q17[]={16,0x08,0x00,0x09,0xFC,0x08,0x44,0x7E,0x44,0x08,0x44,0x08,0x94,0xFF,0x08,0x08,0xFC,
0x28,0x84,0x28,0x84,0x2E,0x84,0x28,0xFC,0x28,0x00,0x58,0x00,0x4F,0xFE,0x80,0x00};
Chinese_typ	Chinese17={
	.zhong=&ZH_17,
	.data=Z15q17
};
//////
zhong_un	ZH_18={
	.chars="时",
};
uc8 Z15q18[]={16,0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08,
0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10};
Chinese_typ	Chinese18={
	.zhong=&ZH_18,
	.data=Z15q18
};
//////
zhong_un	ZH_19={
	.chars="系",
};
uc8 Z15q19[]={16,0x00,0xF8,0x3F,0x00,0x04,0x00,0x08,0x20,0x10,0x40,0x3F,0x80,0x01,0x00,0x06,0x10,
0x18,0x08,0x7F,0xFC,0x01,0x04,0x09,0x20,0x11,0x10,0x21,0x08,0x45,0x04,0x02,0x00};
Chinese_typ	Chinese19={
	.zhong=&ZH_19,
	.data=Z15q19
};
//////
zhong_un	ZH_20={
	.chars="统",
};
uc8 Z15q20[]={16,0x10,0x40,0x10,0x20,0x20,0x20,0x23,0xFE,0x48,0x40,0xF8,0x88,0x11,0x04,0x23,0xFE,
0x40,0x92,0xF8,0x90,0x40,0x90,0x00,0x90,0x19,0x12,0xE1,0x12,0x42,0x0E,0x04,0x00};
Chinese_typ	Chinese20={
	.zhong=&ZH_20,
	.data=Z15q20
};
//////
zhong_un	ZH_21={
	.chars="关",
};
uc8 Z15q21[]={16,0x10,0x10,0x08,0x10,0x08,0x20,0x00,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,
0xFF,0xFE,0x01,0x00,0x02,0x80,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x06};
Chinese_typ	Chinese21={
	.zhong=&ZH_21,
	.data=Z15q21
};
//////
zhong_un	ZH_22={
	.chars="机",
};
uc8 Z15q22[]={16,0x10,0x00,0x11,0xF0,0x11,0x10,0x11,0x10,0xFD,0x10,0x11,0x10,0x31,0x10,0x39,0x10,
0x55,0x10,0x55,0x10,0x91,0x10,0x11,0x12,0x11,0x12,0x12,0x12,0x12,0x0E,0x14,0x00};
Chinese_typ	Chinese22={
	.zhong=&ZH_22,
	.data=Z15q22
};
//////
zhong_un	ZH_23={
	.chars="星",
};
uc8 Z15q23[]={16,0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x01,0x00,0x11,0x00,
0x1F,0xF8,0x21,0x00,0x41,0x00,0x1F,0xF0,0x01,0x00,0x01,0x00,0x7F,0xFC,0x00,0x00};
Chinese_typ	Chinese23={
	.zhong=&ZH_23,
	.data=Z15q23
};
//////
zhong_un	ZH_24={
	.chars="期",
};
uc8 Z15q24[]={16,0x22,0x00,0x22,0x7C,0x7F,0x44,0x22,0x44,0x22,0x44,0x3E,0x7C,0x22,0x44,0x22,0x44,
0x3E,0x44,0x22,0x7C,0x22,0x44,0xFF,0x44,0x04,0x84,0x22,0x84,0x41,0x14,0x82,0x08};
Chinese_typ	Chinese24={
	.zhong=&ZH_24,
	.data=Z15q24
};
//////
zhong_un	ZH_25={
	.chars="一",
};
uc8 Z15q25[]={16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
Chinese_typ	Chinese25={
	.zhong=&ZH_25,
	.data=Z15q25
};
//////
zhong_un	ZH_26={
	.chars="二",
};
uc8 Z15q26[]={16,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00};
Chinese_typ	Chinese26={
	.zhong=&ZH_26,
	.data=Z15q26
};
//////
zhong_un	ZH_27={
	.chars="三",
};
uc8 Z15q27[]={16,0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00};
Chinese_typ	Chinese27={
	.zhong=&ZH_27,
	.data=Z15q27
};
//////
zhong_un	ZH_28={
	.chars="四",
};
uc8 Z15q28[]={16,0x00,0x00,0x00,0x00,0x7F,0xFC,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,
0x48,0x44,0x48,0x3C,0x50,0x04,0x60,0x04,0x40,0x04,0x7F,0xFC,0x40,0x04,0x00,0x00};
Chinese_typ	Chinese28={
	.zhong=&ZH_28,
	.data=Z15q28
};
//////
zhong_un	ZH_29={
	.chars="五",
};
uc8 Z15q29[]={16,0x00,0x00,0x7F,0xFC,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x00,0x3F,0xF0,0x04,0x10,
0x04,0x10,0x04,0x10,0x04,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0xFF,0xFE,0x00,0x00};
Chinese_typ	Chinese29={
	.zhong=&ZH_29,
	.data=Z15q29
};
//////
zhong_un	ZH_30={
	.chars="六",
};
uc8 Z15q30[]={16,0x02,0x00,0x01,0x00,0x00,0x80,0x00,0x80,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,
0x04,0x40,0x04,0x20,0x08,0x10,0x08,0x08,0x10,0x08,0x20,0x04,0x40,0x04,0x00,0x00};
Chinese_typ	Chinese30={
	.zhong=&ZH_30,
	.data=Z15q30
};
//////
zhong_un	ZH_31={
	.chars="日",
};
uc8 Z15q31[]={16,0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10};
Chinese_typ	Chinese31={
	.zhong=&ZH_31,
	.data=Z15q31
};
//////
zhong_un	ZH_32={
	.chars="中",
};
uc8 Z15q32[]={16,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,
0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00};
Chinese_typ	Chinese32={
	.zhong=&ZH_32,
	.data=Z15q32
};
//////
zhong_un	ZH_33={
	.chars="文",
};
uc8 Z15q33[]={16,0x02,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x10,0x10,0x10,0x10,0x08,0x20,0x08,0x20,
0x04,0x40,0x02,0x80,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x06};
Chinese_typ	Chinese33={
	.zhong=&ZH_33,
	.data=Z15q33
};
///
zhong_un	ZH_34={
	.chars="路",
};
uc8 Z15q34[]={16,0x00,0x40,0x7C,0x40,0x44,0x78,0x44,0x88,0x45,0x50,0x7C,0x20,0x10,0x50,0x10,0x88,
0x11,0x06,0x5C,0xF8,0x50,0x88,0x50,0x88,0x50,0x88,0x5C,0x88,0xE0,0xF8,0x00,0x88};
Chinese_typ	Chinese34={
	.zhong=&ZH_34,
	.data=Z15q34
};
///
zhong_un	ZH_35={
	.chars="锁",
};
uc8 Z15q35[]={16,0x10,0x20,0x11,0x24,0x3C,0xA4,0x20,0xA8,0x40,0x20,0xBD,0xFC,0x11,0x04,0x11,0x24,
0xFD,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x14,0x50,0x18,0x88,0x11,0x04,0x02,0x02};
Chinese_typ	Chinese35={
	.zhong=&ZH_35,
	.data=Z15q35
};
///
zhong_un	ZH_36={
	.chars="定",
};
uc8 Z15q36[]={16,0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x80,0x04,0x00,0x00,0x3F,0xF8,0x01,0x00,
0x01,0x00,0x11,0x00,0x11,0xF8,0x11,0x00,0x11,0x00,0x29,0x00,0x47,0xFE,0x80,0x00};
Chinese_typ	Chinese36={
	.zhong=&ZH_36,
	.data=Z15q36
};
///
zhong_un	ZH_37={
	.chars="吾", //5
};
uc8 Z15q37[]={8,0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x58,0x64,0x02,0x02,0x42,0x44,0x38,0x00,0x00};
Chinese_typ	Chinese37={
	.zhong=&ZH_37,
	.data=Z15q37
};
///
zhong_un	ZH_38={
	.chars="次",
};
uc8 Z15q38[]={16,0x00,0x80,0x40,0x80,0x20,0x80,0x20,0xFC,0x01,0x04,0x09,0x08,0x0A,0x40,0x14,0x40,
0x10,0x40,0xE0,0xA0,0x20,0xA0,0x21,0x10,0x21,0x10,0x22,0x08,0x24,0x04,0x08,0x02};
Chinese_typ	Chinese38={
	.zhong=&ZH_38,
	.data=Z15q38
};
///
zhong_un	ZH_39={
	.chars="解",
};
uc8 Z15q39[]={16,0x10,0x00,0x10,0xFC,0x3C,0x24,0x24,0x24,0x48,0x54,0xBE,0x88,0x2A,0x10,0x2A,0x50,
0x3E,0x7C,0x2A,0x90,0x2A,0x10,0x3E,0xFE,0x2A,0x10,0x4A,0x10,0x42,0x10,0x86,0x10};
Chinese_typ	Chinese39={
	.zhong=&ZH_39,
	.data=Z15q39
};
Chinese_typ *const ZHONG16[]={&Chinese0,&Chinese1,&Chinese2,&Chinese3,&Chinese4,&Chinese5,&Chinese6,&Chinese7,&Chinese8,&Chinese9
,&Chinese10,&Chinese11,&Chinese12,&Chinese13,&Chinese14,&Chinese15,&Chinese16,&Chinese17,&Chinese18,&Chinese19
,&Chinese20,&Chinese21,&Chinese22,&Chinese23,&Chinese24,&Chinese25,&Chinese26,&Chinese27,&Chinese28,&Chinese29
,&Chinese30,&Chinese31,&Chinese32,&Chinese33,&Chinese34,&Chinese35,&Chinese36,&Chinese37,&Chinese38,&Chinese39};


#endif
									
									
									





									
		
		
		








