#include "GUI.h"
//#include "GUI_image_FLASH.h"
//#include "Flahs_Driver.h"
//#include "GUI_XBF_Font.h"
//#include "Flahs_Data.h"


//GUI_FONT            FontYaHei22;
//GUI_FONT            FontYaHei24;
//GUI_FONT            FontYaHei28;
//GUI_FONT            FontYaHei31;
//
//GUI_XBF_DATA        XBF_DataYaHei22;
//GUI_XBF_DATA        XBF_DataYaHei24;
//GUI_XBF_DATA        XBF_DataYaHei28;
//GUI_XBF_DATA        XBF_DataYaHei31;

/*****************************************************************************************
**�������ƣ�_cbGetData
** �����������ص�����
** ���������uiOff���ļ�ƫ�Ƶ�ַ usNumBytes����ȡ�ֽ��� pFil���ļ�ָ�� pBuffer�������ַ
** ����ֵ  ��0���ɹ� 1��ʧ��
*******************************************************************************************/
//static int _cbGetData(U32 uiOff, U16 usNumBytes, void * para, void * pBuffer)
//{
//	SPI_Flash_Read_BuffData8((u32)para+uiOff,pBuffer,usNumBytes);
//	SPI_Flash_Read_BuffData_OK();
//  return 0;
//}

/* ��ʼ���ֿ� */
void initCharacterLib(void)
{
	GUI_UC_SetEncodeUTF8();
//
//	GUI_XBF_CreateFont(&FontYaHei22,
//                    &XBF_DataYaHei22,
//                    GUI_XBF_TYPE_PROP_AA2_EXT,
//                    _cbGetData,
//                    (void*)Microsoft22YaHei4_5);
//	GUI_XBF_CreateFont(&FontYaHei24,
//                    &XBF_DataYaHei24,
//                    GUI_XBF_TYPE_PROP_AA2_EXT,
//                    _cbGetData,
//                    (void*)Microsoft24YaHei5_4);
//	GUI_XBF_CreateFont(&FontYaHei28,
//                    &XBF_DataYaHei28,
//                    GUI_XBF_TYPE_PROP_AA2_EXT,
//                    _cbGetData,
//                    (void*)Microsoft28YaHei6_4);
//	GUI_XBF_CreateFont(&FontYaHei31,
//                    &XBF_DataYaHei31,
//                    GUI_XBF_TYPE_PROP_AA2_EXT,
//                    _cbGetData,
//                    (void*)Microsoft31YaHei7_72);
}



