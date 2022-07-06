/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-18 16:33:56
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-19 09:19:45
 * @FilePath: \matrix\src\matrix.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "matrix.h"

mtx_state_t mtx_setMatrix(DATA_TYPE* data_ptr,matrix_t* matrix)
{
    uint8_t x = matrix->rows;
    uint8_t y = matrix->cols;
    int t = x*y;
    for(int i=0;i<t;++i) 
    {
        matrix->elements[i] = data_ptr[i];
    }
    return MTX_OK;
}

mtx_state_t mtx_AddMatrix(DATA_TYPE scalar,matrix_t* matrixA,matrix_t* matrixB,matrix_t* matrixR)
{
    if(matrixA->cols!=matrixB->cols)return MTX_DIMENSION_ERROR;
    if(matrixA->rows!=matrixB->rows)return MTX_DIMENSION_ERROR;
    if(matrixA->cols!=matrixR->cols)return MTX_DIMENSION_ERROR;
    if(matrixA->rows!=matrixR->rows)return MTX_DIMENSION_ERROR;
    uint8_t x = matrixA->rows;
    uint8_t y = matrixA->cols;
    int t = x*y;
    for(int i = 0; i < t; ++i) 
    {
        matrixR->elements[i] = matrixA->elements[i] + matrixB->elements[i] + scalar;
    }
    return MTX_OK;
}

mtx_state_t mtx_SubMatrix(DATA_TYPE scalar,matrix_t* matrixA,matrix_t* matrixB,matrix_t* matrixR)
{
    if(matrixA->cols!=matrixB->cols)return MTX_DIMENSION_ERROR;
    if(matrixA->rows!=matrixB->rows)return MTX_DIMENSION_ERROR;
    if(matrixA->cols!=matrixR->cols)return MTX_DIMENSION_ERROR;
    if(matrixA->rows!=matrixR->rows)return MTX_DIMENSION_ERROR;
    uint8_t x = matrixA->rows;
    uint8_t y = matrixA->cols;
    int t = x*y;
    for(int i=0;i<t;++i) 
    {
        matrixR->elements[i] = matrixA->elements[i] - matrixB->elements[i] + scalar;
    }
    return MTX_OK;
}

mtx_state_t mtx_MulMatrix(DATA_TYPE scalar,matrix_t* matrixA,matrix_t* matrixB,matrix_t* matrixR)
{
    if(matrixA->cols!=matrixB->rows)return MTX_DIMENSION_ERROR;
    if(matrixB->cols!=matrixR->cols)return MTX_DIMENSION_ERROR;
    if(matrixA->rows!=matrixR->rows)return MTX_DIMENSION_ERROR;
    uint8_t x = matrixR->rows;
    uint8_t y = matrixR->cols;
    uint8_t z = matrixA->cols;
    for(int i = 0; i < x; ++i)
    {
        for(int j = 0; j < y; ++j)
        {
            float temp = 0;
            for(int k = 0; k < z; ++k)
            {
                temp += matrixA->elements[x*i+k] * matrixB->elements[y*k+j];
            }
            matrixR->elements[i*y+j] = temp * scalar;
        }
    }
    return MTX_OK;
}

mtx_state_t mtx_DeterminantWithLU(matrix_t* matrix,DATA_TYPE* det)
{
    if(matrix->cols!=matrix->rows)return MTX_DIMENSION_ERROR;
    if(matrix->cols==1)*det = matrix->elements[0];
    else if(matrix->cols==2)*det = matrix->elements[0]*matrix->elements[3]-matrix->elements[1]*matrix->elements[2];
    else if(matrix->cols > 2)
    {
        uint8_t n = matrix->cols;
        MALLOC_NEW_MARTRIX(n,n,L,NULL);
        MALLOC_NEW_MARTRIX(n,n,U,NULL);
        mtx_getLU(matrix,L,U);
        DATA_TYPE s = 1;
        for(int i = 0;i<n;i++)
        {
            s *= U->elements[i*n+i];
        }
        *det = s; 
        DELETE_MARTRIX(L);
        DELETE_MARTRIX(U);
    }
    else return MTX_DIMENSION_ERROR;
    return MTX_OK;

}

mtx_state_t mtx_Determinant(matrix_t* matrix,DATA_TYPE* det)
{
    if(matrix->cols!=matrix->rows)return MTX_DIMENSION_ERROR;
    *det = _det(matrix);
    return MTX_OK;
}

