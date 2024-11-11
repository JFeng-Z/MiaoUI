/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "HAL_Flash.h"
#include "HAL_Tick.h"

/* Definitions of physical drive number for each drive */
#define SPI_FLASH   0     // 外部SPI Flash

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case SPI_FLASH :
		// result = RAM_disk_status();
		if(sFLASH_ID == SPI_FLASH_ReadID())
		{
			stat &= ~STA_NOINIT;
		}
		else stat = STA_NOINIT;
		// translate the reslut code here
		break;
	default:
		stat = STA_NOINIT;
		break;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
    case SPI_FLASH:    /* SPI Flash */
        /* 初始化SPI Flash */
        SPI_FLASH_Init();
        /* 延时一小段时间 */
		HAL_Delay_Ms(1);
        /* 唤醒SPI Flash */
        SPI_Flash_WAKEUP();
        /* 获取SPI Flash芯片状态 */
        stat=disk_status(SPI_FLASH);
		break;
	default:
		stat = STA_NOINIT;
		break;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;
	
	switch (pdrv) {
    case SPI_FLASH:
        /* 扇区偏移2MB，外部Flash文件系统空间放在SPI Flash后面6MB空间 */
        sector+=512;
        SPI_FLASH_BufferRead(buff, sector <<12, count<<12);
        res = RES_OK;
        break;
	default:
		res = RES_PARERR;
		break;
	}

	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	uint32_t write_addr;
	DRESULT res;
	int result;
    if (!count) {
        return RES_PARERR;    /* Check parameter */
    }
	switch (pdrv) {
    case SPI_FLASH:
        /* 扇区偏移2MB，外部Flash文件系统空间放在SPI Flash后面6MB空间 */
        sector+=512;
        write_addr = sector<<12;
        SPI_FLASH_SectorErase(write_addr);
        SPI_FLASH_BufferWrite((u8 *)buff,write_addr,count<<12);
        res = RES_OK;
        break;
    default:
        res = RES_PARERR;
		break;
	}

	return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
    case SPI_FLASH:
        switch (cmd) {
        /* 扇区数量：1536*4096/1024/1024=6(MB) */
        case GET_SECTOR_COUNT:
            *(DWORD * )buff = 1536;
            break;
        /* 扇区大小  */
        case GET_SECTOR_SIZE :
            *(WORD * )buff = 4096;
            break;
        /* 同时擦除扇区个数 */
        case GET_BLOCK_SIZE :
            *(DWORD * )buff = 1;
            break;
        }
        res = RES_OK;
        break;

    default:
        res = RES_PARERR;
		break;
	}

	return res;
}

