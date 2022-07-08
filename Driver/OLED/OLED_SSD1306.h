/*
 * OLED_SSD1306.h
 *
 *  Created on: 2022��7��7��
 *      Author: DELL
 */

#ifndef DRIVER_OLED_OLED_SSD1306_H_
#define DRIVER_OLED_OLED_SSD1306_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <OLED_port.h>
#include <OLED_SSD1306_CMD.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef USE_OLED_SSD1306

/******************************************************************************/
/*----------------------------------ö�ٶ���----------------------------------*/
/******************************************************************************/

/*
 * \brief OLEDдģʽ
 */
typedef enum
{
    CMD,
    DATA,
}oled_write_t;

/******************************************************************************/
/*--------------------------------�������Ͷ���--------------------------------*/
/******************************************************************************/

/*
 * \brief OLED�豸�ṹ��
 */
typedef struct
{
   uint8 width;
   uint8 height;
   uint8* displayBuffer_0;
   uint8* displayBuffer_1;
   boolean bufferIndx;
   boolean useDualBuffer;
   boolean needDisp;
   oled_hardware_interface_t interface;
}oled_t;

/******************************************************************************/
/*----------------------------------�ⲿ����----------------------------------*/
/******************************************************************************/

/*
 * \brief OLED�豸
 */
extern oled_t oled_dev;

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/** \brief OLED��ʼ��
 * \param miso miso����
 * \param mosi mosi����
 * \param sclk sclk����
 * \param cs cs����
 * \param res res����
 * \param dc dc����
 * \param useDualBuffer �Ƿ�ʹ���Դ�
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_init(IfxQspi2_MRSTA_P15_4_IN,IfxQspi2_MTSR_P15_5_OUT,IfxQspi2_SCLK_P15_3_OUT,IfxQspi2_SLSO0_P15_2_OUT,IfxPort_P15_1,IfxPort_P15_0,TRUE);
 * \endcode
 *
 */
void OLED_init(miso_t miso, mosi_t mosi, sclk_t sclk, cs_t cs, res_t res, dc_t dc, boolean useDualBuffer);

/** \brief OLEDд��
 * \param type ���������
 * \param data ����
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_write(CMD,0X20);
 * \endcode
 *
 */
void OLED_write(oled_write_t type, uint8 data);

/** \brief OLEDдȫ��
 * \param data ����(0x00ȫ��0xffȫ��)
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_write(0);
 * \endcode
 *
 */
void OLED_fill(uint8 data);

/** \brief OLED�ƶ����
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_setpos(0,0);
 * \endcode
 *
 */
void OLED_setpos(uint8 x, uint8 y);

/** \brief OLEDд����
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_PutPixel(0,0��0xff);
 * \endcode
 *
 */
void OLED_PutPixel(uint8 x, uint8 y, uint8 data);

/** \brief OLEDд�ַ�
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printfChar(&x,&y,'1');
 * \endcode
 *
 */
void OLED_printfChar(uint8* x, uint8* y, char ch);

/** \brief OLEDд�ַ���
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printfStr(x,y,"hello");
 * \endcode
 *
 */
void OLED_printfStr(uint8 x, uint8 y, const char* format);

/** \brief OLEDд�ַ����Դ�
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printfCharToBuf(&&y,'1');
 * \endcode
 *
 */
void OLED_printfCharToBuf(uint8* x, uint8* y, char ch, uint8* buf);

/** \brief OLEDд�ַ������Դ�
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printfStrToBuf(x,y,"hello");
 * \endcode
 *
 */
void OLED_printfStrToBuf(uint8 x, uint8 y, const char* format);

/** \brief OLED��ʽ�����
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printf(x,y,"hello");
 * \endcode
 *
 */
void OLED_printf(uint8 x, uint8 y, const char* format, ...) __attribute__ ((format (printf, 3, 4)));

/** \brief OLEDˢ��
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printBuf();
 * \endcode
 *
 */
void OLED_printBuf(void);

#endif
#endif /* DRIVER_OLED_OLED_SSD1306_H_ */
