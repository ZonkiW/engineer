#include <main.h>

void FORWARD_BACK_Motor_TASK(void)
{
//  switch(Engineer_workstate)
// {	 
//		 case KEY_STATE://һ��ģʽ
//	 {
//		 single_double_handle(key,X_ID,&KEY_X_count,&X_PRESS);	
//		 if(X_PRESS==1)  //x
//      {
//				if((CM12Encoder.ecd_angle)<(CM12_13position_stop))//��ֹײ������
//			  {CM14PositionPID_ref=CM14position_low;}
//				
//				KEY_X_count=0;
//			}
//		 else if(X_PRESS==2)
//      {
//				if((CM12Encoder.ecd_angle)<(CM12_13position_stop))
//        {CM14PositionPID_ref=CM14position_high;}
//				
//				KEY_X_count=0;
//			}
//		  
//   } break;


//     case CONTROL_STATE://�ɵ�ģʽ
//   {
//		 if(key==X_ID)//x
//		 {
//		  CM14PositionPID_ref-=CM14angel_add;
//		 }
//		 else if(key==X_SHIFT_ID)
//		 {
//		  CM14PositionPID_ref+=CM14angel_add;
//		 }
//		 else
//		 {
//			 CM14ramp.ResetCounter(&CM14ramp);
//		 }
//		 
//		 VAL_LIMIT(CM14PositionPID_ref,CM14position_high,CM14position_low)
//		 POSITION_LIMIT(&CM14PositionPID_ref,CM14Encoder,die_area);//��Ҫ���ò������������Ƿ�ֹ��������
//		 
//   } break;
//	 
//	   case ORIGIN_STATE://ԭ��ģʽ
//	 {
//		  CM14PositionPID_ref+=CM14angel_add; 
//		  POSITION_LIMIT(&CM14PositionPID_ref,CM14Encoder,die_area);		 
//	 } break;
//	 
//	   case INITIAL_STATE://��ʼ״̬
//	 {
//		
//	 } break;
//  
// }


}
