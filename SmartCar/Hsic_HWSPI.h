/*
 * Hsic_HWSPI.h
 *
 *  Created on: 2022��7��4��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_HWSPI_H_
#define SMARTCAR_HSIC_HWSPI_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxQspi_SpiMaster.h>
#include <IfxQspi_PinMap.h>
#include <Hsic_common.h>
#include <Hsic_isr.h>
#include <string.h>

/******************************************************************************/
/*-------------------------------------��-------------------------------------*/
/******************************************************************************/

/*
 * \brief SPI�ж����ȼ�
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
/*----------------------------------ö�ٶ���----------------------------------*/
/******************************************************************************/

/*
 * \brief ��������λ
 */
typedef enum
{
    CPOL_0_CPHA_0,
    CPOL_0_CPHA_1,
    CPOL_1_CPHA_0,
    CPOL_1_CPHA_1,
}hsic_qspi_mode_t;

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

/** \brief SPI���ݴ���
 * \param spich SPI�豸���ýṹ��ָ��
 * \param ptxdata ���͵����ݣ�����NULLʹmosi���У�ֻ��
 * \param prxdata ���յ����ݣ�����NULL����miso��ֻд
 * \para count ������
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
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief SPI�豸��ʼ��
 * \param miso ��������ӻ����
 * \param mosi ��������ӻ�����
 * \param sclk ����ʱ�����
 * \para cs ����Ƭѡ���
 * \para baudrate ������
 * \para srctos �ж���Ӧ��
 * \para mode ��������λ
 * \return IfxQspi_SpiMaster_Channel SPI�豸�ṹ�壬��Ϊ�����ʼ�����ִ���
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
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

static inline void Hsic_hwSPIExchange(IfxQspi_SpiMaster_Channel* spich, uint8* ptxdata, uint8* prxdata, Ifx_SizeT count)
{
    while(IfxQspi_SpiMaster_exchange(spich,ptxdata,prxdata,count)!=SpiIf_Status_ok);
}

#endif /* SMARTCAR_HSIC_HWSPI_H_ */
