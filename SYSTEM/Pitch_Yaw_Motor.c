#include "main.h"

/*
云台控制,位置环与速度环控制
*/

float pitch_angle_dynamic_ref = 0.0f;
void Pitch_Motor_TASK(void)
{
	
		GMPPositionPID.kp = 300;//大的p环节，小的i环节，d环节一般不用
		GMPPositionPID.ki = 0.05;
		GMPPositionPID.kd = 0;
			
		GMPSpeedPID.kp = 5.0;
		GMPSpeedPID.ki = 0.02;
		GMPSpeedPID.kd = 0;
	  	 
		GMPPositionPID.ref = 0;//方向反加负号;
		GMPPositionPID.fdb = GMPitchEncoder.ecd_angle * GMPitchRamp.Calc(&GMPitchRamp);//增加一个斜坡函数  
		GMPPositionPID.Calc(&GMPPositionPID);   
		
		GMPSpeedPID.ref = GMPPositionPID.output;//方向反加负号
		GMPSpeedPID.fdb = Gyro[0];//变化最大的方向
		GMPSpeedPID.Calc(&GMPSpeedPID);
	
	  Set_Gimbal_Current(CAN1,(int16_t)(GMYPositionPID.output),(int16_t)(GMPPositionPID.output),(int16_t)(CM7SpeedPID.output)); 
	
}

float yaw_angle_dynamic_ref = 0.0f;
void Yaw_Motor_TASK(void)
{
	 	
	  GMYPositionPID.kp = 150;
		GMYPositionPID.ki =	0.02;
		GMYPositionPID.kd = 0;
			
		GMYSpeedPID.kp = 3.5;
		GMYSpeedPID.ki = 0.002;
		GMYSpeedPID.kd = 0;
    			
		GMYPositionPID.ref = 0;
		GMYPositionPID.fdb = GMYawEncoder.ecd_angle * GMYawRamp.Calc(&GMYawRamp); 
		GMYPositionPID.Calc(&GMYPositionPID); 
			  	
		GMYSpeedPID.ref = GMYPositionPID.output;
		GMYSpeedPID.fdb = -Gyro[2];
		GMYSpeedPID.Calc(&GMYSpeedPID);
	
	  Set_Gimbal_Current(CAN1,(int16_t)(GMYPositionPID.output),(int16_t)(GMPPositionPID.output),(int16_t)(CM7SpeedPID.output)); 
}
