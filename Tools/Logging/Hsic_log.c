/*
 * Hsic_log.c
 *
 *  Created on: 2022Äê7ÔÂ3ÈÕ
 *      Author: DELL
 */

#include "Hsic_log.h"

void* printf_defult = &Hsic_Log_Writev;

char frameHead[128];
char frameBody[64];

void Hsic_Log_Write(hsic_log_level_t level, const char* tag, const char* format, ...)
{
    uint32 time = Hsic_Log_timeStamp();
    va_list list;
    va_start(list, format);
    sprintf(frameHead,"%c: [%lu] %s:",(char)level,time,tag);
    vsprintf(frameBody,format,list);
    strcat(frameHead,frameBody);
    Hsic_Log_Writev(frameHead);
    va_end(list);
}

void Hsic_Log_Writev(char* format)
{
    Hsic_uartWrite((uint8*)format,strlen(format),0);
}

