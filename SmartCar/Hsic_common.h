/*
 * Hsic_common.h
 *
 *  Created on: 2022Äê7ÔÂ1ÈÕ
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_COMMON_H_
#define SMARTCAR_HSIC_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <IfxSrc_cfg.h>
#include <IfxAsclin_reg.h>

#define __weak __attribute__((weak))

typedef enum
{
    HSIC_OK,
    HSIC_ERR_INVALID_ARG,
}hsic_err_t;

typedef enum
{
    SRC_CPU0 = IfxSrc_Tos_cpu0,
    SRC_CPU1 = IfxSrc_Tos_cpu1,
    SRC_DMA = IfxSrc_Tos_dma,
}hsic_srctos_t;

#define USE_HSIC_STD 0
#ifdef USE_HSIC_STD

#define HSIC_STDOUT 0

void Hsic_assert(pchar message);

#define _STR(x) _VAL(x)

#define _VAL(x) #x

#define HSIC_ASSERT(expression) ((!!(expression))||Hsic_assert(\
        "Assertion failed: "#expression \
        ", file "__FILE__ \
        ", line "_STR(__LINE__) \
        ", function "__FUNCTION__ \
        "\r\n")\
        );

#endif /*USE_HSIC_STD*/

#endif /* SMARTCAR_HSIC_COMMON_H_ */
