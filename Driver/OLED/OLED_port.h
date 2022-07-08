/*
 * OLED_ssd1306_port.h
 *
 *  Created on: 2022��7��7��
 *      Author: DELL
 */

#ifndef DRIVER_OLED_OLED_PORT_H_
#define DRIVER_OLED_OLED_PORT_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <Hsic_GPIO.h>
#include <Hsic_HWSPI.h>

/******************************************************************************/
/*-------------------------------------��-------------------------------------*/
/******************************************************************************/

/*
 * \brief ʹ�õ�OLED��Ļ����оƬ
 */
#define USE_OLED_SSD1306

/******************************************************************************/
/*--------------------------------�������Ͷ���--------------------------------*/
/******************************************************************************/

/*
 * \brief ����������ţ�Ҫ����ʹ�õĵ�Ƭ���޸�
 */
typedef IfxQspi_Mrst_In miso_t;
typedef IfxQspi_Mtsr_Out mosi_t;
typedef IfxQspi_Sclk_Out sclk_t;
typedef IfxQspi_Slso_Out cs_t;
typedef IfxPort_Pin res_t;
typedef IfxPort_Pin dc_t;

/*
 * \brief SPI�豸�ṹ�壬Ҫ����ʹ�õĵ�Ƭ���޸�
 */
typedef IfxQspi_SpiMaster_Channel userData_t;

/*
 * \brief OLED����
 */
typedef struct
{
    miso_t miso;
    mosi_t mosi;
    sclk_t sclk;
    cs_t cs;
    res_t res;
    dc_t dc;
    userData_t userdata;
}oled_pin_t;

/*
 * \brief OLED���ų�ʼ������ָ��
 */
typedef void (*pin_init_f)(oled_pin_t* pin);

/*
 * \brief OLED���Ų�������ָ��
 */
typedef void (*res_write_f)(oled_pin_t pin, uint8 level);
typedef void (*dc_write_f)(oled_pin_t pin, uint8 level);
typedef void (*spi_write_f)(oled_pin_t pin, uint8* data);

/*
 * \brief OLEDӲ���ӿ�
 */
typedef struct
{
    oled_pin_t pin;
    pin_init_f pin_init;
    res_write_f res_write;
    dc_write_f dc_write;
    spi_write_f spi_write;

}oled_hardware_interface_t;

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief OLEDӲ���ӿڳ�ʼ��
 * \param interface OLEDӲ���ӿڽṹ��ָ��
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_hardwareInterfaceInit(interface);
 * \endcode
 *
 */
void OLED_hardwareInterfaceInit(oled_hardware_interface_t* interface);

/******************************************************************************/
/*-------------------------------�Զ��庯������-------------------------------*/
/******************************************************************************/

void USER_pinInit(oled_pin_t* pin);

void USER_resWrite(oled_pin_t pin, uint8 level);

void USER_dcWrite(oled_pin_t pin, uint8 level);

void USER_spiWrite(oled_pin_t pin, uint8* data);

#endif /* DRIVER_OLED_OLED_PORT_H_ */
