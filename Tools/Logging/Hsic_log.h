/*
 * Hsic_log.h
 *
 *  Created on: 2022Äê7ÔÂ3ÈÕ
 *      Author: DELL
 */

#ifndef TOOLS_LOGGING_HSIC_LOG_H_
#define TOOLS_LOGGING_HSIC_LOG_H_

#include <Hsic_UART.h>
#include <Hsic_STM.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    HSIC_LOG_NONE = '\0',
    HSIC_LOG_ERROR = 'E',
    HSIC_LOG_WARN = 'W',
    HSIC_LOG_INFO = 'I',
    HSIC_LOG_DEBUG = 'D',
    HSIC_LOG_VERBOSE = 'V',
}hsic_log_level_t;

#define HSIC_LOGE(tag, format, ...) Hsic_Log_Write(HSIC_LOG_ERROR,tag,format,##__VA_ARGS__)
#define HSIC_LOGW(tag, format, ...) Hsic_Log_Write(HSIC_LOG_WARN,tag,format,##__VA_ARGS__)
#define HSIC_LOGI(tag, format, ...) Hsic_Log_Write(HSIC_LOG_INFO,tag,format,##__VA_ARGS__)
#define HSIC_LOGD(tag, format, ...) Hsic_Log_Write(HSIC_LOG_DEBUG,tag,format,##__VA_ARGS__)
#define HSIC_LOGV(tag, format, ...) Hsic_Log_Write(HSIC_LOG_VERBOSE,tag,format,##__VA_ARGS__)

typedef int (*printf_like_t)(const char *, va_list);

extern void* printf_defult;

static inline void Hsic_Log_setVprintf(printf_like_t func);

static inline uint32 Hsic_Log_timeStamp(void);

void Hsic_Log_Write(hsic_log_level_t level, const char* tag, const char* format, ...) __attribute__ ((format (printf, 3, 4)));

void Hsic_Log_Writev(char* format);

static inline void Hsic_Log_setVprintf(printf_like_t func)
{
    printf_defult = func;
}

static inline uint32 Hsic_Log_timeStamp(void)
{
    return Hsic_getMSFromTicks(STM0,IfxStm_get((Ifx_STM *)STM0));
}
#endif /* TOOLS_LOGGING_HSIC_LOG_H_ */
