#include "main.h"
/*
CM5-8,CM  10-11
*/
void UP_DOWN_Motor_TASK(void)
{
  CM5PositionPID.kp =UP_DOWN_Positionkp;  CM5SpeedPID.kp = UP_DOWN_SpeedPIDkp;   CM5SpeedPID.ki = UP_DOWN_SpeedPIDki; 
	CM6PositionPID.kp =UP_DOWN_Positionkp;  CM6SpeedPID.kp = UP_DOWN_SpeedPIDkp;   CM6SpeedPID.ki = UP_DOWN_SpeedPIDki;
	
	CM5SpeedPID.outputMax=CM6SpeedPID.outputMax=3000;
//---------------------------------------------------¸ù¾Ý²½Öè¸Ä±äµ×ÅÌÓë¸¨ÖúÂÖÔËÐÐ×´Ì¬-----------------------------------------------------------------
//-----------------------------------------------------ÉÏµº---------------------------------------------------------
	if(Engineer_workstate==CLIMB_STATE)
{
	switch(CLIMBSTATE)
	 {
	   case STEP1:
		 {
			 PA2_low();//ÍÈ½µ
			 handle_state=no;
			 handle_state4=yes;
			 chasis_state=FOWARD_STATE;
			 aux_chasis_state=AUX_STATIC_STATE;//¸¨Öú¾²Ö¹
			 //}
		 }break;
		 
	   case STEP2:
		 {
		   PA2_high();//ÍÈÉý
   		 handle_state4=no;	 
			 delay_count_add();
			 if(delay_count<delay_value)
			 {
			 chasis_state=STATIC_STATE;
			 aux_chasis_state=AUX_STATIC_STATE;
			 }
			 else if(delay_count>delay_value)
			 {
				 handle_state=yes;
				 chasis_state=STATIC_STATE;//¾²Ö¹
				 aux_chasis_state=AUX_FOWARD_STATE;//¸¨ÖúÇ°½ø
			 }
		 }break;
		 
		 case STEP3:
		 {
		   PA2_low();//ÍÈ½µ
			 handle_state=no;
			 delay_count_add();
			 if(delay_count<delay_value)
			 {
			 chasis_state=STATIC_STATE;
			 aux_chasis_state=AUX_STATIC_STATE;
			 }
			 else if(delay_count>delay_value)
			 {
				 handle_state4=yes;
				 last_chasis_state=chasis_state;
				 chasis_state=LOCA_STATE;//¾²Ö¹
				 aux_chasis_state=AUX_STATIC_STATE;//¸¨Öú¾²Ö¹
			 }
		 }break;
		 
		 case STEP4:
		 {
			 PA2_high();//ÍÈÉý
       handle_state4=no;			 
			 delay_count_add();
			 if(delay_count<delay_value)
			 {
			 chasis_state=STATIC_STATE;
			 aux_chasis_state=AUX_STATIC_STATE;
			 }
			 else if(delay_count>delay_value)
			 {
				 handle_state=yes;
				 chasis_state=STATIC_STATE;//¾²Ö¹
				 aux_chasis_state=AUX_FOWARD_STATE;//¸¨ÖúÇ°½ø
			 }
		 }break;
		 
		 case STEP5:
		 {
		  PA2_low();//ÍÈ½µ
			chasis_state=STATIC_STATE;
			aux_chasis_state=AUX_STATIC_STATE;
			
		 }break;
	 }
}	
//-----------------------------------------------------ÏÂµº------------------------------------------
else if(Engineer_workstate==DOWN_STATE)
{
 
     switch (DOWNSTATE)
			{
			  case STEP6:
				{
					PA2_low();//ÍÈ½µ
					handle_state2=yes;
					handle_state3=no;
					chasis_state=BACK_STATE;
					aux_chasis_state=AUX_STATIC_STATE;
				}break;
				
				case STEP7:
				{
				   PA2_high();//ÍÈÉý
    			 handle_state2=no;
//			 
    			 delay_count_add();
					 if(delay_count<delay_value)
					 {
					 chasis_state=STATIC_STATE;
					 aux_chasis_state=AUX_STATIC_STATE;
					 }
					 else if(delay_count>delay_value)
					 {
						 handle_state3=yes;
						 handle_state2=no;
						 chasis_state=STATIC_STATE;//¾²Ö¹
						 aux_chasis_state=AUX_BACK_STATE;//¸¨ÖúÇ°½ø
					 }
				}break;
				
				case STEP8:
				{
					 PA2_low();//ÍÈ½µ
					 delay_count_add();
					 handle_state3=no;
					 if(delay_count<delay_value)
					 {
						 chasis_state=STATIC_STATE;
						 aux_chasis_state=AUX_STATIC_STATE;
					 }
					 else if(delay_count>delay_value)
					 {
						 handle_state2=yes;
						 last_chasis_state=chasis_state;
		//				 if(down_step_count==3)
						 chasis_state=LOCA_STATE;//Ç°½ø
		//				 else
		//				 {chasis_state=BACK_STATE;}
						 aux_chasis_state=AUX_STATIC_STATE;//¸¨Öú¾²Ö¹
					 }
				}break;
				
				case STEP9:
				{
					 PA2_high();//ÍÈÉý
    			 handle_state2=no;
//			 
    			 delay_count_add();
					 if(delay_count<delay_value)
					 {
					 chasis_state=STATIC_STATE;
					 aux_chasis_state=AUX_STATIC_STATE;
					 }
					 else if(delay_count>delay_value)
					 {
						 handle_state2=no;
						 handle_state3=yes;
						 chasis_state=STATIC_STATE;//¾²Ö¹
						 aux_chasis_state=AUX_BACK_STATE;//¸¨ÖúÇ°½ø
					 }
				}break;
				
				case STEP10:
				{
					 PA2_low();//ÍÈ½µ
			     chasis_state=STATIC_STATE;
			     aux_chasis_state=AUX_STATIC_STATE;
				}break;
			         			
			}	
}

else if(Engineer_workstate==CONTROL_STATE)
{
    switch(leg_state)
		{
			case LOW_STATE:
			{
			 PA2_low();
			}break;
		
		  case HIGH_STATE:
		  {
			 PA2_high();						
			}break;		
		
		}
 
}
	
	
//-----------------------------------------------------¸¨ÖúÂÖÔËÐÐ×´Ì¬-------------------------------------------------------------------	
if(Engineer_workstate==CLIMB_STATE)	 
{ 
	switch(aux_chasis_state)
	 {
	   case AUX_STATIC_STATE://¾²Ö¹×´Ì¬
		 {
		  CM5SpeedPID.ref=AUX_CHASIS_STATIC;
	    CM6SpeedPID.ref=AUX_CHASIS_STATIC;
		 }break;
		 
		 case AUX_FOWARD_STATE://Ç°ÐÐ×´Ì¬
		 {
		  CM5SpeedPID.ref=AUX_CHASIS_FORWARD ;
	    CM6SpeedPID.ref=-AUX_CHASIS_FORWARD;
		 }break;
		 
		 case AUX_BACK_STATE: //ºóÍË×´Ì¬
		 {
		  CM5SpeedPID.ref=AUX_CHASIS_BACK ;
	    CM6SpeedPID.ref=-AUX_CHASIS_BACK;
		 }break;
	 
	 }
}	

else if(Engineer_workstate==DOWN_STATE)	 
{ 
	switch(aux_chasis_state)
	 {
	   case AUX_STATIC_STATE://¾²Ö¹×´Ì¬
		 {
		  CM5SpeedPID.ref=AUX_CHASIS_STATIC;
	    CM6SpeedPID.ref=AUX_CHASIS_STATIC;
		 }break;
		 
		 case AUX_FOWARD_STATE://Ç°ÐÐ×´Ì¬
		 {
		  CM5SpeedPID.ref=DOWN_AUX_CHASIS_FORWARD ;
	    CM6SpeedPID.ref=-DOWN_AUX_CHASIS_FORWARD;
		 }break;
		 
		 case AUX_BACK_STATE: //ºóÍË×´Ì¬
		 {
		  CM5SpeedPID.ref=DOWN_AUX_CHASIS_BACK ;
	    CM6SpeedPID.ref=-DOWN_AUX_CHASIS_BACK;
		 }break;
	 
	 }
}

if((Engineer_workstate==CONTROL_STATE)&&(PA2))	 
{ 
//	  if(remote_forward_back_ref>0)
//			{
//			 CM5SpeedPID.ref=DOWN_AUX_CHASIS_FORWARD ;
//	     CM6SpeedPID.ref=-DOWN_AUX_CHASIS_FORWARD;
//			}
//		if(remote_forward_back_ref<0)
//			{
//			 CM5SpeedPID.ref=DOWN_AUX_CHASIS_BACK ;
//	     CM6SpeedPID.ref=-DOWN_AUX_CHASIS_BACK;
//			}
//		if(remote_forward_back_ref==0)
//			{
//			 CM5SpeedPID.ref=AUX_CHASIS_STATIC;
//	     CM6SpeedPID.ref=AUX_CHASIS_STATIC;
//			}
			
		if(key&W_ID)      
       {
			 CM5SpeedPID.ref=DOWN_AUX_CHASIS_FORWARD*turnaround ;
	     CM6SpeedPID.ref=-DOWN_AUX_CHASIS_FORWARD*turnaround;
			 }
		else if(key&S_ID) 
       {
				 CM5SpeedPID.ref=DOWN_AUX_CHASIS_BACK*turnaround  ;
  	     CM6SpeedPID.ref=-DOWN_AUX_CHASIS_BACK*turnaround ; 
			 }
		else 
			{
			 CM5SpeedPID.ref=AUX_CHASIS_STATIC;
	     CM6SpeedPID.ref=AUX_CHASIS_STATIC;
			}
		
}
	 CM5SpeedPID.fdb=CM5Encoder.filter_rate;
	 CM6SpeedPID.fdb=CM6Encoder.filter_rate;
	
	 CM5SpeedPID.Calc(&CM5SpeedPID);
   CM6SpeedPID.Calc(&CM6SpeedPID);
}

