/*
 * Hsic_SWSPI.h
 *
 *  Created on: 2022年7月5日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_SWSPI_H_
#define SMARTCAR_HSIC_SWSPI_H_

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
/*--------------------------------数据类型定义--------------------------------*/
/******************************************************************************/

/*
 * \brief 确定极性与相位的函数指针
 */
typedef void (*sclk_active_t)(IfxPort_Pin sclk);
typedef void (*sclk_idle_t)(IfxPort_Pin sclk);
typedef void (*sclk_effectiveedge_t)(IfxPort_Pin sclk, uint32 delaytime);
typedef void (*sclk_ineffectiveedge_t)(IfxPort_Pin sclk, uint32 delaytime);

/*
 * \brief SPI设备结构体
 */
typedef struct
{
    IfxPort_Pin mosi;
    IfxPort_Pin miso;
    IfxPort_Pin sclk;
    IfxPort_Pin cs;
    uint32 delaytime;
    sclk_active_t sclk_active;
    sclk_idle_t sclk_idle;
    sclk_effectiveedge_t sclk_effectiveedge;
    sclk_ineffectiveedge_t sclk_ineffectiveedge;
}hsic_swspi_dev_t;

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief SPI设备初始化
 * \param miso 主机输入从机输出
 * \param mosi 主机输出从机输入
 * \param sclk 主机时钟输出
 * \para cs 主机片选输出
 * \para baudrate 波特率
 * \para mode 极性与相位
 * \return hsic_swspi_dev_t SPI设备结构体
 *
 * Coding example:
 * \code
 *    hsic_swspi_dev_t dev = Hsic_swSPIInit(IfxPort_P20_12,IfxPort_P20_14,IfxPort_P20_11,IfxPort_P20_8,1000000,0);
 * \endcode
 *
 */
hsic_swspi_dev_t Hsic_swSPIInit(IfxPort_Pin miso, IfxPort_Pin mosi, IfxPort_Pin sclk, IfxPort_Pin cs,
        uint32 baudrate,uint8 mode);

/** \brief SPI数据传输
 * \param dev SPI设备配置结构体指针
 * \param ptxdata 发送的数据
 * \param prxdata 接收的数据
 * \para count 数据量
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_swSPIExchange(&dev,&i[0],&j[0],5);
 * \endcode
 *
 */
void Hsic_swSPIExchange(hsic_swspi_dev_t* dev, uint8* ptxdata, uint8* prxdata, size_t count);


#endif /* SMARTCAR_HSIC_SWSPI_H_ */
