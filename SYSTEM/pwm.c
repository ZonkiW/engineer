#include "main.h"

void PWM_Configuration(void)
{
	
	//  PWM_Set PA0_TIME5_CH1;//Ä¦²ÁÂÖ
	 // PWM_Set PA1_TIME5_CH2;//Ä¦²ÁÂÖ
//    PWM_Set PA2_TIME5_CH3;
//    PWM_Set PA3_TIME5_CH4;
	//	PWM_Set PA8_TIME1_CH1;
//		PWM_Set PA9_TIME1_CH2;
	//  PWM_Set PB0_TIME3_CH3;
	 //PWM_Set PB7_TIME4_CH2;//Ò£¿ØÆ÷
	 //PWM_Set PC6_TIME3_CH1;//¾ÅÖá
	 //PWM_Set PC7_TIME3_CH2;//¾ÅÖá
	  //PWM_Set PC8_TIME3_CH3;
	  PWM_Set PB8_TIME4_CH3;

		PB8_TIME4_CH3.GPIOx						=	GPIOB;
		PB8_TIME4_CH3.GPIO_Pin_x			=	GPIO_Pin_8;
		PB8_TIME4_CH3.GPIO_AF					=	GPIO_AF_TIM4;
		PB8_TIME4_CH3.TIMx						=	TIM4;
		PB8_TIME4_CH3.Chx							=	3;
		PB8_TIME4_CH3.Period					=	5000;
		PB8_TIME4_CH3.Prescaler				=	84-1;
		PB8_TIME4_CH3.TIM_Pulse				=	500;
		PWM_Configuration_AUTO(&PB8_TIME4_CH3);

//	 	PA0_TIME5_CH1.GPIOx						=	GPIOA;
//		PA0_TIME5_CH1.GPIO_Pin_x			=	GPIO_Pin_0;
//		PA0_TIME5_CH1.GPIO_AF					=	GPIO_AF_TIM5;
//		PA0_TIME5_CH1.TIMx						=	TIM5;
//		PA0_TIME5_CH1.Chx							=	1;
//		PA0_TIME5_CH1.Period					=	5000;
//		PA0_TIME5_CH1.Prescaler				=	84-1;
//		PA0_TIME5_CH1.TIM_Pulse				=	1500;
//		PWM_Configuration_AUTO(&PA0_TIME5_CH1);
		
//		PA1_TIME5_CH2.GPIOx						=	GPIOA;
//		PA1_TIME5_CH2.GPIO_Pin_x			=	GPIO_Pin_1;
//		PA1_TIME5_CH2.GPIO_AF					=	GPIO_AF_TIM5;
//		PA1_TIME5_CH2.TIMx						=	TIM5;
//		PA1_TIME5_CH2.Chx							=	2;
//		PA1_TIME5_CH2.Period					=	5000;
//		PA1_TIME5_CH2.Prescaler				=	84-1;
//		PA1_TIME5_CH2.TIM_Pulse				=	10000;
//		PWM_Configuration_AUTO(&PA1_TIME5_CH2);
		
//		PA2_TIME5_CH3.GPIOx						=	GPIOA;
//		PA2_TIME5_CH3.GPIO_Pin_x			=	GPIO_Pin_2;
//		PA2_TIME5_CH3.GPIO_AF					=	GPIO_AF_TIM5;
//		PA2_TIME5_CH3.TIMx						=	TIM5;
//		PA2_TIME5_CH3.Chx							=	3;
//		PA2_TIME5_CH3.Period					=	5000;
//		PA2_TIME5_CH3.Prescaler				=	84-1;
//		PA2_TIME5_CH3.TIM_Pulse				=	0;
//		PWM_Configuration_AUTO(&PA2_TIME5_CH3);
//		
//		PA3_TIME5_CH4.GPIOx						=	GPIOA;
//		PA3_TIME5_CH4.GPIO_Pin_x			=	GPIO_Pin_3;
//		PA3_TIME5_CH4.GPIO_AF					=	GPIO_AF_TIM5;
//		PA3_TIME5_CH4.TIMx						=	TIM5;
//		PA3_TIME5_CH4.Chx							=	4;
//		PA3_TIME5_CH4.Period					=	5000;
//		PA3_TIME5_CH4.Prescaler				=	84-1;
//		PA3_TIME5_CH4.TIM_Pulse				=	0;
//		PWM_Configuration_AUTO(&PA3_TIME5_CH4);
		
//		PA8_TIME1_CH1.GPIOx						  =	GPIOA;
//		PA8_TIME1_CH1.GPIO_Pin_x				=	GPIO_Pin_8;
//		PA8_TIME1_CH1.GPIO_AF					  =	GPIO_AF_TIM1;
//		PA8_TIME1_CH1.TIMx							=	TIM1;
//		PA8_TIME1_CH1.Chx							  =	1;
//		PA8_TIME1_CH1.Period						=	5000;
//		PA8_TIME1_CH1.Prescaler				  =	84-1;
//		PA8_TIME1_CH1.TIM_Pulse				  =	1500;
//		PWM_Configuration_AUTO(&PA8_TIME1_CH1);

		
//		PA9_TIME1_CH2.GPIOx						=	GPIOA;
//		PA9_TIME1_CH2.GPIO_Pin_x			=	GPIO_Pin_9;
//		PA9_TIME1_CH2.GPIO_AF					=	GPIO_AF_TIM1;
//		PA9_TIME1_CH2.TIMx						=	TIM1;
//		PA9_TIME1_CH2.Chx							=	2;
//		PA9_TIME1_CH2.Period					=	5000;
//		PA9_TIME1_CH2.Prescaler				=	84-1;
//		PA9_TIME1_CH2.TIM_Pulse				=	3000;
//		PWM_Configuration_AUTO(&PA9_TIME1_CH2);

//    PB0_TIME3_CH3.GPIOx						=	GPIOB;
//		PB0_TIME3_CH3.GPIO_Pin_x			=	GPIO_Pin_0;
//		PB0_TIME3_CH3.GPIO_AF					=	GPIO_AF_TIM3;
//		PB0_TIME3_CH3.TIMx						=	TIM3;
//		PB0_TIME3_CH3.Chx							=	3;
//		PB0_TIME3_CH3.Period					=	5000;
//		PB0_TIME3_CH3.Prescaler				=	84-1;
//		PB0_TIME3_CH3.TIM_Pulse				=	1500;
//		PWM_Configuration_AUTO(&PB0_TIME3_CH3);
		
//		PB7_TIME4_CH2.GPIOx						=	GPIOB;
//		PB7_TIME4_CH2.GPIO_Pin_x			=	GPIO_Pin_7;
//		PB7_TIME4_CH2.GPIO_AF					=	GPIO_AF_TIM4;
//		PB7_TIME4_CH2.TIMx						=	TIM4;
//		PB7_TIME4_CH2.Chx							=	2;
//		PB7_TIME4_CH2.Period					=	5000;
//		PB7_TIME4_CH2.Prescaler				=	84-1;
//		PB7_TIME4_CH2.TIM_Pulse				=	1500;
//		PWM_Configuration_AUTO(&PB7_TIME4_CH2);

//		PC6_TIME3_CH1.GPIOx						=	GPIOC;
//		PC6_TIME3_CH1.GPIO_Pin_x			=	GPIO_Pin_6;
//		PC6_TIME3_CH1.GPIO_AF					=	GPIO_AF_TIM3;
//		PC6_TIME3_CH1.TIMx						=	TIM3;
//		PC6_TIME3_CH1.Chx							=	1;
//		PC6_TIME3_CH1.Period					=	5000;
//		PC6_TIME3_CH1.Prescaler				=	84-1;
//		PC6_TIME3_CH1.TIM_Pulse				=	1500;
//		PWM_Configuration_AUTO(&PC6_TIME3_CH1);

//		PC7_TIME3_CH2.GPIOx						=	GPIOC;
//		PC7_TIME3_CH2.GPIO_Pin_x			=	GPIO_Pin_7;
//		PC7_TIME3_CH2.GPIO_AF					=	GPIO_AF_TIM3;
//		PC7_TIME3_CH2.TIMx						=	TIM3;
//		PC7_TIME3_CH2.Chx							=	2;
//		PC7_TIME3_CH2.Period					=	5000;
//		PC7_TIME3_CH2.Prescaler				=	84-1;
//		PC7_TIME3_CH2.TIM_Pulse				=	1500;
//		PWM_Configuration_AUTO(&PC7_TIME3_CH2);
		
//	PC8_TIME3_CH3.GPIOx						=	GPIOC;
//	PC8_TIME3_CH3.GPIO_Pin_x			=	GPIO_Pin_8;
//	PC8_TIME3_CH3.GPIO_AF					=	GPIO_AF_TIM4;
//	PC8_TIME3_CH3.TIMx						=	TIM3;
//	PC8_TIME3_CH3.Chx							=	3;
//	PC8_TIME3_CH3.Period					=	5000;
//	PC8_TIME3_CH3.Prescaler				=	84-1;
//	PC8_TIME3_CH3.TIM_Pulse				=	1500;
//	PWM_Configuration_AUTO(&PC8_TIME3_CH3);
//	
//	PC9_TIME3_CH4.GPIOx						=	GPIOC;
//	PC9_TIME3_CH4.GPIO_Pin_x			=	GPIO_Pin_9;
//	PC9_TIME3_CH4.GPIO_AF					=	GPIO_AF_TIM4;
//	PC9_TIME3_CH4.TIMx						=	TIM3;
//	PC9_TIME3_CH4.Chx							=	4;
//	PC9_TIME3_CH4.Period					=	5000;
//	PC9_TIME3_CH4.Prescaler				=	84-1;
//	PC9_TIME3_CH4.TIM_Pulse				=	1500;
//	PWM_Configuration_AUTO(&PC9_TIME3_CH4);
		


}

