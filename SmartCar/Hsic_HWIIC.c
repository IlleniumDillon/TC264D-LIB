/*
 * Hsic_HWIIC.c
 *
 *  Created on: 2022Äê7ÔÂ4ÈÕ
 *      Author: DELL
 */
#include <Hsic_HWIIC.h>

IfxI2c_I2c i2c;
IfxI2c_I2c_Device i2cDev;

hsic_err_t Hsic_hwIICInit(IfxI2c_Scl_InOut scl, IfxI2c_Sda_InOut sda, uint32 baudrate)
{
    IfxI2c_I2c_Config config;
    IfxI2c_I2c_initConfig(&config, &MODULE_I2C0);
    const IfxI2c_Pins pins = {
         &scl,
         &sda,
         IfxPort_PadDriver_cmosAutomotiveSpeed1
     };
    config.pins = &pins;
    config.baudrate = (float32)baudrate;
    IfxI2c_I2c_initModule(&i2c, &config);
    IfxI2c_I2c_deviceConfig i2cDeviceConfig;
    IfxI2c_I2c_initDeviceConfig(&i2cDeviceConfig, &i2c);
    i2cDeviceConfig.deviceAddress = 0xff;
    IfxI2c_I2c_initDevice(&i2cDev, &i2cDeviceConfig);
    return HSIC_OK;
}



