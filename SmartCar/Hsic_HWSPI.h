/*
 * Hsic_HWSPI.h
 *
 *  Created on: 2022年7月4日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_HWSPI_H_
#define SMARTCAR_HSIC_HWSPI_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxQspi_SpiMaster.h>
#include <IfxQspi_PinMap.h>
#include <Hsic_common.h>
#include <Hsic_isr.h>
#include <string.h>

/******************************************************************************/
/*-------------------------------------宏-------------------------------------*/
/******************************************************************************/

/*
 * \brief SPI中断优先级
 */
#define INT_PRIO_QSPI0_TX 24
#define INT_PRIO_QSPI0_RX 25
#define INT_PRIO_QSPI0_ER 26

#define INT_PRIO_QSPI1_TX 27
#define INT_PRIO_QSPI1_RX 28
#define INT_PRIO_QSPI1_ER 29

#define INT_PRIO_QSPI2_TX 30
#define INT_PRIO_QSPI2_RX 31
#define INT_PRIO_QSPI2_ER 32

#define INT_PRIO_QSPI3_TX 33
#define INT_PRIO_QSPI3_RX 34
#define INT_PRIO_QSPI3_ER 35

/******************************************************************************/
/*----------------------------------枚举定义----------------------------------*/
/******************************************************************************/

/*
 * \brief 极性与相位
 */
typedef enum
{
    CPOL_0_CPHA_0,
    CPOL_0_CPHA_1,
    CPOL_1_CPHA_0,
    CPOL_1_CPHA_1,
}hsic_qspi_mode_t;

/******************************************************************************/
/*--------------------------------内联函数声明--------------------------------*/
/******************************************************************************/

/** \brief SPI数据传输
 * \param spich SPI设备配置结构体指针
 * \param ptxdata 发送的数据，传入NULL使mosi空闲，只读
 * \param prxdata 接收的数据，传入NULL忽略miso，只写
 * \para count 数据量
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_hwSPIExchange(&dev,NULL,NULL,1);
 * \endcode
 *
 */
static inline void Hsic_hwSPIExchange(IfxQspi_SpiMaster_Channel* spich, uint8* ptxdata, uint8* prxdata, Ifx_SizeT count);

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief SPI设备初始化
 * \param miso 主机输入从机输出
 * \param mosi 主机输出从机输入
 * \param sclk 主机时钟输出
 * \para cs 主机片选输出
 * \para baudrate 波特率
 * \para srctos 中断响应核
 * \para mode 极性与相位
 * \return IfxQspi_SpiMaster_Channel SPI设备结构体，若为空则初始化出现错误
 *
 * Coding example:
 * \code
 *    IfxQspi_SpiMaster_Channel spi = Hsic_hwSPIInit(IfxQspi0_MRSTA_P20_12_IN,IfxQspi0_MTSR_P20_14_OUT,IfxQspi0_SCLK_P20_11_OUT,
 *          IfxQspi0_SLSO0_P20_8_OUT,1000,SRC_CPU0,CPOL_0_CPHA_0);
 * \endcode
 *
 */
IfxQspi_SpiMaster_Channel Hsic_hwSPIInit(IfxQspi_Mrst_In miso, IfxQspi_Mtsr_Out mosi, IfxQspi_Sclk_Out sclk, IfxQspi_Slso_Out cs,
        uint32 baudrate, hsic_srctos_t srctos, hsic_qspi_mode_t mode);

/******************************************************************************/
/*--------------------------------内联函数定义--------------------------------*/
/******************************************************************************/

static inline void Hsic_hwSPIExchange(IfxQspi_SpiMaster_Channel* spich, uint8* ptxdata, uint8* prxdata, Ifx_SizeT count)
{
    while(IfxQspi_SpiMaster_exchange(spich,ptxdata,prxdata,count)!=SpiIf_Status_ok);
}

#endif /* SMARTCAR_HSIC_HWSPI_H_ */
