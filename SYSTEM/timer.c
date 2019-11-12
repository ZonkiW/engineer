#include "main.h"

//Timer 2 32-bit counter 


void TIM6_Configuration(void)
{
	/* --------------Enable Module Clock Source ----------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	/* --------------Configure TIM6----------------------------------------*/
	{
		TIM_TimeBaseInitTypeDef  tim;
    
    tim.TIM_Prescaler = 84-1;        //84M internal clock，1MHz
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 3000;  //3ms
    TIM_TimeBaseInit(TIM6,&tim);
	}
	/* -------------- Configure NVIC ----------------------------------------*/
	{
		NVIC_InitTypeDef         nvic;

    nvic.NVIC_IRQChannel = TIM6_DAC_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority =1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
	}
}

void TIM6_Start(void)
{
    TIM_Cmd(TIM6, ENABLE);	 //使能时钟
    TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);//使能中断
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);	//清除中断标志位
}

void TIM6_DAC_IRQHandler(void)  
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)!= RESET) 
	{
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		TIM_ClearFlag(TIM6, TIM_FLAG_Update);
   	//	INIT_count++;
		REMOTE_LOSE_COUT++;//遥控器计数，遥控器串口中断中不断清零，当遥控器中断进不去，此变量不断变大
		STATE_CHANGE(); //各个功能的状态切换，功能的主要逻辑在此函数中
		
		CHASSIS_Motor_TASK();//底盘控制不同状态的处理  
    UP_DOWN_Motor_TASK();//升降腿控制不同状态的处理
    TRAILER_Motor_TASK();//拖车爪子控制
    PAW_Motor_TASK();//取弹爪子控制不同状态的处理	
 
		CM_OUTPUT();//电机PID的计算结果通过此函数发送

   }
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //清除中断标志位
		
}

