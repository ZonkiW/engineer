#ifndef __YAOKONG_Configuration_H__
#define __YAOKONG_Configuration_H__
#include <stm32f4xx.h>

#define REMOTE_DMA_RX_BUF_LEN 30u

#define RC_FRAME_LENGTH       18u

void YAOKONG_Configuration(void);
void YAOKONG_Handle(uint8_t *pData);

#endif
