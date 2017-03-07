# ifndef _DS1302_H_
# define _DS1302_H_

#define  RST  PORTA_PA3
#define  CK   PORTA_PA7
#define  IO   PORTA_PA5





//extern dword  Sec,Min,Hor,Day,Mon,Week,Year;  


uchar Z10BCD( uchar date);
uchar BCDTO10( uchar date );
void delay_1302(void);
void  MCs(void);
void  MCx(void);
void  WRdate( uchar date );
uchar REdate() ;
uchar  RE1302( uchar addr );
void  WR1302( uchar addr,uchar Date ); //给某地址写数据
void  Initime(uchar sec,uchar min,uchar hor,uchar day,uchar yue,uchar week,uchar year);
void Init_read_time(void);
# endif 