#include "Include.h"  

extern byte BUFFER[];
byte SD_Type=0;
/*************************************************************/
/*                      初始化SPI模块                        */
/*************************************************************/
void SPI_Init(void) 
{
  DDRS    = 0xE0;    
  SPI0CR2 = 0x00;  //SS引脚不被SPI使用
  SPI0CR1 = 0x5e;
  SPI0BR  = 0x45; //设置波特率为100k                  
}

/*************************************************************/
/*                    设置SPI时钟为16MHz                     */
/*************************************************************/
void SPI_16M(void) 
{ 
  SPI0BR  = 0x00; //设置波特律为16M                
}

/*************************************************************/
/*                        初始化SD卡                         */
/*************************************************************/
void SD_Init(void)
{
	SPI_Init();
	SD_deselect();
	CD_dir=0;
	WP_dir=0;
}

/*************************************************************/
/*                        清空缓冲区                         */
/*************************************************************/
void clear_buffer(byte buffer[],word num_min,word num_max)
{
    int i;     
    for(i=num_min;i<num_max;i++)	
		*(buffer+i)=0;
}
 
/*************************************************************/
/*                      SPI读写一个字节                      */
/*************************************************************/
byte SPI_Byte(byte value)
{
	while (!SPI0SR_SPTEF);
	SPI0DR = value;
	while(!(SPI0SR_SPIF));
	return SPI0DR;
}

/*************************************************************/
/*                       向SD卡写入命令                      */
/*************************************************************/
byte SD_send_command(byte cmd, long arg)
{
	byte a;
	byte retry=0;
  byte temp;
  byte crc;

  if(cmd==0) crc=0x95;  	    //CRC for CMD0(0)
  else if(cmd==8) crc=0x87;   //CRC for CMD8(0x1AA) 
  else crc=0x01;              //dummy CRC + Stop

	SD_select();
	
	temp=SPI_Byte(cmd | 0x40); //分别写入命令
	temp=SPI_Byte(arg>>24);    //写入地址
	temp=SPI_Byte(arg>>16);
	temp=SPI_Byte(arg>>8);
	temp=SPI_Byte(arg);
	temp=SPI_Byte(crc);
	
  do
  {
      a = SPI_Byte(0xff);
      retry++;
  }
	while((a == 0xff)&&(retry < 10));//等待响应，

	SD_deselect();
	
  temp=SPI_Byte(0xff);       //在总线上额外增加8个时钟，让SD卡完成剩下的工作
	return a;//返回状态值
}


/*************************************************************/
/*                       向SD卡写入命令                      */
/*  向SD卡发送一个命令(结束时不关闭片选，还有后续数据传来）  */
/*************************************************************/
byte SD_SendCommand_NoDeassert(byte cmd, long arg)
{
	byte a;
	byte retry=0;
  byte temp;
  byte crc;

  if(cmd==0) crc=0x95;  	    //CRC for CMD0(0)
  else if(cmd==8) crc=0x87;   //CRC for CMD8(0x1AA) 
  else crc=0x01;              //dummy CRC + Stop

	SD_select();
	
	temp=SPI_Byte(cmd | 0x40);//分别写入命令
	temp=SPI_Byte(arg>>24);
	temp=SPI_Byte(arg>>16);
	temp=SPI_Byte(arg>>8);
	temp=SPI_Byte(arg);
	temp=SPI_Byte(crc);
	
  do
  {
      a = SPI_Byte(0xff);
      retry++;
  }
	while((a == 0xff)&&(retry < 10));//等待响应，

	return a;//返回状态值
}

