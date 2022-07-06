/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-23 18:07:16
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-24 19:46:37
 * @FilePath: \transfunction\src\tf.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "tf.h"

void _tf_getND(float* dst,float* src,uint8_t size)
{
    float* temp = (float*)calloc(size,sizeof(float));
    for(int i = 0; i < size+1; i++)
    {
        dst[i] = 0;
    }
    dst[size-1] = 1;dst[size] = -src[0];
    for(int i = 1; i < size; i++)
    {
        memcpy(temp,&dst[1],size*sizeof(float));
        for(int j = 0; j < size; j++)
        {
            dst[j] = temp[j];
        }
        dst[size] = 0;
        for(int j = 0; j < size; j++)
        {
            temp[j] = temp[j] * (-src[i]);
            dst[j+1] = dst[j+1] + temp[j];
        }
    }
    free(temp);
}

void tf_initSFunction_ND(tf_function_t* ptr,float* num,uint8_t num_num,float* den,uint8_t den_num,float gain,float samptime)
{
    /*ptr->lastinputsnum = den_num;
    ptr->lastoutputsnum = den_num;
    ptr->inputgain = (float*)calloc((den_num),sizeof(float));
    ptr->lastinputs = (float*)calloc((den_num),sizeof(float));
    ptr->lastoutputs = (float*)calloc((den_num),sizeof(float));
    ptr->outputgain = (float*)calloc((den_num),sizeof(float));*/

    float* setnum = (float*)calloc(den_num,sizeof(float));
    float* setden = (float*)calloc(den_num,sizeof(float));

    float* znum = (float*)calloc(den_num,sizeof(float));
    float* zeros = (float*)calloc(den_num-1,sizeof(float));
    for(int i = 0; i < num_num ; i++)
    {
        for(int j = 0; j < i; j++)
        {
            zeros[j] = 1;
        }
        for(int j = i; j < den_num-1; j++)
        {
            zeros[j] = -1;
        }
        _tf_getND(znum,zeros,den_num-1);
        for(int j = 0; j < den_num; j++)
        {
            znum[j] = znum[j]*num[num_num-1-i]*(float)pow((2.0/samptime),i);
            setnum[j] = setnum[j] + znum[j];
        }
        /*for(int j = 0; j < den_num; j++)
        {
            ptr->inputgain[j] = ptr->inputgain[j] * gain;
        }*/
    }
    float* zden = (float*)calloc(den_num,sizeof(float));
    float* pols = (float*)calloc(den_num-1,sizeof(float));
    for(int i = 0; i < den_num ; i++)
    {
        for(int j = 0; j < i; j++)
        {
            pols[j] = 1;
        }
        for(int j = i; j < den_num-1; j++)
        {
            pols[j] = -1;
        }
        _tf_getND(zden,pols,den_num-1);
        for(int j = 0; j < den_num; j++)
        {
            zden[j] = (float)zden[j]*den[den_num-1-i]*(float)pow((2.0/samptime),i);
            setden[j] = setden[j] + zden[j];
        }
    }
    tf_initZFunction_ND(ptr,setnum,den_num,setden,den_num,gain,samptime);
    free(znum);
    free(zeros);
    free(zden);
    free(pols);
    free(setnum);
    free(setden);
}

void tf_initSFunction_ZP(tf_function_t* ptr,float* zeros,uint8_t zeros_num,float* pols,uint8_t pols_num,float gain,float samptime)
{
    /*float* zeros_z = (float*)calloc(pols_num,sizeof(float));
    for(int i = 0; i < zeros_num; i++)
    {
        zeros_z[i] = (float)pow(e,zeros[i]*samptime);
    }
    for(int i = zeros_num; i < pols_num; i++)
    {
        zeros_z[i] = 0;
    }
    float* plos_z = (float*)calloc(pols_num,sizeof(float));
    for(int i = 0; i < pols_num; i++)
    {
        plos_z[i] = (float)pow(e,pols[i]*samptime);
    }
    //TODO:
    tf_initZFunction_ZP(ptr,zeros_z,pols_num,plos_z,pols_num,gain,samptime);
    free(zeros_z);
    free(plos_z);*/
    uint8_t num_num = zeros_num+1;
    uint8_t den_num = pols_num+1;
    float* num = (float*)malloc(num_num*sizeof(float));
    _tf_getND(num,zeros,zeros_num);
    float* den = (float*)malloc(den_num*sizeof(float));
    _tf_getND(den,pols,pols_num);
    tf_initSFunction_ND(ptr,num,num_num,den,den_num,gain,samptime);
    free(num);
    free(den);
}

