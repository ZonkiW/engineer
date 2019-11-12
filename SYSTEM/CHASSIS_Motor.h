#ifndef __CHASSIS_Motor_H
#define __CHASSIS_Motor_H
#include <main.h>

void CHASSIS_Motor_TASK(void);
//int SPEED_HANDLE(Encoder encoder,int angle_ref);
void POSITION_LIMIT(double* angle_ref,Encoder encoder,double angle_dif);
void CM_OUTPUT(void);
void STATE_CHANGE(void);
void LEG_STATE_HANDLE(void);
void CHASIS_calculate(void);

#endif
