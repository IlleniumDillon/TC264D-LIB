/*
 * Hsic_ENC.h
 *
 *  Created on: 2022年7月5日
 *      Author: DELL
 */

#ifndef SMARTCAR_HSIC_ENC_H_
#define SMARTCAR_HSIC_ENC_H_

/******************************************************************************/
/*----------------------------------包含文件----------------------------------*/
/******************************************************************************/

#include <IfxGpt12_IncrEnc.h>
#include <IfxGpt12_PinMap.h>
#include <Hsic_common.h>

/******************************************************************************/
/*--------------------------------数据类型定义--------------------------------*/
/******************************************************************************/

/*
 * \brief 编码器数据
 */
typedef struct
{
    float32 speed;
    sint32 rawPosition;
    IfxStdIf_Pos_Dir direction;
}hsic_enc_data_t;

/******************************************************************************/
/*--------------------------------全局函数声明--------------------------------*/
/******************************************************************************/

/** \brief 初始化编码器引脚
 * \param a A相引脚
 * \param b B相引脚
 * \param z Z相引脚（不用填NULL）
 * \param resolution 编码器线数
 * \param sampletime 采样周期
 * \param reverse 是否反转
 * \return 返回HSIC_OK表明初始化成功
 *
 * Coding example:
 * \code
 *    Hsic_encInit(IfxGpt120_T2INA_P00_7_IN,IfxGpt120_T2EUDA_P00_8_IN,IfxGpt120_T2INA_P00_7_IN,4096,0.005,FALSE);
 * \endcode
 *
 */
hsic_err_t Hsic_encInit(IfxGpt12_TxIn_In a, IfxGpt12_TxEud_In b, IfxGpt12_TxIn_In z, uint32 resolution, float sampletime, boolean reverse);

/** \brief 获得编码器信息
 * \param data 编码器数据结构体
 * \param a A相引脚
 * \return void
 *
 * Coding example:
 * \code
 *    Hsic_encDataUpdate(&data,IfxGpt120_T2INA_P00_7_IN);
 * \endcode
 *
 */
void Hsic_encDataUpdate(hsic_enc_data_t* data, IfxGpt12_TxIn_In a);

#endif /* SMARTCAR_HSIC_ENC_H_ */
