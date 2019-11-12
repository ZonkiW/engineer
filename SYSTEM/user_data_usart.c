#include "main.h" 
/**********************************************************
������������1��ʼ��
��  �ܣ���ʼ������1
��  �룺������
��  �أ���
��  ע��PB10 ->TX
				PB11 ->RX
**********************************************************/
FIFO_S_t* UART_TranFifo;
uint8_t USART3_DMA1_RX_BUF[2][USART3_DMA_RX_BUF_LEN];
void user_uart_init(u32 bound)
{
	/* -------------- Enable Module Clock Source ----------------------------*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //ʹ��GPIOBʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//ʹ��DMA1ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��
 /* -------------- Configure GPIO & USART3 -------------------------------*/
	{
		GPIO_InitTypeDef gpio;
		USART_InitTypeDef usart;
		//����1��Ӧ���Ÿ���ӳ��
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB11����ΪUSART3 
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11����ΪUSART3 
		//USART3�˿�����
		gpio.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//GPIOA9��GPIOA10
		gpio.GPIO_Mode = GPIO_Mode_AF;//���ù���
		gpio.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
		gpio.GPIO_OType = GPIO_OType_PP; //���츴�����
		gpio.GPIO_PuPd = GPIO_PuPd_UP; //����
		GPIO_Init(GPIOB,&gpio); //��ʼ��PB10��PB11

		//USART3 ��ʼ������
		USART_DeInit(USART3);
		USART_StructInit(&usart);
		usart.USART_BaudRate = bound;//����������
		usart.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		usart.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		usart.USART_Parity = USART_Parity_No;//����żУ��λ
		usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		usart.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;	//�շ�ģʽ
		USART_Init(USART3, &usart); //��ʼ������3
		
		USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//��������ж�
		USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���3
	}
	/* -------------- Configure DMA1_Stream1 --------------------------------*/
	{
		DMA_InitTypeDef dma;
		
		DMA_DeInit(DMA1_Stream1);
		DMA_StructInit(&dma);
		dma.DMA_Channel = DMA_Channel_4;
		dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
		dma.DMA_Memory0BaseAddr = (uint32_t)&USART3_DMA1_RX_BUF[0][0];        //����DMA���ڴ��Ŀ��λ�ã���DMA����Ҫ��ȡ����д���λ��
		dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
		dma.DMA_BufferSize = sizeof(USART3_DMA1_RX_BUF)/2;                    //���鳤��
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
		DMA_Init(DMA1_Stream1, &dma);
		
		//����Memory1,Memory0�ǵ�һ��ʹ�õ�Memory
		DMA_DoubleBufferModeConfig(DMA1_Stream1, (uint32_t)&USART3_DMA1_RX_BUF[1][0], DMA_Memory_0);   //first used memory configuration
		DMA_DoubleBufferModeCmd(DMA1_Stream1, ENABLE);
		
		DMA_Cmd(DMA1_Stream1, ENABLE);
	}
	/* -------------- Configure NVIC ----------------------------------------*/
	{
		NVIC_InitTypeDef nvic;
		//Usart1 NVIC ����
		nvic.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
		nvic.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�3
		nvic.NVIC_IRQChannelSubPriority =2;		//�����ȼ�3
		nvic.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&nvic);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	}
	 
	UART_TranFifo = FIFO_S_Create(100);  
  if(!UART_TranFifo)
   {
       // while(1);  avoid while in program
	 }
}

