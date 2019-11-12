#include "main.h"

//Timer 2 32-bit counter 


void TIM6_Configuration(void)
{
	/* --------------Enable Module Clock Source ----------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	/* --------------Configure TIM6----------------------------------------*/
	{
		TIM_TimeBaseInitTypeDef  tim;
    
    tim.TIM_Prescaler = 84-1;        //84M internal clock��1MHz
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
    TIM_Cmd(TIM6, ENABLE);	 //ʹ��ʱ��
    TIM_ITConfig(TIM6, TIM_IT_Update,ENABLE);//ʹ���ж�
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);	//����жϱ�־λ
}

void TIM6_DAC_IRQHandler(void)  
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)!= RESET) 
	{
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
		TIM_ClearFlag(TIM6, TIM_FLAG_Update);
   	//	INIT_count++;
		REMOTE_LOSE_COUT++;//ң����������ң���������ж��в������㣬��ң�����жϽ���ȥ���˱������ϱ��
		STATE_CHANGE(); //�������ܵ�״̬�л������ܵ���Ҫ�߼��ڴ˺�����
		
		CHASSIS_Motor_TASK();//���̿��Ʋ�ͬ״̬�Ĵ���  
    UP_DOWN_Motor_TASK();//�����ȿ��Ʋ�ͬ״̬�Ĵ���
    TRAILER_Motor_TASK();//�ϳ�צ�ӿ���
    PAW_Motor_TASK();//ȡ��צ�ӿ��Ʋ�ͬ״̬�Ĵ���	
 
		CM_OUTPUT();//���PID�ļ�����ͨ���˺�������

   }
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);  //����жϱ�־λ
		
}

