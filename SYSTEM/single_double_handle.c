#include <main.h>

void single_double_handle(int32_t key,int32_t keyvalue,int32_t* KEY_COUNT,int32_t* PRESS)//�������м���ֵ�ı䰴��״̬
{
    	if(key&keyvalue)//���°��� 
			{
				 if(*PRESS>0)
				 {
				  *KEY_COUNT=0;
					*PRESS=0;
				 }
			  (*KEY_COUNT)++;
			}
			
			if((key&keyvalue)==0)//�ɿ����� 
      {
		    if(*KEY_COUNT==0) 
          {*PRESS=0;}
		    if((*KEY_COUNT>0)&&(*KEY_COUNT<100)) {*PRESS= 1;}
		    if(*KEY_COUNT>100)  {*PRESS= 2;}
				
		  }
	
}
