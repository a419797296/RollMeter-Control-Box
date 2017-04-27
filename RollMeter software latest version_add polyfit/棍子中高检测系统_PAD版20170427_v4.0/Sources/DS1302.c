#include "Include.h" 

//dword  Sec,Min,Hor,Day,Mon,Week,Year;  

/****************十进制转BCD码****************/
uchar Z10BCD( uchar date)  //十进制转BCD码
{
   uchar i,j;
   i=date/10;
   j=date-(i*10);
    i=(i<<4)|j;  
   return (i);
}
/****************BCD码转10进制****************/
uchar BCDTO10( uchar date )   //BCD码转10进制
{
 uchar i,j;
 i=(date & 0xf0)>>4 ;
 j=date & 0x0f ;
 i=i*10+j;
 return i;
}
/****************1302短延时****************/
void delay_1302(void)
{
   int i;
   for(i=5;i>0;i--); 
}  
/***************上升沿*****************/
void MCs(void)   //上升沿
{
   CK=0;
   delay_1302();
   CK=1;
}
/****************下降沿****************/
void  MCx(void)  //下降沿
{
   CK=1;
   delay_1302();
   CK=0;   
}
/****************B写一个字节，由低到高****************/
void WRdate( uchar date )  //写一个字节，由低到高
{
 uchar i;
 DDRA_DDRA5=1;
 delay_1302();
 for(i=0;i<8;i++)
 {
     IO = date & 0x01 ;  //数据在上升沿以前准备好
     delay_1302();
     MCs();  //上升沿时刻写入
     date>>=1;    
 } 
}
/****************读一个字节****************/
uchar REdate()
{
 uchar i,date=0;
 DDRA_DDRA5=0;
 delay_1302();
 for(i=0;i<8;i++)
 { 
  if(IO)
  {
   date|=0x80;
  }
  delay_1302();
  MCx();  //下降沿读出数据 
  date>>=1;      
 }
 return date;
}
/****************读取某地址的数据****************/
uchar  RE1302( uchar addr )
{
 uchar Date;
 RST=0;
    CK=0;
 RST=1; //CK为0时，RST才能为1，然后才能读写
 WRdate(addr); //写地址
 delay_1302();
 Date=REdate(); //读数据
 delay_1302();
 CK=1;
 RST=0;
 return (Date); 
}
/****************给某地址写数据****************/
void  WR1302( uchar addr,uchar Date ) //
{
 RST=0;
 CK=0;
 RST=1; //CK为0时，RST才能为1，然后才能读写
 delay_1302();
 WRdate(addr); //写地址
 delay_1302();
 WRdate(Date); //写数据
 CK=1;
 RST=0;
}

/****************初始化时间****************/
void  Initime(uchar sec,uchar min,uchar hor,uchar day,uchar yue,uchar week,uchar year)
{
 WR1302(0x8E,0X00);  // 0X8E是WP写保护地址，最高位赋0表示可以写
 
 WR1302( 0x80, Z10BCD( sec ) );  //向秒单元赋初值
 WR1302( 0x82, Z10BCD( min ) );  //向分单元赋初值
 WR1302( 0x84, Z10BCD( hor ) );  //向时单元赋初值
 WR1302( 0x86, Z10BCD( day ) );  //向日单元赋初值
 WR1302( 0x88, Z10BCD( yue ) );  //向月单元赋初值
 WR1302( 0x8a, Z10BCD( week) );  //向周单元赋初值
 WR1302( 0x8c, Z10BCD( year) );  //向年单元赋初值
}
/****************开始读时间****************/ 
void Init_read_time(void)
{
  WR1302(0x8E,0X80);  // 0X8E是WP写保护地址，最高位赋1表示写保护，只能读
  
  WR1302(0x90,0XA7);  //0x90是充电设置地址，0XA7表示一个二极管串联一个8K电阻
}
