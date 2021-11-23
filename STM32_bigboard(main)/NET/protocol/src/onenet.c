/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	onenet.c
	*
	*	���ߣ� 		��־ΰ
	*
	*	���ڣ� 		2017-9-29
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 	  Э���
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/

//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸
#include "net_device.h"

//Э���ļ�
#include "onenet.h"

//Ӳ������
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "sht20.h"
#include "adxl345.h"
#include "gy30.h"
#include "fault.h"
#include "iwdg.h"
#include "hwtimer.h"
#include "selfcheck.h"
#include "oled.h"

//ͼƬ�����ļ�
#include "image_2k.h"

//C��
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



//119.29.201.31
ONETNET_INFO oneNetInfo = {"119.28.84.27", "4001", 0, 0, 0, 0};
extern DATA_STREAM dataStream[];


/*
************************************************************
*	�������ƣ�	OneNet_toString
*
*	�������ܣ�	����ֵתΪ�ַ���
*
*	��ڲ�����	dataStream��������
*				buf��ת����Ļ���
*				pos���������е��ĸ�����
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void OneNet_toString(DATA_STREAM *dataStream, char *buf, unsigned short pos)
{
	
	memset(buf, 0, 48);

	switch((unsigned char)dataStream[pos].dataType)
	{
		case TYPE_BOOL:
			snprintf(buf, 48, "%d", *(_Bool *)dataStream[pos].data);
		break;
		
		case TYPE_CHAR:
			snprintf(buf, 48, "%d", *(char *)dataStream[pos].data);
		break;
		
		case TYPE_UCHAR:
			snprintf(buf, 48, "%d", *(unsigned char *)dataStream[pos].data);
		break;
		
		case TYPE_SHORT:
			snprintf(buf, 48, "%d", *(short *)dataStream[pos].data);
		break;
		
		case TYPE_USHORT:
			snprintf(buf, 48, "%d", *(unsigned short *)dataStream[pos].data);
		break;
		
		case TYPE_INT:
			snprintf(buf, 48, "%d", *(int *)dataStream[pos].data);
		break;
		
		case TYPE_UINT:
			snprintf(buf, 48, "%d", *(unsigned int *)dataStream[pos].data);
		break;
		
		case TYPE_LONG:
			snprintf(buf, 48, "%ld", *(long *)dataStream[pos].data);
		break;
		
		case TYPE_ULONG:
			snprintf(buf, 48, "%ld", *(unsigned long *)dataStream[pos].data);
		break;
			
		case TYPE_FLOAT:
			snprintf(buf, 48, "%f", *(float *)dataStream[pos].data);
		break;
		
		case TYPE_DOUBLE:
			snprintf(buf, 48, "%f", *(double *)dataStream[pos].data);
		break;
		
		case TYPE_GPS:
			snprintf(buf, 48, "{\"lon\":%s,\"lat\":%s}", (char *)dataStream[pos].data, (char *)dataStream[pos].data + 16);
		break;
	}

}

/*
************************************************************
*	�������ƣ�	OneNet_Load_DataStream
*
*	�������ܣ�	��������װ
*
*	��ڲ�����	type���������ݵĸ�ʽ
*				send_buf�����ͻ���ָ��
*				len�������������ĸ���
*
*	���ز�����	��
*
*	˵����		��װ��������ʽ
************************************************************
*/
void OneNet_Load_DataStream(unsigned char type, char *send_buf, unsigned char len)
{
	
	unsigned char count = 0;
	char stream_buf[96];
	char data_buf[48];
	char *ptr = send_buf;

	switch(type)
	{
		case HTTP_TYPE1:
			
			UsartPrintf(USART_DEBUG, "Tips:	OneNet_SendData-HTTP_TYPE1\r\n");
		
			strncpy(send_buf, "{\"datastreams\":[", strlen("{\"datastreams\":["));
			for(; count < len; count++)
			{
				if(dataStream[count].flag) //���ʹ�ܷ��ͱ�־λ
				{
					memset(stream_buf, 0, sizeof(stream_buf));

					OneNet_toString(dataStream, data_buf, count);
					snprintf(stream_buf, sizeof(stream_buf), "{\"id\":\"%s\",\"datapoints\":[{\"value\":%s}]},", dataStream[count].name, data_buf);
					
					strncat(send_buf, stream_buf, strlen(stream_buf));
				}
			}
			
			while(*ptr != '\0')					//�ҵ�������
				ptr++;
			*(--ptr) = '\0';					//������','�滻Ϊ������
			
			strncat(send_buf, "]}", 2);
		
		break;
			
		case HTTP_TYPE3:
			
			UsartPrintf(USART_DEBUG, "Tips:	OneNet_SendData-HTTP_TYPE3\r\n");
		
			strncpy(send_buf, "{", 1);
			for(; count < len; count++)
			{
				if(dataStream[count].flag) //���ʹ�ܷ��ͱ�־λ
				{
					memset(stream_buf, 0, sizeof(stream_buf));

					OneNet_toString(dataStream, data_buf, count);
					snprintf(stream_buf, sizeof(stream_buf), "\"%s\":%s,", dataStream[count].name, data_buf);

					strncat(send_buf, stream_buf, strlen(stream_buf));
				}
			}
			
			while(*ptr != '\0')					//�ҵ�������
				ptr++;
			*(--ptr) = '\0';					//������','�滻Ϊ������
			
			strncat(send_buf, "}", 1);
		
		break;
		
		case HTTP_TYPE4:
			
			UsartPrintf(USART_DEBUG, "Tips:	OneNet_SendData-HTTP_TYPE4\r\n");
		
			strncpy(send_buf, "{", 1);
			for(; count < len; count++)
			{
				if(dataStream[count].flag) //���ʹ�ܷ��ͱ�־λ
				{
					memset(stream_buf, 0, sizeof(stream_buf));
					
					OneNet_toString(dataStream, data_buf, count);
					snprintf(stream_buf, sizeof(stream_buf), "\"%s\":{\"2016-08-10T12:31:17\":%s},", dataStream[count].name, data_buf);
					
					strncat(send_buf, stream_buf, strlen(stream_buf));
				}
			}
			
			while(*ptr != '\0')					//�ҵ�������
				ptr++;
			*(--ptr) = '\0';					//������','�滻Ϊ������
			
			strncat(send_buf, "}", 1);
		
		break;
		
		case HTTP_TYPE5:
			
			UsartPrintf(USART_DEBUG, "Tips:	OneNet_SendData-HTTP_TYPE5\r\n");
		
			strncpy(send_buf, ",;", 2);
			for(; count < len; count++)
			{
				if(dataStream[count].flag) //���ʹ�ܷ��ͱ�־λ
				{
					memset(stream_buf, 0, sizeof(stream_buf));
					
					OneNet_toString(dataStream, data_buf, count);
					snprintf(stream_buf, sizeof(stream_buf), "%s,%s;", dataStream[count].name, data_buf);
				}
				
				strncat(send_buf, stream_buf, strlen(stream_buf));
			}
		
		break;
	}

}

