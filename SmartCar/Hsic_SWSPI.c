/*
 * Hsic_SWSPI.c
 *
 *  Created on: 2022Äê7ÔÂ5ÈÕ
 *      Author: DELL
 */
#include <Hsic_SWSPI.h>

static void _delay(uint32 time);

static void _set_high(IfxPort_Pin pin);
static void _set_low(IfxPort_Pin pin);
static void _set_input(IfxPort_Pin pin);
static void _set_output(IfxPort_Pin pin);
static boolean _get_input(IfxPort_Pin pin);

static void _sclk_leading(IfxPort_Pin pin, uint32 time);
static void _sclk_trailing(IfxPort_Pin pin, uint32 time);

static void _start(hsic_swspi_dev_t* dev);
static void _stop(hsic_swspi_dev_t* dev);

static uint8 _exchange_byte(hsic_swspi_dev_t* dev, uint8 byte);

hsic_swspi_dev_t Hsic_swSPIInit(IfxPort_Pin miso, IfxPort_Pin mosi, IfxPort_Pin sclk, IfxPort_Pin cs,
        uint32 baudrate,uint8 mode)
{
    hsic_swspi_dev_t dev;
    dev.cs = cs;
    dev.miso = miso;
    dev.mosi = mosi;
    dev.sclk = sclk;
    dev.delaytime = IfxStm_getTicksFromMicroseconds((Ifx_STM *)STM0,1000000.0/(baudrate*4));
    _set_output(dev.cs);
    IfxPort_setPinPadDriver(dev.cs.port, dev.cs.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    _set_output(dev.sclk);
    IfxPort_setPinPadDriver(dev.sclk.port, dev.sclk.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    _set_output(dev.mosi);
    IfxPort_setPinPadDriver(dev.mosi.port, dev.mosi.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    _set_input(dev.miso);
    IfxPort_setPinPadDriver(dev.miso.port, dev.miso.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    if(mode==0)
    {
        dev.sclk_active = &_set_high;
        dev.sclk_idle = &_set_low;
        dev.sclk_effectiveedge = &_sclk_leading;
        dev.sclk_ineffectiveedge = &_sclk_trailing;
    }
    else if(mode==1)
    {
        dev.sclk_active = &_set_high;
        dev.sclk_idle = &_set_low;
        dev.sclk_effectiveedge = &_sclk_trailing;
        dev.sclk_ineffectiveedge = &_sclk_leading;
    }
    else if(mode==2)
    {
        dev.sclk_active = &_set_low;
        dev.sclk_idle = &_set_high;
        dev.sclk_effectiveedge = &_sclk_trailing;
        dev.sclk_ineffectiveedge = &_sclk_leading;
    }
    else if(mode==3)
    {
        dev.sclk_active = &_set_low;
        dev.sclk_idle = &_set_high;
        dev.sclk_effectiveedge = &_sclk_leading;
        dev.sclk_ineffectiveedge = &_sclk_trailing;
    }
    dev.sclk_idle(dev.sclk);
    _set_high(dev.mosi);
    _set_high(dev.cs);
    return dev;
}

void Hsic_swSPIExchange(hsic_swspi_dev_t* dev, uint8* ptxdata, uint8* prxdata, size_t count)
{
    _start(dev);
    for(size_t i = 0; i < count ; i++)
    {
        prxdata[i] = _exchange_byte(dev,ptxdata[i]);
    }
    _stop(dev);
}

static void _delay(uint32 time)
{
    IfxStm_waitTicks((Ifx_STM *)STM0,time);
}

static void _set_high(IfxPort_Pin pin)
{
    IfxPort_setPinState(pin.port, pin.pinIndex, IfxPort_State_high);
}

static void _set_low(IfxPort_Pin pin)
{
    IfxPort_setPinState(pin.port, pin.pinIndex, IfxPort_State_low);
}

static void _set_input(IfxPort_Pin pin)
{
    IfxPort_setPinMode(pin.port, pin.pinIndex,IfxPort_InputMode_noPullDevice);
}

static void _set_output(IfxPort_Pin pin)
{
    IfxPort_setPinMode(pin.port, pin.pinIndex,IfxPort_Mode_outputPushPullGeneral);
}

static boolean _get_input(IfxPort_Pin pin)
{
    return IfxPort_getPinState(pin.port,pin.pinIndex);
}

static void _sclk_leading(IfxPort_Pin pin, uint32 time)
{
    _delay(time);
    _set_high(pin);
    _delay(time);
}

static void _sclk_trailing(IfxPort_Pin pin, uint32 time)
{
    _delay(time);
    _set_low(pin);
    _delay(time);
}

static void _start(hsic_swspi_dev_t* dev)
{
    _delay(dev->delaytime);
    _set_low(dev->cs);
    _delay(dev->delaytime);
}

static void _stop(hsic_swspi_dev_t* dev)
{
    _delay(dev->delaytime);
    dev->sclk_idle(dev->sclk);
    _delay(dev->delaytime);
    _set_high(dev->mosi);
    _delay(dev->delaytime);
    _set_high(dev->cs);
    _delay(dev->delaytime);
}

static uint8 _exchange_byte(hsic_swspi_dev_t* dev, uint8 byte)
{
    uint8 rx = 0;
    for(uint8 i = 0 ; i < 8 ; i++)
    {
        rx<<=1;
        dev->sclk_ineffectiveedge(dev->sclk,dev->delaytime);
        if(byte & 0x80) _set_high(dev->mosi);
        else _set_low(dev->mosi);
        byte<<=1;
        dev->sclk_effectiveedge(dev->sclk,dev->delaytime);
        if(_get_input(dev->miso)) rx += 1;
    }
    return rx;
}
