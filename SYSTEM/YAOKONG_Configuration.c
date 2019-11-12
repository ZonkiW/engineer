#include "main.h"

static uint8_t REMOTE_DMA_RX_BUF[2][REMOTE_DMA_RX_BUF_LEN];

void YAOKONG_Configuration(void)
{
	/* -------------- Enable Module Clock Source ----------------------------*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	/* -------------- Configure GPIO & USART1 -------------------------------*/
	{
		GPIO_InitTypeDef gpio;
		USART_InitTypeDef usart;
		
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
		
		GPIO_StructInit(&gpio);
		gpio.GPIO_Pin = GPIO_Pin_7;
		gpio.GPIO_Mode = GPIO_Mode_AF;
		gpio.GPIO_Speed = GPIO_Speed_2MHz;
		gpio.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &gpio);
		
		USART_DeInit(USART1);
		USART_StructInit(&usart);
		usart.USART_BaudRate =100000;
		usart.USART_WordLength = USART_WordLength_8b;
		usart.USART_StopBits = USART_StopBits_1;
		usart.USART_Parity = USART_Parity_Even;
		usart.USART_Mode = USART_Mode_Rx;
		usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_Init(USART1, &usart);
		
		USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);        //usart rx idle interrupt  enabled
		USART_Cmd(USART1, ENABLE);
	}
	/* -------------- Configure DMA2_Stream5 --------------------------------*/
	{
		DMA_InitTypeDef dma;
		
		DMA_DeInit(DMA2_Stream5);
		DMA_StructInit(&dma);
		dma.DMA_Channel = DMA_Channel_4;
		dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);
		dma.DMA_Memory0BaseAddr = (uint32_t)&REMOTE_DMA_RX_BUF[0][0];
		dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
		dma.DMA_BufferSize = sizeof(REMOTE_DMA_RX_BUF)/2;
		dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
		dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
		dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
		dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
		dma.DMA_Mode = DMA_Mode_Circular;
		dma.DMA_Priority = DMA_Priority_Medium;
		dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
		dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
		dma.DMA_MemoryBurst = DMA_MemoryBurst_Single;
		dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
		DMA_Init(DMA2_Stream5, &dma);
		
		//����Memory1,Memory0�ǵ�һ��ʹ�õ�Memory
		DMA_DoubleBufferModeConfig(DMA2_Stream5, (uint32_t)&REMOTE_DMA_RX_BUF[1][0], DMA_Memory_0);   //first used memory configuration
		DMA_DoubleBufferModeCmd(DMA2_Stream5, ENABLE);
		
		DMA_Cmd(DMA2_Stream5, ENABLE);
	}
	/* -------------- Configure NVIC ----------------------------------------*/
	{
		NVIC_InitTypeDef nvic;
		nvic.NVIC_IRQChannel = USART1_IRQn;                          
		nvic.NVIC_IRQChannelPreemptionPriority = 0;   //pre-emption priority 
		nvic.NVIC_IRQChannelSubPriority = 0;		    //subpriority 
		nvic.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&nvic);	
	}
}


void USART1_IRQHandler(void)//DMA˫���壬һ�����������ݣ�һ�����������ݣ������ڴ������ݴ���
{
	static uint32_t usart1_this_time_rx_len = 0;
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		//��ռĴ��������Ǻ�������
		(void)USART1->SR;
		(void)USART1->DR;
    REMOTE_LOSE_COUT=0; //�˱������ڼ�ͣ���ص�ң�����󣬳�ͣ��
		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(DMA2_Stream5) == 0)//��ǰ����Ŀ��Ϊ0��
		{
			DMA_Cmd(DMA2_Stream5, DISABLE);
			usart1_this_time_rx_len = REMOTE_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream5);
			DMA2_Stream5->NDTR = (uint16_t)REMOTE_DMA_RX_BUF_LEN;     //relocate the dma memory pointer to the beginning position
			DMA2_Stream5->CR |= (uint32_t)(DMA_SxCR_CT);                  //����Ŀ��תΪ1��
			DMA_Cmd(DMA2_Stream5, ENABLE);
      if(usart1_this_time_rx_len == RC_FRAME_LENGTH) //���յ���Ϣ��������д���
			{
				YAOKONG_Handle(REMOTE_DMA_RX_BUF[0]);
			}
		}
		else //Target is Memory1
		{
			DMA_Cmd(DMA2_Stream5, DISABLE);
			usart1_this_time_rx_len = REMOTE_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream5);
			DMA2_Stream5->NDTR = (uint16_t)REMOTE_DMA_RX_BUF_LEN;      //relocate the dma memory pointer to the beginning position
			DMA2_Stream5->CR &= ~(uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 0
			DMA_Cmd(DMA2_Stream5, ENABLE);
      if(usart1_this_time_rx_len == RC_FRAME_LENGTH)
			{
				YAOKONG_Handle(REMOTE_DMA_RX_BUF[1]);
			}
		}
	}
}



void YAOKONG_Handle(uint8_t *pData)
{

	if(pData == NULL)
	{
			return;
	}
	
	ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; //ң����ͨ��0����������ƽ��
	ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;//ң����ͨ��1������ǰ������
	ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) | ((int16_t)pData[4] << 10)) & 0x07FF;//ң����ͨ��2��������ת
	ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;//ң����ͨ��3�����Ƹ���
  s1  = ((pData[5] >> 4) & 0x000C) >> 2;//ң������߿��أ���3����λ��ң��������ģʽ�����ã���� RemoteShootControl
	s2  = ((pData[5] >> 4) & 0x0003);//ң�����ұ߿��أ���3����λ������Ϊǿ��ֹͣ������Ϊң�������ƣ��м�Ϊ���̿���
	
	mouse_left_right_slide= ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);//�������
	mouse_up_down_slide= ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);//�������
	press_l = pData[12];//������
  press_r = pData[13];//����Ҽ�

	key= ((int16_t)pData[14]) | ((int16_t)pData[15] << 8);//ÿһλ��Ӧһ������
  	
		
	remote_forward_back_ref   = (ch1 - remote_middle)*remote_forward_back_rat;//�õ�ǰ���ٶ�
	remote_left_right_ref     = (ch0 - remote_middle)*remote_left_right_rat; //�õ������ٶ�
	remote_rotate_ref				  = (ch2 - remote_middle)*remote_rotate_rat; //�õ���ת�ٶ�
 	
}
/**  ��Ϊ���°������Ӧ��keyֵ
0x0001:w 
0x0002:s 
0x0004:a 
0x0008:d 

0x0010:shift 
0x0020:ctrl 
0x0040:q 
0x0080:e 

0x0100:r 
0x0200:f 
0x0400:g 
0x0800:z 

0x1000:x 
0x2000:c 
0x4000:v 
0x8000:b
**/


