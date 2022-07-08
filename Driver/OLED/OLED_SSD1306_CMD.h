/*
 * OLED_SSD1306_CMD.h
 *
 *  Created on: 2022��7��8��
 *      Author: DELL
 */

#ifndef DRIVER_OLED_OLED_SSD1306_CMD_H_
#define DRIVER_OLED_OLED_SSD1306_CMD_H_

#define SET_LOWER_START_ADDR        (0X00)      //���ֽ����ʹ��(SET_LOWER_START_ADDR | A)����ҳ��ַģʽ����ʼ��ַ��λ��A[0 : F]

#define SET_HIGHER_START_ADDR       (0X10)      //���ֽ����ʹ��(SET_HIGHER_START_ADDR | A)����ҳ��ַģʽ����ʼ��ַ��λ��A[0 : F]

#define SET_MEMORY_ADDRESS_MODE     (0X20)      //˫�ֽ���������ڴ��ַģʽ
    #define SET_PAGE_MODE           (0X10)      //ҳ��ַģʽ
    #define SET_HORIZON_MODE        (0X00)      //ˮƽ��ַģʽ
    #define DET_VERTICAL_MODE       (0X01)      //��ֱ��ַģʽ

#define SET_COL_ADDRESS             (0X21)      //˫�ֽ���������е�ַ

#define SET_PAGE_ADDRESS            (0X22)      //˫�ֽ��������ҳ��ַ

#define SET_DISPLAY_START_LINE      (0X40)      //˫�ֽ����������Ļ��ʼ��[0 : 63]

#define SET_CONTRAST_CONTROL        (0X81)      //˫�ֽ�������öԱȶ�[0 : FF]

#define SET_SEGMENT_REMAP_0         (0XA0)      //���ֽ�������ö���ӳ��
#define SET_SEGMENT_REMAP_127       (0XA1)

#define SET_ENTIRE_DISPLAY_ON       (0XA4)      //���ֽ����ȫ������
#define SET_ENTIRE_DISPLAY_OFF      (0XA5)

#define SET_NORMAL_DISPLAY          (0XA6)      //���ֽ������������/��ת��ʾ
#define SET_REVERSE_DISPLAY         (0XA7)

#define SET_MULTIPLEX_RATIO         (0XA8)      //˫�ֽ�������ø�����[16 : 63]

#define SET_SLEEP_MODE              (0XAE)      //���ֽ����������Ļ����/�ر�
#define SET_WAKE_MODE               (0XAF)

#define SET_PAGE_START_ADDR         (0XB0)      //˫�ֽ����ҳ��ַģʽ������ҳ��ʼ��ַ[0 : 7]

#define SET_OUTPUT_DIRECTION_0      (0XC0)      //���ֽ�������������ɨ�跽��
#define SET_OUTPUT_DIRECTION_1      (0XC8)

#define SET_DISPLAY_OFFSET          (0XD3)      //˫�ֽ����������ʾƫ��

#define SET_FREQUENCY               (0XD5)      //˫�ֽ����������ʾʱ�ӷ�Ƶֵ/��Ƶ��

#define SET_PRECHARGE_PERIOD        (0XD9)      //˫�ֽ��������Ԥ�������

#define SET_HARDWARE_CONF           (0XDA)      //˫�ֽ��������������Ӳ������

#define SET_VCOMH_DESELECT_LEVEL    (0XDB)      //˫�ֽ��������VCOMH��ѹֵ

#define NOP                         (0XE3)      //��ָ��

#endif /* DRIVER_OLED_OLED_SSD1306_CMD_H_ */
