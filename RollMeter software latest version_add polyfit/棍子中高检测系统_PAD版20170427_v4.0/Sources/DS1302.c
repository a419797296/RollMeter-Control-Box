#include "Include.h" 

//dword  Sec,Min,Hor,Day,Mon,Week,Year;  

/****************ʮ����תBCD��****************/
uchar Z10BCD( uchar date)  //ʮ����תBCD��
{
   uchar i,j;
   i=date/10;
   j=date-(i*10);
    i=(i<<4)|j;  
   return (i);
}
/****************BCD��ת10����****************/
uchar BCDTO10( uchar date )   //BCD��ת10����
{
 uchar i,j;
 i=(date & 0xf0)>>4 ;
 j=date & 0x0f ;
 i=i*10+j;
 return i;
}
/****************1302����ʱ****************/
void delay_1302(void)
{
   int i;
   for(i=5;i>0;i--); 
}  
/***************������*****************/
void MCs(void)   //������
{
   CK=0;
   delay_1302();
   CK=1;
}
/****************�½���****************/
void  MCx(void)  //�½���
{
   CK=1;
   delay_1302();
   CK=0;   
}
/****************Bдһ���ֽڣ��ɵ͵���****************/
void WRdate( uchar date )  //дһ���ֽڣ��ɵ͵���
{
 uchar i;
 DDRA_DDRA5=1;
 delay_1302();
 for(i=0;i<8;i++)
 {
     IO = date & 0x01 ;  //��������������ǰ׼����
     delay_1302();
     MCs();  //������ʱ��д��
     date>>=1;    
 } 
}
/****************��һ���ֽ�****************/
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
  MCx();  //�½��ض������� 
  date>>=1;      
 }
 return date;
}
/****************��ȡĳ��ַ������****************/
uchar  RE1302( uchar addr )
{
 uchar Date;
 RST=0;
    CK=0;
 RST=1; //CKΪ0ʱ��RST����Ϊ1��Ȼ����ܶ�д
 WRdate(addr); //д��ַ
 delay_1302();
 Date=REdate(); //������
 delay_1302();
 CK=1;
 RST=0;
 return (Date); 
}
/****************��ĳ��ַд����****************/
void  WR1302( uchar addr,uchar Date ) //
{
 RST=0;
 CK=0;
 RST=1; //CKΪ0ʱ��RST����Ϊ1��Ȼ����ܶ�д
 delay_1302();
 WRdate(addr); //д��ַ
 delay_1302();
 WRdate(Date); //д����
 CK=1;
 RST=0;
}

/****************��ʼ��ʱ��****************/
void  Initime(uchar sec,uchar min,uchar hor,uchar day,uchar yue,uchar week,uchar year)
{
 WR1302(0x8E,0X00);  // 0X8E��WPд������ַ�����λ��0��ʾ����д
 
 WR1302( 0x80, Z10BCD( sec ) );  //���뵥Ԫ����ֵ
 WR1302( 0x82, Z10BCD( min ) );  //��ֵ�Ԫ����ֵ
 WR1302( 0x84, Z10BCD( hor ) );  //��ʱ��Ԫ����ֵ
 WR1302( 0x86, Z10BCD( day ) );  //���յ�Ԫ����ֵ
 WR1302( 0x88, Z10BCD( yue ) );  //���µ�Ԫ����ֵ
 WR1302( 0x8a, Z10BCD( week) );  //���ܵ�Ԫ����ֵ
 WR1302( 0x8c, Z10BCD( year) );  //���굥Ԫ����ֵ
}
/****************��ʼ��ʱ��****************/ 
void Init_read_time(void)
{
  WR1302(0x8E,0X80);  // 0X8E��WPд������ַ�����λ��1��ʾд������ֻ�ܶ�
  
  WR1302(0x90,0XA7);  //0x90�ǳ�����õ�ַ��0XA7��ʾһ�������ܴ���һ��8K����
}
