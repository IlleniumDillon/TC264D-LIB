/*
 * Hsic_ENC.c
 *
 *  Created on: 2022Äê7ÔÂ5ÈÕ
 *      Author: DELL
 */

#include <Hsic_ENC.h>

static IfxGpt12_IncrEnc gpt12[5];

hsic_err_t Hsic_encInit(IfxGpt12_TxIn_In a, IfxGpt12_TxEud_In b, IfxGpt12_TxIn_In z, uint32 resolution, float sampletime, boolean reverse)
{
    IfxGpt12_enableModule(&MODULE_GPT120);
    IfxGpt12_setGpt1BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt1BlockPrescaler_8);
    IfxGpt12_setGpt2BlockPrescaler(&MODULE_GPT120, IfxGpt12_Gpt2BlockPrescaler_4);
    IfxGpt12_IncrEnc_Config gpt12Config;
    IfxGpt12_IncrEnc_initConfig(&gpt12Config , &MODULE_GPT120);
    gpt12Config.base.offset                    = 0;
    gpt12Config.base.reversed                  = reverse;
    gpt12Config.base.resolution                = resolution;
    gpt12Config.base.periodPerRotation         = 1;
    gpt12Config.base.resolutionFactor          = IfxStdIf_Pos_ResolutionFactor_fourFold;
    gpt12Config.base.updatePeriod              = sampletime;
    gpt12Config.base.speedModeThreshold        = 200;
    gpt12Config.base.minSpeed                  = 0;
    gpt12Config.base.maxSpeed                  = 500;
    gpt12Config.zeroIsrPriority                = 0;
    gpt12Config.zeroIsrProvider                = 0;
    gpt12Config.pinA                           = &a;
    gpt12Config.pinB                           = &b;
    gpt12Config.pinZ                           = NULL;
    gpt12Config.pinMode                        = IfxPort_InputMode_noPullDevice;
    gpt12Config.base.speedFilterEnabled        = TRUE;
    gpt12Config.base.speedFilerCutOffFrequency = gpt12Config.base.maxSpeed / 2 * IFX_PI * 2;
    IfxGpt12_IncrEnc_init(&gpt12[a.timer], &gpt12Config);
    return HSIC_OK;
}

void Hsic_encDataUpdate(hsic_enc_data_t* data, IfxGpt12_TxIn_In a)
{
    IfxGpt12_IncrEnc_update(&gpt12[a.timer]);
    data->speed = IfxGpt12_IncrEnc_getSpeed(&gpt12[a.timer]);
    data->rawPosition = IfxGpt12_IncrEnc_getRawPosition(&gpt12[a.timer]);
    data->direction = IfxGpt12_IncrEnc_getDirection(&gpt12[a.timer]);
}
