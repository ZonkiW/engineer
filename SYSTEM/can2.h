#ifndef __CAN2_H__
#define __CAN2_H__
#include <stm32f4xx.h>

void CAN2_Configuration(void);
void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq);
void Set_Gimbal_Current(CAN_TypeDef *CANx, int16_t gimbal_yaw_iq, int16_t gimbal_pitch_iq, int16_t cm7_iq);
	
#endif 

