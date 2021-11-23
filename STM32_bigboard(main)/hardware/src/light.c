#include "light.h"
 
LIGHT_STATUS lightStatus;

/*???GPIO?? GPIOA PIN15*/
void LIGHT_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Structure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Structure);
	LIGHT_Switch(L_OFF,LIGHT_1);
}



/*???????,????????*/
void LIGHT_Switch(const uint8_t statu,const uint8_t mode){
	if(statu){
		LIGHT_OFF;
		
		if(mode&0x01){
			lightStatus.LightSta=0;
			LIGHT_ON;
		}
	}else{
		if(mode&0x01){
			lightStatus.LightSta=1;
			LIGHT_OFF;
		}
	}
}

 