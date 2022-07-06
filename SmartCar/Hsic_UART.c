/*
 * Hsic_UART.c
 *
 *  Created on: 2022Äê7ÔÂ3ÈÕ
 *      Author: DELL
 */

#include <Hsic_UART.h>

IfxAsclin_Asc asc[4];

static uint8 ascTxBuffer[4][ASC_TX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

static uint8 ascRxBuffer[4][ASC_RX_BUFFER_SIZE + sizeof(Ifx_Fifo) + 8];

hsic_err_t Hsic_uartInit(IfxAsclin_Tx_Out tx, IfxAsclin_Rx_In rx, uint32 baudrate, hsic_srctos_t srctos)
{
    if(tx.module!=rx.module)return HSIC_ERR_INVALID_ARG;
    uint8 i = 0xff&(((uint32)rx.module - (uint32)&MODULE_ASCLIN0)>>2);
    IfxAsclin_Asc_Config ascConfig;
    IfxAsclin_Asc_initModuleConfig(&ascConfig, tx.module);
    ascConfig.baudrate.prescaler = 1;
    ascConfig.baudrate.baudrate = (float32)baudrate;
    // ISR priorities and interrupt target
    if(i==0)
    {
        ascConfig.interrupt.txPriority = ASCLIN0_TX_INT_PRIO;
        ascConfig.interrupt.rxPriority = ASCLIN0_RX_INT_PRIO;
        ascConfig.interrupt.erPriority = ASCLIN0_ER_INT_PRIO;
    }
    else if(i==1)
    {
        ascConfig.interrupt.txPriority = ASCLIN1_TX_INT_PRIO;
        ascConfig.interrupt.rxPriority = ASCLIN1_RX_INT_PRIO;
        ascConfig.interrupt.erPriority = ASCLIN1_ER_INT_PRIO;
    }
    else if(i==2)
    {
        ascConfig.interrupt.txPriority = ASCLIN2_TX_INT_PRIO;
        ascConfig.interrupt.rxPriority = ASCLIN2_RX_INT_PRIO;
        ascConfig.interrupt.erPriority = ASCLIN2_ER_INT_PRIO;
    }
    else if(i==3)
    {
        ascConfig.interrupt.txPriority = ASCLIN3_TX_INT_PRIO;
        ascConfig.interrupt.rxPriority = ASCLIN3_RX_INT_PRIO;
        ascConfig.interrupt.erPriority = ASCLIN3_ER_INT_PRIO;
    }
    else
    {
        return HSIC_ERR_INVALID_ARG;
    }
    ascConfig.interrupt.typeOfService =   (IfxSrc_Tos)srctos;
    // FIFO configuration
    ascConfig.txBuffer = &ascTxBuffer[i][0];
    ascConfig.txBufferSize = ASC_TX_BUFFER_SIZE;
    ascConfig.rxBuffer = &ascRxBuffer[i][0];
    ascConfig.rxBufferSize = ASC_RX_BUFFER_SIZE;
    // pin configuration
    const IfxAsclin_Asc_Pins pins = {
        NULL,                           IfxPort_InputMode_pullUp,    // CTS pin not used
        &rx,   IfxPort_InputMode_pullUp,    // Rx pin
        NULL,                           IfxPort_OutputMode_pushPull, // RTS pin not used
        &tx,   IfxPort_OutputMode_pushPull, // Tx pin
        IfxPort_PadDriver_cmosAutomotiveSpeed1
    };
    ascConfig.pins = &pins;
    IfxAsclin_Asc_initModule(&asc[i], &ascConfig);
    return HSIC_OK;
}



IFX_INTERRUPT(asclin0TxISR, 0, ASCLIN0_TX_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&asc[0]);
    ASCLIN0_TX_CallBack();
}

IFX_INTERRUPT(asclin0RxISR, 0, ASCLIN0_RX_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrReceive(&asc[0]);
    ASCLIN0_RX_CallBack();
}

IFX_INTERRUPT(asclin0ErISR, 0, ASCLIN0_ER_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrError(&asc[0]);
    ASCLIN0_ER_CallBack();
}

IFX_INTERRUPT(asclin1TxISR, 0, ASCLIN1_TX_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&asc[1]);
    ASCLIN1_TX_CallBack();
}

IFX_INTERRUPT(asclin1RxISR, 0, ASCLIN1_RX_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrReceive(&asc[1]);
    ASCLIN1_RX_CallBack();
}

IFX_INTERRUPT(asclin1ErISR, 0, ASCLIN1_ER_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrError(&asc[1]);
    ASCLIN1_ER_CallBack();
}

IFX_INTERRUPT(asclin2TxISR, 0, ASCLIN2_TX_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&asc[2]);
    ASCLIN2_TX_CallBack();
}

IFX_INTERRUPT(asclin2RxISR, 0, ASCLIN2_RX_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrReceive(&asc[2]);
    ASCLIN2_RX_CallBack();
}

IFX_INTERRUPT(asclin2ErISR, 0, ASCLIN2_ER_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrError(&asc[2]);
    ASCLIN2_ER_CallBack();
}

IFX_INTERRUPT(asclin3TxISR, 0, ASCLIN3_TX_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrTransmit(&asc[3]);
    ASCLIN3_TX_CallBack();
}

IFX_INTERRUPT(asclin3RxISR, 0, ASCLIN3_RX_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrReceive(&asc[3]);
    ASCLIN3_RX_CallBack();
}

IFX_INTERRUPT(asclin3ErISR, 0, ASCLIN3_ER_INT_PRIO)
{
    enableInterrupts();
    IfxAsclin_Asc_isrError(&asc[3]);
    ASCLIN3_ER_CallBack();
}
