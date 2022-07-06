/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-25 21:46:16
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-26 16:25:48
 * @FilePath: \filter\include\filter_kalman.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _FILTER_KALMAN_H_
#define _FILTER_KALMAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>

#include "tf.h"
#include "matrix.h"

typedef struct filter_kalman
{
    matrix_t* A,*B,*H;
    matrix_t* P,*K;
    matrix_t* Xhat;
    matrix_t* Q,*R;
}filter_kalman_t;

/**
 * @description: 
 * @param {filter_kalman_t*} ptr
 * @param {matrix_t*} A
 * @param {matrix_t*} B
 * @param {matrix_t*} H
 * @param {matrix_t*} Q
 * @param {matrix_t*} R
 * @return {*}
 */
void fl_initKalmanFilter(filter_kalman_t* ptr,matrix_t* A,matrix_t* B,matrix_t* H,matrix_t* Q,matrix_t* R);

/**
 * @description: 
 * @param {filter_kalman_t*} ptr
 * @param {matrix_t*} U
 * @param {matrix_t*} Z
 * @return {*}
 */
void fl_kalmanFilterUpdate(filter_kalman_t* ptr,matrix_t* U,matrix_t* Z);

#endif
