#include "Include.h"
byte READ_FLAG;


word send_flg=0;    //���͵�һ�����ݱ�־
byte mov_dir ;            //�������ұ�־
byte battery_flg=100;      //��ص�����С
//byte battery_low=0;      //�͵�����־
word i;              //ȫ�ֱ���
word g_idx=0;        //ȫ��ѭ�������������ж���ʹ��
void InitPort(void)
{
  DDRA_DDRA0=0;  //����A0��λ����˿ڣ����ڲ���������ѡװ����
  DDRA_DDRA2=0;  //����A1��λ����˿ڣ����ڲ���������Ȧ��
  DDRA_DDRA4=1;  //λ�ƴ������������
  DDRA_DDRA6=1;  //�͵����������
  DDRB=0xff;
  //PORTB=0x00;
  LEDCPU_dir = 1;     //CPUָʾ�����
  LEDCPU=LED_OFF; 
}

