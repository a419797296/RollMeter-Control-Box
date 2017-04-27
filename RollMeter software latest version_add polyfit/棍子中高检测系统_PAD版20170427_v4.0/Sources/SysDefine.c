#include "Include.h"
byte READ_FLAG;


word send_flg=0;    //发送第一个数据标志
byte mov_dir ;            //向左向右标志
byte battery_flg=100;      //电池电量大小
//byte battery_low=0;      //低电量标志
word i;              //全局变量
word g_idx=0;        //全局循环变量，不在中断里使用
void InitPort(void)
{
  DDRA_DDRA0=0;  //配置A0口位输入端口，用于测量编码器选装方向
  DDRA_DDRA2=0;  //配置A1口位输入端口，用于测量编码器圈数
  DDRA_DDRA4=1;  //位移传感器供电控制
  DDRA_DDRA6=1;  //低电量输出控制
  DDRB=0xff;
  //PORTB=0x00;
  LEDCPU_dir = 1;     //CPU指示灯输出
  LEDCPU=LED_OFF; 
}

