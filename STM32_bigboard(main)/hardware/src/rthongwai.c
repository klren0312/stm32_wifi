#include "rthongwai.h"
volatile unsigned char  body_value=0;

void Body_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(Body_GPIO_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//感应高电平，所以选择下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_InitStructure.GPIO_Pin = Body_GPIO_PIN;
	GPIO_Init(Body_GPIO_PORT,&GPIO_InitStructure);
}

