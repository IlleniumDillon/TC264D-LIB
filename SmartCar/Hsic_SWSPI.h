/*
 * Hsic_SWSPI.h
 *
 *  Created on: 2022��7��5��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_SWSPI_H_
#define SMARTCAR_HSIC_SWSPI_H_

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
/*--------------------------------�������Ͷ���--------------------------------*/
/******************************************************************************/

/*
 * \brief ȷ����������λ�ĺ���ָ��
 */
typedef void (*sclk_active_t)(IfxPort_Pin sclk);
typedef void (*sclk_idle_t)(IfxPort_Pin sclk);
typedef void (*sclk_effectiveedge_t)(IfxPort_Pin sclk, uint32 delaytime);
typedef void (*sclk_ineffectiveedge_t)(IfxPort_Pin sclk, uint32 delaytime);

/*
 * \brief SPI�豸�ṹ��
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
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief SPI�豸��ʼ��
 * \param miso ��������ӻ����
 * \param mosi ��������ӻ�����
 * \param sclk ����ʱ�����
 * \para cs ����Ƭѡ���
 * \para baudrate ������
 * \para mode ��������λ
 * \return hsic_swspi_dev_t SPI�豸�ṹ��
 *
 * Coding example:
 * \code
 *    hsic_swspi_dev_t dev = Hsic_swSPIInit(IfxPort_P20_12,IfxPort_P20_14,IfxPort_P20_11,IfxPort_P20_8,1000000,0);
 * \endcode
 *
 */
hsic_swspi_dev_t Hsic_swSPIInit(IfxPort_Pin miso, IfxPort_Pin mosi, IfxPort_Pin sclk, IfxPort_Pin cs,
        uint32 baudrate,uint8 mode);

/** \brief SPI���ݴ���
 * \param dev SPI�豸���ýṹ��ָ��
 * \param ptxdata ���͵�����
 * \param prxdata ���յ�����
 * \para count ������
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
