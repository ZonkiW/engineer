#include "main.h"
 
  void TASK_Init()
{
//----------------------------------------PA2�ȵ�ŷ�PA3צ�ӵ�ŷ�-----------------------------------------
    GPIO_InitTypeDef       GPIOA23;//��ŷ�
				
    GPIOA23.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIOA23.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOA, &GPIOA23);
		
		PA2_low();
		PA3_low();
//--------------------------------------------PA1צ�ӵ�ŷ�----------------------------------
	  GPIO_InitTypeDef       GPIOA1;//��ŷ�
				
    GPIOA1.GPIO_Pin = GPIO_Pin_1;
    GPIOA1.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOA, &GPIOA1);
		
		PA1_low();
//------------------------------------------------------------------------------
//	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOFʱ��
//	  GPIO_InitTypeDef       GPIOC3;//��ŷ�
//				
//    GPIOC3.GPIO_Pin = GPIO_Pin_3;
//    GPIOC3.GPIO_Mode= GPIO_Mode_OUT;
//	  //GPIOC3.GPIO_OType = GPIO_OType_PP;//�������
//   // GPIOC3.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//    GPIOC3.GPIO_PuPd = GPIO_PuPd_UP;//����
//    GPIO_Init(GPIOC, &GPIOC3);
//		
//		PC3_high();
//-----------------------------------------PC1����-----------------
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOFʱ��
	  GPIO_InitTypeDef       GPIOC1;//��ŷ�
				
    GPIOC1.GPIO_Pin = GPIO_Pin_1;
    GPIOC1.GPIO_Mode= GPIO_Mode_OUT;
    GPIOC1.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOC, &GPIOC1);
		
		PC1_low();
//------------------------------------------PC2צ�Ӽ�ȡ��ŷ�-------------------------------
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOFʱ��
	  GPIO_InitTypeDef       GPIOC2;//��ŷ�
				
    GPIOC2.GPIO_Pin = GPIO_Pin_2;
    GPIOC2.GPIO_Mode= GPIO_Mode_OUT;
    GPIOC2.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOC, &GPIOC2);
		
		PC2_low();
//-----------------------------------------צ���м�λ�ù���-------------	
	  GPIO_InitTypeDef       GPIOB9;
				
    GPIOB9.GPIO_Pin = GPIO_Pin_9;
    GPIOB9.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOB, &GPIOB9);
//------------------------------PA9ǰ�ù���----------------------------------
	  GPIO_InitTypeDef       GPIOA9;
				
    GPIOA9.GPIO_Pin = GPIO_Pin_9;
    GPIOA9.GPIO_Mode = GPIO_Mode_IN;
		GPIO_Init(GPIOA, &GPIOA9);
//--------------------------------PA10���ù���--------------------------------
    GPIO_InitTypeDef       GPIOA10;
		
    GPIOA10.GPIO_Pin = GPIO_Pin_10;
    GPIOA10.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOA, &GPIOA10);
//--------------------------------PA8���ù���--------------------------------
    GPIO_InitTypeDef       GPIOA8;
		
    GPIOA8.GPIO_Pin = GPIO_Pin_8;
    GPIOA8.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOA, &GPIOA8);
//------------------------------------------б��-------------------------------------
    LRSpeedRamp.SetScale(&LRSpeedRamp,500);
	  FBSpeedRamp.SetScale(&FBSpeedRamp,500);
	  RoSpeedRamp.SetScale(&RoSpeedRamp,500);
		LOCA_SpeedRamp.SetScale(&LOCA_SpeedRamp,500);
	  CM8_9ramp  . SetScale(&CM8_9ramp,800);
	  CM10_11ramp. SetScale(&CM10_11ramp,800);
	  CM12_13ramp. SetScale(&CM12_13ramp,800);
	  CM14ramp   . SetScale(&CM14ramp,800);
		paw_up_ramp.SetScale(&paw_up_ramp,100); //DEBUG
		paw_down_ramp.SetScale(&paw_down_ramp,100);
		paw_init_ramp.SetScale(&paw_init_ramp,100); 
}
