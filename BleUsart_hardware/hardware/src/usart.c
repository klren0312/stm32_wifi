/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	usart.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2016-11-23
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		��Ƭ�����������ʼ������ʽ����ӡ
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/
//Ӳ������
#include "usart.h"
#include "delay.h"

//C��
#include <stdarg.h>
#include <string.h>


/*
************************************************************
*	�������ƣ�	Usart1_Init
*
*	�������ܣ�	����1��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA9		RX-PA10
************************************************************
*/
void Usart1_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);							//��GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);							//��USART1��ʱ��
	
	//PA9	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;										//����Ϊ����ģʽ
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9;											//��ʼ��Pin9
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;									//���ص����Ƶ��
	GPIO_Init(GPIOA, &gpioInitStruct);												//��ʼ��GPIOA
	
	//PA10	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;								//����Ϊ��������
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;											//��ʼ��Pin10
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;									//���ص����Ƶ��
	GPIO_Init(GPIOA, &gpioInitStruct);												//��ʼ��GPIOA
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART1, &usartInitStruct);
	
	USART_Cmd(USART1, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;									//usart1�жϺ�
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;										//�ж�ͨ��ʹ��
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;							//��ռ�ж����ȼ�(ֵԽС���ȼ�Խ��)
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;									//���ж����ȼ�(ֵԽС���ȼ�Խ��)
	NVIC_Init(&nvicInitStruct);														//��ʼ��NVIC

}

/*
************************************************************
*	�������ƣ�	Usart2_Init
*
*	�������ܣ�	����2��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA2		RX-PA3
************************************************************
*/
void Usart2_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//PA2	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_2;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//PA3	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_3;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART2, &usartInitStruct);
	
	USART_Cmd(USART2, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicInitStruct);

}


/*
************************************************************
*	�������ƣ�	Usart3_Init
*
*	�������ܣ�	����3��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PB10		RX-PB11
************************************************************
*/
void Usart3_Init(unsigned int baud)
{
	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
	//PB10 TXD
	gpioInitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpioInitStruct);
	
	//PB11 RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_11;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usartInitStruct.USART_Parity = USART_Parity_No;
	usartInitStruct.USART_StopBits = USART_StopBits_1;
	usartInitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3,&usartInitStruct);
	
	USART_Cmd(USART3,ENABLE);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	
	//�ж�
	nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicInitStruct);
	
}
/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//��������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
	}

}

/*
************************************************************
*	�������ƣ�	UsartPrintf
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsprintf((char *)UsartPrintfBuf, fmt, ap);							//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}

//extern unsigned char usart1Buf[64];
//extern unsigned char usart1Len;
/*
************************************************************
*	�������ƣ�	USART1_IRQHandler
*
*	�������ܣ�	����1�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
//void USART1_IRQHandler(void)
//{

//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//�����ж�
//	{
//		if(usart1Len >= 64)									//��ֹ���ݹ��࣬�����ڴ����
//			usart1Len = 0;
//		usart1Buf[usart1Len++] = USART1->DR;
//		
//		USART_ClearFlag(USART1, USART_FLAG_RXNE);
//	}

//}


extern unsigned char usart3Buf[64];
extern unsigned char usart3Len;
/*
************************************************************
*	�������ƣ�	USART3_IRQHandler
*
*	�������ܣ�	����3�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART3_IRQHandler(void)
{

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)	//�����ж�
	{
		if(usart3Len >= 64)									//��ֹ���ݹ��࣬�����ڴ����
			usart3Len = 0;
		usart3Buf[usart3Len++] = USART3->DR;
		
		USART_ClearFlag(USART3, USART_FLAG_RXNE);
	}

}

