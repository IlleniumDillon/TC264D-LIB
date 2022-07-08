/*
 * OLED_SSD1306.c
 *
 *  Created on: 2022年7月7日
 *      Author: DELL
 */

#include <OLED_SSD1306.h>
#include <OLED_matrix>

oled_t oled_dev;

void OLED_init(miso_t miso, mosi_t mosi, sclk_t sclk, cs_t cs, res_t res, dc_t dc, boolean useDualBuffer)
{
    oled_dev.width = 128;
    oled_dev.height = 64;
    oled_dev.useDualBuffer = useDualBuffer;
    if(useDualBuffer)
    {
        oled_dev.displayBuffer_0 = calloc(oled_dev.width*oled_dev.height/8,sizeof(uint8));
        oled_dev.displayBuffer_1 = calloc(oled_dev.width*oled_dev.height/8,sizeof(uint8));
        oled_dev.bufferIndx = 0;
        oled_dev.needDisp = FALSE;
    }
    memcpy(&oled_dev.interface.pin.miso,&miso,sizeof(miso_t));
    memcpy(&oled_dev.interface.pin.mosi,&mosi,sizeof(mosi_t));
    memcpy(&oled_dev.interface.pin.sclk,&sclk,sizeof(sclk_t));
    memcpy(&oled_dev.interface.pin.cs,&cs,sizeof(cs_t));
    memcpy(&oled_dev.interface.pin.res,&res,sizeof(res_t));
    memcpy(&oled_dev.interface.pin.dc,&dc,sizeof(dc_t));
    OLED_hardwareInterfaceInit(&oled_dev.interface);

    oled_dev.interface.dc_write(oled_dev.interface.pin,0);

    oled_dev.interface.res_write(oled_dev.interface.pin,1);
    for(uint8 i = 0; i < 50 ;i++);
    oled_dev.interface.res_write(oled_dev.interface.pin,0);
    for(uint8 i = 0; i < 50 ;i++);
    oled_dev.interface.res_write(oled_dev.interface.pin,1);

    OLED_write(CMD,0xae);
    OLED_write(CMD,0x00);
    OLED_write(CMD,0x10);
    OLED_write(CMD,0x40);
    OLED_write(CMD,0x81);
    OLED_write(CMD,0xcf);
    OLED_write(CMD,0xa1);
    OLED_write(CMD,0xc8);

    OLED_write(CMD,0xa6);
    OLED_write(CMD,0xa8);
    OLED_write(CMD,0x3f);
    OLED_write(CMD,0xd3);
    OLED_write(CMD,0x00);
    OLED_write(CMD,0xd5);
    OLED_write(CMD,0x80);
    OLED_write(CMD,0xd9);
    OLED_write(CMD,0xf1);
    OLED_write(CMD,0xda);
    OLED_write(CMD,0x12);
    OLED_write(CMD,0xdb);
    OLED_write(CMD,0x40);
    OLED_write(CMD,0x20);
    OLED_write(CMD,0x02);

    OLED_write(CMD,0x8d);
    OLED_write(CMD,0x14);
    OLED_write(CMD,0xa4);
    OLED_write(CMD,0xa6);
    OLED_write(CMD,0xaf);

    OLED_fill(0x00);
    //OLED_setpos(0,0);
}

void OLED_write(oled_write_t type, uint8 data)
{
    oled_dev.interface.dc_write(oled_dev.interface.pin,(uint8)type);
    oled_dev.interface.spi_write(oled_dev.interface.pin,&data);
}

void OLED_fill(uint8 data)
{
    uint8 y, x;

    for (y = 0; y < 8; y++)
    {
        OLED_write(CMD,0xb0 + y);
        OLED_write(CMD,0x01);
        OLED_write(CMD,0x10);
        for (x = 0; x < 128; x++)   OLED_write(DATA,data);
    }
    if(oled_dev.useDualBuffer)
    {
        memset(oled_dev.displayBuffer_0,data,oled_dev.width*oled_dev.height/8*sizeof(uint8));
        memset(oled_dev.displayBuffer_1,data,oled_dev.width*oled_dev.height/8*sizeof(uint8));
    }
}