void tf_initZFunction_ND(tf_function_t* ptr,float* num,uint8_t num_num,float* den,uint8_t den_num,float gain,float samptime)
{
    ptr->lastinputsnum = num_num;
    ptr->lastoutputsnum = den_num-1;
    ptr->inputgain = (float*)malloc(num_num*sizeof(float));
    ptr->lastinputs = (float*)malloc(num_num*sizeof(float));
    ptr->lastoutputs = (float*)malloc((den_num-1)*sizeof(float));
    ptr->outputgain = (float*)malloc((den_num-1)*sizeof(float));
    for(int i = 0; i < num_num; i++)
    {
        ptr->inputgain[i] = gain * num[i] / den[0];
        ptr->lastinputs[i] = 0;
    }
    for(int i = 0; i < den_num-1; i++)
    {
        ptr->outputgain[i] = - den[i+1] / den[0];
        ptr->lastoutputs[i] = 0;
    }
    //ptr->lastoutputs[0] = 0;
}

void tf_initZFunction_ZP(tf_function_t* ptr,float* zeros,uint8_t zeros_num,float* pols,uint8_t pols_num,float gain,float samptime)
{
    uint8_t num_num = zeros_num+1;
    uint8_t den_num = pols_num+1;
    ptr->lastinputsnum = num_num;
    ptr->lastoutputsnum = den_num-1;
    ptr->inputgain = (float*)malloc(num_num*sizeof(float));
    ptr->lastinputs = (float*)malloc(num_num*sizeof(float));
    ptr->lastoutputs = (float*)malloc((den_num-1)*sizeof(float));
    ptr->outputgain = (float*)malloc((den_num-1)*sizeof(float));
    float* num = (float*)malloc(num_num*sizeof(float));
    _tf_getND(num,zeros,zeros_num);
    float* den = (float*)malloc(den_num*sizeof(float));
    _tf_getND(den,pols,pols_num);
    for(int i = 0; i < num_num; i++)
    {
        ptr->inputgain[i] = gain * num[i] / den[0];
        ptr->lastinputs[i] = 0;
    }
    for(int i = 0; i < den_num; i++)
    {
        ptr->outputgain[i] = - den[i+1] / den[0];
        ptr->lastoutputs[i] = 0;
    }
    free(num);
    free(den);
}

float tf_update(tf_function_t* ptr,float input)
{
    for(int i = ptr->lastinputsnum; i > 0; i--)
    {
        ptr->lastinputs[i] = ptr->lastinputs[i-1];
    }
    ptr->lastinputs[0] = input;
    float output = 0;
    for(int i = 0; i < ptr->lastinputsnum; i++)
    {
        output += ptr->inputgain[i] * ptr->lastinputs[i];
    }
    for(int i = 0; i < ptr->lastoutputsnum; i++)
    {
        output += ptr->outputgain[i] * ptr->lastoutputs[i];
    }
    for(int i = ptr->lastoutputsnum; i > 0; i--)
    {
        ptr->lastoutputs[i] = ptr->lastoutputs[i-1];
    }
    ptr->lastoutputs[0] = output;
    return output;
}

void tf_deinit(tf_function_t* ptr)
{
    free(ptr->inputgain);
    free(ptr->lastinputs);
    free(ptr->lastoutputs);
    free(ptr->outputgain);
}
