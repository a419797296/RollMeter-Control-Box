#include "Include.h"

byte detect_power(void) 
{
 //控制盒电量显示
          dword power_AD;
          byte battery_low=0;
          power_AD=AD_capture(0);
          power_AD=2500*power_AD;             
          power_AD=power_AD>>11;
          
          if(power_AD<3100)
              power_AD=0;
          else
          {
            
            power_AD-=3100;
            power_AD= power_AD/10;//电压电量显示
            if(power_AD>100)
               power_AD=100;
            //power_AD>100?power_AD=100:power_AD=power_AD;
          }
          
          
          if(power_AD<battery_flg)                 //确保电量显示的数字逐渐减小
          {
            
              battery_flg=power_AD;
              if(battery_flg<15)
              {
                  battery_low=1;
                  battery_flg=15;
     
              }
              else
              {
      //            PORTB=(0XFF<<(battery_flg/25+1));
                  battery_low=0;
              }
              
          }
          
          if(power_AD>battery_flg+10)             //可能重新上电，电量显示数字会变大
          
          {
            
              battery_flg=power_AD;
              if(battery_flg<10)
              {
                  battery_low=1;
     
              }
              else
              {
      //            PORTB=(0XFF<<(battery_flg/25+1));
                  battery_low=0;
              }
              
          }
          return battery_low ;
}
/*************************************************************/
/*                          主函数                           */
/*************************************************************/
void main(void) {
 // delay(1500);
  DisableInterrupts;
  InitPort();
  INIT_PLL();
  initialize_ect();
  InitPIT();
  InitATD();
  InitSCI();
  EnableInterrupts;
  TIE=0x00;                //处理数据的时候关中断
  PITINTE=0x00;
  point.x=0;
  point.num=0;
  for(;;) 
  {
      

      switch(data_receive) 
      {
        case 1:                     //电量查询
          
          if(detect_power())
          {
               for(i=0;i<=100;i=i+20)
               {
                  Send1SCI(0,i);
                  delay(500);
               }

          }
          else
          {
              Send1SCI(0,battery_flg);
          }
          
     
          break; 
        case 2:                      //测量界面

  //          PORTB=(0xff<<2);            
            break; 
            
        case 3:                      //零位校正确认
           // SENSOR_POWER=POWER_DOWN;
            Send1SCI(0,0x00);
 //           PORTB=(0xff<<3); 
            READ_FLAG=0;                            
          break;    
        case 4:                      //进入开始测量界面
            
            if(!send_flg)
            {
              //SENSOR_POWER=POWER_ON;
              //delay(2000);
              send_point();
              pulse_add+=1;
              send_flg=1;
              PACNT=0;
              data2=0;
            }
            TIE=0x01;                   //开中断
            PITINTE=0x02;
    //        PORTB=(0xff<<4);  
            READ_FLAG=0;  
          break;
        case 5:                      //保存测量数据
            TIE=0x00;                //
            PITINTE=0x00;
            send_flg=0;
            pulse_sum=0;
            SENSOR_POWER=POWER_DOWN;
          
     //       PORTB=(0xff<<5); 
                                      
          break;
        case 6:                      //退出到主界面
          TIE=0x00;                
          PITINTE=0x00;
          send_flg=0;
          pulse_sum=0;
          READ_FLAG=0;
          pulse_change=0;
          pulse_add=0;
          point.num=0;
          //SENSOR_POWER=POWER_DOWN;  //do not cut down the power
          break; 

 
        default:                    
          break;                  

      }        
      if(READ_FLAG==FINISH_CONFIG)
        {
                                  //保存后开始校零
          SENSOR_POWER=POWER_ON;
          delay(1);
          sens_AD=PAD_RT_AD();
    //      PORTB=(0XFF<<long_AD);
                   
        }
         //电量低则开灯提示；反之关闭
          if(detect_power())
          {
                  
              SYS_POWER=LED_ON;
          } 
          else 
          {
              SYS_POWER=LED_OFF;
          }
          delay(500);

  }

}
