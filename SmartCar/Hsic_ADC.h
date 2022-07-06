/*
 * Hsic_ADC.h
 *
 *  Created on: 2022年7月5日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_ADC_H_
#define SMARTCAR_HSIC_ADC_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxVadc_Adc.h>
#include <IfxVadc_PinMap.h>
#include <IfxVadc.h>
#include <Hsic_common.h>

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief ADC引脚初始化
 * \param pin ADC引脚
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_adcInit(IfxVadc_G0_0_AN0_IN);
 * \endcode
 *
 */
hsic_err_t Hsic_adcInit(IfxVadc_Vadcg_In pin);

/** \brief ADC采样
 * \param pin ADC引脚
 * \return uint16 精度为12位
 *
 * Coding example:
 * \code
 *    Hsic_adcGet(IfxVadc_G0_0_AN0_IN);
 * \endcode
 *
 */
uint16 Hsic_adcGet(IfxVadc_Vadcg_In pin);


#endif /* SMARTCAR_HSIC_ADC_H_ */
