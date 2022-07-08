/*
 * OLED_SSD1306_CMD.h
 *
 *  Created on: 2022年7月8日
 *      Author: DELL
 */

#ifndef DRIVER_OLED_OLED_SSD1306_CMD_H_
#define DRIVER_OLED_OLED_SSD1306_CMD_H_

#define SET_LOWER_START_ADDR        (0X00)      //单字节命令，使用(SET_LOWER_START_ADDR | A)配置页地址模式下起始地址低位，A[0 : F]

#define SET_HIGHER_START_ADDR       (0X10)      //单字节命令，使用(SET_HIGHER_START_ADDR | A)配置页地址模式下起始地址高位，A[0 : F]

#define SET_MEMORY_ADDRESS_MODE     (0X20)      //双字节命令，设置内存地址模式
    #define SET_PAGE_MODE           (0X10)      //页地址模式
    #define SET_HORIZON_MODE        (0X00)      //水平地址模式
    #define DET_VERTICAL_MODE       (0X01)      //垂直地址模式

#define SET_COL_ADDRESS             (0X21)      //双字节命令，设置列地址

#define SET_PAGE_ADDRESS            (0X22)      //双字节命令，设置页地址

#define SET_DISPLAY_START_LINE      (0X40)      //双字节命令，设置屏幕起始行[0 : 63]

#define SET_CONTRAST_CONTROL        (0X81)      //双字节命令，设置对比度[0 : FF]

#define SET_SEGMENT_REMAP_0         (0XA0)      //单字节命令，设置段重映射
#define SET_SEGMENT_REMAP_127       (0XA1)

#define SET_ENTIRE_DISPLAY_ON       (0XA4)      //单字节命令，全屏点亮
#define SET_ENTIRE_DISPLAY_OFF      (0XA5)

#define SET_NORMAL_DISPLAY          (0XA6)      //单字节命令，设置正常/反转显示
#define SET_REVERSE_DISPLAY         (0XA7)

#define SET_MULTIPLEX_RATIO         (0XA8)      //双字节命令，设置复用率[16 : 63]

#define SET_SLEEP_MODE              (0XAE)      //单字节命令，设置屏幕开启/关闭
#define SET_WAKE_MODE               (0XAF)

#define SET_PAGE_START_ADDR         (0XB0)      //双字节命令，页地址模式下设置页起始地址[0 : 7]

#define SET_OUTPUT_DIRECTION_0      (0XC0)      //单字节命令，设置列输出扫描方向
#define SET_OUTPUT_DIRECTION_1      (0XC8)

#define SET_DISPLAY_OFFSET          (0XD3)      //双字节命令，设置显示偏移

#define SET_FREQUENCY               (0XD5)      //双字节命令，设置显示时钟分频值/震荡频率

#define SET_PRECHARGE_PERIOD        (0XD9)      //双字节命令，设置预充电周期

#define SET_HARDWARE_CONF           (0XDA)      //双字节命令，设置列引脚硬件配置

#define SET_VCOMH_DESELECT_LEVEL    (0XDB)      //双字节命令，设置VCOMH反压值

#define NOP                         (0XE3)      //空指令

#endif /* DRIVER_OLED_OLED_SSD1306_CMD_H_ */
