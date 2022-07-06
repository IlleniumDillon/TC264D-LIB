/*
 * Hsic_Flash.h
 *
 *  Created on: 2022��7��5��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_FLASH_H_
#define SMARTCAR_HSIC_FLASH_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxFlash.h>
#include <IfxScuWdt.h>
#include <Hsic_common.h>

/******************************************************************************/
/*-------------------------------------��-------------------------------------*/
/******************************************************************************/

/*
 * \brief dflash�Ĵ�С��������ҳ�Ĵ�С
 */
#define DFLASH_BASE_ADDR    IFXFLASH_DFLASH_START
#define DFLASH_SIZE         IFXFLASH_DFLASH_SIZE

#define DFLASH_SECROT_NUM   IFXFLASH_DFLASH_NUM_LOG_SECTORS
#define DFLASH_SECTOR_SIZE  (IFXFLASH_DFLASH_SIZE/IFXFLASH_DFLASH_NUM_LOG_SECTORS)

#define DFLASH_PAGE_NUM     (DFLASH_SECTOR_SIZE/IFXFLASH_DFLASH_PAGE_LENGTH)
#define DFLASH_PAGE_SIZE    IFXFLASH_DFLASH_PAGE_LENGTH

/*
 * \brief ����ַ
 */
#define DFLASH_READ_PAGE(addr) (*(uint32*)addr)

/******************************************************************************/
/*--------------------------------�������Ͷ���--------------------------------*/
/******************************************************************************/

/*
 * \brief dflash��ַ
 */
typedef uint32 hsic_dflash_addr_t;

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

/** \brief dflash��������ҳ����
 * \param sector ������
 * \param page ҳ��
 * \return uint32 ����������
 *
 * Coding example:
 * \code
 *    uint32 i = Hsic_dflashRead(0,0);
 * \endcode
 *
 */
static inline uint32 Hsic_dflashRead(uint8 sector, uint8 page);

/** \brief dflash��ҳд����
 * \param sector ������
 * \param page ҳ��
 * \param pdata ����ָ��
 * \return hsic_dflash_addr_t д���dflash��ַ
 *
 * Coding example:
 * \code
 *    Hsic_dflashWritePage(0,0,&i);
 * \endcode
 *
 */
static inline hsic_dflash_addr_t Hsic_dflashWritePage(uint8 sector, uint8 page, uint32* pdata);

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief dflash��������
 * \param sector ������
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_dflashSectorErase(0);
 * \endcode
 *
 */
void Hsic_dflashSectorErase(uint8 sector);

/** \brief dflash����ַд����
 * \param addr ��ַ
 * \param pdata ����ָ��
 * \return hsic_dflash_addr_t д���dflash��ַ
 *
 * Coding example:
 * \code
 *    Hsic_dflashWriteAddr(0xaf000000&i);
 * \endcode
 *
 */
hsic_dflash_addr_t Hsic_dflashWriteAddr(hsic_dflash_addr_t addr, uint32* pdata);

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
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
