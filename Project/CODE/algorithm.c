/**
  ******************************************************************************
  * @author  Pump_Li
  * @version V1.0.0
  * @date    2023.3.13
  * @brief   һЩ���������㷨
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "headfile.h"
/* Private Define ------------------------------------------------------------*/
uint8 annulus_flag=0;           //������־λ
uint8 annulus_success=0;        //�����ɹ���������
uint8 Round_Start =0;           //Բ���������������ǻ��ֱ�־λ
uint8 Adc_Solve_annulus=0;
uint8 Left_Annulus=0;           //�󻷵���־λ
uint8 Right_Annulus=0;          //�һ�����־λ
float Annulus_Angle = 0;            //���ֳ�Ȧ�Ƕ�
float Average_Encoder = 0;  //���ұ�����ƽ��ֵ
float Annulus_Distance = 0;         //�������ߵ�·��

uint16 Out_Time=0;//������ʱʱ��
uint32 T_annulus=0;//�뻷ʱ��
uint16 T_Clear=60;//�������־λ��ʱ�䣬�Է�����ʶ��

uint8 flag_1=0;
uint8 flag_2=0;
uint8 flag_3=0;
uint16 flag_4=0;

uint16 count_delay_In=0;


uint8 flag_obstacle=0;//·�ϱ�־λ
uint8 temp_TOF=0;
float Position_TOF=0;
float obstacle_Current_Dir[]={
                              -0.6,-0.57,-0.54,-0.51,-0.48,-0.45,-0.42,-0.39,-0.36,-0.33,
                              -0.30,-0.27,-0.24,-0.21,-0.18,-0.15,-0.12,-0.09,-0.06,-0.03,0,
                              0.03,0.06,0.09,0.12,0.15,0.18,0.21,0.24,0.27,0.30,
                              0.33,0.36,0.39,0.42,0.45,0.48,0.51,0.54,0.57,0.6
                             };


/* Private Functions ---------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/**
  * @brief  ����ֵ����
  * @param  None
  * @retval None
  */
