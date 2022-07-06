/*
 * Hsic_PWM.c
 *
 *  Created on: 2022Äê7ÔÂ1ÈÕ
 *      Author: DELL
 */

#include <Hsic_PWM.h>

Ifx_GTM *gtm = &MODULE_GTM;
float32 frequency = 0;

hsic_err_t Hsic_pwmInit(IfxGtm_Atom_ToutMap pin, float freq, float duty)
{
    frequency = IfxGtm_Cmu_getModuleFrequency(gtm);
    IfxGtm_enable(gtm);
    IfxGtm_Cmu_setGclkFrequency(gtm, frequency);
    IfxGtm_Cmu_setClkFrequency(gtm, IfxGtm_Cmu_Clk_0, frequency);
    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
    IfxGtm_Atom_Pwm_Config atomConfig;
    IfxGtm_Atom_Pwm_Driver atomHandle;
    IfxGtm_Atom_Pwm_initConfig(&atomConfig, gtm);
    atomConfig.atom = pin.atom;
    atomConfig.atomChannel  = pin.channel;
    atomConfig.period = (uint32)(frequency / freq);
    atomConfig.dutyCycle = (uint32)(duty * frequency / freq);
    atomConfig.pin.outputPin = &pin;
    atomConfig.synchronousUpdateEnabled = TRUE;
    IfxGtm_Atom_Pwm_init(&atomHandle, &atomConfig);
    IfxGtm_Atom_Pwm_start(&atomHandle, TRUE);
    return HSIC_OK;
}

hsic_err_t Hsic_pwmSetDuty(IfxGtm_Atom_ToutMap pin, float duty)
{
    uint32 period;
    period = IfxGtm_Atom_Ch_getCompareZero(&gtm->ATOM[pin.atom], pin.channel);
    IfxGtm_Atom_Ch_setCompareOneShadow(&gtm->ATOM[pin.atom], pin.channel, (uint32)(duty * period));
    return HSIC_OK;
}

hsic_err_t Hsic_pwmSetFreq(IfxGtm_Atom_ToutMap pin, float freq)
{
    uint32 period,dutyCycle;
    period = IfxGtm_Atom_Ch_getCompareZero(&gtm->ATOM[pin.atom], pin.channel);
    dutyCycle = IfxGtm_Atom_Ch_getCompareOne(&gtm->ATOM[pin.atom], pin.channel);
    float duty = (float)dutyCycle / period;
    IfxGtm_Atom_Ch_setCompareZeroShadow(&gtm->ATOM[pin.atom], pin.channel,(uint32)(frequency / freq));
    IfxGtm_Atom_Ch_setCompareOneShadow(&gtm->ATOM[pin.atom], pin.channel,(uint32)(duty * frequency / freq));
    return HSIC_OK;
}

hsic_err_t Hsic_pwmSetFreqDuty(IfxGtm_Atom_ToutMap pin, float freq, float duty)
{
    IfxGtm_Atom_Ch_setCompareZeroShadow(&gtm->ATOM[pin.atom], pin.channel,(uint32)(frequency / freq));
    IfxGtm_Atom_Ch_setCompareOneShadow(&gtm->ATOM[pin.atom], pin.channel,(uint32)(duty * frequency / freq));
    return HSIC_OK;
}
