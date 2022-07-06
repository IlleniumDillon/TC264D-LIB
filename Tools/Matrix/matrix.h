/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-18 16:33:30
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-19 09:19:37
 * @FilePath: \matrix\include\matrix.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */


#ifndef _MATRIX_LIB_
#define _MATRIX_LIB_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

//定义计算精度，使用单精度速度会快一点
typedef float DATA_TYPE;

//矩阵数据类型
typedef struct matrix
{
    uint8_t rows;           //行数
    uint8_t cols;           //列数
    DATA_TYPE* elements;    //矩阵元素指针
}matrix_t;

typedef enum mtx_state
{
    MTX_OK,
    MTX_DIMENSION_ERROR,
    MTX_SINGULAR_ERROR
}mtx_state_t;

 /**
 * @brief		定义新矩阵
 * @details	    利用已有一维数组定义矩阵，或定义新矩阵 
 * @param[in]	ROWS 定义矩阵行数
 * @param[in]	COLS 定义矩阵列数
 * @param[in]	NAME 为矩阵命名,类型为matrix_t
 * @param[in]	INITVALUE 初始化数组，如不进行初始化用NULL占位
 * @param[out]	无
 * @retval		无
 */
#define CREATE_NEW_MARTRIX(ROWS,COLS,NAME,INITVALUE)\
matrix_t NAME;\
DATA_TYPE val##NAME##[(ROWS)*(COLS)];\
NAME.rows = (ROWS);\
NAME.cols = (COLS);\
NAME.elements = &val##NAME[0];\
if(INITVALUE!=NULL) mtx_setMatrix(INITVALUE,&(NAME));
 /**
 * @brief		动态定义新矩阵
 * @details	    利用已有一维数组定义矩阵，或定义新矩阵 
 * @param[in]	ROWS 定义矩阵行数
 * @param[in]	COLS 定义矩阵列数
 * @param[in]	NAME 为矩阵命名,类型为matrix_t*
 * @param[in]	INITVALUE 初始化数组，如不进行初始化用NULL占位
 * @param[out]	无
 * @retval		无
 */
#define MALLOC_NEW_MARTRIX(ROWS,COLS,NAME,INITVALUE)\
matrix_t* NAME = (matrix_t*)malloc(sizeof(matrix_t));\
NAME->rows = (ROWS);\
NAME->cols = (COLS);\
NAME->elements = (DATA_TYPE*)malloc(sizeof(DATA_TYPE)*(ROWS)*(COLS));\
if(INITVALUE!=NULL) mtx_setMatrix(INITVALUE,NAME);

 /**
 * @brief		释放动态申请矩阵的内存空间
 * @details	     
 * @param[in]	NAME 矩阵指针名,类型为matrix_t*
 * @param[out]	无
 * @retval		无
 */
#define DELETE_MARTRIX(NAME)\
free(NAME->elements);\
free(NAME);

 /**
 * @brief		矩阵赋值
 * @details	    利用已有一维数组对矩阵进行赋值 
 * @param[in]	data_ptr 数据源数组首地址
 * @param[in]	matrix 目标矩阵地址
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_setMatrix(DATA_TYPE* data_ptr,matrix_t* matrix);

 /**
 * @brief		矩阵加法
 * @details	    矩阵加矩阵，对应项相加 r=a+b;矩阵加标量，r=r.+s
 * @param[in]	scalar 加数(标量)
 * @param[in]	matrixA 加数
 * @param[in]	matrixB 加数
 * @param[out]	matrixR 结果
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_AddMatrix(DATA_TYPE scalar,matrix_t* matrixA,matrix_t* matrixB,matrix_t* matrixR);

 /**
 * @brief		矩阵减法
 * @details	    矩阵加矩阵，对应项相加 r=a-b;矩阵加标量，r=r.+s
 * @param[in]	scalar 加数(标量)
 * @param[in]	matrixA 被减数
 * @param[in]	matrixB 减数
 * @param[out]	matrixR 结果
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_SubMatrix(DATA_TYPE scalar,matrix_t* matrixA,matrix_t* matrixB,matrix_t* matrixR);

/**
 * @brief		矩阵乘法
 * @details	    矩阵乘矩阵 r=a*b;矩阵乘标量，r=r.*s
 * @param[in]	scalar 加数(标量)
 * @param[in]	matrixA 乘数
 * @param[in]	matrixB 乘数
 * @param[out]	matrixR 结果
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_MulMatrix(DATA_TYPE scalar,matrix_t* matrixA,matrix_t* matrixB,matrix_t* matrixR);

/**
 * @brief		方阵行列式(LU分解方法)
 * @details	    LU分解方法计算速度较快，但要求方阵可逆；递归方法更通用
 * @param[in]	matrix 方阵
 * @param[out]	det 结果
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_DeterminantWithLU(matrix_t* matrix,DATA_TYPE* det);

/**
 * @brief		方阵行列式(递归方法)
 * @details	    LU分解方法计算速度较快，但要求方阵可逆；递归方法更通用
 * @param[in]	matrix 方阵
 * @param[out]	det 结果
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_Determinant(matrix_t* matrix,DATA_TYPE* det);
DATA_TYPE _det(matrix_t* matrix);
mtx_state_t _left(matrix_t* src,matrix_t* dst,uint8_t i,uint8_t j);

/**
 * @brief		方阵LU分解
 * @details	    
 * @param[in]	matrix 方阵
 * @param[out]	L 结果
 * @param[out]	U 结果
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_getLU(matrix_t* matrix,matrix_t* L,matrix_t* U);

/**
 * @brief		矩阵转置
 * @details	    
 * @param[in]	src 输入矩阵
 * @param[out]	dst 结果
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_transMatrix(matrix_t* src,matrix_t* dst);

/**
 * @brief		矩阵求逆
 * @details	    
 * @param[in]	src 输入矩阵
 * @param[out]	dst 结果
 * @retval		MTX_OK  成功 
 */
mtx_state_t mtx_invMatrix(matrix_t* src,matrix_t* dst);
mtx_state_t _adjMatrix(matrix_t* src,matrix_t* dst);
mtx_state_t _eyeMatrix(matrix_t* src);

#endif