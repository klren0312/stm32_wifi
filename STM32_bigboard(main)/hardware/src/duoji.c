#include "duoji.h"


volatile unsigned char  duoji_value=0;

void Duoji_Init(u16 arr,u16 psc){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //使能TIM2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period =  arr;//设置在下一个更新事件装入活动的自动重装载寄存器的周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//设置时钟分割：TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //设置定时器模式：TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性，TIM输出比较极性高
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure); //根据TIM_OCInitStructure中指定的参数初始化外设TIMx
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);//CH1预装载使能
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);//使能TIMx在ARR上的预装载寄存器
	TIM_CtrlPWMOutputs(TIM3,ENABLE); //MOE 主输出使能
	TIM_Cmd(TIM3, ENABLE);  //TIM3使能
	TIM3->CCR1= 735;
}

 

 
 


