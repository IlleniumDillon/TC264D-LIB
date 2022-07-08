/*
 * OLED_ssd1306_port.h
 *
 *  Created on: 2022年7月7日
 *      Author: DELL
 */

#ifndef DRIVER_OLED_OLED_PORT_H_
#define DRIVER_OLED_OLED_PORT_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <Hsic_GPIO.h>
#include <Hsic_HWSPI.h>

/******************************************************************************/
/*-------------------------------------宏-------------------------------------*/
/******************************************************************************/

/*
 * \brief 使用的OLED屏幕驱动芯片
 */
#define USE_OLED_SSD1306

/******************************************************************************/
/*--------------------------------数据类型定义--------------------------------*/
/******************************************************************************/

/*
 * \brief 定义输出引脚，要根据使用的单片机修改
 */
typedef IfxQspi_Mrst_In miso_t;
typedef IfxQspi_Mtsr_Out mosi_t;
typedef IfxQspi_Sclk_Out sclk_t;
typedef IfxQspi_Slso_Out cs_t;
typedef IfxPort_Pin res_t;
typedef IfxPort_Pin dc_t;

/*
 * \brief SPI设备结构体，要根据使用的单片机修改
 */
typedef IfxQspi_SpiMaster_Channel userData_t;

/*
 * \brief OLED引脚
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
 * \brief OLED引脚初始化函数指针
 */
typedef void (*pin_init_f)(oled_pin_t* pin);

/*
 * \brief OLED引脚操作函数指针
 */
typedef void (*res_write_f)(oled_pin_t pin, uint8 level);
typedef void (*dc_write_f)(oled_pin_t pin, uint8 level);
typedef void (*spi_write_f)(oled_pin_t pin, uint8* data);

/*
 * \brief OLED硬件接口
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
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief OLED硬件接口初始化
 * \param interface OLED硬件接口结构体指针
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
/*-------------------------------自定义函数声明-------------------------------*/
/******************************************************************************/

void USER_pinInit(oled_pin_t* pin);

void USER_resWrite(oled_pin_t pin, uint8 level);

void USER_dcWrite(oled_pin_t pin, uint8 level);

void USER_spiWrite(oled_pin_t pin, uint8* data);

#endif /* DRIVER_OLED_OLED_PORT_H_ */
