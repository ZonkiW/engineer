#include "main.h"

  void Aux_Function(void) //辅助功能
{
//------------------------------------PA1图传舵机,PA0放弹舵机-----------------------------------------------------------------
  	single_double_handle(press_l,0x0001,&MOUSE_L_count,&PRESS_MOUSE_L);	
    if(PRESS_MOUSE_L==1) {TIM_SetCompare2(TIM5,500);turnaround=1;back_car_turnaround=1;MOUSE_L_count=0;}  //图传
		else if(PRESS_MOUSE_L==2) {TIM_SetCompare2(TIM5,900);turnaround=1;back_car_turnaround=-1;MOUSE_L_count=0;}//归零计数值，防止多次进入
	
    single_double_handle(press_r,0x0001,&MOUSE_R_count,&PRESS_MOUSE_R);	
		if(PRESS_MOUSE_R==2) {TIM_SetCompare2(TIM5,1500);turnaround=-1;back_car_turnaround=-1;MOUSE_R_count=0;} //图传
		else if(PRESS_MOUSE_R==1) {TIM_SetCompare2(TIM5,2500);turnaround=-1;back_car_turnaround=1;MOUSE_R_count=0;} //图传
		
		single_double_handle(key,0x1000,&KEY_X_count,&X_PRESS); //弹仓舵机
		if(X_PRESS==1){TIM_SetCompare1(TIM5,1500);X_STATE_FLAG=0;KEY_X_count=0;}
		else if(X_PRESS==2){TIM_SetCompare1(TIM5,550);X_STATE_FLAG=1;KEY_X_count=0;}


//------------------------------------PA2,PA3，PB9电磁阀----------------------------------------------------------------
//    single_double_handle(key,0x4000,&KEY_V_count,&V_PRESS);			
//		if(V_PRESS==1) {PA2_low();V_STATE_FLAG=0;KEY_V_count=0;}
//		else if(V_PRESS==2) {PA2_high();V_STATE_FLAG=1;KEY_V_count=0;}//电磁阀
//		
//		single_double_handle(key,0x8000,&KEY_B_count,&B_PRESS);	
//		if(B_PRESS==1) {PA3_low();B_STATE_FLAG=0;KEY_B_count=0;}
//		else if(B_PRESS==2) {PA3_high();B_STATE_FLAG=1;KEY_B_count=0;}//电磁阀
//		
//		single_double_handle(key,0x2000,&KEY_C_count,&C_PRESS);	
//		if(C_PRESS==1) {PB9_low();C_STATE_FLAG=0;KEY_C_count=0;}
//		else if(C_PRESS==2) {PB9_high();C_STATE_FLAG=1;KEY_C_count=0;}//电磁阀
 
}
