 /**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.13
  * @brief   Ԫ��ʶ��ͷ�ļ�
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
#ifndef _CONTROL_H
#define _CONTROL_H

extern float aim_speed;         //�����ٶ�
extern float price_Velocite;    //���ֲ������
extern float speed_output;      //���������ٶ����
extern float my_gyro_z;
extern float Position_Get,Position_pre_Get;
extern float target_vel_z;  //Ŀ��Ƕ�
extern uint8 stop_flag;
extern uint8 fan_start_flag; //��ѹ������־
#define BUZZ_ON           pwm_duty(PWMA_CH4N_P67, 9500);          //��������   
#define BUZZ_OFF          pwm_duty(PWMA_CH4N_P67, 0);         //�ط�����



void motor_speed(float speed);
void set_speed_target(float a,float b);
void DifferControl();
void DerectError_Get(void);
void Direction_out(void);
void fan_start();

#endif