/*
************************************************************
*	�������ƣ�	OneNet_SendData
*
*	�������ܣ�	�ϴ����ݵ�ƽ̨
*
*	��ڲ�����	type���������ݵĸ�ʽ
*
*	���ز�����	��
*
*	˵����		������Ҫ����Ϊ�Լ���Ҫ�ϴ������ݣ����ո�ʽ��д
************************************************************
*/
_Bool OneNet_SendData(HTTP_TYPE  type, unsigned char len)
{
	
	char sendBuf[512];
	char streams[416];
//	unsigned short strLen = 0;
	
	if(!oneNetInfo.netWork || NET_DEVICE_Get_DataMode() != DEVICE_DATA_MODE)
		return 1;
	
	NET_DEVICE_Set_DataMode(DEVICE_CMD_MODE);
	
	memset(sendBuf, 0, sizeof(sendBuf));
	memset(streams, 0, sizeof(streams));
	
	OneNet_Load_DataStream(type, streams, len);
	
	// strLen = strlen(streams);
	
	//�������
//	snprintf(sendBuf, sizeof(sendBuf), "POST /devices/%s/datapoints?type=%d HTTP/1.1\r\napi-key:%s\r\nHost:api.heclouds.com\r\n"
//					"Content-Length:%d\r\n\r\n",
//	
//					oneNetInfo.devID, type, oneNetInfo.apiKey, strLen);
	
	strncat(sendBuf, streams, strlen(streams));
	
	NET_DEVICE_SendData((unsigned char *)sendBuf, strlen(sendBuf));
	
	faultTypeReport = FAULT_NONE; //����֮��������
	
	NET_DEVICE_Set_DataMode(DEVICE_DATA_MODE);
	
	return 0;
	
}

