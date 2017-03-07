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

DSTATUS Drv0Stat    = STA_NOINIT;           //����״̬
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
            return STA_NODISK;  //ʧ��
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
  	if(SD_Reset()==0)     //��ʼ��SD��
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
���ܣ������豸ָ�����Ժͳ��˶�/д��������
��Σ�
    Drive��     ָ���߼��������ţ����̷���Ӧ��ȡֵ 0~9
    Command��   ָ���������
        CTRL_SYNC�� ȷ�������������Ѿ������д������һ��д�ػ��棬����ˢ��ԭ������ֻ�������²����ô�����
        GET_SECTOR_SIZE��   ���ش��̵�������С��ֻ���� f_mkfs()
        GET_SECTOR_COUNT��  ���ؿ����õ�������, _MAX_SS >= 1024 ʱ����
        GET_BLOCK_SIZE��    ��ȡ�������С��ֻ���� f_mkfs()
        CTRL_ERASE_SECTOR�� ǿ�Ʋ���һ���������_USE_ERASE >0  ʱ����
    Buffer��    ָ�������������ָ�룬ȡ����������룬��ʹ��ʱ��ָ��һ�� NULL   ָ��
���Σ�
    RES_OK(0)�� �����ɹ�
    RES_ERROR�� �������ڼ�������κδ����Ҳ��ָܻ���
    RES_PARERR���Ƿ�����
    RES_NOTRDY������������û�г�ʼ��
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

      /*  case GET_SECTOR_SIZE:   //������С
            *(DWORD*)Buffer = 512;
            return RES_OK;

        case GET_SECTOR_COUNT:  //������
            *(DWORD*)Buffer = BspEePromSectorConutGet();
            return RES_OK;

        case GET_BLOCK_SIZE:    //���С  Ҫ����128
            *(DWORD*)Buffer = BspEePromPageSizeGet();
            return RES_OK;

        case CTRL_ERASE_SECTOR: //��������
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
  Sec  = BCDTO10( RE1302(0x81) ); //0x81��������,����������BCD��,��Ҫת����ʮ������
  Min  = BCDTO10( RE1302(0x83) ); //0x83��������
  Hor  = BCDTO10( RE1302(0x85) ); //0x85��ʱ����
  Day  = BCDTO10( RE1302(0x87) ); //0x87��������
  Mon  = BCDTO10( RE1302(0x89) ); //0x89��������
  Week = BCDTO10( RE1302(0x8B) ); //0x8b����������
  Year = BCDTO10( RE1302(0x8D) ); //0x8d��������*/
   
 // PORTB=Sec;   //����ʱ����鿴
//	return ((Year+2000-1980) << 25) /* Year = 2010 */       //+2000��DS1302�Ļ�׼��-1980��FATFS�Ļ�׼
  //| (Mon << 21) /* Month = 11 */
  //| (Day << 16) /* Day = 2 */
 // | (Hor << 11) /* Hour = 15 */
  //| (Min << 5) /* Min = 0 */
 // | (Sec >> 1) /* Sec = 0 */
  return 0; 
}