void OLED_setpos(uint8 x, uint8 y)
{
    OLED_write(CMD,0xb0+y);
    OLED_write(CMD,((x & 0xf0)>>4)|0x10);
    OLED_write(CMD,(x & 0x0f)|0x00);
}

void OLED_PutPixel(uint8 x, uint8 y, uint8 data)
{
    OLED_setpos(x, y);
    OLED_write(CMD,0xb0 + y);
    OLED_write(CMD,((x&0xf0) >> 4) | 0x10);
    OLED_write(CMD,(x&0x0f) | 0x00);
    OLED_write(DATA,data);
}

void OLED_printfChar(uint8* x, uint8* y, char ch)
{
    if(ch=='\n')
    {
        *x = 0;
        *y = *y + 1;
        return;
    }
    else
    {
        ch = ch - 32;
        if(*x > 127) {*x = 0; *y = *y + 1;}
        OLED_setpos(*x, *y);
        for(uint8 i = 0;i < 6;i++)
        {
            OLED_write(DATA,font[ch][i]);
        }
        *x = *x + 6;
    }
}

void OLED_printfStr(uint8 x, uint8 y, const char* format)
{
    for(uint8 i = 0; format[i]!='\0'&&i<64 ; i++)
    {
        OLED_printfChar(&x,&y,format[i]);
    }
}

void OLED_printfCharToBuf(uint8* x, uint8* y, char ch, uint8* buf)
{
    if(ch=='\n')
    {
        *x = 0;
        *y = *y + 1;
        return;
    }
    else
    {
        ch = ch - 32;
        if(*x > 127) {*x = 0; *y = *y + 8;}
        uint8* ptr = buf+128*(*y)+(*x);
        for(uint8 i = 0;i < 6;i++)
        {
            ptr[i] = font[ch][i];
        }
        *x = *x + 6;
    }
}

void OLED_printfStrToBuf(uint8 x, uint8 y, const char* format)
{
    for(uint8 i = 0; format[i]!='\0'&&i<64 ; i++)
    {
        OLED_printfCharToBuf(&x,&y,format[i],oled_dev.bufferIndx ? oled_dev.displayBuffer_1 : oled_dev.displayBuffer_0);
    }
    oled_dev.needDisp = TRUE;
}

void OLED_printf(uint8 x, uint8 y, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    char buf[64] = {0};
    vsnprintf(buf, 64, format, args);
    if(oled_dev.useDualBuffer==FALSE) OLED_printfStr(x,y,buf);
    else
    {
        OLED_printfStrToBuf(x,y,buf);
    }
    va_end(list);
}

void OLED_printBuf(void)
{
    if(oled_dev.needDisp == FALSE) return;
    uint8* nowptr = oled_dev.bufferIndx ? oled_dev.displayBuffer_1 : oled_dev.displayBuffer_0;
    uint8* lastptr = oled_dev.bufferIndx ? oled_dev.displayBuffer_0 : oled_dev.displayBuffer_1;
    for (uint8 y = 0; y < 8; y++)
    {
        //oled_dev.interface.dc_write(oled_dev.interface.pin,(uint8)1);
        for (uint8 x = 0; x < 128; x++)
        {
            if(nowptr[y*128+x]!=lastptr[y*128+x])
            {
                OLED_setpos(x, y);
                OLED_write(DATA,(oled_dev.bufferIndx ? oled_dev.displayBuffer_1 : oled_dev.displayBuffer_0)[y*128+x]);
            }
        }
    }
    oled_dev.bufferIndx = !oled_dev.bufferIndx ;
    oled_dev.needDisp = FALSE;
}
