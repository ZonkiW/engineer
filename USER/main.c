#include "main.h"
/* 
���ܣ��ǵ���ȡ�����ϳ�
ע�⾧�������Ҫ����һ��
�����ڴ��
*/

int main(void)
{ 
	delay_init(168);		//��ʱ��ʼ�� 
	delay_ms(3000);//��ʱҪ�ӣ���һ���ϵ��ʱ��
	           /*---------------����------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ȼ�����2����ռ���ȼ�����Ӧ���ȼ�����λ��ע������жϵ����ȼ�
	                                               //ң�������ȼ����
	CAN1_Configuration();//���͵����Ϣ���������������ݴ����õ�ENCODERֵ ��can1��can2һ���ɽ���14�����
	CAN2_Configuration();//can2��������Ҫ����can1��ʱ��
	PWM_Configuration();//���p��������
	YAOKONG_Configuration();//����ң�������ݣ��������õ���ͨ��ֵ
	TASK_Init();//��ʼ��
			       /*----------------����-----------------*/
	TIM6_Configuration();//3ms�����ƻ��������ƻ����� �����������TIM6��ִ��
	TIM6_Start();
	    
	while(1)
	{
    //printf("����������,�Իس�������\r\n");
		
	}
			
}	




