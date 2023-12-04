/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"


/*
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */
void main()
{
  DisableGlobalIRQ();     																	//�ر����ж�
	board_init();			// ��ʼ���Ĵ���,��ɾ���˾���롣
	
	// �˴���д�û�����(���磺�����ʼ�������)
	//lcd_init();
  motor_init();
  imu660ra_init();
  while(dl1a_init())
	{
		delay_ms(500);
		printf("g:VL53L0X init try again.\r\n");
	}
//  servo_init();
  adc_Init_all();
  //pit_timer_ms(TIM_4,1);	   //��ʱ��4  2ms�ж�
   bluetooth_ch9141_init();
  pwm_init(PWMB_CH3_P33,50,0);       //Ƶ��Ϊ50hz��ˢ�����ʼ��
  pwm_init(PWMB_CH4_P77,50,0);       
    if(fan_start_flag==0)   //�ȴ���ˢ���ȿ���
    {
    delay_ms(4000);
    fan_start_flag=1;
    }
  pit_timer_ms(TIM_1,1);	   //��ʱ��1  5ms�ж�
	EnableGlobalIRQ();                                         //��ʼ����ϣ��������ж�
    while(1)
	{ 
   Handle_Barn_Out(1);     //ִ�г��⺯����flag_start��־λ��һ�Ż���ж�
//flag_start=1;         //ƽʱ����ֱ�Ӹ�1�����ó���
	 if(flag_start)
	 {
		 HALL_Detect();               //�ɻɹ�ͣ�����
	 }
	 Handle_Barn_In(1);             //ͣ����⴦��
   
   printf("g:%f,%f,%f,%f,%f,%f,%f,%f,%d,%d\r\n",Left_Encoder*0.0017f*10,Right_Encoder*0.0017f*10,Right_Adc,Left_Adc,Left_Xie_Adc,Right_Xie_Adc,right_wheel_goal,left_wheel_goal,Right_Duty,Left_Duty);
   //printf("g:%f,%f,%f,%f,%d,%d\r\n",Left_Encoder*0.0017f*10,Right_Encoder*0.0017f*10,pid_Delta_L,pid_Delta_R,right_wheel_goal,left_wheel_goal,Right_Duty,Left_Duty);
    //printf("g:%d,%d,%d,%d,%d,%f,%d,%f\r\n",flag_1,flag_2,flag_3,flag_4,Out_Time,Annulus_Angle,count_delay_In,Annulus_Distance);
    //printf("g:%d,%d,%f\r\n",flag_4,Out_Time,Annulus_Angle);
    //printf("%d\r\n",fan_start_flag);
   //printf("g:%d,%d,%d\r\n",T_outku,flag_end,dl1a_distance_mm);
//   		if(dl1a_finsh_flag)
//		{
//			printf("Range : %d.\r\n", dl1a_distance_mm);
//			dl1a_finsh_flag = 0;
//		}
		 // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

