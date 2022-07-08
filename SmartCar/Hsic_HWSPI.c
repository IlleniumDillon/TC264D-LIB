/*
 * Hsic_HWSPI.c
 *
 *  Created on: 2022Äê7ÔÂ4ÈÕ
 *      Author: DELL
 */
#include <Hsic_HWSPI.h>

IfxQspi_SpiMaster spi[4];

IfxQspi_SpiMaster_Channel Hsic_hwSPIInit(IfxQspi_Mrst_In miso, IfxQspi_Mtsr_Out mosi, IfxQspi_Sclk_Out sclk, IfxQspi_Slso_Out cs,
        uint32 baudrate, hsic_srctos_t srctos, hsic_qspi_mode_t mode)
{
    IfxQspi_SpiMaster_Channel spiMasterChannel;
    memset(&spiMasterChannel,0,sizeof(spiMasterChannel));
    IfxQspi_SpiMaster_ChannelConfig spiMasterChannelConfig;
    if(miso.module!=mosi.module||miso.module!=sclk.module||miso.module!=cs.module) return spiMasterChannel;
    uint32 t = (uint32)miso.module-0xF0001C00u;
    uint8 i = 0xff&(t>>8);
    if(spi[i].qspi!=NULL)
    {
        goto INITQSPICH;
    }
    else if(spi[i].qspi!=miso.module&&spi[i].qspi!=NULL)
    {
        return spiMasterChannel;
    }
    IfxQspi_SpiMaster_Config spiMasterConfig;
    IfxQspi_SpiMaster_initModuleConfig(&spiMasterConfig, miso.module);
    spiMasterConfig.base.mode             = SpiIf_Mode_master;
    spiMasterConfig.base.maximumBaudrate  = 10000000;
    switch(i)
    {
        case 0:
        {
            spiMasterConfig.base.txPriority       = INT_PRIO_QSPI0_TX;
            spiMasterConfig.base.rxPriority       = INT_PRIO_QSPI0_RX;
            spiMasterConfig.base.erPriority       = INT_PRIO_QSPI0_ER;
            break;
        }
        case 1:
        {
            spiMasterConfig.base.txPriority       = INT_PRIO_QSPI1_TX;
            spiMasterConfig.base.rxPriority       = INT_PRIO_QSPI1_RX;
            spiMasterConfig.base.erPriority       = INT_PRIO_QSPI1_ER;
            break;
        }
        case 2:
        {
            spiMasterConfig.base.txPriority       = INT_PRIO_QSPI2_TX;
            spiMasterConfig.base.rxPriority       = INT_PRIO_QSPI2_RX;
            spiMasterConfig.base.erPriority       = INT_PRIO_QSPI2_ER;
            break;
        }
        case 3:
        {
            spiMasterConfig.base.txPriority       = INT_PRIO_QSPI3_TX;
            spiMasterConfig.base.rxPriority       = INT_PRIO_QSPI3_RX;
            spiMasterConfig.base.erPriority       = INT_PRIO_QSPI3_ER;
            break;
        }
    }
    spiMasterConfig.base.isrProvider      = (IfxSrc_Tos)srctos;
    const IfxQspi_SpiMaster_Pins pins = {
        &sclk, IfxPort_OutputMode_pushPull, // SCLK
        &mosi, IfxPort_OutputMode_pushPull, // MTSR
        &miso, IfxPort_InputMode_pullDown,  // MRST
        IfxPort_PadDriver_cmosAutomotiveSpeed1 // pad driver mode
    };
    spiMasterConfig.pins = &pins;
    IfxQspi_SpiMaster_initModule(&spi[i], &spiMasterConfig);
INITQSPICH:
    IfxQspi_SpiMaster_initChannelConfig(&spiMasterChannelConfig, &spi[i]);
    spiMasterChannelConfig.base.baudrate = (float32)baudrate;
    spiMasterChannelConfig.base.mode.clockPolarity = (mode/2);
    spiMasterChannelConfig.base.mode.shiftClock = (1-mode%2);
    const IfxQspi_SpiMaster_Output slsOutput = {
        &cs,
        IfxPort_OutputMode_pushPull,
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    spiMasterChannelConfig.sls.output = slsOutput;
    IfxQspi_SpiMaster_initChannel(&spiMasterChannel, &spiMasterChannelConfig);
    return spiMasterChannel;
}

IFX_INTERRUPT(qspi0TxISR, 0, INT_PRIO_QSPI0_TX)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrTransmit(&spi[0]);
    QSPI0_TX_CallBack();
}

IFX_INTERRUPT(qspi0RxISR, 0, INT_PRIO_QSPI0_RX)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrReceive(&spi[0]);
    QSPI0_RX_CallBack();
}

IFX_INTERRUPT(qspi0ErISR, 0, INT_PRIO_QSPI0_ER)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrError(&spi[0]);
    QSPI0_ER_CallBack();
}

IFX_INTERRUPT(qspi1TxISR, 0, INT_PRIO_QSPI1_TX)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrTransmit(&spi[1]);
    QSPI1_TX_CallBack();
}

IFX_INTERRUPT(qspi1RxISR, 0, INT_PRIO_QSPI1_RX)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrReceive(&spi[1]);
    QSPI1_RX_CallBack();
}

IFX_INTERRUPT(qspi1ErISR, 0, INT_PRIO_QSPI1_ER)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrError(&spi[1]);
    QSPI1_ER_CallBack();
}

IFX_INTERRUPT(qspi2TxISR, 0, INT_PRIO_QSPI2_TX)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrTransmit(&spi[2]);
    QSPI2_TX_CallBack();
}

IFX_INTERRUPT(qspi2RxISR, 0, INT_PRIO_QSPI2_RX)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrReceive(&spi[2]);
    QSPI2_RX_CallBack();
}

IFX_INTERRUPT(qspi2ErISR, 0, INT_PRIO_QSPI2_ER)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrError(&spi[2]);
    QSPI2_ER_CallBack();
}

IFX_INTERRUPT(qspi3TxISR, 0, INT_PRIO_QSPI3_TX)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrTransmit(&spi[3]);
    QSPI3_TX_CallBack();
}

IFX_INTERRUPT(qspi3RxISR, 0, INT_PRIO_QSPI3_RX)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrReceive(&spi[3]);
    QSPI3_RX_CallBack();
}

IFX_INTERRUPT(qspi3ErISR, 0, INT_PRIO_QSPI3_ER)
{
    enableInterrupts();
    IfxQspi_SpiMaster_isrError(&spi[3]);
    QSPI3_ER_CallBack();
}
