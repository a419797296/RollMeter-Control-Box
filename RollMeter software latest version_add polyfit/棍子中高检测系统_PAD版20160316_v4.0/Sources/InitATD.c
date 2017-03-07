#include "Include.h"  



//*****************************************************************************
//函数名：InitATD
//参  数：无
//返回值：无
//功  能：AD初始化设置
//说  明：多通道转换，16路AD,从AD0开始，10位精度，数据右对齐，禁止中断使能，
//        采样前放电，快速自动清零
//日  期：
//*****************************************************************************

void InitATD(void)
{   
   // ATD0CTL0 = 0X0f;                   //设置回旋位
    /*
        0  ATD0CTL0_WRAP0 = 1;         //转换到15后，再从0开始
        1  ATD0CTL0_WRAP1 = 1;            
        2  ATD0CTL0_WRAP2 = 1;           
        3  ATD0CTL0_WRAP3 = 1;
    */
    ATD0CTL1 = 0X40;                   //设置转换精度、外部触发方式选择位；8位精度
    /*
       0   ATD0CTL1_ETRIGCH0 = 0;      //外部触发源选择位，下同    
       1   ATD0CTL1_ETRIGCH1 = 0;          
       2   ATD0CTL1_ETRIGCH2 = 0;          
       3   ATD0CTL1_ETRIGCH3 = 0;        
       4   ATD0CTL1_SMP_DIS  = 1;      //采样前放电    
       5*  ATD0CTL1_SRES0 = 1;         //SRES[1:0] = 00, AD Resolution = 8;  SRES[1:0] = 01, AD Resolution = 10  
       6*  ATD0CTL1_SRES1 = 0;         //SRES[1:0] = 10  AD Resolution = 12  SRES[1:0] = 11, AD Resolution = 保留 
       7*  ATD0CTL1_ETRIGSEL = 0;      //外部触发源选择位
    */         
    ATD0CTL2 = 0X40;                   //中断、外部触发方式、内部时钟（停止模式）；
    /*
        0   ATD0CTL2_ACMPIE = 0;       //0=禁止比较中断                                                                 
        1   ATD0CTL2_ASCIE = 0;        //0=禁止转换完成中断     
        2   ATD0CTL2_ETRIGE = 0;       //0=禁止外部触发模式使能     
        3*  ATD0CTL2_ETRIGP = 0;       //ETRIGLE   _ETRIGP      External Trigger Sensitivity
        4*  ATD0CTL2_ETRIGLE = 0;      //   0         0                 Falling edge
                                       //   0         1                 Rising edge
                                       //   1         0                 Low level
                                       //   1         1                 High level
        5*  ATD0CTL2_ICLKSTP = 1;      // 1 = 停止模式下选用内部时钟
        6*  ATD0CTL2_AFFC = 1;         //快速自动清零位；0=先读状态寄存器ATD0STAT1,再读结果寄存器CCF才清零；1=读结果寄存器自动清零 
    */
    ATD0CTL3 = 0x88;                   //
    /*
        0*  ATD0CTL3_FRZ0 = 0;         //FRZ=[1:0]=00 继续转换              FRZ=[1:0]=01 保留  
        1*  ATD0CTL3_FRZ1 = 0;         //FRZ=[1:0]=10 完成当前转换后冻结    FRZ=[1:0]=11 立即冻结 
        2*  ATD0CTL3_FIFO = 0;         //0=非先进先出模式，即转换完成后数据存在对应的结果寄存器中；1=结果依次存入结果寄存器    
        3*  ATD0CTL3_S1C = 0;          //转换序列长度选择位，即每次转换启用通道的个数；16路AD转换   
        4*  ATD0CTL3_S2C = 0;          //  
        5*  ATD0CTL3_S4C = 0;          //   
        6*  ATD0CTL3_S8C = 0;          //   
        7*  ATD0CTL3_DJM = 1;          //0=结果寄存器数据左对齐；1=右对齐
    */
    ATD0CTL4 = 0x07;                   //设置AD转换频率、第二阶段采样时间
    /*  
        0*  ATD0CTL4_PRS0 = 1;         //fATDCLK=fBUS/(PRS + 1)/2;       
        1*  ATD0CTL4_PRS1 = 1;         //fATDCLK=40M/(3+1)/2=5M    
        2*  ATD0CTL4_PRS2 = 0;              
        3*  ATD0CTL4_PRS3 = 0;              
        4*  ATD0CTL4_PRS4 = 0;             
        5*  ATD0CTL4_SMP0 = 0;         //第二阶段采样时间;SMP[7:5]=000 采样时间为AD转换周期的4倍     
        6*  ATD0CTL4_SMP1 = 0;         //                 SMP[7:5]=001 采样时间为AD转换周期的6倍
        7*  ATD0CTL4_SMP2 = 0;         //                 SMP[7:5]=010 采样时间为AD转换周期的8倍
    */
    //ATD0CTL5 = 0X30; 
    /*
        0*  ATD0CTL5_CA = 0;           //单通道模式下，选择哪个通道作为转化通道；多通道模式下，选择转换通道起始位    
        1*  ATD0CTL5_CB = 0;                
        2*  ATD0CTL5_CC = 0;                
        3*  ATD0CTL5_CD = 0;                
        4*  ATD0CTL5_MULT = 1;         //0=单通道转化；1=多通道    
        5*  ATD0CTL5_SCAN = 1;         //0=单次转换；1=多次持续转换    
        6   ATD0CTL5_SC = 0;           //0=不选用特殊通道；1=选用特殊通道
    */ 
    //ATD0DIEN = 0X00;                   //禁止数字输入
                          
}




//*****************************************************************************
//函数名： ReadATD
//参  数： ch
//返回值： 
//功  能：
//说  明：
//日  期：
//*****************************************************************************

unsigned int AD_capture(unsigned char chanel) 
{
 unsigned int AD_data;
 switch(chanel)
 { 
  case 0:
    ATD0CTL5 = 0x00;    //转换AD00
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 1:
    ATD0CTL5 = 0x01;    //转换AD01
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;
  
  case 2:
    ATD0CTL5 = 0x02;    //转换AD02
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;
 
  case 3:
    ATD0CTL5 = 0x03;    //转换AD03
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 4:
    ATD0CTL5 = 0x04;    //转换AD04
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 5:
    ATD0CTL5 = 0x05;    //转换AD05
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 6:
    ATD0CTL5 = 0x06;    //转换AD06
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 7:
    ATD0CTL5 = 0x07;    //转换AD07
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 8:
    ATD0CTL5 = 0x08;    //转换AD08
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 9:
    ATD0CTL5 = 0x09;    //转换AD09
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 10:
    ATD0CTL5 = 0x0a;    //转换AD10
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 11:
    ATD0CTL5 = 0x0b;    //转换AD11
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 12:
    ATD0CTL5 = 0x0c;    //转换AD12
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 13:
    ATD0CTL5 = 0x0d;    //转换AD13
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 14:
    ATD0CTL5 = 0x0e;    //转换AD14
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;

  case 15:
    ATD0CTL5 = 0x0f;    //转换AD15
    while(!ATD0STAT0_SCF);
    AD_data = ATD0DR0;
    break;
  
 }
 return(AD_data);
}


//*****************************************************************************
//函数名： ATD_Filte
//参  数： ch
//返回值： 
//功  能： ATD采集滤波
//说  明：
//日  期： 
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
     {     //如果初始化为10位
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