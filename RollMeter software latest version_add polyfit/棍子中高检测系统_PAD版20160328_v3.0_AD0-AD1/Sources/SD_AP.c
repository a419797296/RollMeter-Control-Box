#include "Include.h" 

FATFS FatFs;   /* Work area (file system object) for logical drive */
FIL fil;       /* File object */
FRESULT fr;    /* FatFs return code */
FRESULT res;

//POINT SD_point[700];
byte SD_read_buf[720];
byte buffer[12];
char path[_MAX_LFN]="0:/";
//word  head_size;

     
byte SD_check(void)
{
  if(CD==1)           //SD��û�в�����
  {
      /*lcd_clear();
      lcd_string(0,1,xianshi[0]);
      lcd_string(1,0,xianshi[1]);
      lcd_string(2,0,xianshi[2]); */
      return 1;
  } 
  else if(WP==1)     //д�������
  {
      /*lcd_clear();
      lcd_string(0,1,xianshi[0]);
      lcd_string(1,0,xianshi[3]);
      lcd_string(2,0,xianshi[4]);
      lcd_string(3,0,xianshi[2]);*/
      return 1;
  } 
  else             //SD������
  {
      /*lcd_clear();
      lcd_string(0,1,FilDeal[0]);
      lcd_string(1,0,FilDeal[1]);
      lcd_string(2,0,xianshi[5]);
      lcd_string(3,0,xianshi[6]);*/
      if(!disk_initialize(0))
      {
        /*if(!f_mount(&FatFs, "0:", 1));   //load file success!
        {
          f_setlabel("0:WillTech");
          f_mkdir("0:/W_tech");
          return 0;
        } */
        return 0; 
      }
      else
        return 1;
  }
}


/************************д���굽SD����****************************/
void send_point_SD(word x,word y,char *path0)                   
{
   byte i=0; 
   *buffer=x/10000+0x30;
   *(buffer+1)=x%10000/1000+0x30;
   *(buffer+2)=x%1000/100+0x30;
   *(buffer+3)=x%100/10+0x30;
   *(buffer+4)=x%10+0x30;
   while(*(buffer+i)==0x30)
   {
        *(buffer+i)=0x20;
        i++;
        if(i==4)
          break;     
   }
   
   *(buffer+5)=0x09;         //�Ʊ��\t
   
   *(buffer+6)=y/1000+0x30;
   *(buffer+7)=y%1000/100+0x30;
   *(buffer+8)=y%100/10+0x30;
   *(buffer+9)=y%10+0x30;
   i=6;
   while(*(buffer+i)==0x30)
   {
        *(buffer+i)=0x20; 
        i++;
        if(i==9)
          break;     
   }   
   *(buffer+10)=0x0D;
   *(buffer+11)=0x0A;
   
   res=f_mount(&FatFs, "0:", 1);
   if(!res)   //load file success!
   {
      res = f_open(&fil, path0, FA_CREATE_ALWAYS | FA_WRITE);
     // if(res==FR_OK)    
        {   
           f_lseek(&fil,fil.fsize);
           res=f_write(&fil,buffer,12,&bw);
           f_close(&fil);
        }

   }
   f_mount(NULL, "0:", 1); 

}

/************************д���굽SD����****************************/
/*void send_points_SD(POINT *sd_point,char *path0,num)                   
{
   byte i=0; 
   *buffer=x/10000+0x30;
   *(buffer+1)=x%10000/1000+0x30;
   *(buffer+2)=x%1000/100+0x30;
   *(buffer+3)=x%100/10+0x30;
   *(buffer+4)=x%10+0x30;
   while(*(buffer+i)==0x30)
   {
        *(buffer+i)=0x20;
        i++;
        if(i==4)
          break;     
   }
   
   *(buffer+5)=0x09;         //�Ʊ��\t
   
   *(buffer+6)=y/1000+0x30;
   *(buffer+7)=y%1000/100+0x30;
   *(buffer+8)=y%100/10+0x30;
   *(buffer+9)=y%10+0x30;
   i=6;
   while(*(buffer+i)==0x30)
   {
        *(buffer+i)=0x20; 
        i++;
        if(i==9)
          break;     
   }   
   *(buffer+10)=0x0D;
   *(buffer+11)=0x0A;
   

   if(!f_mount(&FatFs, "0:", 1));   //load file success!
   {
      res = f_open(&fil, path0, FA_OPEN_ALWAYS | FA_WRITE);
      if(res==FR_OK)    
        {   
           f_lseek(&fil,fil.fsize);
           res=f_write(&fil,buffer,12,&bw);
           f_close(&fil);
        }

   }
   f_mount(NULL, "0:", 1); 

}
*/

