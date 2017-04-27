# include "Include.h"

/*************************************************************/
/*                     PIT模块初始化函数                     */
/*************************************************************/
/* void init_PIT(){
 
 PITMTLD0=249;     //为0通道8位计数器赋值
 PITLD0=63999;     //为0通道16位计数器赋值   //(249+1)*(63999+1)=16000000个总线周期=0.5秒
 PITMUX_PMUX0=0;   //第0通道使用微计数器0
 PITCE_PCE0=1;     //第0通道计数器工作 
 PITCFLMT=0X80;    //使能周期中断定时器
 PITINTE_PINTE0=1; //0通道定时器定时中断被使能
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
//函数名：InitPIT
//参  数：无
//返回值：无
//功  能：初始化定时器模块
//说  明：总线时钟周期 1/40M=25ns 定时器周期=(PITMTLD+1)*(PITLD+1)*25
//日  期：2011年8月26日1:11:00
//*****************************************************************************
void InitPIT(void)
{
    PITCFLMT |=0X00;                   //定时器模块使能，工作方式选择，8位重装初值控制位
    /*
    0   PITCFLMT_PFLMT0 = 0;           //0=禁止8位重装初值；1=使能8位重装初值   
    1   PITCFLMT_PFLMT1 = 0;           //     
    5   PITCFLMT_PITFRZ = 0;           //冻结模式下计数器工作方式；0=正常计数；1=冻结   
    6   PITCFLMT_PITSWAI = 0;          //等待模式选择位     
    7   PITCFLMT_PITE = 0;             //定时器模块使能位；0=禁止；1=使能
    */
    
    PITMTLD0 = (20 - 1);              //8位微定时器0初值 指令周期25ns
    PITMTLD1 = (200 - 1);              //
    PITLD0 = (50000 - 1);                //16位定时器0初值 定时周期=200*50000*25ns=250ms
    PITLD1 = (5000 - 1);                //                定时周期=200*10000*25ns=50ms
    
    PITMUX = 0x03;                     //时基选择位；0=选择0时基；1=选择1时基
    /*
        0   PMUX0 = 0;                 //定时器0选择0时基；                          
        1   PMUX1 = 1;                 //定时器1选择1时基；                            
        2   PMUX2 = 0;                 //                          
        3   PMUX3 = 0;                 //
    */
     
    PITCE = 0x03;                      //相应通道使能位；1=使能
    /*
        0   PITCE_PCE0 = 1;            //0=定时器0禁止；1=定时器0使能          
        1   PITCE_PCE1 = 1;            //         
        2   PITCE_PCE2 = 0;            //         
        3   PITCE_PCE3 = 0;            //
    */      
                                       
    PITINTE = 0x03;                    //相应中断允许位
    /*
        0   PITINTE_PINTE0 = 1;        //0=定时器0中断禁止；1=使能        
        1   PITINTE_PINTE1 = 1;        //        
        2   PITINTE_PINTE2 = 0;        //         
        3   PITINTE_PINTE3 = 0;        //
    */
    PITCFLMT |=0X80;                   //定时器模块使能
    /*
        7   PITCFLMT_PITE = 1;         //定时器模块使能
    */
    
}



/***********************定时器0中断服务程序**********************************/
/*# pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 66 PIT0(void)            //定时器0 选用0时基 s3
{
    DisableInterrupts;
  	PITCFLMT_PITE=0; //定时中断通道0关
  	
  	LEDCPU=~LEDCPU;
    Send1SCI(0,'A');
    
    
    PACNT=0; //清计数位  
    PITTF = 0x01;////清中断标志位 
    PITCFLMT_PITE=1;//定时器通道0使能
    EnableInterrupts;
}
# pragma CODE_SEG DEFAULT

*/

/************************定时器1中断服务程序********
**************************/
# pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 67 PIT1(void)            //定时器1 选用1时基 s5 50ms
{   
    
  	PITCFLMT_PITE=0; //定时中断通道0关

    //LEDCPU=~LEDCPU;
      
    data1 = data2;
    data2 = PACNT;
    pulsenum = data2-data1;   //计算1秒钟采集的上升沿的数量

    if(dir)           //判断编码器方向
    {
        
        pulse_sum+=pulsenum;
        if(pulse_sum>pulse_change)
        {
          pulse_change=pulse_sum;
          if(pulse_sum<pulse_max)
          {
              if(pulse_sum*stick_peri/Encoder/sample_dist/10==pulse_add)       //如果距离是所设定的倍数
              {
                  pulse_add+=1;
                  send_point();                        
              }
          }
          else
          {         
              pulse_max=0;
              TIE=0x00;                //处理数据的时候关中断
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
    PITCFLMT_PITE=1;//定时器通道0使能
    EnableInterrupts;
    //SYS_POWER=LED_ON;
    
}
# pragma CODE_SEG DEFAULT



/***********************定时器2中断服务程序***********************************/
/*
# pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 68 PIT0(void)            //定时器1 选用1时基 s5 50ms
{   
 //   LED3 = ~LED3;
    PITTF = 0x04;
}
# pragma CODE_SEG DEFAULT
*/

/************************定时器3中断服务程序**********************************/
/*
# pragma CODE_SEG __NEAR_SEG NON_BANKED //指示该程序在不分页区
void interrupt 69 PIT3(void)            //定时器1 选用1时基 s5 50ms
{   
 //   LED3 = ~LED3;
    PITTF = 0x08;
}
# pragma CODE_SEG DEFAULT
*/





/*************************************************************/
/*                       初始化实时中断                      */
/*************************************************************/
/*void INIT_RTI(void)
{
  CRGINT = 0x80;       //使能实时中断
  RTICTL = 0x6f;       //设置实时中断的时间间隔为32.768ms
}
*/
/*************************************************************/
/*                       实时中断函数                        */
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
    LEDCPU = ~LEDCPU;    //大约0.5s将指示灯翻转一次
  }
}
#pragma CODE_SEG DEFAULT

*/
