/*
 * Hsic_ADC.h
 *
 *  Created on: 2022��7��5��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_ADC_H_
#define SMARTCAR_HSIC_ADC_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxVadc_Adc.h>
#include <IfxVadc_PinMap.h>
#include <IfxVadc.h>
#include <Hsic_common.h>

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief ADC���ų�ʼ��
 * \param pin ADC����
 * \return ����HSIC_OK������ʼ���ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_adcInit(IfxVadc_G0_0_AN0_IN);
 * \endcode
 *
 */
hsic_err_t Hsic_adcInit(IfxVadc_Vadcg_In pin);

/** \brief ADC����
 * \param pin ADC����
 * \return uint16 ����Ϊ12λ
 *
 * Coding example:
 * \code
 *    Hsic_adcGet(IfxVadc_G0_0_AN0_IN);
 * \endcode
 *
 */
uint16 Hsic_adcGet(IfxVadc_Vadcg_In pin);


#endif /* SMARTCAR_HSIC_ADC_H_ */
