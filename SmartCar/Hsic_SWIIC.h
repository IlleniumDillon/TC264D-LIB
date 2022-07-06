/*
 * Hsic_SWIIC.h
 *
 *  Created on: 2022��7��4��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_SWIIC_H_
#define SMARTCAR_HSIC_SWIIC_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxPort_PinMap.h>
#include <IfxPort_Io.h>
#include <IfxPort.h>
#include <IfxPort_reg.h>
#include <IfxStm.h>
#include <IfxStm_Timer.h>
#include <Hsic_STM.h>
#include <Hsic_common.h>

/******************************************************************************/
/*----------------------------------ö�ٶ���----------------------------------*/
/******************************************************************************/

typedef enum
{
    ACK,
    NACK,
}hsic_ack_t;

/******************************************************************************/
/*--------------------------------�������Ͷ���--------------------------------*/
/******************************************************************************/

typedef struct
{
    IfxPort_Pin scl;
    IfxPort_Pin sda;
    uint32 delaytime;
    uint8 slaveaddr;
}hsic_swiic_dev_t;

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief IIC��ʼ��
 * \param dev IIC�豸���ýṹ��ָ��
 * \param scl ʱ������
 * \param sda ��������
 * \para baudrate ������
 * \return ����HSIC_OK������ʼ���ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_swIICInit(&dev,IfxPort_P02_5,IfxPort_P02_4,1000);
 * \endcode
 *
 */
hsic_err_t Hsic_swIICInit(hsic_swiic_dev_t* dev, IfxPort_Pin scl, IfxPort_Pin sda, uint32 baudrate);

/** \brief IICд
 * \param dev IIC�豸���ýṹ��ָ��
 * \param slaveaddr �豸��ַ
 * \param pdata ����ָ��
 * \para size ������
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_swIICWrite(&dev,0x7e,&i,1);
 * \endcode
 *
 */
void Hsic_swIICWrite(hsic_swiic_dev_t* dev, uint8 slaveaddr, uint8* pdata, size_t size);

/** \brief IIC��
 * \param dev IIC�豸���ýṹ��ָ��
 * \param slaveaddr �豸��ַ
 * \param pdata ����ָ��
 * \param size ������
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_swIICRead(&dev,0x7e,&i,1);
 * \endcode
 *
 */
void Hsic_swIICRead(hsic_swiic_dev_t* dev, uint8 slaveaddr, uint8* pdata, size_t size);

#endif /* SMARTCAR_HSIC_SWIIC_H_ */
