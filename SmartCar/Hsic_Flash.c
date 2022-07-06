/*
 * Hsic_Flash.c
 *
 *  Created on: 2022Äê7ÔÂ5ÈÕ
 *      Author: DELL
 */

#include <Hsic_Flash.h>

void Hsic_dflashSectorErase(uint8 sector)
{
    uint16 end_init_sfty_pw = IfxScuWdt_getSafetyWatchdogPassword();
    IfxScuWdt_clearSafetyEndinit(end_init_sfty_pw);
    IfxFlash_eraseSector(IfxFlash_dFlashTableEepLog[sector].start);
    IfxScuWdt_setSafetyEndinit(end_init_sfty_pw);
    IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
}

hsic_dflash_addr_t Hsic_dflashWriteAddr(hsic_dflash_addr_t addr, uint32* pdata)
{
    uint16 end_init_sfty_pw = IfxScuWdt_getSafetyWatchdogPassword();
    if(IfxFlash_enterPageMode((uint32)addr)==1) return (hsic_dflash_addr_t)NULL;
    IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
    IfxFlash_loadPage(addr, pdata[0], 0);
    IfxScuWdt_clearSafetyEndinit(end_init_sfty_pw);
    IfxFlash_writePage(addr);
    IfxScuWdt_setSafetyEndinit(end_init_sfty_pw);
    IfxFlash_waitUnbusy(0, IfxFlash_FlashType_D0);
    return addr;
}
