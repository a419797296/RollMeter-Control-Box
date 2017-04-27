 /******************************************************************************
项目主头文件
******************************************************************************/

# ifndef _SYSDEFINE_H_
# define _SYSDEFINE_H_


#define LEDCPU PORTB_PB0
#define LEDCPU_dir DDRB_DDRB0
#define LED_ON 1
#define LED_OFF 0
#define KEY1 PTIH_PTIH3
#define KEY1_dir DDRH_DDRH3
#define Encoder		   2000	   //编码器线数
#define Threshold    6       //误差阈值

//#define SENSOR_POWER PORTA_PA4      //控制传感器供电
//#define SYS_POWER PORTA_PA6      //low power LED
#define SENSOR_POWER PORTB_PB1      //控制传感器供电
#define SYS_POWER PORTB_PB0      //low power LED
#define POWER_ON 1
#define POWER_DOWN 0





#define  CONFIG_RIGHT   1
#define  CONFIG_LEFT   2
#define  FINISH_CONFIG   3


extern byte READ_FLAG;
extern word g_idx;
extern word send_flg;
extern byte mov_dir ;
extern byte battery_flg;
//extern byte battery_low;      //低电量标志
extern word i;
void InitPort(void);
# endif 
