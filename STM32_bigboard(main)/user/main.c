/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	main.c
	*
	*	作者： 		任志伟
	*
	*	日期： 		2017-06-14
	*
	*	版本： 		V1.5
	*
	*	说明： 	  主函数
	*
	*	修改记录：	
	*	PB3 -- 人体红外
	* PA6 -- 舵机
	* PA5 -- 红外对管
	* PC3 -- 红外对管ADC采样
	* PC2 -- 紫外线灯
	* PC1 -- 加热垫
	*	PA8 -- 风扇
	************************************************************
	************************************************************
	************************************************************
**/

//单片机头文件
#include "stm32f10x.h"

//网络协议层
#include "onenet.h"
#include "fault.h"

//网络设备
#include "net_device.h"

//硬件驱动
#include "led.h"
#include "delay.h"
#include "lcd1602.h"
#include "usart.h"
#include "hwtimer.h"
#include "i2c.h"
#include "gy30.h"
#include "adxl345.h"
#include "sht20.h"
#include "iwdg.h"
#include "at24c02.h"
#include "selfcheck.h"
#include "beep.h"
#include "info.h"
#include "tcrt5000.h"
#include "rthongwai.h"
#include "duoji.h"
#include "fengshan.h"
#include "light.h"
#include "jiaredian.h"

//C库
#include <string.h>


//全局变量
unsigned char uart5Len = 0;	//uart5接收的数据长度
char uart5Buf[64];	//uart5接收缓存
unsigned char usart1Len = 0;//usart1接收的数据长度
char usart1Buf[64];//usart1接收缓存
 

//数据流
DATA_STREAM dataStream[] = {
//								{"Red_Led", &ledStatus.Led4Sta, TYPE_BOOL, 1},
								{"Green_Led", &ledStatus.Led5Sta, TYPE_BOOL, 1},
								{"Yellow_Led", &ledStatus.Led6Sta, TYPE_BOOL, 1},
								{"Blue_Led", &ledStatus.Led7Sta, TYPE_BOOL, 1},
								{"Fengshan", &fengStatus.FengSta, TYPE_BOOL, 1},
								{"beep", &beepInfo.Beep_Status, TYPE_BOOL, 1},
								{"temperature", &sht20Info.tempreture, TYPE_FLOAT, 1},
								{"humidity", &sht20Info.humidity, TYPE_FLOAT, 1},
								{"Xg", &adxlInfo.incidence_Xf, TYPE_FLOAT, 1},
								{"Yg", &adxlInfo.incidence_Yf, TYPE_FLOAT, 1},
								{"Zg", &adxlInfo.incidence_Zf, TYPE_FLOAT, 1},
								{"errType", &faultTypeReport, TYPE_UCHAR, 1},
							};
unsigned char dataStreamLen = sizeof(dataStream) / sizeof(dataStream[0]);





/*
************************************************************
*	函数名称：	Hardware_Init
*
*	函数功能：	硬件初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		初始化单片机功能以及外接设备
************************************************************
*/
void Hardware_Init(void)
{

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);								//中断控制器分组设置

	Delay_Init();																//systick初始化
	
	Led_Init();																	//LED初始化
	
	Body_Init();																//人体红外初始化
	
	Duoji_Init(9999,143);	 											//舵机初始化 
	
	Beep_Init();																//蜂鸣器初始化
	
	TCRT5000_Init();															//TCRT5000初始化
	
	IIC_Init();																	//软件IIC总线初始化
	
	Lcd1602_Init();																//LCD1602初始化
	
	Usart1_Init(115200); 														//初始化串口   115200bps
	
	Uart5_Init(9600);															//初始化蓝牙串口  9600bps
	
	JDQ_Init();                                //初始化风扇
	
	LIGHT_Init();                               //初始化紫外线灯
	
	HOT_Init();																	//初始化加热垫
	
	Lcd1602_DisString(0x80, "Check Power On");									//提示进行开机检测
	Check_PowerOn(); 															//上电自检
	Lcd1602_Clear(0x80);														//清第一行显示
	
	if(checkInfo.ADXL345_OK == DEV_OK) 											//如果检测到ADXL345则初始化
		ADXL345_Init();
	


	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET) 								//如果是看门狗复位则提示
	{
		UsartPrintf(USART_DEBUG, "WARN:	IWDG Reboot\r\n");
		
		RCC_ClearFlag();														//清除看门狗复位标志位
		
		faultTypeReport = faultType = FAULT_REBOOT; 							//标记为重启错误
		
		netDeviceInfo.reboot = 1;
	}
	else
	{
//		UsartPrintf(USART_DEBUG, "2.DEVID: %s,     APIKEY: %s\r\n"
//								, oneNetInfo.devID, oneNetInfo.apiKey);
		
		netDeviceInfo.reboot = 0;
	}
	
	//Iwdg_Init(4, 1250); 														//64分频，每秒625次，重载1250次，2s
	
	Lcd1602_Clear(0xff);														//清屏
	
	Timer6_7_Init(TIM6, 49, 35999);												//72MHz，36000分频-500us，50重载值。则中断周期为500us * 50 = 25ms
	Timer6_7_Init(TIM7, 1999, 35999);											//72MHz，36000分频-500us，2000重载值。则中断周期为500us * 2000 = 1s
																				//定时检查网络状态标志位
	
	UsartPrintf(USART_DEBUG, "3.Hardware init OK\r\n");							//提示初始化完成

}

