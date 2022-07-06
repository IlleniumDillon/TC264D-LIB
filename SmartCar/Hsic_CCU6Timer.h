/*
 * Hsic_CCU6Timer.h
 *
 *  Created on: 2022��7��6��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_CCU6TIMER_H_
#define SMARTCAR_HSIC_CCU6TIMER_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxCcu6_Timer.h>
#include <IfxCcu6_reg.h>
#include <Hsic_common.h>
#include "SysSe/Bsp/Bsp.h"
#include "If/Ccu6If/Timer.h"
#include <Hsic_isr.h>

/******************************************************************************/
/*-------------------------------------��-------------------------------------*/
/******************************************************************************/

/*
 * \brief ��ʱ���ж����ȼ�
 */
#define INT_PRIO_CCU60_TM0 100
#define INT_PRIO_CCU60_TM1 101
#define INT_PRIO_CCU61_TM0 102
#define INT_PRIO_CCU61_TM1 103

/******************************************************************************/
/*----------------------------------ö�ٶ���----------------------------------*/
/******************************************************************************/

/*
 * \brief CCU6ģ�����ַ
 */
typedef enum
{
    CCU60 = (int)0xF0002A00u,
    CCU61 = (int)0xF0002B00u,
}hsic_ccu6_t;

/*
 * \brief CCU6��ʱ��ö��
 */
typedef enum
{
    TM0,
    TM1,
}hsic_ccu6_timer_t;

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

/** \brief �ر�ccu6��ʱ��
 * \param ccu6 CCU6ģ��
 * \param tm ��ʱ��ͨ��
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_ccu6TimerStop(CCU60,TM0);
 * \endcode
 *
 */
static inline void Hsic_ccu6TimerStop(hsic_ccu6_t ccu6, hsic_ccu6_timer_t tm);

/** \brief ����ccu6��ʱ��
 * \param ccu6 CCU6ģ��
 * \param tm ��ʱ��ͨ��
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
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief ��ʼ��ccu6��ʱ���ж�
 * \param ccu6 CCU6ģ��
 * \param tm ��ʱ��ͨ��
 * \param srctos �ж���Ӧ��
 * \param prio �ж����ȼ�
 * \param ms ��ʱ���жϴ���ʱ��
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
/*--------------------------------������������--------------------------------*/
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
