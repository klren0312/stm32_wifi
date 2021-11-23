#include "jiaredian.h"
 
HOT_STATUS hotStatus;

/*???GPIO?? GPIOA PIN5*/
void HOT_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Structure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Structure);
	HOT_Switch(H_OFF,HOT_1);
}



/*???????,????????*/
void HOT_Switch(const uint8_t statu,const uint8_t mode){
	if(statu){
		HOT_OFF;
		
		if(mode&0x01){
			hotStatus.HotSta=0;
			HOT_ON;
		}
	}else{
		if(mode&0x01){
			hotStatus.HotSta=1;
			HOT_OFF;
		}
	}
}

 