/*
 * Hsic_GPIO.h
 *
 *  Created on: 2022年7月1日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_GPIO_H_
#define SMARTCAR_HSIC_GPIO_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxPort_PinMap.h>
#include <IfxPort_Io.h>
#include <IfxPort.h>
#include <IfxPort_reg.h>
#include <Hsic_common.h>

/******************************************************************************/
/*----------------------------------枚举定义----------------------------------*/
/******************************************************************************/

/*
 * \brief 通用IO端口基地址枚举
 */
typedef enum
{
    P00 = (int)0xF003A000u,
    P02 = (int)0xF003A200u,
    P10 = (int)0xF003B000u,
    P11 = (int)0xF003B100u,
    P13 = (int)0xF003B300u,
    P14 = (int)0xF003B400u,
    P15 = (int)0xF003B500u,
    P20 = (int)0xF003C000u,
    P21 = (int)0xF003C100u,
    P22 = (int)0xF003C200u,
    P23 = (int)0xF003C300u,
    P33 = (int)0xF003D300u,
}hsic_port_t;

/*
 * \brief 通用IO引脚模式枚举
 */
typedef enum
{
    INPUT_NOPULL = IfxPort_Mode_inputNoPullDevice,          //无上下拉输入
    INPUT_PULLUP = IfxPort_Mode_inputPullUp,                //上拉输入
    INPUT_PULLDOWN = IfxPort_Mode_inputPullDown,            //下拉输入
    OUTPUT_OPENDRAIN = IfxPort_Mode_outputOpenDrainGeneral, //开漏输出
    OUTPUT_PUSHPULL = IfxPort_Mode_outputPushPullGeneral,   //推挽输出
}hsic_pinmode_t;

/*
 * \brief 通用IO引脚操作枚举
 */
typedef enum
{
    NOTCHANGE = IfxPort_State_notChanged,       //无操作
    HIGH = IfxPort_State_high,                  //置高
    LOW = IfxPort_State_low,                    //置低
    TOGGLE = IfxPort_State_toggled,             //翻转
}hsic_pinstate_t;

/******************************************************************************/
/*--------------------------------内联函数声明--------------------------------*/
/******************************************************************************/

/** \brief 初始化指定通用IO引脚
 * \param port 访问端口的枚举号
 * \param pin 指定要初始化的引脚编号
 * \param mode 指定引脚工作模式
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_gpioInit(P20,9,OUTPUT_PUSHPULL);
 * \endcode
 *
 */
static hsic_err_t Hsic_gpioInit(hsic_port_t port, uint8 pin, hsic_pinmode_t mode);

/** \brief 操作指定通用IO引脚
 * \param port 访问端口的枚举号
 * \param pin 指定要操作的引脚编号
 * \param state 指定引脚操作
 * \return 返回HSIC_OK表明操作成功
 *
 * Coding example:
 * \code
 *    Hsic_gpioSetState(P20,9,HIGH);
 * \endcode
 *
 */
static hsic_err_t Hsic_gpioSetState(hsic_port_t port, uint8 pin, hsic_pinstate_t state);

/** \brief 读引脚电平状态
 * \param port 访问端口的枚举号
 * \param pin 指定要读取的引脚编号
 * \return 返回1为高电平，0为低电平
 *
 * Coding example:
 * \code
 *    Hsic_gpioRead(P20,9);
 * \endcode
 *
 */
static boolean Hsic_gpioRead(hsic_port_t port, uint8 pin);

/******************************************************************************/
/*--------------------------------内联函数定义--------------------------------*/
/******************************************************************************/

static inline hsic_err_t Hsic_gpioInit(hsic_port_t port, uint8 pin, hsic_pinmode_t mode)
{
    IfxPort_setPinMode((Ifx_P *)port,pin,(IfxPort_Mode)mode);
    IfxPort_setPinPadDriver((Ifx_P *)port,pin,IfxPort_PadDriver_cmosAutomotiveSpeed1);
    return HSIC_OK;
}

static inline hsic_err_t Hsic_gpioSetState(hsic_port_t port, uint8 pin, hsic_pinstate_t state)
{
    IfxPort_setPinState((Ifx_P *)port,pin,(IfxPort_State)state);
    return HSIC_OK;
}

static inline boolean Hsic_gpioRead(hsic_port_t port, uint8 pin)
{
    return IfxPort_getPinState((Ifx_P *)port, pin);
}
#endif /* SMARTCAR_HSIC_GPIO_H_ */
