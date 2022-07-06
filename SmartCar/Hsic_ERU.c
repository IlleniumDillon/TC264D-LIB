/*
 * Hsic_ERU.c
 *
 *  Created on: 2022Äê7ÔÂ1ÈÕ
 *      Author: DELL
 */

#include <Hsic_ERU.h>

hsic_err_t Hsic_eruPinInit(IfxScu_Req_In pin, hsic_trigger_t trigger, hsic_srctos_t srctos, uint8 prio)
{
    boolean interrupt_state = disableInterrupts();
    IfxScuEru_initReqPin(&pin, IfxPort_InputMode_pullUp);
    IfxScuEru_enableFallingEdgeDetection(pin.channelId);
    IfxScuEru_enableRisingEdgeDetection(pin.channelId);
    if(trigger==RISING)IfxScuEru_disableFallingEdgeDetection(pin.channelId);
    else if(trigger==FALLING)IfxScuEru_disableRisingEdgeDetection(pin.channelId);
    IfxScuEru_enableTriggerPulse(pin.channelId);
    IfxScuEru_connectTrigger(pin.channelId,pin.channelId);
    IfxScuEru_setFlagPatternDetection(pin.channelId,pin.channelId,TRUE);
    IfxScuEru_enablePatternDetectionTrigger(pin.channelId);
    IfxScuEru_setInterruptGatingPattern(pin.channelId,IfxScuEru_InterruptGatingPattern_alwaysActive);
    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)pin.channelId % 4];
    IfxSrc_init(src,(IfxSrc_Tos)srctos,prio);
    IfxSrc_enable(src);
    restoreInterrupts(interrupt_state);
    return HSIC_OK;
}

hsic_err_t Hsic_eruEnable(IfxScu_Req_In pin)
{
    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)pin.channelId % 4];
    IfxSrc_enable(src);
    return HSIC_OK;
}

hsic_err_t Hsic_eruDisable(IfxScu_Req_In pin)
{
    volatile Ifx_SRC_SRCR *src = &MODULE_SRC.SCU.SCU.ERU[(int)pin.channelId % 4];
    IfxSrc_disable(src);
    return HSIC_OK;
}

IFX_INTERRUPT(eru_ch0_ch4_isr, 0, ERU_CH0_CH4_INT_PRIO)
{
    enableInterrupts();
    if(IfxScuEru_getEventFlagStatus(ERUCH0_P15_4.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH0_P15_4.channelId);
        ERUCH0_P15_4_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH0_P10_7.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH0_P10_7.channelId);
        ERUCH0_P10_7_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH4_P33_7.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH4_P33_7.channelId);
        ERUCH4_P33_7_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH4_P15_5.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH4_P15_5.channelId);
        ERUCH4_P15_5_CallBack();
    }
}

IFX_INTERRUPT(eru_ch1_ch5_isr, 0, ERU_CH1_CH5_INT_PRIO)
{
    enableInterrupts();
    if(IfxScuEru_getEventFlagStatus(ERUCH1_P14_3.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH1_P14_3.channelId);
        ERUCH1_P14_3_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH1_P10_8.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH1_P10_8.channelId);
        ERUCH1_P10_8_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH5_P15_8.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH5_P15_8.channelId);
        ERUCH5_P15_8_CallBack();
    }
}

IFX_INTERRUPT(eru_ch2_ch6_isr, 0, ERU_CH2_CH6_INT_PRIO)
{
    enableInterrupts();
    if(IfxScuEru_getEventFlagStatus(ERUCH2_P02_1.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH2_P02_1.channelId);
        ERUCH2_P02_1_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH2_P10_2.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH2_P10_2.channelId);
        ERUCH2_P10_2_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH2_P00_4.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH2_P00_4.channelId);
        ERUCH2_P00_4_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH6_P11_10.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH6_P11_10.channelId);
        ERUCH6_P11_10_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH6_P20_0.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH6_P20_0.channelId);
        ERUCH6_P20_0_CallBack();
    }
}

IFX_INTERRUPT(eru_ch3_ch7_isr, 0, ERU_CH3_CH7_INT_PRIO)
{
    enableInterrupts();
    if(IfxScuEru_getEventFlagStatus(ERUCH3_P14_1.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH3_P14_1.channelId);
        ERUCH3_P14_1_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH3_P10_3.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH3_P10_3.channelId);
        ERUCH3_P10_3_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH3_P02_0.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH3_P02_0.channelId);
        ERUCH3_P02_0_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH7_P20_9.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH7_P20_9.channelId);
        ERUCH7_P20_9_CallBack();
    }
    if(IfxScuEru_getEventFlagStatus(ERUCH7_P15_1.channelId))
    {
        IfxScuEru_clearEventFlag(ERUCH7_P15_1.channelId);
        ERUCH7_P15_1_CallBack();
    }
}

