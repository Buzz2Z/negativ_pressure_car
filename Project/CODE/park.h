/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.5.4
  * @brief   ����⣬�ɻɹܼ��ͷ�ļ�
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
 /* Includes ------------------------------------------------------------------*/
 #ifndef _park_h
#define _park_h


#define START_T          100
#define T_OUT_PARK1      200
#define T_OUT_PARK2      100
#define T_IN_PARK1       10
#define T_IN_PARK2       100
#define T_IN_PARK3       100
#define Reed_Switch_HALL_Pin P26

//��������
extern int8   flag_start;          //�������
extern int8   flag_open_reed;      //���θɻɹ�
extern int8   reed_state;          //�ɻɹ�״̬
extern int8   flag_end;            //��ʼͣ����־λ
extern uint16 T_outku;
extern uint16 T_inku;
extern uint16 Open_pack_time;
extern uint8 stop_flag_IN;

//��������
extern void Handle_Barn_Out(uint8 type);
extern void HALL_Detect(void);
extern void Handle_Barn_In(uint8 type);

#endif