DATA_TYPE _det(matrix_t* matrix)
{
    if(matrix->cols==1)return matrix->elements[0];
    else if(matrix->cols==2)return matrix->elements[0]*matrix->elements[3]-matrix->elements[1]*matrix->elements[2];
    DATA_TYPE sum = 0, temp = 0;
    for(uint8_t j = 0; j < matrix->cols; j++)
    {
        MALLOC_NEW_MARTRIX((matrix->cols-1),(matrix->cols-1),left,NULL);
        _left(matrix,left,0,j);
        temp = _det(left);
        sum += (DATA_TYPE)pow(-1,j+2)*(DATA_TYPE)matrix->elements[j]*temp;
        DELETE_MARTRIX(left);
    }
    return sum;
}

mtx_state_t _left(matrix_t* src,matrix_t* dst,uint8_t i,uint8_t j)
{
    int index = 0;
    int index_src = 0;
    uint8_t x =src->rows;
    uint8_t y =src->cols;
    for(uint8_t kk=0;kk<x;++kk) 
    {
        for(uint8_t ww=0;ww<y;++ww) 
        {
            if(!(kk==i||ww==j)) 
            {
                dst->elements[index] = src->elements[index_src];
                index++;
            }
            index_src++;
        }
    }
    return MTX_OK;
}

mtx_state_t mtx_getLU(matrix_t* matrix,matrix_t* L,matrix_t* U)
{
    if(matrix->cols!=matrix->rows)return MTX_DIMENSION_ERROR;
    if(L->cols!=L->rows)return MTX_DIMENSION_ERROR;
    if(U->cols!=U->rows)return MTX_DIMENSION_ERROR;
    if(matrix->cols!=L->cols||matrix->cols!=U->cols)return MTX_DIMENSION_ERROR;
    uint8_t n = matrix->rows;
    memset(L->elements,0,sizeof(DATA_TYPE)*n*n);
    memset(U->elements,0,sizeof(DATA_TYPE)*n*n);
    DATA_TYPE s = 0;
    for(int i = 0; i < n; i++) 
    {
        L->elements[i*n+i] = 1.0;
    }
    for(int i=0;i<n;i++) 
    {
        for(int j=i;j<n;j++) 
        {
            s = 0.0;
            for(int k=0;k<i;++k) 
            {
                s+=L->elements[i*n+k]*U->elements[k*n+j];
            }
            U->elements[i*n+j]= matrix->elements[i*n+j] - s; 
        }
        for (int j = i + 1;j < n;j++) 
        {
            s = 0.0;
            for (int k = 0; k < i; k++)
            {
                s += L->elements[j*n+k] * U->elements[k*n+i];
            }
            L->elements[j*n+i] = (matrix->elements[j*n+i] - s) / U->elements[i*n+i];      //按列计算l值
        }
    }
    return MTX_OK;
}

mtx_state_t mtx_transMatrix(matrix_t* src,matrix_t* dst)
{
    if(src->cols!=dst->rows||src->rows!=dst->cols)return MTX_DIMENSION_ERROR;
    uint8_t x = src->rows;
    uint8_t y = src->cols;
    //int n = x*y;
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            dst->elements[j*x+i] = src->elements[i*y+j];
        }
    }
    return MTX_OK;
}

mtx_state_t mtx_invMatrix(matrix_t* src,matrix_t* dst)
{
    DATA_TYPE det;
    if(mtx_Determinant(src,&det)!=MTX_OK)return MTX_DIMENSION_ERROR;
    if(fabs(det)<1e-20)return MTX_SINGULAR_ERROR;
    uint8_t n = src->cols;
    MALLOC_NEW_MARTRIX(n,n,adj,NULL);
    MALLOC_NEW_MARTRIX(n,n,eye,NULL);
    _adjMatrix(src,adj);
    _eyeMatrix(eye);
    mtx_MulMatrix((DATA_TYPE)1.0/det,adj,eye,dst);
    DELETE_MARTRIX(adj);
    DELETE_MARTRIX(eye);
    return MTX_OK;
}

mtx_state_t _adjMatrix(matrix_t* src,matrix_t* dst)
{
    uint8_t n = src->cols;
    MALLOC_NEW_MARTRIX(n,n,Tadj,NULL);
    for(uint8_t i = 0; i < n; i++)
    {
        for(uint8_t j = 0; j < n; j++)
        {
            MALLOC_NEW_MARTRIX(n-1,n-1,left,NULL);
            _left(src,left,i,j);
            Tadj->elements[i*n+j] = (DATA_TYPE)pow(-1,i+j+2)*(DATA_TYPE)_det(left);
            DELETE_MARTRIX(left);
        }
    }
    mtx_transMatrix(Tadj,dst);
    DELETE_MARTRIX(Tadj);
    return MTX_OK;
}

mtx_state_t _eyeMatrix(matrix_t* src)
{
    uint8_t n = src->cols;
    memset(src->elements,0,sizeof(DATA_TYPE)*n*n);
    for(int i = 0; i < n; i++)
    {
        src->elements[i*n+i] = 1;
    }
    return MTX_OK;
}
