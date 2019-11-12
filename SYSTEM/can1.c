#include "main.h"

/*----CAN1_TX-----PB9----*/
/*----CAN1_RX-----PB8----*/

void CAN1_Configuration(void)
{
	/* -------------- Enable Module Clock Source ----------------------------*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	/* -------------- Configure GPIO & CAN1 ---------------------------------*/
	{
		GPIO_InitTypeDef       gpio;
		CAN_InitTypeDef        can1;
		CAN_FilterInitTypeDef  can1_filter;
		
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);

    gpio.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOA, &gpio);
	
		CAN_DeInit(CAN1);
    CAN_StructInit(&can1);
    
    can1.CAN_TTCM = DISABLE;
    can1.CAN_ABOM = DISABLE;
    can1.CAN_AWUM = DISABLE;
    can1.CAN_NART = DISABLE;
    can1.CAN_RFLM = DISABLE;
    can1.CAN_TXFP = ENABLE;
    can1.CAN_Mode = CAN_Mode_Normal;
    can1.CAN_SJW  = CAN_SJW_1tq;
    can1.CAN_BS1 = CAN_BS1_9tq;
    can1.CAN_BS2 = CAN_BS2_4tq;
    can1.CAN_Prescaler = 3;   //CAN BaudRate 42/(1+9+4)/3=1Mbps
    CAN_Init(CAN1, &can1);

	  can1_filter.CAN_FilterNumber=0;
	  can1_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
	  can1_filter.CAN_FilterScale=CAN_FilterScale_32bit;
	  can1_filter.CAN_FilterIdHigh=0x0000;
	  can1_filter.CAN_FilterIdLow=0x0000;
	  can1_filter.CAN_FilterMaskIdHigh=0x0000;
	  can1_filter.CAN_FilterMaskIdLow=0x0000;
	  can1_filter.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//the message which pass the filter save in fifo0
	  can1_filter.CAN_FilterActivation=ENABLE;
	  CAN_FilterInit(&can1_filter);
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
    CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);
	}
  /* -------------- Configure NVIC ----------------------------------------*/
	{
		NVIC_InitTypeDef       nvic;

    nvic.NVIC_IRQChannel = CAN1_RX0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 2;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    
    nvic.NVIC_IRQChannel = CAN1_TX_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);    
	}
}
/*************************************************************************
                          CAN1_TX_IRQHandler
描述：CAN1的发数中断函数
*************************************************************************/
void CAN1_TX_IRQHandler(void) //CAN TX
{
	if (CAN_GetITStatus(CAN1,CAN_IT_TME)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
  }
}
/*************************************************************************
                          CAN1_RX0_IRQHandler
描述：CAN1的接收中断函数
*************************************************************************/
void CAN1_RX0_IRQHandler(void)
{   
	CanRxMsg rx_message;
  if(CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
		CanReceiveMsgProcess(&rx_message);//信息处理
	}
}






