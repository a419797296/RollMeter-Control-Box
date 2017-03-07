#include "Include.h"  

#define BAUD0 9600                    //串口波特率
#define BAUD1 9600                    //串口波特率

unsigned char data_receive;
//*****************************************************************************
//函数名：
//参  数：
//返回值：
//功  能：
//说  明：
//日  期：
//*****************************************************************************


//*****************************************************************************
//函数名：InitSCI
//参  数：无
//返回值：无
//功  能：初始化串行通信
//说  明：总线时钟40M,设置波特率为9600=40M/(16*260),正常码输出，8位数据，无校验，
//        禁止中断，查询方式收发, 
//日  期：2011年8月16日5:59:09
//*****************************************************************************
void InitSCI(void)
{
  SCI0BD = BUS_CLOCK/16/BAUD0;   //设置SCI0波特率为9600
  SCI0CR1 = 0x00;       //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI0CR2 = 0x2C;       //允许发送数据，禁止中断功能  
  SCI1BD = BUS_CLOCK/16/BAUD1;   //设置SCI0波特率为9600
  SCI1CR1 = 0x00;       //设置SCI0为正常模式，八位数据位，无奇偶校验
  SCI1CR2 = 0x0C;       //允许发送数据，禁止中断功能           
}


//*****************************************************************************
//函数名：Send1SCI
//参  数：data
//返回值：无
//功  能：发送单个字符
//说  明：
//日  期：2011年8月20日1:22:57
//*****************************************************************************
void Send1SCI(char num,byte data )    //SCI chanle
{
    if(!num)
    { 
      while ( !SCI0SR1_TDRE  );    //等待TDRE置1，即发送数据寄存器为空
      SCI0DRL = data;                    //向发送数数据寄存器写数据
    } 
    else
    { 
      while ( !SCI1SR1_TDRE  );    //等待TDRE置1，即发送数据寄存器为空
      SCI1DRL = data;                    //向发送数数据寄存器写数据
    }
}




//*****************************************************************************
//函数名：SendNSCI
//参  数：n = 字节个数 
//返回值：无
//功  能：发送n字节
//说  明：
//日  期：2011年8月20日1:23:38
//*****************************************************************************
void SendNSCI(char num, byte ch[], word N_byte)
{
    word i;
    for ( i = 0;  i<N_byte; i++)

       Send1SCI(num,ch[i] );  
}

//*****************************************************************************
//函数名：SendStringSCI
//参  数：ch[]字符串
//返回值：无
//功  能：发送字符串
//说  明：内部调用Send1SCI()
//日  期：2011年8月18日1:43:58
//*****************************************************************************
void SendStringSCI(char num,byte ch[] )
{
    byte i = 0;
    while (ch[i]!='\0')                      //判断是否等于\0空字符
    {
        Send1SCI(num,ch[i++]);
    }
}


//*****************************************************************************
//函数名：Re1SCI
//参  数：无
//返回值：接收到得值
//功  能：接收单个字符
//说  明：
//日  期：2011年8月20日1:24:25
//*****************************************************************************
byte  Re1SCI(char num) 
{
  if(!num) 
  {
      while(!SCI0SR1_RDRF);          //等待发送数据寄存器满
      return(SCI0DRL);
  } 
  else
  {
      while(!SCI1SR1_RDRF);          //等待发送数据寄存器满
      return(SCI1DRL);
  }

}



//*****************************************************************************
//函数名：ReNSCI
//参  数：无
//返回值：无
//功  能：发送字符串
//说  明：
//日  期：2011年8月20日1:25:17
//***************************************************************************** 
void ReNSCI(char num,byte *get)
{    
    byte j;
    for (j = 0; j < 100; j++)
    {
        
        get[j] = Re1SCI(num);
        
    }   
}



/*************************************************************/
/*                     串口中断接收函数                      */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 20 receivedata(void) 
{
    data_receive = Re1SCI(0);
    if(READ_FLAG==CONFIG_RIGHT||READ_FLAG==CONFIG_LEFT)
    {
        *(read_tmp+g_idx++)=data_receive;
        if(g_idx==5)
        {
          
           READ_FLAG=0;
           g_idx=0;
           stick_length=read_tmp[0]<<8|read_tmp[1] ;
           sample_dist= read_tmp[2];
           stick_peri=read_tmp[3]<<8|read_tmp[4] ;
           pulse_step= (long)Encoder*sample_dist*10/stick_peri;       //采样脉冲数
           pulse_max=(long)Encoder*stick_length*10/stick_peri;       //测量最大脉冲数
           pulse_sum=0;
           READ_FLAG=FINISH_CONFIG;
        }
    } 
    if(data_receive==0xff)
    {
      mov_dir= CONFIG_RIGHT;
      READ_FLAG=CONFIG_RIGHT;
    }
    if(data_receive==0xfe)
    {
      mov_dir= CONFIG_LEFT;
      READ_FLAG=CONFIG_LEFT;   
    }
}
#pragma CODE_SEG DEFAULT
