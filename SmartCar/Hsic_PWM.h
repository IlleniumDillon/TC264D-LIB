/*
 * Hsic_PWM.h
 *
 *  Created on: 2022年7月1日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_PWM_H_
#define SMARTCAR_HSIC_PWM_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxGtm_Atom_Pwm.h>
#include <IfxGtm_reg.h>
#include <IfxGtm_PinMap.h>
#include "Hsic_common.h"

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief 初始化指定PWM引脚
 * \param pin PWM引脚
 * \param freq PWM频率
 * \param duty PWM占空比
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_pwmInit(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,1000,0.5);
 * \endcode
 *
 */
hsic_err_t Hsic_pwmInit(IfxGtm_Atom_ToutMap pin, float freq, float duty);

/** \brief 设定占空比
 * \param pin PWM引脚
 * \param duty PWM占空比
 * \return 返回HSIC_OK表明操作成功
 *
 * Coding example:
 * \code
 *    Hsic_pwmSetDuty(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,0.5);
 * \endcode
 *
 */
hsic_err_t Hsic_pwmSetDuty(IfxGtm_Atom_ToutMap pin, float duty);

/** \brief 设定频率，占空比保持不变
 * \param pin PWM引脚
 * \param freq PWM频率
 * \return 返回HSIC_OK表明操作成功
 *
 * Coding example:
 * \code
 *    Hsic_pwmSetFreq(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,1000);
 * \endcode
 *
 */
hsic_err_t Hsic_pwmSetFreq(IfxGtm_Atom_ToutMap pin, float freq);

/** \brief 设定频率和占空比
 * \param pin PWM引脚
 * \param freq PWM频率
 * \param duty PWM占空比
 * \return 返回HSIC_OK表明操作成功
 *
 * Coding example:
 * \code
 *    Hsic_pwmSetFreqDuty(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,1000,0.5);
 * \endcode
 *
 */
hsic_err_t Hsic_pwmSetFreqDuty(IfxGtm_Atom_ToutMap pin, float freq, float duty);

#endif /* SMARTCAR_HSIC_PWM_H_ */
