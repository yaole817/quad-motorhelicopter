#include "includes.h"

volatile uint32_t	TIM4_IRQCNT;				//TIM4中断计数器
volatile uint32_t	TIM2_IRQCNT;				//TIM2中断计数器

/**************************实现函数********************************************
*函数原型:		
*功　　能:1ms中断一次,计数器为1000		
*******************************************************************************/
void TIM4_INIT(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//基础设置，时基和比较输出设置，由于这里只需定时，所以不用OC比较输出
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_DeInit(TIM4);
	//a period is 1000 times
	TIM_TimeBaseStructure.TIM_Period=1000;
	//prescaler is 1200,that is 72000000/72/1000=1000Hz;
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;//division number   is 72 
	//set clock division 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4
	//count up
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	//clear the TIM2 overflow interrupt flag
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	//TIM2 overflow interrupt enable
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	//enable TIM4
	TIM_Cmd(TIM4,ENABLE);
}
/**************************实现函数********************************************
*函数原型:		
*功　　能:		延时  
*******************************************************************************/
void delay_ms(uint16_t nms)
{	
	TIM4->CNT = 0;
  	while(nms--)
	{
		while(TIM_GetITStatus(TIM4 , TIM_IT_Update) == RESET);
			TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);   //清除中断标志
	}
} 
void delay_us(uint16_t nus)
{	
	TIM3->CNT = 1000 - nus;
	while(TIM_GetITStatus(TIM4 , TIM_IT_Update) == RESET);
	TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);   //清除中断标志
} 

/**************************实现函数********************************************
*函数原型:		
*功　　能:1ms中断一次,计数器为1000		
*******************************************************************************/
void TIM2_INIT(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//基础设置，时基和比较输出设置，由于这里只需定时，所以不用OC比较输出
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_DeInit(TIM2);
	//a period is 1000 times
	TIM_TimeBaseStructure.TIM_Period=1000;
	//prescaler is 1200,that is 72000000/72/1000=1000Hz;
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;//division number   is 72 
	//set clock division 
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //or TIM_CKD_DIV2 or TIM_CKD_DIV4
	//count up
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	//clear the TIM2 overflow interrupt flag
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//TIM2 overflow interrupt enable
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	//enable TIM2
	TIM_Cmd(TIM2,ENABLE);
}		

void TIM2_IRQ(void)
{
	TIM2_IRQCNT++;
	
	//CONTROL();
	//NRF_LOOP();
}

