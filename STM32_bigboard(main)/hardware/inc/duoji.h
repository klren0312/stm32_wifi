#ifndef __duoji_H
#define __duoji_H
#include "stm32f10x.h"

extern volatile unsigned char  duoji_value;

void Duoji_Init(u16 arr,u16 psc);
 
#endif