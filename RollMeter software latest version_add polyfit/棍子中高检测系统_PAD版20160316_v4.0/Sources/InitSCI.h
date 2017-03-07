# ifndef _InitSCI_H_
# define _InitSCI_H_
extern unsigned char data_receive;


/******************************************************************************
串行通信相关函数声明
******************************************************************************/
void InitSCI(void);                    //串行口初始化函数声明
void Send1SCI(char num,byte data );             //串行发送1字节
void SendNSCI(char num,byte ch[] , word N_byte);   //串行发送n字节
byte Re1SCI(char num);               //串行接收1字节
void ReNSCI(char num,byte *get);     //串行接收n字节
void SendStringSCI(char num,byte ch[]);         //发送字符串



# endif 