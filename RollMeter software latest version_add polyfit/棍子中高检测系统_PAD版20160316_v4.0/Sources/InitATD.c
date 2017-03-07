#include "Include.h"  



//*****************************************************************************
//��������InitATD�R
//��  ������
//����ֵ����
//��  �ܣ�AD��ʼ������
//˵  ������ͨ��ת����16·AD,��AD0��ʼ��10λ���ȣ������Ҷ��룬��ֹ�ж�ʹ�ܣ�
//        ����ǰ�ŵ磬�����Զ�����
//��  �ڣ�
//*****************************************************************************

void InitATD(void)
{   
   // ATD0CTL0 = 0X0f;                   //���û���λ
    /*
        0  ATD0CTL0_WRAP0 = 1;         //ת����15���ٴ�0��ʼ
        1  ATD0CTL0_WRAP1 = 1;            
        2  ATD0CTL0_WRAP2 = 1;           
        3  ATD0CTL0_WRAP3 = 1;
    */
    ATD0CTL1 = 0X40;                   //����ת�����ȡ��ⲿ������ʽѡ��λ��8λ����
    /*
       0   ATD0CTL1_ETRIGCH0 = 0;      //�ⲿ����Դѡ��λ����ͬ    
       1   ATD0CTL1_ETRIGCH1 = 0;          
       2   ATD0CTL1_ETRIGCH2 = 0;          
       3   ATD0CTL1_ETRIGCH3 = 0;        
       4   ATD0CTL1_SMP_DIS  = 1;      //����ǰ�ŵ�    
       5*  ATD0CTL1_SRES0 = 1;         //SRES[1:0] = 00, AD Resolution = 8;  SRES[1:0] = 01, AD Resolution = 10  
       6*  ATD0CTL1_SRES1 = 0;         //SRES[1:0] = 10  AD Resolution = 12  SRES[1:0] = 11, AD Resolution = ���� 
       7*  ATD0CTL1_ETRIGSEL = 0;      //�ⲿ����Դѡ��λ
    */         
    ATD0CTL2 = 0X40;                   //�жϡ��ⲿ������ʽ���ڲ�ʱ�ӣ�ֹͣģʽ����
    /*
        0   ATD0CTL2_ACMPIE = 0;       //0=��ֹ�Ƚ��ж�                                                                 
        1   ATD0CTL2_ASCIE = 0;        //0=��ֹת������ж�     
        2   ATD0CTL2_ETRIGE = 0;       //0=��ֹ�ⲿ����ģʽʹ��     
        3*  ATD0CTL2_ETRIGP = 0;       //ETRIGLE   _ETRIGP      External Trigger Sensitivity
        4*  ATD0CTL2_ETRIGLE = 0;      //   0         0                 Falling edge
                                       //   0         1                 Rising edge
                                       //   1         0                 Low level
                                       //   1         1                 High level
        5*  ATD0CTL2_ICLKSTP = 1;      // 1 = ֹͣģʽ��ѡ���ڲ�ʱ��
        6*  ATD0CTL2_AFFC = 1;         //�����Զ�����λ��0=�ȶ�״̬�Ĵ���ATD0STAT1,�ٶ�����Ĵ���CCF�����㣻1=������Ĵ����Զ����� 
    */
    ATD0CTL3 = 0x88;                   //
    /*
        0*  ATD0CTL3_FRZ0 = 0;         //FRZ=[1:0]=00 ����ת��              FRZ=[1:0]=01 ����  
        1*  ATD0CTL3_FRZ1 = 0;         //FRZ=[1:0]=10 ��ɵ�ǰת���󶳽�    FRZ=[1:0]=11 �������� 
        2*  ATD0CTL3_FIFO = 0;         //0=���Ƚ��ȳ�ģʽ����ת����ɺ����ݴ��ڶ�Ӧ�Ľ���Ĵ����У�1=������δ������Ĵ���    
        3*  ATD0CTL3_S1C = 0;          //ת�����г���ѡ��λ����ÿ��ת������ͨ���ĸ�����16·ADת��   
        4*  ATD0CTL3_S2C = 0;          //  
        5*  ATD0CTL3_S4C = 0;          //   
        6*  ATD0CTL3_S8C = 0;          //   
        7*  ATD0CTL3_DJM = 1;          //0=����Ĵ�����������룻1=�Ҷ���
    */
    ATD0CTL4 = 0x07;                   //����ADת��Ƶ�ʡ��ڶ��׶β���ʱ��
    /*  
        0*  ATD0CTL4_PRS0 = 1;         //fATDCLK=fBUS/(PRS + 1)/2;       
        1*  ATD0CTL4_PRS1 = 1;         //fATDCLK=40M/(3+1)/2=5M    
        2*  ATD0CTL4_PRS2 = 0;              
        3*  ATD0CTL4_PRS3 = 0;              
        4*  ATD0CTL4_PRS4 = 0;             
        5*  ATD0CTL4_SMP0 = 0;         //�ڶ��׶β���ʱ��;SMP[7:5]=000 ����ʱ��ΪADת�����ڵ�4��     
        6*  ATD0CTL4_SMP1 = 0;         //                 SMP[7:5]=001 ����ʱ��ΪADת�����ڵ�6��
        7*  ATD0CTL4_SMP2 = 0;         //                 SMP[7:5]=010 ����ʱ��ΪADת�����ڵ�8��
    */
    //ATD0CTL5 = 0X30; 
    /*
        0*  ATD0CTL5_CA = 0;           //��ͨ��ģʽ�£�ѡ���ĸ�ͨ����Ϊת��ͨ������ͨ��ģʽ�£�ѡ��ת��ͨ����ʼλ    
        1*  ATD0CTL5_CB = 0;                
        2*  ATD0CTL5_CC = 0;                
        3*  ATD0CTL5_CD = 0;                
        4*  ATD0CTL5_MULT = 1;         //0=��ͨ��ת����1=��ͨ��    
        5*  ATD0CTL5_SCAN = 1;         //0=����ת����1=��γ���ת��    
        6   ATD0CTL5_SC = 0;           //0=��ѡ������ͨ����1=ѡ������ͨ��
    */ 
    //ATD0DIEN = 0X00;                   //��ֹ��������
                          
}




