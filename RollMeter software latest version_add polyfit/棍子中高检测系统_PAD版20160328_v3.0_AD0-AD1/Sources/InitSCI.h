# ifndef _InitSCI_H_
# define _InitSCI_H_
extern unsigned char data_receive;


/******************************************************************************
����ͨ����غ�������
******************************************************************************/
void InitSCI(void);                    //���пڳ�ʼ����������
void Send1SCI(char num,byte data );             //���з���1�ֽ�
void SendNSCI(char num,byte ch[] , word N_byte);   //���з���n�ֽ�
byte Re1SCI(char num);               //���н���1�ֽ�
void ReNSCI(char num,byte *get);     //���н���n�ֽ�
void SendStringSCI(char num,byte ch[]);         //�����ַ���



# endif 