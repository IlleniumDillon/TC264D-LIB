/*
 * Hsic_common.c
 *
 *  Created on: 2022Äê7ÔÂ26ÈÕ
 *      Author: DELL
 */
#include "Hsic_common.h"
#include "IfxCpu.h"
#include "Hsic_UART.h"

#ifdef USE_HSIC_STD

void Hsic_assert(pchar message)
{
    size_t count = strlen(message);
    IfxAsclin_Asc_write(&asc[HSIC_STDOUT], message, &count, TIME_INFINITE);
    while(asc[HSIC_STDOUT].txInProgress);
    abort();
}


#endif
