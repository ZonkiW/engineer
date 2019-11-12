#include "main.h"

void user_data_handle(void)//0-3，4-7，8-11，12
{
	 int i;
	 user_float1= CM8PositionPID_ref;
	 user_float2= CM10PositionPID_ref;
	 user_float3= CM12PositionPID_ref;
	
	 unsigned char * a = (unsigned char*)&user_float1;//进制转化
	 unsigned char * b = (unsigned char*)&user_float2;
	 unsigned char * c = (unsigned char*)&user_float3;
	
	 for(int i = 0; i<4; i++)
	 {
		user_data[i]  =a[i]; 
	  user_data[i+4]=b[i];
		user_data[i+8]=c[i];
	 }
	 
	 if(X_STATE_FLAG==0)
   {
	  user_data[12]=user_data[12]&0xFE;
	 }
	 else if(X_STATE_FLAG==1)
	 {
	  user_data[12]=user_data[12]|0x01;//最低位点亮
	 } 
	 
	 if(C_STATE_FLAG==0)
   {
	  user_data[12]=user_data[12]&0xFD;
	 }
	 else if(C_STATE_FLAG==1)
	 {
	  user_data[12]=user_data[12]|0x02;//第二位点亮
	 } 
	 
	 if(V_STATE_FLAG==0)
   {
	  user_data[12]=user_data[12]&0xFB;
	 }
	 else if(V_STATE_FLAG==1)
	 {
	  user_data[12]=user_data[12]|0x04;//第二位点亮
	 } 
	 
	  if(B_STATE_FLAG==0)
   {
	  user_data[12]=user_data[12]&0xF7;
	 }
	 else if(B_STATE_FLAG==1)
	 {
	  user_data[12]=user_data[12]|0x08;//第二位点亮
	 } 
	 
	 
}
