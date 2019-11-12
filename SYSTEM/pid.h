#ifndef __PID_H__
#define __PID_H__
#include "BIANLIANG_Definition.h"


void PID_Calc(PID_Regulator *pid);
void PID_Reset(PID_Regulator *pid);

#endif
