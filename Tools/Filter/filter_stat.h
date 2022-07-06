/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-26 17:01:32
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-26 19:29:24
 * @FilePath: \filter\include\filter_stat.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _FILTER_STAT_H_
#define _FILTER_STAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>

typedef struct filter_limit
{
    float upRange;
    float lowRange;
    float upRate;
    float lowRate;
    float lastOutput;
    uint8_t flag;
}filter_limit_t;

/**
 * @description: 
 * @param {filter_limit_t*} ptr
 * @param {float} uprange
 * @param {float} lowrange
 * @param {float} uprate
 * @param {float} lowrate
 * @return {*}
 */
void fl_initLimitFilter(filter_limit_t* ptr,float uprange,float lowrange,float uprate,float lowrate);

/**
 * @description: 
 * @param {filter_limit_t*} ptr
 * @param {float} input
 * @return {*}
 */
float fl_limitFilterUpdate(filter_limit_t* ptr,float input);

typedef struct filter_average
{
    float* datas;
    uint8_t size;
}filter_average_t;

/**
 * @description: 
 * @param {filter_average_t*} ptr
 * @param {uint8_t} size
 * @return {*}
 */
void fl_initAverageFilter(filter_average_t* ptr,uint8_t size);

/**
 * @description: 
 * @param {filter_average_t*} ptr
 * @param {float} input
 * @return {*}
 */
float fl_averageFilterUpdate(filter_average_t* ptr,float input);


#endif