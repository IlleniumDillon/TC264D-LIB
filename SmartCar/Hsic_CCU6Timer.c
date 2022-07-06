/*
 * Hsic_CCU6Timer.c
 *
 *  Created on: 2022Äê7ÔÂ6ÈÕ
 *      Author: DELL
 */
#include <Hsic_CCU6Timer.h>

hsic_err_t Hsic_ccu6TimerIrqInit(hsic_ccu6_t ccu6, hsic_ccu6_timer_t tm, hsic_srctos_t srctos, uint8 prio, uint32 ms)
{
    boolean interrupt_state = disableInterrupts();
    uint64 timer_input_clk;
    uint32 timer_period;
    IfxCcu6_Timer timer;
    IfxCcu6_Timer_Config timerConfig;
    IfxCcu6_Timer_initModuleConfig(&timerConfig, (Ifx_CCU6*)ccu6);
    timer_input_clk = IfxScuCcu_getSpbFrequency();
    uint8 i = 0;
    while(i<16)
    {
        timer_period = (uint32)(timer_input_clk * ms / 1000);
        if(timer_period < 0xffff)   break;
        timer_input_clk >>= 1;
        i++;
    }
    if(16 <= i) return HSIC_ERR_INVALID_ARG;

    switch(tm)
    {
        case TM0:
        {
            if(CCU60 == ccu6)
            {
                timerConfig.interrupt1.typeOfService  = (IfxSrc_Tos)srctos;
                timerConfig.interrupt1.priority       = INT_PRIO_CCU60_TM0;
            }
            else
            {

                timerConfig.interrupt1.typeOfService  = (IfxSrc_Tos)srctos;
                timerConfig.interrupt1.priority       = INT_PRIO_CCU61_TM0;
            }
            timerConfig.timer = IfxCcu6_TimerId_t12;
            timerConfig.interrupt1.source         = IfxCcu6_InterruptSource_t12PeriodMatch;
            timerConfig.interrupt1.serviceRequest = IfxCcu6_ServiceRequest_1;
            timerConfig.base.t12Period            = timer_period;
            timerConfig.base.t12Frequency         = (float)timer_input_clk;
            timerConfig.clock.t12countingInputMode = IfxCcu6_CountingInputMode_internal;
        }break;

        case TM1:
        {
            if(CCU60 == ccu6)
            {
                timerConfig.interrupt2.typeOfService  = (IfxSrc_Tos)srctos;
                timerConfig.interrupt2.priority       = INT_PRIO_CCU60_TM1;
            }
            else
            {
                timerConfig.interrupt2.typeOfService  = (IfxSrc_Tos)srctos;
                timerConfig.interrupt2.priority       = INT_PRIO_CCU61_TM1;
            }
            timerConfig.timer = IfxCcu6_TimerId_t13;
            timerConfig.interrupt2.source         = IfxCcu6_InterruptSource_t13PeriodMatch;
            timerConfig.interrupt2.serviceRequest = IfxCcu6_ServiceRequest_2;
            timerConfig.base.t13Period            = timer_period;
            timerConfig.base.t13Frequency         = (float)timer_input_clk;
            timerConfig.clock.t13countingInputMode = IfxCcu6_CountingInputMode_internal;
        }break;
    }
    timerConfig.timer12.counterValue = 0;
    timerConfig.timer13.counterValue = 0;
    timerConfig.trigger.t13InSyncWithT12 = FALSE;
    IfxCcu6_Timer_initModule(&timer, &timerConfig);
    restoreInterrupts(interrupt_state);
    IfxCcu6_setSuspendMode((Ifx_CCU6*)ccu6, IfxCcu6_SuspendMode_hard);
    IfxCcu6_Timer_start(&timer);
    return HSIC_OK;
}

IFX_INTERRUPT(ccu60ISR_Timer0, 0, INT_PRIO_CCU60_TM0)
{
    enableInterrupts();
    IfxCcu6_clearInterruptStatusFlag((Ifx_CCU6*)CCU60,IfxCcu6_InterruptSource_t12PeriodMatch);
    CCU60_TM0_CallBack();
}

IFX_INTERRUPT(ccu60ISR_Timer1, 0, INT_PRIO_CCU60_TM1)
{
    enableInterrupts();
    IfxCcu6_clearInterruptStatusFlag((Ifx_CCU6*)CCU60,IfxCcu6_InterruptSource_t13PeriodMatch);
    CCU60_TM1_CallBack();
}

IFX_INTERRUPT(ccu61ISR_Timer0, 0, INT_PRIO_CCU61_TM0)
{
    enableInterrupts();
    IfxCcu6_clearInterruptStatusFlag((Ifx_CCU6*)CCU61,IfxCcu6_InterruptSource_t12PeriodMatch);
    CCU61_TM0_CallBack();
}

IFX_INTERRUPT(ccu61ISR_Timer1, 0, INT_PRIO_CCU61_TM1)
{
    enableInterrupts();
    IfxCcu6_clearInterruptStatusFlag((Ifx_CCU6*)CCU61,IfxCcu6_InterruptSource_t13PeriodMatch);
    CCU61_TM1_CallBack();
}
