#include "main.h" 
/**********************************************************
函数名：串口1初始化
功  能：初始化串口1
输  入：波特率
返  回：无
备  注：PB10 ->TX
				PB11 ->RX
**********************************************************/
FIFO_S_t* UART_TranFifo;
uint8_t USART3_DMA1_RX_BUF[2][USART3_DMA_RX_BUF_LEN];
void user_uart_init(u32 bound)
{
	/* -------------- Enable Module Clock Source ----------------------------*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//使能DMA1时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//使能USART3时钟
 /* -------------- Configure GPIO & USART3 -------------------------------*/
	{
		GPIO_InitTypeDef gpio;
		USART_InitTypeDef usart;
		//串口1对应引脚复用映射
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //GPIOB11复用为USART3 
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); //GPIOB11复用为USART3 
		//USART3端口配置
		gpio.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//GPIOA9与GPIOA10
		gpio.GPIO_Mode = GPIO_Mode_AF;//复用功能
		gpio.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
		gpio.GPIO_OType = GPIO_OType_PP; //推挽复用输出
		gpio.GPIO_PuPd = GPIO_PuPd_UP; //上拉
		GPIO_Init(GPIOB,&gpio); //初始化PB10，PB11

		//USART3 初始化设置
		USART_DeInit(USART3);
		USART_StructInit(&usart);
		usart.USART_BaudRate = bound;//波特率设置
		usart.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		usart.USART_StopBits = USART_StopBits_1;//一个停止位
		usart.USART_Parity = USART_Parity_No;//无奇偶校验位
		usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		usart.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;	//收发模式
		USART_Init(USART3, &usart); //初始化串口3
		
		USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
		USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//开启相关中断
		USART_Cmd(USART3, ENABLE);  //使能串口3
	}
	/* -------------- Configure DMA1_Stream1 --------------------------------*/
	{
		DMA_InitTypeDef dma;
		
		DMA_DeInit(DMA1_Stream1);
		DMA_StructInit(&dma);
		dma.DMA_Channel = DMA_Channel_4;
		dma.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
		dma.DMA_Memory0BaseAddr = (uint32_t)&USART3_DMA1_RX_BUF[0][0];        //定义DMA在内存的目标位置，即DMA即将要读取或者写入的位置
		dma.DMA_DIR = DMA_DIR_PeripheralToMemory;
		dma.DMA_BufferSize = sizeof(USART3_DMA1_RX_BUF)/2;                    //数组长度
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
		
		//配置Memory1,Memory0是第一个使用的Memory
		DMA_DoubleBufferModeConfig(DMA1_Stream1, (uint32_t)&USART3_DMA1_RX_BUF[1][0], DMA_Memory_0);   //first used memory configuration
		DMA_DoubleBufferModeCmd(DMA1_Stream1, ENABLE);
		
		DMA_Cmd(DMA1_Stream1, ENABLE);
	}
	/* -------------- Configure NVIC ----------------------------------------*/
	{
		NVIC_InitTypeDef nvic;
		//Usart1 NVIC 配置
		nvic.NVIC_IRQChannel = USART3_IRQn;//串口1中断通道
		nvic.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
		nvic.NVIC_IRQChannelSubPriority =2;		//子优先级3
		nvic.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&nvic);	//根据指定的参数初始化VIC寄存器、
	}
	 
	UART_TranFifo = FIFO_S_Create(100);  
  if(!UART_TranFifo)
   {
       // while(1);  avoid while in program
	 }
}

