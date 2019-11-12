#ifndef _RAMP__H_
#define _RAMP__H_
#include <stm32f4xx.h>
#include "BIANLIANG_Definition.h"


						
void RampInit(RampGen_t *ramp, int32_t XSCALE);
float RampCalc(RampGen_t *ramp);
void RampSetCounter(struct RampGen_t *ramp, int32_t count);
void RampResetCounter(struct RampGen_t *ramp);
void RampSetScale(struct RampGen_t *ramp, int32_t scale);
uint8_t RampIsOverflow(struct RampGen_t *ramp);

#endif