/*
************************************************************
*	�������ƣ�	OneNet_Status
*
*	�������ܣ�	����״̬���
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void OneNet_Status(void)
{
	
	unsigned char errType = 0;
	
	if(!oneNetInfo.netWork || NET_DEVICE_Get_DataMode() != DEVICE_DATA_MODE)	//�������Ϊ���� �� ��Ϊ�����շ�ģʽ
		return;
	
	NET_DEVICE_Set_DataMode(DEVICE_CMD_MODE);									//����Ϊ�����շ�ģʽ
	
	errType = NET_DEVICE_Check();
	
	if(errType == CHECK_CLOSED || errType == CHECK_GOT_IP)
	{
		faultTypeReport = faultType = FAULT_EDP;								//���ΪЭ�����
		
		oneNetInfo.errCount++;
	}
	else if(errType == CHECK_NO_DEVICE)
	{
		faultTypeReport = faultType = FAULT_NODEVICE;							//���Ϊ�豸����
		
		oneNetInfo.errCount++;
	}
	else
	{
		faultTypeReport = faultType = FAULT_NONE;								//�޴���
	}
	
	NET_DEVICE_ClrData();														//�������
	
	NET_DEVICE_Set_DataMode(DEVICE_DATA_MODE);									//����Ϊ�����շ�ģʽ
	
	

}

/*
************************************************************
*	�������ƣ�	Net_Event
*
*	�������ܣ�	������ƺ��� ���ƿ���ιʳ
*
*	��ڲ�����	dataPtr��ƽ̨���ص�����
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Net_Event(unsigned char *dataPtr)
{
		if(strstr((char *)dataPtr, "1"))
		{
			UsartPrintf(USART_DEBUG, "��\r\n");
			TIM3->CCR1= 300;//open
			DelayXms(1000);
			TIM3->CCR1= 735;//close
			Led4_Set(LED_ON);
		}
		else if(strstr((char *)dataPtr,"0")){
			UsartPrintf(USART_DEBUG,"��\r\n");
			
			Led4_Set(LED_OFF);
		}
//	if(strstr((char *)dataPtr, "CLOSED"))
//	{
//		UsartPrintf(USART_DEBUG, "TCP CLOSED1\r\n");
//		
//		faultTypeReport = faultType = FAULT_EDP;						//���ΪЭ�����
//		
//		oneNetInfo.errCount++;
//	}
//	else
//	{
//		//������������Ƿ��ͳɹ�
//		if(strstr((char *)dataPtr, "succ"))
//		{
//			UsartPrintf(USART_DEBUG, "Tips:		Send OK\r\n");
//			oneNetInfo.errCount = 0;
//		}
//		else
//		{
//			UsartPrintf(USART_DEBUG, "Tips:		Send Err\r\n");
//			oneNetInfo.errCount++;
//		}
//	}
//	
	NET_DEVICE_ClrData();

}
