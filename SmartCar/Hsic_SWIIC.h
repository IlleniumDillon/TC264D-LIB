/*
 * Hsic_SWIIC.h
 *
 *  Created on: 2022年7月4日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_SWIIC_H_
#define SMARTCAR_HSIC_SWIIC_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
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
/*----------------------------------枚举定义----------------------------------*/
/******************************************************************************/

typedef enum
{
    ACK,
    NACK,
}hsic_ack_t;

/******************************************************************************/
/*--------------------------------数据类型定义--------------------------------*/
/******************************************************************************/

typedef struct
{
    IfxPort_Pin scl;
    IfxPort_Pin sda;
    uint32 delaytime;
    uint8 slaveaddr;
}hsic_swiic_dev_t;

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief IIC初始化
 * \param dev IIC设备配置结构体指针
 * \param scl 时钟引脚
 * \param sda 数据引脚
 * \para baudrate 波特率
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_swIICInit(&dev,IfxPort_P02_5,IfxPort_P02_4,1000);
 * \endcode
 *
 */
hsic_err_t Hsic_swIICInit(hsic_swiic_dev_t* dev, IfxPort_Pin scl, IfxPort_Pin sda, uint32 baudrate);

/** \brief IIC写
 * \param dev IIC设备配置结构体指针
 * \param slaveaddr 设备地址
 * \param pdata 数据指针
 * \para size 数据量
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_swIICWrite(&dev,0x7e,&i,1);
 * \endcode
 *
 */
void Hsic_swIICWrite(hsic_swiic_dev_t* dev, uint8 slaveaddr, uint8* pdata, size_t size);

/** \brief IIC读
 * \param dev IIC设备配置结构体指针
 * \param slaveaddr 设备地址
 * \param pdata 数据指针
 * \param size 数据量
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
