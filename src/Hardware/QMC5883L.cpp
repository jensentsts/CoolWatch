

#include "QMC5883L.h"

#include <Arduino.h>
#include <driver/gpio.h>

#define IIC_SCL_L gpio_set_level(IIC_SCL, LOW);
#define IIC_SCL_H gpio_set_level(IIC_SCL, HIGH);
#define IIC_SDA_L gpio_set_level(IIC_SDA, LOW);
#define IIC_SDA_H gpio_set_level(IIC_SDA, HIGH);
#define IIC_SDA_set(x) gpio_set_level(IIC_SDA, x);

void QMC5883L_I2C_Start(void)
{
    IIC_SCL_L;
    IIC_SDA_H;
    IIC_SCL_H;
    IIC_SDA_L;
}

void QMC5883L_I2C_Stop(void)
{
    IIC_SCL_L;
    IIC_SDA_L;
    IIC_SCL_H;
    IIC_SDA_H;
}

void QMC5883L_I2C_SendByte(uint8_t dat)
{
    uint8_t i;
    // addr
    for (i = 0; i < 8; ++i)
    {
        IIC_SCL_L;
        IIC_SDA_set(dat & 1);
        IIC_SCL_H;
        dat >>= 1;
    }
    // ACK
    IIC_SCL_L;
    IIC_SCL_H;
    IIC_SCL_L;
}

void QMC5883L_I2C_ReadByte(uint8_t *dat)
{
    uint8_t i;
    *dat = 0;
    // addr
    for (i = 0; i < 8; ++i)
    {
        IIC_SCL_L;
        *dat |= gpio_get_level(IIC_SDA) << i;
        IIC_SCL_H;
    }
    // ACK
    IIC_SCL_L;
    IIC_SCL_H;
    IIC_SCL_L;
}

void QMC5883L_SendData(uint8_t addr, uint8_t dat)
{
    QMC5883L_I2C_Start();
    QMC5883L_I2C_SendByte(addr & 0x80);
    QMC5883L_I2C_SendByte(dat);
    QMC5883L_I2C_Stop();
}

uint8_t QMC5883L_ReadData(uint8_t addr, uint8_t *dat)
{
    QMC5883L_I2C_Start();
    QMC5883L_I2C_SendByte(addr & 0x00);
    QMC5883L_I2C_ReadByte(dat);
    QMC5883L_I2C_Stop();
}

void QMC5883L_PinInit(void)
{
    gpio_config_t gpio_init_structure;
    gpio_init_structure.intr_type = GPIO_INTR_DISABLE;
    gpio_init_structure.mode = GPIO_MODE_OUTPUT_OD;
    gpio_init_structure.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpio_init_structure.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_init_structure.pin_bit_mask = IIC_SCL;
    gpio_config(&gpio_init_structure);
    gpio_init_structure.pin_bit_mask = IIC_SDA;
    gpio_config(&gpio_init_structure);
    gpio_init_structure.pin_bit_mask = DRDY;
    gpio_config(&gpio_init_structure);
}

void QMC5883L_Init(void)
{
    QMC5883L_PinInit();
    QMC5883L_SendData(QMC5883L_ADDR_CFGA, QMC5883L_SETTING);
}

void QMC5883L_Start(void)
{
    QMC5883L_SendData(QMC5883L_ADDR_CFGA, QMC5883L_SETTING | QMC5883L_MODE_CONTINOUS);
}

void QMC5883L_Stop(void)
{
    QMC5883L_SendData(QMC5883L_ADDR_CFGA, QMC5883L_SETTING | 00);
}

uint16_t QMC5883L_GetXData(void)
{
    uint16_t x;
    QMC5883L_ReadData(QMC5883L_ADDR_XOUTL, (uint8_t*)(&x));
    QMC5883L_ReadData(QMC5883L_ADDR_XOUTH, (uint8_t*)(&x) + 1);
    return x;
}

uint16_t QMC5883L_GetYData(void)
{
    uint16_t x;
    QMC5883L_ReadData(QMC5883L_ADDR_YOUTL, (uint8_t*)(&x));
    QMC5883L_ReadData(QMC5883L_ADDR_YOUTH, (uint8_t*)(&x) + 1);
    return x;
}

uint16_t QMC5883L_GetZData(void)
{
    uint16_t x;
    QMC5883L_ReadData(QMC5883L_ADDR_ZOUTL, (uint8_t*)(&x));
    QMC5883L_ReadData(QMC5883L_ADDR_ZOUTH, (uint8_t*)(&x) + 1);
    return x;
}

QMC5883L_DataPackage QMC5883L_GetData(void)
{
    QMC5883L_DataPackage res = {0};
    uint16_t x = QMC5883L_GetXData(), 
            y = QMC5883L_GetYData(), 
            z = QMC5883L_GetZData();
    res.x = (double)x / 65535.0 * 360.0;
    res.y = (double)y / 65535.0 * 360.0;
    res.z = (double)z / 65535.0 * 360.0;
    return res;
}
