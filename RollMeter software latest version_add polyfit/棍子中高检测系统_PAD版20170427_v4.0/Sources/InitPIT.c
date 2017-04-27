# include "Include.h"

/*************************************************************/
/*                     PITģ���ʼ������                     */
/*************************************************************/
/* void init_PIT(){
 
 PITMTLD0=249;     //Ϊ0ͨ��8λ��������ֵ
 PITLD0=63999;     //Ϊ0ͨ��16λ��������ֵ   //(249+1)*(63999+1)=16000000����������=0.5��
 PITMUX_PMUX0=0;   //��0ͨ��ʹ��΢������0
 PITCE_PCE0=1;     //��0ͨ������������ 
 PITCFLMT=0X80;    //ʹ�������ж϶�ʱ��
 PITINTE_PINTE0=1; //0ͨ����ʱ����ʱ�жϱ�ʹ��
 }

#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PIT_INTER(void) 
{
    if(PITTF_PTF0==1) {
      
      PITTF_PTF0=1;            
      LEDCPU=~LEDCPU;
    }
}
#pragma CODE_SEG DEFAULT  */

//*****************************************************************************
//��������InitPIT�R
//��  ������
//����ֵ����
//��  �ܣ���ʼ����ʱ��ģ��
//˵  ��������ʱ������ 1/40M=25ns ��ʱ������=(PITMTLD+1)*(PITLD+1)*25
//��  �ڣ�2011��8��26��1:11:00
//*****************************************************************************
void InitPIT(void)
{
    PITCFLMT |=0X00;                   //��ʱ��ģ��ʹ�ܣ�������ʽѡ��8λ��װ��ֵ����λ
    /*
    0   PITCFLMT_PFLMT0 = 0;           //0=��ֹ8λ��װ��ֵ��1=ʹ��8λ��װ��ֵ   
    1   PITCFLMT_PFLMT1 = 0;           //     
    5   PITCFLMT_PITFRZ = 0;           //����ģʽ�¼�����������ʽ��0=����������1=����   
    6   PITCFLMT_PITSWAI = 0;          //�ȴ�ģʽѡ��λ     
    7   PITCFLMT_PITE = 0;             //��ʱ��ģ��ʹ��λ��0=��ֹ��1=ʹ��
    */
    
    PITMTLD0 = (20 - 1);              //8λ΢��ʱ��0��ֵ ָ������25ns
    PITMTLD1 = (200 - 1);              //
    PITLD0 = (50000 - 1);                //16λ��ʱ��0��ֵ ��ʱ����=200*50000*25ns=250ms
    PITLD1 = (5000 - 1);                //                ��ʱ����=200*10000*25ns=50ms
    
    PITMUX = 0x03;                     //ʱ��ѡ��λ��0=ѡ��0ʱ����1=ѡ��1ʱ��
    /*
        0   PMUX0 = 0;                 //��ʱ��0ѡ��0ʱ����                          
        1   PMUX1 = 1;                 //��ʱ��1ѡ��1ʱ����                            
        2   PMUX2 = 0;                 //                          
        3   PMUX3 = 0;                 //
    */
     
    PITCE = 0x03;                      //��Ӧͨ��ʹ��λ��1=ʹ��
    /*
        0   PITCE_PCE0 = 1;            //0=��ʱ��0��ֹ��1=��ʱ��0ʹ��          
        1   PITCE_PCE1 = 1;            //         
        2   PITCE_PCE2 = 0;            //         
        3   PITCE_PCE3 = 0;            //
    */      
                                       
    PITINTE = 0x03;                    //��Ӧ�ж�����λ
    /*
        0   PITINTE_PINTE0 = 1;        //0=��ʱ��0�жϽ�ֹ��1=ʹ��        
        1   PITINTE_PINTE1 = 1;        //        
        2   PITINTE_PINTE2 = 0;        //         
        3   PITINTE_PINTE3 = 0;        //
    */
    PITCFLMT |=0X80;                   //��ʱ��ģ��ʹ��
    /*
        7   PITCFLMT_PITE = 1;         //��ʱ��ģ��ʹ��
    */
    
}