/************************���ݸ�ʽת��****************************/
word asc2num(word x,word N,byte *num_buf) 
{
    word i;
    if(N==2)
    {
       *num_buf=x/10+0x30;
       *(num_buf+1)=x%10+0x30;
       i=0;
       while(*(num_buf+i)==0x30)
       {
            *(num_buf+i)=0x20;
            i++;
            if(i==1)
              break;     
       }       
    }
    if(N==3)
    {
       *num_buf=x/100+0x30;
       *(num_buf+1)=x%10/10+0x30;
       *(num_buf+2)=x%10+0x30;  
       i=0;
       while(*(num_buf+i)==0x30)
       {
            *(num_buf+i)=0x20;
            i++;
            if(i==2)
              break;     
       }            
    }
    if(N==4)
    {
       *num_buf=x/1000+0x30;
       *(num_buf+1)=x%1000/100+0x30;
       *(num_buf+2)=x%100/10+0x30;
       *(num_buf+3)=x%10+0x30;
       i=0;
       while(*(num_buf+i)==0x30)
       {
            *(num_buf+i)=0x20;
            i++;
            if(i==3)
              break;     
       }       
    }
    if(N==5)
    {
       *num_buf=x/10000+0x30;
       *(num_buf+1)=x%10000/1000+0x30;
       *(num_buf+2)=x%1000/100+0x30;
       *(num_buf+3)=x%100/10+0x30;
       *(num_buf+4)=x%10+0x30;
       i=0;
       while(*(num_buf+i)==0x30)
       {
            *(num_buf+i)=0x20;
            i++;
            if(i==4)
              break;     
       }              
    }
    return N; 
}

/************************���ݸ�ʽת��****************************/
word num2asc(word N,byte *num_buf) 
{
     word i=0;
     static word data=0;
     while(*(num_buf+i)==0x20)
     {
        N--;
        i++;
        if(N==1)
          break;
     }
     switch(N)
     {
         case 1:
            data=*(num_buf+i)-0x30 ;
            break;
         case 2:
            data=(*(num_buf+i)-0x30)*10+(*(num_buf+i+1)-0x30);
            break;
         case 3:
            data=(*(num_buf+i)-0x30)*100+(*(num_buf+i+1)-0x30)*10+(*(num_buf+i+2)-0x30) ;
            break;            
         case 4:
            data=(*(num_buf+i)-0x30)*1000+(*(num_buf+i+1)-0x30)*100+(*(num_buf+i+2)-0x30)*10+(*(num_buf+i+3)-0x30) ; 
            break;           
         case 5:
            data=(*(num_buf+i)-0x30)*10000+(*(num_buf+i+1)-0x30)*1000+(*(num_buf+i+2)-0x30)*100+(*(num_buf+i+3)-0x30)*10+(*(num_buf+i+4)-0x30);            
            break;   
         default:
            data=0;
            break;
                  
     }
     return data;
  
}


/************************word to bytes****************************/
void word2bytes(word x,word y,byte * num_buf) 
{
     *(num_buf)=x>>8;
     *(num_buf+1)=x;
     *(num_buf+2)=y>>8;
     *(num_buf+3)=y; 
}
/************************ָ���ַ���ָ��ĳ���****************************/
word string_lenth(char *string) 
{
    word i=0;
    while((*(string+i)!='\0'))
      i++;
    return i;
}
/************************�������****************************/
word clear_cell(char *string) 
{
    word i=0;
    while(i<6)
    {
        *(string+i)=0x00;
        i++;
    } 
    return i;
}

