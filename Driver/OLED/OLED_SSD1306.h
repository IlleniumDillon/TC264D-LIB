/*
 * OLED_SSD1306.h
 *
 *  Created on: 2022年7月7日
 *      Author: DELL
 */

#ifndef DRIVER_OLED_OLED_SSD1306_H_
#define DRIVER_OLED_OLED_SSD1306_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <OLED_port.h>
#include <OLED_SSD1306_CMD.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef USE_OLED_SSD1306

/******************************************************************************/
/*----------------------------------枚举定义----------------------------------*/
/******************************************************************************/

/*
 * \brief OLED写模式
 */
typedef enum
{
    CMD,
    DATA,
}oled_write_t;

/******************************************************************************/
/*--------------------------------数据类型定义--------------------------------*/
/******************************************************************************/

/*
 * \brief OLED设备结构体
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
/*----------------------------------外部变量----------------------------------*/
/******************************************************************************/

/*
 * \brief OLED设备
 */
extern oled_t oled_dev;

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief OLED初始化
 * \param miso miso引脚
 * \param mosi mosi引脚
 * \param sclk sclk引脚
 * \param cs cs引脚
 * \param res res引脚
 * \param dc dc引脚
 * \param useDualBuffer 是否使用显存
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_init(IfxQspi2_MRSTA_P15_4_IN,IfxQspi2_MTSR_P15_5_OUT,IfxQspi2_SCLK_P15_3_OUT,IfxQspi2_SLSO0_P15_2_OUT,IfxPort_P15_1,IfxPort_P15_0,TRUE);
 * \endcode
 *
 */
void OLED_init(miso_t miso, mosi_t mosi, sclk_t sclk, cs_t cs, res_t res, dc_t dc, boolean useDualBuffer);

/** \brief OLED写入
 * \param type 命令或数据
 * \param data 内容
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_write(CMD,0X20);
 * \endcode
 *
 */
void OLED_write(oled_write_t type, uint8 data);

/** \brief OLED写全屏
 * \param data 内容(0x00全灭，0xff全亮)
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_write(0);
 * \endcode
 *
 */
void OLED_fill(uint8 data);

/** \brief OLED移动光标
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_setpos(0,0);
 * \endcode
 *
 */
void OLED_setpos(uint8 x, uint8 y);

/** \brief OLED写像素
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_PutPixel(0,0，0xff);
 * \endcode
 *
 */
void OLED_PutPixel(uint8 x, uint8 y, uint8 data);

/** \brief OLED写字符
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printfChar(&x,&y,'1');
 * \endcode
 *
 */
void OLED_printfChar(uint8* x, uint8* y, char ch);

/** \brief OLED写字符串
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printfStr(x,y,"hello");
 * \endcode
 *
 */
void OLED_printfStr(uint8 x, uint8 y, const char* format);

/** \brief OLED写字符到显存
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printfCharToBuf(&&y,'1');
 * \endcode
 *
 */
void OLED_printfCharToBuf(uint8* x, uint8* y, char ch, uint8* buf);

/** \brief OLED写字符串到显存
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printfStrToBuf(x,y,"hello");
 * \endcode
 *
 */
void OLED_printfStrToBuf(uint8 x, uint8 y, const char* format);

/** \brief OLED格式化输出
 * \return void
 *
 * Coding example:
 * \code
 *    OLED_printf(x,y,"hello");
 * \endcode
 *
 */
void OLED_printf(uint8 x, uint8 y, const char* format, ...) __attribute__ ((format (printf, 3, 4)));

/** \brief OLED刷新
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