/***********************��ʱ��0�жϷ������**********************************/
/*# pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 66 PIT0(void)            //��ʱ��0 ѡ��0ʱ�� s3
{
    DisableInterrupts;
  	PITCFLMT_PITE=0; //��ʱ�ж�ͨ��0��
  	
  	LEDCPU=~LEDCPU;
    Send1SCI(0,'A');
    
    
    PACNT=0; //�����λ  
    PITTF = 0x01;////���жϱ�־λ 
    PITCFLMT_PITE=1;//��ʱ��ͨ��0ʹ��
    EnableInterrupts;
}
# pragma CODE_SEG DEFAULT

*/

/************************��ʱ��1�жϷ������********
**************************/
# pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 67 PIT1(void)            //��ʱ��1 ѡ��1ʱ�� s5 50ms
{   
    
  	PITCFLMT_PITE=0; //��ʱ�ж�ͨ��0��

    //LEDCPU=~LEDCPU;
      
    data1 = data2;
    data2 = PACNT;
    pulsenum = data2-data1;   //����1���Ӳɼ��������ص�����

    if(dir)           //�жϱ���������
    {
        
        pulse_sum+=pulsenum;
        if(pulse_sum>pulse_change)
        {
          pulse_change=pulse_sum;
          if(pulse_sum<pulse_max)
          {
              if(pulse_sum*stick_peri/Encoder/sample_dist/10==pulse_add)       //������������趨�ı���
              {
                  pulse_add+=1;
                  send_point();                        
              }
          }
          else
          {         
              pulse_max=0;
              TIE=0x00;                //�������ݵ�ʱ����ж�
              PITINTE=0x00;
              
          }
          
        }
        else
          ;
        
    }
    else
    {
        
        pulse_sum-=pulsenum;
        if(pulse_sum<0)   //smaller than 0
          pulse_sum=0;  
    }
       
    PITTF = 0x02;   
    PITCFLMT_PITE=1;//��ʱ��ͨ��0ʹ��
    EnableInterrupts;
    //SYS_POWER=LED_ON;
    
}
# pragma CODE_SEG DEFAULT



/***********************��ʱ��2�жϷ������***********************************/
/*
# pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 68 PIT0(void)            //��ʱ��1 ѡ��1ʱ�� s5 50ms
{   
 //   LED3 = ~LED3;
    PITTF = 0x04;
}
# pragma CODE_SEG DEFAULT
*/

/************************��ʱ��3�жϷ������**********************************/
/*
# pragma CODE_SEG __NEAR_SEG NON_BANKED //ָʾ�ó����ڲ���ҳ��
void interrupt 69 PIT3(void)            //��ʱ��1 ѡ��1ʱ�� s5 50ms
{   
 //   LED3 = ~LED3;
    PITTF = 0x08;
}
# pragma CODE_SEG DEFAULT
*/





/*************************************************************/
/*                       ��ʼ��ʵʱ�ж�                      */
/*************************************************************/
/*void INIT_RTI(void)
{
  CRGINT = 0x80;       //ʹ��ʵʱ�ж�
  RTICTL = 0x6f;       //����ʵʱ�жϵ�ʱ����Ϊ32.768ms
}
*/
/*************************************************************/
/*                       ʵʱ�жϺ���                        */
/*************************************************************/
/*#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void RTI_inter(void)
{
  if(CRGFLG_RTIF == 1)
    CRGFLG_RTIF = 1;
  count += 1;
  if(count == 15)
  {
    count = 0;
    LEDCPU = ~LEDCPU;    //��Լ0.5s��ָʾ�Ʒ�תһ��
  }
}
#pragma CODE_SEG DEFAULT

*/
