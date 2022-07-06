/*
 * Hsic_CCU6Timer.h
 *
 *  Created on: 2022年7月6日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_CCU6TIMER_H_
#define SMARTCAR_HSIC_CCU6TIMER_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxCcu6_Timer.h>
#include <IfxCcu6_reg.h>
#include <Hsic_common.h>
#include "SysSe/Bsp/Bsp.h"
#include "If/Ccu6If/Timer.h"
#include <Hsic_isr.h>

/******************************************************************************/
/*-------------------------------------宏-------------------------------------*/
/******************************************************************************/

/*
 * \brief 定时器中断优先级
 */
#define INT_PRIO_CCU60_TM0 100
#define INT_PRIO_CCU60_TM1 101
#define INT_PRIO_CCU61_TM0 102
#define INT_PRIO_CCU61_TM1 103

/******************************************************************************/
/*----------------------------------枚举定义----------------------------------*/
/******************************************************************************/

/*
 * \brief CCU6模块基地址
 */
typedef enum
{
    CCU60 = (int)0xF0002A00u,
    CCU61 = (int)0xF0002B00u,
}hsic_ccu6_t;

/*
 * \brief CCU6定时器枚举
 */
typedef enum
{
    TM0,
    TM1,
}hsic_ccu6_timer_t;

/******************************************************************************/
/*--------------------------------内联函数声明--------------------------------*/
/******************************************************************************/

/** \brief 关闭ccu6定时器
 * \param ccu6 CCU6模块
 * \param tm 定时器通道
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_ccu6TimerStop(CCU60,TM0);
 * \endcode
 *
 */
static inline void Hsic_ccu6TimerStop(hsic_ccu6_t ccu6, hsic_ccu6_timer_t tm);

/** \brief 开启ccu6定时器
 * \param ccu6 CCU6模块
 * \param tm 定时器通道
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_ccu6TimerStart(CCU60,TM0);
 * \endcode
 *
 */
static inline void Hsic_ccu6TimerStart(hsic_ccu6_t ccu6, hsic_ccu6_timer_t tm);

/******************************************************************************/
/*--------------------------------全局函数定义--------------------------------*/
/******************************************************************************/

/** \brief 初始化ccu6定时器中断
 * \param ccu6 CCU6模块
 * \param tm 定时器通道
 * \param srctos 中断响应核
 * \param prio 中断优先级
 * \param ms 定时器中断触发时间
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_ccu6TimerIrqInit(CCU60,TM0,SRC_CPU0,INT_PRIO_CCU60_TM0,100);
 * \endcode
 *
 */
hsic_err_t Hsic_ccu6TimerIrqInit(hsic_ccu6_t ccu6, hsic_ccu6_timer_t tm, hsic_srctos_t srctos, uint8 prio, uint32 ms);

/******************************************************************************/
/*--------------------------------内联函数定义--------------------------------*/
/******************************************************************************/

static inline void Hsic_ccu6TimerStop(hsic_ccu6_t ccu6, hsic_ccu6_timer_t tm)
{
    IfxCcu6_Timer ccu6Timer = {.ccu6 = (Ifx_CCU6*)ccu6, .timer=(IfxCcu6_TimerId)TM0};
    IfxCcu6_Timer_stop(&ccu6Timer);
}

static inline void Hsic_ccu6TimerStart(hsic_ccu6_t ccu6, hsic_ccu6_timer_t tm)
{
    IfxCcu6_Timer ccu6Timer = {.ccu6 = (Ifx_CCU6*)ccu6, .timer=(IfxCcu6_TimerId)TM0};
    IfxCcu6_Timer_start(&ccu6Timer);
}

#endif /* SMARTCAR_HSIC_CCU6TIMER_H_ */
