#include "Include.h"  
POINT point;


byte read_tmp[40];


word stick_length=2000, stick_peri=1730,sample_dist=20,stick_diameter=500;      //棍子检测相关参数
char stick_name[10];
word pulse_step=0,pulse_add=0,pulse_change=0;
long pulse_sum,pulse_max;
dword sens_AD, last_sensor_AD;
byte  RT_point[6];





/***********************机械零位调整,AD值实时显示*********************/
int PAD_RT_AD(void)                   
{

     byte disp_data[2]= {0x00,0x00};
     dword tmp_AD;
   /*  tmp_AD=AD_capture(0);
     tmp_AD=2500*tmp;
     sens_AD=tmp_AD>>11;   */
     
     tmp_AD=ATD_Filte(20,2); //平均值滤波
     
     if(tmp_AD-sens_AD<=Threshold||sens_AD-tmp_AD<=Threshold)       //阀值滤波
     {
        if(tmp_AD-sens_AD<=3||sens_AD-tmp_AD<=3)
             tmp_AD=sens_AD;
        else
             tmp_AD=(tmp_AD+sens_AD)/2;
     }   
     
     tmp_AD=tmp_AD*10038/10000-13;
     //tmp_AD=tmp_AD/10*10;
     disp_data[0]= tmp_AD>>8;
     disp_data[1]= tmp_AD;
     SendNSCI(0,disp_data,2);
     return tmp_AD;     
    
}


void send_point(void)

{
     /*  sens_AD=AD_capture(0);
       sens_AD=2500*sens_AD;              //y轴坐标转换,uV
       sens_AD=long_tmp>>11;
       */
       sens_AD=ATD_Filte(20,2);  //平均值滤波
       
      /* if(point.y-sens_AD<=Threshold||sens_AD-point.y<=Threshold)      //阀值滤波
       {
          if(point.y-sens_AD<=3||sens_AD-point.y<=3)
              sens_AD=point.y;
          else
              sens_AD=(point.y+sens_AD)/2;   
           
       }    */
       //sens_AD=sens_AD/10*10;  
       point.y= sens_AD*10038/10000-13;;    
         
       point.x=pulse_sum*stick_peri/Encoder/10; //x轴坐标转换,mm
       point.num++;
                                
       RT_point[0]=point.x>>8;
       RT_point[1]=point.x;
       RT_point[2]=point.y>>8;
       RT_point[3]=point.y;                                
        SendNSCI(0,RT_point,4);
        //LEDCPU=~LEDCPU;
}