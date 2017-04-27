# include "Include.h" 

unsigned int data1,data2;
unsigned int pulsenum;
unsigned int delaytime;
unsigned int time1;
unsigned int time2;
byte dir;
 
/************************************************************/
/*                    初始化ECT模块                         */
/************************************************************/
void initialize_ect(void){
  TSCR1_TFFCA = 1;  // 定时器标志位快速清除
  TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
  TIOS  = 0x0e;      //指定所有通道为输出比较方式     0x0f
  TCTL1 = 0x00;	    // 后四个通道设置为定时器与输出引脚断开
  TCTL2 = 0x00;     // 前四个通道设置为定时器与输出引脚断开
  TIE   = 0x01;     // 允许通道0定时中断
  TSCR2 = 0x07;	    // 预分频系数pr2-pr0:111,,时钟周期为4us,
  TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
  TFLG2 = 0xff;     // 清除自由定时器中断标志位
  PACTL = 0x50;      //始能脉冲累加器，累加上升沿
  TCTL4 = 0x01;	    // 设置通道0为捕捉上升沿方式
} 
/*************************************************************/
/*                   输入捕捉中断函数                        */
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
/*                    初始化ECT模块                         */
/************************************************************/
/*void initialize_ect(void){
  TSCR1_TFFCA = 1;  // 定时器标志位快速清除
  TSCR1_TEN = 1;    // 定时器使能位. 1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
  TIOS  = 0xfe;      //指定通道0为输入捕捉方式
  TCTL4 = 0x01;	    // 设置通道0为捕捉上升沿方式
  TIE   = 0x01;     // 允许通道0定时中断
  TSCR2 = 0x07;	    // 预分频系数pr2-pr0:111,时钟周期为4us,
  TFLG1 = 0xff;	    // 清除各IC/OC中断标志位
  TFLG2 = 0xff;     // 清除自由定时器中断标志位
}
      */
/*************************************************************/
/*                   输入捕捉中断函数                        */
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