void USART3_IRQHandler(void)                	//串口1中断服务程序
{
	int i,j;
	static uint32_t usart3_this_time_rx_len = 0;
	
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)//发送寄存器空中断
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
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)      //接收到数据
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
			if(buffer.tailPosition-buffer.headPosition>=0) Tail_Over_Zero_Value=0;   //未过零点
			else                                           Tail_Over_Zero_Value=100; //通过零点
			
			if(buffer.headPosition>=96&&buffer.headPosition<=99)  Head_Over_Zero_Value = 100;//读五个元素头指针过零点
			else                                                  Head_Over_Zero_Value = 0;  //读五个元素头指针未过零点
				
			for(j=0;j<5;j++)   //取出帧头
			{
				RingBuffer_Read(Save_Element_Array+j);
			}
			CRC8_Ref_Value   = Save_Element_Array[4];
			CRC8_Solve_Value = Get_CRC8_Check_Sum(Save_Element_Array,4,0xff);
			if(CRC8_Ref_Value == CRC8_Solve_Value)  //帧头通过CRC8校验
			{
				data_Length = Save_Element_Array[1]|Save_Element_Array[2]<<8;//本该用两个变量，为了方便用1个
				data_Length = Transform_Hex_To_Oct(data_Length,16);
					
				if(buffer.tailPosition+Tail_Over_Zero_Value-(Head_Over_Zero_Value+buffer.headPosition-5)>=5+2+data_Length+2)
				{
					for(j=0;j<data_Length+2+2;j++)
					{
						RingBuffer_Read(Save_Element_Array+5+j);
					}
					CRC16_Ref_Value   = Save_Element_Array[5+2+data_Length+2-2]|Save_Element_Array[5+2+data_Length+2-1]<<8;
					CRC16_Solve_Value = Get_CRC16_Check_Sum(Save_Element_Array,7+data_Length+2-2,0xffff);
					if(CRC16_Ref_Value == CRC16_Solve_Value)  //通过CRC16校验
					{
						if(Save_Element_Array[5]==0x01&&Save_Element_Array[6]==0x00)
						{
							//getRobotState(Save_Element_Array);//读取机器人血量值
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
							getRobotPowerHeat(Save_Element_Array);//读取功率
							//debug4++;
							
						}
						
						if(Save_Element_Array[5]==0x05&&Save_Element_Array[6]==0x00)
						{
							//getRobotState(Save_Element_Array);//读取机器人血量值
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
							//getRobotPowerHeat(Save_Element_Array);//读取17mm弹丸枪口热量
							//debug8++;
						}
						
						if(Save_Element_Array[5]==0x00&&Save_Element_Array[6]==0x01)
						{
							//getRobotPowerHeat(Save_Element_Array);//读取17mm弹丸枪口热量
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
函数：void RingBuffer_Write(uint8_t data)
功能：将数据data写入环形队列buffer.ringBuf中
备注：无
***/
void RingBuffer_Write(uint8_t data)
{
	buffer.ringBuf[buffer.tailPosition] = data;     //从尾部追加
	if(++buffer.tailPosition>=BUFFER_MAX)           //尾节点偏移
		buffer.tailPosition = 0;                      //大于数组最大长度，归零，形成环形队列
	if(buffer.tailPosition == buffer.headPosition)  //如果尾部节点追到头部节点，则修改头结点偏移位置丢弃早期数据
		if(++buffer.headPosition>=BUFFER_MAX)
			buffer.headPosition = 0;
}

/***
函数：u8 RingBuffer_Read(uint8_t *pdata)
功能：从环形队列buffer.ringBuf中读取数据到地址pdata中
备注：无
***/
u8 RingBuffer_Read(uint8_t *pdata)
{
	if(buffer.headPosition == buffer.tailPosition)  //如果头尾接触表示缓冲区为空
	{
		return 1;  //返回1，环形缓冲区是空的
	}
	else
	{
		*pdata = buffer.ringBuf[buffer.headPosition];  //如果缓冲区非空则取头节点值并偏移头节点
		if(++buffer.headPosition>=BUFFER_MAX)
			buffer.headPosition = 0;
		return 0;   //返回0，表示读取数据成功
	}
	
}

/***
函数：int Transform_Hex_To_Oct(int data,int len)
功能：16进制数转换成10进制数
备注：data:16进制格式  len：data中2进制位数
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
功能：乘方计算函数
入口参数：x--底数
          n--指数
返回值：乘方计算值
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
函数：void getRobotPowerHeat(uint8_t *powerHeartData)
功能：从裁判系统读取实时功率热量数据
备注：ID：0x0004   50Hz频率周期发送
      共29个数据，下标23，24为17mm弹丸枪口热量数据
***/
void getRobotPowerHeat(uint8_t *powerHeartData)//15,16,17,18
{
	int tempReferrrData[44];
	for(int temp_num=0;temp_num<44;temp_num++)
       tempReferrrData[temp_num]=powerHeartData[temp_num];
	int V_array[4];                       //电压值数组
	long int v_temp_value;                //32位变量
	int V_jiema;                          //阶码
	long int V_weishu;                    //尾数
	float V_value;                        //十进制小数表示的电压值
	int V_every_bit;                       //取电压尾数的每一位

//	int I_array[4];                       //电压值数组
//	long int I_temp_value;                //32位变量
//	int I_jiema;                          //阶码
//	long int I_weishu;                    //尾数
//	float I_value;                        //十进制小数表示的电流值
//	int I_every_bit;                      //取电流尾数的每一位

//	float P_value;                        //底盘功率
	
	for(int V_j=0;V_j<4;V_j++)
    V_array[V_j]=tempReferrrData[V_j+15];//7电压，11电流，15功率
	v_temp_value=(V_array[0]<<0)|(V_array[1]<<8)|(V_array[2]<<16)|(V_array[3]<<24);//倒序组合二进制形式表示的电压值
	V_jiema=((v_temp_value&0X7F800000)>>23)-127;     //阶码n
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


void UART3_PrintCh(uint8_t ch)//字符发送
{    
    FIFO_S_Put(UART_TranFifo, ch);//
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
    
}

void UART3_PrintBlock(uint8_t* pdata, uint8_t len)//数组发送
{
	uint8_t i = 0;
    for(i = 0; i < len; i++)
    {
        FIFO_S_Put(UART_TranFifo, pdata[i]);//
    }
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);//发送寄存器空中断
}

int fputc(int ch, FILE *f)//循环发送
{
    while (USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
    USART_SendData(USART3, (uint8_t)ch);
    return ch;
}


