/*
 * Hsic_STM.h
 *
 *  Created on: 2022��7��2��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_STM_H_
#define SMARTCAR_HSIC_STM_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxStm.h>
#include <IfxStm_Timer.h>
#include <Hsic_common.h>
#include "Hsic_isr.h"

/******************************************************************************/
/*-------------------------------------��-------------------------------------*/
/******************************************************************************/

/*
 * \brief ��ʱ���ж�ʵ�ַ�ʽ
 * \note  ����ѡ��ʱ�����߱Ƚ�����ʽ������ʹ�ö�ʱ��
 */
#define USE_TIMER//USE_CMP

/*
 * \brief ��ʱ���ж����ȼ�
 */
#define INT_PRIO_CMPSTM0_SR0 20
#define INT_PRIO_CMPSTM0_SR1 21
#define INT_PRIO_CMPSTM1_SR0 22
#define INT_PRIO_CMPSTM1_SR1 23

/*
 * \brief ��ʱ���жϴ���ʱ��
 */
#define INT_MS_CMPSTM0_SR0 500
#define INT_MS_CMPSTM0_SR1 5
#define INT_MS_CMPSTM1_SR0 5
#define INT_MS_CMPSTM1_SR1 5

/******************************************************************************/
/*----------------------------------ö�ٶ���----------------------------------*/
/******************************************************************************/

/*
 * \brief ϵͳ����ʱ������ַ
 */
typedef enum
{
    STM0 = (int)0xF0000000u,
    STM1 = (int)0xF0000100u,
}hsic_stm_t;

/*
 * \brief ϵͳ����ʱ���Ƚ���ö��
 */
typedef enum
{
    COMPARATOR0,
    COMPARATOR1,
}hsic_stm_comparator_t;

/******************************************************************************/
/*----------------------------------�ⲿ����----------------------------------*/
/******************************************************************************/

/*
 * \brief ��ʱ���ж�����
 */
#ifdef USE_TIMER
extern IfxStm_Timer Timers[4];
#endif

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

/** \brief ���뼶��ʱ
 * \param stm ��ʱ��ģ��
 * \param ms ��ʱʱ��
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_DelayMS(STM0,1000);
 * \endcode
 *
 */
static inline void Hsic_DelayMS(hsic_stm_t stm, uint32 ms);

/** \brief ��õ�ǰʱ���
 * \param stm ��ʱ��ģ��
 * \return uint32 ���ص�Ƭ���ϵ絽��ʱ�ĵδ���
 *
 * Coding example:
 * \code
 *    uint32 ticks = Hsic_systickGet(STM0);
 * \endcode
 *
 */
static inline uint32 Hsic_systickGet(hsic_stm_t stm);

/** \brief ���δ�������ɺ���
 * \param stm ��ʱ��ģ��
 * \param ticks �δ���
 * \return uint32 ����ĺ��뼶ʱ��
 *
 * Coding example:
 * \code
 *    uint32 ms = Hsic_getMSFromTicks(STM0,0xFFFFF);
 * \endcode
 *
 */
static inline uint32 Hsic_getMSFromTicks(hsic_stm_t stm, uint64 ticks);

#ifdef USE_CMP

/** \brief ʹ�ܱȽ����ж�
 * \param stm ��ʱ��ģ��
 * \param cmp �Ƚ���ģ��
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_enableStmCmpIrq(STM0,COMPARATOR0);
 * \endcode
 *
 */
static inline void Hsic_enableStmCmpIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp);

/** \brief ���ñȽ����ж�
 * \param stm ��ʱ��ģ��
 * \param cmp �Ƚ���ģ��
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

/** \brief ʹ�ܶ�ʱ���ж�
 * \param stm ��ʱ��ģ��
 * \param cmp �Ƚ���ģ��
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_enableStmTimIrq(STM0,COMPARATOR0);
 * \endcode
 *
 */
static inline void Hsic_enableStmTimIrq(hsic_stm_t stm, hsic_stm_comparator_t cmp);

/** \brief ���ö�ʱ���ж�
 * \param stm ��ʱ��ģ��
 * \param cmp �Ƚ���ģ��
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
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

#ifdef USE_CMP

/** \brief ��ʼ���Ƚ����ж�
 * \param stm ��ʱ��ģ��
 * \param cmp �Ƚ���ģ��
 * \para srctos �ж���Ӧ��
 * \para prio �ж����ȼ�
 * \para ms �жϴ���ʱ��
 * \return ����HSIC_OK������ʼ���ɹ�
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

/** \brief ��ʼ����ʱ���ж�
 * \param stm ��ʱ��ģ��
 * \param cmp �Ƚ���ģ��
 * \para srctos �ж���Ӧ��
 * \para prio �ж����ȼ�
 * \para ms �жϴ���ʱ��
 * \para once �Ƿ�ֻ����һ�Σ�TRUE Ϊ���δ���
 * \return ����HSIC_OK������ʼ���ɹ�
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
/*--------------------------------������������--------------------------------*/
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
