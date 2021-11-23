/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	info.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2017-02-23
	*
	*	�汾�� 		V1.1
	*
	*	˵���� 		V1.0��SSID��PSWD��DEVID��APIKEY���漰��ȡ��
	*				V1.1��ȡ����SSID��PSWD�ı���Ͷ�д���滻Ϊ������������wifi���͵������豸�����Զ����档
	*
	*				��Ҫ��ֻ�е��ⲿ�洢������ʱ���Ŵ��ж�ȡ��Ϣ
	*					  �������ڣ����ȡ�̻��ڴ��������Ϣ
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/

//Ӳ������
#include "info.h"
#include "at24c02.h"
#include "delay.h"
#include "usart.h"

//Э��
#include "onenet.h"

//C��
#include <string.h>
#include <stdlib.h>




/*
************************************************************
*	�������ƣ�	Info_Check
*
*	�������ܣ�	�����Ϣ�Ƿ����
*
*	��ڲ�����	��
*
*	���ز�����	�����
*
*	˵����		�ж�wifi��ssid��pswd�Ƿ����
*				0-ok	1-��ssid	2-��pswd
*				3-��devid	4-��apikey
************************************************************
*/
unsigned char Info_Check(void)
{
	
	unsigned char rData = 0;
	
	AT24C02_ReadByte(DEVID_ADDRESS, &rData);	//��ȡ����ֵ
	if(rData == 0 || rData >= 10)				//���Ϊ0�򳬳�
		return 1;
	
	AT24C02_ReadByte(AKEY_ADDRESS, &rData);		//��ȡ����ֵ
	if(rData == 0 || rData >= 30)				//���Ϊ0�򳬳�
		return 2;
        
	return 0;

}

/*
************************************************************
*	�������ƣ�	Info_WifiLen
*
*	�������ܣ�	��ȡ��Ϣ����
*
*	��ڲ�����	sp����Ҫ������Ϣ-��˵��
*
*	���ز�����	�����
*
*	˵����		��ȡ0-ssid����	1-pswd����	
*				2-devid����		3-apikey����
************************************************************
*/
unsigned char Info_WifiLen(unsigned char sp)
{
	
	unsigned char len = 0;
    
    switch(sp)
    {
        case 0:
            AT24C02_ReadByte(DEVID_ADDRESS, &len);		//��ȡ����ֵ
			if(len == 0 || len >= 10)					//���Ϊ0�򳬳�
				return 1;
        break;
        
        case 1:
            AT24C02_ReadByte(AKEY_ADDRESS, &len);		//��ȡ����ֵ
			if(len == 0 || len >= 30)					//���Ϊ0�򳬳�
				return 1;
        break;
    }
	
	return len;

}

/*
************************************************************
*	�������ƣ�	Info_CountLen
*
*	�������ܣ�	�����ֶγ���
*
*	��ڲ�����	info����Ҫ�����ֶ�
*
*	���ز�����	�ֶγ���
*
*	˵����		���㴮1���������ֶγ���   ��"\r\n"��β
************************************************************
*/
unsigned char Info_CountLen(char *info)
{

	unsigned char len = 0;
	char *buf = strstr(info, ":");		//�ҵ�':'
	
	buf++;								//ƫ�Ƶ���һ���ֽڣ������ֶ���Ϣ��ʼ
	while(1)
	{
		if(*buf == '\r')				//ֱ��'\r'Ϊֹ
			return len;
		
		buf++;
		len++;
	}

}

/*
************************************************************
*	�������ƣ�	Info_Read
*
*	�������ܣ�	��ȡssid��pswd��devid��apikey
*
*	��ڲ�����	��
*
*	���ز�����	��ȡ���
*
*	˵����		0-�ɹ�		1-ʧ��
************************************************************
*/
_Bool Info_Read(void)
{
	
//    memset(oneNetInfo.devID, 0, sizeof(oneNetInfo.devID));											//���֮ǰ������
//	AT24C02_ReadBytes(DEVID_ADDRESS + 1, (unsigned char *)oneNetInfo.devID, Info_WifiLen(0));		//��ȡdevid����  ��devid
//    DelayXms(10);																					//��ʱ
//                
//    memset(oneNetInfo.apiKey, 0, sizeof(oneNetInfo.apiKey));										//���֮ǰ������
//	AT24C02_ReadBytes(AKEY_ADDRESS + 1, (unsigned char *)oneNetInfo.apiKey, Info_WifiLen(1));		//��ȡapikey����  ��apikey

    return 0;

}

/*
************************************************************
*	�������ƣ�	Info_Alter
*
*	�������ܣ�	����wifi��Ϣ����Ŀ��Ϣ
*
*	��ڲ�����	��Ҫ������ֶ�
*
*	���ز�����	������
*
*	˵����		0-����Ҫ��������		1-��Ҫ��������
************************************************************
*/
//_Bool Info_Alter(char *info)
//{
//    
//    char *usart1Tmp;
//    unsigned char usart1Count = 0;
//	_Bool flag = 0;
//        
//	if((usart1Tmp = strstr(info, "DEVID:")) != (void *)0)								//��ȡdevid
//	{
//		usart1Count = Info_CountLen(usart1Tmp);											//���㳤��
//        if(usart1Count > 0)
//        {
//            memset(oneNetInfo.devID, 0, sizeof(oneNetInfo.devID));						//���֮ǰ������
//            strncpy(oneNetInfo.devID, usart1Tmp + 6, usart1Count);
//            UsartPrintf(USART_DEBUG, "Tips:	Save DEVID: %s\r\n", oneNetInfo.devID);

//			AT24C02_WriteByte(DEVID_ADDRESS, strlen(oneNetInfo.devID));					//����devid����
//			DelayXms(10);
//			AT24C02_WriteBytes(DEVID_ADDRESS + 1,										//����ssid
//								(unsigned char *)oneNetInfo.devID,
//								strlen(oneNetInfo.devID));
//            
//            flag = 1;
//        }
//	}
//        
//	if((usart1Tmp = strstr(info, "APIKEY:")) != (void *)0)								//��ȡapikey
//	{
//		usart1Count = Info_CountLen(usart1Tmp);											//���㳤��
//        if(usart1Count > 0)
//        {
//            memset(oneNetInfo.apiKey, 0, sizeof(oneNetInfo.apiKey));					//���֮ǰ������
//            strncpy(oneNetInfo.apiKey, usart1Tmp + 7, usart1Count);
//            UsartPrintf(USART_DEBUG, "Tips:	Save APIKEY: %s\r\n", oneNetInfo.apiKey);

//			AT24C02_WriteByte(AKEY_ADDRESS, strlen(oneNetInfo.apiKey));					//����apikey����
//			DelayXms(10);
//			AT24C02_WriteBytes(AKEY_ADDRESS + 1,										//����ssid
//								(unsigned char *)oneNetInfo.apiKey,
//								strlen(oneNetInfo.apiKey));
//            
//            flag = 1;
//        }
//	}
//	
//	return flag;

//}
