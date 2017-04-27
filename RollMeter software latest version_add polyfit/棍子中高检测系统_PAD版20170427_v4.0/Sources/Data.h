/******************************************************************************
项目主头文件
******************************************************************************/

# ifndef _DATA_H_
# define _DATA_H_

//-----------------------标定系数---------------------------//
#define  FIRST_ORDERE         10076         //扩大10000倍后的一次项系数
#define  CONSTANT_ORDERE      19          //常数项取整
//----------------------------------------------------------//
typedef struct {
   int num;
   int x;
   int y;
} POINT;

extern POINT point;

extern byte RT_point[6];
extern byte read_tmp[40];




extern word stick_length, stick_peri,sample_dist,stick_diameter;      //棍子检测相关参数
extern char stick_name[10];
extern word pulse_step,pulse_add,pulse_change;
extern long pulse_sum,pulse_max;
extern dword sens_AD, last_sensor_AD;


int PAD_RT_AD(void);
void send_point(void);
# endif 