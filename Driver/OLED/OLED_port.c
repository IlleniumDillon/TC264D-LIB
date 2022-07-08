/*
 * OLED_port.c
 *
 *  Created on: 2022Äê7ÔÂ7ÈÕ
 *      Author: DELL
 */
#include <OLED_port.h>

void OLED_hardwareInterfaceInit(oled_hardware_interface_t* interface)
{
    interface->pin_init = &USER_pinInit;
    interface->pin_init(&interface->pin);
    interface->spi_write = &USER_spiWrite;
    interface->res_write = &USER_resWrite;
    interface->dc_write = &USER_dcWrite;
}

void USER_pinInit(oled_pin_t* pin)
{
    IfxPort_setPinMode(pin->dc.port,pin->dc.pinIndex,IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(pin->dc.port,pin->dc.pinIndex,IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinMode(pin->res.port,pin->res.pinIndex,IfxPort_Mode_outputPushPullGeneral);
    IfxPort_setPinPadDriver(pin->res.port,pin->res.pinIndex,IfxPort_PadDriver_cmosAutomotiveSpeed1);
    pin->userdata = Hsic_hwSPIInit(pin->miso,pin->mosi,pin->sclk,pin->cs,10000000,SRC_CPU0,CPOL_1_CPHA_0);
}

void USER_resWrite(oled_pin_t pin, uint8 level)
{
    if(level)
    {
        IfxPort_setPinState(pin.res.port,pin.res.pinIndex,IfxPort_State_high);
    }
    else
    {
        IfxPort_setPinState(pin.res.port,pin.res.pinIndex,IfxPort_State_low);
    }
}

void USER_dcWrite(oled_pin_t pin, uint8 level)
{
    if(level)
    {
        IfxPort_setPinState(pin.dc.port,pin.dc.pinIndex,IfxPort_State_high);
    }
    else
    {
        IfxPort_setPinState(pin.dc.port,pin.dc.pinIndex,IfxPort_State_low);
    }
}

void USER_spiWrite(oled_pin_t pin, uint8* data)
{
    Hsic_hwSPIExchange(&pin.userdata,data,NULL,1);
}

