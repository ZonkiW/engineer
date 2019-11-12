#include "main.h"
/* 
功能：登岛，取弹，拖车
注意晶振的配置要与板的一样
适用于大板
*/

int main(void)
{ 
	delay_init(168);		//延时初始化 
	delay_ms(3000);//延时要加，给一个上电的时间
	           /*---------------定义------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组2，抢占优先级与相应优先级各两位，注意各个中断的优先级
	                                               //遥控器优先级最高
	CAN1_Configuration();//发送电机信息，并接收码盘数据处理，得到ENCODER值 ，can1与can2一共可接收14个电机
	CAN2_Configuration();//can2的配置中要开启can1的时钟
	PWM_Configuration();//多个p波的配置
	YAOKONG_Configuration();//接收遥控器数据，并处理，得到各通道值
	TASK_Init();//初始化
			       /*----------------任务-----------------*/
	TIM6_Configuration();//3ms进控制环，主控制环任务 ，大多任务在TIM6中执行
	TIM6_Start();
	    
	while(1)
	{
    //printf("请输入数据,以回车键结束\r\n");
		
	}
			
}	




