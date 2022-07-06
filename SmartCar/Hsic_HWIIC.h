/*
 * Hsic_HWIIC.h
 *
 *  Created on: 2022年7月4日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_HWIIC_H_
#define SMARTCAR_HSIC_HWIIC_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxI2c_I2c.h>
#include <Hsic_common.h>
#include <IfxI2c_PinMap.h>

/******************************************************************************/
/*----------------------------------外部变量----------------------------------*/
/******************************************************************************/

/*
 * \brief IIC设备
 */
extern IfxI2c_I2c_Device i2cDev;

/******************************************************************************/
/*--------------------------------内联函数声明--------------------------------*/
/******************************************************************************/

/** \brief IIC写
 * \param slaveaddr 设备地址
 * \param pdata 数据指针
 * \para size 数据量
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_hwIICWrite(0xfe,data,1);
 * \endcode
 *
 */
static inline void Hsic_hwIICWrite(uint8 slaveaddr, uint8* pdata, size_t size);

/** \brief IIC读
 * \param slaveaddr 设备地址
 * \param pdata 数据指针
 * \param size 数据量
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
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief IIC初始化
 * \param scl 时钟引脚
 * \param sda 数据引脚
 * \para baudrate 波特率
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_hwIICInit(IfxI2c0_SCL_P02_5_INOUT,IfxI2c0_SDA_P02_4_INOUT,1000);
 * \endcode
 *
 */
hsic_err_t Hsic_hwIICInit(IfxI2c_Scl_InOut scl, IfxI2c_Sda_InOut sda, uint32 baudrate);

/******************************************************************************/
/*--------------------------------内联函数定义--------------------------------*/
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
