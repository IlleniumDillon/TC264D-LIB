/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-25 21:46:27
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-26 16:38:21
 * @FilePath: \filter\src\filter_kalman.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "filter_kalman.h"

void fl_initKalmanFilter(filter_kalman_t* ptr,matrix_t* A,matrix_t* B,matrix_t* H,matrix_t* Q,matrix_t* R)
{
    //MALLOC_NEW_MARTRIX(A->rows,A->cols,temp,A->elements);
    ptr->A = (matrix_t*)calloc(1,sizeof(matrix_t));
    ptr->A->cols = A->cols;
    ptr->A->rows = A->rows;
    ptr->A->elements = (float*)calloc(ptr->A->cols*ptr->A->rows,sizeof(float));
    mtx_setMatrix(A->elements,ptr->A);
    ptr->B = (matrix_t*)calloc(1,sizeof(matrix_t));
    ptr->B->cols = B->cols;
    ptr->B->rows = B->rows;
    ptr->B->elements = (float*)calloc(ptr->B->cols*ptr->B->rows,sizeof(float));
    mtx_setMatrix(B->elements,ptr->B);
    ptr->H = (matrix_t*)calloc(1,sizeof(matrix_t));
    ptr->H->cols = H->cols;
    ptr->H->rows = H->rows;
    ptr->H->elements = (float*)calloc(ptr->H->cols*ptr->H->rows,sizeof(float));
    mtx_setMatrix(H->elements,ptr->H);
    ptr->Q = (matrix_t*)calloc(1,sizeof(matrix_t));
    ptr->Q->cols = Q->cols;
    ptr->Q->rows = Q->rows;
    ptr->Q->elements = (float*)calloc(ptr->Q->cols*ptr->Q->rows,sizeof(float));
    mtx_setMatrix(Q->elements,ptr->Q);
    ptr->R = (matrix_t*)calloc(1,sizeof(matrix_t));
    ptr->R->cols = R->cols;
    ptr->R->rows = R->rows;
    ptr->R->elements = (float*)calloc(ptr->R->cols*ptr->R->rows,sizeof(float));
    mtx_setMatrix(R->elements,ptr->R);

    ptr->K = (matrix_t*)calloc(1,sizeof(matrix_t));
    ptr->K->cols = A->cols;
    ptr->K->rows = A->rows;
    ptr->K->elements = (float*)calloc(ptr->K->cols*ptr->K->rows,sizeof(float));
    _eyeMatrix(ptr->K);
    ptr->P = (matrix_t*)calloc(1,sizeof(matrix_t));
    ptr->P->cols = A->cols;
    ptr->P->rows = A->rows;
    ptr->P->elements = (float*)calloc(ptr->P->cols*ptr->P->rows,sizeof(float));
    ptr->Xhat = (matrix_t*)calloc(1,sizeof(matrix_t));
    ptr->Xhat->cols = 1;
    ptr->Xhat->rows = A->rows;
    ptr->Xhat->elements = (float*)calloc(ptr->Xhat->cols*ptr->Xhat->rows,sizeof(float));
}

void _priEst(matrix_t* Xhat_,matrix_t* A,matrix_t* B,matrix_t* Xhat,matrix_t* U)
{
    MALLOC_NEW_MARTRIX(Xhat_->rows,Xhat_->cols,temp,NULL);
    mtx_MulMatrix(1,A,Xhat,Xhat_);
    mtx_MulMatrix(1,B,U,temp);
    mtx_AddMatrix(0,Xhat_,temp,Xhat_);
    DELETE_MARTRIX(temp);
}

void _priEstErrP(matrix_t* P_,matrix_t* A,matrix_t* P,matrix_t* Q)
{
    MALLOC_NEW_MARTRIX(P->rows,P->cols,temp,NULL);
    MALLOC_NEW_MARTRIX(A->rows,A->cols,AT,NULL);
    mtx_transMatrix(A,AT);
    mtx_MulMatrix(1,A,P,P_);
    mtx_MulMatrix(1,P_,AT,temp);
    mtx_AddMatrix(0,Q,temp,P_);
    DELETE_MARTRIX(temp);
    DELETE_MARTRIX(AT);
}

void _updateKalmanGain(matrix_t* K,matrix_t* P_,matrix_t* H,matrix_t* R)
{
    MALLOC_NEW_MARTRIX(P_->rows,P_->cols,num,NULL);
    MALLOC_NEW_MARTRIX(P_->rows,P_->cols,temp,NULL);
    MALLOC_NEW_MARTRIX(P_->rows,P_->cols,temp2,NULL);
    MALLOC_NEW_MARTRIX(H->rows,H->cols,HT,NULL);
    mtx_transMatrix(H,HT);
    mtx_MulMatrix(1,P_,HT,num);
    mtx_MulMatrix(1,H,P_,temp);
    mtx_MulMatrix(1,temp,HT,temp2);
    mtx_AddMatrix(0,temp2,R,temp2);
    mtx_invMatrix(temp2,temp);
    mtx_MulMatrix(1,num,temp,K);
    DELETE_MARTRIX(num);
    DELETE_MARTRIX(temp);
    DELETE_MARTRIX(temp2);
    DELETE_MARTRIX(HT);
}

void _postEst(matrix_t* Xhat,matrix_t* Xhat_,matrix_t* K,matrix_t* H,matrix_t* Z)
{
    MALLOC_NEW_MARTRIX(H->rows,1,temp,NULL);
    MALLOC_NEW_MARTRIX(H->rows,1,temp2,NULL);
    mtx_MulMatrix(1,H,Xhat_,temp);
    mtx_SubMatrix(0,Z,temp,temp);
    mtx_MulMatrix(1,K,temp,temp2);
    mtx_AddMatrix(0,Xhat_,temp2,Xhat);
    DELETE_MARTRIX(temp2);
    DELETE_MARTRIX(temp);
}

void _updateErrP(matrix_t* P,matrix_t* K,matrix_t* H,matrix_t* P_)
{
    MALLOC_NEW_MARTRIX(P_->rows,P_->cols,eye,NULL);
    MALLOC_NEW_MARTRIX(P_->rows,P_->cols,temp,NULL);
    _eyeMatrix(eye);
    mtx_MulMatrix(1,K,H,temp);
    mtx_SubMatrix(0,eye,temp,temp);
    mtx_MulMatrix(1,temp,P_,P);
    DELETE_MARTRIX(eye);
    DELETE_MARTRIX(temp);
}

void fl_kalmanFilterUpdate(filter_kalman_t* ptr,matrix_t* U,matrix_t* Z)
{
    MALLOC_NEW_MARTRIX(ptr->A->rows,1,Xhat_,NULL);
    MALLOC_NEW_MARTRIX(ptr->A->rows,ptr->A->cols,P_,NULL);
    //先验估计
    _priEst(Xhat_,ptr->A,ptr->B,ptr->Xhat,U);
    //先验误差协方差
    _priEstErrP(P_,ptr->A,ptr->P,ptr->Q);
    //更新卡尔曼系数
    _updateKalmanGain(ptr->K,P_,ptr->H,ptr->R);
    //后验估计
    _postEst(ptr->Xhat,Xhat_,ptr->K,ptr->H,Z);
    //更新误差协方差
    _updateErrP(ptr->P,ptr->K,ptr->H,P_);
    DELETE_MARTRIX(Xhat_);
    DELETE_MARTRIX(P_);
}
