/*
 * Hsic_UART.h
 *
 *  Created on: 2022年7月3日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_UART_H_
#define SMARTCAR_HSIC_UART_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxAsclin_Asc.h>
#include <Hsic_common.h>
#include <IfxAsclin_PinMap.h>
#include <Hsic_isr.h>

/******************************************************************************/
/*-------------------------------------宏-------------------------------------*/
/******************************************************************************/

/*
 * \brief 串口缓冲区大小
 */
#define ASC_TX_BUFFER_SIZE 64
#define ASC_RX_BUFFER_SIZE 64

/*
 * \brief 串口中断响应核和优先级
 */
#define ASCLIN0_INT_SERVICE  SRC_CPU0
#define ASCLIN0_TX_INT_PRIO  1
#define ASCLIN0_RX_INT_PRIO  2
#define ASCLIN0_ER_INT_PRIO  3

#define ASCLIN1_INT_SERVICE  SRC_CPU0
#define ASCLIN1_TX_INT_PRIO  4
#define ASCLIN1_RX_INT_PRIO  5
#define ASCLIN1_ER_INT_PRIO  6

#define ASCLIN2_INT_SERVICE  SRC_CPU0
#define ASCLIN2_TX_INT_PRIO  7
#define ASCLIN2_RX_INT_PRIO  8
#define ASCLIN2_ER_INT_PRIO  9

#define ASCLIN3_INT_SERVICE  SRC_CPU0
#define ASCLIN3_TX_INT_PRIO  10
#define ASCLIN3_RX_INT_PRIO  11
#define ASCLIN3_ER_INT_PRIO  12

/******************************************************************************/
/*----------------------------------外部变量----------------------------------*/
/******************************************************************************/

/*
 * \brief 串口驱动
 */
extern IfxAsclin_Asc asc[4];

/******************************************************************************/
/*--------------------------------内联函数声明--------------------------------*/
/******************************************************************************/

/** \brief 串口写
 * \param pdata 数据指针
 * \param size 数据量
 * \para ascnum 串口模块号
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_uartWrite(&data,1,0);
 * \endcode
 *
 */
static inline void Hsic_uartWrite(uint8* pdata, Ifx_SizeT size, uint8 ascnum);

/** \brief 串口读一个字节（阻塞）
 * \param pdata 数据指针
 * \para ascnum 串口模块号
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_uartReadOneByte(&data,0);
 * \endcode
 *
 */
static inline void Hsic_uartReadOneByte(uint8* pdata, uint8 ascnum);

/** \brief 串口读缓存所有数据（阻塞）
 * \param pdata 数据指针
 * \param size 读取数据量
 * \para ascnum 串口模块号
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_uartReadALL(&data,&size,0);
 * \endcode
 *
 */
static inline void Hsic_uartReadALL(uint8* pdata, Ifx_SizeT* size, uint8 ascnum);

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief 串口初始化
 * \param tx tx引脚
 * \param rx rx引脚
 * \para baudrate 波特率
 * \para srctos 中断响应核
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_uartInit(IfxAsclin0_TX_P14_0_OUT,IfxAsclin0_RXA_P14_1_IN,115200,SRC_CPU0);
 * \endcode
 *
 */
hsic_err_t Hsic_uartInit(IfxAsclin_Tx_Out tx, IfxAsclin_Rx_In rx, uint32 baudrate, hsic_srctos_t srctos);

/******************************************************************************/
/*--------------------------------内联函数定义--------------------------------*/
/******************************************************************************/

static inline void Hsic_uartReadOneByte(uint8* pdata, uint8 ascnum)
{
    *pdata = IfxAsclin_Asc_blockingRead(&asc[ascnum]);
}

static inline void Hsic_uartReadAll(uint8* pdata, Ifx_SizeT* psize, uint8 ascnum)
{
    *psize = (Ifx_SizeT)IfxAsclin_Asc_getReadCount(&asc[ascnum]);
    IfxAsclin_Asc_read(&asc[ascnum], pdata, psize, TIME_INFINITE);
}

static inline void Hsic_uartWrite(uint8* pdata, Ifx_SizeT size, uint8 ascnum)
{
    IfxAsclin_Asc_write(&asc[ascnum], pdata, &size, TIME_INFINITE);
}

#endif /* SMARTCAR_HSIC_UART_H_ */