void USART3_IRQHandler(void)                	//����1�жϷ������
{
	int i,j;
	static uint32_t usart3_this_time_rx_len = 0;
	
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)//���ͼĴ������ж�
    {   
        if(!FIFO_S_IsEmpty(UART_TranFifo))
        {
        uint16_t data = (uint16_t)FIFO_S_Get(UART_TranFifo);
        USART_SendData(USART3, data);
        }
        else
        {
        USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
        }  
    }
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)      //���յ�����
	{
		//clear the idle pending flag 
		(void)USART3->SR;
		(void)USART3->DR;

		//Target is Memory0
		if(DMA_GetCurrentMemoryTarget(DMA1_Stream1) == 0)
		{
			DMA_Cmd(DMA1_Stream1, DISABLE);
			usart3_this_time_rx_len = USART3_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA1_Stream1);
			DMA1_Stream1->NDTR = (uint16_t)USART3_DMA_RX_BUF_LEN;     //relocate the dma memory pointer to the beginning position
			DMA1_Stream1->CR |= (uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 1
			DMA_Cmd(DMA1_Stream1, ENABLE);
      for(i=0;i<usart3_this_time_rx_len;i++)
			{
				RingBuffer_Write(USART3_DMA1_RX_BUF[0][i]);
			}
		}
		else //Target is Memory1
		{
			DMA_Cmd(DMA1_Stream1, DISABLE);
			usart3_this_time_rx_len = USART3_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA1_Stream1);
			DMA1_Stream1->NDTR = (uint16_t)USART3_DMA_RX_BUF_LEN;      //relocate the dma memory pointer to the beginning position
			DMA1_Stream1->CR &= ~(uint32_t)(DMA_SxCR_CT);                  //enable the current selected memory is Memory 0
			DMA_Cmd(DMA1_Stream1, ENABLE);
      for(i=0;i<usart3_this_time_rx_len;i++)
			{
				RingBuffer_Write(USART3_DMA1_RX_BUF[0][i]);
			}
		}
		 while(buffer.tailPosition!=buffer.headPosition)
		{
			if(buffer.tailPosition-buffer.headPosition>=0) Tail_Over_Zero_Value=0;   //δ�����
			else                                           Tail_Over_Zero_Value=100; //ͨ�����
			
			if(buffer.headPosition>=96&&buffer.headPosition<=99)  Head_Over_Zero_Value = 100;//�����Ԫ��ͷָ������
			else                                                  Head_Over_Zero_Value = 0;  //�����Ԫ��ͷָ��δ�����
				
			for(j=0;j<5;j++)   //ȡ��֡ͷ
			{
				RingBuffer_Read(Save_Element_Array+j);
			}
			CRC8_Ref_Value   = Save_Element_Array[4];
			CRC8_Solve_Value = Get_CRC8_Check_Sum(Save_Element_Array,4,0xff);
			if(CRC8_Ref_Value == CRC8_Solve_Value)  //֡ͷͨ��CRC8У��
			{
				data_Length = Save_Element_Array[1]|Save_Element_Array[2]<<8;//����������������Ϊ�˷�����1��
				data_Length = Transform_Hex_To_Oct(data_Length,16);
					
				if(buffer.tailPosition+Tail_Over_Zero_Value-(Head_Over_Zero_Value+buffer.headPosition-5)>=5+2+data_Length+2)
				{
					for(j=0;j<data_Length+2+2;j++)
					{
						RingBuffer_Read(Save_Element_Array+5+j);
					}
					CRC16_Ref_Value   = Save_Element_Array[5+2+data_Length+2-2]|Save_Element_Array[5+2+data_Length+2-1]<<8;
					CRC16_Solve_Value = Get_CRC16_Check_Sum(Save_Element_Array,7+data_Length+2-2,0xffff);
					if(CRC16_Ref_Value == CRC16_Solve_Value)  //ͨ��CRC16У��
					{
						if(Save_Element_Array[5]==0x01&&Save_Element_Array[6]==0x00)
						{
							//getRobotState(Save_Element_Array);//��ȡ������Ѫ��ֵ
							//debug1++;
						}
						
						if(Save_Element_Array[5]==0x02&&Save_Element_Array[6]==0x00)
						{
							//getRobotHurt(Save_Element_Array);
							//debug2++;
						}
						
						if(Save_Element_Array[5]==0x03&&Save_Element_Array[6]==0x00)
						{
							//getRobotShootData(Save_Element_Array);
							//debug3++;
						}
						
						if(Save_Element_Array[5]==0x04&&Save_Element_Array[6]==0x00)
						{
							getRobotPowerHeat(Save_Element_Array);//��ȡ����
							//debug4++;
							
						}
						
						if(Save_Element_Array[5]==0x05&&Save_Element_Array[6]==0x00)
						{
							//getRobotState(Save_Element_Array);//��ȡ������Ѫ��ֵ
							//debug5++;
						}
						
						if(Save_Element_Array[5]==0x06&&Save_Element_Array[6]==0x00)
						{
							//getRobotHurt(Save_Element_Array);
							//debug6++;
						}
						
						if(Save_Element_Array[5]==0x07&&Save_Element_Array[6]==0x00)
						{
							//getRobotShootData(Save_Element_Array);
							//debug7++;
						}
						
						if(Save_Element_Array[5]==0x08&&Save_Element_Array[6]==0x00)
						{
							//getRobotPowerHeat(Save_Element_Array);//��ȡ17mm����ǹ������
							//debug8++;
						}
						
						if(Save_Element_Array[5]==0x00&&Save_Element_Array[6]==0x01)
						{
							//getRobotPowerHeat(Save_Element_Array);//��ȡ17mm����ǹ������
							//debug10++;
						}
					}
				}
				else
				{
					buffer.headPosition = Head_Over_Zero_Value+buffer.headPosition-5;
					break;
				}
			}
	  }
	}
} 


/***
������void RingBuffer_Write(uint8_t data)
���ܣ�������dataд�뻷�ζ���buffer.ringBuf��
��ע����
***/
void RingBuffer_Write(uint8_t data)
{
	buffer.ringBuf[buffer.tailPosition] = data;     //��β��׷��
	if(++buffer.tailPosition>=BUFFER_MAX)           //β�ڵ�ƫ��
		buffer.tailPosition = 0;                      //����������󳤶ȣ����㣬�γɻ��ζ���
	if(buffer.tailPosition == buffer.headPosition)  //���β���ڵ�׷��ͷ���ڵ㣬���޸�ͷ���ƫ��λ�ö�����������
		if(++buffer.headPosition>=BUFFER_MAX)
			buffer.headPosition = 0;
}