/************************��ȡ������SD������****************************/
word SD_read(char *path0)
{
	 /*word i=0,j,k=1,num;
	 word lines;
	 word read_num;
	 POINT sd_point;
	 POINT lcd_point,lcd_last_point;
	 POINT MAX_point,MIN_point;
	 static byte MAX_MIN_buf[24];
	
	 if(!f_mount(&FatFs, "0:", 1));   //load file success!
   {
      res = f_open(&fil, path0, FA_READ);
      if(res==FR_OK)    
        {   
           lines=(fil.fsize-head_size)/12-1;
           
           
           
           
           //********************��ȡ����ͷ�ļ�                               
            f_read(&fil,SD_read_buf,65,&br);                //���ų���Ϊ10���ַ�
            for(num=0;num<10;num++)
              *(stick_name+num)=*(SD_read_buf+num+9);
            stick_length=num2asc(5,SD_read_buf+30);          //������30���ַ���ʼ
            sample_dist= num2asc(2,SD_read_buf+51);          //���������51���ַ���ʼ
            RT_point[0]=stick_length;                        //��ʱ��ʵʱ��ʾ�������飬�����ڴ�ռ��
            RT_point[1]=sample_dist; 
            LCD_write_data_word(0x0000,2,RT_point);           //д���������������
            LCD_write_data(0x0002,10,stick_name);             //д�����
           //********************��ȡ��������                                                   
           while((head_size+720*i)<fil.fsize)           //-24means the max&min point
           {
               f_lseek(&fil,head_size+720*i);
               f_read(&fil,SD_read_buf,sizeof(SD_read_buf),&br);
               br==720;read_num=br;read_num=br-24;
               for(j=0;j<read_num;j+=12)
               {
                 
                 sd_point.x=num2asc(5,SD_read_buf+j);
                 sd_point.y=num2asc(4,SD_read_buf+6+j);
                 sd_point.num=k; 
                 //point2LCD_point(sd_point,lcd_point);
                 
                 lcd_point.x=STAR_X+(long)(sd_point.x)*DISP_DIF_W/stick_length;        //��ӦҺ��x���ص�
                 lcd_point.y=STAR_Y-(long)(sd_point.y)*DISP_DIF_H/DISP_DIF_VALUE+curve_disp_shift;             //curve_disp_shift means the shift of the curve display
                 lcd_point.num=sd_point.num; 
                 *(LCD_x+lcd_point.num)=lcd_point.x;
                 *(LCD_y+lcd_point.num)=lcd_point.y;
                 if(lcd_point.num>1)                                //if not the first point
                    realtime_write(lcd_last_point,lcd_point);
                 k++;  
                 lcd_last_point=lcd_point;             
               }
               i++;              
           }
           //********************��ȡ�����С����                                                                    
           f_lseek(&fil,fil.fsize-24);         //move to the last two point 
           f_read(&fil,MAX_MIN_buf,sizeof(MAX_MIN_buf),&br);
           MAX_point.x=num2asc(5,MAX_MIN_buf);
           MAX_point.y=num2asc(4,MAX_MIN_buf+6);
           MIN_point.x=num2asc(5,MAX_MIN_buf+12);
           MIN_point.y=num2asc(4,MAX_MIN_buf+18);
           RT_point[0]=MAX_point.x;                        //��ʱ��ʵʱ��ʾ�������飬�����ڴ�ռ��
           RT_point[1]=MAX_point.y-2500;                
           RT_point[2]=MIN_point.x;
           RT_point[3]=MIN_point.y-2500;
           LCD_write_data_word(0x0012,4,RT_point);
           
           lcd_point.x=STAR_X+(long)(MAX_point.x)*DISP_DIF_W/stick_length;        //��ӦҺ��x���ص�
           lcd_point.y=STAR_Y-(long)(MAX_point.y)*DISP_DIF_H/DISP_DIF_VALUE+curve_disp_shift;
           lcd_point.num=1;
           LCD_draw_circle(lcd_point,0x0006);
           
           lcd_point.x=STAR_X+(long)(MIN_point.x)*DISP_DIF_W/stick_length;        //��ӦҺ��x���ص�
           lcd_point.y=STAR_Y-(long)(MIN_point.y)*DISP_DIF_H/DISP_DIF_VALUE+curve_disp_shift;
           lcd_point.num=2;
           LCD_draw_circle(lcd_point,0x0006);
           f_close(&fil);
        }

   }
   if( return_data==2)
      f_unlink(path0) ;
   f_mount(NULL, "0:", 1); 
   return lines;    */
}

