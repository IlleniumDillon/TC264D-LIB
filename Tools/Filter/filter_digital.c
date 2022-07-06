/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-24 20:46:10
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-25 21:18:38
 * @FilePath: \filter\src\filter_digital.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "filter_digital.h"

const float butterValue[10][11] = 
{
    {1,1},
    {1,1.4142136,1},
    {1,2,2,1},
    {1,2.6131259,3.4142136,2.6131259,1},
    {1,3.236068,5.236068,5.236068,3.236068,1},
    {1,3.8637033,7.4641016,9.1416202,7.4641016,3.8637033,1},
    {1,4.4939592,10.0978347,14.5917939,14.5917939,10.0978347,4.4939592,1},
    {1,5.1258309,13.1370712,21.846151,25.6883559,21.846151,13.1370712,5.1258309,1},
    {1,5.7587705,16.5817187,31.1634375,41.9863857,41.9863857,31.1634375,16.5817187,5.7587705,1},
    {1,6.3924532,20.4317291,42.8020611,64.8823963,74.2334292,64.8823963,42.8020611,20.4317291,6.3924532,1}
};

void fl_firstOrderLPFConfig(filter_t* ptr,float sampleTime,float w,float k)
{
    float num[1] = {1};
    float den[2] = {1.0/w,1};
    tf_initSFunction_ND(ptr,num,1,den,2,k,sampleTime);
}

void fl_firstOrderHPFConfig(filter_t* ptr,float sampleTime,float w,float k)
{
    float num[2] = {1.0/w,0};
    float den[2] = {1.1/w,1};
    tf_initSFunction_ND(ptr,num,2,den,2,k,sampleTime);
}

void fl_secondOrderLPFConfig(filter_t* ptr,float sampleTime,float w,float z,float k)
{
    float num[1] = {1};
    float den[3] = {1.0/w/w,2*z/w,1};
    tf_initSFunction_ND(ptr,num,1,den,3,k,sampleTime);
}

void fl_secondOrderHPFConfig(filter_t* ptr,float sampleTime,float w,float z,float k)
{
    float num[3] = {1.0/w/w,2*z/w,0};
    float den[3] = {1.0/w/w,2*z/w,1};
    tf_initSFunction_ND(ptr,num,3,den,3,k,sampleTime);
}

void fl_butterLPFConfig(filter_t* ptr,float sampleTime,float passBand,float stopBand,float passRipple,float stopRipple,float k)
{
    //float fs = 1/sampleTime;
    uint8_t N = (uint8_t)ceil(0.5*log10f(pow(10,0.1*stopRipple-1)/pow(10,0.1*passRipple-1))/log10f(stopBand/passBand));
    float wc = stopBand/pow(pow(10,0.1*stopRipple-1),1/2/(float)N);
    float* num = (float*)calloc(1,sizeof(float));
    float* den = (float*)calloc(N+1,sizeof(float));
    num[0]=pow(wc,N);
    for(int i = 0; i < N+1; i++)
    {
        den[i] = (float)butterValue[N-1][N-i]*(float)pow(wc,i);
    }
    tf_initSFunction_ND(ptr,num,1,den,N+1,k,sampleTime);
    free(num);
    free(den);
}

void fl_FilterListInit(filterlist_t* fs,uint8_t num)
{
    fs->filternum = num;
    fs->size = 0;
    fs->filter = (filter_t*)calloc(num,sizeof(filter_t));
}

void fl_FilterConfigsPushback(filterlist_t* fs,filter_t filter)
{
    if(fs->filternum<=fs->size)
    {
        return;
    }
    else
    {
        fs->size++;
        fs->filter[fs->size-1] = filter;
    }
}

void fl_FilterConfigsPushbackList(filterlist_t* fs,int num,...)
{
    va_list li;
    va_start(li,num);
    for( int i = 0;i< num; ++i )
    {
        fl_FilterConfigsPushback(fs,va_arg(li, filter_t));
    }
    va_end(li);
}

float fl_FilterUpdate(filter_t* filter,float input)
{
    return tf_update(filter,input);
}

float fl_FilterlistUpdate(filterlist_t* fs,float input)
{
    for(int i = 0;i<fs->filternum;i++)
    {
        input = fl_FilterUpdate(&fs->filter[i],input);
    }
    return input;
}
