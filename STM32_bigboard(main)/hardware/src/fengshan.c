#include "fengshan.h"
 
FENG_STATUS fengStatus;

/*???GPIO?? GPIOA PIN5*/
void JDQ_Init(void){
	GPIO_InitTypeDef GPIO_Structure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Structure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Structure);
	JDQ_Switch(J_OFF,JDQ_1);
}



/*???????,????????*/
void JDQ_Switch(const uint8_t statu,const uint8_t mode){
	if(statu){
		JDQ_OFF;
		
		if(mode&0x01){
			fengStatus.FengSta=0;
			JDQ_ON;
		}
	}else{
		if(mode&0x01){
			fengStatus.FengSta=1;
			JDQ_OFF;
		}
	}
}

 