#ifndef __IRENTI_H
#define __IRENTI_H

#include "stm32f10x.h"
#include "led.h"

extern volatile unsigned char  body_value;
#define Body_GPIO_PORT GPIOB
#define Body_GPIO_PIN GPIO_Pin_3
#define Body_GPIO_CLK RCC_APB2Periph_GPIOB

void Body_Init(void);
#endif