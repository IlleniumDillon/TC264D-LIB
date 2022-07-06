/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-24 20:43:44
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-24 22:14:17
 * @FilePath: \filter\include\filter_digital.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _FILTER_DIGITAL_H_
#define _FILTER_DIGITAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>

#include "tf.h"
#include "matrix.h"

typedef tf_function_t filter_t;

typedef struct filterlist
{
    filter_t* filter;
    uint8_t filternum;
    uint8_t size;
}filterlist_t;

/**
 * @description: 
 * @param {filter_t*} ptr
 * @param {float} sampleTime
 * @param {float} w
 * @param {float} k
 * @return {*}
 */
void fl_firstOrderLPFConfig(filter_t* ptr,float sampleTime,float w,float k);

/**
 * @description: 
 * @param {filter_t*} ptr
 * @param {float} sampleTime
 * @param {float} w
 * @param {float} k
 * @return {*}
 */
void fl_firstOrderHPFConfig(filter_t* ptr,float sampleTime,float w,float k);

/**
 * @description: 
 * @param {filter_t*} ptr
 * @param {float} sampleTime
 * @param {float} w
 * @param {float} z
 * @param {float} k
 * @return {*}
 */
void fl_secondOrderLPFConfig(filter_t* ptr,float sampleTime,float w,float z,float k);

/**
 * @description: 
 * @param {filter_t*} ptr
 * @param {float} sampleTime
 * @param {float} w
 * @param {float} z
 * @param {float} k
 * @return {*}
 */
void fl_secondOrderHPFConfig(filter_t* ptr,float sampleTime,float w,float z,float k);

/**
 * @description: 
 * @param {filter_t*} ptr
 * @param {float} sampleTime
 * @param {float} passBand
 * @param {float} stopBand
 * @param {float} passRipple
 * @param {float} stopRipple
 * @param {float} k
 * @return {*}
 */
void fl_butterLPFConfig(filter_t* ptr,float sampleTime,float passBand,float stopBand,float passRipple,float stopRipple,float k);

/**
 * @description: 
 * @param {filterlist_t*} fs
 * @param {uint8_t} num
 * @return {*}
 */
void fl_FilterListInit(filterlist_t* fs,uint8_t num);

/**
 * @description: 
 * @param {filterlist_t*} fs
 * @param {filter_t} filter
 * @return {*}
 */
void fl_FilterConfigsPushback(filterlist_t* fs,filter_t filter);

/**
 * @description: 
 * @param {filterlist_t*} fs
 * @param {int} num
 * @return {*}
 */
void fl_FilterConfigsPushbackList(filterlist_t* fs,int num,...);

/**
 * @description: 
 * @param {filter_t*} filter
 * @param {float} input
 * @return {*}
 */
float fl_FilterUpdate(filter_t* filter,float input);

/**
 * @description: 
 * @param {filterlist_t*} fs
 * @param {float} input
 * @return {*}
 */
float fl_FilterlistUpdate(filterlist_t* fs,float input);

#endif
