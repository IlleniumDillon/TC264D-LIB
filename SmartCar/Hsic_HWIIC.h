/*
 * Hsic_HWIIC.h
 *
 *  Created on: 2022��7��4��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_HWIIC_H_
#define SMARTCAR_HSIC_HWIIC_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxI2c_I2c.h>
#include <Hsic_common.h>
#include <IfxI2c_PinMap.h>

/******************************************************************************/
/*----------------------------------�ⲿ����----------------------------------*/
/******************************************************************************/

/*
 * \brief IIC�豸
 */
extern IfxI2c_I2c_Device i2cDev;

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

/** \brief IICд
 * \param slaveaddr �豸��ַ
 * \param pdata ����ָ��
 * \para size ������
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_hwIICWrite(0xfe,data,1);
 * \endcode
 *
 */
static inline void Hsic_hwIICWrite(uint8 slaveaddr, uint8* pdata, size_t size);

/** \brief IIC��
 * \param slaveaddr �豸��ַ
 * \param pdata ����ָ��
 * \param size ������
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_hwIICWrite(0xff,data,1);
 * \endcode
 *
 */
static inline void Hsic_hwIICRead(uint8 slaveaddr, uint8* pdata, size_t size);

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief IIC��ʼ��
 * \param scl ʱ������
 * \param sda ��������
 * \para baudrate ������
 * \return ����HSIC_OK������ʼ���ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_hwIICInit(IfxI2c0_SCL_P02_5_INOUT,IfxI2c0_SDA_P02_4_INOUT,1000);
 * \endcode
 *
 */
hsic_err_t Hsic_hwIICInit(IfxI2c_Scl_InOut scl, IfxI2c_Sda_InOut sda, uint32 baudrate);

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

static inline void Hsic_hwIICWrite(uint8 slaveaddr, uint8* pdata, size_t size)
{
    i2cDev.deviceAddress = slaveaddr;
    while(IfxI2c_I2c_write(&i2cDev, pdata, (Ifx_SizeT)size)==IfxI2c_I2c_Status_nak);
}

static inline void Hsic_hwIICRead(uint8 slaveaddr, uint8* pdata, size_t size)
{
    i2cDev.deviceAddress = slaveaddr;
    while(IfxI2c_I2c_read(&i2cDev, pdata, (Ifx_SizeT)size)==IfxI2c_I2c_Status_nak);
}

#endif /* SMARTCAR_HSIC_HWIIC_H_ */
