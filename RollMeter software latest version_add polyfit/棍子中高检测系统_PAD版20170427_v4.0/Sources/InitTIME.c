# include "Include.h" 

unsigned int data1,data2;
unsigned int pulsenum;
unsigned int delaytime;
unsigned int time1;
unsigned int time2;
byte dir;
 
/************************************************************/
/*                    ��ʼ��ECTģ��                         */
/************************************************************/
void initialize_ect(void){
  TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
  TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
  TIOS  = 0x0e;      //ָ������ͨ��Ϊ����ȽϷ�ʽ     0x0f
  TCTL1 = 0x00;	    // ���ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
  TCTL2 = 0x00;     // ǰ�ĸ�ͨ������Ϊ��ʱ����������ŶϿ�
  TIE   = 0x01;     // ����ͨ��0��ʱ�ж�
  TSCR2 = 0x07;	    // Ԥ��Ƶϵ��pr2-pr0:111,,ʱ������Ϊ4us,
  TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
  TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ
  PACTL = 0x50;      //ʼ�������ۼ������ۼ�������
  TCTL4 = 0x01;	    // ����ͨ��0Ϊ��׽�����ط�ʽ
} 
/*************************************************************/
/*                   ���벶׽�жϺ���                        */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 8 capture(void) 
{
  //DisableInterrupts 
 if(TFLG1_C0F == 1)
   TFLG1_C0F = 1;
 
     if(mov_dir==CONFIG_RIGHT)
        dir=PORTA_PA0;
     if(mov_dir==CONFIG_LEFT)
        dir=!PORTA_PA0;     
     time1 = time2;
     time2 = TC0;
     delaytime = time2-time1;
     //LEDCPU = ~LEDCPU;
     //PORTB=0XF0;

 

 //delay1ms(200);
//EnableInterrupts
}                           
#pragma CODE_SEG DEFAULT

/************************************************************/
/*                    ��ʼ��ECTģ��                         */
/************************************************************/
/*void initialize_ect(void){
  TSCR1_TFFCA = 1;  // ��ʱ����־λ�������
  TSCR1_TEN = 1;    // ��ʱ��ʹ��λ. 1=����ʱ����������; 0=ʹ����ʱ����������(����������)
  TIOS  = 0xfe;      //ָ��ͨ��0Ϊ���벶׽��ʽ
  TCTL4 = 0x01;	    // ����ͨ��0Ϊ��׽�����ط�ʽ
  TIE   = 0x01;     // ����ͨ��0��ʱ�ж�
  TSCR2 = 0x07;	    // Ԥ��Ƶϵ��pr2-pr0:111,ʱ������Ϊ4us,
  TFLG1 = 0xff;	    // �����IC/OC�жϱ�־λ
  TFLG2 = 0xff;     // ������ɶ�ʱ���жϱ�־λ
}
      */
/*************************************************************/
/*                   ���벶׽�жϺ���                        */
/*************************************************************/
/*#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void capture(void) 
{
 if(TFLG1_C0F == 1)
   TFLG1_C0F = 1;
 
 dir=PORTA_PA0;
 time1 = time2;
 time2 = TC0;
 delaytime = time2-time1;
 LEDCPU = ~LEDCPU;
}
#pragma CODE_SEG DEFAULT   */