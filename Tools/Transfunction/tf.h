/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-23 18:07:08
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-24 19:46:34
 * @FilePath: \transfunction\include\tf.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _TF_H_
#define _TF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define e 2.71828182846

typedef struct tf_function
{
    float* lastinputs;
    float* inputgain;
    float* lastoutputs;
    float* outputgain;
    uint8_t lastinputsnum;
    uint8_t lastoutputsnum;
}tf_function_t;

/**
 * @description: S域传递函数 分子分母形式
 * @param {tf_function_t*} ptr  传递函数结构体指针
 * @param {float*} num  分子系数
 * @param {uint8_t} num_num 分子系数个数
 * @param {float*} den  分母系数
 * @param {uint8_t} den_num 分母系数个数
 * @param {float} gain  增益
 * @param {float} samptime  采样时间
 * @return {*}
 */
void tf_initSFunction_ND(tf_function_t* ptr,float* num,uint8_t num_num,float* den,uint8_t den_num,float gain,float samptime);

/**
 * @description: S域传递函数 零极点形式
 * @param {tf_function_t*} ptr  传递函数结构体指针
 * @param {float*} zeros    零点
 * @param {uint8_t} zeros_num   零点个数
 * @param {float*} pols 极点
 * @param {uint8_t} pols_num    极点个数
 * @param {float} gain  增益
 * @param {float} samptime  采样时间
 * @return {*}
 */
void tf_initSFunction_ZP(tf_function_t* ptr,float* zeros,uint8_t zeros_num,float* pols,uint8_t pols_num,float gain,float samptime);

/**
 * @description: Z域传递函数 分子分母形式
 * @param {tf_function_t*} ptr 传递函数结构体指针
 * @param {float*} num  分子系数
 * @param {uint8_t} num_num 分子系数个数
 * @param {float*} den  分母系数
 * @param {uint8_t} den_num 分母系数个数
 * @param {float} gain  增益
 * @param {float} samptime  采样时间
 * @return {*}
 */
void tf_initZFunction_ND(tf_function_t* ptr,float* num,uint8_t num_num,float* den,uint8_t den_num,float gain,float samptime);

/**
 * @description: Z域传递函数 零极点形式
 * @param {tf_function_t*} ptr  传递函数结构体指针
 * @param {float*} zeros    零点
 * @param {uint8_t} zeros_num   零点个数
 * @param {float*} pols 极点
 * @param {uint8_t} pols_num    极点个数
 * @param {float} gain  增益
 * @param {float} samptime  采样时间
 * @return {*}
 */
void tf_initZFunction_ZP(tf_function_t* ptr,float* zeros,uint8_t zeros_num,float* pols,uint8_t pols_num,float gain,float samptime);

/**
 * @description: 更新输出
 * @param {tf_function_t*} ptr  传递函数结构体指针
 * @param {float} input 输入
 * @return {*}
 */
float tf_update(tf_function_t* ptr,float input);

/**
 * @description: 删除传递函数
 * @param {tf_function_t*} ptr  传递函数结构体指针
 * @return {*}
 */
void tf_deinit(tf_function_t* ptr);

#endif