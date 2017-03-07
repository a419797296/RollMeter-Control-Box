# ifndef _SD_AP_H_
# define _SD_AP_H_


extern byte SD_check(void);
extern byte buffer[12];
extern char path[_MAX_LFN];
extern word stick_config(void );
//extern POINT SD_point[700];
extern byte SD_read_buf[720];
#define   head_size 65         //头文件固定长度


void send_point_SD(word x,word y,char *path0);
void send_points_SD(POINT *sd_point,char *path0);
word asc2num(word x,word N,byte *num_buf);
word string_lenth(char *string);
word clear_cell(char *string) ;
word SD_read(char *path0);
word asc2num(word x,word N,byte *num_buf); 
void word2bytes(word x,word y,byte *num_buf);
void SD_time_postfix(char *str);
void scan_dir(char *path0);
void SD_delete_file(char *path0);
# endif 
