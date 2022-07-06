/*
 * Hsic_ADC.c
 *
 *  Created on: 2022Äê7ÔÂ5ÈÕ
 *      Author: DELL
 */
#include <Hsic_ADC.h>

IfxVadc_Adc vadc;
IfxVadc_Adc_Group adcGroup[4];

hsic_err_t Hsic_adcInit(IfxVadc_Vadcg_In pin)
{
    IfxVadc_Adc_ChannelConfig adcChannelConfig;
    IfxVadc_Adc_Channel adcChannel;
    if(vadc.vadc!=NULL) goto INITADCGROUP;
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);
    IfxVadc_Adc_initModule(&vadc, &adcConfig);
INITADCGROUP:
    if(adcGroup[pin.groupId].group!=NULL) goto INITADCCH;
    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &vadc);
    adcGroupConfig.groupId = pin.groupId;
    adcGroupConfig.master = pin.groupId;
    adcGroupConfig.arbiter.requestSlotQueueEnabled          = TRUE;
    adcGroupConfig.arbiter.requestSlotScanEnabled           = TRUE;
    adcGroupConfig.arbiter.requestSlotBackgroundScanEnabled = TRUE;
    adcGroupConfig.queueRequest.triggerConfig.gatingMode          = IfxVadc_GatingMode_always;
    adcGroupConfig.scanRequest.triggerConfig.gatingMode           = IfxVadc_GatingMode_always;
    adcGroupConfig.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;
    adcGroupConfig.scanRequest.autoscanEnabled = TRUE;
    adcGroupConfig.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;
    IfxVadc_Adc_initGroup(&adcGroup[pin.groupId], &adcGroupConfig);
INITADCCH:
    IfxVadc_Adc_initChannelConfig(&adcChannelConfig, &adcGroup[pin.groupId]);
    adcChannelConfig.channelId = pin.channelId;
    adcChannelConfig.resultRegister = (IfxVadc_ChannelResult)pin.groupId;
    adcChannelConfig.backgroundChannel = TRUE;
    IfxVadc_Adc_initChannel(&adcChannel,&adcChannelConfig);
    unsigned channels = (1 << adcChannelConfig.channelId);
    unsigned mask     = channels;
    IfxVadc_Adc_setBackgroundScan(&vadc, &adcGroup[pin.groupId], channels, mask);
    IfxVadc_Adc_startBackgroundScan(&vadc);
    return HSIC_OK;
}

uint16 Hsic_adcGet(IfxVadc_Vadcg_In pin)
{
    while(IfxVadc_getScanStatus(&pin.module->G[pin.groupId])==IfxVadc_Status_channelsStillPending);
    Ifx_VADC_RES res = IfxVadc_getResult(&pin.module->G[pin.groupId],pin.channelId);
    return (res.B.RESULT&0x0fff);

}
