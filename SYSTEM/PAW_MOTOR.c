#include <main.h>

void PAW_Motor_TASK(void)
{
	CM8SpeedPID.componentKpMax=8000; //8000
	CM8SpeedPID.componentKiMax=4000; // 4000
	CM8SpeedPID.componentKdMax=0; //0
	CM9SpeedPID.componentKpMax=8000; //8000
	CM9SpeedPID.componentKiMax=4000; // 4000
	CM9SpeedPID.componentKdMax=0; //0
	CM8SpeedPID.outputMax=CM9SpeedPID.outputMax=12000;
	switch(paw_cylinder_state)//夹紧松开
	{
	  case OPEN_STATE:
		{
		  PC2_low();
		}break;
		
		case CLOSE_STATE:
		{
			PC2_high();	
		}	
	}
	
	switch(paw_hori_state)//水平夹取箱子位置
	{
	  case FIRST_STATE:
		{
		 PA1_low(); 
		 PA3_high();
		 paw_second_changable=yes;
		}break;
		
		case SECOND_STATE:
		{
      if((PB9==0)&&(paw_second_changable==yes))
			{
			 PA1_low();
			 PA3_high();
			}			
      if(PB9==1)
			{
			 PA1_low();
			 PA3_low();
			 paw_second_changable=no;
			}				
		}break;
	
	  case THIRD_STATE:
		{
		 	PA1_high();	
			PA3_low();
			paw_second_changable=yes;
		}break;
	}
	
  paw_ramp();	
	
	switch(paw_verti_state) //箱子抬起放下
	{
	  case PAW_DOWN_STATE:
		{
		 CM8SpeedPID.outputMax=CM9SpeedPID.outputMax=4500;
			
	   CM8PositionPID.ref=paw_up_position+65*paw_down_ramp.Calc(&paw_down_ramp);//-65
		 VAL_LIMIT(CM8PositionPID.ref, -130, -65)	
			
	   CM9PositionPID.ref=-CM8PositionPID.ref;
		 paw_up_ramp.ResetCounter(&paw_up_ramp);	
		}break;
		
		case PAW_UP_STATE:
		{
  	 CM8PositionPID.ref=paw_down_position+(-65)*paw_up_ramp.Calc(&paw_up_ramp);//-130
		 VAL_LIMIT(CM8PositionPID.ref, -130, -65)	
			
	   CM9PositionPID.ref=-CM8PositionPID.ref;
		 paw_down_ramp.ResetCounter(&paw_down_ramp);
		}break;
		
		case PAW_CONTROL_STATE://手控操作
		{
		 	if(key==C_ID)
			{
			  paw_ref+=0.35;
			}
			else if(key==C_SHIFT_ID)
			{
			 	paw_ref-=0.35;		
			}
		 VAL_LIMIT(paw_ref, -130, -65)	
		 CM8PositionPID.ref=paw_ref;
	   CM9PositionPID.ref=-paw_ref;
		}break;
		
		case PAW_INIT_STATE://初始位置
		{
		 CM8SpeedPID.outputMax=CM9SpeedPID.outputMax=1000;
	   CM8PositionPID.ref=paw_init_position; 
	   CM9PositionPID.ref=-paw_init_position;
		} break;
 	}	
	
	 CM8PositionPID.kp =PAW_Positionkp;  CM8SpeedPID.kp = PAW_SpeedPIDkp;   CM8SpeedPID.ki = PAW_SpeedPIDki;
   CM9PositionPID.kp =PAW_Positionkp;  CM9SpeedPID.kp = PAW_SpeedPIDkp;   CM9SpeedPID.ki = PAW_SpeedPIDki;	
	
	 CM8PositionPID.fdb=CM8Encoder.ecd_angle;
	 CM9PositionPID.fdb=CM9Encoder.ecd_angle;
	
	 CM8PositionPID.Calc(&CM8PositionPID);
	 CM9PositionPID.Calc(&CM9PositionPID);
	
   CM8SpeedPID.ref=CM8PositionPID.output;
	 CM9SpeedPID.ref=CM9PositionPID.output;
	
	 CM8SpeedPID.fdb=CM8Encoder.filter_rate;
	 CM9SpeedPID.fdb=CM9Encoder.filter_rate;
	
	 CM8SpeedPID.Calc(&CM8SpeedPID);
   CM9SpeedPID.Calc(&CM9SpeedPID);

}	

void TRAILER_Motor_TASK(void)
{

	 VAL_LIMIT(CM7PositionPID.ref, 0, 130)//130	
   CM7PositionPID.kp =TRAILER_Positionkp;  CM7SpeedPID.kp = TRAILER_SpeedPIDkp;   CM7SpeedPID.ki = TRAILER_SpeedPIDki;
	 CM7SpeedPID.outputMax=2000;
	
	 CM7PositionPID.fdb=CM7Encoder.ecd_angle;
	 CM7PositionPID.Calc(&CM7PositionPID);
	 
   CM7SpeedPID.ref=CM7PositionPID.output;
	 CM7SpeedPID.fdb=CM7Encoder.filter_rate;
	 CM7SpeedPID.Calc(&CM7SpeedPID);

}

void PAW_POSITION_HANDLE(void)
{
	if((PAW_CHANGE_HANDLE==no)&&(s2==s2_up))
 {
		switch(paw_hori_state)
	{
	  case FIRST_STATE:
		{
		 paw_hori_state=THIRD_STATE;
		}break;
		
    case SECOND_STATE:
    {
		 paw_hori_state=FIRST_STATE;
		}break;

    case THIRD_STATE:
    {
		 paw_hori_state=SECOND_STATE;		
		}break;		
			
	}
	PAW_CHANGE_HANDLE=yes;
 }
 
 if((PAW_CHANGE_HANDLE2==no)&&(s2==s2_middle))
 {
		switch(paw_hori_state)
	{
	  case FIRST_STATE:
		{
		 paw_hori_state=THIRD_STATE;
		}break;
		
    case SECOND_STATE:
    {
		 paw_hori_state=FIRST_STATE;
		}break;

    case THIRD_STATE:
    {
		 paw_hori_state=SECOND_STATE;		
		}break;		
			
	}
	PAW_CHANGE_HANDLE2=yes;
 }
}

void paw_ramp(void)
{






}
