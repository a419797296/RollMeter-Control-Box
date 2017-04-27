#include <hidef.h>      /* common defines and macros */


#define CD PTM_PTM4
#define CD_dir DDRM_DDRM4
#define WP PTM_PTM5
#define WP_dir DDRM_DDRM5

#define SD_select()        PTS_PTS7=0        //低电平
#define SD_deselect()      PTS_PTS7=1        //高电平

/* SD卡类型定义 */
#define SD_TYPE_MMC     0
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    3


void SPI_Init(void); 
void SPI_16M(void); 
void clear_buffer(byte buffer[],word num_min,word num_max);
byte SPI_Byte(byte value);
void SD_Init(void);
byte SD_send_command(byte cmd, long arg);
byte SD_SendCommand_NoDeassert(byte cmd, long arg);
byte SD_Reset(void);
byte read_block(long sector, byte* buffer);
byte write_block(long sector,const byte* buffer);
 
