/***
������u8 RingBuffer_Read(uint8_t *pdata)
���ܣ��ӻ��ζ���buffer.ringBuf�ж�ȡ���ݵ���ַpdata��
��ע����
***/
u8 RingBuffer_Read(uint8_t *pdata)
{
	if(buffer.headPosition == buffer.tailPosition)  //���ͷβ�Ӵ���ʾ������Ϊ��
	{
		return 1;  //����1�����λ������ǿյ�
	}
	else
	{
		*pdata = buffer.ringBuf[buffer.headPosition];  //����������ǿ���ȡͷ�ڵ�ֵ��ƫ��ͷ�ڵ�
		if(++buffer.headPosition>=BUFFER_MAX)
			buffer.headPosition = 0;
		return 0;   //����0����ʾ��ȡ���ݳɹ�
	}
	
}

/***
������int Transform_Hex_To_Oct(int data,int len)
���ܣ�16������ת����10������
��ע��data:16���Ƹ�ʽ  len��data��2����λ��
***/
int Transform_Hex_To_Oct(int data,int len)
{
	int a=0x0001,temp=0;
	int ans=0;
	for(int i=0;i<len;i++)
	{
		temp=(data&(a<<i))>>i;
		ans = ans + temp*solve_chengfang(2,i);
	}
	return ans;
}

/*******************
���ܣ��˷����㺯��
��ڲ�����x--����
          n--ָ��
����ֵ���˷�����ֵ
*********************/
float solve_chengfang(float x,int n)         
{
	int i;
	int a;
	float s=1.0;
	if(n>=0) a=n;
	if(n<0) a=-n;
	for(i=1;i<=a;i++)
		s*=x;
	if(n>=0)
	   return s;
	if(n<0)
	  return 1/s;
	return 0;
}

/***
������void getRobotPowerHeat(uint8_t *powerHeartData)
���ܣ��Ӳ���ϵͳ��ȡʵʱ������������
��ע��ID��0x0004   50HzƵ�����ڷ���
      ��29�����ݣ��±�23��24Ϊ17mm����ǹ����������
***/
void getRobotPowerHeat(uint8_t *powerHeartData)//15,16,17,18
{
	int tempReferrrData[44];
	for(int temp_num=0;temp_num<44;temp_num++)
       tempReferrrData[temp_num]=powerHeartData[temp_num];
	int V_array[4];                       //��ѹֵ����
	long int v_temp_value;                //32λ����
	int V_jiema;                          //����
	long int V_weishu;                    //β��
	float V_value;                        //ʮ����С����ʾ�ĵ�ѹֵ
	int V_every_bit;                       //ȡ��ѹβ����ÿһλ

//	int I_array[4];                       //��ѹֵ����
//	long int I_temp_value;                //32λ����
//	int I_jiema;                          //����
//	long int I_weishu;                    //β��
//	float I_value;                        //ʮ����С����ʾ�ĵ���ֵ
//	int I_every_bit;                      //ȡ����β����ÿһλ

//	float P_value;                        //���̹���
	
	for(int V_j=0;V_j<4;V_j++)
    V_array[V_j]=tempReferrrData[V_j+15];//7��ѹ��11������15����
	v_temp_value=(V_array[0]<<0)|(V_array[1]<<8)|(V_array[2]<<16)|(V_array[3]<<24);//������϶�������ʽ��ʾ�ĵ�ѹֵ
	V_jiema=((v_temp_value&0X7F800000)>>23)-127;     //����n
  V_weishu=v_temp_value&0X007FFFFF;
	for(int a=0;a<24;a++)
	{
		if(a==0) {V_value=1*solve_chengfang(2,V_jiema);}
    else 
		{
		V_every_bit=(V_weishu&(0X00400000>>(a-1)))>>(23-a);
    V_value=V_value+V_every_bit*solve_chengfang(2,V_jiema-a);
		}	
	}
	P_value=V_value;
}


void UART3_PrintCh(uint8_t ch)//�ַ�����
{    
    FIFO_S_Put(UART_TranFifo, ch);//
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
    
}

void UART3_PrintBlock(uint8_t* pdata, uint8_t len)//���鷢��
{
	uint8_t i = 0;
    for(i = 0; i < len; i++)
    {
        FIFO_S_Put(UART_TranFifo, pdata[i]);//
    }
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);//���ͼĴ������ж�
}

int fputc(int ch, FILE *f)//ѭ������
{
    while (USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3, (uint8_t)ch);
    return ch;
}


