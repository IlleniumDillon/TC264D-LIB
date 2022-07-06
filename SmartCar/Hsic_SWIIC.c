/*
 * Hsic_SWIIC.c
 *
 *  Created on: 2022Äê7ÔÂ4ÈÕ
 *      Author: DELL
 */

#include <Hsic_SWIIC.h>

static void _delay(uint32 time);

static void _set_high(IfxPort_Pin pin);
static void _set_low(IfxPort_Pin pin);
static void _set_input(IfxPort_Pin pin);
static void _set_output(IfxPort_Pin pin);
static boolean _get_input(IfxPort_Pin pin);

static void _start(hsic_swiic_dev_t* dev);
static void _stop(hsic_swiic_dev_t* dev);
static void _send_ack(hsic_swiic_dev_t* dev, hsic_ack_t ack);
static hsic_ack_t _get_ack(hsic_swiic_dev_t* dev);

static hsic_ack_t _send_byte(hsic_swiic_dev_t* dev, uint8 byte);
static uint8 _read_byte(hsic_swiic_dev_t* dev, hsic_ack_t ack);

static hsic_ack_t _IIC_write(hsic_swiic_dev_t* dev, uint8* pdata, size_t size);
static hsic_ack_t _IIC_read(hsic_swiic_dev_t* dev, uint8* pdata, size_t size);

hsic_err_t Hsic_swIICInit(hsic_swiic_dev_t* dev, IfxPort_Pin scl, IfxPort_Pin sda, uint32 baudrate)
{
    dev->delaytime = IfxStm_getTicksFromMicroseconds((Ifx_STM *)STM0,1000000.0/(baudrate*2));
    dev->scl = scl;
    dev->sda = sda;
    dev->slaveaddr = 0xfe;
    _set_output(dev->scl);
    _set_output(dev->sda);
    IfxPort_setPinPadDriver(dev->scl.port, dev->scl.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    IfxPort_setPinPadDriver(dev->sda.port, dev->sda.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
    _set_high(dev->scl);
    _set_high(dev->sda);
    return HSIC_OK;
}

void Hsic_swIICWrite(hsic_swiic_dev_t* dev, uint8 slaveaddr, uint8* pdata, size_t size)
{
    dev->slaveaddr = slaveaddr;
    _IIC_write(dev,pdata,size);
}

void Hsic_swIICRead(hsic_swiic_dev_t* dev, uint8 slaveaddr, uint8* pdata, size_t size)
{
    dev->slaveaddr = slaveaddr;
    _IIC_read(dev,pdata,size);
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

static void _start(hsic_swiic_dev_t* dev)
{
    _set_high(dev->scl);
    _set_high(dev->sda);
    _delay(dev->delaytime);
    _set_low(dev->sda);
    _delay(dev->delaytime);
    _set_low(dev->scl);
    _delay(dev->delaytime);
}

static void _stop(hsic_swiic_dev_t* dev)
{
    _set_low(dev->scl);
    _set_low(dev->sda);
    _delay(dev->delaytime);
    _set_high(dev->scl);
    _delay(dev->delaytime);
    _set_high(dev->sda);
}

static void _send_ack(hsic_swiic_dev_t* dev, hsic_ack_t ack)
{
    _set_low(dev->scl);
    _delay(dev->delaytime);
    if(ack==ACK)_set_low(dev->sda);
    else _set_high(dev->sda);
    _set_high(dev->scl);
    _delay(dev->delaytime);
    _set_low(dev->scl);
    _delay(dev->delaytime);
}

static hsic_ack_t _get_ack(hsic_swiic_dev_t* dev)
{
    //_set_low(dev->scl);
    _set_input(dev->sda);
    //_delay(dev->delaytime);
    _set_high(dev->scl);
    _delay(dev->delaytime);
    if(_get_input(dev->sda))
    {
        _set_output(dev->sda);
        _set_low(dev->scl);
        _delay(dev->delaytime);
        return NACK;
    }
    else
    {
        _set_output(dev->sda);
        _set_low(dev->scl);
        _delay(dev->delaytime);
        return ACK;
    }
}

static hsic_ack_t _send_byte(hsic_swiic_dev_t* dev, uint8 byte)
{
    for(uint8 i = 0; i < 8 ; i++)
    {
        if(byte & 0x80) _set_high(dev->sda);
        else _set_low(dev->sda);
        byte <<= 1;
        //_delay(dev->delaytime);
        _set_high(dev->scl);
        _delay(dev->delaytime);
        _set_low(dev->scl);
        _delay(dev->delaytime);
    }
    return _get_ack(dev);
}

static uint8 _read_byte(hsic_swiic_dev_t* dev, hsic_ack_t ack)
{
    uint8 byte = 0;
    //_set_high(dev->scl);
    _set_input(dev->sda);
    for(uint8 i = 0; i < 8 ; i++)
    {
        byte<<=1;
        _set_high(dev->scl);
        _delay(dev->delaytime);
        if(_get_input(dev->sda))byte+=1;
        if(i==7)break;
        _set_low(dev->scl);
        _delay(dev->delaytime);
    }
    _set_output(dev->sda);
    _send_ack(dev,ack);
    return byte;
}

static hsic_ack_t _IIC_write(hsic_swiic_dev_t* dev, uint8* pdata, size_t size)
{
    _start(dev);
    if(_send_byte(dev,(dev->slaveaddr<<1)|0x00)==NACK)
    {
        _stop(dev);
        return NACK;
    }
    for(size_t i = 0; i < size ; i++)
    {
        _send_byte(dev,pdata[i]);
    }
    _stop(dev);
    return ACK;
}

static hsic_ack_t _IIC_read(hsic_swiic_dev_t* dev, uint8* pdata, size_t size)
{
    _start(dev);
    if(_send_byte(dev,(dev->slaveaddr<<1)|0x01)==NACK)
    {
        _stop(dev);
        return NACK;
    }
    for(size_t i = 0; i < size-1 ; i++)
    {
        pdata[i] = _read_byte(dev,ACK);
    }
    pdata[size-1] = _read_byte(dev,NACK);
    _stop(dev);
    return ACK;
}
