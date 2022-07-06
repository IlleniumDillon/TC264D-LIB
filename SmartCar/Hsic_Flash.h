/*
 * Hsic_Flash.h
 *
 *  Created on: 2022年7月5日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_FLASH_H_
#define SMARTCAR_HSIC_FLASH_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxFlash.h>
#include <IfxScuWdt.h>
#include <Hsic_common.h>

/******************************************************************************/
/*-------------------------------------宏-------------------------------------*/
/******************************************************************************/

/*
 * \brief dflash的大小、扇区和页的大小
 */
#define DFLASH_BASE_ADDR    IFXFLASH_DFLASH_START
#define DFLASH_SIZE         IFXFLASH_DFLASH_SIZE

#define DFLASH_SECROT_NUM   IFXFLASH_DFLASH_NUM_LOG_SECTORS
#define DFLASH_SECTOR_SIZE  (IFXFLASH_DFLASH_SIZE/IFXFLASH_DFLASH_NUM_LOG_SECTORS)

#define DFLASH_PAGE_NUM     (DFLASH_SECTOR_SIZE/IFXFLASH_DFLASH_PAGE_LENGTH)
#define DFLASH_PAGE_SIZE    IFXFLASH_DFLASH_PAGE_LENGTH

/*
 * \brief 读地址
 */
#define DFLASH_READ_PAGE(addr) (*(uint32*)addr)

/******************************************************************************/
/*--------------------------------数据类型定义--------------------------------*/
/******************************************************************************/

/*
 * \brief dflash地址
 */
typedef uint32 hsic_dflash_addr_t;

/******************************************************************************/
/*--------------------------------内联函数声明--------------------------------*/
/******************************************************************************/

/** \brief dflash按扇区和页读数
 * \param sector 扇区号
 * \param page 页号
 * \return uint32 读到的数据
 *
 * Coding example:
 * \code
 *    uint32 i = Hsic_dflashRead(0,0);
 * \endcode
 *
 */
static inline uint32 Hsic_dflashRead(uint8 sector, uint8 page);

/** \brief dflash按页写数据
 * \param sector 扇区号
 * \param page 页号
 * \param pdata 数据指针
 * \return hsic_dflash_addr_t 写入的dflash地址
 *
 * Coding example:
 * \code
 *    Hsic_dflashWritePage(0,0,&i);
 * \endcode
 *
 */
static inline hsic_dflash_addr_t Hsic_dflashWritePage(uint8 sector, uint8 page, uint32* pdata);

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief dflash擦除扇区
 * \param sector 扇区号
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_dflashSectorErase(0);
 * \endcode
 *
 */
void Hsic_dflashSectorErase(uint8 sector);

/** \brief dflash按地址写数据
 * \param addr 地址
 * \param pdata 数据指针
 * \return hsic_dflash_addr_t 写入的dflash地址
 *
 * Coding example:
 * \code
 *    Hsic_dflashWriteAddr(0xaf000000&i);
 * \endcode
 *
 */
hsic_dflash_addr_t Hsic_dflashWriteAddr(hsic_dflash_addr_t addr, uint32* pdata);

/******************************************************************************/
/*--------------------------------内联函数定义--------------------------------*/
/******************************************************************************/

static inline uint32 Hsic_dflashRead(uint8 sector, uint8 page)
{
    return *(uint32*)(DFLASH_BASE_ADDR + sector * DFLASH_SECTOR_SIZE + page * DFLASH_PAGE_SIZE);
}

static inline hsic_dflash_addr_t Hsic_dflashWritePage(uint8 sector, uint8 page, uint32* pdata)
{
    hsic_dflash_addr_t addr = IfxFlash_dFlashTableEepLog[sector].start + page * DFLASH_PAGE_SIZE;
    Hsic_dflashWriteAddr(addr, pdata);
    return addr;
}

#endif /* SMARTCAR_HSIC_FLASH_H_ */
