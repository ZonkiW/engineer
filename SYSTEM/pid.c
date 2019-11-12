#include "main.h"
/*
pid计算
*/

void PID_Calc(struct PID_Regulator *pid) //增量式PID
{
	pid->err[0] = pid->ref - pid->fdb;
	
	if((pid->err[0] >= pid->jump_out) || (pid->err[0] < -pid->jump_out))
	{
		pid->componentKp = pid->kp * pid->err[0];
		VAL_LIMIT(pid->componentKp,-pid->componentKpMax,pid->componentKpMax)

		pid->componentKi+= pid->ki * pid->err[0];
		VAL_LIMIT(pid->componentKi,-pid->componentKiMax,pid->componentKiMax)
		if(pid->Reset_i == 1&& (pid->err[0] * pid->err[1] < 0))
		{
			pid->componentKi = 0;
		}
		
		pid->componentKd = pid->kd * ( pid->err[0] - pid->err[1] );
		VAL_LIMIT(pid->componentKd,-pid->componentKdMax,pid->componentKdMax)
		pid->componentoutput =pid->componentKp + pid->componentKi + pid->componentKd;
	}
	else
	{
		
	}
	pid->output = pid->componentoutput;
	VAL_LIMIT(pid->output,-pid->outputMax,pid->outputMax)
	
	pid->err[1] = pid->err[0];
}

void PID_Reset(PID_Regulator *pid)
{
	pid->ref 		= 0;
	pid->fdb		= 0;
	
	pid->err[0] = 0;
	pid->err[1]	= 0;

	pid->componentKp = 0;
	pid->componentKi = 0;
	pid->componentKd = 0;
	pid->componentoutput=0;
	pid->output			 = 0;
}

