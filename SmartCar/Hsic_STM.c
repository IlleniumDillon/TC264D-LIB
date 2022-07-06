/*
 * Hsic_STM.c
 *
 *  Created on: 2022Äê7ÔÂ2ÈÕ
 *      Author: DELL
 */
#include <Hsic_STM.h>

#ifdef USE_TIMER

IfxStm_Timer Timers[4] = {{.stm = (Ifx_STM *)STM0,.comparator = (IfxStm_Comparator)COMPARATOR0},
                         {.stm = (Ifx_STM *)STM0,.comparator = (IfxStm_Comparator)COMPARATOR1},
                         {.stm = (Ifx_STM *)STM1,.comparator = (IfxStm_Comparator)COMPARATOR0},
                         {.stm = (Ifx_STM *)STM1,.comparator = (IfxStm_Comparator)COMPARATOR1}};

#endif

#ifdef USE_CMP

hsic_err_t Hsic_stmCmpIrqInit(hsic_stm_t stm, hsic_stm_comparator_t cmp, hsic_srctos_t srctos, uint8 prio, uint32 ms)
{
    boolean interrupt_state = disableInterrupts();
    IfxStm_CompareConfig stmConfig;
    IfxStm_initCompareConfig(&stmConfig);
    sint32 ticks = IfxStm_getTicksFromMilliseconds((Ifx_STM *)stm,ms);
    stmConfig.ticks = ticks;
    stmConfig.comparator = (IfxStm_Comparator)cmp;
    stmConfig.comparatorInterrupt = (IfxStm_ComparatorInterrupt)cmp;
    stmConfig.triggerPriority = prio;
    stmConfig.typeOfService = (IfxSrc_Tos)srctos;
    IfxStm_initCompare((Ifx_STM *)stm, &stmConfig);
    restoreInterrupts(interrupt_state);
    return HSIC_OK;
}

#endif

#ifdef USE_TIMER

hsic_err_t Hsic_stmTimIrqInit(hsic_stm_t stm, hsic_stm_comparator_t cmp, hsic_srctos_t srctos, uint8 prio, uint32 ms, boolean once)
{
    boolean interrupt_state = disableInterrupts();
    uint8 i = 0;
    if((Ifx_STM *)stm == &MODULE_STM1)i=2;
    if(cmp == 1)i+=1;
    IfxStm_Timer_Config timerConfig;
    IfxStm_Timer_initConfig(&timerConfig, (Ifx_STM *)stm);
    timerConfig.base.frequency       = 1000.0/ms;
    timerConfig.base.isrPriority     = prio;
    timerConfig.base.isrProvider     = (IfxSrc_Tos)srctos;
    timerConfig.base.minResolution   = (1.0 / timerConfig.base.frequency) / 1000;
    timerConfig.comparator           = (IfxStm_Comparator)cmp;
    IfxStm_Timer_init(&Timers[i], &timerConfig);
    IfxStm_Timer_setSingleMode(&Timers[i],once);
    restoreInterrupts(interrupt_state);
    IfxStm_Timer_run(&Timers[i]);
    return HSIC_OK;
}

#endif

#ifdef USE_CMP

IFX_INTERRUPT(stm0Sr0ISR, 0, INT_PRIO_CMPSTM0_SR0)
{
    enableInterrupts();
    IfxStm_clearCompareFlag((Ifx_STM *)STM0, (IfxStm_Comparator)COMPARATOR0);
    IfxStm_increaseCompare((Ifx_STM *)STM0, (IfxStm_Comparator)COMPARATOR0, IfxStm_getTicksFromMilliseconds((Ifx_STM *)STM0,INT_MS_CMPSTM0_SR0));
    STMSTM0_SR0_CallBack();
}

IFX_INTERRUPT(stm0Sr1ISR, 0, INT_PRIO_CMPSTM0_SR1)
{
    enableInterrupts();
    IfxStm_clearCompareFlag((Ifx_STM *)STM0, (IfxStm_Comparator)COMPARATOR1);
    IfxStm_increaseCompare((Ifx_STM *)STM0, (IfxStm_Comparator)COMPARATOR1, IfxStm_getTicksFromMilliseconds((Ifx_STM *)STM0,INT_MS_CMPSTM0_SR1));
    STMSTM0_SR1_CallBack();
}

IFX_INTERRUPT(stm1Sr0ISR, 0, INT_PRIO_CMPSTM1_SR0)
{
    enableInterrupts();
    IfxStm_clearCompareFlag((Ifx_STM *)STM1, (IfxStm_Comparator)COMPARATOR0);
    IfxStm_increaseCompare((Ifx_STM *)STM1, (IfxStm_Comparator)COMPARATOR0, IfxStm_getTicksFromMilliseconds((Ifx_STM *)STM1,INT_MS_CMPSTM1_SR0));
    STMSTM1_SR0_CallBack();
}

IFX_INTERRUPT(stm1Sr1ISR, 0, INT_PRIO_CMPSTM1_SR1)
{
    enableInterrupts();
    IfxStm_clearCompareFlag((Ifx_STM *)STM1, (IfxStm_Comparator)COMPARATOR1);
    IfxStm_increaseCompare((Ifx_STM *)STM1, (IfxStm_Comparator)COMPARATOR1, IfxStm_getTicksFromMilliseconds((Ifx_STM *)STM1,INT_MS_CMPSTM1_SR1));
    STMSTM1_SR1_CallBack();
}

#endif

#ifdef USE_TIMER

IFX_INTERRUPT(stm0Sr0ISR, 0, INT_PRIO_CMPSTM0_SR0)
{
    enableInterrupts();
    IfxStm_Timer_acknowledgeTimerIrq(&Timers[0]);
    STMSTM0_SR0_CallBack();
    IfxStm_Timer_run(&Timers[0]);
}

IFX_INTERRUPT(stm0Sr1ISR, 0, INT_PRIO_CMPSTM0_SR1)
{
    enableInterrupts();
    IfxStm_Timer_acknowledgeTimerIrq(&Timers[1]);
    STMSTM0_SR1_CallBack();
    IfxStm_Timer_run(&Timers[1]);
}

IFX_INTERRUPT(stm1Sr0ISR, 0, INT_PRIO_CMPSTM1_SR0)
{
    enableInterrupts();
    IfxStm_Timer_acknowledgeTimerIrq(&Timers[2]);
    STMSTM1_SR0_CallBack();
    IfxStm_Timer_run(&Timers[2]);
}

IFX_INTERRUPT(stm1Sr1ISR, 0, INT_PRIO_CMPSTM1_SR1)
{
    enableInterrupts();
    IfxStm_Timer_acknowledgeTimerIrq(&Timers[3]);
    STMSTM1_SR1_CallBack();
    IfxStm_Timer_run(&Timers[3]);
}

#endif