/*************************************************************/
/*                       向SD卡写入命令                      */
/*************************************************************/
byte SD_Reset(void)
{
	unsigned char i;
	unsigned char retry;
	unsigned char a=0;
	byte temp;
	byte re_sdtype;
  byte buff[4];
  byte ocr[4];
	
	retry = 0;
  
  SD_deselect();
  for(i=0;i<10;i++) temp=SPI_Byte(0xff);
  SD_select();
  temp=SPI_Byte(0xff);
  temp=SPI_Byte(0xff);
  	
	do
	{
		a = SD_send_command(0,0);  //发空闲命令
		retry++;
		if(retry>10) return 1;      //超时退出
	} while(a != 0x01);

  //卡识别及初始化开始
  re_sdtype=SD_SendCommand_NoDeassert(8,0x1aa); //获取卡片的SD版本信息
      
 //2.0卡识别及初始化开始
  if(re_sdtype==0x01) // V2.0的卡、需要根据OCR数据，判断是SD2.0还是SD2.0HC卡                        
  { 
                               //CMD8会传回4字节数据
    buff[0]=SPI_Byte(0xff);//should be 0x00
    buff[1]=SPI_Byte(0xff);//should be 0x00        
    buff[2]=SPI_Byte(0xff);//should be 0x01        
    buff[3]=SPI_Byte(0xff);//should be 0xAA

  	SD_deselect();
    temp=SPI_Byte(0xff);

   // 判断该卡是否支持2.7V-3.6V的电压范围 
    if((buff[2]==0x01)&&(buff[3]==0xAA)) //支持电压范围，可以操作
    {
        retry=0;
        do 
        {            //发卡初始化指令CMD55+ACMD41
            a=SD_send_command(55,0);
            if(a!=0x01)
            {
              return a;
            } 
            
            a=SD_send_command(41, 0x40000000);
            
            retry++;
            if(retry>50)
            {
              return a ;//超时则返回r1状态  
            }
        }
        while(a!=0);  //初始化指令发送完成，接下来获取OCR信息
      
      
        //-----------鉴别SD2.0卡版本开始-----------
       
        a=SD_SendCommand_NoDeassert(58,0);
        if(a!=0x00)
        {
            return a ;//如果命令没有返回正确应答，直接退出，返回应答
        }
         //读OCR指令发出后，紧接着是4字节的OCR信息
        ocr[0]=SPI_Byte(0xff);
        ocr[1]=SPI_Byte(0xff);
        ocr[2]=SPI_Byte(0xff);
        ocr[3]=SPI_Byte(0xff);            
         
          
        SD_deselect();  //OCR接收完成，片选置高
        temp=SPI_Byte(0xff);

        //检查接收到的OCR中的bit30位（CCS），确定其为SD2.0还是SDHC
        //如果CCS=1：SDHC   CCS=0：SD2.0
        //检查CCS
        if(ocr[0]&0x40)
            SD_Type=SD_TYPE_V2HC ;
        else 
            SD_Type=SD_TYPE_V2 ; 
        //-----------鉴别SD2.0卡版本结束-----------
    }//支持电压范围      
  } //2.0卡识别及初始化完成
      /*--------------------------------2.0卡识别及初始化完成------------------------------------------*/
  else if(re_sdtype==0x05) //卡片版本信息是v1.0版本的,SD1.0或者MMC
  {                  //如果是V1.0卡，CMD8指令后没有后续数据
      temp=SPI_Byte(0xff);

  //-----------------SD1.0卡、MMC卡初始化开始-----------------

  //发卡初始化指令CMD55+ACMD41
  // 如果有应答，说明是SD卡，且初始化完成
  // 没有回应，说明是MMC卡，额外进行相应初始化
      retry=0 ;
      do 
      {
          a=SD_send_command(55,0);//先发CMD55，应返回0x01；否则出错
          if(a!=0x01)
          {
              return a ;
          }
          //得到正确响应后，发ACMD41，应得到返回值0x00，否则重试100次
          a=SD_send_command(41,0);
          retry++;
          
      }
      while((a!=0x00)&&(retry<100));
    // 判断是超时还是得到正确回应
    
      if(retry>=100) //超时，则说明是MMC卡需要对MMC卡额外初始化
      {
          retry=0 ;
          //发送MMC卡初始化命令
          do 
          { 
              a=SD_send_command(1,0);
              retry++;
          }
          while((a!=0x00)&&(retry<100));
          if(retry>=100)
          {
            return 1 ;  //MMC卡初始化超时
          }
        
          SD_Type=SD_TYPE_MMC ;//写入卡类型
      }
      else SD_Type=SD_TYPE_V1;  //如果不超时则为返回值正确，为SD1.0卡
  }   
  //----------SD1.0卡、MMC卡初始化操作结束------------
  /*---------------------1.0卡或MMC卡识别及初始化完成-----------------*/


  temp=SPI_Byte(0xff); // Dummy SPI cycle

  if(SD_Type<3) //MMC、SD1.0、SD2.0三种卡需要设置块大小到512
  {
      retry=0;
      do
      {
          retry++;
          a=SD_send_command(16,0x00000200);
     
      }while((a!=0x00)&&(retry<20));
  }
          
	return a;  //返回
}

/*************************************************************/
/*                     由SD卡读取一个扇区                    */
/*************************************************************/
byte read_block(long sector, byte* buffer)
{
	byte a;          
	word i;
	
  //如果不是SDHC，将sector地址转成byte地址
  if(SD_Type!=SD_TYPE_V2HC)
  {
      sector=sector<<9 ;
  }


	a = SD_send_command(17, sector);  //读命令 	
	if(a != 0x00) 		return a;

	SD_select();
	//等数据的开始
	while(SPI_Byte(0xff) != 0xfe);

	for(i=0; i<512; i++)              //读512个数据
	{
		*buffer++ = SPI_Byte(0xff);
	}

	SPI_Byte(0xff);              
	SPI_Byte(0xff);  	
	SD_deselect();
  SPI_Byte(0xff);              
	return 0;
} 

/*************************************************************/
/*                     向SD卡写入一个扇区                    */
/*************************************************************/
byte write_block(long sector, const byte* buffer)
{
	byte a;
	word i;
  if(sector<1) return 0xff;     //为了保护SD卡引导区，跳过该区
  
  //如果不是SDHC，将sector地址转成byte地址
  if(SD_Type!=SD_TYPE_V2HC)
  {
      sector=sector<<9 ;
  }

	a = SD_send_command(24, sector);//写命令
	if(a != 0x00) return a;

	SD_select();
	
	SPI_Byte(0xff);
	SPI_Byte(0xff);
	SPI_Byte(0xff);

	SPI_Byte(0xfe);//发开始符
	
	for(i=0; i<512; i++)//送512字节数据
	{
		SPI_Byte(*buffer++);
	}
	
	SPI_Byte(0xff);
	SPI_Byte(0xff);
	
	a = SPI_Byte(0xff); 	
	if( (a&0x1f) != 0x05)
	{
	  SD_deselect();
		return a;
	}
	//等待操作完
	while(!SPI_Byte(0xff));

  SD_deselect();

	return 0;
} 