/************************��ȡʱ���׺****************************/
void SD_time_postfix(char *str)
{
  DWORD  Sec,Min,Hor,Day,Mon,Week,Year; 
  Sec  = BCDTO10( RE1302(0x81) ); //0x81��������,����������BCD��,��Ҫת����ʮ������
  Min  = BCDTO10( RE1302(0x83) ); //0x83��������
  Hor  = BCDTO10( RE1302(0x85) ); //0x85��ʱ����
  Day  = BCDTO10( RE1302(0x87) ); //0x87��������
  Mon  = BCDTO10( RE1302(0x89) ); //0x89��������
  Week = BCDTO10( RE1302(0x8B) ); //0x8b����������
  Year = BCDTO10( RE1302(0x8D) ); //0x8d��������  
  *str=0x5F;                    //�»���
  *(str+1)=Year/10+0x30;
  *(str+2)=Year%10+0x30;
  
  *(str+3)=Mon/10+0x30;
  *(str+4)=Mon%10+0x30;
  
  *(str+5)=Day/10+0x30;
  *(str+6)=Day%10+0x30;
  
  *(str+7)=0x5F
  ;
  *(str+8)=Hor/10+0x30;
  *(str+9)=Hor%10+0x30;
  *(str+10)=Min/10+0x30;
  *(str+11)=Min%10+0x30;
  *(str+12)=Sec/10+0x30;
  *(str+13)=Sec%10+0x30;
  
  *(str+14)=0x2E;            //.txt
  *(str+15)=0x74;
  *(str+16)=0x78;
  *(str+17)=0x74;
  *(str+18)=0;  
}

/************************�����ļ���****************************/
//ʱ�䣺2015.8.24                                              /
//ԭ�ͣ�
//������
//����ֵ��
/*************************************************************/
void scan_dir(char *path0)
{
    char name[_MAX_LFN]=
    {0};
    char *fn;
    DIR dir;
    word i=0;
    FILINFO filinfo;
    filinfo.lfsize = _MAX_LFN ;
    filinfo.lfname = name;
    for(i=0;i<5;i++)                                            //�ݶ���5������
       LCD_write_data(0x0130+LIST_WID*i,LIST_WID<<1,name);        //0X0B��ʾ�б��ȣ�����б�����
    i=0;
    if(!f_mount(&FatFs, "0:", 1));   //load file success!
    {
        res = f_opendir(&dir,(const TCHAR*)path0); //��һ��Ŀ¼
        if (res == FR_NO_PATH)
           LCD_change_img(13);
        if (res == FR_OK)
        { 
          //SendNSCI(0,"\r\n",2);
          while(1)
          {
                 res = f_readdir(&dir, &filinfo);                   //��ȡĿ¼�µ�һ���ļ�
                 if (res != FR_OK || filinfo.lfname[0] == 0) break;  //������/��ĩβ��,�˳�
                 //if (fileinfo.fname[0] == '.') continue;             //�����ϼ�Ŀ¼

                 fn = filinfo.lfname ;    
                 //SendNSCI(0,fn,sizeof(name));
                 LCD_write_data(0x0130+LIST_WID*i,sizeof(name),fn);        //0X0B��ʾ�б���
                 
                 i++;
          }                           
       }        
    }
    f_mount(NULL, "0:", 1); 
}

void SD_delete_file(char *path0)
{
    if(!f_mount(&FatFs, "0:", 1));   //load file success!
      {
        res=f_unlink(path0);
      }
    f_mount(NULL, "0:", 1);
}































/* if(!disk_initialize(0))                   //�����ʼ���ɹ�
  {
  
      lenth=strlen(willtech); 
      	for(m=0;m<lenth;m++)
    	   BUFFER[m]=*(willtech+m);
    //	for(m=0;m<512;m++)
    //	   BUFFER[m]='A';
      if(!(disk_write(0,BUFFER,32768,1))){      //д������
        lcd_clear();
        lcd_string(0,1,xianshi[0]);
        lcd_string(1,1,xianshi[13]);
        lcd_string(2,1,xianshi[6]);
    	}
    	else
    	{
        lcd_clear();
        lcd_string(0,1,xianshi[0]);
        lcd_string(1,1,xianshi[14]);
        lcd_string(2,1,xianshi[10]);
     	}


      clear_buffer(BUFFER);       //��ս��ջ�����	
    	if(!(disk_read(0,BUFFER,32768,1))){      //��ȡ����
        lcd_clear();
        lcd_string(0,2,(char*)BUFFER);
    	}
    	else
    	{
        lcd_clear();
        lcd_string(0,0,xianshi[0]);
        lcd_string(1,1,xianshi[14]);
        lcd_string(2,1,xianshi[10]);
     	}
  }
    lcd_clear();
    lcd_string(0,1,FilDeal[0]);
    delay();
    lcd_string(1,0,FilDeal[1]);
    delay();
    lcd_string(2,0,FilDeal[2]);
    delay();*/