//*****************************************************************************
//�������� ReadATD�R
//��  ���� ch
//����ֵ�� 
//��  �ܣ�
//˵  ����
//��  �ڣ�
//*****************************************************************************

unsigned int AD_capture(unsigned char chanel) 
{
 unsigned int AD_data;
 switch(chanel)
 { 
  case 0:
    ATD0CTL5 = 0x00;    //ת��AD00
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 1:
    ATD0CTL5 = 0x01;    //ת��AD01
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;
  
  case 2:
    ATD0CTL5 = 0x02;    //ת��AD02
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;
 
  case 3:
    ATD0CTL5 = 0x03;    //ת��AD03
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 4:
    ATD0CTL5 = 0x04;    //ת��AD04
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 5:
    ATD0CTL5 = 0x05;    //ת��AD05
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 6:
    ATD0CTL5 = 0x06;    //ת��AD06
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 7:
    ATD0CTL5 = 0x07;    //ת��AD07
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 8:
    ATD0CTL5 = 0x08;    //ת��AD08
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 9:
    ATD0CTL5 = 0x09;    //ת��AD09
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 10:
    ATD0CTL5 = 0x0a;    //ת��AD10
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 11:
    ATD0CTL5 = 0x0b;    //ת��AD11
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 12:
    ATD0CTL5 = 0x0c;    //ת��AD12
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 13:
    ATD0CTL5 = 0x0d;    //ת��AD13
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 14:
    ATD0CTL5 = 0x0e;    //ת��AD14
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 15:
    ATD0CTL5 = 0x0f;    //ת��AD15
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;
  
 }
 return(AD_data);
}


//*****************************************************************************
//�������� ATD_Filte�R
//��  ���� ch
//����ֵ�� 
//��  �ܣ� ATD�ɼ��˲�
//˵  ����
//��  �ڣ� 
//*****************************************************************************
int ATD_Filte(int N_num,int chanel)
{
     uint ATD[20]={0},Max=0,Min=5000;
     uint Votage=0;
     long tmp,Sum=0;
     for(i=0;i<N_num;i++)
     {
        ATD[i]=AD_capture(chanel);
        Max>ATD[i] ? (Max=Max):(Max=ATD[i]);
        Min<ATD[i] ? (Min=Min):(Min=ATD[i]);
        Sum+=ATD[i];
     }
     Votage=(Sum-Max-Min)/(N_num-2);
     if(ATD0CTL1==0x40)
     {     //�����ʼ��Ϊ10λ
        tmp=(long)5000*Votage;
        Votage=tmp>>12;
     }
     else if(ATD0CTL1==0x20) 
     {

        tmp=(long)5000*Votage;
        Votage=tmp>>10; 
     } 
     else if(ATD0CTL1==0x00) 
     {
        
        tmp=(long)5000*Votage;
        Votage=tmp>>8; 
     }

    
     return Votage;
  
}