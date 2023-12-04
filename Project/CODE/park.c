/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.5.4
  * @brief   ����⣬�ɻɹܼ��
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
/*ȫ�ֱ������壺

flag_start: ������ɱ�־λ����ʼֵΪ0��
flag_open_reed: �򿪸ɻɹܱ�־λ����ʼֵΪ0��
reed_state: �ɻɹ�״̬����ʼֵΪ0��
flag_end: ��ʼͣ����־λ����ʼֵΪ0��
T_outku, T_inku: ��������Ķ�ʱ�������ڿ��Ƴ��������ʱ�䡣
Open_pack_time: �򿪸ɻɹܵĶ�ʱ����
Stop_time: ͣ���Ķ�ʱ����
stop_flag_IN: ͣ����־λ����ʼֵΪ0��
���⺯�� Handle_Barn_Out��

ͨ���������ҵ�����ٶȣ�ʵ��С���ĳ��⶯����
ʹ�ö�ʱ�� T_outku ���Ƴ�������в�ͬ�׶ε��ٶȡ�
�ɻɹܼ�⺯�� HALL_Detect��

�ڳ�������У���С���߹�һ�ξ�������ɻɹܼ�⡣
ͨ����ȡ Reed_Switch_HALL_Pin ��״̬����ȡ�ɻɹܵ�״̬��
����ɻɹܼ�⵽�ų��仯��״̬Ϊ1���������� flag_end Ϊ1����ʾ��ʼͣ����
��⺯�� Handle_Barn_In��

����С��������⶯��������ͣ���͸ı䷽��
ʹ�ö�ʱ�� T_inku �����������в�ͬ�׶ε��ٶȡ�
stop_flag_IN ���ڱ�־ͣ��״̬��
ע�����

�������漰�ľ�����ֵ�����ٶȡ�ʱ��ȣ�������Ҫ����ʵ�ʻ�е�͵���ϵͳ�����ܽ��е�����
���ֱ������� Reed_Switch_HALL_Pin��Ӧ�������ⲿ���������״̬��
*/


 /* Includes ------------------------------------------------------------------*/
 #include "headfile.h"
/* Private Define ------------------------------------------------------------*/
int8   flag_start           = 0;    //������ɱ�־λ
int8   flag_open_reed       = 0;    //�򿪸ɻɹ�
int8   reed_state           = 0;    //�ɻɹ�״̬
int8   flag_end             = 0;    //��ʼͣ����־λ
uint16 T_outku              = 0;    //����ֱ�ߺʹ�Ƕ�ʱ
uint16 T_inku               = 0;    //���ͣ���ʹ�Ƕ�ʱ
uint16 Open_pack_time = 0;   //�򿪸ɻɹܶ�ʱ
uint16 Stop_time = 0;        //ͣ����ʱ
uint8 stop_flag_IN = 0;  //ͣ����־λ
  /* Functions -----------------------------------------------------------------*/
  /* @brief  ���⺯��
     @param  type-----1Ϊ����⣬2Ϊ�ҳ���
     @retval None
  */
void Handle_Barn_Out(uint8 type)
{//1Ϊ����⣬2Ϊ�ҳ���
    if(type == 1)
    {
		 if(!flag_start)
		 {
      if(T_outku < T_OUT_PARK1)
      {
      Moto_L(2000);
      Moto_R(2000);
      }
			 if (T_outku >= T_OUT_PARK1) 
			 {
      Moto_L(1000);
      Moto_R(3000);
			 }
			 if(T_outku > T_OUT_PARK2)
			 {
				  flag_start = 1;
				  //T_outku=0;
			 }		
		  }	
	  }
		if(type ==2)
    {
			if(!flag_start)
			{
      if(T_outku < T_OUT_PARK1)
      {
//     Moto_L(2000);
//     Moto_R(2000);
      }
			 if (T_outku >= T_OUT_PARK1) 
			 {
				 
//     Moto_L(2000);
//     Moto_R(2000);
			 }
			 if(T_outku > T_OUT_PARK2)
			 {
				  flag_start = 1;
				  //T_outku=0;
			 }															
			}
    }
}

/**
  * @brief  �ɻɹܼ��ͣ��
  * @param  None
  * @retval �ɻɹ�ʹ�÷����ͺͰ������ƣ�ͨ����ȡIO�ڵ�ƽ����
  */
void HALL_Detect(void)
{
	if(flag_start)//��ʼʱ�������ɻɹܼ�⣬��ֹ����ʱ���
	{
		//�߹�һ�ξ�������ɻɹܼ��
		if(T_outku > START_T)
		{
			flag_open_reed = 1;
			T_outku=0;
		}
	}
	if(flag_open_reed)             //�ɻɹܼ���־λ������ſ�ʼ���
	{
		reed_state = Reed_Switch_HALL_Pin;//�ɻɹ�״̬
		if(reed_state==1)
		{
			flag_end = 1;              //ʶ��ͣ����־λ����
		}
	 }
}

/**
  * @brief  ��⺯��
  * @param  None
  * @retval None
  */
void Handle_Barn_In(uint8 type)
{
	if(type ==1)
  {
		if(flag_end==1)
		{
        stop_flag_IN = 1;
        motor_speed(0);
			 if (T_inku >= T_IN_PARK1) 
			 {
         stop_flag = 0;
        Moto_L(-2000);
        Moto_R(-2000);
			 }
        if(T_inku >= T_IN_PARK2)
			 {
        Moto_L(-1000);
        Moto_R(-3000);
			 }
        if(T_inku >= T_IN_PARK3)
			 {
        stop_flag_IN = 1;
        Moto_L(0);
        Moto_R(0);
        while(1);
			 }
       
		}
 }
	if(type ==2)
  {
		if(flag_end==1)
		{
        stop_flag_IN = 1;
        motor_speed(0);
			 if (T_inku >= T_IN_PARK1) 
			 {
        stop_flag_IN = 0;
        Moto_L(-2000);
        Moto_R(-2000);
			 }
        if(T_inku >= T_IN_PARK2)
			 {
        Moto_L(-3000);
        Moto_R(-1000);
			 }
        if(T_inku >= T_IN_PARK3)
			 {
        stop_flag_IN = 1;
        Moto_L(0);
        Moto_R(0);
        while(1);
			 }
		}
 }
	
}