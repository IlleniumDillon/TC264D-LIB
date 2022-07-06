/*
 * Hsic_ENC.h
 *
 *  Created on: 2022��7��5��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_ENC_H_
#define SMARTCAR_HSIC_ENC_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxGpt12_IncrEnc.h>
#include <IfxGpt12_PinMap.h>
#include <Hsic_common.h>

/******************************************************************************/
/*--------------------------------�������Ͷ���--------------------------------*/
/******************************************************************************/

/*
 * \brief ����������
 */
typedef struct
{
    float32 speed;
    sint32 rawPosition;
    IfxStdIf_Pos_Dir direction;
}hsic_enc_data_t;

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief ��ʼ������������
 * \param a A������
 * \param b B������
 * \param z Z�����ţ�������NULL��
 * \param resolution ����������
 * \param sampletime ��������
 * \param reverse �Ƿ�ת
 * \return ����HSIC_OK������ʼ���ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_encInit(IfxGpt120_T2INA_P00_7_IN,IfxGpt120_T2EUDA_P00_8_IN,IfxGpt120_T2INA_P00_7_IN,4096,0.005,FALSE);
 * \endcode
 *
 */
hsic_err_t Hsic_encInit(IfxGpt12_TxIn_In a, IfxGpt12_TxEud_In b, IfxGpt12_TxIn_In z, uint32 resolution, float sampletime, boolean reverse);

/** \brief ��ñ�������Ϣ
 * \param data ���������ݽṹ��
 * \param a A������
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_encDataUpdate(&data,IfxGpt120_T2INA_P00_7_IN);
 * \endcode
 *
 */
void Hsic_encDataUpdate(hsic_enc_data_t* data, IfxGpt12_TxIn_In a);

#endif /* SMARTCAR_HSIC_ENC_H_ */
