/*
 * Hsic_PWM.h
 *
 *  Created on: 2022��7��1��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_PWM_H_
#define SMARTCAR_HSIC_PWM_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxGtm_Atom_Pwm.h>
#include <IfxGtm_reg.h>
#include <IfxGtm_PinMap.h>
#include "Hsic_common.h"

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief ��ʼ��ָ��PWM����
 * \param pin PWM����
 * \param freq PWMƵ��
 * \param duty PWMռ�ձ�
 * \return ����HSIC_OK������ʼ���ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_pwmInit(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,1000,0.5);
 * \endcode
 *
 */
hsic_err_t Hsic_pwmInit(IfxGtm_Atom_ToutMap pin, float freq, float duty);

/** \brief �趨ռ�ձ�
 * \param pin PWM����
 * \param duty PWMռ�ձ�
 * \return ����HSIC_OK���������ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_pwmSetDuty(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,0.5);
 * \endcode
 *
 */
hsic_err_t Hsic_pwmSetDuty(IfxGtm_Atom_ToutMap pin, float duty);

/** \brief �趨Ƶ�ʣ�ռ�ձȱ��ֲ���
 * \param pin PWM����
 * \param freq PWMƵ��
 * \return ����HSIC_OK���������ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_pwmSetFreq(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,1000);
 * \endcode
 *
 */
hsic_err_t Hsic_pwmSetFreq(IfxGtm_Atom_ToutMap pin, float freq);

/** \brief �趨Ƶ�ʺ�ռ�ձ�
 * \param pin PWM����
 * \param freq PWMƵ��
 * \param duty PWMռ�ձ�
 * \return ����HSIC_OK���������ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_pwmSetFreqDuty(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,1000,0.5);
 * \endcode
 *
 */
hsic_err_t Hsic_pwmSetFreqDuty(IfxGtm_Atom_ToutMap pin, float freq, float duty);

#endif /* SMARTCAR_HSIC_PWM_H_ */
