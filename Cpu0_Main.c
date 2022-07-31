/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include <Hsic_common.h>
#include <Hsic_isr.h>
#include <IfxSrc_cfg.h>
#include "Hsic_GPIO.h"
#include "Hsic_ERU.h"
#include "Hsic_PWM.h"
#include "Hsic_STM.h"
#include "Hsic_UART.h"
#include "Hsic_HWIIC.h"
#include "Hsic_SWIIC.h"
#include "Hsic_HWSPI.h"
#include "Hsic_SWSPI.h"
#include "Hsic_ADC.h"
#include "Hsic_Flash.h"
#include "Hsic_ENC.h"
#include "Hsic_CCU6Timer.h"
#include "Hsic_log.h"
#include <OLED_SSD1306.h>

IfxCpu_syncEvent g_cpuSyncEvent = 0;

int core0_main(void)
{
    IfxCpu_disableInterrupts();
    
    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);
    
    //Hsic_eruPinInit(ERUCH6_P11_10,FALLING,ERU_CH2_CH6_INT_SERVICE,ERU_CH2_CH6_INT_PRIO);

    /*Hsic_gpioInit(P20,9,OUTPUT_PUSHPULL);
    Hsic_gpioSetState(P20,9,HIGH);
    Hsic_gpioInit(P21,4,OUTPUT_PUSHPULL);
    Hsic_gpioSetState(P21,4,HIGH);
    Hsic_gpioInit(P20,8,OUTPUT_PUSHPULL);
    Hsic_gpioSetState(P20,9,HIGH);
    Hsic_gpioInit(P21,5,OUTPUT_PUSHPULL);
    Hsic_gpioSetState(P21,4,HIGH);*/

    //Hsic_pwmInit(IfxGtm_ATOM0_3_TOUT56_P21_5_OUT,1000,0);

    //Hsic_stmCmpIrqInit(STM0,COMPARATOR0,SRC_CPU0,INT_PRIO_CMPSTM0_SR0,INT_MS_CMPSTM0_SR0);
    Hsic_stmTimIrqInit(STM0,COMPARATOR0,SRC_CPU0,INT_PRIO_CMPSTM0_SR0,INT_MS_CMPSTM0_SR0,FALSE);
    /*Hsic_stmTimIrqInit(STM0,COMPARATOR1,SRC_CPU0,INT_PRIO_CMPSTM0_SR1,INT_MS_CMPSTM0_SR0,FALSE);
    Hsic_stmTimIrqInit(STM1,COMPARATOR0,SRC_CPU0,INT_PRIO_CMPSTM1_SR0,INT_MS_CMPSTM0_SR0,FALSE);
    Hsic_stmTimIrqInit(STM1,COMPARATOR1,SRC_CPU0,INT_PRIO_CMPSTM1_SR1,INT_MS_CMPSTM0_SR0,FALSE);*/

    Hsic_uartInit(IfxAsclin0_TX_P14_0_OUT,IfxAsclin0_RXA_P14_1_IN,115200,SRC_CPU0);

    //Hsic_hwIICInit(IfxI2c0_SCL_P02_5_INOUT,IfxI2c0_SDA_P02_4_INOUT,1000);
    //hsic_swiic_dev_t dev;
    //Hsic_swIICInit(&dev,IfxPort_P02_5,IfxPort_P02_4,1000);
    /*IfxQspi_SpiMaster_Channel spi = Hsic_hwSPIInit(IfxQspi0_MRSTA_P20_12_IN,IfxQspi0_MTSR_P20_14_OUT,IfxQspi0_SCLK_P20_11_OUT,
            IfxQspi0_SLSO0_P20_8_OUT,1000,SRC_CPU0,CPOL_0_CPHA_0);*/
    /*hsic_swspi_dev_t dev = Hsic_swSPIInit(IfxPort_P20_12,IfxPort_P20_14,IfxPort_P20_11,IfxPort_P20_8,1000000,0);
    Hsic_adcInit(IfxVadc_G0_0_AN0_IN);
    Hsic_encInit(IfxGpt120_T2INA_P00_7_IN,IfxGpt120_T2EUDA_P00_8_IN,IfxGpt120_T2INA_P00_7_IN,4096,0.005,FALSE);
    hsic_enc_data_t data;
    Hsic_ccu6TimerIrqInit(CCU60,TM0,SRC_CPU0,INT_PRIO_CCU60_TM0,100);
    Hsic_ccu6TimerIrqInit(CCU60,TM1,SRC_CPU0,INT_PRIO_CCU60_TM1,100);
    Hsic_ccu6TimerIrqInit(CCU61,TM0,SRC_CPU0,INT_PRIO_CCU61_TM0,100);
    Hsic_ccu6TimerIrqInit(CCU61,TM1,SRC_CPU0,INT_PRIO_CCU61_TM1,100);*/
    //OLED_init(IfxQspi2_MRSTA_P15_4_IN,IfxQspi2_MTSR_P15_5_OUT,IfxQspi2_SCLK_P15_3_OUT,IfxQspi2_SLSO0_P15_2_OUT,IfxPort_P15_1,IfxPort_P15_0);
    IfxCpu_enableInterrupts();
    OLED_init(IfxQspi2_MRSTA_P15_4_IN,IfxQspi2_MTSR_P15_5_OUT,IfxQspi2_SCLK_P15_3_OUT,IfxQspi2_SLSO0_P15_2_OUT,IfxPort_P15_1,IfxPort_P15_0,TRUE);
    while(1)
    {
        HSIC_ASSERT(1>2);
        //static int i = 0;
        uint32 time = Hsic_systickGet(STM0);
        for(int i = 0; i < 4096;i++)
        {
            OLED_printf(0,0,"%d",i);
            OLED_printf(0,1,"%d",i);
            OLED_printf(0,2,"%d",i);
            OLED_printf(0,3,"%d",i);
            OLED_printf(0,4,"%d",i);
            OLED_printf(0,5,"%d",i);
            OLED_printf(0,6,"%d",i);

            OLED_printf(64,0,"%d",i);
            OLED_printf(64,1,"%d",i);
            OLED_printf(64,2,"%d",i);
            OLED_printf(64,3,"%d",i);
            OLED_printf(64,4,"%d",i);
            OLED_printf(64,5,"%d",i);
            OLED_printf(64,6,"%d",i);
            //OLED_printBuf();
        }
        time = Hsic_systickGet(STM0) - time;
        OLED_printf(0,7,"%d",Hsic_getMSFromTicks(STM0,time));
        //OLED_printBuf();
        while(1);
        //OLED_printf(0,0,"%d",i++);
        //OLED_printfStrToBuf(0,0,"h");
        //OLED_printBuf();
        //Hsic_DelayMS(STM0,1000);
//        OLED_fill(0xff);
//        Hsic_DelayMS(STM0,1000);
//        OLED_fill(0x00);
        //OLED_write(DATA,data);
        /*for(uint8 i = 0; i < 128; i++)
        {
            for(uint8 j = 0; j < 8; j++)
            {
                OLED_PutPixel(i,j,0xff);
                Hsic_DelayMS(STM0,10);
            }
        }
        OLED_fill(0x00);
        Hsic_DelayMS(STM0,1000);
        for(uint8 i = 0; i < 128; i++)
        {
            for(uint8 j = 0; j < 8; j++)
            {
                OLED_PutPixel(i,j,0x00);
                Hsic_DelayMS(STM0,10);
            }
        }*/
    }
    return (1);
}

void STMSTM0_SR0_CallBack(void)
{
    OLED_printBuf();
    //Hsic_gpioSetState(P21,4,TOGGLE);
}

void STMSTM0_SR1_CallBack(void)
{
    Hsic_gpioSetState(P20,9,TOGGLE);
}
void STMSTM1_SR0_CallBack(void)
{
    Hsic_gpioSetState(P21,5,TOGGLE);
}

void STMSTM1_SR1_CallBack(void)
{
    Hsic_gpioSetState(P20,8,TOGGLE);
}

void CCU60_TM0_CallBack(void)
{
    Hsic_gpioSetState(P21,4,TOGGLE);
}
void CCU60_TM1_CallBack(void)
{
    Hsic_gpioSetState(P20,9,TOGGLE);
}
void CCU61_TM0_CallBack(void)
{
    Hsic_gpioSetState(P21,5,TOGGLE);
}
void CCU61_TM1_CallBack(void)
{
    Hsic_gpioSetState(P20,8,TOGGLE);
}
