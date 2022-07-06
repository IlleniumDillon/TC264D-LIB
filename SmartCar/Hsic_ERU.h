/*
 * Hsic_ERU.h
 *
 *  Created on: 2022年7月1日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_ERU_H_
#define SMARTCAR_HSIC_ERU_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include "Src/Std/IfxSrc.h"
#include "SysSe/Bsp/Bsp.h"
#include "IfxScuEru.h"
#include <Hsic_common.h>
#include "Hsic_isr.h"

/******************************************************************************/
/*-------------------------------------宏-------------------------------------*/
/******************************************************************************/

/*
 * \brief 外部中断引脚基地址
 * \note  每一通道只能使用一个外部中断引脚
 */
#define    ERUCH0_P15_4    IfxScu_REQ0_P15_4_IN
#define    ERUCH1_P14_3    IfxScu_REQ10_P14_3_IN
#define    ERUCH7_P20_9    IfxScu_REQ11_P20_9_IN
#define    ERUCH6_P11_10   IfxScu_REQ12_P11_10_IN
#define    ERUCH4_P15_5    IfxScu_REQ13_P15_5_IN
#define    ERUCH2_P02_1    IfxScu_REQ14_P02_1_IN
#define    ERUCH3_P14_1    IfxScu_REQ15_P14_1_IN
#define    ERUCH7_P15_1    IfxScu_REQ16_P15_1_IN
#define    ERUCH5_P15_8    IfxScu_REQ1_P15_8_IN
#define    ERUCH2_P10_2    IfxScu_REQ2_P10_2_IN
#define    ERUCH3_P10_3    IfxScu_REQ3_P10_3_IN
#define    ERUCH0_P10_7    IfxScu_REQ4_P10_7_IN
#define    ERUCH1_P10_8    IfxScu_REQ5_P10_8_IN
#define    ERUCH3_P02_0    IfxScu_REQ6_P02_0_IN
#define    ERUCH2_P00_4    IfxScu_REQ7_P00_4_IN
#define    ERUCH4_P33_7    IfxScu_REQ8_P33_7_IN
#define    ERUCH6_P20_0    IfxScu_REQ9_P20_0_IN

/*
 * \brief 外部中断绑定核和中断优先级
 * \note  同一组中断只能由同一核响应
 */
#define ERU_CH0_CH4_INT_SERVICE IfxSrc_Tos_cpu0
#define ERU_CH0_CH4_INT_PRIO    40

#define ERU_CH1_CH5_INT_SERVICE IfxSrc_Tos_cpu0
#define ERU_CH1_CH5_INT_PRIO    41

#define ERU_CH2_CH6_INT_SERVICE IfxSrc_Tos_cpu0
#define ERU_CH2_CH6_INT_PRIO    5

#define ERU_CH3_CH7_INT_SERVICE IfxSrc_Tos_cpu0
#define ERU_CH3_CH7_INT_PRIO    43

/******************************************************************************/
/*----------------------------------枚举定义----------------------------------*/
/******************************************************************************/

/*
 * \brief 外部中断触发方式
 */
typedef enum
{
    RISING,
    FALLING,
    BOTH,
}hsic_trigger_t;

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief 初始化指定外部中断引脚
 * \param pin 外部中断引脚基地址
 * \param trigger 中断触发方式
 * \param srctos 指定中断响应核
 * \param prio 中断优先级
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_eruPinInit(ERUCH6_P11_10,FALLING,ERU_CH2_CH6_INT_SERVICE,ERU_CH2_CH6_INT_PRIO);
 * \endcode
 *
 */
hsic_err_t Hsic_eruPinInit(IfxScu_Req_In pin, hsic_trigger_t trigger, hsic_srctos_t srctos, uint8 prio);

/** \brief 使能指定外部中断引脚
 * \param pin 外部中断引脚基地址
 * \return 返回HSIC_OK表明操作成功
 *
 * Coding example:
 * \code
 *    Hsic_eruEnable(ERUCH6_P11_10);
 * \endcode
 *
 */
hsic_err_t Hsic_eruEnable(IfxScu_Req_In pin);

/** \brief 禁用指定外部中断引脚
 * \param pin 外部中断引脚基地址
 * \return 返回HSIC_OK表明操作成功
 *
 * Coding example:
 * \code
 *    Hsic_eruDisable(ERUCH6_P11_10);
 * \endcode
 *
 */
hsic_err_t Hsic_eruDisable(IfxScu_Req_In pin);

#endif /* SMARTCAR_HSIC_ERU_H_ */
