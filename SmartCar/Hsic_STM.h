/*
 * Hsic_STM.h
 *
 *  Created on: 2022年7月2日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_STM_H_
#define SMARTCAR_HSIC_STM_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxStm.h>
#include <IfxStm_Timer.h>
#include <Hsic_common.h>
#include "Hsic_isr.h"

/******************************************************************************/
/*-------------------------------------宏-------------------------------------*/
/******************************************************************************/

/*
 * \brief 定时器中断实现方式
 * \note  可以选择定时器或者比较器方式，建议使用定时器
 */
#define USE_TIMER//USE_CMP

/*
 * \brief 定时器中断优先级
 */
#define INT_PRIO_CMPSTM0_SR0 20
#define INT_PRIO_CMPSTM0_SR1 21
#define INT_PRIO_CMPSTM1_SR0 22
#define INT_PRIO_CMPSTM1_SR1 23

/*
 * \brief 定时器中断触发时间
 */
#define INT_MS_CMPSTM0_SR0 500
#define INT_MS_CMPSTM0_SR1 5
#define INT_MS_CMPSTM1_SR0 5
#define INT_MS_CMPSTM1_SR1 5

/******************************************************************************/
/*----------------------------------枚举定义----------------------------------*/
/******************************************************************************/

/*
 * \brief 系统级定时器基地址
 */
typedef enum
{
    STM0 = (int)0xF0000000u,
    STM1 = (int)0xF0000100u,
}hsic_stm_t;

/*
 * \brief 系统级定时器比较器枚举
 */
typedef enum
{
    COMPARATOR0,
    COMPARATOR1,
}hsic_stm_comparator_t;

/******************************************************************************/
/*----------------------------------外部变量----------------------------------*/
/******************************************************************************/

/*
 * \brief 定时器中断驱动
 */
#ifdef USE_TIMER
extern IfxStm_Timer Timers[4];
#endif

/******************************************************************************/
/*--------------------------------内联函数声明--------------------------------*/
/******************************************************************************/

/** \brief 毫秒级延时
 * \param stm 定时器模块
 * \param ms 延时时间
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_DelayMS(STM0,1000);
 * \endcode
 *
 */
static inline void Hsic_DelayMS(hsic_stm_t stm, uint32 ms);

/** \brief 获得当前时间戳
 * \param stm 定时器模块
 * \return uint32 返回单片机上电到此时的滴答数
 *
 * Coding example:
 * \code
 *    uint32 ticks = Hsic_systickGet(STM0);
 * \endcode
 *
 */
static inline uint32 Hsic_systickGet(hsic_stm_t stm);

/** \brief 将滴答数换算成毫秒
 * \param stm 定时器模块
 * \param ticks 滴答数
 * \return uint32 换算的毫秒级时间
 *
 * Coding example:
 * \code
 *    uint32 ms = Hsic_getMSFromTicks(STM0,0xFFFFF);
 * \endcode
 *
 */
static inline uint32 Hsic_getMSFromTicks(hsic_stm_t stm, uint64 ticks);

#ifdef USE_CMP

/** \brief 使能比较器中断
 * \param stm 定时器模块
 * \param cmp 比较器模块
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_enableStmCmpIrq(STM0,COMPARATOR0);
 * \endcode
 *
 */
static inline void Hsic_enableStmCmpIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp);

/** \brief 禁用比较器中断
 * \param stm 定时器模块
 * \param cmp 比较器模块
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_disableStmCmpIrq(STM0,COMPARATOR0);
 * \endcode
 *
 */
static inline void Hsic_disableStmCmpIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp);

#endif

#ifdef USE_TIMER

/** \brief 使能定时器中断
 * \param stm 定时器模块
 * \param cmp 比较器模块
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_enableStmTimIrq(STM0,COMPARATOR0);
 * \endcode
 *
 */
static inline void Hsic_enableStmTimIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp);

/** \brief 禁用定时器中断
 * \param stm 定时器模块
 * \param cmp 比较器模块
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_disableStmTimIrq(STM0,COMPARATOR0);
 * \endcode
 *
 */
static inline void Hsic_disableStmTimIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp);
#endif

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

#ifdef USE_CMP

/** \brief 初始化比较器中断
 * \param stm 定时器模块
 * \param cmp 比较器模块
 * \para srctos 中断响应核
 * \para prio 中断优先级
 * \para ms 中断触发时间
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_stmCmpIrqInit(STM0,COMPARATOR0,SRC_CPU0,INT_PRIO_CMPSTM0_SR0,INT_MS_CMPSTM0_SR0);
 * \endcode
 *
 */
hsic_err_t Hsic_stmCmpIrqInit(hsic_stm_t stm, hsic_stm_comparator_t cmp, hsic_srctos_t srctos, uint8 prio, uint32 ms);

#endif

#ifdef USE_TIMER

/** \brief 初始化定时器中断
 * \param stm 定时器模块
 * \param cmp 比较器模块
 * \para srctos 中断响应核
 * \para prio 中断优先级
 * \para ms 中断触发时间
 * \para once 是否只触发一次，TRUE 为单次触发
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_stmTimIrqInit(STM0,COMPARATOR0,SRC_CPU0,INT_PRIO_CMPSTM0_SR0,INT_MS_CMPSTM0_SR0,FALSE);
 * \endcode
 *
 */
hsic_err_t Hsic_stmTimIrqInit(hsic_stm_t stm, hsic_stm_comparator_t cmp, hsic_srctos_t srctos, uint8 prio, uint32 ms, boolean once);

#endif

/******************************************************************************/
/*--------------------------------内联函数定义--------------------------------*/
/******************************************************************************/

static inline void Hsic_DelayMS(hsic_stm_t stm, uint32 ms)
{
    IfxStm_waitTicks((Ifx_STM *)stm,IfxStm_getTicksFromMilliseconds((Ifx_STM *)stm,ms));
}

static inline uint32 Hsic_systickGet(hsic_stm_t stm)
{
    return IfxStm_getLower((Ifx_STM *)stm);
}

static inline uint32 Hsic_getMSFromTicks(hsic_stm_t stm, uint64 ticks)
{
    return (uint32)((float)ticks/IfxStm_getFrequency((Ifx_STM *)stm)*1000.0);
}

#ifdef USE_CMP

static inline void Hsic_enableStmCmpIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp)
{
    IfxStm_enableComparatorInterrupt((Ifx_STM *)stm, (IfxStm_Comparator)cmp);
}

static inline void Hsic_disableStmCmpIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp)
{
    IfxStm_disableComparatorInterrupt((Ifx_STM *)stm, (IfxStm_Comparator)cmp);
}

#endif

#ifdef USE_TIMER

static inline void Hsic_enableStmTimIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp)
{
    uint8 i = 0;
    if((Ifx_STM *)stm == &MODULE_STM1)i=2;
    if(cmp == 1)i+=1;
    IfxStm_Timer_run(&Timers[i]);
}

static inline void Hsic_disableStmTimIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp)
{
    uint8 i = 0;
    if((Ifx_STM *)stm == &MODULE_STM1)i=2;
    if(cmp == 1)i+=1;
    IfxStm_Timer_stop(&Timers[i]);
}

#endif

#endif /* SMARTCAR_HSIC_STM_H_ */
