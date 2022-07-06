/*
 * Hsic_UART.h
 *
 *  Created on: 2022��7��3��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_UART_H_
#define SMARTCAR_HSIC_UART_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxAsclin_Asc.h>
#include <Hsic_common.h>
#include <IfxAsclin_PinMap.h>
#include <Hsic_isr.h>

/******************************************************************************/
/*-------------------------------------��-------------------------------------*/
/******************************************************************************/

/*
 * \brief ���ڻ�������С
 */
#define ASC_TX_BUFFER_SIZE 64
#define ASC_RX_BUFFER_SIZE 64

/*
 * \brief �����ж���Ӧ�˺����ȼ�
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
/*----------------------------------�ⲿ����----------------------------------*/
/******************************************************************************/

/*
 * \brief ��������
 */
extern IfxAsclin_Asc asc[4];

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

/** \brief ����д
 * \param pdata ����ָ��
 * \param size ������
 * \para ascnum ����ģ���
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_uartWrite(&data,1,0);
 * \endcode
 *
 */
static inline void Hsic_uartWrite(uint8* pdata, Ifx_SizeT size, uint8 ascnum);

/** \brief ���ڶ�һ���ֽڣ�������
 * \param pdata ����ָ��
 * \para ascnum ����ģ���
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_uartReadOneByte(&data,0);
 * \endcode
 *
 */
static inline void Hsic_uartReadOneByte(uint8* pdata, uint8 ascnum);

/** \brief ���ڶ������������ݣ�������
 * \param pdata ����ָ��
 * \param size ��ȡ������
 * \para ascnum ����ģ���
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
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief ���ڳ�ʼ��
 * \param tx tx����
 * \param rx rx����
 * \para baudrate ������
 * \para srctos �ж���Ӧ��
 * \return ����HSIC_OK������ʼ���ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_uartInit(IfxAsclin0_TX_P14_0_OUT,IfxAsclin0_RXA_P14_1_IN,115200,SRC_CPU0);
 * \endcode
 *
 */
hsic_err_t Hsic_uartInit(IfxAsclin_Tx_Out tx, IfxAsclin_Rx_In rx, uint32 baudrate, hsic_srctos_t srctos);

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
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