void PWM_Configuration_AUTO(PWM_Set* pwm)
{

	  GPIO_InitTypeDef          gpio;
    TIM_TimeBaseInitTypeDef   tim;
    TIM_OCInitTypeDef         oc;
	
		if(pwm->TIMx == TIM1 )
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
			
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
		
		gpio.GPIO_Mode	= GPIO_Mode_AF;
		gpio.GPIO_OType	= GPIO_OType_PP;
		gpio.GPIO_Pin		= pwm->GPIO_Pin_x;//GPIO_Pin_x
		gpio.GPIO_PuPd	= GPIO_PuPd_NOPULL;
		gpio.GPIO_Speed	= GPIO_Speed_100MHz;
		GPIO_Init(pwm->GPIOx,&gpio);//GPIOx

		Switch_GPIO_PinSource(pwm);
		GPIO_PinAFConfig(pwm->GPIOx,pwm->GPIO_PinSource,pwm->GPIO_AF);//GPIOx 
																																	//GPIO_PinSource 
																																	//GPIO_AF
		
		tim.TIM_Prescaler					=	pwm->Prescaler;//Prescaler
		tim.TIM_CounterMode				=	TIM_CounterMode_Up;
		tim.TIM_Period						= pwm->Period;//Period
		tim.TIM_ClockDivision			=	TIM_CKD_DIV1;
		tim.TIM_RepetitionCounter	=0;
		TIM_TimeBaseInit(pwm->TIMx,&tim);//TIMx
		
		oc.TIM_OCMode = TIM_OCMode_PWM1;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OutputNState = TIM_OutputNState_Enable;
    oc.TIM_OCPolarity = TIM_OCPolarity_High;
    oc.TIM_OCNPolarity = TIM_OCPolarity_High;
    oc.TIM_OCIdleState = TIM_OCIdleState_Set;
    oc.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		oc.TIM_Pulse = pwm->TIM_Pulse;

		//Chx TIMx
		switch (pwm->Chx)
		{
			case 1:
			{
				TIM_OC1Init(pwm->TIMx,&oc);
			}break;
			case 2:
			{
				TIM_OC2Init(pwm->TIMx,&oc);
			}break;
			case 3:
			{
				TIM_OC3Init(pwm->TIMx,&oc);
			}break;
		
			default:
			{
				TIM_OC4Init(pwm->TIMx,&oc);
			}break;
		}
		TIM_CtrlPWMOutputs(pwm->TIMx,ENABLE);
		TIM_Cmd(pwm->TIMx,ENABLE);//TIMx
	}
	else
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);

		gpio.GPIO_Mode	= GPIO_Mode_AF;
		gpio.GPIO_OType	= GPIO_OType_PP;
		gpio.GPIO_Pin		= pwm->GPIO_Pin_x;//GPIO_Pin_x
		gpio.GPIO_PuPd	= GPIO_PuPd_NOPULL;
		gpio.GPIO_Speed	= GPIO_Speed_100MHz;
		GPIO_Init(pwm->GPIOx,&gpio);//GPIOx

		Switch_GPIO_PinSource(pwm);
		GPIO_PinAFConfig(pwm->GPIOx,pwm->GPIO_PinSource,pwm->GPIO_AF);//GPIOx 
																																	//GPIO_PinSource 
																																	//GPIO_AF
		
		tim.TIM_Prescaler					=	pwm->Prescaler;//Prescaler
		tim.TIM_CounterMode				=	TIM_CounterMode_Up;
		tim.TIM_Period						= pwm->Period;//Period
		tim.TIM_ClockDivision			=	TIM_CKD_DIV1;
		tim.TIM_RepetitionCounter	=0;
		TIM_TimeBaseInit(pwm->TIMx,&tim);//TIMx
		
		oc.TIM_OCMode = TIM_OCMode_PWM1;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OutputNState = TIM_OutputNState_Enable;
    oc.TIM_OCPolarity = TIM_OCPolarity_High;
    oc.TIM_OCNPolarity = TIM_OCPolarity_High;
    oc.TIM_OCIdleState = TIM_OCIdleState_Set;
    oc.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
		oc.TIM_Pulse = pwm->TIM_Pulse;

		//Chx TIMx
		switch (pwm->Chx)
		{
			case 1:
			{
				TIM_OC1Init(pwm->TIMx,&oc);
				TIM_OC1PreloadConfig(pwm->TIMx,TIM_OCPreload_Enable);
			}break;
			case 2:
			{
				TIM_OC2Init(pwm->TIMx,&oc);
				TIM_OC2PreloadConfig(pwm->TIMx,TIM_OCPreload_Enable);
			}break;
			case 3:
			{
				TIM_OC3Init(pwm->TIMx,&oc);
				TIM_OC3PreloadConfig(pwm->TIMx,TIM_OCPreload_Enable);
			}break;
		
			default:
			{
				TIM_OC4Init(pwm->TIMx,&oc);
				TIM_OC4PreloadConfig(pwm->TIMx,TIM_OCPreload_Enable);
			}break;
		}
		TIM_ARRPreloadConfig(pwm->TIMx,ENABLE);//TIMx
		TIM_Cmd(pwm->TIMx,ENABLE);//TIMx
	}
}

void Switch_GPIO_PinSource(PWM_Set* pwm)
{
			switch(pwm->GPIO_Pin_x)
		{
			case GPIO_Pin_0: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource0;
			}break;
			case GPIO_Pin_1: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource1;
			}break;
			case GPIO_Pin_2: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource2;
			}break;
			case GPIO_Pin_3: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource3;
			}break;
			case GPIO_Pin_4: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource4;
			}break;
			case GPIO_Pin_5: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource5;
			}break;
			case GPIO_Pin_6: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource6;
			}break;
			case GPIO_Pin_7: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource7;
			}break;
			case GPIO_Pin_8: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource8;
			}break;
			case GPIO_Pin_9: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource9;
			}break;
			case GPIO_Pin_10: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource10;
			}break;
			case GPIO_Pin_11: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource11;
			}break;
			case GPIO_Pin_12: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource12;
			}break;
			case GPIO_Pin_13: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource13;
			}break;
			case GPIO_Pin_14: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource14;
			}break;
			default: 
			{
				pwm->GPIO_PinSource = GPIO_PinSource15;
			}break;
		}
}

