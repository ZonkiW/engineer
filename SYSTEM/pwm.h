#ifndef __PWM_H__
#define __PWM_H__
#include <stm32f4xx.h>

typedef struct PWM_Set
{
	uint32_t RCC_AHB1Periph;
	uint32_t GPIO_Pin_x;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_PinSource;
  uint8_t GPIO_AF;
	uint32_t Prescaler;
	uint32_t Period;
	TIM_TypeDef* TIMx;
	uint32_t TIM_Pulse;
	uint32_t Chx;
}PWM_Set;

void PWM_Configuration(void);
void PWM_Configuration_AUTO(PWM_Set* PWM);
void Switch_GPIO_PinSource(PWM_Set* PWM);

#endif

