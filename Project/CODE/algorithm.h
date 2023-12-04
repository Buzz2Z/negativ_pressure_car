/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.2.13
  * @brief   �㷨ͷ�ļ�
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
#ifndef _ALGORITHM_H
#define _ALGORITHM_H
/* Functions -----------------------------------------------------------------*/

//����ģ���趨����(����ʵ������޸�)
#define SET_DLLA_DISTANCE         400
int myabs(int16 a);
float abs_adc(float adc);

void element_annulus_detect();

extern uint8 Adc_Solve_annulus;
extern float Annulus_Angle;
extern float Average_Encoder;  //���ұ�����ƽ��ֵ
extern float Annulus_Distance;         //�������ߵ�·��



extern uint8 flag_1;
extern uint8 flag_2;
extern uint8 flag_3;
extern uint16 flag_4;
extern uint32 T_annulus;//�뻷ʱ��
extern uint16 Out_Time;//������ʱʱ��
extern uint16 count_delay_In;

extern float Position_TOF;
extern uint8 flag_obstacle;//·�ϱ�־λ



void obstacle_avoidance(void);

#endif