/*
************************************************************
*	函数名称：	main
*
*	函数功能：	
*
*	入口参数：	无
*
*	返回参数：	0
*
*	说明：		
************************************************************
*/
int main(void)
{
	
	unsigned char *dataPtr;
	unsigned int runTime = 0;
	_Bool sendFlag = 0;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST , ENABLE);
	Hardware_Init();									//硬件初始化
	
Lcd1602_DisString(0x80, "PetHouse ENV");
	
	NET_DEVICE_IO_Init();								//网络设备IO初始化
	NET_DEVICE_Reset();									//网络设备复位
	NET_DEVICE_Set_DataMode(DEVICE_CMD_MODE);			//设置为命令收发模式(例如ESP8266要区分AT的返回还是平台下发数据的返回)
	
	while(1)
	{
		
		if(oneNetInfo.netWork == 1)
		{

/******************************************************************************
			数据与心跳
******************************************************************************/
			if(timInfo.timer6Out - runTime >= 60)									//25s一次(25ms中断)
			{
				runTime = timInfo.timer6Out;
				
				if(sendFlag)
				{
					TIM_Cmd(OS_TIMER, DISABLE);
					OneNet_Status();												//状态检查
					TIM_Cmd(OS_TIMER, ENABLE);
				}
				else
				{
					TIM_Cmd(OS_TIMER, DISABLE);
					OneNet_SendData(HTTP_TYPE3, dataStreamLen);						//数据发送
					TIM_Cmd(OS_TIMER, ENABLE);
				}
		
				sendFlag = !sendFlag;
			}
			
/******************************************************************************
			发送结果解析
******************************************************************************/
			if(oneNetInfo.netWork && NET_DEVICE_Get_DataMode() == DEVICE_DATA_MODE)	//当有网络 且 在命令接收模式时
			{
				dataPtr = NET_DEVICE_GetIPD(0);										//不等待，获取平台下发的数据
				if(dataPtr != NULL)													//如果数据指针不为空，则代表收到了数据
				{
					Net_Event(dataPtr);											//集中处理
				}
			}
			
/******************************************************************************
			传感器
******************************************************************************/
			if(checkInfo.ADXL345_OK == DEV_OK) 										//只有设备存在时，才会读取值和显示
			{
				ADXL345_GetValue();													//采集传感器数据
        //Lcd1602_DisString(0x80, "PetHouse ENV");
			}
			if(checkInfo.SHT20_OK == DEV_OK) 										//只有设备存在时，才会读取值和显示
			{
				SHT20_GetValue();													//采集传感器数据
				Lcd1602_DisString(0xC0, "%0.1fC,%0.1f%%", sht20Info.tempreture, sht20Info.humidity);
				if(sht20Info.tempreture>=30){
					JDQ_Switch(J_ON,JDQ_1);	
					LIGHT_Switch(L_ON,LIGHT_1);
				}
				if(sht20Info.tempreture<=25){
					JDQ_Switch(J_OFF,JDQ_1);
					LIGHT_Switch(L_OFF,LIGHT_1);
				}
				if(sht20Info.tempreture<=10){
					HOT_Switch(H_ON,HOT_1);
				}
				if(sht20Info.tempreture>=23){
					HOT_Switch(H_OFF,HOT_1);
				}
			}
			//红外
			if(t5000Info.status == TCRT5000_ON)
			{
				TCRT5000_GetValue(5);
//				&& GPIO_ReadInputDataBit(Body_GPIO_PORT,Body_GPIO_PIN)
				if(t5000Info.voltag < 3500 ){
					LIGHT_Switch(J_OFF,JDQ_1);
//					HOT_Switch(J_OFF,JDQ_1);
					Led6_Set(LED_ON);
				}else{
					LIGHT_Switch(J_ON,JDQ_1);
//					HOT_Switch(J_ON,JDQ_1);
					Led6_Set(LED_OFF);
				}
			}
			

//			if(GPIO_ReadInputDataBit(Body_GPIO_PORT,Body_GPIO_PIN)){
//				//TIM3->CCR1= 300;//open
//				Led6_Set(LED_ON);
//			}else{
//				//TIM3->CCR1= 735;//close
//				Led6_Set(LED_OFF);
//			}
			

/******************************************************************************
			错误处理
******************************************************************************/
			if(faultType != FAULT_NONE)												//如果错误标志被设置
			{
				UsartPrintf(USART_DEBUG, "WARN:	Fault Process\r\n");
				Fault_Process();													//进入错误处理函数
			}
			
/******************************************************************************
			数据反馈
******************************************************************************/
			if(oneNetInfo.sendData)
			{
				oneNetInfo.sendData = OneNet_SendData(HTTP_TYPE3, dataStreamLen);
			}
		}
		else
		{
/******************************************************************************
			初始化网络设备、接入平台
******************************************************************************/
			if(!oneNetInfo.netWork && (checkInfo.NET_DEVICE_OK == DEV_OK))			//当没有网络 且 网络模块检测到时
			{
				NET_DEVICE_Set_DataMode(DEVICE_CMD_MODE);							//设置为命令收发模式
				
				if(!NET_DEVICE_Init(oneNetInfo.ip, oneNetInfo.port))				//初始化网络设备，能连入网络
				{
					UsartPrintf(USART_DEBUG, "Tips:	NetWork OK\r\n");
		
					oneNetInfo.netWork = 1;
					
					NET_DEVICE_Set_DataMode(DEVICE_DATA_MODE);						//网络设备指令模式
					
					DelayXms(200);

					runTime = timInfo.timer6Out;
				}
			}
			
/******************************************************************************
			网络设备检测
******************************************************************************/
			if(checkInfo.NET_DEVICE_OK == DEV_ERR) 									//当网络设备未做检测
			{
				NET_DEVICE_Set_DataMode(DEVICE_CMD_MODE);							//设置为命令收发模式
				
				if(timerCount >= NET_TIME) 											//如果网络连接超时
				{
					UsartPrintf(USART_DEBUG, "Tips:		Timer Check Err\r\n");
					
					NET_DEVICE_Reset();												//复位网络设备
					timerCount = 0;													//清零连接超时计数
					faultType = FAULT_NONE;											//清除错误标志
				}
				
				if(!NET_DEVICE_Exist())												//网络设备检测
				{
					UsartPrintf(USART_DEBUG, "NET Device :Ok\r\n");
					checkInfo.NET_DEVICE_OK = DEV_OK;								//检测到网络设备，标记
					NET_DEVICE_Set_DataMode(DEVICE_DATA_MODE);						//设置为数据收发模式
				}
				else
					UsartPrintf(USART_DEBUG, "NET Device :Error\r\n");
			}
		}

/******************************************************************************
	    小娜控制
******************************************************************************/					
		if(usart1Len>0){
			if(strcmp(usart1Buf,"open") == 0){
				UsartPrintf(USART1,"输入的命令是：\r\n%s\r\n",usart1Buf);
				JDQ_Switch(J_ON,JDQ_1);
			}
			else if(strcmp(usart1Buf,"close") == 0){
				UsartPrintf(USART1,"输入的命令是：\r\n%s\r\n",usart1Buf);
				JDQ_Switch(J_OFF,JDQ_1);
			} 
			
			memset(usart1Buf, 0, sizeof(usart1Buf));
			usart1Len = 0;
		}
 
/******************************************************************************
			蓝牙控制
******************************************************************************/			
		if(uart5Len > 0)
		{
			 
			if(strcmp(uart5Buf, "666") == 0){
				UsartPrintf(UART5, "输入的命令是：\r\n%s\r\n", uart5Buf);
				JDQ_Switch(J_ON,JDQ_1);				
			}
			else if(strcmp(uart5Buf, "233") == 0){
				UsartPrintf(UART5, "输入的命令是：\r\n%s\r\n", uart5Buf);
			  JDQ_Switch(J_OFF,JDQ_1);
			}
			
			
			memset(uart5Buf, 0, sizeof(uart5Buf));
			uart5Len = 0;
		}		
	}

}
