#include "main.h"
/*
CM1-4
ֱ���˶����е���̾����кܴ�Ĺ�ϵ
ʵ�飺�����Կ��Գ���ʹ�õ���λ�û���һ��ʽ�ɳ�����λ�û����ж�λ
���⣺һ���ϵ���ÿһ�������ܳ�������λ���ٶȵ�Ҫ��Ƚϸ�
״̬��Engineer_workstate-----���µ���һ��������ģʽ
      chasis_state-----------���µ�ģʽ�е��̵�����ģʽ
			aux_chasis_state-------���µ�ģʽ���ȵ��������ģʽ
			speed_state------------�ٶ����ģʽ
			DOWNSTATE--------------�µ�ģʽ
			CLIMBSTATE-------------�ϵ�ģʽ
*/
void CHASSIS_Motor_TASK(void)
{
//-----------------------------------------�ϵ�ģʽ-------------------------------------------------
 if(Engineer_workstate==CLIMB_STATE)
 {
	speed_level=0.8;
	CM1SpeedPID.outputMax=CM2SpeedPID.outputMax=CM3SpeedPID.outputMax=CM4SpeedPID.outputMax=CHASIS_Speedoutputmax;//1000
	 
	CM1PositionPID.kp=CHASIS_PositionPIDkp;  CM2PositionPID.kp=CHASIS_PositionPIDkp; 
	CM3PositionPID.kp=CHASIS_PositionPIDkp;  CM4PositionPID.kp=CHASIS_PositionPIDkp;
	
	CM1PositionPID.ki=CHASIS_PositionPIDki;  CM2PositionPID.ki=CHASIS_PositionPIDki; 
	CM3PositionPID.ki=CHASIS_PositionPIDki;  CM4PositionPID.ki=CHASIS_PositionPIDki;
	
	CM1PositionPID.kd=CHASIS_PositionPIDkd;  CM2PositionPID.kd=CHASIS_PositionPIDkd; 
	CM3PositionPID.kd=CHASIS_PositionPIDkd;  CM4PositionPID.kd=CHASIS_PositionPIDkd;
	 
	CM1SpeedPID.kp=CHASIS_SpeedPIDkp;  CM2SpeedPID.kp=CHASIS_SpeedPIDkp;   CM3SpeedPID.kp=CHASIS_SpeedPIDkp;   CM4SpeedPID.kp=CHASIS_SpeedPIDkp;
	CM1SpeedPID.ki=CHASIS_SpeedPIDki;  CM2SpeedPID.ki=CHASIS_SpeedPIDki;   CM3SpeedPID.ki=CHASIS_SpeedPIDki;   CM4SpeedPID.ki=CHASIS_SpeedPIDki;
	CM1SpeedPID.kd=CHASIS_SpeedPIDkd;  CM2SpeedPID.kd=CHASIS_SpeedPIDkd;   CM3SpeedPID.kd=CHASIS_SpeedPIDkd;   CM4SpeedPID.kd=CHASIS_SpeedPIDkd;
	 
	switch(chasis_state)
	 {
	   case STATIC_STATE:
	   {
			forward_back_ref=0;left_right_ref=0;rotate_ref=0;
			 
			 CM1SpeedPID.ref = ( forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
			 CM2SpeedPID.ref = (-forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
			 CM3SpeedPID.ref = (-forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
			 CM4SpeedPID.ref = ( forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 }break;
		 
		  case FOWARD_STATE:
	   {
		 forward_back_ref=-forward_back_speed;left_right_ref=0;rotate_ref=0;
			
		 CM1SpeedPID.ref = ( forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM2SpeedPID.ref = (-forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM3SpeedPID.ref = (-forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM4SpeedPID.ref = ( forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 }break;
		 
		  case BACK_STATE:
	   {
		 forward_back_ref=forward_back_speed;left_right_ref=0;rotate_ref=0;
			 
		 CM1SpeedPID.ref = ( forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM2SpeedPID.ref = (-forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM3SpeedPID.ref = (-forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM4SpeedPID.ref = ( forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 }break;
		 
		 case LOCA_STATE:
	   {
			aim_location.Sx=Sx_value;
			aim_location.Sy=Sy_value;
			aim_location.Angle=Angle_value; 
			CHASIS_calculate();
		 }break;
	  	 
	 }
 
 }
//-----------------------------------------------�µ�ģʽ------------------------------------------------------------- 
 else if(Engineer_workstate==DOWN_STATE) 
 {
  speed_level=0.8;
	CM1SpeedPID.outputMax=CM2SpeedPID.outputMax=CM3SpeedPID.outputMax=CM4SpeedPID.outputMax=DOWN_CHASIS_Speedoutputmax;//1000
	 
	CM1PositionPID.kp=CHASIS_PositionPIDkp;  CM2PositionPID.kp=CHASIS_PositionPIDkp; 
	CM3PositionPID.kp=CHASIS_PositionPIDkp;  CM4PositionPID.kp=CHASIS_PositionPIDkp;
	
	CM1PositionPID.ki=CHASIS_PositionPIDki;  CM2PositionPID.ki=CHASIS_PositionPIDki; 
	CM3PositionPID.ki=CHASIS_PositionPIDki;  CM4PositionPID.ki=CHASIS_PositionPIDki;
	
	CM1PositionPID.kd=CHASIS_PositionPIDkd;  CM2PositionPID.kd=CHASIS_PositionPIDkd; 
	CM3PositionPID.kd=CHASIS_PositionPIDkd;  CM4PositionPID.kd=CHASIS_PositionPIDkd;
	 
	CM1SpeedPID.kp=CHASIS_SpeedPIDkp;  CM2SpeedPID.kp=CHASIS_SpeedPIDkp;   CM3SpeedPID.kp=CHASIS_SpeedPIDkp;   CM4SpeedPID.kp=CHASIS_SpeedPIDkp;
	CM1SpeedPID.ki=CHASIS_SpeedPIDki;  CM2SpeedPID.ki=CHASIS_SpeedPIDki;   CM3SpeedPID.ki=CHASIS_SpeedPIDki;   CM4SpeedPID.ki=CHASIS_SpeedPIDki;
	CM1SpeedPID.kd=CHASIS_SpeedPIDkd;  CM2SpeedPID.kd=CHASIS_SpeedPIDkd;   CM3SpeedPID.kd=CHASIS_SpeedPIDkd;   CM4SpeedPID.kd=CHASIS_SpeedPIDkd;
	 
	switch(chasis_state)
	 {
	   case STATIC_STATE:
	   {
			forward_back_ref=0;left_right_ref=0;rotate_ref=0;
			 
			 CM1SpeedPID.ref = ( forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
			 CM2SpeedPID.ref = (-forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
			 CM3SpeedPID.ref = (-forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
			 CM4SpeedPID.ref = ( forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 }break;
		 
		  case FOWARD_STATE:
	   {
		 forward_back_ref=-forward_back_speed;left_right_ref=0;rotate_ref=0;
			
		 CM1SpeedPID.ref = ( forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM2SpeedPID.ref = (-forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM3SpeedPID.ref = (-forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM4SpeedPID.ref = ( forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 }break;
		 
		  case BACK_STATE:
	   {
			forward_back_ref=forward_back_speed;left_right_ref=0;rotate_ref=0;
			 
		 CM1SpeedPID.ref = ( forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM2SpeedPID.ref = (-forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM3SpeedPID.ref = (-forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 CM4SpeedPID.ref = ( forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)*speed_level;
		 }break;
		 
		 case LOCA_STATE:
	   {
			aim_location.Sx=Sx_value;
			aim_location.Sy=Sy_value;
			aim_location.Angle=Angle_value; 
			CHASIS_calculate();
		 }break;
	  	 
	 }
 }

//-----------------------------------------------------��ͨģʽ---------------------------------------------------------------
 if((Engineer_workstate==CONTROL_STATE)&&(!PA2)) 
 {	
	 //ʵ�������ͣ��13��Щ��24��Щ
	  CM5SpeedPID.ref=AUX_CHASIS_STATIC;
    CM6SpeedPID.ref=AUX_CHASIS_STATIC;
//----------------------------------------(���̿���)-------------------------------------------------------------	 
    if(key&W_ID)      {forward_back_ref=-forward_back_speed*FBSpeedRamp.Calc(&FBSpeedRamp);}     //����ģʽ
		else if(key&S_ID) {forward_back_ref=forward_back_speed*FBSpeedRamp.Calc(&FBSpeedRamp);}
		else              {forward_back_ref=0;   FBSpeedRamp.ResetCounter(&FBSpeedRamp);}
		
		if(key&A_ID)      {left_right_ref=-left_right_speed*back_car_turnaround*LRSpeedRamp.Calc(&LRSpeedRamp);}
		else if(key&D_ID) {left_right_ref=left_right_speed*back_car_turnaround*LRSpeedRamp.Calc(&LRSpeedRamp);}
		else              {left_right_ref=0;   LRSpeedRamp.ResetCounter(&LRSpeedRamp);}
		
    if(key&Q_ID)      {rotate_ref=-rotate_speed*turnaround*back_car_turnaround*RoSpeedRamp.Calc(&RoSpeedRamp);}
		else if(key&E_ID) {rotate_ref=rotate_speed*turnaround*back_car_turnaround*RoSpeedRamp.Calc(&RoSpeedRamp);}
		else              {rotate_ref=0;    RoSpeedRamp.ResetCounter(&RoSpeedRamp);} 

//-----------------------------------------(ң������Ծ����)-------------------------------------------------------- 
//	  if(ch1>REMOTE_MIDDLE)      {forward_back_ref=forward_back_speed*FBSpeedRamp.Calc(&FBSpeedRamp);}       //ң����ģʽ
//		else if(ch1<REMOTE_MIDDLE) {forward_back_ref=-forward_back_speed*FBSpeedRamp.Calc(&FBSpeedRamp);}
//		else                       {forward_back_ref=0;  FBSpeedRamp.ResetCounter(&FBSpeedRamp);}
//			 		
//		if(ch0<REMOTE_MIDDLE)      {left_right_ref=left_right_speed*back_car_turnaround*LRSpeedRamp.Calc(&LRSpeedRamp);}
//		else if(ch0>REMOTE_MIDDLE) {left_right_ref=-left_right_speed*back_car_turnaround*LRSpeedRamp.Calc(&LRSpeedRamp);}
//		else                       {left_right_ref=0;   LRSpeedRamp.ResetCounter(&LRSpeedRamp);}
//		
//    if(ch2>REMOTE_MIDDLE)      {rotate_ref=rotate_speed*turnaround*back_car_turnaround*RoSpeedRamp.Calc(&RoSpeedRamp);}
//		else if(ch2<REMOTE_MIDDLE) {rotate_ref=-rotate_speed*turnaround*back_car_turnaround*RoSpeedRamp.Calc(&RoSpeedRamp);}
//		else                       {rotate_ref=0;       RoSpeedRamp.ResetCounter(&RoSpeedRamp);} 
		
//-----------------------------------------(ң�����������)---------------------------------------------------------
//     forward_back_ref=-remote_forward_back_ref;
//     left_right_ref  =remote_left_right_ref;
//     rotate_ref      =remote_rotate_ref;


//------------------------------------------(�ٶȷּ�)-----------------------------------------------------------------		
		if(key&SHIFT_ID)//shift�ٶȷּ� ������ֱ��
    {
		speed_level=speed_level_low_rat;
		CM1SpeedPID.outputMax=CM2SpeedPID.outputMax=CM3SpeedPID.outputMax=CM4SpeedPID.outputMax=5000;
		CM1SpeedPID.kp=20;  CM2SpeedPID.kp=20;   CM3SpeedPID.kp=20;   CM4SpeedPID.kp=20;
	  CM1SpeedPID.ki=1.5; CM2SpeedPID.ki=1.5;  CM3SpeedPID.ki=1.5;  CM4SpeedPID.ki=1.5;
	  CM1SpeedPID.kd=20;  CM2SpeedPID.kd=20;   CM3SpeedPID.kd=20;   CM4SpeedPID.kd=20;
		} //�ٶȷּ�
		else
    {
		speed_level=speed_level_hign_rat;
		CM1SpeedPID.outputMax=CM2SpeedPID.outputMax=CM3SpeedPID.outputMax=CM4SpeedPID.outputMax=8000;//������
		CM1SpeedPID.componentKdMax=CM2SpeedPID.componentKdMax=CM3SpeedPID.componentKdMax=CM4SpeedPID.componentKdMax=2000;
		CM1SpeedPID.kp=25;  CM2SpeedPID.kp=25;   CM3SpeedPID.kp=25;   CM4SpeedPID.kp=25; // 20
		CM1SpeedPID.ki=3.0; CM2SpeedPID.ki=3.0;  CM3SpeedPID.ki=3.0;  CM4SpeedPID.ki=3.0; //3.0
		CM1SpeedPID.kd=20;  CM2SpeedPID.kd=20;   CM3SpeedPID.kd=20;   CM4SpeedPID.kd=20;  //20
		}  
		
		switch(speed_step)
		{
		  case LOW_STEP:
			{
				CM1SpeedPID.ref = ( forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)\
																																*turnaround*speed_level*OVER_P_SPEED;
				CM2SpeedPID.ref = (-forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)\
																						*turnaround*speed_level*OVER_P_SPEED*chasis_dif_step_via;
				CM3SpeedPID.ref = (-forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)\
																																*turnaround*speed_level*OVER_P_SPEED;
				CM4SpeedPID.ref = ( forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)\
																						*turnaround*speed_level*OVER_P_SPEED*chasis_dif_step_via;
			}break;
		
		  case FAST_STEP:
			{
				CM1SpeedPID.ref = ( forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)\
																																*turnaround*speed_level*OVER_P_SPEED;
				CM2SpeedPID.ref = (-forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)\
																																*turnaround*speed_level*OVER_P_SPEED;
				CM3SpeedPID.ref = (-forward_back_ref - left_right_ref*left_right_rat + rotate_ref*rotate_rat)\
																																*turnaround*speed_level*OVER_P_SPEED;
				CM4SpeedPID.ref = ( forward_back_ref + left_right_ref*left_right_rat + rotate_ref*rotate_rat)\
																																*turnaround*speed_level*OVER_P_SPEED;
			 			
			}		
		}

 }
 
 	CM1SpeedPID.fdb = CM1Encoder.filter_rate;
	CM2SpeedPID.fdb = CM2Encoder.filter_rate;
	CM3SpeedPID.fdb = CM3Encoder.filter_rate;
	CM4SpeedPID.fdb = CM4Encoder.filter_rate;
	
	CM1SpeedPID.Calc(&CM1SpeedPID);
	CM2SpeedPID.Calc(&CM2SpeedPID);
	CM3SpeedPID.Calc(&CM3SpeedPID);
	CM4SpeedPID.Calc(&CM4SpeedPID);
 
}


void POSITION_LIMIT(double* angle_ref,Encoder encoder,double angle_dif)
{
//   if((*angle_ref-encoder.ecd_angle)>angle_dif)
//	  {
//	    *angle_ref-=compensate_angel_add;
//	  }
//	 if((*angle_ref-encoder.ecd_angle)<(-angle_dif))
//	  {
//	    *angle_ref+=compensate_angel_add;
//	  }

}

void CM_OUTPUT(void) //������
{
	 switch(speed_state)
	{		 
		case PMAX_STATE: 
		{
		 OVER_P_SPEED=over_p_rat;
		 Set_CM_Speed(CAN1,CM1SpeedPID.output,CM2SpeedPID.output,CM3SpeedPID.output,CM4SpeedPID.output);//can1��������ٶ�
		 Set_Gimbal_Current(CAN1,CM5SpeedPID.output,CM6SpeedPID.output,CM7SpeedPID.output);

		 Set_CM_Speed(CAN2,CM8SpeedPID.output,CM9SpeedPID.output,CM10SpeedPID.output,CM11SpeedPID.output);//can1��������ٶ�
		 Set_Gimbal_Current(CAN2,CM12SpeedPID.output,CM13SpeedPID.output,CM14SpeedPID.output); 
		}break;
	 
		case NORMAL_STATE:
		{
		 OVER_P_SPEED=sub_p_rat;	
			
		 Set_CM_Speed(CAN1,CM1SpeedPID.output,CM2SpeedPID.output,CM3SpeedPID.output,CM4SpeedPID.output);//can1��������ٶ�
		 Set_Gimbal_Current(CAN1,CM5SpeedPID.output,CM6SpeedPID.output,CM7SpeedPID.output);

		 Set_CM_Speed(CAN2,CM8SpeedPID.output,CM9SpeedPID.output,CM10SpeedPID.output,CM11SpeedPID.output);//can1��������ٶ�
		 Set_Gimbal_Current(CAN2,CM12SpeedPID.output,CM13SpeedPID.output,CM14SpeedPID.output); 
		}break;
		
		case STOP_STATE: 
		{
		 Set_CM_Speed(CAN1,0,0,0,0);//can1��������ٶ�
		 Set_Gimbal_Current(CAN1,0,0,0);

		 Set_CM_Speed(CAN2,0,0,0,0);//can1��������ٶ�
		 Set_Gimbal_Current(CAN2,0,0,0);
		
		 PA2_low();
			
		}break;
  }

}

void STATE_CHANGE(void)  //�л�����ģʽ
{
//----------------------------------------����״̬�жϣ�s1�����ı�״̬��----------------------------------------------
   LAST_workstate=Engineer_workstate;
	 switch(s1)
		{
			case s1_up://s1���ϱ�
			{
			 Engineer_workstate=CLIMB_STATE;
			}break;
			
			case s1_middle:
			{
			 Engineer_workstate=CONTROL_STATE;
			}break;
			
			case s1_down:
			{
			 Engineer_workstate=DOWN_STATE;
			}break;
		}
//----------------------------------------�ϵ�״̬�ж�----------------------------------------------
		LAST_CLIMBSTATE=CLIMBSTATE;
		if(Engineer_workstate==CLIMB_STATE)//ֻ�����ϵ�״̬�� ���Զ��ϵ�
		{
			switch(CLIMBSTATE)
			{
			  case STEP1:
				{
					if((PA8==NEAR_LEVEL)&&(handle_state4==yes))
				  {
				   CLIMBSTATE=STEP2;
				   delay_count_clear();//ʹ�ӳ�һ��ʱ�䣬������ȶ�������ǰ��
				  }
				}break;
				
				case STEP2:        //PA10Ҫ������ʱ�ж�
        {
				  if((PA10==NEAR_LEVEL)&&(handle_state==yes))//�ڵ�һ��ʱ��PA10ҲΪNEAR,�����ͻ
				{
				  CLIMBSTATE=STEP3;
				  delay_count_clear();
				}	
				}break;

        case STEP3:
				{
					if((PA8==NEAR_LEVEL)&&(handle_state4==yes))
				  {
				   CLIMBSTATE=STEP4;
				   delay_count_clear();//ʹ�ӳ�һ��ʱ�䣬������ȶ�������ǰ��
				  }
				}break;
				
				case STEP4:
				{
				   if((PA10==NEAR_LEVEL)&&(handle_state==yes))//�ڵ�һ��ʱ��PA10ҲΪNEAR,�����ͻ
				  {
				   CLIMBSTATE=STEP5;
				   delay_count_clear();
				  }	
				}break;
				
				case STEP5:
				{
				}break;
					
			}
    }
			
//----------------------------------------�µ�״̬�ж�----------------------------------------------
	  else if(Engineer_workstate==DOWN_STATE)//PA10Ҫ�ڽ���ʱ�ж�
		{

			switch (DOWNSTATE)
			{
			  case STEP6:
				{
					 if((PA10==FAR_LEVEL)&&(handle_state2==yes))
			    {
			     DOWNSTATE=STEP7;
				   delay_count_clear();
				  }
				}break;
				
				case STEP7:
				{
					 if((PA9==FAR_LEVEL)&&(handle_state3==yes))
					{
					 DOWNSTATE=STEP8;
					 delay_count_clear();					
					}
				}break;
				
				case STEP8:
				{
					if((PA10==FAR_LEVEL)&&(handle_state2==yes))
			    {
			     DOWNSTATE=STEP9;
				   delay_count_clear();
				  }
				}break;
				
				case STEP9:
				{
					 if((PA9==FAR_LEVEL)&&(handle_state3==yes))
					{
					 DOWNSTATE=STEP10;
					 delay_count_clear();					
					}
				}break;
				
				case STEP10:
				{
				}break;
			         			
			}	
				
		}
//-----------------------------------------�ֶ��������µ�--------------------------------------------------		
		else if(Engineer_workstate==CONTROL_STATE)
		{
		  if(key&F_ID)
			{
			 leg_state=LOW_STATE;
			}
		  if(key&R_ID)
			{
			 leg_state=HIGH_STATE;		
			}
		}
//--------------------------------------����״̬�ж�--------------------------------------------------			
			
			if((P_value>P_limit_value)&&(REMOTE_LOSE_COUT<remote_lose_cut))
			{
			  speed_state=PMAX_STATE; //�����ʵ���
			}
			if((P_value<P_limit_value)&&(REMOTE_LOSE_COUT<remote_lose_cut))
			{
			  speed_state=NORMAL_STATE;//����ģʽ
			}
			if((REMOTE_LOSE_COUT>remote_lose_cut)) //����ֹͣ��ң��������
			{
				speed_state=STOP_STATE;
			}
			

			
//---------------------------------------צ��״̬�жϣ�s2����ץ������λ��ͣ��������λԭλ��------------------------------------------------
//�ſ�צ��200������600���ƶ�λ��1500������400���н�200������600�����ƣ�ѭ����
//צ��ץ�ᣬ���õ��̽��е���
			last_paw_verti_state=paw_verti_state;
			switch(s2)
			{
			  case s2_up://��ʼץȡ
				{
				  paw_count++;//��ʱ��
					if((0<paw_count)&&(paw_count<200))       {paw_cylinder_state =CLOSE_STATE; }
		 else if((200<paw_count)&&(paw_count<600))     {paw_verti_state   =PAW_UP_STATE; }
		 else if((600<paw_count)&&(paw_count<900))    {paw_verti_state   =PAW_DOWN_STATE;}			
		 else if((900<paw_count)&&(paw_count<1100))   {paw_cylinder_state =OPEN_STATE; }			
		 else if((1100<paw_count)&&(paw_count<1500))   {paw_verti_state    =PAW_UP_STATE;}			
		 else if((1500<paw_count)&&(paw_count<3000))   {PAW_POSITION_HANDLE();}			
		 else if((3000<paw_count)&&(paw_count<3300))   {paw_verti_state    =PAW_DOWN_STATE;}
     else if(paw_count>3300)		                   {paw_count=0;PAW_CHANGE_HANDLE=no;}
								
				}break;
				
				case s2_middle:
				{
					 PAW_CHANGE_HANDLE=no;
					 paw_init_count=0;
					 paw_count=0;
					//----------------------------------צ�������½�------------------------------
					 paw_verti_state=PAW_CONTROL_STATE;
					//----------------------------------צ�ӿ���-----------------------------------
					 if(key&Z_ID)
					 {
						paw_cylinder_state=OPEN_STATE;
					 }
					 if(key&X_ID)
					 {
						paw_cylinder_state=CLOSE_STATE;
					 }
					//----------------------------------צ��λ��ѡ��------------------------------
					 if(key&G_ID)
					 {
						PAW_POSITION_HANDLE();
					 }
					 if((key&G_ID)!=G_ID)
					 {
						 PAW_CHANGE_HANDLE2=no;
					 }
							 
				}break;
				
				
				
				case s2_down:
				{
				  paw_init_count++;
          if((0<paw_init_count)&&(paw_init_count<400))   {paw_verti_state=PAW_INIT_STATE;}
		 else if((400<paw_init_count)&&(paw_init_count<1400)){paw_hori_state=THIRD_STATE; paw_cylinder_state=OPEN_STATE;}
		 else if((1400<paw_init_count)&&(paw_init_count<2000)){paw_hori_state=SECOND_STATE;}
				}break;
			  	
			
			}
//---------------------------------------�ϳ�״̬�ж�------------------------------------------------
			if(key==V_ID)
			{
				CM7PositionPID.ref+=2;
			}
			else if(key==V_SHIFT_ID)
			{
			  CM7PositionPID.ref-=2;
			}
//----------------------------------------����״̬����----------------------------------------------
			if(key&B_ID)
			{
			 PC1_high();
			}
			else
			{
			 PC1_low();
			}

//---------------------------------------ͼ�����---------------------------------------------------
    single_double_handle(press_l,0x0001,&MOUSE_L_count,&PRESS_MOUSE_L);	
    if(PRESS_MOUSE_L==1) {TIM_SetCompare3(TIM4,500);turnaround=1;back_car_turnaround=1;MOUSE_L_count=0;}  //ͼ��
		else if(PRESS_MOUSE_L==2) {TIM_SetCompare3(TIM4,1500);turnaround=1;back_car_turnaround=-1;MOUSE_L_count=0;}//�������ֵ����ֹ��ν���
	
    single_double_handle(press_r,0x0001,&MOUSE_R_count,&PRESS_MOUSE_R);	
		if(PRESS_MOUSE_R==2) {TIM_SetCompare3(TIM4,2000);turnaround=-1;back_car_turnaround=-1;MOUSE_R_count=0;} //ͼ��
		else if(PRESS_MOUSE_R==1) {TIM_SetCompare3(TIM4,2500);turnaround=-1;back_car_turnaround=1;MOUSE_R_count=0;} //ͼ��			
//---------------------------------------�л�״̬����------------------------------------------------
			if((last_chasis_state!=LOCA_STATE)&&(chasis_state==LOCA_STATE))
			{
			  can_count_1_4=0;
				CM1Encoder.round_cnt=0;  CM2Encoder.round_cnt=0; CM3Encoder.round_cnt=0; CM4Encoder.round_cnt=0;
  		}
			if((LAST_workstate!=CLIMB_STATE)&&(Engineer_workstate==CLIMB_STATE))
			{
			  CLIMBSTATE=STEP1;
			}
			if((LAST_workstate!=DOWN_STATE)&&(Engineer_workstate==DOWN_STATE))
			{
			  DOWNSTATE=STEP6;
			}
			if(last_paw_verti_state!=paw_verti_state)
			{
			  paw_ref=CM8PositionPID.ref;
      }
}


void CHASIS_calculate(void)
{
	if(Engineer_workstate==CLIMB_STATE)	 
	{
  CM1Encoder.aim_ecd_angle=circal_angel*(aim_location.Sy*Sy_rat-aim_location.Sx*Sx_rat+aim_location.Angle*Angle_rat);
	CM2Encoder.aim_ecd_angle=circal_angel*(-aim_location.Sy*Sy_rat+aim_location.Sx*Sx_rat+aim_location.Angle*Angle_rat);
	CM3Encoder.aim_ecd_angle=circal_angel*(-aim_location.Sy*Sy_rat-aim_location.Sx*Sx_rat+aim_location.Angle*Angle_rat);
	CM4Encoder.aim_ecd_angle=circal_angel*(aim_location.Sy*Sy_rat+aim_location.Sx*Sx_rat+aim_location.Angle*Angle_rat);
	}
	else if(Engineer_workstate==DOWN_STATE)
	{
	CM1Encoder.aim_ecd_angle=circal_angel*(aim_location.Sy*DOWN_Sy_rat-aim_location.Sx*DOWN_Sx_rat\
		                                                           +aim_location.Angle*DOWN_Angle_rat);
	CM2Encoder.aim_ecd_angle=circal_angel*(-aim_location.Sy*DOWN_Sy_rat+aim_location.Sx*DOWN_Sx_rat\
		                                                           +aim_location.Angle*DOWN_Angle_rat);
	CM3Encoder.aim_ecd_angle=circal_angel*(-aim_location.Sy*DOWN_Sy_rat-aim_location.Sx*DOWN_Sx_rat\
		                                                           +aim_location.Angle*DOWN_Angle_rat);
	CM4Encoder.aim_ecd_angle=circal_angel*(aim_location.Sy*DOWN_Sy_rat+aim_location.Sx*DOWN_Sx_rat+\
		                                                           aim_location.Angle*DOWN_Angle_rat);
	}
	CM1PositionPID.ref=CM1Encoder.aim_ecd_angle*LOCA_SpeedRamp.Calc(&LOCA_SpeedRamp);
  CM2PositionPID.ref=CM2Encoder.aim_ecd_angle*LOCA_SpeedRamp.Calc(&LOCA_SpeedRamp);
  CM3PositionPID.ref=CM3Encoder.aim_ecd_angle*LOCA_SpeedRamp.Calc(&LOCA_SpeedRamp);
  CM4PositionPID.ref=CM4Encoder.aim_ecd_angle*LOCA_SpeedRamp.Calc(&LOCA_SpeedRamp);

	CM1PositionPID.fdb=CM1Encoder.ecd_angle;
	CM2PositionPID.fdb=CM2Encoder.ecd_angle;
	CM3PositionPID.fdb=CM3Encoder.ecd_angle;
	CM4PositionPID.fdb=CM4Encoder.ecd_angle;
	
	CM1PositionPID.Calc(&CM1PositionPID);
	CM2PositionPID.Calc(&CM2PositionPID);
	CM3PositionPID.Calc(&CM3PositionPID);
	CM4PositionPID.Calc(&CM4PositionPID);
	
	CM1SpeedPID.ref=CM1PositionPID.output;
	CM2SpeedPID.ref=CM2PositionPID.output;
	CM3SpeedPID.ref=CM3PositionPID.output;
	CM4SpeedPID.ref=CM4PositionPID.output;
}

