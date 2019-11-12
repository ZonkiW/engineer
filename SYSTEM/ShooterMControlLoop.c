#include "main.h"

void ShooterMControlLoop(void)
{
											
			CM7PositionPID.kp = 40.0; //位置环
			CM7PositionPID.ki =	0.0;
			CM7PositionPID.kd = 0;
														
			CM7PositionPID.ref = 0;
			CM7PositionPID.fdb = CM7Encoder.ecd_angle;
			CM7PositionPID.Calc(&CM7PositionPID);
		
			CM7SpeedPID.kp = 40;  //速度环
			CM7SpeedPID.ki = 0.0;
			CM7SpeedPID.kd = 0;
		  								
			CM7SpeedPID.ref = CM7PositionPID.output;
			CM7SpeedPID.fdb = CM7Encoder.ecd_raw_rate;
			CM7SpeedPID.Calc(&CM7SpeedPID);
			
		  Set_Gimbal_Current(CAN1,(int16_t)(GMYSpeedPID.output),(int16_t)(GMPSpeedPID.output),(int16_t)(CM7SpeedPID.output)); 

}
