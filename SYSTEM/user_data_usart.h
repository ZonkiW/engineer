#ifndef __USER_DATA_USART_H
#define __USER_DATA_USART_H
#include <main.h>

#define USART3_DMA_RX_BUF_LEN   88          //每级数组的长度
#define USART3_DMA_RX_buff 80           //应接受的数据量

extern uint8_t USART3_DMA1_RX_BUF[2][USART3_DMA_RX_BUF_LEN];
void user_uart_init(u32 bound);
void RingBuffer_Write(uint8_t data);
u8   RingBuffer_Read(uint8_t *pdata);
int Transform_Hex_To_Oct(int data,int len);
float solve_chengfang(float x,int n);
void getRobotPowerHeat(uint8_t *powerHeartData);

#endif
