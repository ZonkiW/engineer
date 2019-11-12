#include <main.h>

void single_double_handle(int32_t key,int32_t keyvalue,int32_t* KEY_COUNT,int32_t* PRESS)//根据现有计数值改变按键状态
{
    	if(key&keyvalue)//摁下按键 
			{
				 if(*PRESS>0)
				 {
				  *KEY_COUNT=0;
					*PRESS=0;
				 }
			  (*KEY_COUNT)++;
			}
			
			if((key&keyvalue)==0)//松开按键 
      {
		    if(*KEY_COUNT==0) 
          {*PRESS=0;}
		    if((*KEY_COUNT>0)&&(*KEY_COUNT<100)) {*PRESS= 1;}
		    if(*KEY_COUNT>100)  {*PRESS= 2;}
				
		  }
	
}