int myabs(int16 a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

float abs_adc(float adc)
{
  	 float temp;
		if(adc<0)  temp=-adc;  
	  else temp=adc;
	  return temp;
}

/**
  * @brief  ����Ԫ��ʶ���־λ��������Ϊ�Ķο��ƣ�1��Ԥ�⻷��������ֵ�ת���2��ת���̶���ǽ��뻷��3�������ڻָ�����ѭ��4�������ǻ��ֳ�����//�ֱ��Ӧannulus_flag
  * @param  None
  * @retval None
  */
void element_annulus_detect(){
  ////------------------Ԥ��Բ��------------------1-----------------------//
  
	if((Left_Xie_Adc+Right_Xie_Adc)>300&&annulus_flag==0)        //�󻷵���־λ���
	{
		//Buzz = 1;
    annulus_flag=1;//������־λ
    //Left_Annulus=1; //�󻷵���־
	}
//  	if(Right_Xie_Adc>200&&Left_Xie_Adc>200&&annulus_flag==0)        //�һ�����־λ���
//	{
//		//Buzz = 1;
//    annulus_flag=1;//������־λ
    //Right_Annulus=1;//�һ�����־
//	} 
//  	if((Left_Adc-Right_Adc)>100&&(Left_Xie_Adc-Right_Xie_Adc)>0&&annulus_flag==0)        //�󻷵���־λ���
//	{
//		//Buzz = 1;
//    annulus_flag=1;//������־λ
//    Left_Annulus=1; //�󻷵���־
//	}
//  	if((Right_Adc-Left_Adc)>100&&(Right_Xie_Adc-Left_Xie_Adc)>0&&annulus_flag==0)        //�һ�����־λ���
//	{
//		//Buzz = 1;
//    annulus_flag=1;//������־λ
//    Right_Annulus=1;//�һ�����־
//	} 

//----------Բ����---------------------------------2---------------------//
//	 if(annulus_flag==1)    
//	{
//		Round_Start =1;   //���������ֱ�־λ
//    flag_1=1;
//    if((Left_Adc>250||Right_Adc>250)&&annulus_flag==1)//&&Annulus_Distance>60
//    {
//     annulus_flag = 2; //�ߵ�Բ��ת�䴦��־λ���ڴ˴����
//    }
//  }
  	 if(annulus_flag==1)    
	{
		Round_Start =1;   //�������������ǻ��ֱ�־λ
    flag_1=1;
    count_delay_In++;
//    if((Right_Adc>250&&Right_Xie_Adc>300&&Left_Adc<50&&Left_Xie_Adc<200||Left_Adc>250&&Left_Xie_Adc>300&&Right_Adc<50&&Right_Xie_Adc<200)&&annulus_flag==1&&count_delay_In>10)//&&Annulus_Distance>60
//    {
//     annulus_flag = 2; //�ߵ�Բ��ת�䴦��־λ���ڴ˴����
//    }
      if(Left_Adc>500&&annulus_flag==1&&Annulus_Distance>=10&&count_delay_In>50)//&&Annulus_Distance>60
    {
     annulus_flag = 2; //�ߵ�Բ��ת�䴦��־λ���ڴ˴����
      Left_Annulus=1; //�󻷵���־
    } 
      if(Right_Adc>300&&annulus_flag==1&&Annulus_Distance>=10&&count_delay_In>50)//&&Annulus_Distance>60
    {
     annulus_flag = 2; //�ߵ�Բ��ת�䴦��־λ���ڴ˴����
     Right_Annulus=1;//�һ�����־
    } 
  }
  if(annulus_flag==2)
		{
     T_annulus++;      //��ȥʱ�����
      //flag_2=1;
							//�����ǹ���Ļ��Ӵ�T_annulus�����ޣ������ǹ��ٵĻ��ͼ�С���ޣ�����������ǿ��ƣ���������ʱ�����
						if(T_annulus>0&&T_annulus<100) //���ƹ̶���ǵ�ʱ��0---50
						{
             
												if(Left_Annulus==1)  //��
												{
													Adc_Solve_annulus=1;  //ǿ���������󻷽���
                          flag_2=1;
                         
												}
												else if(Right_Annulus==1) //�һ�
												{
													Adc_Solve_annulus=2; //ǿ�����Ҵ���һ�����
                          flag_2=1;
                         
												}
            }
//            else if(Annulus_Distance<300)
//            {
//              annulus_flag=3;//�����лָ�����ѭ��
//            }
            else if(T_annulus>=100)
            {
             annulus_flag=3;//�����лָ�����ѭ��
            }
						
		}
if(annulus_flag==3)
{
             Adc_Solve_annulus=3;
             flag_3=1;
}
  
//---------��������-----------------------------------3-------------------//
	if(annulus_flag==4)
	{
      if (Out_Time>0&&Out_Time<50)
      {
      Adc_Solve_annulus=4;//ǿ��ֱ���뿪�����ٴ�ʶ��
      annulus_flag = 0;
        flag_4=1;
      }
      else if(Out_Time>=50)
      {
        annulus_success++;
        annulus_flag=0;
        Round_Start=0;
        T_annulus=0;
        Out_Time=0;
        Adc_Solve_annulus=0;
        count_delay_In=0;
        flag_1=0;
        flag_2=0;
        flag_3=0;
        flag_4=0;
        Annulus_Angle=0;
        Annulus_Distance=0;
      }
	}
   
/********�������̶Ա����������ǵȲ���***************************/
	if(Round_Start ==1)
	{
      Annulus_Angle += my_gyro_z*0.00012480f*47.75;      //�����ǻ��ֻ������ʵ�Ƕ�
      Average_Encoder = (Left_Encoder + Right_Encoder)*0.05;
      Annulus_Distance += (Average_Encoder*0.08735f);  //ת��Ϊ����  distance=<����>����1��
      if(Annulus_Angle>=330||Annulus_Angle<=(-330))     //�������ж�Բ��
      {
 			 Round_Start =2;//�Ƴ�����
			 annulus_flag =4;//������־λ
      }
//    if((Left_Adc>430||Right_Adc>430)&&annulus_flag==3)
//    {
//  		 Round_Start =2;//�Ƴ�����
//			 annulus_flag =4;//������־λ
//    }
	}
	
  if(Round_Start ==2)         //������ʱ��
	 { 
	 Out_Time++;
    //������ʱ��
	 }
	 
  
      if(Out_Time>T_Clear)    //���б�־λ����
   {
        //Buzz = 0;
        annulus_success++;
        annulus_flag=0;
        Round_Start =0;
        T_annulus=0;
        Out_Time=0;
     Adc_Solve_annulus=0;
     count_delay_In=0;
             flag_1=0;
        flag_2=0;
        flag_3=0;
        flag_4=0;
     Annulus_Angle=0;
     Annulus_Distance=0;
   }

}



/**
  * @brief  ·��tofʶ��
  * @param  None
  * @retval TOF����ģ���⣬ʹ�����ģ��IICͨ�ţ��������κ����Ŷ�����ʹ�ã�����Ҫע�ⲻ������
            ���á�TOFģ�����ϰ���ԽԶ��ֵԽ��Խ����ֵԽС
  */
void obstacle_avoidance(void)
{
	dl1a_get_distance();                                       //�������
	if(dl1a_finsh_flag==1&&dl1a_distance_mm<SET_DLLA_DISTANCE) //��������С���趨ֵ��־λ����
	{
		dl1a_finsh_flag=0;
		flag_obstacle=1;
	}
  		//��������
	  if(flag_obstacle==1)
		{
				 //BUZZ_ON;
				 //aim_speed=100;
				 Position_TOF = obstacle_Current_Dir[temp_TOF];
				 temp_TOF++;
				 if(temp==40)
				 {
					 temp=0;
					 flag_obstacle=0;
				   //aim_speed=400;
				   //BUZZ_OFF;
				 }
		}
}