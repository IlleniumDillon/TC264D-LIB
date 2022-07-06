/*
 * @Author: IlleniumDillon 147900130@qq.com
 * @Date: 2022-06-26 17:02:09
 * @LastEditors: IlleniumDillon 147900130@qq.com
 * @LastEditTime: 2022-06-26 19:13:11
 * @FilePath: \filter\src\filter_stat.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "filter_stat.h"

void fl_initLimitFilter(filter_limit_t* ptr,float uprange,float lowrange,float uprate,float lowrate)
{
    ptr->lastOutput = 0;
    ptr->upRange = uprange;
    ptr->lowRange = lowrange;
    ptr->upRate = uprate;
    ptr->lowRate = lowrate;
    ptr->flag = 0;
}

float fl_limitFilterUpdate(filter_limit_t* ptr,float input)
{
    if(ptr->flag==0)
    {
        ptr->flag = 1;
        if(input>ptr->upRange)
        {
            ptr->lastOutput = ptr->upRange;
        }
        else if(input<ptr->lowRange)
        {
            ptr->lastOutput = ptr->lowRange;
        }
        else
        {
            ptr->lastOutput = input;
        }
        return ptr->lastOutput;
    }
    else
    {
        float rate = input-ptr->lastOutput;
        if(rate>ptr->upRate)
        {
            rate = ptr->upRate;
        }
        else if(rate<ptr->lowRate)
        {
            rate = ptr->lowRate;
        }
        float temp;
        temp = ptr->lastOutput + rate;
        if(temp>ptr->upRange)
        {
            ptr->lastOutput = ptr->upRange;
        }
        else if(temp<ptr->lowRange)
        {
            ptr->lastOutput = ptr->lowRange;
        }
        else
        {
            ptr->lastOutput = temp;
        }
        return ptr->lastOutput;
    }
}

void fl_initAverageFilter(filter_average_t* ptr,uint8_t size)
{
    ptr->size = size;
    ptr->datas = (float*)calloc(size,sizeof(float));
}

float fl_averageFilterUpdate(filter_average_t* ptr,float input)
{
    float sum = 0;
    for(int i = 1; i < ptr->size; i++)
    {
        sum += ptr->datas[i-1];
        ptr->datas[i-1] = ptr->datas[i];
    }
    sum += input;
    ptr->datas[ptr->size-1] = input;
    return  sum/ptr->size;
}
