#ifndef _JIAREDIAN_H_
#define _JIAREDIAN_H_

#include "stm32f10x.h"



#define HOT_ON GPIO_SetBits(GPIOC,GPIO_Pin_1)
#define HOT_OFF GPIO_ResetBits(GPIOC,GPIO_Pin_1)
	
#define  HOT_1    0X01
#define  H_ON  1
#define  H_OFF  (!H_ON)

typedef struct
{

	_Bool HotSta;

}  HOT_STATUS;

 extern HOT_STATUS hotStatus;


void HOT_Init(void);
 
void HOT_Switch(const uint8_t statu,const uint8_t mode);
_Bool HOT_GetValue(void);



#endif