#ifndef __DATA_SEND_HANDLE_H__
#define __DATA_SEND_HANDLE_H__
#include <stm32f4xx.h>

extern unsigned char CRC8_INIT;
extern uint16_t CRC_INIT;

void data_pack_handle(uint16_t cmd_id, uint8_t *p_data, uint16_t len);
void Append_CRC8_Check_Sum(unsigned char*pchMessage,unsigned int dwLength);
void Append_CRC16_Check_Sum(uint8_t* pchMessage,uint32_t dwLength);
unsigned char Get_CRC8_Check_Sum(unsigned char *pchMessage,unsigned int dwLength,unsigned char ucCRC8);
uint16_t Get_CRC16_Check_Sum(uint8_t* pchMessage,uint32_t dwLength,uint16_t wCRC);
#endif
