/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "Include.h"    

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define USB		2	/* Example: Map USB MSD to physical drive 2 */

DSTATUS Drv0Stat    = STA_NOINIT;           //磁盘状态
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	switch (pdrv) 

    {
        case 0 :
            return Drv0Stat;
        default:
            return STA_NODISK;  //失败
    }
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
  Drv0Stat |= STA_NOINIT;
	switch (pdrv) 
	{

	case 0 :
	  SD_Init ();
	  INIT: 			
  	if(SD_Reset()==0)     //初始化SD卡
  	{ 	  
      SPI_16M();     
  	}
  	else
  	{
  	  delay1ms(1000);
  	  goto INIT; 
  	}
	  Drv0Stat=0;
	  return Drv0Stat;
	  
  default:
  
    return STA_NOINIT;
	}
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	int result;
  
    if (Drv0Stat & STA_NOINIT)
    {
        return RES_NOTRDY;
    } 
    else if (!count)
    {
        return RES_PARERR;
    }
  
    switch(pdrv)
    {
        case 0 :
            result = read_block( sector, buff);
            if (result != 0x00)
            {
                return RES_ERROR;
            } else
            {
                return RES_OK;
            }
        default:
            return RES_PARERR;
    } 
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{

    byte result;

    if (Drv0Stat & STA_NOINIT)
    {
        return RES_NOTRDY;
    } else if (!count)
    {
        return RES_PARERR;
    }

    switch (pdrv)
    {
        case 0 :
                result=write_block( sector, buff);
                if (result != 0x00)
                {
                    return RES_ERROR;
                }else
                {
                    return RES_OK;
                }

    }
    return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

/*****************************************************************************************
功能：控制设备指定特性和除了读/写外的杂项功能
入参：
    Drive：     指定逻辑驱动器号，即盘符，应当取值 0~9
    Command：   指定命令代码
        CTRL_SYNC： 确保磁盘驱动器已经完成了写处理，有一个写回缓存，立即刷新原扇区，只读配置下不适用此命令
        GET_SECTOR_SIZE：   返回磁盘的扇区大小，只用于 f_mkfs()
        GET_SECTOR_COUNT：  返回可利用的扇区数, _MAX_SS >= 1024 时可用
        GET_BLOCK_SIZE：    获取擦除块大小，只用于 f_mkfs()
        CTRL_ERASE_SECTOR： 强制擦除一块的扇区，_USE_ERASE >0  时可用
    Buffer：    指向参数缓冲区的指针，取决于命令代码，不使用时，指定一个 NULL   指针
出参：
    RES_OK(0)： 函数成功
    RES_ERROR： 读操作期间产生了任何错误且不能恢复它
    RES_PARERR：非法参数
    RES_NOTRDY：磁盘驱动器没有初始化
*/
#if _USE_IOCTL
DRESULT disk_ioctl(BYTE pdrv, BYTE Command, void* Buffer)
{
    if (Drv0Stat & STA_NOINIT)
    {
        return RES_NOTRDY;
    }

    switch (pdrv)
    {
        case 0:
            break;
        default:
            return RES_PARERR;
    }

    switch (Command)
    {
        case CTRL_SYNC:
            return RES_OK;

      /*  case GET_SECTOR_SIZE:   //扇区大小
            *(DWORD*)Buffer = 512;
            return RES_OK;

        case GET_SECTOR_COUNT:  //扇区数
            *(DWORD*)Buffer = BspEePromSectorConutGet();
            return RES_OK;

        case GET_BLOCK_SIZE:    //块大小  要大于128
            *(DWORD*)Buffer = BspEePromPageSizeGet();
            return RES_OK;

        case CTRL_ERASE_SECTOR: //扇区擦除
            return RES_OK;
                            */
        default:
            return RES_PARERR;
    }
}

#endif


DWORD get_fattime (void)
{				 
  /*DWORD  Sec,Min,Hor,Day,Mon,Week,Year; 
  Sec  = BCDTO10( RE1302(0x81) ); //0x81读秒数据,读出来的是BCD码,还要转换成十进制数
  Min  = BCDTO10( RE1302(0x83) ); //0x83读分数据
  Hor  = BCDTO10( RE1302(0x85) ); //0x85读时数据
  Day  = BCDTO10( RE1302(0x87) ); //0x87读日数据
  Mon  = BCDTO10( RE1302(0x89) ); //0x89读月数据
  Week = BCDTO10( RE1302(0x8B) ); //0x8b读星期数据
  Year = BCDTO10( RE1302(0x8D) ); //0x8d读年数据*/
   
 // PORTB=Sec;   //仿真时方便查看
//	return ((Year+2000-1980) << 25) /* Year = 2010 */       //+2000是DS1302的基准，-1980是FATFS的基准
  //| (Mon << 21) /* Month = 11 */
  //| (Day << 16) /* Day = 2 */
 // | (Hor << 11) /* Hour = 15 */
  //| (Min << 5) /* Min = 0 */
 // | (Sec >> 1) /* Sec = 0 */
  return 0; 
}


