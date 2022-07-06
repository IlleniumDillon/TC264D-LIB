/*
 * Hsic_isr.h
 *
 *  Created on: 2022��7��1��
 *      Author: DELL
 */

#ifndef HSIC_ISR_H_
#define HSIC_ISR_H_

/******************************************************************************/
/*----------------------------------�����ļ�----------------------------------*/
/******************************************************************************/

#include <Hsic_ERU.h>
#include <Hsic_common.h>

/******************************************************************************/
/*--------------------------------ȫ�ֺ�������--------------------------------*/
/******************************************************************************/

/*******************************�ⲿ�жϷ�����*******************************/
void ERUCH0_P15_4_CallBack(void);
void ERUCH0_P10_7_CallBack(void);
void ERUCH4_P33_7_CallBack(void);
void ERUCH4_P15_5_CallBack(void);
void ERUCH1_P14_3_CallBack(void);
void ERUCH1_P10_8_CallBack(void);
void ERUCH5_P15_8_CallBack(void);
void ERUCH2_P02_1_CallBack(void);
void ERUCH2_P10_2_CallBack(void);
void ERUCH2_P00_4_CallBack(void);
void ERUCH6_P11_10_CallBack(void);
void ERUCH6_P20_0_CallBack(void);
void ERUCH3_P14_1_CallBack(void);
void ERUCH3_P10_3_CallBack(void);
void ERUCH3_P02_0_CallBack(void);
void ERUCH7_P20_9_CallBack(void);
void ERUCH7_P15_1_CallBack(void);

/****************************ϵͳ����ʱ���жϷ�����****************************/
void STMSTM0_SR0_CallBack(void);
void STMSTM0_SR1_CallBack(void);
void STMSTM1_SR0_CallBack(void);
void STMSTM1_SR1_CallBack(void);

/***************************����Ƚ϶�ʱ���жϷ�����***************************/
void CCU60_TM0_CallBack(void);
void CCU60_TM1_CallBack(void);
void CCU61_TM0_CallBack(void);
void CCU61_TM1_CallBack(void);

/********************************�����жϷ�����********************************/
void ASCLIN0_TX_CallBack(void);
void ASCLIN0_RX_CallBack(void);
void ASCLIN0_ER_CallBack(void);
void ASCLIN1_TX_CallBack(void);
void ASCLIN1_RX_CallBack(void);
void ASCLIN1_ER_CallBack(void);
void ASCLIN2_TX_CallBack(void);
void ASCLIN2_RX_CallBack(void);
void ASCLIN2_ER_CallBack(void);
void ASCLIN3_TX_CallBack(void);
void ASCLIN3_RX_CallBack(void);
void ASCLIN3_ER_CallBack(void);

/******************************���������жϷ�����******************************/
void QSPI0_TX_CallBack(void);
void QSPI0_RX_CallBack(void);
void QSPI0_ER_CallBack(void);
void QSPI1_TX_CallBack(void);
void QSPI1_RX_CallBack(void);
void QSPI1_ER_CallBack(void);
void QSPI2_TX_CallBack(void);
void QSPI2_RX_CallBack(void);
void QSPI2_ER_CallBack(void);
void QSPI3_TX_CallBack(void);
void QSPI3_RX_CallBack(void);
void QSPI3_ER_CallBack(void);

#endif /* HSIC_ISR_H_ */
