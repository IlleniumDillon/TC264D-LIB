/*
 * Hsic_common.h
 *
 *  Created on: 2022Äê7ÔÂ1ÈÕ
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_COMMON_H_
#define SMARTCAR_HSIC_COMMON_H_

#include <stdio.h>
#include <IfxSrc_cfg.h>

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

#endif /* SMARTCAR_HSIC_COMMON_H_ */
