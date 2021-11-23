#ifndef _FENGSHAN_H_
#define _FENGSHAN_H_

#include "stm32f10x.h"



#define JDQ_ON GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define JDQ_OFF GPIO_ResetBits(GPIOA,GPIO_Pin_8)

#define  JDQ_1    0X01
#define  J_ON  1
#define  J_OFF  (!J_ON)

typedef struct
{

	_Bool FengSta;

} FENG_STATUS;

 extern FENG_STATUS fengStatus;


void JDQ_Init(void);
 
void JDQ_Switch(const uint8_t statu,const uint8_t mode);
_Bool JDQ_GetValue(void);



#endif