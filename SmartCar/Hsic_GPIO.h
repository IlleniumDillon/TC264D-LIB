/*
 * Hsic_GPIO.h
 *
 *  Created on: 2022��7��1��
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_GPIO_H_
#define SMARTCAR_HSIC_GPIO_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <IfxPort_PinMap.h>
#include <IfxPort_Io.h>
#include <IfxPort.h>
#include <IfxPort_reg.h>
#include <Hsic_common.h>

/******************************************************************************/
/*----------------------------------ö�ٶ���----------------------------------*/
/******************************************************************************/

/*
 * \brief ͨ��IO�˿ڻ���ַö��
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
 * \brief ͨ��IO����ģʽö��
 */
typedef enum
{
    INPUT_NOPULL = IfxPort_Mode_inputNoPullDevice,          //������������
    INPUT_PULLUP = IfxPort_Mode_inputPullUp,                //��������
    INPUT_PULLDOWN = IfxPort_Mode_inputPullDown,            //��������
    OUTPUT_OPENDRAIN = IfxPort_Mode_outputOpenDrainGeneral, //��©���
    OUTPUT_PUSHPULL = IfxPort_Mode_outputPushPullGeneral,   //�������
}hsic_pinmode_t;

/*
 * \brief ͨ��IO���Ų���ö��
 */
typedef enum
{
    NOTCHANGE = IfxPort_State_notChanged,       //�޲���
    HIGH = IfxPort_State_high,                  //�ø�
    LOW = IfxPort_State_low,                    //�õ�
    TOGGLE = IfxPort_State_toggled,             //��ת
}hsic_pinstate_t;

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
/******************************************************************************/

/** \brief ��ʼ��ָ��ͨ��IO����
 * \param port ���ʶ˿ڵ�ö�ٺ�
 * \param pin ָ��Ҫ��ʼ�������ű��
 * \param mode ָ�����Ź���ģʽ
 * \return ����HSIC_OK������ʼ���ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_gpioInit(P20,9,OUTPUT_PUSHPULL);
 * \endcode
 *
 */
static hsic_err_t Hsic_gpioInit(hsic_port_t port, uint8 pin, hsic_pinmode_t mode);

/** \brief ����ָ��ͨ��IO����
 * \param port ���ʶ˿ڵ�ö�ٺ�
 * \param pin ָ��Ҫ���������ű��
 * \param state ָ�����Ų���
 * \return ����HSIC_OK���������ɹ�
 *
 * Coding example:
 * \code
 *    Hsic_gpioSetState(P20,9,HIGH);
 * \endcode
 *
 */
static hsic_err_t Hsic_gpioSetState(hsic_port_t port, uint8 pin, hsic_pinstate_t state);

/** \brief �����ŵ�ƽ״̬
 * \param port ���ʶ˿ڵ�ö�ٺ�
 * \param pin ָ��Ҫ��ȡ�����ű��
 * \return ����1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ
 *
 * Coding example:
 * \code
 *    Hsic_gpioRead(P20,9);
 * \endcode
 *
 */
static boolean Hsic_gpioRead(hsic_port_t port, uint8 pin);

/******************************************************************************/
/*--------------------------------������������--------------------------------*/
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
